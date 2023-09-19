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
    int billion;

};

// Function to convert words to int32_t
int32_t wordsToInt(char *words) {
    // Define arrays for mapping words to digits (ones, teens, tens)
    char *ones[] = {"", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    char *teens[] = {"", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
    char *tens[] = {"", "ten", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"};

    struct Number decoded;
    decoded.billion = decoded.hundredmillions = decoded.tenmillions = decoded.millions = 0;
    decoded.hundredthousands = decoded.tenthousands = decoded.thousands = decoded.hundreds = decoded.tens = decoded.ones = 0;

    char *token;
    token = strtok(words, " \n");
    int tokencount = 0;
    char *tokens[10];
    char typeCheck = ' ';

    while (token != NULL) {
        tokens[tokencount] = token;
	tokencount++;
	token = strtok(NULL, " \n");
    }
    for (int i = tokencount - 1; i >= 0; i--) {
        printf("%s ", tokens[i]);

        if (tokens[i] == "billion") {
	    typeCheck = 'b';
	} else if (tokens[i] == "million") {
            typeCheck = 'm';
        } else if (token[i] == "thousand") {
            typeCheck = 't';
        } else if (token[i] ==  "hundred") {
            typeCheck = 'h';
        } else {
            int i;
            for (i = 0; i < 10; i++) {
                if (strcmp(token[i], ones[i]) == 0) {
                    if (typeCheck == 'h'){
	                decoded.hundreds = token[i];
		    }else if(typeCheck == 't'){
                    	decoded.thousands = token[i];
		    }else if(typeCheck == 'm'){
		        decoded.millions = token[i];
                    }else if(typeCheck == 'b'){
		        decoded.billions = token[i];
		    }else{
		        decoded.ones = token[i];
		    }
                    break;
                }
            }
            if (i == 10) {
                for (i = 1; i < 10; i++) {
                    if (strcmp(token[i], tens[i]) == 0) {
                        if(typeCheck == 't'){
                           decoded.tenthousands = token[i];
                        }else if(typeCheck == 'm'){
                           decoded.tenmillions = token[i];
                        }else if(typeCheck == 'b'){
                           decoded.tenbillions = token[i];
                        }else{
                           decoded.tens = token[i];
                        }

                        break;
                    }
                }
                if (i == 10) {
                    for (i = 1; i < 10; i++) {
                        if (strcmp(token, teens[i]) == 0) {
                            if(typeCheck == 't'){
	                       decoded.tenthousands = 1;
                               decoded.thousands = token[i];
			    }else if(typeCheck == 'm'){
                               decoded.tenmillions = 1;
                               decoded.millions = token[i];
                            }else if(typeCheck == 'b'){
                               decoded.billions = token[i];
                            }else{
                               decoded.tens = 1;
                               decoded.ones = token[i];
                            }
                            break;
                        }
                    }
                }
            }
        }


    }

    // Calculate the integer value based on the extracted struct
    int32_t result = 0;
    result += decoded.millions * 1000000;
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
