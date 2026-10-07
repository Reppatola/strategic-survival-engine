use crate::slice::*;

pub const ATTACH_X: f32 = 0.0;
pub const ATTACH_Z: f32 = 145.0;

// ============================================================
// ЛИЦО — тонкая полоска ВНУТРИ границ головы
// Голова спереди заканчивается на y ≈ +7. Лицо — на y = +4..+5.5.
// ============================================================
pub const H_SLICES: &[HSlice] = &[
    HSlice {
        z: 174.0,
        width: 4.0,
        depth: 3.0,
        off_x: 0.0,
        off_y: 3.0,
    },
    HSlice {
        z: 172.0,
        width: 6.0,
        depth: 3.0,
        off_x: 0.0,
        off_y: 4.0,
    },
    HSlice {
        z: 170.0,
        width: 7.0,
        depth: 3.0,
        off_x: 0.0,
        off_y: 4.5,
    },
    HSlice {
        z: 168.0,
        width: 7.5,
        depth: 3.0,
        off_x: 0.0,
        off_y: 5.0,
    },
    HSlice {
        z: 165.0,
        width: 8.0,
        depth: 3.0,
        off_x: 0.0,
        off_y: 5.0,
    },
    HSlice {
        z: 162.0,
        width: 8.0,
        depth: 3.0,
        off_x: 0.0,
        off_y: 5.0,
    },
    HSlice {
        z: 158.0,
        width: 7.5,
        depth: 3.0,
        off_x: 0.0,
        off_y: 5.0,
    },
    HSlice {
        z: 154.0,
        width: 6.0,
        depth: 3.0,
        off_x: 0.0,
        off_y: 4.5,
    },
    HSlice {
        z: 150.0,
        width: 4.0,
        depth: 3.0,
        off_x: 0.0,
        off_y: 4.0,
    },
];
