#ifndef TREE_H
#define TREE_H

typedef struct TreeNode {
    char letter;
    int occurrences;
    int theme;
    int level;
    struct TreeNode *left;
    struct TreeNode *right;
} tree;


#endif
