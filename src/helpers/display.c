#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../headers/struct.h"
#include "../../headers/Dictionary.h"

void printCharactere(char charactere, int number)
{
    if (charactere != ' ')
        printf("\n");

    for (int i = 0; i < number; i++)
    {
        printf("%c", charactere);
    }

    if (charactere != ' ')
        printf("\n");
}

void printSingleOption(const char *content, int firstSpacing, int secondSpacing, int last)
{
    printf("|");
    printCharactere(' ', firstSpacing);
    printf("%s", content);
    printCharactere(' ', secondSpacing);
    printf("|");
    if (last == 0)
        printf("\n");
}

void printOptions()
{
    printSingleOption("1. Ajouter des mots au dictionaires", 4, 29, 0);
    printSingleOption("2. Consulter le dictionaire", 4, 37, 0);
    printSingleOption("3. Afficher le nombre totales des mots", 4, 26, 0);
    printSingleOption("4. Afficher le nombre des mots differents", 4, 23, 0);
    printSingleOption("5. Consulter le nombre d'occurence d'un mot", 4, 21, 0);
    printSingleOption("6. Choisir un Niveau", 4, 47, 0);

    printSingleOption("7. Vider l'arbre", 4, 48, 0);
    printSingleOption(" ", 4, 63, 0);
    printSingleOption("0. Quitter", 4, 54, 1);
}


void printHeader(const char *content, int spacing)
{
    printCharactere('-', 70);
    printf("|");
    printCharactere(' ', 25);
    printf("%s", content);
    printCharactere(' ', spacing);
    printf("|");
    printCharactere('-', 70);
}

void printFooter()
{
    printCharactere('-', 70);
}

void printToConsole()
{
    printHeader("Dictionary Management", 22);
    printOptions();
    printFooter();
}

void printDictionary(tree *dico, char path[], int wordLen)
{
    system("clear");
    printHeader("Current Dictionary", 25);
    if (dico == NULL)
    {
        printCharactere(' ', 25);
        printf("\033[1;31mL'arbre est vide\033[0m");
    }
    else
    {
        dicoAfficher(dico, path, wordLen);
    }

    printFooter();

    int option;

    do
    {
        printCharactere(' ', 4);
        printf(" 0 pour retourner => ");
        scanf("%d", &option);
    } while (option != 0);

    system("clear");
}

void printDifferentWords(tree *dico)
{
    system("clear");
    printHeader("Dictionary Stats", 27);
    printCharactere(' ', 20);
    printf("Le nombre de mot different est:  \033[0;35m%d\033[0m", dicoNbMotsDifferents(dico));
    printFooter();
}

void printTotalWords(tree *dico)
{
    system("clear");
    printHeader("Dictionary Stats", 27);
    printCharactere(' ', 22);
    printf("Le nombre total de mot est:  \033[0;35m%d\033[0m", dicoNbMotsTotal(dico));
    printFooter();
}

void printOccurrences(tree *dico)
{
    char word[100];

    if (dico == NULL)
    {
        system("clear");
        printHeader("Dictionary Stats", 27);
        printCharactere(' ', 25);
        printf("\033[1;31mL'arbre est déja vide\033[0m");
        printFooter();
    }
    else
    {
        do
        {
            printCharactere(' ', 4);
            printf("Entrer mot => ");
            scanf("%s", word);
        } while (strlen(word) < 0 || strlen(word) > 100);

        system("clear");
        printHeader("Dictionary Stats", 27);
        printCharactere(' ', 18);
        printf("Le nombre d'occurence de \033[0;35m%s\033[0m est: \033[0;35m%d\033[0m", word, dicoNbOcc(word, 0, dico));
        printFooter();
    }
}

void printEmptiedTree(tree *dico)
{
    system("clear");
    printHeader("Dictionary Management", 22);
    printCharactere(' ', 25);
    if (dico == NULL)
    {
        printf("\033[1;31mL'arbre est déja vide\033[0m");
    }
    else
    {
        printf("\033[0;32mArbre effacé avec succès\033[0m");
    }

    printFooter();
}

void printSubMenu()
{
    system("clear");
    printHeader("Insertion Options", 26);
    printSingleOption("1. Ajouter manuellement", 4, 41, 0);
    printSingleOption("2. Ajouter à partir d'une fichier", 4, 31, 0);
    printSingleOption(" ", 4, 63, 0);
    printSingleOption("0. Retourner", 4, 52, 1);
    printFooter();
}

tree *handleFile(tree *dico, const char *filePath)
{
    FILE *file = fopen(filePath, "r");

    system("clear");
    printHeader("Insertion Options", 25);
    printCharactere(' ', 18);

    if (!file)
    {
        printf("\033[1;31mVeuillez vérifier le nom de fichier\033[0m");
        printFooter();
        return dico;
    }

    char line[500];

    while (fgets(line, sizeof(line), file))
    {
        line[strlen(line) - 1] = '\0';
        dico = dicoInsererMot(line, dico, 0);
    }

    fclose(file);

    printf("\033[0;32mMots ajoutés avec succès\033[0m");
    printFooter();

    return dico;
}


