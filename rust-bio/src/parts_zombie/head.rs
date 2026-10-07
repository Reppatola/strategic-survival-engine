use crate::slice::*;

pub const ATTACH_X: f32 = 0.0;

// Голова зомби: меньше, наклонена вперёд (off_y = +2)
pub const H_SLICES: &[HSlice] = &[
    HSlice {
        z: 175.0,
        width: 6.0,
        depth: 8.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 172.0,
        width: 9.0,
        depth: 11.0,
        off_x: 0.0,
        off_y: 1.0,
    },
    HSlice {
        z: 168.0,
        width: 11.0,
        depth: 13.5,
        off_x: 0.0,
        off_y: 1.5,
    },
    HSlice {
        z: 165.0,
        width: 12.0,
        depth: 14.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 160.0,
        width: 12.0,
        depth: 14.0,
        off_x: 0.0,
        off_y: 2.0,
    },
    HSlice {
        z: 156.0,
        width: 11.5,
        depth: 13.5,
        off_x: 0.0,
        off_y: 1.5,
    },
    HSlice {
        z: 152.0,
        width: 11.0,
        depth: 12.5,
        off_x: 0.0,
        off_y: 1.0,
    },
    HSlice {
        z: 148.0,
        width: 12.0,
        depth: 12.0,
        off_x: 0.0,
        off_y: 0.5,
    },
    HSlice {
        z: 146.0,
        width: 13.0,
        depth: 12.0,
        off_x: 0.0,
        off_y: 0.0,
    },
];
