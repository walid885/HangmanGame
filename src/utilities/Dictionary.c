#include <stdio.h>
#include <stdlib.h>
#include "../../headers/struct.h"
#include "../../headers/Display.h"
#include "../../headers/Dictionary.h"

// ? START HELPERS

// * Créer un noeud intermédiaire
tree *append(char letter)
{
    tree *node = (tree *)malloc(sizeof(tree));

    node->letter = letter;
    node->left = NULL;
    node->right = NULL;
    node->occurrences = 0;

    return node;
}

// * Créer un noeud pour marquer la fin d'un mot
tree *markEndOfWord()
{
    tree *node = (tree *)malloc(sizeof(tree));

    node->letter = '\0';
    node->left = NULL;
    node->right = NULL;
    node->occurrences = 1;

    return node;
}

// * Afficher le mot à partir d'un tableau de caractères pour un indice donné
void printArray(char letters[], int len)
{
    int index;

    printCharactere(' ', 5);

    for (index = 0; index < len; index++)
        printf("%c", letters[index]);

    printf("\n");
}

// ? END HELPERS
tree *createTempTree(int theme, int level) {
    // Implement the logic to create a temporary tree based on theme and level
    // You may need to read words from the corresponding file and insert them into the tree
    // Example:
    tree *tempTree = arbreConsVide();
    tempTree = fillTree(tempTree);  // Implement fillTree based on theme and level
    return tempTree;
}

// * Afficher tous les mots d'un arbre donné
void printDictionary(tree *dico, int theme, int level) {
    system("clear");
    printHeader("Current Dictionary", 25);
    if (dico == NULL) {
        printCharactere(' ', 25);
        printf("\033[1;31mL'arbre est vide\033[0m");
    } else {
        // Create a temporary tree based on the specified theme and level
        tree *tempTree = createTempTree(theme, level);
        
        // Assuming dicoAfficher needs the theme and level parameters
        dicoAfficher(tempTree, "", 0);
        
        // Delete the temporary tree after use
        arbreSuppr(tempTree);
    }

    printFooter();

    int option;

    do {
        printCharactere(' ', 4);
        printf(" 0 pour retourner => ");
        scanf("%d", &option);
    } while (option != 0);

    system("clear");
}

// * On insère un mot dans un arbre donné, si le mot existe on incremente le nombre d'occurence
// * du mot
tree *dicoInsererMot(char word[50], tree *root, int wordIndex)
{
    tree *temp;

    // * Si l'arbre est intialement vide, on va insérer le mot
    if (root == NULL)
    {
        // * Si le mot est n'est pas vide, on procced
        if (word[wordIndex] != '\0')
        {
            // * La creation du racine
            root = append(word[wordIndex]);
            temp = root;
            wordIndex++;

            // * L'ajout du mot dans l'arbre on utilisation la fonction 'append'
            while (word[wordIndex] != '\0')
            {
                temp->left = append(word[wordIndex]);
                temp = temp->left;
                wordIndex++;
            }

            // * On marque la fin du mot par un noeud qui contient le nombre d'occurence 1
            temp->left = markEndOfWord();

            return root;
        }
    }
    else
    {
        // * Sinon l'arbre n'est pas vide
        // * On test si la lettre existe
        if (root->letter == word[wordIndex])
        {
            // * Si la lettre existe déja on test le reste de mot
            // * pour savoir si on va incrementer le nombre
            // * d'occurence.
            if (root->left == NULL && root->letter == '\0')
            {
                root->occurrences++;
            }
            else
            {
                root->left = dicoInsererMot(word, root->left, wordIndex + 1);
            }

            return root;
        }
        // * La lettre n'existe pas ce qui indique que cette une nouveau mot a inserer
        // * on passe alors au sous arbre droite

        root->right = dicoInsererMot(word, root->right, wordIndex);
        return root;
    }
}

// * Afficher le nombre d'occurence d'un mot donné
int dicoNbOcc(char *word, int wordIndex, tree *root)
{
    // * Si la premiere lettre du mot donné est égale a celle de la racine
    // * on passe au sous arbre gauche
    if (word[wordIndex] == root->letter)
    {
        // * Si le caractere est \0, le mot est vérifier et on
        // * retourne le nombre d'occurence.
        if (root->left == NULL && root->letter == '\0')
            return root->occurrences;

        // * Sinon on passe au noeud suivant pour vérfier le reste du mot
        return dicoNbOcc(word, wordIndex + 1, root->left);
    }

    if (root->right == NULL)
        return 0;

    // * Si la premiere lettre du mot donné est differente de celle
    // * de la racine on vérifie les sous arbres droites.
    return dicoNbOcc(word, wordIndex, root->right);
}

// * Afficher le nombre des mots différents
int dicoNbMotsDifferents(tree *root)
{
    if (root != NULL)
    {
        // * Si le noeud marque la fin d'un mot, on retourne
        // * 1  et on passe aux sous arbre gauche et droite
        if (root->letter == '\0')
            return 1 + (dicoNbMotsDifferents(root->left) + dicoNbMotsDifferents(root->right));

        // * Sinon on passe aux sous arbres gauche et droite
        return dicoNbMotsDifferents(root->left) + dicoNbMotsDifferents(root->right);
    }

    return 0;
}

// * Afficher le nombre total des mots
int dicoNbMotsTotal(tree *root)
{
    if (root != NULL)
    {
        // * Si le noeud marque la fin d'un mot, on retourne
        // * le nombre d'occurence de ce mot, et on passe
        // * aux sous arbre gauche et droite
        if (root->letter == '\0')
            return root->occurrences + (dicoNbMotsTotal(root->left) + dicoNbMotsTotal(root->right));

        // * Sinon on passe aux sous arbres gauche et droite
        return dicoNbMotsTotal(root->left) + dicoNbMotsTotal(root->right);
    }

    return 0;
}

void printTreeStructure(tree *root, int level) {
    if (root == NULL) {
        return;
    }

    // Print the right subtree
    printTreeStructure(root->right, level + 1);

    // Indentation based on the level
    for (int i = 0; i < level; i++) {
        printf("   ");
    }

    // Print the node data
    printf("%c\n", root->letter);

    // Print the left subtree
    printTreeStructure(root->left, level + 1);
}
