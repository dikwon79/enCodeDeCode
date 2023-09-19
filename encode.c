#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

struct Number{
    int ones;
    int tens;
    int hundreds;
    int thousands;
    int tenthousands;
    int hundredthousands;
    int millions;
    int tenmillions;
    int hundredmillions;
    int billions;
};

void printLabel(int i){
    char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    printf("%s ", ones[i]);
}


void tentoone(int m, int n){
    char *teens[] = {"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    // Handle tens and ones
    if (m == 1) {
        printf("%s ", teens[n]);
    } else {
        if (m > 1) {
            printf("%s ", tens[m]);
        }
        printLabel(n);
    }
}
void intTowords(int32_t num) {
    char *teens[] = {"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen",
                     "nineteen"};
    char *tens[] = {"", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};


    int32_t result = 0;
    struct Number digits;
    digits.ones = digits.tens = digits.hundreds = digits.thousands = digits.millions = 0;

    int iteration = 0;
    int32_t digit = 0;
    while (num != 0) {
        digit = num % 10;
        num /= 10;

        switch (iteration) {
            case 0:
                digits.ones = digit;
                break;
            case 1:
                digits.tens = digit;
                break;
            case 2:
                digits.hundreds = digit;
                break;
            case 3:
                digits.thousands = digit;
                break;
            case 4:
                digits.tenthousands = digit;
                break;
            case 5:
                digits.hundredthousands = digit;
                break;
            case 6:
                digits.millions = digit;
                break;
            case 7:
                digits.tenmillions = digit;
                break;
            case 8:
                digits.hundredmillions = digit;
                break;
            case 9:
                digits.billions = digit;
                break;
        }

        iteration++;

    }


    if (digits.billions > 0) {
        printLabel(digits.billions);
        printf("billion ");
    }
    if (digits.hundredmillions > 0) {
        printLabel(digits.hundredmillions);
        printf("hundred ");
    }
    if (digits.tenmillions > 0) {
        tentoone(digits.tenmillions, digits.millions);
        printf("million ");
    }
    if (digits.tenmillions == 0 && digits.millions > 0) {

        printLabel(digits.millions);
        printf("million ");
    }
    if (digits.hundredthousands > 0) {
        printLabel(digits.hundredthousands);
        printf("hundred ");
    }
    if (digits.tenthousands > 0) {
        tentoone(digits.tenthousands, digits.thousands);
        printf("thousand ");
    }
    if (digits.tenthousands == 0 && digits.thousands > 0) {

        printLabel(digits.thousands);
        printf("thousand ");
    }
    if (digits.hundreds > 0) {
        printLabel(digits.hundreds);
        printf("hundred ");
    }
    // Handle tens and ones
    tentoone(digits.tens, digits.ones);
    printf("\n");
}
int main(int argc, char* argv[]){

    if (argc != 2){
        fputs("error! input number\n", stderr);
	exit(1);
    }

    intTowords(atoi(argv[1]));

    return 0;
}
