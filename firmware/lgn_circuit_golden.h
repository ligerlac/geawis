#ifndef GEAWIS_LGN_CIRCUIT_GOLDEN_H
#define GEAWIS_LGN_CIRCUIT_GOLDEN_H

#include "lgn_circuit.h"

// Behavioral reference only on this branch -- see lgn_circuit_golden.cpp.
void lgn_circuit_golden(bool in[N_LGN_INPUTS], ap_uint<7> out[N_LGN_OUTPUTS]);

#endif
