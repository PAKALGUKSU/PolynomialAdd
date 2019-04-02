#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_TERMS 101           //We can contain no more than 100 set of (coef, expon)

typedef struct{
    float coef;
    int expon;
}polyterm;                      //terms of polynomial (each pair of (coef, expon)) is stored in a struct 'polyterm'

polyterm terms[MAX_TERMS];      //this global variable will contain all polynomial terms, regardless of which polynomial it's in
int usedTerms = -1;              //this global variable checks how many space in global array 'terms' are used. To make first element to be stored in index '0', it is initialized as -1

typedef struct{
    int start;
    int end;
}polynomial;                    //polynomial could be defined by knowing its terms' starting and ending position in global polyterm array, 'terms'

polynomial initPoly();                              //function for initializing a polynomial
int isValid(polynomial);                            //function for checking if a polynomial is valid or not
polynomial attach(polynomial, float, float);       //function for adding a term to a input polynomial
void add(polynomial, polynomial);                   //function for adding two polynomials and displaying its result

int main(){


    int input;                                      //variable for storing input character
    printf("Input first polynomial\n");
    float poly1[100];                               //array to store first polynomial's terms data temporarily
    char keyInput[100];
    int poly1cnt = 0;
    char* ptr = NULL;                               //variable to store cut character

    fgets(keyInput, 100, stdin);
    ptr = strtok(keyInput, " ");

    while(ptr != NULL)
    {
        float gotValue = atof(ptr);                 //temporary value to store input number. atof changes string into it's real number value.


        if(poly1cnt% 2  == 1 && (int)gotValue != gotValue)
        {
            printf("Exponent should be only integer! Input Error.\n");
            exit(0);
        }

        poly1[poly1cnt] = gotValue;

        ptr = strtok(NULL, " ");
        poly1cnt++;
    }


    if(poly1cnt % 2 != 0) {
        printf("Pair of Coefficient and Exponent does not matches! Invalid Input\n");     //exception handled in case terms does not matches
        exit(0);
    }

    polynomial firstPoly = initPoly();              //the polynomial variable directly representing first polynomial!

    for(int i = 0; i < poly1cnt; i = i + 2){
        attach(firstPoly, poly1[i], poly1[i + 1]);
        firstPoly.end++;                            //end position of first polynomial is extended
        usedTerms++;                                //by adding new term, usedTerms count must be increased
    }

    firstPoly.end--;                                //polynomial's end is always added once more, so needs to be subtracted

    for(int i = firstPoly.start; i <= firstPoly.end; i++){        //sorting data in descending order using bubble sort
        for(int j = firstPoly.start; j <= firstPoly.end - i; j++){
            if(terms[j].expon < terms[j+1].expon){
                float tempCoef;
                int tempExpon;

                tempExpon = terms[j].expon;
                terms[j].expon = terms[j+1].expon;
                terms[j+1].expon = tempExpon;

                tempCoef = terms[j].coef;
                terms[j].coef = terms[j+1].coef;
                terms[j+1].coef = tempCoef;

            }
        }
    };


    printf("Input Second polynomial\n");
    float poly2[100];                               //array to store first polynomial's terms data temporarily
    int poly2cnt = 0;
                                                    //array to store first polynomial's terms data temporarily

    fgets(keyInput, 100, stdin);
    ptr = strtok(keyInput, " ");

    while(ptr != NULL)
    {
        float gotValue = atof(ptr);                 //temporary value to store input number. atof changes string into it's real number value.


        if(poly2cnt% 2  == 1 && (int)gotValue != gotValue)
        {
            printf("Exponent should be only integer! Input Error.\n");
            exit(0);
        }
        poly2[poly2cnt] = gotValue;

        ptr = strtok(NULL, " ");
        poly2cnt++;
    }

    if(poly2cnt % 2 != 0) {
        printf("Pair of Coefficient and Exponent does not matches! Invalid Input\n");     //exception handled in case terms does not matches
        exit(0);
    }

    polynomial secondPoly = initPoly();             //polynomial variable directly representing second polynomial!

    for(int i = 0; i < poly2cnt; i = i + 2){
        attach(secondPoly, poly2[i], poly2[i + 1]);
        secondPoly.end++;                            //end position of second polynomial is extended
        usedTerms++;                                //by adding new term, usedTerms count must be increased
    }

    secondPoly.end--;                                //polynomial's end is always added once more, so needs to be subtracted

    for(int i = secondPoly.start; i <= secondPoly.end; i++){        //sorting data in descending order using bubble sort
        for(int j = secondPoly.start; j <= secondPoly.end - (i-secondPoly.start); j++){
            if(terms[j].expon < terms[j+1].expon){
                float tempCoef;
                int tempExpon;

                tempExpon = terms[j].expon;
                terms[j].expon = terms[j+1].expon;
                terms[j+1].expon = tempExpon;

                tempCoef = terms[j].coef;
                terms[j].coef = terms[j+1].coef;
                terms[j+1].coef = tempCoef;

            }
        }
    };


    add(firstPoly, secondPoly);                     //adding two given polynomials

}

