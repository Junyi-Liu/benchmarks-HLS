# Contents:
Benchmarks, testbenches, and transformed codes by parametric loop pipelining (PLP) and runtime dependence analysis (RT-Dep)  

# Naming rule:  
XXX.c : benchmark loop  
XXX_vivado.c : transformed by PLP for Vivado HLS 2015.4
XXX_rt.c : transformed by RT-Dep and manually tuned for Vivado HLS 2015.4  
XXX_test.c : testbench  

globals.h is the head file for the codes transformed by RT-Dep   

# Related publication:
Junyi Liu, Samuel Bayliss, and George A. Constantinides, "Offline synthesis of online dependence testing: Parametric loop pipelining for HLS," in FCCM, 2015.
