Test & Set Lock
===============
This lock is based on atomic operation, and must be supported at hardware level, such as `xchg` is an atomic operation. I have checked NPTL mutex implementation, it is also based on atomic operation. [**Success**]
