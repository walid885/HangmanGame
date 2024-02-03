#include<stdio.h>
#include "headers/struct.h"
#include "headers/tree.h"


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