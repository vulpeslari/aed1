#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode TreeNode;
typedef struct link Link;

TreeNode *balancear(TreeNode *aux);
TreeNode *insert_in_root(int key, TreeNode *arvore);
TreeNode *create(int key, TreeNode *dad);

struct TreeNode
{
    int keys[3];
    int num_keys;
    TreeNode *children[3]; // children[menor que todas as chaves, entre as chaves, maior qur todas as chaves]
    TreeNode *father;
};

TreeNode *insert(int key, TreeNode *arvore)
{
    TreeNode *aux = arvore;
    int find_pos = 1;
    // Caso a inserção ocorre na nó raiz da arvore
    if (aux->father == NULL && aux->children[0] == NULL && aux->children[1] == NULL && aux->children[2] == NULL)
    {
        return insert_in_root(key, arvore);
    }

    // Caso não ,inicia um loop buscando uma posição na arvore
    while (find_pos)
    {
        // Se a chave a ser inseria é menor que a chave de menor valor do nó pai, então vai para o galho esquerdo se esse for não nulo
        if (key < aux->keys[0] && aux->children[0] != NULL)
        {
            aux = aux->children[0];
        }
        // Se a chave a ser inseria é maior que a chave de menor valor do nó pai e menor que a chave de maior valor do nó pai, então vai para o galho intermediário se esse for não nulo
        else if (key > aux->keys[0] && key < aux->keys[1] && aux->children[1] != NULL)
        {
            aux = aux->children[1];
        }
        // Se a chave a ser inseria é maior que a chave de maior valor do nó pai, então vai para o galho direito se esse for não nulo
        else if (key > aux->keys[2] && aux->children[2] != NULL)
        {
            aux = aux->children[2];
        }
        // Caso encontre um  nó não nulo, e com apenas uma chave, então adicione key a esse nó.
        else if (aux->num_keys == 1)
        {
            aux->keys[1] = key;
            aux->num_keys += 1;
            aux = balancear(aux);
            find_pos = 0;
        }
        // Caso encontre um nó não nulo, com duas chaves nele.
        else if (aux->num_keys == 2 && aux->father != NULL)
        {
            TreeNode *temp;
            aux = insert_in_root(key, aux);
            // Inseri um valor no nó da arvore, e se o nó atingir tamanho 3, então divide os em três nós
            /*
            Exemplo: no(2,3), insiro o 4, então fica no(2,3,4), isso não pode ocorrer, logo é transformado em:
            O novo nó pai:              ------3------
                                        |           |
            Os novos nós filhos:        2           4
            */
            temp = aux->father;

            // Caso esse nó tenha um nó pai simples(apenas uma chave)
            if (temp->num_keys == 1)
            {
                // Caso esse nó seja maior que a chave do nó pai
                if (aux->keys[0] > temp->keys[0])
                {
                    temp->keys[1] = aux->keys[0];
                    temp->children[1] = aux->children[0];
                    temp->children[1]->father = temp;
                    temp->children[2] = aux->children[2];
                    temp->children[2]->father = temp;
                    temp->num_keys += 1;
                    free(aux);
                    aux = NULL;
                }

                // Caso esse nó seja menor que a chave do nó pai
                else if (aux->keys[0] < temp->keys[0])
                {
                    temp->keys[1] = temp->keys[0];
                    temp->keys[0] = aux->keys[0];

                    temp->children[0] = aux->children[0];
                    temp->children[0]->father = temp;
                    temp->children[1] = aux->children[2];
                    temp->children[1]->father = temp;
                    temp->num_keys += 1;

                    free(aux);
                    aux = NULL;
                }
            }

            // Caso o nó possui um nó pai duplo
            else if (temp->num_keys == 2)
            {
                TreeNode *temp_2;

                // Caso a chave seja maior que o nó de maior valor do nó pai
                if (aux->keys[0] > temp->keys[1])
                {

                    temp_2 = create(temp->keys[0], temp);
                    temp_2->keys[0] = temp->keys[0];

                    temp->keys[0] = temp->keys[1];
                    temp->keys[1] = 0;

                    temp_2->children[0] = temp->children[0];
                    temp_2->children[2] = temp->children[1];

                    temp_2->children[0]->father = temp_2;
                    temp_2->children[2]->father = temp_2;

                    temp->children[0] = temp_2;
                    temp->children[2] = aux;
                    temp->children[1] = NULL;

                    temp->num_keys = 1;
                }
                // Caso a chave seja menor que o nó de menor valor do nó pai
                else if (aux->keys[0] < temp->keys[0])
                {
                    temp_2 = create(temp->keys[1], temp);
                    temp_2->keys[0] = temp->keys[1];

                    temp->keys[1] = 0;

                    temp_2->children[0] = temp->children[1];
                    temp_2->children[2] = temp->children[2];

                    temp_2->children[0]->father = temp_2;
                    temp_2->children[2]->father = temp_2;

                    temp->children[0] = aux;
                    temp->children[1] = NULL;

                    temp->children[2] = temp_2;
                    temp->num_keys = 1;
                }
                // Caso a chave seja intermediária
                else if (aux->keys[0] > temp->keys[0] && aux->keys[0] < temp->keys[1])
                {
                    temp = insert_in_root(aux->keys[0], temp);
                    temp->children[0]->children[2] = aux->children[0];
                    temp->children[2]->children[0] = aux->children[2];
                    temp->children[1] = NULL;
                    free(aux);
                }
            }
            find_pos = 0;
        }
    }
    return arvore;
}

