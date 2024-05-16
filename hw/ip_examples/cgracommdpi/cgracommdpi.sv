// Copyright lowRISC contributors.
// Licensed under the Apache License, Version 2.0, see LICENSE for details.
// SPDX-License-Identifier: Apache-2.0

module cgracommdpi #(
  parameter string NAME = "cgracomm"
)(
  input  logic clk_i,
  input  logic rst_ni
);
  import "DPI-C" function
    void CGRACallToWrite(input int a);

endmodule
