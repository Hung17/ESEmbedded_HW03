HW03
===
This is the hw03 sample. Please follow the steps below.

# Build the Sample Program

1. Fork this repo to your own github account.

2. Clone the repo that you just forked.

3. Under the hw03 dir, use:

	* `make` to build.

	* `make clean` to clean the ouput files.

4. Extract `gnu-mcu-eclipse-qemu.zip` into hw03 dir. Under the path of hw03, start emulation with `make qemu`.

	See [Lecture 02 ─ Emulation with QEMU] for more details.

5. The sample is a minimal program for ARM Cortex-M4 devices, which enters `while(1);` after reset. Use gdb to get more details.

	See [ESEmbedded_HW02_Example] for knowing how to do the observation and how to use markdown for taking notes.

# Build Your Own Program

1. Edit main.c.

2. Make and run like the steps above.

3. Please avoid using hardware dependent C Standard library functions like `printf`, `malloc`, etc.

# HW03 Requirements

1. How do C functions pass and return parameters? Please describe the related standard used by the Application Binary Interface (ABI) for the ARM architecture.

2. Modify main.c to observe what you found.

3. You have to state how you designed the observation (code), and how you performed it.

	Just like how you did in HW02.

3. If there are any official data that define the rules, you can also use them as references.

4. Push your repo to your github. (Use .gitignore to exclude the output files like object files or executable files and the qemu bin folder)

[Lecture 02 ─ Emulation with QEMU]: http://www.nc.es.ncku.edu.tw/course/embedded/02/#Emulation-with-QEMU
[ESEmbedded_HW02_Example]: https://github.com/vwxyzjimmy/ESEmbedded_HW02_Example

--------------------

- [ ] **If you volunteer to give the presentation next week, check this.**

--------------------

# Calling Convention
指程序或函數間呼叫所用之引數的安排，如在不同的程式語言可能會要求以不同的順序，如由左至右或由右至左將所呼叫函數的引數放入記憶體的暫存器或堆疊之中，亦規定呼叫函數或被呼叫函數必須負責將使用引數自記憶體移除。引數之變數的個數上限亦於呼叫約定中規定。


# ATPCS和AAPCS
1. 基本概念

ATPCS (ARM-Thumb Procedure Call Standard)

規定了一些子程序間調用的基本規則，這些規則包括子程序調用過程中寄存器的使用規則，數據棧的使用規則，參數的傳遞規則。有了這些規則之後，單獨編譯的C語言程序就可以和彙編程序相互調用。
使用ADS的C語言編譯器編譯的C語言子程序滿足用戶指定的ATPCS類型。而對於彙編語言來說，則需要用戶來保證各個子程序滿足ATPCS的要求。

AAPCS (ARM Archtecture Procedure Call Standard)

2007年ARM公司正式推出了AAPCS標準，AAPCS是ATPCS的改進版，目前， AAPCS和ATPCS都是可用的標準。
2. 寄存器使用規則

子程序間通過寄存器R0～R3來傳遞參數。這時，寄存器R0～R3可記作a0～a3。被調用的子程序在返回前無需恢復寄存器R0～R3的內容。
在子程序中，使用寄存器R4～R11來保存局部變量。這時，寄存器R4～R11可以記作v1～v8。如果在子程序中使用了寄存器v1～v8中的某些寄存器，則子程序進入時必須保存這些寄存器的值，在返回前必須恢復這些寄存器的值。在Thumb程序中，通常只能使用寄存器R4～R7來保存局部變量。
寄存器R12用作過程調用中間臨時寄存器，記作IP。在子程序之間的連接代碼段中常常有這種使用規則。
寄存器R13用作堆棧指針，記作SP。在子程序中寄存器R13不能用作其他用途。寄存器SP在進入子程序時的值和退出子程序時的值必須相等。
寄存器R14稱爲連接寄存器，記作LR。它用於保存子程序的返回地址。如果在子程序中保存了返回地址，寄存器R14則可以用作其他用途。
寄存器R15是程序計數器，記作PC。它不能用作其它用途。