// Funções auxiliares

TreeNode *create(int key, TreeNode *dad)
{
    TreeNode *temp;
    temp = (TreeNode *)malloc(sizeof(TreeNode));
    for (int i = 0; i < 3; i++)
    {
        temp->keys[i] = 0;
        temp->children[i] = NULL;
    }
    temp->keys[0] = key;
    temp->father = dad; //
    temp->num_keys = 1;
    return temp;
}

TreeNode *insert_in_root(int key, TreeNode *arvore)
{
    if (arvore->num_keys == 1)
    {
        arvore->num_keys += 1;
        arvore->keys[1] = key;
        arvore = balancear(arvore);
        return arvore;
    }
    else if (arvore->num_keys == 2)
    {
        arvore->num_keys += 1;
        arvore->keys[2] = key;
        arvore = balancear(arvore);

        TreeNode *menor = (TreeNode *)malloc(sizeof(TreeNode));
        TreeNode *maior = (TreeNode *)malloc(sizeof(TreeNode));

        menor = create(arvore->keys[0], arvore);
        maior = create(arvore->keys[2], arvore);

        arvore->keys[0] = arvore->keys[1];
        arvore->keys[1] = 0;
        arvore->keys[2] = 0;
        arvore->children[0] = menor;
        arvore->children[2] = maior;
        arvore->num_keys = 1;

        return arvore;
    }
}

TreeNode *balancear(TreeNode *aux)
{
    if (aux->num_keys == 2)
    {
        // Caso o nó tenha duas chaves, ordene-as
        if (aux->keys[0] > aux->keys[1])
        {
            int temp = aux->keys[0];
            aux->keys[0] = aux->keys[1];
            aux->keys[1] = temp;
        }
        return aux;
    }
    else if (aux->num_keys == 3)
    {
        // Caso o nó tenha três chaves, ordene-as
        if (aux->keys[0] > aux->keys[1])
        {
            int temp = aux->keys[0];
            aux->keys[0] = aux->keys[1];
            aux->keys[1] = temp;
        }
        if (aux->keys[1] > aux->keys[2])
        {
            int temp = aux->keys[1];
            aux->keys[1] = aux->keys[2];
            aux->keys[2] = temp;
        }
        if (aux->keys[0] > aux->keys[1])
        {
            int temp = aux->keys[0];
            aux->keys[0] = aux->keys[1];
            aux->keys[1] = temp;
        }
    }

    return aux;
}

void imprime(TreeNode *root, int level)
{
    if (root == NULL)
        return;

    imprime(root->children[2], level + 1);
    for (int i = 0; i < level; i++)
        printf("    ");
    for (int i = 0; i < root->num_keys; i++)
        printf("%d ", root->keys[i]);
    printf("\n");
    imprime(root->children[1], level + 1);
    imprime(root->children[0], level + 1);
}

