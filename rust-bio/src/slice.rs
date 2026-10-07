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
pub const PART_CAP: u8 = 9;
pub const PART_BACKPACK: u8 = 10;
pub const PART_STRAP_L: u8 = 11;
pub const PART_STRAP_R: u8 = 12;
pub const PART_FACE: u8 = 13;
pub const PART_EAR_L: u8 = 14;
pub const PART_EAR_R: u8 = 15;
pub const PART_NOSE: u8 = 16;

// ============================================================
// Часть тела
// ============================================================
pub struct Part {
    pub id: u8,
    pub attach_x: f32,
    pub slices: &'static [HSlice],
}

// ============================================================
// КАЧАНИЕ КОНЕЧНОСТЕЙ
// Значение — sin(угла). Безразмерное.
// Применяется ПРОПОРЦИОНАЛЬНО расстоянию от сустава.
// ============================================================
pub struct Swing {
    pub arm_left: f32,
    pub arm_right: f32,
    pub leg_left: f32,
    pub leg_right: f32,
}

// ============================================================
// ID ЧАСТЕЙ ЗОМБИ
// ============================================================
pub const ZPART_HEAD: u8 = 20;
pub const ZPART_TORSO_UP: u8 = 21;
pub const ZPART_TORSO_LOW: u8 = 22;
pub const ZPART_ARM_LEFT: u8 = 23;
pub const ZPART_ARM_RIGHT: u8 = 24;
pub const ZPART_LEG_LEFT: u8 = 25;
pub const ZPART_LEG_RIGHT: u8 = 26;
pub const ZPART_FOOT_LEFT: u8 = 27;
pub const ZPART_FOOT_RIGHT: u8 = 28;
