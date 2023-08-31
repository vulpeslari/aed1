/*
    Nomes: ALICE SOPHIA LIMA VIEIRA				
        JORGE HENRIQUE BORGES SANTOS			
        JÚLIO CÉSAR PINHEIRO DE ARAÚJO			
        KAUÃ SALES VIANA					
        LARISSA DE SOUZA COSTA 				
        MATHEUS MARTINS RODRIGUES 			
        RAYANE MORAES FERREIRA				
        VITOR HUGO TROVÃO DE MORAES 			

    Mat:2215310033
        2215310039
        2215310015
        2215310041
        2215310042
        2215310024
        2215310026
        2215310049
*/

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
