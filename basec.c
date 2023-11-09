#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basec.h"


#ifndef TEST
int main(int argc, char *argv[]) {
    char *value;
    char base;     /* Base of the argument (d, b, o, h, a)*/
    struct values *values;

    if (argc < 2 || argc > 3) {
        printf("Error: invalid arguments. Use --help for usage info.\n");
        return 1;
    } else if (argc == 2 && (!strcmp(argv[1], "--help") ||
                             !strcmp(argv[1], "--info") ||
                             !strcmp(argv[1], "--usage"))) {
        showUsage();
        return 1;
    } else if (argc == 3){
        value = argv[2];
        base  = argv[1][1];
        if (base == 'd' || base == 'b' || base == 'o' || base == 'h' ||
            base == 'a') {
            values = convertValue(value, base);
            if (values) {
                printValues(values);
            } else {
                return 1;
            }
        } else {
            printf("Error: invalid base. Use --help for usage info.\n");
            return 1;
        }
    } else {
        printf("Error: invalid arguments. Use --help for usage info.\n");
        return 1;
    }

    return 0;
}
#endif /* TEST */

void showUsage() {
        printf("USAGE:\n");
        printf("  basec -[base] <value>\n");
        printf("\n");
        printf("OPTIONS:\n");
        printf("  base:\n");
        printf("  -d       for decimal\n");
        printf("  -b       for binary\n");
        printf("  -o       for octal\n");
        printf("  -h       for hexadecimal\n");
        printf("  -a       for ascii\n");
        printf("\n");
        printf("  --usage  (show this page)\n");
        printf("  --info   (show this page)\n");
        printf("  --help   (show tihs page)\n");
        printf("\n");
        printf("EXAMPLES:\n");
        printf("  basec -d 100\n");
        printf("  basec -b 10001000\n");
        printf("  basec -o 644\n");
        printf("  basec -h 106FA00B\n");
        printf("  basec -a text\n");
}

struct values *convertValue(char *value, char base) {
    struct values *values = (struct values *) malloc(sizeof(struct values));

    /* First convert to decimal then convert to other bases */
    if (!toDecimal(value, base, &(values->decimal)) &&
        !convertAlgorithm(values->decimal, 2, values->binary, MAX_DIGIT_BIN) &&
        !convertAlgorithm(values->decimal, 8, values->octal, MAX_DIGIT_OCT) &&
        !convertAlgorithm(values->decimal, 16, values->hexadecimal,
                         MAX_DIGIT_HEX)) {
        /* Convert to ascii */
        if (values->decimal >= 0 && values->decimal <= 255) {
            values->ascii = (char) values->decimal;
        } else {
            values->ascii = -1;
        }
    } else {
        free(values);
        return NULL;
    }

    return values;
}

int toDecimal(char *value, char base, long int *returnValue) {
    char *endptr;

    if (returnValue == NULL) {
        return -1;
    }
    endptr = NULL; /* For strtol */

    switch (base) {
        case 'd':
            *returnValue = strtol(value, &endptr, 10);
            break;
        case 'b':
            *returnValue = strtol(value, &endptr, 2);
            break;
        case 'o':
            *returnValue = strtol(value, &endptr, 8);
            break;
        case 'h':
            *returnValue = strtol(value, &endptr, 16);
            break;
        case 'a':
            *returnValue = (int) value[0];
    }

    if (base == 'a') {
        if (strlen(value) > 1) {
            printf("Error: Ascii value must be a single character.\n");
            return -1;
        } else {
            return 0;
        }
    } else if (*endptr == '\0') {
        /* Correct conversion */
        return 0;
    } else {
        printf("Error: Cannot convert %s from %c base.\n", value, base);
        return -1;
    }
}

int convertAlgorithm(long int value, int base, char* returnValue, int size) {
    int    res;
    int    index = 0;

    while (value > 0) {
        res = value % base;
        /* Decimal digit */
        if (res < 10) {
            returnValue[index] = res + '0';
        /* More than base 10 (A, B, C, etc.) */
        } else {
            returnValue[index] = res - 10 + 'A';
        }
        index++;
        value = value / base;
        if (index > size) {
            printf("Error: Overflow converting %ld to base %c\n", value, base);
            return -1;
        }
    }

    if (index == 0) {
        returnValue[0] = '0';
        index ++;
    }

    /* Put the termination char in the result */
    returnValue[index] = '\0';
    /* Reverse the array */
    if (reverseCharArray(returnValue, index)) {
        printf("Error: Cannot reverse the array\n");
        return -1;
    }

    return 0;
}

