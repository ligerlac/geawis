#include "lgn_circuit.h"

// lgn_circuit_rtl is the RTL black box described by lgn_circuit_rtl.json:
// real hardware is lgn_stuff/LogicModelTiny_20261102-180844/circuit.v (the
// gate network compiled straight from the trained model), wrapped by
// firmware/lgn_circuit_rtl_wrapper.v; firmware/lgn_circuit_rtl_model.cpp is
// the behavioral stand-in Vitis HLS runs during csim. This function is just
// the pack/call/unpack shim between that bit-packed blackbox signature and
// the bool[]/ap_uint<7>[] contract the rest of the firmware (firmware/lgn.cpp)
// already uses -- so nothing downstream of lgn_circuit() needs to know or
// care which backend (this branch's RTL import vs. feat-train-lgn's pure
// HLS-C++) produced the result.
void lgn_circuit_rtl(ap_uint<N_LGN_INPUTS> inp, ap_uint<96> *scores_flat);

void lgn_circuit(bool in[N_LGN_INPUTS], ap_uint<7> out[N_LGN_OUTPUTS]) {
#pragma HLS ARRAY_PARTITION variable=in complete
#pragma HLS ARRAY_PARTITION variable=out complete

  ap_uint<N_LGN_INPUTS> packed_in = 0;
  for (int i = 0; i < N_LGN_INPUTS; ++i) {
#pragma HLS UNROLL
    packed_in[i] = in[i];
  }

  // Receive into a local variable, not a forwarded pointer argument --
  // Vitis HLS rejects passing a caller's own pointer-typed argument
  // straight through to a black-boxed call.
  ap_uint<96> result;
  lgn_circuit_rtl(packed_in, &result);

  for (int k = 0; k < N_LGN_OUTPUTS; ++k) {
#pragma HLS UNROLL
    out[k] = result.range(k * 32 + 6, k * 32);
  }
}
