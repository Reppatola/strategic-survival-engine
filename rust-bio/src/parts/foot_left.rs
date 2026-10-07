use crate::slice::*;

pub const ATTACH_X: f32 = -8.5;

pub const H_SLICES: &[HSlice] = &[
    HSlice {
        z: 6.0,
        width: 9.0,
        depth: 22.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 4.0,
        width: 9.0,
        depth: 22.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 2.0,
        width: 8.5,
        depth: 21.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 0.0,
        width: 8.0,
        depth: 20.0,
        off_x: 0.0,
        off_y: 2.0,
    },
];
