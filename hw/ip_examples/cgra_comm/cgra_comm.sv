// Copyright 2022 OpenHW Group
// Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1




            // .req_req_t (req_pkg::req_req_t), 
            // .req_rsp_t (req_pkg::req_rsp_t),
            // .obi_req_t (obi_pkg::obi_req_t),
            // .obi_resp_t(obi_pkg::obi_resp_t)



            // .clk_i, 
            // .rst_ni, 
            // .reg_req_i(ext_periph_slv_req[testharness_pkg::CGRACOMM_PERIPH_ACC_IDX]),
            // .reg_rsp_o(ext_periph_slv_rsp[testharness_pkg::CGRACOMM_PERIPH_ACC_IDX]),
            // .masters_req_o(ext_master_req[testharness_pkg::EXT_MASTER0_IDX]),
            // .masters_resp_i(ext_master_resp[testharness_pkg::EXT_MASTER0_IDX]),
            // .slave_req_i(ext_slave_req[testharness_pkg::CGRAITF_IDX]),
            // .slave_resp_o(ext_slave_resp[testharness_pkg::CGRAITF_IDX])


import "DPI-C" function void CGRACallToWrite(int a);


module cgra_comm #(
    parameter type reg_req_t = logic,
    parameter type reg_rsp_t = logic,
    parameter type obi_req_t = logic,
    parameter type obi_resp_t = logic
    
)(
    input logic clk_i,    
    input logic rst_ni,   

    // input  obi_req_t  slave_req_i,
    // output obi_resp_t slave_resp_o,

    // input reg_rsp_t masters_resp_i,
    // output reg_req_t masters_req_o,

    input  reg_req_t reg_req_i,
    output reg_rsp_t reg_rsp_o
); 

  // assign slave_resp_o = '0;
  // assign masters_req_o = '0;
  assign reg_rsp_o = '0;
  wire dummy_unused_bits = |reg_req_i[67:32];

  always_ff @(posedge clk_i or negedge rst_ni) begin : proc_
      if (reg_req_i.valid && reg_req_i.write) begin
        CGRACallToWrite(reg_req_i.wdata);
      end
  end


endmodule
