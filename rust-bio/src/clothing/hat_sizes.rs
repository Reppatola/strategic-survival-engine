// ============================================================
// ГОЛОВНЫЕ УБОРЫ
// Размер = обхват головы в см.
// ============================================================

pub struct HatSize {
    pub size: u32,          // 54..65
    pub circumference: f32, // обхват
    pub width: f32,         // ширина (между ушами)
    pub depth: f32,         // глубина (лоб → затылок)
}

pub const HAT_SIZES: &[HatSize] = &[
    HatSize {
        size: 54,
        circumference: 54.0,
        width: 15.5,
        depth: 18.9,
    },
    HatSize {
        size: 55,
        circumference: 55.0,
        width: 15.8,
        depth: 19.3,
    },
    HatSize {
        size: 56,
        circumference: 56.0,
        width: 16.1,
        depth: 19.6,
    },
    HatSize {
        size: 57,
        circumference: 57.0,
        width: 16.3,
        depth: 20.0,
    },
    HatSize {
        size: 58,
        circumference: 58.0,
        width: 16.6,
        depth: 20.3,
    },
    HatSize {
        size: 59,
        circumference: 59.0,
        width: 16.9,
        depth: 20.7,
    },
    HatSize {
        size: 60,
        circumference: 60.0,
        width: 17.2,
        depth: 21.0,
    },
    HatSize {
        size: 61,
        circumference: 61.0,
        width: 17.5,
        depth: 21.4,
    },
    HatSize {
        size: 62,
        circumference: 62.0,
        width: 17.8,
        depth: 21.7,
    },
    HatSize {
        size: 63,
        circumference: 63.0,
        width: 18.1,
        depth: 22.1,
    },
    HatSize {
        size: 64,
        circumference: 64.0,
        width: 18.4,
        depth: 22.4,
    },
    HatSize {
        size: 65,
        circumference: 65.0,
        width: 18.7,
        depth: 22.8,
    },
];

// Найти размер по обхвату
pub fn find_hat_size(size: u32) -> Option<&'static HatSize> {
    HAT_SIZES.iter().find(|h| h.size == size)
}