3. 堆棧使用規則

ATPCS規定堆棧爲FD(Full Descending: sp指向最後一個壓入的值，數據棧由高地址向低地址生長)類型，即滿遞減堆棧，並且對堆棧的操作是8字節對齊。所以經常使用的指令就有STMFD和LDMFD。

    對於彙編程序來說，如果目標文件中包含了外部調用，則必須滿足下列條件：

外部接口的堆棧必須是8字節對齊的。
在彙編程序中使用PRESERVE8僞指令告訴連接器，本彙編程序數據是8字節對齊的。

4. 參數傳遞規則

根據參數個數是否固定，可以將子程序分爲參數個數固定的子程序和參數個數可變化的子程序。
這兩種子程序的參數傳遞規則是不一樣的。

4.1 參數個數可變子程序參數傳遞規則

對於參數個數可變的子程序，當參數個數不超過4個時，可以使用寄存器R0～R3來傳遞參數；當參數超過4個時，還可以使用堆棧來傳遞參數。
在傳遞參數時，將所有參數看作是存放在連續的內存字單元的字數據。然後，依次將各字數據傳遞到寄存器R0，R1，R2和R3中。如果參數多於4個，則將剩餘的字數據傳遞到堆棧中。入棧的順序與參數傳遞順序相反，即最後一個字數據先入棧。

4.2 參數個數固定子程序參數傳遞規則

如果系統不包含浮點運算的硬件部件，浮點參數會通過相應的規則轉換成整數參數（若沒有浮點參數，此步省略），然後依次將各字數據傳送到寄存器R0～R3中。如果參數多於4個，將剩餘的字數據傳送堆棧中，入棧的順序與參數順序相反，即最後一個字數據先入棧。在參數傳遞時，將所有參數看作是存放在連續的內存字單元的字數據。

5. 子程序結果返回規則

子程序中結果返回的規則如下：

結果爲一個32位整數時，可以通過寄存器R0返回；
結果爲一個64位整數時，可以通過寄存器R0和R1返回；
結果爲一個浮點數時，可以通過浮點運算部件的寄存器f0、d0或s0來返回；
結果爲複合型浮點數（如複數）時，可以通過寄存器f0～fn或d0～dn來返回；
對於位數更多的結果，需要通過內存來傳遞。


		int singleparameter(int a)
		{
		    return a+a;
		}

		int multieparameter(int a, int b, int c, int d, int e, int f)
		{
		    return a+b+c+d+e+f;
		}
		void manyreturn(int a, int b, int *add, int *sub, int *mul, int *divi, int *square)
		{
		    *add = a+b ;
		    *sub = a-b ;
		    *mul = a*b ;
		    *divi = a/b ;
		    *square =a^b;
		}
		void reset_handler(void)
		{
		    int add, sub, mul, divi, square ;
		    singleparameter(1);
		    multieparameter(1, 2, 3, 4, 5, 6);
		    manyreturn(1, 2, &add, &sub, &mul, &divi, &square);
		    while (1)
				;
		}

