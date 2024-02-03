#include<stdio.h>
#include "headers/struct.h"
#include "headers/tree.h"

int main() {
    // Create an empty tree
    tree *myTree = arbreConsVide();

    // Open the file containing the words
    FILE *fp;
    fp = fopen("../src/Words/Animals/level1.txt", "r");

    // Read each word from the file and insert it into the tree
    char word[50];
    while (fscanf(fp, "%s", word) != EOF) {
        myTree = dicoInsererMot(word, myTree, 0);
    }

    // Close the file
    fclose(fp);

    // Display all the words in the tree
    char wordArray[50];
    dicoAfficher(myTree, wordArray, 0);

    // Delete the tree
    arbreSuppr(myTree);

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



