// ============================================================
// ТАБЛИЦА ШУМА
//
// Все значения в ДЕЦИБЕЛАХ (dB).
// Источник: реальные измерения акустики.
//
// Правила:
//   own    — шум исходит от игрока / NPC
//   world  — шум среды (не зависит от игрока)
//
// Диапазоны:
//   0 – 40    тихо         (никого не привлекает)
//   40 – 60   комфортно    (малый радиус)
//   60 – 80   громко       (средний радиус)
//   80 – 100  опасно       (большой радиус)
//   110+      экстрим      (орда)
// ============================================================

pub struct NoiseSource {
    pub name: &'static str,
    pub db: f32,           // уровень громкости
    pub min_db: f32,       // нижняя граница диапазона
    pub max_db: f32,       // верхняя граница диапазона
    pub is_own: bool,      // true = от игрока/NPC
    pub duration_sec: f32, // 0.0 = мгновенный, >0 = длится
}

// ============================================================
// ОСНОВНАЯ ТАБЛИЦА — 8 категорий по возрастанию
// ============================================================

pub const NOISE_TABLE: &[NoiseSource] = &[
    // ---- 0 – 40 dB: тихо ----
    NoiseSource {
        name: "threshold",
        db: 0.0,
        min_db: 0.0,
        max_db: 0.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "breath_quiet",
        db: 12.0,
        min_db: 10.0,
        max_db: 15.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "leaves",
        db: 12.5,
        min_db: 10.0,
        max_db: 15.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "clock",
        db: 25.0,
        min_db: 20.0,
        max_db: 30.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "whisper_1m",
        db: 25.0,
        min_db: 20.0,
        max_db: 30.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "library",
        db: 35.0,
        min_db: 30.0,
        max_db: 40.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "sneak_step",
        db: 32.0,
        min_db: 28.0,
        max_db: 36.0,
        is_own: true,
        duration_sec: 0.0,
    },
    // ---- 40 – 60 dB: комфортно ----
    NoiseSource {
        name: "quiet_talk",
        db: 42.5,
        min_db: 40.0,
        max_db: 45.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "fridge",
        db: 40.0,
        min_db: 38.0,
        max_db: 42.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "normal_talk",
        db: 52.5,
        min_db: 50.0,
        max_db: 55.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "razor",
        db: 55.0,
        min_db: 50.0,
        max_db: 60.0,
        is_own: true,
        duration_sec: 0.0,
    },
    // ---- 60 – 80 dB: громко ----
    NoiseSource {
        name: "walk_step",
        db: 62.5,
        min_db: 60.0,
        max_db: 65.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "busy_street",
        db: 62.5,
        min_db: 60.0,
        max_db: 65.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "washer",
        db: 57.5,
        min_db: 50.0,
        max_db: 65.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "vacuum",
        db: 72.5,
        min_db: 70.0,
        max_db: 75.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "run_step",
        db: 75.0,
        min_db: 72.0,
        max_db: 78.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "car_interior",
        db: 75.0,
        min_db: 70.0,
        max_db: 80.0,
        is_own: false,
        duration_sec: 0.0,
    },
    // ---- 80 – 100 dB: опасно ----
    NoiseSource {
        name: "washer_spin",
        db: 82.5,
        min_db: 80.0,
        max_db: 85.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "hair_dryer",
        db: 82.5,
        min_db: 80.0,
        max_db: 85.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "blender",
        db: 82.5,
        min_db: 80.0,
        max_db: 85.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "scream",
        db: 85.0,
        min_db: 80.0,
        max_db: 90.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "shout",
        db: 85.0,
        min_db: 80.0,
        max_db: 90.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "lawnmower",
        db: 90.0,
        min_db: 85.0,
        max_db: 95.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "drill",
        db: 90.0,
        min_db: 85.0,
        max_db: 95.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "subway",
        db: 95.0,
        min_db: 90.0,
        max_db: 100.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "headphones",
        db: 100.0,
        min_db: 95.0,
        max_db: 105.0,
        is_own: true,
        duration_sec: 0.0,
    },
    // ---- 110 – 160 dB: экстрим ----
    NoiseSource {
        name: "car_horn",
        db: 115.0,
        min_db: 110.0,
        max_db: 120.0,
        is_own: true,
        duration_sec: 0.5,
    },
    NoiseSource {
        name: "concert",
        db: 117.5,
        min_db: 115.0,
        max_db: 120.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "jackhammer",
        db: 120.0,
        min_db: 120.0,
        max_db: 120.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "siren",
        db: 120.0,
        min_db: 120.0,
        max_db: 120.0,
        is_own: true,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "pain_threshold",
        db: 140.0,
        min_db: 140.0,
        max_db: 140.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "jet_takeoff",
        db: 145.0,
        min_db: 140.0,
        max_db: 150.0,
        is_own: false,
        duration_sec: 0.0,
    },
    NoiseSource {
        name: "gunshot",
        db: 155.0,
        min_db: 150.0,
        max_db: 160.0,
        is_own: true,
        duration_sec: 0.0,
    },
];

// ============================================================
// Найти источник по имени
// ============================================================
pub fn find_noise(name: &str) -> Option<&'static NoiseSource> {
    NOISE_TABLE.iter().find(|n| n.name == name)
}

// ============================================================
// Категория по dB
// ============================================================
pub enum NoiseCategory {
    Quiet,     // 0–40
    Comfort,   // 40–60
    Loud,      // 60–80
    Dangerous, // 80–100
    Extreme,   // 110+
}

pub fn category_of(db: f32) -> NoiseCategory {
    match db {
        d if d < 40.0 => NoiseCategory::Quiet,
        d if d < 60.0 => NoiseCategory::Comfort,
        d if d < 80.0 => NoiseCategory::Loud,
        d if d < 100.0 => NoiseCategory::Dangerous,
        _ => NoiseCategory::Extreme,
    }
}
