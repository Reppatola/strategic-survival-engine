// ============================================================
// БРЮКИ МУЖСКИЕ
// Полуобхваты = половина измерения. Умножаем на 2 для полного.
// ============================================================

pub struct PantsSize {
    pub size: u32,         // 50..68
    pub waist_half: f32,   // полуобхват талии
    pub hips_half: f32,    // полуобхват бёдер
    pub length_side: f32,  // длина по боковому шву
    pub length_inner: f32, // длина внутренняя
    pub thigh_half: f32,   // полуобхват одного бедра
}

pub const PANTS_SIZES: &[PantsSize] = &[
    PantsSize {
        size: 50,
        waist_half: 48.0,
        hips_half: 56.0,
        length_side: 98.0,
        length_inner: 68.0,
        thigh_half: 34.0,
    },
    PantsSize {
        size: 52,
        waist_half: 50.0,
        hips_half: 58.0,
        length_side: 98.0,
        length_inner: 68.0,
        thigh_half: 35.0,
    },
    PantsSize {
        size: 54,
        waist_half: 52.0,
        hips_half: 60.0,
        length_side: 98.0,
        length_inner: 68.0,
        thigh_half: 36.0,
    },
    PantsSize {
        size: 56,
        waist_half: 54.0,
        hips_half: 62.0,
        length_side: 98.0,
        length_inner: 68.0,
        thigh_half: 37.0,
    },
    PantsSize {
        size: 58,
        waist_half: 56.0,
        hips_half: 65.0,
        length_side: 98.0,
        length_inner: 68.0,
        thigh_half: 38.0,
    },
    PantsSize {
        size: 60,
        waist_half: 58.0,
        hips_half: 67.0,
        length_side: 98.0,
        length_inner: 68.0,
        thigh_half: 39.0,
    },
    PantsSize {
        size: 62,
        waist_half: 60.0,
        hips_half: 69.0,
        length_side: 98.0,
        length_inner: 68.0,
        thigh_half: 40.0,
    },
    PantsSize {
        size: 64,
        waist_half: 62.0,
        hips_half: 71.0,
        length_side: 98.0,
        length_inner: 68.0,
        thigh_half: 41.0,
    },
];

pub fn find_pants_size(size: u32) -> Option<&'static PantsSize> {
    PANTS_SIZES.iter().find(|p| p.size == size)
}
