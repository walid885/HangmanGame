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
    //printSingleOption("6. Piocher un mot", 4, 47, 0);
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

tree *handleFile(tree *dico)
{
    char filename[100];

    do
    {
        printCharactere(' ', 4);
        printf("Entrer nom fichier => ");
        scanf("%s", filename);
    } while (strlen(filename) < 0 || strlen(filename) > 100);

    FILE *file = fopen("src/Words/Animals/level1.txt", "r");

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

    printf("\033[0;32mMots ajouté avec success\033[0m");
    printFooter();

    return dico;
}

tree *HandleManual(tree *dico)
{
    char word[100];

    do
    {
        printCharactere(' ', 4);
        printf("Entrer mot => ");
        scanf("%s", word);
    } while (strlen(word) < 0 || strlen(word) > 100);

    system("clear");
    printHeader("Insertion Options", 25);
    printCharactere(' ', 23);

    printf("\033[0;32mMot ajouté avec success\033[0m");
    printFooter();

    return dicoInsererMot(word, dico, 0);
}

tree *fillTree(tree *dico)
{
    int option;

    printSubMenu();
    do
    {
        printCharactere(' ', 4);
        printf(" => ");
        scanf("%d", &option);
    } while (option < 0 || option > 2);

    switch (option)
    {
    case 0:
        system("clear");
        break;
    case 1:
        dico = HandleManual(dico);
        break;

    case 2:
        dico = handleFile(dico);
        break;

    default:
        break;
    }

    return dico;
}