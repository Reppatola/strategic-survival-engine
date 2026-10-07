use crate::slice::*;
use crate::volume::{highest_z_local, highest_z_zombie};
use std::sync::OnceLock;

// ============================================================
// ЦВЕТ ЧАСТИ ГЕРОЯ
// ============================================================
fn color_for_part(part: u8, z: f32) -> u32 {
    let base: u32 = match part {
        PART_HEAD => 0xFF4A3520,
        PART_TORSO_UP => 0xFF2E3D5E,
        PART_TORSO_LOW => 0xFF283044,
        PART_ARM_LEFT => 0xFF2E3D5E,
        PART_ARM_RIGHT => 0xFF2E3D5E,
        PART_LEG_LEFT => 0xFF1E2436,
        PART_LEG_RIGHT => 0xFF1E2436,
        PART_FOOT_LEFT => 0xFF141414,
        PART_FOOT_RIGHT => 0xFF141414,
        PART_CAP => 0xFF5A8AB8,
        PART_BACKPACK => 0xFF4A5A3A,
        PART_STRAP_L => 0xFF2A1F18,
        PART_STRAP_R => 0xFF2A1F18,
        PART_FACE => 0xFFDCB48C,
        PART_EAR_L => 0xFFDCB48C,
        PART_EAR_R => 0xFFDCB48C,
        PART_NOSE => 0xFFDCB48C,
        _ => return 0,
    };

    let br = 0.7 + (z / 175.0) * 0.3;
    let r = (((base >> 16) & 0xFF) as f32 * br) as u32;
    let g = (((base >> 8) & 0xFF) as f32 * br) as u32;
    let b = ((base & 0xFF) as f32 * br) as u32;

    0xFF000000 | (r.min(255) << 16) | (g.min(255) << 8) | b.min(255)
}

// ============================================================
// ЦВЕТ ЧАСТИ ЗОМБИ
// ============================================================
fn color_zombie(part: u8, z: f32) -> u32 {
    let base: u32 = match part {
        ZPART_HEAD => 0xFFA8B8A0,
        ZPART_TORSO_UP => 0xFF3A2E28,
        ZPART_TORSO_LOW => 0xFF2A2420,
        ZPART_ARM_LEFT => 0xFFA8B8A0,
        ZPART_ARM_RIGHT => 0xFFA8B8A0,
        ZPART_LEG_LEFT => 0xFF3A2E28,
        ZPART_LEG_RIGHT => 0xFF3A2E28,
        ZPART_FOOT_LEFT => 0xFF1A1510,
        ZPART_FOOT_RIGHT => 0xFF1A1510,
        _ => return 0,
    };

    let br = 0.7 + (z / 175.0) * 0.3;
    let r = (((base >> 16) & 0xFF) as f32 * br) as u32;
    let g = (((base >> 8) & 0xFF) as f32 * br) as u32;
    let b = ((base & 0xFF) as f32 * br) as u32;

    0xFF000000 | (r.min(255) << 16) | (g.min(255) << 8) | b.min(255)
}

// ============================================================
// РЕНДЕР ГЕРОЯ (вид строго сверху)
// ============================================================
pub unsafe fn render_hero(
    buffer: *mut u32,
    width: i32,
    height: i32,
    cx: i32,
    cy: i32,
    facing: f32,
    scale: f32,
    pose: u32,
    anim_phase: f32,
) {
    let (arm_amp, leg_amp) = crate::animation::amplitudes_for(pose);

    let s = anim_phase.sin();

    let swing = Swing {
        arm_left: -arm_amp * s,
        arm_right: arm_amp * s,
        leg_left: leg_amp * s,
        leg_right: -leg_amp * s,
    };

    let max_local: f32 = 30.0;
    let px_max = (max_local * scale) as i32 + 2;
    let py_max = (max_local * scale) as i32 + 2;

    let ca = facing.cos();
    let sa = facing.sin();

    for dy in -py_max..=py_max {
        for dx in -px_max..=px_max {
            let px = cx + dx;
            let py = cy + dy;

            if px < 0 || px >= width {
                continue;
            }
            if py < 0 || py >= height {
                continue;
            }

            let wx = dx as f32 / scale;
            let wy = dy as f32 / scale;

            let lx = wx * ca - wy * sa;
            let ly = wx * sa + wy * ca;

            let mut part: u8 = 255;
            let z = highest_z_local(lx, ly, &mut part, &swing);

            if z >= 0.0 && part < 17 {
                let idx = (py * width + px) as usize;
                *buffer.add(idx) = color_for_part(part, z);
            }
        }
    }
}

// ============================================================
// СПРАЙТ-КЭШ ЗОМБИ
//
// Один раз при старте строим 48 спрайтов (4 pose × 12 phase).
// При рендере — просто копируем пиксели.
// ============================================================
const SPRITE_SIZE: i32 = 128;
const SPRITE_HALF: i32 = SPRITE_SIZE / 2;
const SPRITE_SCALE: f32 = 1.5;

const PHASE_STEPS: usize = 12;
const POSE_COUNT: usize = 4;
const SPRITE_TOTAL: usize = PHASE_STEPS * POSE_COUNT;

