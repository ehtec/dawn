SKIP: INVALID

//
// fragment_main
//

RWByteAddressBuffer prevent_dce : register(u0);
uint3 subgroupShuffleUp_abaea0() {
  uint3 res = WaveReadLaneAt((1u).xxx, (WaveGetLaneIndex() - 1u));
  return res;
}

void fragment_main() {
  prevent_dce.Store3(0u, subgroupShuffleUp_abaea0());
}

//
// compute_main
//

RWByteAddressBuffer prevent_dce : register(u0);
uint3 subgroupShuffleUp_abaea0() {
  uint3 res = WaveReadLaneAt((1u).xxx, (WaveGetLaneIndex() - 1u));
  return res;
}

[numthreads(1, 1, 1)]
void compute_main() {
  prevent_dce.Store3(0u, subgroupShuffleUp_abaea0());
}

