use crate::slice::*;

pub const ATTACH_X: f32 = 0.0;

// Верх торса: узкий, сгорбленный (off_y = +3)
pub const H_SLICES: &[HSlice] = &[
    HSlice {
        z: 145.0,
        width: 10.0,
        depth: 8.0,
        off_x: 0.0,
        off_y: 3.0,
    },
    HSlice {
        z: 144.0,
        width: 16.0,
        depth: 10.0,
        off_x: 0.0,
        off_y: 3.0,
    },
    HSlice {
        z: 143.0,
        width: 26.0,
        depth: 14.0,
        off_x: 0.0,
        off_y: 2.5,
    },
    HSlice {
        z: 141.0,
        width: 30.0,
        depth: 16.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 138.0,
        width: 32.0,
        depth: 16.0,
        off_x: 0.0,
        off_y: 1.5,
    },
    HSlice {
        z: 134.0,
        width: 32.0,
        depth: 16.0,
        off_x: 0.0,
        off_y: 1.0,
    },
    HSlice {
        z: 130.0,
        width: 31.0,
        depth: 16.0,
        off_x: 0.0,
        off_y: 0.5,
    },
    HSlice {
        z: 125.0,
        width: 30.0,
        depth: 15.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 120.0,
        width: 26.0,
        depth: 14.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 117.0,
        width: 24.0,
        depth: 14.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 115.0,
        width: 22.0,
        depth: 13.0,
        off_x: 0.0,
        off_y: 0.0,
    },
];
