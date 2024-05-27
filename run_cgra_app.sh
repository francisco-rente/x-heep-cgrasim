#!/bin/bash


# if it exists remove /tmp/cgrasim
rm /tmp/cgrasim 
make app PROJECT=cgra_itf 
cd ./build/openhwgroup.org_systems_core-v-mini-mcu_0/sim-verilator
./Vtestharness +firmware=../../../sw/build/main.hex
 

