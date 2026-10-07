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
// Верхний Z с учётом качания конечностей.
//
// Ключевое: смещение по Y зависит от Z.
//   offset(z) = swing * (pivot_z - z)
//
// Плечо (z = pivot) — не смещается.
// Кисть (z << pivot) — смещается максимально.
// ============================================================
pub fn highest_z_local(lx: f32, ly: f32, part_out: &mut u8, swing: &Swing) -> f32 {
    let mut best_z: f32 = -1.0;
    let mut best_part: i32 = -1;

    // --- Статика: голова, торс ---
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

    // --- Конечности: смещение пропорционально удалению от сустава ---
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

    // --- Статика ---
    check_rigid!(head::H_SLICES, PART_HEAD as i32, head::ATTACH_X);
    check_rigid!(
        torso_upper::H_SLICES,
        PART_TORSO_UP as i32,
        torso_upper::ATTACH_X
    );
    check_rigid!(
        torso_lower::H_SLICES,
        PART_TORSO_LOW as i32,
        torso_lower::ATTACH_X
    );
    //check_rigid!(cap::H_SLICES, PART_CAP as i32, cap::ATTACH_X);
    check_rigid!(backpack::H_SLICES, PART_BACKPACK as i32, backpack::ATTACH_X);
    check_rigid!(straps::H_SLICES_L, PART_STRAP_L as i32, straps::ATTACH_X_L);
    check_rigid!(straps::H_SLICES_R, PART_STRAP_R as i32, straps::ATTACH_X_R);

    // --- Руки: вращаются вокруг плеча (z = 143) ---
    check_swing!(
        arm_left::H_SLICES,
        PART_ARM_LEFT as i32,
        arm_left::ATTACH_X,
        swing.arm_left,
        143.0
    );
    check_swing!(
        arm_right::H_SLICES,
        PART_ARM_RIGHT as i32,
        arm_right::ATTACH_X,
        swing.arm_right,
        143.0
    );

    // --- Ноги: вращаются вокруг бедра (z = 84) ---
    check_swing!(
        leg_left::H_SLICES,
        PART_LEG_LEFT as i32,
        leg_left::ATTACH_X,
        swing.leg_left,
        84.0
    );
    check_swing!(
        leg_right::H_SLICES,
        PART_LEG_RIGHT as i32,
        leg_right::ATTACH_X,
        swing.leg_right,
        84.0
    );

    // --- Стопы: жёстко прикреплены к концу голени (z = 6) ---
    // Смещение стопы = смещение голени на её конце
    //   = swing_leg * (84 - 6) = swing_leg * 78
    let foot_left_off = swing.leg_left * 78.0;
    let foot_right_off = swing.leg_right * 78.0;

    for s in foot_left::H_SLICES {
        if point_in_slice(lx - foot_left::ATTACH_X, ly - foot_left_off, s) {
            if s.z > best_z {
                best_z = s.z;
                best_part = PART_FOOT_LEFT as i32;
            }
        }
    }
    for s in foot_right::H_SLICES {
        if point_in_slice(lx - foot_right::ATTACH_X, ly - foot_right_off, s) {
            if s.z > best_z {
                best_z = s.z;
                best_part = PART_FOOT_RIGHT as i32;
            }
        }
    }
    // --------------------------------------------------------
    // ЛЯМКИ — рисуются ПОСЛЕ всего. Перекрывают тело и рюкзак.
    // Условие >= для перекрытия при равных z.
    // --------------------------------------------------------
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
    // --------------------------------------------------------
    // ГОЛОВА: face, ears, nose — перекрывают волосы
    // --------------------------------------------------------
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

    check_head_over!(head_face::H_SLICES, PART_FACE as i32, head_face::ATTACH_X);
    check_head_over!(
        head_ears::H_SLICES_L,
        PART_EAR_L as i32,
        head_ears::ATTACH_X_L
    );
    check_head_over!(
        head_ears::H_SLICES_R,
        PART_EAR_R as i32,
        head_ears::ATTACH_X_R
    );
    check_head_over!(head_nose::H_SLICES, PART_NOSE as i32, head_nose::ATTACH_X);

    check_over!(straps::H_SLICES_L, PART_STRAP_L as i32, straps::ATTACH_X_L);
    check_over!(straps::H_SLICES_R, PART_STRAP_R as i32, straps::ATTACH_X_R);

    *part_out = if best_part < 0 { 255 } else { best_part as u8 };
    best_z
}