polynomial initPoly(){
    if(usedTerms == 100){
        printf("There are no space for new terms!");
        exit(0);
    }


    polynomial poly;                //declaring new polynomial

    if(usedTerms == -1) {           //when no polynomial is created previously
        poly.start = ++usedTerms;   //polynomial's terms will be stored in 'terms' array, and its starting point will be the very first index not used in the array
        poly.end = usedTerms;       //end point will be modified later in other functions. Default location will be same as the starting point
    }
    else{                           //when there exists a polynomial created previously
        poly.start = usedTerms;
        poly.end = usedTerms;
    }

    polyterm term;
    term.coef = -1;                 //trash value
    term.expon = -1;                //trash value

    terms[poly.start] = term;   //initializing a space in terms array as invalid pair. This will be used as identifier for checking is a polynomial valid, in function isValid()

    return poly;                //return created polynomial
}

int isValid(polynomial poly){
    if(poly.start == poly.end && terms[poly.start].expon == -1)         //if polynomial is never modified after being initialized, it is invalid
        return 0;

    else return 1;
}

polynomial attach(polynomial poly, float coef, float expon){
    if(usedTerms == 100){                                   //exception handling for situation terms array is full
        printf("There are no space for new terms!");
        exit(0);
    }

        terms[poly.end].expon = (int)expon;
        terms[poly.end].coef = coef;

}

void add(polynomial pol1, polynomial pol2){
    if(isValid(pol1) && isValid(pol2)){                     //add if both polynomials are valid
        int pol1cnt = pol1.start, pol2cnt = pol2.start;

        while(1){
            if(terms[pol1cnt].expon == terms[pol2cnt].expon) {
                if(pol1cnt == pol1.end && pol2cnt == pol2.end){
                    if(terms[pol1cnt].expon == 0){
                        printf("%f", terms[pol1cnt].coef + terms[pol2cnt].coef);
                        break;
                    }
                    printf("%f^%d", terms[pol1cnt].coef + terms[pol2cnt].coef, terms[pol1cnt].expon);
                    break;
                }
                printf("%f^%d+ ", terms[pol1cnt].coef + terms[pol2cnt].coef, terms[pol1cnt].expon);
                pol1cnt++;
                pol2cnt++;
            }
            else if(terms[pol1cnt].expon > terms[pol2cnt].expon){
                printf("%f^%d+ ", terms[pol1cnt].coef, terms[pol1cnt].expon);
                pol1cnt++;
            }
            else if(terms[pol1cnt].expon < terms[pol2cnt].expon){
                printf("%f^%d+ ", terms[pol2cnt].coef, terms[pol2cnt].expon);
                pol2cnt++;
            }


            if(pol1cnt > pol1.end && pol2cnt <= pol2.end){          //when pol1 has reached its' end
                while(pol2cnt < pol2.end){
                    printf("%f^%d+ ", terms[pol2cnt].coef, terms[pol2cnt].expon);
                    pol2cnt++;
                }
                if(terms[pol2cnt].expon == 0){
                    printf("%f", terms[pol2cnt].coef);
                    break;
                }
                printf("%f^%d.", terms[pol2cnt].coef, terms[pol2cnt].expon);
                break;
            }

            if(pol2cnt > pol2.end && pol1cnt <= pol1.end){          //when pol2 has reached its' end
                while(pol1cnt < pol1.end){
                    printf("%f^%d+ ", terms[pol1cnt].coef, terms[pol1cnt].expon);
                    pol1cnt++;
                }
                if(terms[pol1cnt].expon == 0){
                    printf("%f", terms[pol1cnt].coef);
                    break;
                }
                printf("%f^%d.", terms[pol1cnt].coef, terms[pol1cnt].expon);
                break;
            }


        }


    }
}