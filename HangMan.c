#include<stdio.h>
#include "headers/struct.h"
#include "headers/tree.h"
#include "headers/Dictionary.h"
#include "headers/Display.h"

int main() {
    printf("Main is running!\n");

    // Create an empty tree
    tree *myTree = arbreConsVide();
    printf("Line 10\n");

    int userChoice;

    do {
        // Display the main menu
        printToConsole();

        // Get user choice
        printf("\nEnter your choice (0-6): ");
        scanf("%d", &userChoice);

        // Process user choice
        switch (userChoice) {
            case 1:
                // Add words manually
                myTree = HandleManual(myTree);
                break;
            case 2:
                // Consult the dictionary
                printDictionary(myTree, "", 0);
                break;
            case 3:
                // Display the total number of words
                printTotalWords(myTree);
                break;
            case 4:
                // Display the number of different words
                printDifferentWords(myTree);
                break;
            case 5:
                // Consult the number of occurrences of a word
                printOccurrences(myTree);
                break;
            case 6:
                // Choose a level and load words into the tree
                chooseLevel(myTree);
                break;
            case 7:
                // Empty the tree
                myTree = arbreConsVide();
                printEmptiedTree(myTree);
                break;
            case 0:
                // Quit the program
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (userChoice != 0);

    // Delete the tree before exiting
    arbreSuppr(myTree);
    printf("Tree deleted.\n");

    return 0;
}





/*

int main() {
    // Create an empty tree
    tree *myTree = arbreConsVide();

    // Construct a tree node
    tree *leftSubtree = arbreConsVide();
    tree *rightSubtree = arbreConsVide();
    tree *root = arbreCons('A', 2, leftSubtree, rightSubtree);

    // Access the properties of the tree node
    char letter = arbreRacineLetter(root);
    int occurrences = arbreRacineNbOcc(root);

    // Access the left and right subtrees
    tree *left = arbreFilsGauche(root);
    tree *right = arbreFilsDroit(root);

    // Check if the tree is empty
    int isEmpty = arbreEstVide(root);
   printf("Success! and It is working !!");
    // Delete the tree
    arbreSuppr(root);

    return 0;
}
/*
commands : make to make the files 
            make run : to make and execute the project 
            make cleanobj  , in order to clean the .o files 
            make clean : to clean all the files, and lets only the code 



*/



