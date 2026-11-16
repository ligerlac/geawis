// Thin clocked/handshake shell around the real (purely combinational,
// clock-free) generated gate network in
// lgn_stuff/LogicModelTiny_20261102-180844/circuit.v, so it satisfies Vitis
// HLS's RTL-blackbox import requirements (ap_clk/ap_rst/ap_ce + full
// ap_ctrl_chain handshake, an ap_vld-qualified output). The module name
// must be exactly "lgn_circuit_rtl" -- Vitis HLS instantiates the blackbox
// by c_function_name (see lgn_circuit_rtl.json), not by rtl_top_module_name.
// tau/beta normalization is skipped here exactly as in circuit.v itself --
// scores_flat carries raw per-class integer sums; see firmware/lgn_circuit.h.
module lgn_circuit_rtl (
    input  wire        ap_clk,
    input  wire        ap_rst,
    input  wire        ap_ce,
    input  wire        ap_start,
    output wire        ap_done,
    output wire        ap_idle,
    output wire        ap_ready,
    input  wire        ap_continue,
    input  wire [1727:0] inp,
    output wire [95:0]   scores_flat,
    output wire          scores_flat_ap_vld
);
  circuit u_circuit (
    .inp(inp),
    .scores_flat(scores_flat)
  );
  assign scores_flat_ap_vld = 1'b1;
  assign ap_done  = ap_start;
  assign ap_idle  = ~ap_start;
  assign ap_ready = ap_start;
endmodule
