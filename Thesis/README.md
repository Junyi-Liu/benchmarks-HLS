# Contents:
Benchmarks, testbenches, and transformed codes 

# Abbreviation: 
Orig   : Original Benchmark Loops
PLP    : Parametric Loop Pipelining
LSP    : Loop Splitting
RT-Dep : Runtime Dependence Analysis

# Naming rule:  
XXX.c        : benchmark loop  
XXX_vivado.c : transformed by PLP or LSP for Vivado HLS 2017.2
XXX_rt.c     : transformed by RT-Dep and manually tuned for Vivado HLS 2017.2  
XXX_test.c   : testbench  

globals.h is the head file for the codes transformed by RT-Dep   

# Related publication:
Junyi Liu, "Parametric Polyhedral Optimisation for High-level Synthesis," PhD Thesis, Imperial College London, 2017