objdump result

		Disassembly of section .mytext:

		00000000 <singleparameter-0x8>:
		   0:	20000100 	andcs	r0, r0, r0, lsl #2
		   4:	000000a5 	andeq	r0, r0, r5, lsr #1

		00000008 <singleparameter>:
		   8:	b480      	push	{r7}
		   a:	b083      	sub	sp, #12
		   c:	af00      	add	r7, sp, #0
		   e:	6078      	str	r0, [r7, #4]
		  10:	687a      	ldr	r2, [r7, #4]
		  12:	687b      	ldr	r3, [r7, #4]
		  14:	4413      	add	r3, r2
		  16:	4618      	mov	r0, r3
		  18:	370c      	adds	r7, #12
		  1a:	46bd      	mov	sp, r7
		  1c:	f85d 7b04 	ldr.w	r7, [sp], #4
		  20:	4770      	bx	lr
		  22:	bf00      	nop

		00000024 <multieparameter>:
		  24:	b480      	push	{r7}
		  26:	b085      	sub	sp, #20
		  28:	af00      	add	r7, sp, #0
		  2a:	60f8      	str	r0, [r7, #12]
		  2c:	60b9      	str	r1, [r7, #8]
		  2e:	607a      	str	r2, [r7, #4]
		  30:	603b      	str	r3, [r7, #0]
		  32:	68fa      	ldr	r2, [r7, #12]
		  34:	68bb      	ldr	r3, [r7, #8]
		  36:	441a      	add	r2, r3
		  38:	687b      	ldr	r3, [r7, #4]
		  3a:	441a      	add	r2, r3
		  3c:	683b      	ldr	r3, [r7, #0]
		  3e:	441a      	add	r2, r3
		  40:	69bb      	ldr	r3, [r7, #24]
		  42:	441a      	add	r2, r3
		  44:	69fb      	ldr	r3, [r7, #28]
		  46:	4413      	add	r3, r2
		  48:	4618      	mov	r0, r3
		  4a:	3714      	adds	r7, #20
		  4c:	46bd      	mov	sp, r7
		  4e:	f85d 7b04 	ldr.w	r7, [sp], #4
		  52:	4770      	bx	lr

		00000054 <manyreturn>:
		  54:	b480      	push	{r7}
		  56:	b085      	sub	sp, #20
		  58:	af00      	add	r7, sp, #0
		  5a:	60f8      	str	r0, [r7, #12]
		  5c:	60b9      	str	r1, [r7, #8]
		  5e:	607a      	str	r2, [r7, #4]
		  60:	603b      	str	r3, [r7, #0]
		  62:	68fa      	ldr	r2, [r7, #12]
		  64:	68bb      	ldr	r3, [r7, #8]
		  66:	441a      	add	r2, r3
		  68:	687b      	ldr	r3, [r7, #4]
		  6a:	601a      	str	r2, [r3, #0]
		  6c:	68fa      	ldr	r2, [r7, #12]
		  6e:	68bb      	ldr	r3, [r7, #8]
		  70:	1ad2      	subs	r2, r2, r3
		  72:	683b      	ldr	r3, [r7, #0]
		  74:	601a      	str	r2, [r3, #0]
		  76:	68fb      	ldr	r3, [r7, #12]
		  78:	68ba      	ldr	r2, [r7, #8]
		  7a:	fb02 f203 	mul.w	r2, r2, r3
		  7e:	69bb      	ldr	r3, [r7, #24]
		  80:	601a      	str	r2, [r3, #0]
		  82:	68fa      	ldr	r2, [r7, #12]
		  84:	68bb      	ldr	r3, [r7, #8]
		  86:	fb92 f2f3 	sdiv	r2, r2, r3
		  8a:	69fb      	ldr	r3, [r7, #28]
		  8c:	601a      	str	r2, [r3, #0]
		  8e:	68fa      	ldr	r2, [r7, #12]
		  90:	68bb      	ldr	r3, [r7, #8]
		  92:	405a      	eors	r2, r3
		  94:	6a3b      	ldr	r3, [r7, #32]
		  96:	601a      	str	r2, [r3, #0]
		  98:	3714      	adds	r7, #20
		  9a:	46bd      	mov	sp, r7
		  9c:	f85d 7b04 	ldr.w	r7, [sp], #4
		  a0:	4770      	bx	lr
		  a2:	bf00      	nop

		000000a4 <reset_handler>:
		  a4:	b590      	push	{r4, r7, lr}
		  a6:	b08b      	sub	sp, #44	; 0x2c
		  a8:	af04      	add	r7, sp, #16
		  aa:	2001      	movs	r0, #1
		  ac:	f7ff ffac 	bl	8 <singleparameter>
		  b0:	2305      	movs	r3, #5
		  b2:	9300      	str	r3, [sp, #0]
		  b4:	2306      	movs	r3, #6
		  b6:	9301      	str	r3, [sp, #4]
		  b8:	2001      	movs	r0, #1
		  ba:	2102      	movs	r1, #2
		  bc:	2203      	movs	r2, #3
		  be:	2304      	movs	r3, #4
		  c0:	f7ff ffb0 	bl	24 <multieparameter>
		  c4:	f107 0214 	add.w	r2, r7, #20
		  c8:	f107 0410 	add.w	r4, r7, #16
		  cc:	f107 030c 	add.w	r3, r7, #12
		  d0:	9300      	str	r3, [sp, #0]
		  d2:	f107 0308 	add.w	r3, r7, #8
		  d6:	9301      	str	r3, [sp, #4]
		  d8:	1d3b      	adds	r3, r7, #4
		  da:	9302      	str	r3, [sp, #8]
		  dc:	2001      	movs	r0, #1
		  de:	2102      	movs	r1, #2
		  e0:	4623      	mov	r3, r4
		  e2:	f7ff ffb7 	bl	54 <manyreturn>
		  e6:	e7fe      	b.n	e6 <reset_handler+0x42>

		Disassembly of section .comment:

		00000000 <.comment>:
		   0:	3a434347 	bcc	10d0d24 <reset_handler+0x10d0c80>
		   4:	35312820 	ldrcc	r2, [r1, #-2080]!	; 0xfffff7e0
		   8:	392e343a 	stmdbcc	lr!, {r1, r3, r4, r5, sl, ip, sp}
		   c:	732b332e 			; <UNDEFINED> instruction: 0x732b332e
		  10:	33326e76 	teqcc	r2, #1888	; 0x760
		  14:	37373131 			; <UNDEFINED> instruction: 0x37373131
		  18:	2029312d 	eorcs	r3, r9, sp, lsr #2
		  1c:	2e392e34 	mrccs	14, 1, r2, cr9, cr4, {1}
		  20:	30322033 	eorscc	r2, r2, r3, lsr r0
		  24:	35303531 	ldrcc	r3, [r0, #-1329]!	; 0xfffffacf
		  28:	28203932 	stmdacs	r0!, {r1, r4, r5, r8, fp, ip, sp}
		  2c:	72657270 	rsbvc	r7, r5, #112, 4
		  30:	61656c65 	cmnvs	r5, r5, ror #24
		  34:	00296573 	eoreq	r6, r9, r3, ror r5

		Disassembly of section .ARM.attributes:

		00000000 <.ARM.attributes>:
		   0:	00003041 	andeq	r3, r0, r1, asr #32
		   4:	61656100 	cmnvs	r5, r0, lsl #2
		   8:	01006962 	tsteq	r0, r2, ror #18
		   c:	00000026 	andeq	r0, r0, r6, lsr #32
		  10:	726f4305 	rsbvc	r4, pc, #335544320	; 0x14000000
		  14:	2d786574 	cfldr64cs	mvdx6, [r8, #-464]!	; 0xfffffe30
		  18:	0600344d 	streq	r3, [r0], -sp, asr #8
		  1c:	094d070d 	stmdbeq	sp, {r0, r2, r3, r8, r9, sl}^
		  20:	14041202 	strne	r1, [r4], #-514	; 0xfffffdfe
		  24:	17011501 	strne	r1, [r1, -r1, lsl #10]
		  28:	1a011803 	bne	4603c <reset_handler+0x45f98>
		  2c:	22061e01 	andcs	r1, r6, #1, 28
		  30:	Address 0x0000000000000030 is out of bounds.

在ARM架構下，當引數超過4個時，就必須用stack來進行傳遞，從manyreturn的組合語言中可以觀察到多的參數會先被存放到sp的暫存器中
