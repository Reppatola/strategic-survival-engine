// ============================================================
// ОБУВЬ (EU)
// ============================================================

pub struct ShoeSize {
    pub size: u32,        // 38..46
    pub foot_length: f32, // длина стопы
    pub foot_width: f32,  // ширина
    pub foot_height: f32, // высота
}

pub const SHOE_SIZES: &[ShoeSize] = &[
    ShoeSize {
        size: 38,
        foot_length: 24.5,
        foot_width: 9.5,
        foot_height: 5.5,
    },
    ShoeSize {
        size: 39,
        foot_length: 25.0,
        foot_width: 9.7,
        foot_height: 5.6,
    },
    ShoeSize {
        size: 40,
        foot_length: 25.5,
        foot_width: 9.8,
        foot_height: 5.8,
    },
    ShoeSize {
        size: 41,
        foot_length: 26.0,
        foot_width: 10.0,
        foot_height: 6.0,
    },
    ShoeSize {
        size: 42,
        foot_length: 26.5,
        foot_width: 10.1,
        foot_height: 6.1,
    },
    ShoeSize {
        size: 43,
        foot_length: 27.0,
        foot_width: 10.3,
        foot_height: 6.2,
    },
    ShoeSize {
        size: 44,
        foot_length: 27.5,
        foot_width: 10.5,
        foot_height: 6.4,
    },
    ShoeSize {
        size: 45,
        foot_length: 28.0,
        foot_width: 10.7,
        foot_height: 6.5,
    },
    ShoeSize {
        size: 46,
        foot_length: 28.5,
        foot_width: 10.9,
        foot_height: 6.7,
    },
];

pub fn find_shoe_size(size: u32) -> Option<&'static ShoeSize> {
    SHOE_SIZES.iter().find(|s| s.size == size)
}
