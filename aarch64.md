# Arm V8 A-profile Tutorial [src](https://developer.arm.com/architectures/learn-the-architecture/a-profile)
# Registers
`Rx` means registers `R0, R1, ...`
## General Purpose
31 regisrers: `X0...X30 = 64 bit = 8 bytes` or `W0...W30 = 32 bit = 4 bytes`.\
При арифметических операциях на `W` старшая часть регистров зануляется.\
## Floating point registers
32 128-bit floating point registers `V0..V31`:
```
Size suffix extentions:
B = 8 bit little part
H = 16
S = 32
D = 64
Q = 128
```

**Attention!**
```
addr = X = 64 = 8B; in [..] can be X reg only!!!
```
## Zero registers
`XZR`, `WZR` - NULL-read-only
## Special registers
`SP` - on of the stack pointers\
`PC` - programm counter (not generally aviable, need special instr `ADR`)\
`ELR_ELx` - registers are used for returning from exceptions\
## System Registers
`SCTLR_ELx` - system registers (`x` указывает на уровень привилегий)\
Используют команды `MRS`, `MSR` для чтения и записи в регистры `X0..`\

# Arithmetic and logic operations
Basic format
```
<operation> <destination = 1 or 2 registers> <input register> <input register or constant>
```
`S` suffix means flag influence\
Математические операции с регистрами `W` зануляют старшую часть `X`.

# Floating point
Instructions start with `F`.
# Bit manipulations
Supports:
* bit field insert
* bit field extract
* bit field clear
* reverse bit order

# Extention and Saturation
* Sign extend (filling by `0xF` or `0x0` at the `B`, `H` or `W` size)
* Zero extend (similar to sign but using `0x0`)

# Format Conversion

# Vector Data

# Loads and Stores
basic syntax:
```
LDR<Sign><Size> <Destination>, [<src addr>]
STR<Size> <Source>, [<dst addr>]
```
## Size
```
# load 32-bit from <address> to W0
LDR        W0, [<address>]
# load 64-bit from <address> to X0
LDR        X0, [<address>]
# store bottom 8-bit (1/4 W0) of W0 to <address>
STRB       W0, [<address>]
# store bottom 16-bit (1/2 W0) of W0 to <address>
STRH       W0, [<address>]
# store bottom 32-bit (1/2 X0) of X0 to <address>
STRW       X0, [<address>]
```

## Zero and Sign extension of loads
**By default (without `<Sign>`) loads' destination register are zero-extended (the hight rest of register is zeroed)**
Adding `S` means sign extension.

## Addressing modes of loads and stores
### Base register
```
LDR W0, [X1] = 32-bit from addr in X1 to reg W0, rest high bits of W0 are zeroes.
```
### Offset addressing modes
```
LDR W0, [X1, #12] = 32-bit from addr X1+12 to reg W0, rest high bits of W0 are zeroes.
LDR W0, [X1, X2]
```

### Pre-index addressing mode
```
LDR W0, [X1, #12]! = X1 += 12; 32-bit from updated addr in X1 to reg W0, rest high bits of W0 are zeroes.
```

### Post-index addressing mode
```
LDR W0, [X1], #12 = 32-bit from updated addr in X1 to reg W0, rest high bits of W0 are zeroes; X1 += 12
```

## Load pair and store pair
`LDP`, `STP` with all addressing modes support.\
They are often used with stack.
```
Size suffix extentions:
B = 8 bit little part = 1 byte little part
H = 16 = 2B
S = 32 = 4B
D = 64 = 8B
Q = 128 = 16B
```
**Attention!**
```
addr = X = 64 = 8B; in [..] can be X reg only!!!
```
```
LDP W3, W7, [X0] = load 32-bit (4 bytes) from addr X0 to reg W3; load 32-bit (4 bytes) from addr X0 + 4 to reg W7.

STP D0, D1, [X4] = store bottom 8 bytes from reg D0 to addr X4; store bottom 8 bytes from reg D1 to addr X4 + 8.
```
### Typical PUSH
```
STP X0, X1, [SP, #-16]! =
  SP -= 16
  store 8 bytes of reg X0 into addr SP
  store 8 bytes of reg X1 into addr SP + 8
```
### Typical POP
```
LDP X0, X1, [SP], #16 =
  load 8 bytes from addr SP to reg X0 
  load 8 bytes from addr SP + 8 to reg X0
  SP += 16
```

**In Aarh64 stack-pointer must be 128-bit (16-byte) aligned!**

## Using floating-point registers
```
LDR D1, [X0] = load bottom 8 bytes from addr X0 to register D1
STR Q0, [X0, X1] = store 16 bytes to addr X0+X1
LDP Q1, Q3, [X5], #256 = 
  load 128-bit from addr X5 to reg Q1
  load 128-bit from addr X5 + 16 to reg Q3
  X5 += 256 (+= 32 byte = 2*Q)
  equivalent of loading pair of registers in continuous mem segment
```

# Program flow
## unconditional
```
B <label> - PC-relative, direct, [-128MB; +128MB]
BR <Xn> - jump to addr in reg Xn
```
## conditional

