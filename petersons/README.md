Peterson Locking Algorithm
=========================

Memory barrier is needed, but it seems that `asm volatile ("mfence":::"memory")` doesn't create a hardware memory barrier, the result is not consistent with the expected. My CPU arch is Intel x86-64 SMP, it seems that CPU reordered the instructions. [**FAILED**]
