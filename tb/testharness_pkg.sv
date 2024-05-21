// Copyright 2022 EPFL
// Solderpad Hardware License, Version 2.1, see LICENSE.md for details.
// SPDX-License-Identifier: Apache-2.0 WITH SHL-2.1

package testharness_pkg;

  import addr_map_rule_pkg::*;
  import core_v_mini_mcu_pkg::*;

  localparam EXT_XBAR_NMASTER = 1;
  localparam EXT_XBAR_NSLAVE = 1;

  //master idx
  localparam logic [31:0] EXT_MASTER0_IDX = 0;


  //slave mmap and idx
  localparam logic [31:0] CGRAITF_START_ADDRESS = core_v_mini_mcu_pkg::EXT_SLAVE_START_ADDRESS;
  localparam logic [31:0] CGRAITF_SIZE = 32'h100;
  localparam logic [31:0] CGRAITF_END_ADDRESS = CGRAITF_START_ADDRESS + CGRAITF_SIZE;
  localparam logic [31:0] CGRAITF_IDX = 32'd0;

  localparam addr_map_rule_t [EXT_XBAR_NSLAVE-1:0] EXT_XBAR_ADDR_RULES = '{
      '{idx: CGRAITF_IDX, start_addr: CGRAITF_START_ADDRESS, end_addr: CGRAITF_END_ADDRESS}
  };

  //slave encoder
  localparam EXT_NPERIPHERALS = 1;

  // CGRA interface test
  localparam logic [31:0] CGRAITF_PERIPH_START_ADDRESS = core_v_mini_mcu_pkg::EXT_PERIPHERAL_START_ADDRESS + 32'h0;
  localparam logic [31:0] CGRAITF_PERIPH_ACC_SIZE = 32'h100;
  localparam logic [31:0] CGRAITF_PERIPH_ACC_END_ADDRESS = CGRAITF_PERIPH_START_ADDRESS + CGRAITF_PERIPH_ACC_SIZE;
  localparam logic [31:0] CGRAITF_PERIPH_ACC_IDX = 32'd0;

  localparam addr_map_rule_t [EXT_NPERIPHERALS-1:0] EXT_PERIPHERALS_ADDR_RULES = '{
      '{
          idx: CGRAITF_PERIPH_ACC_IDX,
          start_addr: CGRAITF_PERIPH_START_ADDRESS,
          end_addr: CGRAITF_PERIPH_ACC_END_ADDRESS
      }
  };

  localparam int unsigned EXT_PERIPHERALS_PORT_SEL_WIDTH = EXT_NPERIPHERALS > 1 ? $clog2(
      EXT_NPERIPHERALS
  ) : 32'd1;

endpackage
