mod animation;
mod clothing;
mod parts;
mod render;
mod slice;
mod volume;

use crate::render::render_hero;

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