TreeNode *removeNo(TreeNode *arvore)
{
    TreeNode *aux = arvore;
    // printf("removeNo");
    // no folha
    
    if(aux->children[0] == NULL && aux->children[1] == NULL && aux->children[2] == NULL && aux->num_keys == 1)
    {
        aux->keys[0] = aux->keys[1];
        aux->keys[1] = 0;
        return arvore;
    }
    else if (aux->children[0] == NULL && aux->children[1] == NULL && aux->children[2] == NULL && aux->num_keys == 0)
    {
        printf("\n\nfree");

        aux = aux->father;
        return removeNo(aux);
    }

    // no galho
    if (aux->num_keys == 2)
    {
        printf("\n\ngalho");
        if (aux->children[0]->num_keys == 0 )
        {
            aux->children[0]->keys[0] = aux->keys[0];
            aux->children[0]->num_keys++;
            aux->children[0]->children[2] = aux->children[1]->children[1];
            
            aux->keys[0] = aux->children[1]->keys[0];
            aux->children[1]->keys[0] = aux->children[1]->keys[1];
            aux->children[1]->num_keys--;
            if(aux->children[1]->num_keys == 0)
            {
                aux->children[0]->children[2] = aux->children[1]->children[2];
            }
            else
            {
                aux->children[0]->children[2] = aux->children[1]->children[1];
            }
            return removeNo(aux);
        }

        else if (aux->children[1]->num_keys == 0)
        {
            if(aux->children[0]->num_keys == 1)
            {
                 aux->children[0]->keys[1] = aux->keys[0];
                 aux->children[0]->num_keys++;
                 aux->children[0]->children[1] = aux->children[0]->children[2];
                 aux->children[0]->children[2] = aux->children[1]->children[0];
                 aux->keys[0] = aux->keys[1];
                 aux->keys[1] = 0;
                 aux->num_keys--;
                 free(aux->children[1]);
                 aux->children[1] = NULL;
            }
            else
            {

                aux->children[1]->keys[0] = aux->keys[0];
                aux->children[1]->num_keys++;

                aux->keys[0] = aux->children[0]->keys[1];
                aux->children[0]->keys[1] = 0;
                aux->children[0]->num_keys--;
            }
           
            return removeNo(aux);
        }

        else if (aux->children[2]->num_keys == 0)
        {
            aux->children[2]->keys[0] = aux->keys[1];
            aux->children[2]->num_keys++;
            aux->keys[1] = 0;
            if(aux->children[1]->num_keys == 2)
            {
                aux->keys[1] = aux->children[1]->keys[1];
                aux->children[1]->keys[1] = 0;
                aux->children[1]->num_keys--;
            }
            else
            {
                aux->children[2]->keys[1] = aux->children[2]->keys[0];
                aux->children[2]->keys[0] = aux->children[1]->keys[0];
                aux->children[2]->num_keys++;
                aux->children[1]->keys[1] = 0;
                aux->children[1]->num_keys--;
                free(aux->children[1]);
                aux->children[1] = NULL;
                aux->num_keys--;
            }

            return removeNo(aux);
        }
    }
    else if(aux->num_keys == 1)
    {
        if(aux->children[0]->num_keys == 0)
        {
            if(aux->children[2]->num_keys == 2)
            {
                aux->children[0]->keys[0] = aux->keys[0];
                aux->children[0]->num_keys++;
                aux->keys[0] = aux->children[2]->keys[0];
                aux->children[2]->keys[0] = aux->children[2]->keys[1];
                aux->children[2]->keys[1] = 0;
                aux->children[2]->num_keys--;
            }
            else
            {
                aux->keys[1] = aux->children[2]->keys[0];
                free(aux->children[0]);
                free(aux->children[2]);
                aux->children[0] = NULL;
                aux->children[2] = NULL;
            }
        }
        else if(aux->children[2]->num_keys == 0)
        {
            if(aux->children[0]->num_keys == 2)
            {
                aux->children[2]->keys[0] = aux->keys[0];
                aux->children[2]->num_keys++;
                aux->keys[0] = aux->children[0]->keys[1];
                aux->children[0]->keys[1] = 0;
                aux->children[0]->num_keys--;
            }
            else
            {
                aux->keys[1] = aux->keys[0];
                aux->keys[0] = aux->children[0]->keys[0];
                free(aux->children[0]);
                free(aux->children[2]);
                aux->children[0] = NULL;
                aux->children[2] = NULL;
            }
        }
    }
    else if(aux->num_keys == 0)
    {
         if(aux->children[0]->num_keys == 2)
            {
                aux->keys[0] = aux->children[0]->keys[1];
                aux->children[0]->num_keys++;
                aux->keys[0] = aux->children[2]->keys[0];
                aux->children[2]->keys[0] = aux->children[2]->keys[1];
                aux->children[2]->keys[1] = 0;
                aux->children[2]->num_keys--;
            }
            else
            {
                aux->keys[0] = aux->children[0]->keys[0];
                aux->keys[1] = aux->children[2]->keys[0];
                aux->num_keys+=2;
                free(aux->children[0]);
                free(aux->children[2]);
                aux->children[0] = NULL;
                aux->children[2] = NULL;
            }
        
    }
    else{
        return arvore;
    }

}

