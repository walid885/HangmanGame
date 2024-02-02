#include<stdio.h>
#include "headers.c/HangmanTermInt.h"

int  main (){
    char body[7] = "      "; // Initialize the body array with spaces
    int mistakes = 0;
    char guess[] = "example"; // Replace this with the actual guessed word

    // Call the printBody function to display the initial body
    printBody(mistakes, body);

    // Call the printWord function to display the initial guessed word
    printWord(guess, strlen(guess));


   return 0 ; 
}