// ============================================================
// ТОЛСТОВКИ МУЖСКИЕ
// ============================================================

pub struct HoodieSize {
    pub size: u32,          // 38..62
    pub body_height: f32,   // рост
    pub chest_width: f32,   // ширина изделия
    pub body_length: f32,   // длина от плеча
    pub sleeve_length: f32, // рукав от плеча
}

pub const HOODIE_SIZES: &[HoodieSize] = &[
    HoodieSize {
        size: 38,
        body_height: 158.0,
        chest_width: 47.0,
        body_length: 62.0,
        sleeve_length: 61.0,
    },
    HoodieSize {
        size: 40,
        body_height: 164.0,
        chest_width: 48.0,
        body_length: 63.0,
        sleeve_length: 64.0,
    },
    HoodieSize {
        size: 42,
        body_height: 170.0,
        chest_width: 50.0,
        body_length: 64.0,
        sleeve_length: 65.0,
    },
    HoodieSize {
        size: 44,
        body_height: 176.0,
        chest_width: 52.0,
        body_length: 66.0,
        sleeve_length: 66.0,
    },
    HoodieSize {
        size: 46,
        body_height: 176.0,
        chest_width: 54.0,
        body_length: 67.0,
        sleeve_length: 69.0,
    },
    HoodieSize {
        size: 48,
        body_height: 176.0,
        chest_width: 56.0,
        body_length: 67.0,
        sleeve_length: 70.0,
    },
    HoodieSize {
        size: 50,
        body_height: 176.0,
        chest_width: 58.0,
        body_length: 68.0,
        sleeve_length: 70.0,
    },
    HoodieSize {
        size: 52,
        body_height: 176.0,
        chest_width: 60.0,
        body_length: 68.0,
        sleeve_length: 70.0,
    },
    HoodieSize {
        size: 54,
        body_height: 176.0,
        chest_width: 62.0,
        body_length: 68.0,
        sleeve_length: 70.0,
    },
    HoodieSize {
        size: 56,
        body_height: 176.0,
        chest_width: 64.0,
        body_length: 68.0,
        sleeve_length: 70.0,
    },
    HoodieSize {
        size: 58,
        body_height: 176.0,
        chest_width: 66.0,
        body_length: 68.0,
        sleeve_length: 71.0,
    },
    HoodieSize {
        size: 60,
        body_height: 176.0,
        chest_width: 68.0,
        body_length: 69.0,
        sleeve_length: 71.0,
    },
    HoodieSize {
        size: 62,
        body_height: 176.0,
        chest_width: 71.0,
        body_length: 70.0,
        sleeve_length: 72.0,
    },
];

pub fn find_hoodie_size(size: u32) -> Option<&'static HoodieSize> {
    HOODIE_SIZES.iter().find(|h| h.size == size)
}