void removeMin(TreeNode *arvore, int key)
{

    int find_pos2 = 1;
    TreeNode *aux = arvore;

    while (find_pos2)
    {
        // remover nó folha
        if (key == aux->keys[0])
        {
            aux->keys[0] = 0;
            // printf("\nachou");
            aux->num_keys--;

            aux = removeNo(aux);
            find_pos2 = 0;
        }
        else if (key == aux->keys[1])
        {
            aux->keys[1] = 0;
            aux->num_keys--;
            // printf("\nachou");

            find_pos2 = 0;
        }
        else if (key > aux->keys[0] && key < aux->keys[1] && aux->children[1] != NULL)
        {
            // printf("\nmeio");

            aux = aux->children[1];
        }
        else if (key < aux->keys[0] && aux->children[0] != NULL)
        {
            // printf("\nesqu");

            aux = aux->children[0];
        }
        else if (key > aux->keys[0] && aux->children[2] != NULL)
        {
            aux = aux->children[2];
            // printf("\ndir");
        }
    }
}
int search(TreeNode *tree, int value)
{
    int i;
    int pos;

    // Verifica se a árvore não está vazia
    if (tree != NULL)
    {
        // Percorre as chaves do nó da árvore
        // Se o valor foi encontrado retorna 1
        if (tree->num_keys == 1)
        {
            if (tree->keys[0] == value)
            {
                printf("Value %d was found \n", value);
                return 1;
            }
            else if (value < tree->keys[0])
                pos = 0;
            else if (value > tree->keys[0])
                pos = 2;
        }
        else
        {
            if (tree->keys[0] == value)
            {
                printf("Value %d was found \n", value);
                return 1;
            }
            // Se o valor buscado for menor que a primeira chave do árvore, a busca segue a subárvore esquerda
            else if (value < tree->keys[0])
                pos = 0;

            // Se o valor buscado está entre as duas chaves da árvore, a busca segue a subárvore do meio
            else if (value > tree->keys[0] && value < tree->keys[1])
                pos = 1;
            else if (tree->keys[1] == value)
            {
                printf("Value %d was found \n", value);
                return 1;
            }
            // Se o valor buscado for maior que a segunda chave da árvore, a busca segue a subárvore direita
            else if (value > tree->keys[1])
                pos = 2;
        }

        // Chamada recursiva para a busca, seguindo uma subárvore
        return search(tree->children[pos], value);
    }

    // Se o valor não foi encontrado, retorna nulo
    printf("Value not found \n");
    return 0;
}
//     TreeNode *aux;
//     if (arvore == NULL)
//     {

//         return;
//     }

//     if (arvore->children[0] != NULL)
//     {
//         aux = arvore;
//         arvore = arvore->children[1];
//         free(aux);
//         return arvore;
//     }
//     return arvore;

// }