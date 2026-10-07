use crate::slice::*;
use crate::volume::highest_z_local;

fn color_for_part(part: u8, z: f32) -> u32 {
    let base: u32 = match part {
        PART_HEAD => 0xFF4A3520,      // волосы (светлее, видно на фоне)
        PART_TORSO_UP => 0xFF2E3D5E,  // тёмно-синяя толстовка
        PART_TORSO_LOW => 0xFF283044, // тёмный низ
        PART_ARM_LEFT => 0xFF2E3D5E,  // тот же рукав
        PART_ARM_RIGHT => 0xFF2E3D5E,
        PART_LEG_LEFT => 0xFF1E2436, // тёмные штаны
        PART_LEG_RIGHT => 0xFF1E2436,
        PART_FOOT_LEFT => 0xFF141414, // тёмная обувь
        PART_FOOT_RIGHT => 0xFF141414,
        PART_CAP => 0xFF5A8AB8,      // голубая бейсболка (светлая!)
        PART_BACKPACK => 0xFF4A5A3A, // олива (тёмно-зелёный)
        PART_STRAP_L => 0xFF2A1F18,  // тёмно-коричневые лямки
        PART_STRAP_R => 0xFF2A1F18,
        PART_FACE => 0xFFDCB48C, // кожа
        PART_EAR_L => 0xFFDCB48C,
        PART_EAR_R => 0xFFDCB48C,
        PART_NOSE => 0xFFDCB48C,
        _ => return 0,
    };

    let br = 0.7 + (z / 175.0) * 0.3;
    let r = (((base >> 16) & 0xFF) as f32 * br) as u32;
    let g = (((base >> 8) & 0xFF) as f32 * br) as u32;
    let b = ((base & 0xFF) as f32 * br) as u32;

    let r = r.min(255);
    let g = g.min(255);
    let b = b.min(255);

    0xFF000000 | (r << 16) | (g << 8) | b
}

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
    // --- Амплитуды из таблицы анимации ---
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
