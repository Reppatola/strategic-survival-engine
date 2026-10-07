mod parts;
mod render;
mod slice;
mod volume;

use crate::render::render_hero;

// ============================================================
// FFI: единственная функция, которую вызывает C++
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
) {
    render_hero(buffer, width, height, cx, cy, facing, scale);
}

// ============================================================
// Версия — для проверки связи
// ============================================================
#[no_mangle]
pub extern "C" fn rust_hero_version() -> u32 {
    100
}
