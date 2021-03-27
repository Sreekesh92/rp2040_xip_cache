This is an example program to demonstrate the effect of XIP Cache on program performance of Raspberry Pi Pico (rp2040) microcontroller.

The RP2040 Microcontroller does not contain an in-built Flash memory for storing usercode. It only has a mask-programmed ROM 
(fixed during production) which contains the ROM bootloader. The usercode is stored in an external QSPI NOR Flash memory.
The ROM Bootloader and the second stage bootloader sets up the interface to access the QSPI Flash, and the XIP(eXecute In Place)
hardware. Once the XIP hardware is setup correctly, the usercode can execute directly from external QSPI NOR Flash.

The QSPI NOR Flash interface is slow compared to the CPU clock speed. The XIP hardware has a small amount of SRAM which caches
the access to Flash, and thus speeds up the program execution. If this cache memory of XIP is turned-off or bypassed, the 
program execution slows down.

A Flash memory of maximum 16 MB (requires 24-bit addess lines) is supported by the XIP hardware.
The XIP hardware maps the Flash memory into the following address ranges :

• 0x10... XIP access, cacheable, allocating - Normal cache operation
• 0x11... XIP access, cacheable, non-allocating - Check for hit, don’t update cache on miss
• 0x12... XIP access, non-cacheable, allocating - Don’t check for hit, always update cache
• 0x13... XIP access, non-cacheable, non-allocating - Bypass cache completely
• 0x15... Use XIP cache as SRAM bank, mirrored across entire segment
(Refer Section 2.6.3.1 of RP2040 Datasheet)

Assume a function 'foo()' in usercode(residing in Flash), which is mapped at location 0x1000_abcd (this address belongs to 
"Normal Cache Operation" range of the address map exposed by XIP hardware) by the XIP hardware. If 'foo()' is invoked using this 
address (for instance, using an assembly language instruction CALL 0x1000_abcd), the cache memory of XIP hardware is made use of.

The same function 'foo()' can be accessed from the address 0x1300_abcd (this adress belongs to "Bypass cache" range of the the
address map exposed by XIP hardware). If 'foo()' is invoked using this address (for instance, using an assembly language instruction
 CALL 0x1300_abcd), the cache memory of XIP hardware is bypassed, and the program runs slower.

This program has a function that blinks an LED (by turning on/off a GPIO), and uses a long-running loop to create the delay.
This function is called from its two address aliases - one for normal cache operation, and other for bypassing cache.

Run the program by yourself and see how much effect the cache has on program performance !

How to compile ?
1. Install the pico-sdk repo (Refer : https://github.com/raspberrypi/pico-sdk)

2. Clone this repo. Create a build directory inside this repo
	mkdir build
	cd build

3. Run cmake from build/ directory to generate makefiles :
	cmake ../

4. Run make to generate binary :
	make

5. Copy the blinky.uf2 firmware file created in build/ after step-4, into raspberry-pi pico which appears as a USB storage device.
   (Press the BOOTSEL button before plugging in pico pi into USB port)

6. Modify the program to run the blink function bypassing Cache, and see if LED is blinking slower.
