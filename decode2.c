#include <stdio.h>
#include <stdint.h>
#include <string.h>

struct Number {
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

// Function to convert words to int32_t
int32_t wordsToInt(char *words) {
    // Define arrays for mapping words to digits (ones, teens, tens)
    char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *teens[] = {"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tens[] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    struct Number decoded;
    decoded.billions = decoded.hundredmillions = decoded.tenmillions = decoded.millions= 0;
    decoded.thousands = decoded.hundredthousands = decoded.tenthousands = decoded.hundreds = decoded.tens = decoded.ones = 0;

    char *token;
    token = strtok(words, " \n");

    while (token != NULL) {
        if (strcmp(token,"billion") == 0) {
            decoded.billions = decoded.ones;
        } else if (strcmp(token, "million") == 0) {
            decoded.hundredmillions =decoded.hundreds;
            decoded.tenmillions = decoded.tens;
            decoded.millions = decoded.ones;

            decoded.hundreds = 0;
            decoded.tens = 0;
            decoded.ones = 0;

        } else if (strcmp(token, "thousand") == 0) {
            decoded.hundredthousands = decoded.hundreds;
            decoded.tenthousands = decoded.tens;
            decoded.thousands = decoded.ones;

            decoded.hundreds = 0;
            decoded.tens = 0;
            decoded.ones = 0;

        } else if (strcmp(token, "hundred") == 0) {
            decoded.hundreds = decoded.ones;
            decoded.ones = 0;
        } else {
            int i;
            for (i = 0; i < 10; i++) {
                if (strcmp(token, ones[i]) == 0) {
                    decoded.ones = i;
                    break;
                }
            }
            if (i == 10) {
                for (i = 1; i < 10; i++) {
                    if (strcmp(token, tens[i]) == 0) {
                        decoded.tens = i;
                        break;
                    }
                }
                if (i == 10) {
                    for (i = 1; i < 10; i++) {
                        if (strcmp(token, teens[i]) == 0) {
                            decoded.tens = 1;  // Handle teens
                            decoded.ones = i;
                            break;
                        }
                    }
                }
            }
        }

        token = strtok(NULL, " \n");
    }

    // Calculate the integer value based on the decoded struct
    int32_t result = 0;
    result += decoded.billions * 1000000000;
    result += decoded.hundredmillions * 100000000;
    result += decoded.tenmillions * 10000000;
    result += decoded.millions * 1000000;
    result += decoded.hundredthousands * 100000;
    result += decoded.tenthousands * 10000;
    result += decoded.thousands * 1000;
    result += decoded.hundreds * 100;
    result += decoded.tens * 10;
    result += decoded.ones;

    return result;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <string>\n", argv[0]);
        return 1;
    }

    // Concatenate command-line arguments into a single string
    char inputString[1024];  // Adjust the buffer size as needed
    strcpy(inputString, argv[1]);

    for (int i = 2; i < argc; i++) {
        strcat(inputString, " ");
        strcat(inputString, argv[i]);
    }

    int32_t result = wordsToInt(inputString);
    printf("%d\n", result);

    return 0;
}
