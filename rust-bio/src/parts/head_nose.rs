use crate::slice::*;

pub const ATTACH_X: f32 = 0.0;
pub const ATTACH_Z: f32 = 162.0;

// ============================================================
// НОС — маленький выступ чуть впереди лица
// Лицо на y ≈ +5. Нос на y ≈ +6..+7. Внутри головы или на грани.
// ============================================================
pub const H_SLICES: &[HSlice] = &[
    HSlice {
        z: 166.0,
        width: 2.5,
        depth: 2.0,
        off_x: 0.0,
        off_y: 5.5,
    },
    HSlice {
        z: 164.0,
        width: 3.0,
        depth: 2.5,
        off_x: 0.0,
        off_y: 6.0,
    },
    HSlice {
        z: 162.0,
        width: 3.5,
        depth: 3.0,
        off_x: 0.0,
        off_y: 6.5,
    },
    HSlice {
        z: 160.0,
        width: 3.0,
        depth: 2.5,
        off_x: 0.0,
        off_y: 6.0,
    },
    HSlice {
        z: 158.0,
        width: 2.0,
        depth: 2.0,
        off_x: 0.0,
        off_y: 5.5,
    },
];
