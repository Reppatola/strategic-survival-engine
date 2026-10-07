use crate::slice::*;
use crate::volume::highest_z_local;

// ------------------------------------------------------------
// Цвет части (BGRA)
// ------------------------------------------------------------
fn color_for_part(part: u8, z: f32) -> u32 {
    let base: u32 = match part {
        PART_HEAD => 0xFF5A4128,
        PART_TORSO_UP => 0xFF5064A0,
        PART_TORSO_LOW => 0xFF3C4664,
        PART_ARM_LEFT => 0xFF5064A0,
        PART_ARM_RIGHT => 0xFF5064A0,
        PART_LEG_LEFT => 0xFF3C4664,
        PART_LEG_RIGHT => 0xFF3C4664,
        PART_FOOT_LEFT => 0xFF281E19,
        PART_FOOT_RIGHT => 0xFF281E19,
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

// ------------------------------------------------------------
// Рендер героя в буфер (BGRA)
// ------------------------------------------------------------
pub unsafe fn render_hero(
    buffer: *mut u32,
    width: i32,
    height: i32,
    cx: i32,
    cy: i32,
    facing: f32,
    scale: f32,
) {
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

            // Мировое → локальное (обратный поворот)
            let lx = wx * ca - wy * sa;
            let ly = wx * sa + wy * ca;

            let mut part: u8 = 255;
            let z = highest_z_local(lx, ly, &mut part);

            if z >= 0.0 && part < 9 {
                let idx = (py * width + px) as usize;
                *buffer.add(idx) = color_for_part(part, z);
            }
        }
    }
}