int printValues(struct values *values) {
    int asciiPrintable;
    char asciiSymbol[4]; /* Used for non-printable chars */

    asciiPrintable = 1;
    /* Check if the ASCII value is printable */
    if (values->decimal < 32 || values->decimal == 127) {
        asciiPrintable = 0;
        switch (values->decimal) {
            case 0:
                strcpy(asciiSymbol, "NUL");
                break;
            case 1:
                strcpy(asciiSymbol, "SOH");
                break;
            case 2:
                strcpy(asciiSymbol, "STX");
                break;
            case 3:
                strcpy(asciiSymbol, "ETX");
                break;
            case 4:
                strcpy(asciiSymbol, "EOT");
                break;
            case 5:
                strcpy(asciiSymbol, "ENQ");
                break;
            case 6:
                strcpy(asciiSymbol, "ACK");
                break;
            case 7:
                strcpy(asciiSymbol, "BEL");
                break;
            case 8:
                strcpy(asciiSymbol, "BS ");
                break;
            case 9:
                strcpy(asciiSymbol, "HT ");
                break;
            case 10:
                strcpy(asciiSymbol, "LF ");
                break;
            case 11:
                strcpy(asciiSymbol, "VT ");
                break;
            case 12:
                strcpy(asciiSymbol, "FF ");
                break;
            case 13:
                strcpy(asciiSymbol, "CR ");
                break;
            case 14:
                strcpy(asciiSymbol, "SO ");
                break;
            case 15:
                strcpy(asciiSymbol, "SI ");
                break;
            case 16:
                strcpy(asciiSymbol, "DLE");
                break;
            case 17:
                strcpy(asciiSymbol, "DC1");
                break;
            case 18:
                strcpy(asciiSymbol, "DC2");
                break;
            case 19:
                strcpy(asciiSymbol, "DC3");
                break;
            case 20:
                strcpy(asciiSymbol, "DC4");
                break;
            case 21:
                strcpy(asciiSymbol, "NAK");
                break;
            case 22:
                strcpy(asciiSymbol, "SYN");
                break;
            case 23:
                strcpy(asciiSymbol, "ETB");
                break;
            case 24:
                strcpy(asciiSymbol, "CAN");
                break;
            case 25:
                strcpy(asciiSymbol, "EM ");
                break;
            case 26:
                strcpy(asciiSymbol, "SUB");
                break;
            case 27:
                strcpy(asciiSymbol, "ESC");
                break;
            case 28:
                strcpy(asciiSymbol, "FS ");
                break;
            case 29:
                strcpy(asciiSymbol, "GS ");
                break;
            case 30:
                strcpy(asciiSymbol, "RS ");
                break;
            case 31:
                strcpy(asciiSymbol, "US ");
                break;
            case 127:
                strcpy(asciiSymbol, "DEL");
        }
    }

    if (asciiPrintable) {
        printf("D:%ld, B:%s, O:%s, H:%s, A:%c\n",
            values->decimal,
            values->binary,
            values->octal,
            values->hexadecimal,
            values->ascii);

    } else {
        printf("D:%ld, B:%s, O:%s, H:%s, A:%s\n",
            values->decimal,
            values->binary,
            values->octal,
            values->hexadecimal,
            asciiSymbol);

    }

    return 0;
}

int reverseCharArray(char *array, int arraySize) {
    int  index;
    int  start;
    int  end;
    char readed;

    if (array == NULL || arraySize <= 0) {
        return -1;
    }

    /* Search the end of the array content */
    /* The index variable will point to the end */
    index = 0;
    readed = array[index];
    while (readed != '\0') {
        readed = array[index];
        index++;
    }
    index--;

    if (index > arraySize) {
        return -1;
    }

    /* Reverse the array */
    start = 0;
    end   = index - 1;
    while (start < end) {
        readed       = array[start];
        array[start] = array[end];
        array[end]   = readed;
        start++;
        end--;
    }

    return 0;
}
