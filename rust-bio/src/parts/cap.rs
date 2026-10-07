use crate::slice::*;

pub const ATTACH_X: f32 = 0.0;
pub const ATTACH_Z: f32 = 175.0; // крепится к макушке

// Бейсболка сверху:
//   - купол: овал 18 × 20 см на z = 175..182
//   - козырёк: выступает вперёд от y = +5 до +14 см
pub const H_SLICES: &[HSlice] = &[
    // купол (высшая точка)
    HSlice {
        z: 182.0,
        width: 10.0,
        depth: 11.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 180.0,
        width: 14.0,
        depth: 15.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 178.0,
        width: 17.0,
        depth: 18.5,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 176.0,
        width: 18.5,
        depth: 20.0,
        off_x: 0.0,
        off_y: 0.0,
    },
    HSlice {
        z: 175.0,
        width: 18.0,
        depth: 19.5,
        off_x: 0.0,
        off_y: 0.0,
    },
    // козырёк — выступает вперёд (z = 174..176, y = +8..+14)
    // представим как отдельный срез со смещением вперёд
    HSlice {
        z: 175.0,
        width: 14.0,
        depth: 6.0,
        off_x: 0.0,
        off_y: 10.0,
    },
    HSlice {
        z: 174.5,
        width: 13.5,
        depth: 6.0,
        off_x: 0.0,
        off_y: 10.5,
    },
    HSlice {
        z: 174.0,
        width: 13.0,
        depth: 6.0,
        off_x: 0.0,
        off_y: 11.0,
    },
];
