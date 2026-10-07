use crate::parts;
use crate::parts_zombie;
use crate::slice::*;

// ============================================================
// Проверка: точка внутри среза
// ============================================================
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

// ============================================================
// ВЕРХНИЙ Z ДЛЯ ГЕРОЯ
// ============================================================
pub fn highest_z_local(lx: f32, ly: f32, part_out: &mut u8, swing: &Swing) -> f32 {
    let mut best_z: f32 = -1.0;
    let mut best_part: i32 = -1;

    // ---- Статика ----
    macro_rules! check_rigid {
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

    // ---- Конечности (качаются) ----
    macro_rules! check_swing {
        ($slices:expr, $id:expr, $xoff:expr, $sw:expr, $pivot_z:expr) => {
            for s in $slices {
                let yoff = $sw * ($pivot_z - s.z);
                if point_in_slice(lx - $xoff, ly - yoff, s) {
                    if s.z > best_z {
                        best_z = s.z;
                        best_part = $id;
                    }
                }
            }
        };
    }

    // ---- Статика: голова, торс ----
    check_rigid!(
        parts::head::H_SLICES,
        PART_HEAD as i32,
        parts::head::ATTACH_X
    );
    check_rigid!(
        parts::torso_upper::H_SLICES,
        PART_TORSO_UP as i32,
        parts::torso_upper::ATTACH_X
    );
    check_rigid!(
        parts::torso_lower::H_SLICES,
        PART_TORSO_LOW as i32,
        parts::torso_lower::ATTACH_X
    );
    check_rigid!(
        parts::backpack::H_SLICES,
        PART_BACKPACK as i32,
        parts::backpack::ATTACH_X
    );

    // ---- Руки ----
    check_swing!(
        parts::arm_left::H_SLICES,
        PART_ARM_LEFT as i32,
        parts::arm_left::ATTACH_X,
        swing.arm_left,
        143.0
    );
    check_swing!(
        parts::arm_right::H_SLICES,
        PART_ARM_RIGHT as i32,
        parts::arm_right::ATTACH_X,
        swing.arm_right,
        143.0
    );

    // ---- Ноги ----
    check_swing!(
        parts::leg_left::H_SLICES,
        PART_LEG_LEFT as i32,
        parts::leg_left::ATTACH_X,
        swing.leg_left,
        84.0
    );
    check_swing!(
        parts::leg_right::H_SLICES,
        PART_LEG_RIGHT as i32,
        parts::leg_right::ATTACH_X,
        swing.leg_right,
        84.0
    );

    // ---- Стопы ----
    let foot_left_off = swing.leg_left * 78.0;
    let foot_right_off = swing.leg_right * 78.0;

    for s in parts::foot_left::H_SLICES {
        if point_in_slice(lx - parts::foot_left::ATTACH_X, ly - foot_left_off, s) {
            if s.z > best_z {
                best_z = s.z;
                best_part = PART_FOOT_LEFT as i32;
            }
        }
    }
    for s in parts::foot_right::H_SLICES {
        if point_in_slice(lx - parts::foot_right::ATTACH_X, ly - foot_right_off, s) {
            if s.z > best_z {
                best_z = s.z;
                best_part = PART_FOOT_RIGHT as i32;
            }
        }
    }

    // ---- Перекрытия: face, ears, nose ----
    macro_rules! check_head_over {
        ($slices:expr, $id:expr, $xoff:expr) => {
            for s in $slices {
                if point_in_slice(lx - $xoff, ly, s) {
                    if s.z >= best_z {
                        best_z = s.z;
                        best_part = $id;
                    }
                }
            }
        };
    }

    check_head_over!(
        parts::head_face::H_SLICES,
        PART_FACE as i32,
        parts::head_face::ATTACH_X
    );
    check_head_over!(
        parts::head_ears::H_SLICES_L,
        PART_EAR_L as i32,
        parts::head_ears::ATTACH_X_L
    );
    check_head_over!(
        parts::head_ears::H_SLICES_R,
        PART_EAR_R as i32,
        parts::head_ears::ATTACH_X_R
    );
    check_head_over!(
        parts::head_nose::H_SLICES,
        PART_NOSE as i32,
        parts::head_nose::ATTACH_X
    );

    // ---- Лямки (поверх всего) ----
    macro_rules! check_over {
        ($slices:expr, $id:expr, $xoff:expr) => {
            for s in $slices {
                if point_in_slice(lx - $xoff, ly, s) {
                    if s.z >= best_z {
                        best_z = s.z;
                        best_part = $id;
                    }
                }
            }
        };
    }

    check_over!(
        parts::straps::H_SLICES_L,
        PART_STRAP_L as i32,
        parts::straps::ATTACH_X_L
    );
    check_over!(
        parts::straps::H_SLICES_R,
        PART_STRAP_R as i32,
        parts::straps::ATTACH_X_R
    );

    *part_out = if best_part < 0 { 255 } else { best_part as u8 };
    best_z
}

// ============================================================
// ВЕРХНИЙ Z ДЛЯ ЗОМБИ
// ============================================================
pub fn highest_z_zombie(lx: f32, ly: f32, part_out: &mut u8, swing: &Swing) -> f32 {
    let mut best_z: f32 = -1.0;
    let mut best_part: i32 = -1;

    macro_rules! check_rigid {
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

    macro_rules! check_swing {
        ($slices:expr, $id:expr, $xoff:expr, $sw:expr, $pivot_z:expr) => {
            for s in $slices {
                let yoff = $sw * ($pivot_z - s.z);
                if point_in_slice(lx - $xoff, ly - yoff, s) {
                    if s.z > best_z {
                        best_z = s.z;
                        best_part = $id;
                    }
                }
            }
        };
    }

    // ---- Статика ----
    check_rigid!(
        parts_zombie::head::H_SLICES,
        ZPART_HEAD as i32,
        parts_zombie::head::ATTACH_X
    );
    check_rigid!(
        parts_zombie::torso_upper::H_SLICES,
        ZPART_TORSO_UP as i32,
        parts_zombie::torso_upper::ATTACH_X
    );
    check_rigid!(
        parts_zombie::torso_lower::H_SLICES,
        ZPART_TORSO_LOW as i32,
        parts_zombie::torso_lower::ATTACH_X
    );

    // ---- Руки ----
    check_swing!(
        parts_zombie::arm_left::H_SLICES,
        ZPART_ARM_LEFT as i32,
        parts_zombie::arm_left::ATTACH_X,
        swing.arm_left,
        143.0
    );
    check_swing!(
        parts_zombie::arm_right::H_SLICES,
        ZPART_ARM_RIGHT as i32,
        parts_zombie::arm_right::ATTACH_X,
        swing.arm_right,
        143.0
    );

    // ---- Ноги ----
    check_swing!(
        parts_zombie::leg_left::H_SLICES,
        ZPART_LEG_LEFT as i32,
        parts_zombie::leg_left::ATTACH_X,
        swing.leg_left,
        84.0
    );
    check_swing!(
        parts_zombie::leg_right::H_SLICES,
        ZPART_LEG_RIGHT as i32,
        parts_zombie::leg_right::ATTACH_X,
        swing.leg_right,
        84.0
    );

    // ---- Стопы ----
    let foot_left_off = swing.leg_left * 78.0;
    let foot_right_off = swing.leg_right * 78.0;

    for s in parts_zombie::foot_left::H_SLICES {
        if point_in_slice(
            lx - parts_zombie::foot_left::ATTACH_X,
            ly - foot_left_off,
            s,
        ) {
            if s.z > best_z {
                best_z = s.z;
                best_part = ZPART_FOOT_LEFT as i32;
            }
        }
    }
    for s in parts_zombie::foot_right::H_SLICES {
        if point_in_slice(
            lx - parts_zombie::foot_right::ATTACH_X,
            ly - foot_right_off,
            s,
        ) {
            if s.z > best_z {
                best_z = s.z;
                best_part = ZPART_FOOT_RIGHT as i32;
            }
        }
    }

    *part_out = if best_part < 0 { 255 } else { best_part as u8 };
    best_z
}
