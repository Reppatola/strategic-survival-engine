use crate::slice::*;

pub const ATTACH_X: f32 = 0.0;
pub const ATTACH_Z: f32 = 100.0;

// ============================================================
// РЮКЗАК — поднят на 10 см (z +10)
// Диапазон: 76 .. 138 (был 66 .. 128)
// ============================================================
pub const H_SLICES: &[HSlice] = &[
    HSlice {
        z: 76.0,
        width: 22.0,
        depth: 14.0,
        off_x: 0.0,
        off_y: -12.0,
    },
    HSlice {
        z: 82.0,
        width: 28.0,
        depth: 16.0,
        off_x: 0.0,
        off_y: -14.0,
    },
    HSlice {
        z: 88.0,
        width: 32.0,
        depth: 18.0,
        off_x: 0.0,
        off_y: -16.0,
    },
    HSlice {
        z: 96.0,
        width: 34.0,
        depth: 19.0,
        off_x: 0.0,
        off_y: -17.0,
    },
    HSlice {
        z: 104.0,
        width: 36.0,
        depth: 20.0,
        off_x: 0.0,
        off_y: -18.0,
    },
    HSlice {
        z: 112.0,
        width: 36.0,
        depth: 20.0,
        off_x: 0.0,
        off_y: -18.0,
    },
    HSlice {
        z: 120.0,
        width: 36.0,
        depth: 20.0,
        off_x: 0.0,
        off_y: -18.0,
    },
    HSlice {
        z: 128.0,
        width: 36.0,
        depth: 20.0,
        off_x: 0.0,
        off_y: -18.0,
    },
    HSlice {
        z: 134.0,
        width: 34.0,
        depth: 18.0,
        off_x: 0.0,
        off_y: -17.0,
    },
    HSlice {
        z: 138.0,
        width: 30.0,
        depth: 16.0,
        off_x: 0.0,
        off_y: -16.0,
    },
];
