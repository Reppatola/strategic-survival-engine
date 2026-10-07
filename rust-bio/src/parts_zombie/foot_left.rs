use crate::slice::*;

pub const ATTACH_X: f32 = -7.0;

pub const H_SLICES: &[HSlice] = &[
    HSlice {
        z: 6.0,
        width: 8.0,
        depth: 20.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 4.0,
        width: 8.0,
        depth: 20.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 2.0,
        width: 7.5,
        depth: 19.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 0.0,
        width: 7.0,
        depth: 18.0,
        off_x: 0.0,
        off_y: 2.0,
    },
];
