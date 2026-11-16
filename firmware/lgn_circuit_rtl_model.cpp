// Behavioral C model for the lgn_circuit_rtl black box (see
// firmware/lgn_circuit_rtl.json). Vitis HLS runs *this* during csim/cosim's
// C half; the actual synthesized hardware comes from
// lgn_stuff/LogicModelTiny_20261102-180844/circuit.v +
// firmware/lgn_circuit_rtl_wrapper.v instead. Must stay functionally
// identical to that Verilog (both were derived from the same circuit.json),
// which is why it just packs/unpacks around the same golden gate-network
// model used on the HLS-only branch.
#include "ap_int.h"
#include "lgn_circuit_golden.h"

void lgn_circuit_rtl(ap_uint<N_LGN_INPUTS> inp, ap_uint<96> *scores_flat) {
  bool in[N_LGN_INPUTS];
  for (int i = 0; i < N_LGN_INPUTS; ++i) {
#pragma HLS UNROLL
    in[i] = inp[i];
  }
  ap_uint<7> out[N_LGN_OUTPUTS];
  lgn_circuit_golden(in, out);
  ap_uint<96> packed = 0;
  for (int k = 0; k < N_LGN_OUTPUTS; ++k) {
#pragma HLS UNROLL
    packed.range(k * 32 + 31, k * 32) = out[k];
  }
  *scores_flat = packed;
}
