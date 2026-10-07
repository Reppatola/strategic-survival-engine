// ============================================================
// ФИЗИЧЕСКАЯ МОДЕЛЬ ШУМА ШАГА
//
//   L = 10 · log10( η · E / (P_0 · Δt) )
//
// где:
//   L   — уровень звука, дБ (на источнике)
//   η   — акустическая эффективность (поверхность × обувь)
//   E   — кинетическая энергия удара ноги, Дж
//   Δt  — время соударения, сек
//   P_0 — порог слышимости = 1e-12 Вт
//
// Итог: число → dB → радиус слышимости → реакция мира.
// ============================================================

pub const P_0: f32 = 1e-12;

// ------------------------------------------------------------
// ПОХОДКА — сколько энергии отдаёт каждый шаг
// ------------------------------------------------------------
pub struct GaitEnergy {
    pub pose: u32,
    pub energy_j: f32, // E, Дж
    pub dt: f32,       // Δt, сек
}

pub const GAIT_ENERGY: &[GaitEnergy] = &[
    GaitEnergy {
        pose: 0,
        energy_j: 0.00,
        dt: 0.000,
    }, // стоит
    GaitEnergy {
        pose: 1,
        energy_j: 0.50,
        dt: 0.020,
    }, // ходьба
    GaitEnergy {
        pose: 2,
        energy_j: 2.00,
        dt: 0.015,
    }, // бег
    GaitEnergy {
        pose: 3,
        energy_j: 0.10,
        dt: 0.100,
    }, // крастьба
];

// ------------------------------------------------------------
// ПОВЕРХНОСТЬ — акустическая эффективность η
// Жёсткая поверхность — громче, мягкая — тише
// ------------------------------------------------------------
pub struct Surface {
    pub name: &'static str,
    pub eta: f32,
}

pub const SURFACES: &[Surface] = &[
    Surface {
        name: "sand",
        eta: 3.0e-9,
    }, // самый тихий
    Surface {
        name: "grass",
        eta: 5.0e-9,
    },
    Surface {
        name: "dirt",
        eta: 2.0e-8,
    },
    Surface {
        name: "wood",
        eta: 3.0e-8,
    },
    Surface {
        name: "water",
        eta: 4.0e-8,
    },
    Surface {
        name: "concrete",
        eta: 1.0e-7,
    },
    Surface {
        name: "metal",
        eta: 2.0e-7,
    }, // самый громкий
];

// ------------------------------------------------------------
// ОБУВЬ — множитель к η поверхности
// Гасит или усиливает удар
// ------------------------------------------------------------
pub struct Footwear {
    pub name: &'static str,
    pub eta_mod: f32,
}

pub const FOOTWEAR: &[Footwear] = &[
    Footwear {
        name: "barefoot",
        eta_mod: 2.0,
    }, // босиком — громко
    Footwear {
        name: "socks",
        eta_mod: 1.2,
    },
    Footwear {
        name: "sneakers",
        eta_mod: 1.0,
    }, // эталон
    Footwear {
        name: "boots_soft",
        eta_mod: 0.7,
    },
    Footwear {
        name: "boots_rubber",
        eta_mod: 0.5,
    }, // тише всех
    Footwear {
        name: "heels",
        eta_mod: 3.0,
    }, // каблуки — очень громко
];

// ------------------------------------------------------------
// Поиск по таблицам
// ------------------------------------------------------------
pub fn find_gait(pose: u32) -> Option<&'static GaitEnergy> {
    GAIT_ENERGY.iter().find(|g| g.pose == pose)
}

pub fn find_surface(name: &str) -> Option<&'static Surface> {
    SURFACES.iter().find(|s| s.name == name)
}

pub fn find_footwear(name: &str) -> Option<&'static Footwear> {
    FOOTWEAR.iter().find(|f| f.name == name)
}

// ------------------------------------------------------------
// ГЛАВНАЯ ФУНКЦИЯ — расчёт dB шага
//
//   L = 10 · log10( η_surface × η_footwear × E / (P_0 × Δt) )
// ------------------------------------------------------------
pub fn compute_step_db(pose: u32, surface: &str, footwear: &str) -> f32 {
    let (Some(g), Some(s), Some(f)) = (
        find_gait(pose),
        find_surface(surface),
        find_footwear(footwear),
    ) else {
        return 0.0;
    };

    if g.energy_j <= 0.0 || g.dt <= 0.0 {
        return 0.0;
    }

    let eta_total = s.eta * f.eta_mod;
    let p_ac = eta_total * g.energy_j / g.dt;

    let db = 10.0 * (p_ac / P_0).log10();
    if db < 0.0 {
        0.0
    } else {
        db
    }
}

// ============================================================
// ЗАТУХАНИЕ ЗВУКА В ВОЗДУХЕ
//
//   L2 = L1 − 20·log10(R2 / R1)
//
// R1 = 1 м — исходное расстояние (замер у источника)
// R2 = R  — расстояние до слушателя, м
//
// Упрощённо: L2 = L1 − 20·log10(R)
// ============================================================

pub fn db_at_distance(l1_db: f32, r_meters: f32) -> f32 {
    if r_meters <= 1.0 {
        return l1_db;
    }
    l1_db - 20.0 * r_meters.log10()
}

// ------------------------------------------------------------
// Слышит ли слушатель с порогом threshold_db?
// ------------------------------------------------------------
pub fn can_hear(l1_db: f32, r_meters: f32, threshold_db: f32) -> bool {
    db_at_distance(l1_db, r_meters) >= threshold_db
}

// ------------------------------------------------------------
// Максимальный радиус слышимости источника
//   найти R, при котором L2 = threshold
//
//   L1 − 20·log10(R) = threshold
//   log10(R) = (L1 − threshold) / 20
//   R = 10^( (L1 − threshold) / 20 )
// ------------------------------------------------------------
pub fn hearing_radius(l1_db: f32, threshold_db: f32) -> f32 {
    let diff = l1_db - threshold_db;
    if diff <= 0.0 {
        return 0.0;
    }
    10.0f32.powf(diff / 20.0)
}
