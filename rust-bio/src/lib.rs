// ============================================================
// rust-hero — библиотека рендера и данных героя
// FFI-мост между C++ (мир) и Rust (герой, шум, анимация)
// ============================================================

mod animation;
mod clothing;
mod noise_table;
mod parts;
mod render;
mod slice;
mod step_noise;
mod volume;

use crate::render::render_hero;

// ============================================================
// FFI: рендер героя
// ============================================================
#[no_mangle]
pub unsafe extern "C" fn rust_render_hero(
    buffer: *mut u32,
    width: i32,
    height: i32,
    cx: i32,
    cy: i32,
    facing: f32,
    scale: f32,
    pose: u32,
    anim_phase: f32,
) {
    render_hero(
        buffer, width, height, cx, cy, facing, scale, pose, anim_phase,
    );
}

// ============================================================
// FFI: версия библиотеки
// ============================================================
#[no_mangle]
pub extern "C" fn rust_hero_version() -> u32 {
    100
}

// ============================================================
// FFI: частота фазы для позы
// ============================================================
#[no_mangle]
pub extern "C" fn rust_get_phase_rate(pose: u32) -> f32 {
    crate::animation::phase_rate_for(pose)
}

// ============================================================
// FFI: амплитуды рук и ног для позы
// ============================================================
#[no_mangle]
pub extern "C" fn rust_get_amplitudes(pose: u32, arm_out: *mut f32, leg_out: *mut f32) {
    let (arm, leg) = crate::animation::amplitudes_for(pose);
    unsafe {
        *arm_out = arm;
        *leg_out = leg;
    }
}

// ============================================================
// FFI: получить dB по имени источника шума
// ============================================================
#[no_mangle]
pub extern "C" fn rust_get_noise_db(name: *const u8, len: usize) -> f32 {
    if name.is_null() || len == 0 {
        return 0.0;
    }

    let slice = unsafe { std::slice::from_raw_parts(name, len) };

    match std::str::from_utf8(slice) {
        Ok(s) => match crate::noise_table::find_noise(s) {
            Some(n) => n.db,
            None => 0.0,
        },
        Err(_) => 0.0,
    }
}

// ============================================================
// FFI: шум шага в dB
// ============================================================
#[no_mangle]
pub extern "C" fn rust_step_db(
    pose: u32,
    surface: *const u8,
    surface_len: usize,
    footwear: *const u8,
    footwear_len: usize,
) -> f32 {
    if surface.is_null() || footwear.is_null() {
        return 0.0;
    }

    let s_str = unsafe { std::slice::from_raw_parts(surface, surface_len) };
    let f_str = unsafe { std::slice::from_raw_parts(footwear, footwear_len) };

    let s = match std::str::from_utf8(s_str) {
        Ok(v) => v,
        Err(_) => return 0.0,
    };
    let f = match std::str::from_utf8(f_str) {
        Ok(v) => v,
        Err(_) => return 0.0,
    };

    crate::step_noise::compute_step_db(pose, s, f)
}

// ============================================================
// FFI: печать таблицы шума шага в консоль
// ============================================================
#[no_mangle]
pub extern "C" fn rust_print_step_table() {
    use crate::step_noise::*;

    println!("=== ТАБЛИЦА ШУМА ШАГА (dB) ===\n");

    let surfaces = [
        "sand", "grass", "dirt", "wood", "water", "concrete", "metal",
    ];
    let footwear = [
        "barefoot",
        "socks",
        "sneakers",
        "boots_soft",
        "boots_rubber",
        "heels",
    ];
    let gaits = [(1u32, "walk"), (2, "run"), (3, "sneak")];

    for (pose, gait_name) in gaits {
        println!("--- {} ---", gait_name);
        print!("{:12}", "");
        for f in footwear {
            print!("{:>13}", f);
        }
        println!();

        for s in surfaces {
            print!("{:12}", s);
            for f in footwear {
                let db = compute_step_db(pose, s, f);
                print!("{:>12.1}", db);
            }
            println!();
        }
        println!();
    }
}

// ============================================================
// FFI: громкость на расстоянии
// ============================================================
#[no_mangle]
pub extern "C" fn rust_db_at_distance(l1_db: f32, r_meters: f32) -> f32 {
    crate::step_noise::db_at_distance(l1_db, r_meters)
}

// ============================================================
// FFI: радиус слышимости
// ============================================================
#[no_mangle]
pub extern "C" fn rust_hearing_radius(l1_db: f32, threshold_db: f32) -> f32 {
    crate::step_noise::hearing_radius(l1_db, threshold_db)
}
