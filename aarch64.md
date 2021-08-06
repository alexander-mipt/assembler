# Arm V8 A-profile Tutorial [src](https://developer.arm.com/architectures/learn-the-architecture/a-profile)
# Registers
`Rx` means registers `R0, R1, ...`
## General Purpose
31 regisrers: `X0...X30` or `W0...W30`.\
При арифметических операциях на `W` старшая часть регистров зануляется.\
## Floating point registers
32 128-bit floating point registers `V0..V31`:
```
B = 8 bit little part
H = 16
S = 32
D = 64
Q = 128
```
## Zero registers
`XZR`, `WZR` - NULL-read-only
## Special registers
`SP` - on of the stack pointers\
`PC` - programm counter (not generally aviable, need special instr `ADR`)\
`ELR_ELx` - registers are used for returning from exceptions\
## System Registers
`SCTLR_ELx` - system registers\
Используют команды `MRS`, `MSR` для чтения и записи в регистры `X0..`
