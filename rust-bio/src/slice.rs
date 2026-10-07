// ============================================================
// СРЕЗЫ ТЕЛА
// ============================================================

#[derive(Clone, Copy)]
pub struct HSlice {
    pub z: f32,
    pub width: f32,
    pub depth: f32,
    pub off_x: f32,
    pub off_y: f32,
}

#[derive(Clone, Copy)]
pub struct VSlice {
    pub x: f32,
    pub height: f32,
    pub depth: f32,
    pub off_z: f32,
    pub off_y: f32,
}

// ============================================================
// ID частей тела
// ============================================================
pub const PART_HEAD: u8 = 0;
pub const PART_TORSO_UP: u8 = 1;
pub const PART_TORSO_LOW: u8 = 2;
pub const PART_ARM_LEFT: u8 = 3;
pub const PART_ARM_RIGHT: u8 = 4;
pub const PART_LEG_LEFT: u8 = 5;
pub const PART_LEG_RIGHT: u8 = 6;
pub const PART_FOOT_LEFT: u8 = 7;
pub const PART_FOOT_RIGHT: u8 = 8;

// ============================================================
// Часть тела
// ============================================================
pub struct Part {
    pub id: u8,
    pub attach_x: f32,
    pub slices: &'static [HSlice],
}
