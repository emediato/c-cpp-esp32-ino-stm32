#include <stdio.h>


/*
ADDRESS - DESCRIPTION - ACRONYM

0x0000 0000
0x0000 0004 - RESET
0x0000 0008 - NON MASKABLE INTERRUPT. The RCC clock security system is linked to the NMI vector - NMI
0x0000 000C - all clas of fault - HardFault
0x0000 0010 - memory management - MemManage
0x0000 0014 - pre-fetch fault, memory access fault - BusFault
0x0000 0018 - undefined function or illegal state - UsageFAULT
0x0000 001C - reserved
0x0000 002C - system service call via SWI instruction - SVCall
0x0000 0030 - debug monitor
0x0000 0034 - reserved
0x0000 0038 - pendable request for system service - pendSV
0x0000 003C - system tick timer - systick

*/
int main() {
    int a, b, x, y, z, *p1, **p2;
    a=12;
    b=4;
    p1=&a;
    p2=&b; 
    x=*p1 * *p2 -6;
    y=4 - *p2 +10;

    printf("address of a = %u \n", &p1);
    printf("address of b = %u \n", &p2);
    printf("\n  a = %d \n", a);
    printf("\n b = %d \n", b);
    printf("\n b = %d \n", b);

    
}