void chooseLevel(tree *myTree)
{
    int levelOption;

    do
    {
        printCharactere(' ', 4);
        printf("Choisissez un niveau (1-3) => ");
        scanf("%d", &levelOption);

    } while (levelOption < 1 || levelOption > 3);

    char filePath[100];
    sprintf(filePath, "src/Words/Animals/level%d.txt", levelOption);
    printf("this is where is line 219!00");
    // Clear the tree before loading words from a new level
    arbreSuppr(myTree);

    // Open and load words from the selected level file
    myTree = handleFile(myTree, filePath);

    // Display the words in the chosen level
    printf("Words in Level %d:\n", levelOption);
    char wordArray[50];
    dicoAfficher(myTree, wordArray, 0);

    // Optionally, you can continue with other game logic or interactions here

    // Example: Ask the user to play the Hangman game with words from this level
    // playHangman(myTree);

    // Clear the tree if needed
    arbreSuppr(myTree);
}


void printThemeSubMenu(int *theme) {
    system("clear");
    printHeader("Theme Selection", 27);
    printSingleOption("1. Animals", 4, 41, 0);
    printSingleOption("2. Furniture", 4, 35, 0);
    printSingleOption("3. Food", 4, 40, 0);
    printSingleOption("0. Back", 4, 54, 1);
    printFooter();

    do {
        printCharactere(' ', 4);
        printf(" => ");
        scanf("%d", theme);
    } while (*theme < 0 || *theme > 3);
}

void printLevelSubMenu(int *level) {
    system("clear");
    printHeader("Level Selection", 27);
    printSingleOption("1. Level 1", 4, 45, 0);
    printSingleOption("2. Level 2", 4, 45, 0);
    printSingleOption("3. Level 3", 4, 45, 0);
    printSingleOption("0. Back", 4, 54, 1);
    printFooter();

    do {
        printCharactere(' ', 4);
        printf(" => ");
        scanf("%d", level);
    } while (*level < 0 || *level > 3);
}

tree *HandleManual(tree *dico)
{
    int theme;
    int level;
    char word[100];

    // Choose the theme (Animals, Furniture, Food)
    printThemeSubMenu(&theme);

    if (theme == 0) {
        system("clear");
        return dico;
    }

    // Choose the level
    do {
        printSubMenu();
        printCharactere(' ', 4);
        printf(" => ");
        scanf("%d", &level);
    } while (level < 0 || level > 3);

    while (1) {
        // Choose the level submenu (Level 1, Level 2, Level 3)
        printLevelSubMenu(&level);

        if (level == 0) {
            // If the user selects 0, go back to the main menu
            system("clear");
            printHeader("Insertion Options", 25);
            printCharactere(' ', 18);
            printf("\033[0;32mWords added successfully\033[0m");
            printFooter();
            return dico;
        }

        char filePath[100];
        sprintf(filePath, "src/Words/%s/level%d.txt", (theme == 1) ? "Animals" : ((theme == 2) ? "Furniture" : "Food"), level);

        // Open the file in append mode
        FILE *file = fopen(filePath, "a");

        if (!file) {
            printf("\033[1;31mError opening the file\033[0m");
            printFooter();
            return dico;
        }

        // Get the word from the user
        do {
            printCharactere(' ', 4);
            printf("Enter a word (or type 'exit' to finish) => ");
            scanf("%s", word);

            if (strcmp(word, "exit") == 0) {
                fclose(file);
                break;  // Break the loop to go back to level selection
            }

        } while (strlen(word) == 0 || strlen(word) > 100);

        // Append the word to the file
        fprintf(file, "%s\n", word);

        // Insert the word into the tree
        dico = dicoInsererMot(word, dico, 0);

        fclose(file);
    }

    return dico;
}


/*
tree *printRandomWord(tree *dico)
{
    char filename[100];
    char buffer[100];

    do
    {
        printCharactere(' ', 4);
        printf("Entrer le fichier => ");
        scanf("%s", filename);
    } while (strlen(filename) < 0 || strlen(filename) > 100);

    system("clear");
    printHeader("Random Word Picker", 25);
    printCharactere(' ', 18);
    if (piocherMot(buffer, filename) == 1)
    {
        printf("\033[0;32mMot ajouté avec success, le mot est \033[0;35m%s\033[0m", buffer);
        printFooter();

        return dicoInsererMot(buffer, dico, 0);
    }

    printf("\033[1;31mVeuillez vérifier le nom de fichier\033[0m");
    printFooter();

    return dico;
}
*/