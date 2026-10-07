use crate::slice::*;

// ============================================================
// ЛЯМКИ РЮКЗАКА — проходят НАД плечом (z = 146..147)
// Торс заканчивается на z=145. Лямки идут выше — перекрывают.
// ============================================================

pub const ATTACH_X_L: f32 = -11.0;
pub const ATTACH_X_R: f32 = 11.0;

pub const H_SLICES_L: &[HSlice] = &[
    // от рюкзака вверх (спина)
    HSlice {
        z: 132.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -17.0,
    },
    HSlice {
        z: 136.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -14.5,
    },
    HSlice {
        z: 140.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -11.0,
    },
    HSlice {
        z: 143.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -6.5,
    },
    HSlice {
        z: 145.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -2.0,
    },
    // НАД плечом — выше торса
    HSlice {
        z: 146.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 147.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 147.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 4.5,
    },
    // спуск на грудь
    HSlice {
        z: 145.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 7.5,
    },
    HSlice {
        z: 142.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 9.0,
    },
    HSlice {
        z: 137.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 10.0,
    },
    HSlice {
        z: 131.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 10.0,
    },
    HSlice {
        z: 125.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 9.5,
    },
];

pub const H_SLICES_R: &[HSlice] = &[
    HSlice {
        z: 132.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -17.0,
    },
    HSlice {
        z: 136.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -14.5,
    },
    HSlice {
        z: 140.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -11.0,
    },
    HSlice {
        z: 143.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -6.5,
    },
    HSlice {
        z: 145.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: -2.0,
    },
    HSlice {
        z: 146.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 147.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 147.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 4.5,
    },
    HSlice {
        z: 145.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 7.5,
    },
    HSlice {
        z: 142.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 9.0,
    },
    HSlice {
        z: 137.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 10.0,
    },
    HSlice {
        z: 131.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 10.0,
    },
    HSlice {
        z: 125.0,
        width: 8.0,
        depth: 4.0,
        off_x: 0.0,
        off_y: 9.5,
    },
];
