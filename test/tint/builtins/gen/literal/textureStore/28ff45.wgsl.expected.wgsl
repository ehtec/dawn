@group(1) @binding(0) var arg_0 : texture_storage_2d_array<rg16unorm, write>;

fn textureStore_28ff45() {
  textureStore(arg_0, vec2<i32>(1i), 1i, vec4<f32>(1.0f));
}

@fragment
fn fragment_main() {
  textureStore_28ff45();
}

@compute @workgroup_size(1)
fn compute_main() {
  textureStore_28ff45();
}
