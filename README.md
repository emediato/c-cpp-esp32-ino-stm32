# :) 

## stm32

https://www.st.com/en/development-tools/stm32cubemx.html
https://www.st.com/en/development-tools/stm32cubemx.html#get-software
http://stackoverflow.com/questions/8632586/macos-whats-the-difference-between-dev-tty-and-dev-cu

For terminal apps on Mac, visit to these links.
http://pbxbook.com/other/mac-tty.html

http://pbxbook.com/other/mac-ser.html



## CH340 DRIVER for MAC OS
https://www.wch-ic.com/downloads/CH34XSER_MAC_ZIP.html

https://github.com/LilyGO/LILYGO-T-OI/issues/3#issuecomment-907645945



## Useful

https://www.youtube.com/@PhilsLab

https://www.pcb-hero.com/blogs/lickys-column/rfid-and-keypad-based-door-lock-using-arduino?utm_source=licky&utm_medium=Linkedin&utm_campaign=post20231002135816&utm_content=23100213native_image


## Volatile Keyword in C.
####  In C, the volatile keyword is a qualifier that can be applied to a variable declaration. 
####  When a variable is declared as volatile, it indicates to the compiler that the variable’s value may change at any time without any action being taken by the code the compiler finds nearby.
#### volatile int counter;
 
Here are some common scenarios where you might use volatile:

##### 1.Hardware Interfacing:

·      When you interface with hardware that changes the value itself (e.g., memory-mapped devices), using volatile ensures that the compiler doesn’t optimize away memory assignments or reorder them incorrectly.
·      For example, if you’re working with a hardware gadget that has command and data ports, declaring the pointer to the gadget as volatile ensures correct order of assignments and prevents optimization issues.

##### 2.Multithreading and Signal Handlers:

·      When there’s another thread running that also uses the variable or when a signal handler might change its value, marking the variable as volatile ensures that the compiler doesn’t optimize away memory accesses or cache variables in registers.

##### 3.Reading a Hardware Register

·      Imagine you’re working on a microcontroller-based project, and you need to read data from a hardware register. 
·      These registers often represent various device settings, status flags, or sensor data. Here’s how you might use volatile

LED Status Register:

·      Suppose you have an LED connected to a GPIO pin. The LED’s state (on/off) is controlled by a hardware register.
·      You declare a pointer to the register as volatile to ensure that the compiler doesn’t optimize away reads or writes to this memory location.

Eg:
// Assume the LED status register is at address 0x1234
volatile uint32_t* ledStatusReg = (volatile uint32_t*)0x1234;
 
// Read LED status
uint32_t ledState = *ledStatusReg;
if (ledState) {
 // LED is on
 // ...
} else {
 // LED is off
 // ...
 
