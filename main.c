#include <stdio.h>
#include <stdlib.h>

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
float coef(polynomial, int);                        //function returning coefficient of input polynomial's input exponent
int leadExp(polynomial);                            //function returning the largest exponent of input polynomial
polynomial attatch(polynomial, float, float);         //function for adding a term to a input polynomial
polynomial add(polynomial, polynomial);             //function for adding two polynomials

int main(){


    int input;                  //variable for storing input character
//0 input must be handled
    printf("Input first polynomial\n");
    float poly1[100];                               //array to store first polynomial's terms data temporarily
    int poly1cnt = 0;
    while((input = getchar()) != '\0'){

        if(input == ' ')                //in case when space is read
            continue;
        if(input == '\n')               //in case when enter is read
            break;

        input = input - '0';                        //changing char value into integer value
        if(input == 0){         //exception handled in case of zero input
            printf("Coefficient or Exponent cannot be zero! Invalid Input.");
            exit(0);
        }
        poly1[poly1cnt] = input;
        poly1cnt++;
    }

    if(poly1cnt % 2 != 0) {
        printf("Pair of Coefficient and Exponent does not matches! Invalid Input\n");     //exception handled in case terms does not matches
        exit(0);
    }

    polynomial firstPoly = initPoly();

    for(int i = 0; i < poly1cnt; i = i + 2){
        attatch(firstPoly, poly1[i], poly1[i+1]);
        firstPoly.end++;                            //end position of first polynomial is extended
        usedTerms++;                                //by adding new term, usedTerms count must be increased
    }

    firstPoly.end--;                                //polynomial's end is always added once more, so needs to be subtracted




    printf("Input Second polynomial\n");
    float poly2[100];                               //array to store first polynomial's terms data temporarily
    int poly2cnt = 0;
    while((input = getchar()) != '\0'){

        if(input == ' ')                //in case when space is read
            continue;
        if(input == '\n')               //in case when enter is read
            break;

        input = input - '0';                        //changing char value into integer value
        if(input == 0){         //exception handled in case of zero input
            printf("Coefficient or Exponent cannot be zero! Invalid Input.");
            exit(0);
        }
        poly2[poly2cnt] = input;
        poly2cnt++;
    }

    if(poly2cnt % 2 != 0) {
        printf("Pair of Coefficient and Exponent does not matches! Invalid Input\n");     //exception handled in case terms does not matches
        exit(0);
    }

    polynomial secondPoly = initPoly();

    for(int i = 0; i < poly2cnt; i = i + 2){
        attatch(secondPoly, poly2[i], poly2[i+1]);
        secondPoly.end++;                            //end position of second polynomial is extended
        usedTerms++;                                //by adding new term, usedTerms count must be increased
    }

    secondPoly.end--;                                //polynomial's end is always added once more, so needs to be subtracted


    //test

    printf("usedTerms count : %d\n", usedTerms);
    printf("first poly start : %d\n", firstPoly.start);
    printf("first poly end : %d\n", firstPoly.end);
    printf("second poly start : %d\n", secondPoly.start);
    printf("second poly end : %d\n", secondPoly.end);

    for(int i = 0; i < usedTerms; i++){
        printf("%f %d\n", terms[i].coef, terms[i].expon);
    }


}

polynomial initPoly(){
    if(usedTerms == 100){
        printf("There are no space for new terms!");
        exit(0);
    }


    polynomial poly;            //declaring new polynomial

    if(usedTerms == -1) {           //initial state
        poly.start = ++usedTerms;   //polynomial's terms will be stored in 'terms' array, and its starting point will be the very first index not used in the array
        poly.end = usedTerms;       //end point will be modified later in other functions. Default location will be same as the starting point
    }
    else{                           //not an initial state
        poly.start = usedTerms;
        poly.end = usedTerms;
    }

    polyterm term;
    term.coef = -1;
    term.expon = -1;

    terms[poly.start] = term;   //initializing a space in terms array as invalid pair. This will be used as identifier for checking is a polynomial valid, in function isValid()

    return poly;                //return created polynomial
}

int isValid(polynomial poly){
    if(poly.start == poly.end && terms[poly.start].expon == -1)         //if polynomial is never modified after being initialized, it is invalid
        return 0;

    else return 1;
}

float coef(polynomial poly, int expon){
    if(isValid(poly)) {
        for (int i = poly.start; i <=
                                 poly.end; i++) {          //for loop checks is there is input exponent in input polynomial. If exists, returns its coefficient
            if (terms[i].expon == expon)
                return terms[i].coef;
        }
    }
    return 0;               //if input exponent does not exists in input polynomial, returns 0
}

int leadExp(polynomial poly){
    if(isValid(poly))
        return terms[poly.start].expon;                     //since we will store terms in order, starting position's exponent will always be a leading exponent
}

polynomial attatch(polynomial poly, float coef, float expon){
    if(usedTerms == 100){                                   //exception handling for situation terms array is full
        printf("There are no space for new terms!");
        exit(0);
    }

        terms[poly.end].expon = (int)expon;
        terms[poly.end].coef = coef;

    //attatch 실행하면 polynomial의 end 1 늘려주기!
}

