//
// fragment_main
//

RWTexture2D<float4> arg_0 : register(u0, space1);
void textureStore_a517cb() {
  arg_0[(int(1)).xx] = (1.0f).xxxx;
}

void fragment_main() {
  textureStore_a517cb();
}

//
// compute_main
//

RWTexture2D<float4> arg_0 : register(u0, space1);
void textureStore_a517cb() {
  arg_0[(int(1)).xx] = (1.0f).xxxx;
}

[numthreads(1, 1, 1)]
void compute_main() {
  textureStore_a517cb();
}

