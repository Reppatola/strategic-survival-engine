use crate::parts::*;
use crate::slice::*;

// ------------------------------------------------------------
// Проверка: точка внутри среза
// ------------------------------------------------------------
fn point_in_slice(x: f32, y: f32, s: &HSlice) -> bool {
    let dx = x - s.off_x;
    let dy = y - s.off_y;
    let rx = s.width * 0.5;
    let ry = s.depth * 0.5;
    if rx < 0.1 || ry < 0.1 {
        return false;
    }
    (dx * dx) / (rx * rx) + (dy * dy) / (ry * ry) <= 1.0
}

// ------------------------------------------------------------
// Найти верхний Z в локальной точке (lx, ly).
// part_out — ID части тела.
// ------------------------------------------------------------
pub fn highest_z_local(lx: f32, ly: f32, part_out: &mut u8) -> f32 {
    let mut best_z: f32 = -1.0;
    let mut best_part: i32 = -1;

    macro_rules! check_part {
        ($slices:expr, $id:expr, $xoff:expr) => {
            for s in $slices {
                if point_in_slice(lx - $xoff, ly, s) {
                    if s.z > best_z {
                        best_z = s.z;
                        best_part = $id;
                    }
                }
            }
        };
    }

    check_part!(head::H_SLICES, PART_HEAD as i32, head::ATTACH_X);
    check_part!(
        torso_upper::H_SLICES,
        PART_TORSO_UP as i32,
        torso_upper::ATTACH_X
    );
    check_part!(
        torso_lower::H_SLICES,
        PART_TORSO_LOW as i32,
        torso_lower::ATTACH_X
    );
    check_part!(arm_left::H_SLICES, PART_ARM_LEFT as i32, arm_left::ATTACH_X);
    check_part!(
        arm_right::H_SLICES,
        PART_ARM_RIGHT as i32,
        arm_right::ATTACH_X
    );
    check_part!(leg_left::H_SLICES, PART_LEG_LEFT as i32, leg_left::ATTACH_X);
    check_part!(
        leg_right::H_SLICES,
        PART_LEG_RIGHT as i32,
        leg_right::ATTACH_X
    );
    check_part!(
        foot_left::H_SLICES,
        PART_FOOT_LEFT as i32,
        foot_left::ATTACH_X
    );
    check_part!(
        foot_right::H_SLICES,
        PART_FOOT_RIGHT as i32,
        foot_right::ATTACH_X
    );

    *part_out = if best_part < 0 { 255 } else { best_part as u8 };
    best_z
}
