## Ccылки
* [Народный справочник по инструкциям x86](http://looch-disasm.narod.ru/refe01.htm)
* [Архитектура Aarch64](https://developer.arm.com/architectures/learn-the-architecture/a-profile)
* [Анализ кода с помощью ассемблера](https://ru.wikibooks.org/wiki/%D0%90%D1%81%D1%81%D0%B5%D0%BC%D0%B1%D0%BB%D0%B5%D1%80_%D0%B2_Linux_%D0%B4%D0%BB%D1%8F_%D0%BF%D1%80%D0%BE%D0%B3%D1%80%D0%B0%D0%BC%D0%BC%D0%B8%D1%81%D1%82%D0%BE%D0%B2_C#%D0%A1%D1%82%D0%B5%D0%BA)
## [Little-endian / Big-endian](https://en.wikipedia.org/wiki/Endianness)
* **Endianness** - the order or sequence of bytes of a word of digital data in computer memory.
  Endianness is primarily expressed as big-endian (BE) or little-endian (LE).

![Endian](https://user-images.githubusercontent.com/55103017/125188165-76434500-e23b-11eb-8d0d-4f2c4612add6.PNG) \
[src](https://en.wikipedia.org/wiki/File:Big-Endian.svg)

## Структура команд Ассемблера
* **Инструкция** - набор чисел, представляющий собой закодированную функцию процессора. В ее состав входит операция и операнды.
* **Операция (opcode)** - определяет вид инструкции (сложение, запись в память и т.д.)
* **Операнды (operands)** - аргументы операции
  * От 0 до 3-х
  * **Непосредственный операнд**
    * **Числовая константа**
    * **Символ**
  * **Указатель на ячейку памяти**
  * **Неявный операнд** - операнд, не фиксирующийся в исходном коде инстркуции,
    но входящий в логику ее работы (к примеру, закрепленный за инструкцией регистр) - должен быть задокументирован
* **Суффикс** - суффикс операции, указывающий на размер всех операндов
  * `b` (byte) - 1B
  * `w` (word) - 2B
  * `l` (long) - 4B
  * `q` (quad) - 8B
### Группы команд в ассемблере (на примере x86)
* Основная арифметика (`add`, `adc`, `cmp`)
* Умножение и деление (`div`, `mul`)
* Логическая арифметика (`xor`, `test`)
* Битовые операции (`bsf`, `bsr`, `bt`, `bts`)
* Инкремент и декремент (`inc`, `dec`)
* Пересылка данных (`mov`, `cbw`, `bswap`, `nop`)
* Работа со стеком (`push`, `pop`)
* Условные команды (`jmp`, `jnz`, )
* Переходы и процедуры (`jmp`, `call`, `leave`, `enter`)
* Команды сдвига (`shl`, `sar`, `rol`, `rcr`, `shld`)
* Цепочечные команды (`movs`, `cmps`, `stos`, `lods`, `ins`)
* Десятичная арифметика (`daa`, `das`, `aaa`)
* Установка флагов (`clc`, `stc`, `cli`)
* Команды для работы с сегментными регистрами (`lds`, `lfs`, `lss`)
* Специальные команды (`lea`, `xlat`, `bound`, `cmpxchg`)
* Системные команды (`out`, `lsl`, `lock`)
* Привилегированные (`ltr`, `lldt`, `lar`)
* Вызов прерывания (`int`)

### Команды цикла
* `loop label` - `do {} while(--ecx)`: 
  1. ecx -= 1
  2. ecx == 0 --> перейти на метку `label`; ecx != 0 --> перейти на метку после инструкции `loop`

### Команды сравнения, условный и безусловный переходы (conditional / unconditional branch)
#### Команды сравнения
##### x86_64
`cmp op2, op1` - выполняет вычитание `op1` - `op2` и устанавливает флаги
`test op1, op2` - выполняет побитовое И на операндами, не изменяя их, а только выставляя флаги
#### Условный переход
Порядок дейтвий: арифметика --> выставление флагов --> анализ флагов и сам переход \
Обычно пара [cmp+jmp], или [test+jmp], или специальная инструкция \
`jxx label` - условный переход, где xx - обозначает мнемонику операции:
* `e` - equal (==)
* `n` - not (~)
* `g` - greater (signed >)
* `l` - less (signed <)
* `a` - above (unsigned >)
* `b` - below (unsigned <)
```
cmpl $15, %eax /* сравнение */
jne not_equal: /* если операнды не равны, перейти на метку not_equal */
```
#### Безусловный переход (uncoditional branch)
`jmp addr` - передаёт управление на адрес, не проверяя никаких условий. Адрес может быть задан в виде непосредственного значения (метки), регистра или обращения к памяти.

### Команда `mov`
#### x86_64
`mov src, dst`
#### Aarch64
`mov dst src`
### Команда `lea` - load effective address
`lea src dst`
```
leal 0x32, %eax /* аналогично movl $0x32, %eax */
leal $0x32, %eax /* вызовет ошибку при компиляции, так как $0x32 не является адресом */
leal $some_var, %eax /* аналогично, ошибка компиляции */
leal 4(%esp), %eax /* поместить в %eax адрес предыдущего элемента в стеке; фактически, %eax = %esp + 4 */
```
```
 movl $10, %eax
 movl $7, %ebx
 leal 5(%eax) , %ecx /* %ecx = %eax + 5 = 15 */
 leal -3(%eax) , %ecx /* %ecx = %eax - 3 = 10 */
 leal (%eax,%ebx) , %ecx /* %ecx = %eax + %ebx × 1 = 17 */
 leal (%eax,%ebx,2) , %ecx /* %ecx = %eax + %ebx × 2 = 24 */
 leal 1(%eax,%ebx,2), %ecx /* %ecx = %eax + %ebx × 2 + 1 = 25 */
 leal (,%eax,8) , %ecx /* %ecx = %eax × 8 = 80 */
 leal (%eax,%eax,2) , %ecx /* %eax = %eax + %eax × 2 = %eax × 3 = 30 */
 leal (%eax,%eax,4) , %ecx /* %eax = %eax + %eax × 4 = %eax × 5 = 50 */
 leal (%eax,%eax,8) , %ecx /* %eax = %eax + %eax × 8 = %eax × 9 = 90 */
```

## Символы и метки
* **Символ** - некоторая константа. Хранится в объектном файле, используется для наименования констант, переменных, функций и т.д. Имеет характеристики:
  * тип: `a` - absolute value, `t` - in text section, `D` - global in, data section, ...
  * имя - привязанное к символу наименование
  * константа - значение символа
```
[user@host:~]$ nm hello.o
00000000 d hello_str
0000000e a hello_str_length
00000000 T main
```
* **Метка** - символ, значение которого - адрес памяти. Используется для упорядочивания инструкций в программе.
  * `.` - текущее значение адреса
  * `string:` - создает метку с именем "string"
```
hello_str:
 .string "Hello, world!\n"
```
## Константы
* `$0x01` - константа
* 0x01 - обращение по адресу

## Директивы ассемблера
Директивы размещают данные в памяти. Их аргументы - список выражений, разделенных запятыми.

### Директивы для работы с символами
* `.set` *`symbol`*, *`expression`* - создает новый символ
* `.globl` *`symbol`* - сделать символ *`symbol`* глобальным

### Директивы для размещения числовых констант
* `.byte` - размещают каждое выражение как 1B
* `.short`, `.hword`  - 2B
*  `.long`, `.word` - 4B
*  `.quad` - 8B
```
.byte 0x10, 0xf5, 0x42, 0x55
.long 0xaabbaabb
.short -123, 456
```
### Директивы для размещения строковых [литералов](https://ru.wikipedia.org/wiki/%D0%9B%D0%B8%D1%82%D0%B5%D1%80%D0%B0%D0%BB_(%D0%B8%D0%BD%D1%84%D0%BE%D1%80%D0%BC%D0%B0%D1%82%D0%B8%D0%BA%D0%B0))
* `.ascii` *`"STR"`* - размещает *`STR`* в памяти без добавления нулевого байта `\0`
* `.string` *`"STR"`* - размещает *`STR`* в памяти с добавленияем нулевого байта `\0`
```
.string "Hello, world\n"
```
### Директивы секций
* `.data` - секция данных
* `.section .rodata` - секция для хранения read only data
* `.bss` - секция неинициализированных данных

### Директива заполнения, выравнивания
* `.space` *`кол-во байт`*, *`заполнитель`* - резервирует *`кол-во байт`*, инициализируя их *`заполнитель`* (опционально)
* `.p2align` *`степень 2`*, *`заполнитель`*, *`максимум`* - выравнивает текущий адрес до заданной границы. Граница
выравнивания задаётся как степень числа 2: например, если вы указали `.p2align 3` —
следующее значение будет выровнено по **8-байтной** границе. Для выравнивания
размещается необходимое количество байт-заполнителей со значением заполнитель.
Если для выравнивания требуется разместить **более** чем максимум байт-заполнителей,
то выравнивание **не выполняется**.

## Регистры
* **Общего назначения (general purpose)**
  * x86-64
    * `rax` (8B), `eax` (least 4B of rax), `ax` (least 2B of eax), `ah` (high 1B of ax), `al` (least 1B of ax)
    * `rbx`, `rcx`, `rdx`
    * `rsp` (stack pointer), `rbp` (stack base pointer)
    * `rsi` (src idx reg), `rdi` (dst idx reg)
* **Сегментные регистры**
  * x86-64
    * `cs` - code segment
    * `ds` - data segment
    * `ss` - stack segment
    * `es` - extra segment
    * `fs` - F segment
    * `gs` - G segment
* **Регистр флагов**
  * x86-64
    * [`rflags`](https://ru.wikipedia.org/wiki/%D0%A0%D0%B5%D0%B3%D0%B8%D1%81%D1%82%D1%80_%D1%84%D0%BB%D0%B0%D0%B3%D0%BE%D0%B2)
      * `CF` - carry flag
      * `PF` - parity flag
      * `ZF` - zero flag
      * `SF` - sign flag
      * `OF` - overflow flag
      * `AC` - alignment check
      * `AF`, `TF`, `IF`, `DF`, `IOPL`, `NT`, `RF`, `VM`, `VIF`, `VIP`, `ID`
* **Регистр текущей команды**
  * x86-64 (not available directly)
    * `rip` - instruction pointer


## Stack
  * стэк растет в сторону убывания адресов
  * вершина стека (stack pointer) динамична
  * дно стека (base pointer) статично - начало стекового фрейма
  * `push`
    1. `rsp` -= sizeof(elem) bytes
    2. записать элемент по адресу, на который указывает значение в регистре rsp
  * `pop`
    1. записать элемент по адресу, на который указывает значение в регистре rsp
    2. `rsp` += sizeof(elem) bytes
  * `call` *`label`*
    1. Поместить в стек (`push`) адрес следующей за `call` команды (адрес возврата, берется из `rip`)
    2. Передать управление указанной метке (*`label`*)
  * `ret` / `ret` *`number`*
    1. Извлечь из стека адрес возврата (`pop`)
    2. Передать управление команде, расположенной по адресу возврата
    3. `rsp` += *`number`* (optional - need to forget func arguments)
  * **Интересный вопрос:** какое значение помещает в стек вот эта команда `pushl %esp`
    Если ещё раз взглянуть на алгоритм работы команды push, кажется очевидным, что в
    данном случае она должна поместить уже уменьшенное значение %esp. Однако в
    документации Intel сказано, что в стек помещается такое значение %esp, каким оно
    было до выполнения команды — и она действительно работает именно так.


## [Типы адресации](https://en.wikipedia.org/wiki/Addressing_mode)
### Addressing modes for code
#### Absolute or Direct
The effective address for an absolute instruction address is the address parameter itself with no modifications.
```
   +----+------------------------------+
   |jump|           address            |
   +----+------------------------------+

   (Effective PC address = address)
```
#### PC-relative
The effective address for a PC-relative instruction address is the offset parameter added to the address of the next instruction. This offset is usually signed to allow reference to code both before and after the instruction.
```
   +----+------------------------------+
   |jump|           offset             |    jump relative
   +----+------------------------------+

   (Effective PC address = next instruction address + offset, offset may be negative)
```
#### Register indirect
The effective address for a Register indirect instruction is the address in the specified register. For example, (A7) to access the content of address register A7.
```
   +-------+-----+
   |jumpVia| reg |
   +-------+-----+

   (Effective PC address = contents of register 'reg')
```
### Addressing modes for data
#### Register or Register Direct
This "addressing mode" does not have an effective address and is not considered to be an addressing mode on some computers.
```
   +------+-----+-----+-----+
   | mul  | reg1| reg2| reg3|      reg1 := reg2 * reg3;
   +------+-----+-----+-----+
```
```
/* записать в регистр %ecx операнд, который
находится в регистре %eax */
movl %eax, %ecx
```

#### Base + offset, and variations
```
   +------+-----+-----+----------------+
   | load | reg | base|     offset     |  reg := RAM[base + offset]
   +------+-----+-----+----------------+

   (Effective address = offset + contents of specified base register)
```
```
/* обратиться по адресу %ebx + 4 */
movl 4(%ebx), %eax
```

#### Immediate/literal
```
   +------+-----+-----+----------------+
   | add  | reg1| reg2|    constant    |    reg1 := reg2 + constant;
   +------+-----+-----+----------------+
```
```
/* загрузить константу 0x12345 в регистр %eax.*/
movl $0x12345, %eax

```

#### Implicit
The implied addressing mode, also called the implicit addressing mode (x86 assembly language), does not explicitly specify an effective address for either the source or the destination (or sometimes both).

Either the source (if any) or destination effective address (or sometimes both) is implied by the opcode.
```
   +-----------------+
   | clear carry bit |
   +-----------------+

   +-------------------+
   | clear Accumulator |
   +-------------------+
```
### Mixed addressing modes (for code or data) 
#### Absolute / direct
```
   +------+-----+--------------------------------------+
   | load | reg |         address                      |
   +------+-----+--------------------------------------+

   (Effective address = address as given in instruction)
```
```
/* Записать в регистр %eax операнд, который содержится в
оперативной памяти по адресу метки num */
movl (num), %eax
```

#### Indexed absolute
```
   +------+-----+-----+--------------------------------+
   | load | reg |index|         address                |
   +------+-----+-----+--------------------------------+

   (Effective address = address + contents of specified index register)
```

#### Base + index
```
   +------+-----+-----+-----+
   | load | reg | base|index|
   +------+-----+-----+-----+

   (Effective address = contents of specified base register + contents of specified index register)
```

#### Base + index + offset
```
   +------+-----+-----+-----+----------------+
   | load | reg | base|index|         offset |
   +------+-----+-----+-----+----------------+

   (Effective address = offset + contents of specified base register + contents of specified index register)
```

#### Scaled
```
   +------+-----+-----+-----+
   | load | reg | base|index|
   +------+-----+-----+-----+

   (Effective address = contents of specified base register + scaled contents of specified index register)
```

#### Register indirect
```
   +------+------+-----+
   | load | reg1 | base|
   +------+------+-----+
 
   (Effective address = contents of base register)
```
```
/* записать в регистр %eax операнд из оперативной памяти, адрес
которого находится в регистре адреса %ebx */
movl (%ebx), %eax
```
#### Memory indirect
Any of the addressing modes mentioned in this article could have an extra bit to indicate indirect addressing, i.e. the address calculated using some mode is in fact the address of a location (typically a complete word) which contains the actual effective address.

#### PC-relative
The PC-relative addressing mode can be used to load a register with a value stored in program memory a short distance away from the current instruction. It can be seen as a special case of the "base plus offset" addressing mode, one that selects the program counter (PC) as the "base register".
```
   +------+------+---------+----------------+
   | load | reg1 | base=PC |     offset     |
   +------+------+---------+----------------+

   reg1 := RAM[PC + offset]
   (Effective address = PC + offset)
```
### Autoincrement / decerement addressing modes
#### Register autoincrement indirect (for code or data)
```
   +------+-----+-------+
   | load | reg | base  |
   +------+-----+-------+

   (Effective address = contents of base register)
```

#### Register autodecrement indirect (for code or data)
```
   +------+-----+-----+
   | load | reg | base|
   +------+-----+-----+

   (Effective address = new contents of base register)
```
### Sequential addressing modes
#### Sequential execution
```
   +------+
   | nop  |              execute the following instruction
   +------+

   (Effective PC address = next instruction address)
```
#### Conditional execution
Some computer architectures have conditional instructions (such as ARM, but no longer for all instructions in 64-bit mode) or conditional load instructions (such as x86) which can in some cases make conditional branches unnecessary and avoid flushing the instruction pipeline. An instruction such as a 'compare' is used to set a condition code, and subsequent instructions include a test on that condition code to see whether they are obeyed or ignored.

#### Skip
```
   +------+-----+-----+
   |skipEQ| reg1| reg2|      skip the next instruction if reg1=reg2
   +------+-----+-----+

   (Effective PC address = next instruction address + 1)
```

## Caller / callee convention
Перед вызовом функции (подпрограммы) необходимо сохранить ее аргументы:
* при помощи регистров
* при помощи общей области памяти (глобальные переменные)
* **при помощи стека**
Также необходимо сохранить контекст программы. \
[Context](https://en.wikipedia.org/wiki/Context_(computing)) - the minimal set of data used by a task (which may be a process, thread, or fiber) that must be saved to allow a task to be interrupted, and later continued from the same point. The context data may be located in processor registers, memory used by the task, or in control registers used by some operating systems to manage the task. The storage memory (files used by a task) is not concerned by the "task context" in the case of a context switch, even if this can be stored for some uses (checkpointing).

## Типичные ассемблерные структуры / оптимизации / трюки






