#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ARRAY_SIZE 50

typedef struct{
    char operators[ARRAY_SIZE];
    long double converted_nums[sizeof(long double) * ARRAY_SIZE];
} parsedEquation;

void removeSpaces(char * str);
parsedEquation * parseCalculation(char * original_equation);


int main(){
    char equation[ARRAY_SIZE];
    parsedEquation * parsed_nums;

    printf("Calculator:\n\n");
    fgets(equation, ARRAY_SIZE, stdin);
    removeSpaces(equation);
    
    parsed_nums = parseCalculation(equation);
    char * pOperators = parsed_nums->operators;
    long double * pConverted_nums = parsed_nums->converted_nums;
    long double sum = 0;
    long double power_sum = 1;
    long double base = 0;
    long double power = 0;

    // printf("%c", *parsed_nums->operators);
    while(*pOperators){
        switch(*pOperators++){
            case '+':
                if(sum == 0){
                    sum += *pConverted_nums++;
                }
                sum += *pConverted_nums++;
                break;
            case '-':
                if(sum == 0){
                    sum += *pConverted_nums++;
                }
                sum -= *pConverted_nums++;
                break;
            case '*':
                if(sum == 0){
                    sum += *pConverted_nums++;
                }
                sum *= *pConverted_nums++;
                break;
            case '/':
                if(sum == 0){
                    sum += *pConverted_nums++;
                }
                if(*pConverted_nums == 0){
                    printf("Cannot divide by 0.");
                    return 2;
                }
                sum /= *pConverted_nums++;
                break;
            default:
                printf("Invalid input.\n");
                return 1;
        }
    }
    free(parsed_nums);
    printf("%.2Lf", (float)sum);

    return 0;
}


parsedEquation * parseCalculation(char * original_equation){
    char num_hold[ARRAY_SIZE];
    parsedEquation * parsed_nums = malloc(sizeof(parsedEquation));
    long double * pConverted_nums = parsed_nums->converted_nums;
    char * pOperators = parsed_nums->operators;

    int num_hold_index = 0;

    while(*original_equation){
        if(*original_equation >= '0' && *original_equation <= '9' || *original_equation == '.'){
            num_hold[num_hold_index++] = *original_equation++;
        }
        else{
            *pConverted_nums++ = strtold(num_hold, NULL);
            strncpy(num_hold, "", sizeof(num_hold));
            num_hold_index = 0;

            *pOperators++ = *original_equation++;
        }
    }
    *--pOperators = '\0';
    return parsed_nums;
}


void removeSpaces(char* str) {
    char* temp = str;
    do {
        while (*temp == ' ') {
            ++temp;
        }
    } while (*str++ = *temp++);
}