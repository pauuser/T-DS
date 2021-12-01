#include "../inc/bst.h"

bst_node_t *bst_create_node(int num)
{
    bst_node_t *node = malloc(sizeof(bst_node_t));

    if (node)
    {
        node->num = num;
        node->left = NULL;
        node->right = NULL;
    }

    return node;
}

bst_node_t *bst_add_node(bst_node_t *head, bst_node_t *node)
{
    if (head == NULL)
        return node;
    else if (node == NULL)
        return head;
    else
    {
        if (node->num > head->num)
            head->right = bst_add_node(head->right, node);
        else if (node->num < head->num)
            head->left = bst_add_node(head->left, node);
        //else
        //    printf("ADD : This node already exists!\n");
    }

    return head;
}

bst_node_t *bst_search_node(bst_node_t *head, int num, int *comp_number)
{
    if (head == NULL)
        return NULL;
    else
    {
        *comp_number += 1;
        if (head->num == num)
            return head;
        else if (num > head->num)
            return bst_search_node(head->right, num, comp_number);
        else
            return bst_search_node(head->left, num, comp_number);
    }
}

void bst_traverse(bst_node_t *tree, void (*f)(bst_node_t*, void*), void *arg, char *order)
{
    if (tree == NULL)
        return;

    if (strcmp(order, "pre") == 0)
    {
        f(tree, arg);
        bst_traverse(tree->left, f, arg, order);
        bst_traverse(tree->right, f, arg, order);
    }
    else if (strcmp(order, "in") == 0)
    {
        bst_traverse(tree->left, f, arg, order);
        f(tree, arg);
        bst_traverse(tree->right, f, arg, order);
    }
    else if (strcmp(order, "post") == 0)
    {
        bst_traverse(tree->left, f, arg, order);
        bst_traverse(tree->right, f, arg, order);
        f(tree, arg);
    }
    else
        printf("Wrong way!\n"); 
}

void bst_node_print(bst_node_t *node, void *arg)
{
    FILE *f = arg;
    fprintf(f, "%d ", node->num);
}

bst_node_t *bst_delete_node(bst_node_t *head, int num)
{
    if (head == NULL)
        return head;

    if (num < head->num)
        head->left = bst_delete_node(head->left, num);
    else if (num > head->num)
        head->right = bst_delete_node(head->right, num);
    else
    {
        // нет сыновей или только один
        if ((head->left == NULL) || (head->right == NULL))
        {
            bst_node_t *temp = head->left ? head->left : head->right;
 
            // нет сыновей
            if (temp == NULL)
            {
                temp = head;
                head = NULL;
            }
            // один сын
            else
                *head = *temp;

            free(temp);
        }
        // два сына
        else
        {
            bst_node_t *tmp = head->left;

            while (tmp && tmp->right != NULL)
                tmp = tmp->right;
            
            head->num = tmp->num;

            head->left = bst_delete_node(head->left, tmp->num);
        }
    }
    return head;
}

void bst_free_node(bst_node_t *node, void *arg)
{
    free(node);
}

void bst_free_tree(bst_node_t *head)
{
    bst_traverse(head, bst_free_node, NULL, "post");
}
