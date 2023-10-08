// 1.1 ���������� ��� - �� ��������� ��� � ������� �����, ������� �� ������ ��������.������� ����� ���������� � 0.
// 1.2 ������� �������� ���� � ����� N �� ��� ������ K. ������ ������� ������.����� N, ����� ���� K
// 1.3 ���� � ����� ���������� ������ ���� ��� �� ��������� 1, �������� � �������� ����� OK. ����� �������� FAIL 
// 1.4 ������������ �������� ���� � ����� N �� ��� ������ K. ������ ������� ������.����� N, ����� ���� K. ������ �������� ������.����� � ��������������� ����� � ���������� ����.

#include <iostream>

// 1.1
unsigned short count_units(unsigned int number) {
    unsigned short counter = 0;
    unsigned short pos = 0;
    while (number > 0) {
        if (pos % 2 == 0) counter += number & 0b1;
        number >>= 1;
        pos++;
    }
    return counter;
}

// 1.2
unsigned short get_bit_value(unsigned int number, unsigned short bit) {
    while (bit > 0) {
        number >>= 1;
        bit--;
    }
    return number & 0b1;
}

// 1.3
std::string is_only_one_unit(unsigned int number) {
    unsigned short counter = 0;
    while (number > 0) {
        if (number & 0b1) counter++;
        number >>= 1;
    }
    return counter == 1 ? "OK" : "FAIL";
}

// 1.4
unsigned int invert_bit(unsigned int number, unsigned short bit) {
    return number ^ (1 << bit);
}

int main() {
    // 1.1
    //unsigned int number;
    //std::cin >> number;
    //std::cout << count_units(number) << std::endl;

    // 1.2
    //unsigned int number;
    //unsigned short bit;
    //std::cin >> number >> bit;
    //std::cout << get_bit_value(number, bit) << std::endl;

    // 1.3
    //unsigned int number;
    //std::cin >> number;
    //std::cout << is_only_one_unit(number) << std::endl;

    // 1.4
    unsigned int number;
    unsigned short bit;
    std::cin >> number >> bit;
    std::cout << invert_bit(number, bit) << std::endl;

    return 0;
}