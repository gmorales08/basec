#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TEST
#include "../basec.c"

int main() {
    /*long int decimalExpected;*/
    /*char     binaryExpected[MAX_DIGIT_BIN + 1];*/
    /*char     octalExpected[MAX_DIGIT_OCT + 1];*/
    /*char     hexadecimalExpected[MAX_DIGIT_HEX + 1];*/
    /*char     asciiExpected;*/
    int ok;
    int pass;
    int fail;
    struct values *values;

    pass = 0;
    fail = 0;

    printf("=====TESTING CONVERSIONS=====\n");
    /* From decimal */
    values = convertValue("10", 'd');
    printf("Decimal 10 to all bases:\n");
    printf("  To binary: %s ", values->binary);
    ok = strncmp(values->binary, "1010", MAX_DIGIT_BIN + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To octal: %s ", values->octal);
    ok = strncmp(values->octal, "12", MAX_DIGIT_OCT + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To hexadecimal: %s ", values->hexadecimal);
    ok = strncmp(values->hexadecimal, "A", MAX_DIGIT_HEX + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    ok = !(values->ascii == 10);
    printf("  To ascii: %d ", values->ascii);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    free(values);

    /* From binary */
    values = convertValue("1010", 'b');
    printf("Binary 1010 to all bases:\n");
    printf("  To decimal: %ld ", values->decimal);
    ok = (values->decimal == 10);
    if (ok == 1) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To octal: %s ", values->octal);
    ok = strncmp(values->octal, "12", MAX_DIGIT_OCT + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To hexadecimal: %s ", values->hexadecimal);
    ok = strncmp(values->hexadecimal, "A", MAX_DIGIT_HEX + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    ok = !(values->ascii == 10);
    printf("  To ascii: %d ", values->ascii);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    free(values);

    /* From octal */
    values = convertValue("12", 'o');
    printf("Octal 12 to all bases:\n");
    printf("  To decimal: %ld ", values->decimal);
    ok = (values->decimal == 10);
    if (ok == 1) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To binary: %s ", values->binary);
    ok = strncmp(values->binary, "1010", MAX_DIGIT_BIN + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To hexadecimal: %s ", values->hexadecimal);
    ok = strncmp(values->hexadecimal, "A", MAX_DIGIT_HEX + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    ok = !(values->ascii == 10);
    printf("  To ascii: %d ", values->ascii);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    free(values);

    /* From hexadecimal */
    values = convertValue("A", 'h');
    printf("Hexadecimal A to all bases:\n");
    printf("  To decimal: %ld ", values->decimal);
    ok = (values->decimal == 10);
    if (ok == 1) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To binary: %s ", values->binary);
    ok = strncmp(values->binary, "1010", MAX_DIGIT_BIN + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To octal: %s ", values->octal);
    ok = strncmp(values->octal, "12", MAX_DIGIT_OCT + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    ok = !(values->ascii == 10);
    printf("  To ascii: %d ", values->ascii);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    free(values);

    /* From ascii */
    values = convertValue("a", 'a');
    printf("ASCII 10 to all bases:\n");
    printf("  To decimal: %ld ", values->decimal);
    ok = (values->decimal == 97);
    if (ok == 1) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To binary: %s ", values->binary);
    ok = strncmp(values->binary, "1100001", MAX_DIGIT_BIN + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To octal: %s ", values->octal);
    ok = strncmp(values->octal, "141", MAX_DIGIT_OCT + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    printf("  To hexadecimal: %s ", values->hexadecimal);
    ok = strncmp(values->hexadecimal, "61", MAX_DIGIT_HEX + 1);
    if (ok == 0) {
        printf("[OK]\n");
        pass++;
    } else {
        printf("[FAIL]\n");
        fail++;
    }
    free(values);

    return 0;
}
