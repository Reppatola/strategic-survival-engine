use crate::slice::*;

pub const ATTACH_X_L: f32 = -7.5;
pub const ATTACH_X_R: f32 = 7.5;
pub const ATTACH_Z: f32 = 160.0;

// ============================================================
// УШИ — маленькие выступы по бокам головы
// Сверху видны как два маленьких «пятнышка» слева и справа.
// ============================================================
pub const H_SLICES_L: &[HSlice] = &[
    HSlice {
        z: 163.0,
        width: 3.0,
        depth: 3.5,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 161.0,
        width: 3.5,
        depth: 4.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 159.0,
        width: 3.5,
        depth: 4.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 157.0,
        width: 3.0,
        depth: 3.5,
        off_x: 0.0,
        off_y: 0.0,
    },
];

pub const H_SLICES_R: &[HSlice] = &[
    HSlice {
        z: 163.0,
        width: 3.0,
        depth: 3.5,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 161.0,
        width: 3.5,
        depth: 4.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 159.0,
        width: 3.5,
        depth: 4.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 157.0,
        width: 3.0,
        depth: 3.5,
        off_x: 0.0,
        off_y: 0.0,
    },
];
