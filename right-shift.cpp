/*
Shift Right Logical (SRL):

In a logical right shift operation, the bits are shifted to the right by a certain number of positions, and the leftmost bit is always filled with a zero.
This operation is typically used when you want to divide an unsigned integer by a power of two.
In languages like C and C++, the right shift operator (>>) performs a logical right shift on unsigned integers.
Shift Right Arithmetic (SRA):

In an arithmetic right shift operation, the bits are shifted to the right by a certain number of positions, and the leftmost bit (sign bit) is replicated to fill the vacant positions.
This operation preserves the sign of signed integers (positive or negative).
Arithmetic right shift is used when you want to perform division or division-related operations on signed integers, ensuring that the sign of the result is maintained.
Languages like C and C++ perform arithmetic right shift (>>) on signed integers.
Here's a simple example to illustrate the difference:
*/

#include <iostream>

int main() {
    // Logical Right Shift
    unsigned int logical_num = 8; // 1000
    unsigned int logical_result = logical_num >> 1; // Shift right by 1 position
    std::cout << "Logical right shift result: " << logical_result << std::endl; // Output: 4 (0100)

    // Arithmetic Right Shift
    int arithmetic_num = -8; // 11111111111111111111111111111000 (assuming 32-bit)
    int arithmetic_result = arithmetic_num >> 1; // Shift right by 1 position
    std::cout << "Arithmetic right shift result: " << arithmetic_result << std::endl; // Output: -4 (11111111111111111111111111111100)

    return 0;
}