struct ZombieSprite {
    pixels: Vec<u32>,
    min_x: i32,
    max_x: i32,
    min_y: i32,
    max_y: i32,
}

struct SpriteCache {
    sprites: Vec<ZombieSprite>,
}

static SPRITE_CACHE: OnceLock<Box<SpriteCache>> = OnceLock::new();

fn build_sprite(pose: u32, phase: f32) -> ZombieSprite {
    let n = (SPRITE_SIZE * SPRITE_SIZE) as usize;
    let mut pixels = vec![0u32; n];

    let (arm_amp, leg_amp) = match pose {
        1 => (0.10f32, 0.10f32),
        2 => (0.15f32, 0.15f32),
        _ => (0.0f32, 0.0f32),
    };
    let s = phase.sin();
    let swing = Swing {
        arm_left: -arm_amp * s,
        arm_right: arm_amp * s,
        leg_left: leg_amp * s,
        leg_right: -leg_amp * s,
    };

    let mut min_x = SPRITE_SIZE;
    let mut max_x = 0;
    let mut min_y = SPRITE_SIZE;
    let mut max_y = 0;

    for py in 0..SPRITE_SIZE {
        for px in 0..SPRITE_SIZE {
            let wx = (px - SPRITE_HALF) as f32 / SPRITE_SCALE;
            let wy = (py - SPRITE_HALF) as f32 / SPRITE_SCALE;

            let mut part: u8 = 255;
            let z = highest_z_zombie(wx, wy, &mut part, &swing);

            if z >= 0.0 && part < 29 {
                let color = color_zombie(part, z);
                pixels[(py * SPRITE_SIZE + px) as usize] = color;
                if px < min_x {
                    min_x = px;
                }
                if px > max_x {
                    max_x = px;
                }
                if py < min_y {
                    min_y = py;
                }
                if py > max_y {
                    max_y = py;
                }
            }
        }
    }

    ZombieSprite {
        pixels,
        min_x,
        max_x,
        min_y,
        max_y,
    }
}

fn build_sprites() -> Box<SpriteCache> {
    let mut sprites = Vec::with_capacity(SPRITE_TOTAL);
    for pose in 0..POSE_COUNT {
        for phi in 0..PHASE_STEPS {
            let phase = (phi as f32 / PHASE_STEPS as f32) * 6.2831853;
            sprites.push(build_sprite(pose as u32, phase));
        }
    }
    Box::new(SpriteCache { sprites })
}

fn get_sprites() -> &'static SpriteCache {
    SPRITE_CACHE.get_or_init(build_sprites)
}

fn sprite_index(pose: u32, phase: f32) -> usize {
    let p = (pose as usize).min(POSE_COUNT - 1);
    let mut t = phase / 6.2831853;
    t = t - t.floor();
    let phi = (t * PHASE_STEPS as f32) as usize;
    let phi = phi.min(PHASE_STEPS - 1);
    p * PHASE_STEPS + phi
}

// ============================================================
// РЕНДЕР ЗОМБИ ИЗ СПРАЙТА
// ============================================================
pub unsafe fn render_zombie(
    buffer: *mut u32,
    width: i32,
    height: i32,
    cx: i32,
    cy: i32,
    facing: f32,
    scale: f32,
    pose: u32,
    anim_phase: f32,
    obs_height_cm: f32,
    fade: f32,
) {
    if fade <= 0.02 {
        return;
    }

    let sprites = get_sprites();
    let gi = sprite_index(pose, anim_phase);
    let sprite = &sprites.sprites[gi];

    // Перспективное масштабирование
    let persp = obs_height_cm / (obs_height_cm - 90.0);
    let final_scale = scale * persp / SPRITE_SCALE;

    let ca = facing.cos();
    let sa = facing.sin();

    for sy in sprite.min_y..=sprite.max_y {
        for sx in sprite.min_x..=sprite.max_x {
            let idx = (sy * SPRITE_SIZE + sx) as usize;
            let color = sprite.pixels[idx];
            if color == 0 {
                continue;
            }

            let lx = (sx - SPRITE_HALF) as f32;
            let ly = (sy - SPRITE_HALF) as f32;

            // Обратный поворот
            let rx = lx * ca - ly * sa;
            let ry = lx * sa + ly * ca;

            let px = cx + (rx * final_scale) as i32;
            let py = cy + (ry * final_scale) as i32;

            if px < 0 || px >= width {
                continue;
            }
            if py < 0 || py >= height {
                continue;
            }

            let out_idx = (py * width + px) as usize;

            if fade >= 0.98 {
                *buffer.add(out_idx) = color;
            } else {
                let bg = *buffer.add(out_idx);
                let a = (fade * 255.0) as u32;
                let inv = 255 - a;

                let r = (((color >> 16) & 0xFF) * a + ((bg >> 16) & 0xFF) * inv) >> 8;
                let g = (((color >> 8) & 0xFF) * a + ((bg >> 8) & 0xFF) * inv) >> 8;
                let b = ((color & 0xFF) * a + (bg & 0xFF) * inv) >> 8;

                *buffer.add(out_idx) = 0xFF000000 | (r << 16) | (g << 8) | b;
            }
        }
    }
}
