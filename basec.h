#ifndef BASEC
#define BASEC

/* Max size of the value digits. Used for screen adjustments */
#define MAX_DIGIT_BIN 32
#define MAX_DIGIT_OCT 32 / 3 + 1
#define MAX_DIGIT_HEX 32 / 4 + 1

/* Struct that contains the value in all bases */
struct values {
    long int  decimal;
    char      binary[MAX_DIGIT_BIN + 1];
    char      octal[MAX_DIGIT_OCT + 1];
    char      hexadecimal[MAX_DIGIT_HEX + 1];
    char      ascii;
};

/* Prints usage information */
void showUsage();

/* Convert the value provided by argument to all the bases */
/* Returns the pointer of the values struct created */
struct values *convertValue(char *value, char base);

/** TO_DECIMAL
 *
 * Converts to decimal the value passed by parameter
 * The return value will be stored in a variable passed by parameter
 *
 * Parameters:
 *   char *value : The origin value
 *   char base   : The base of the origin value
 *   long int *  : Pointer that will store the return value
 */
int toDecimal(char *value, char base, long int *returnValue);

/** CONVERT_ALGORITHM
 *
 * Convert a decimal value to another base.
 * Stores the result in the array passed by parameter.
 * Must indicate the size of the array.
 *
 * Parameters:
 *   long int value       : The origin value
 *   int      base        : The base of the origin value
 *   char     *returnValue: The char where the result will be stored
 *   int      size        : The size of the returnValue array
 */
int convertAlgorithm(long int value, int base, char* returnValue, int size);

/* Print the values on the screen */
/* Check if the ASCII value is printable */
int printValues(struct values *values);

/* Reverts the array content. Only for char arrays */
int reverseCharArray(char *array, int arraySize);

#endif /* ifndef BASEC */
