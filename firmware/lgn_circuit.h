#ifndef GEAWIS_LGN_CIRCUIT_H
#define GEAWIS_LGN_CIRCUIT_H

// Public contract for the LGN gate-network classifier. On this branch
// (lgn-direct-rtl) lgn_circuit() is a hand-written pack/unpack shim around
// an RTL black box (see lgn_circuit.cpp/lgn_circuit_rtl.json); on
// feat-train-lgn it's generated directly by scripts/generate_lgn_firmware.py.
// Either way the signature below is what firmware/lgn.cpp calls.

#include "ap_int.h"

#define N_LGN_INPUTS 1728
#define N_LGN_OUTPUTS 3

// out[k] is the raw (unnormalized) group-sum logit for class k -- the sum of
// up to 86 boolean circuit taps feeding that class, each contributing 0 or 1.
// Fits in ap_uint<7> (max observed group size well under 128). Classification
// is argmax(out[0..N_LGN_OUTPUTS-1]); the "tau" normalization applied in the
// original circuit.c (a constant positive scale shared by all classes) is
// omitted here since it does not change the argmax.
void lgn_circuit(bool in[N_LGN_INPUTS], ap_uint<7> out[N_LGN_OUTPUTS]);

#endif
