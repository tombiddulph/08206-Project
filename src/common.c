#include "Commonheader.h"

void str_cpy(char *original, char *added) {
    while (*original++ = *added++);
    }

void concat_strings(char *original, char *added) {
    while (*original) {
        original++;
    }

    while (*added) {
        *original = *added;
        added++;
        original++;
    }
    *original = '\0';
}

void int_to_string(char str[], unsigned char num) {
    int i, rem, len = 0, n;

    n = num;
    while (n != 0) {
        len++;
        n /= 10;
    }
    for (i = 0; i < len; i++) {
        rem = num % 10;
        num = num / 10;
        str[len - (i + 1)] = rem + '0';
    }
    str[len] = '\0';
}

void Delay_loop(unsigned long j) {
    for (unsigned long i = j; i > 0; --i);
}

unsigned char convert_from_bit_pos(unsigned char bitPos) {
    char val = 0;
    while (bitPos >>= 1) {
        ++val;
    }
    return val;
}

void ClearButtons() {
    TRISB0 = 0;
    TRISB1 = 0;
    TRISB2 = 0;
    TRISB3 = 0;
    TRISE0 = 0;
    TRISE1 = 0;
    TRISE2 = 0;
    PORTB = PORTB & 0xF0;
    PORTE = PORTE & 0xF8;
    TRISB0 = 1;
    TRISB1 = 1;
    TRISB2 = 1;
    TRISB3 = 1;
    TRISE0 = 1;
    TRISE1 = 1;
    TRISE2 = 1;
}

unsigned char convert_to_bit_pos(unsigned char pinNum) {
    return (1 << pinNum);
}

bool single_key_pressed(char byteVal) {
    return byteVal && !(byteVal & (byteVal - 1));
}

DateTime *convertDateFromArray(unsigned char input[]) {
    char *ptr = input;
    DateTime d;
    d.Day = *ptr++;
    d.Month = *ptr++;
    d.Year = *ptr++;
    d.Hour = *ptr++;
    d.Minute = *ptr++;
    d.Second = *ptr;
    return &d;
}

void ButtonInit() {
    TRISB = 0x0F;
    PORTB = 0x00;

    TRISE0 = 1;
    TRISE1 = 1;
    TRISE2 = 1;
    RE0 = RE1 = RE2 = 0;

}

unsigned char bcd_to_decimal(unsigned char val) {
    return ((val & 0x0F) + (((val & 0xF0) >> 4) * 10));
}

unsigned char decimal_to_bcd(unsigned char val) {
    return (((val / 10) << 4) & 0xF0) | ((val % 10) & 0x0F);
}