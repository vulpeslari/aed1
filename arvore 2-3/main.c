#include "tree.h"

int main(int argc, char *argv)
{
    TreeNode *arvore;
    arvore = create(10, NULL);

    int inserir[] = {5,
                     15,
                     3,
                     7, 12, 18, 2, 4, 14};

    for (int i = 0; i < 9; i++)
    {
        arvore = insert(inserir[i], arvore);
    }

    printf("\nÁrvore:\n");
    imprime(arvore, 0);

    removeMin(arvore, 7);
    removeMin(arvore, 2);
    removeMin(arvore, 4);
    // removeMin(arvore, 2);

    // removeMin(arvore, 15);

    printf("\nÁrvore:\n");
    imprime(arvore, 0);


    return 0;
}