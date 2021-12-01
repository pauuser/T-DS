#include "../inc/avl.h"

avl_node_t *avl_create_node(int num)
{
    avl_node_t *tmp = malloc(sizeof(avl_node_t));

    if (tmp)
    {
        tmp->num = num;
        tmp->left = NULL;
        tmp->right = NULL;
        tmp->height = 1;
    }
    
    return tmp;
}

avl_node_t *avl_add_node(avl_node_t *head, avl_node_t *node)
{
    if (head == NULL)
        return node;
    else if (node == NULL)
        return head;
    else
    {
        if (node->num > head->num)
            head->right = avl_add_node(head->right, node);
        else if (node->num < head->num)
            head->left = avl_add_node(head->left, node);
        //else
        //    printf("ADD : This node already exists!\n");
        
        head->height = max(avl_node_height(head->right), avl_node_height(head->left)) + 1;

        int balance = avl_node_height(head->left) - avl_node_height(head->right);
        
        // левый левый поворот
        if (balance > 1 && node->num < head->left->num)
        {
            head = avl_ll_rotation(head);
        }
        // правый правый поворот
        else if (balance < -1 && node->num > head->right->num)
        {
            head = avl_rr_rotation(head);
        }
        // левый правый поворот
        else if (balance > 1 && node->num > head->left->num)
        {
            head = avl_lr_rotation(head);
        }
        // правый левый поворот
        else if (balance < -1 && node->num < head->right->num)
        {
            head = avl_rl_rotation(head);
        }
    }

    return head;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int avl_node_height(avl_node_t *node)
{
    int height = 0;
    if (node)
        height = node->height;
    
    return height;
}

avl_node_t *avl_ll_rotation(avl_node_t *tree)
{
    avl_node_t *new_root = tree->left;
    tree->left = new_root->right;
    new_root->right = tree;

    tree->height = max(avl_node_height(tree->left), avl_node_height(tree->right)) + 1;
    new_root->height = max(avl_node_height(new_root->left), avl_node_height(new_root->right)) + 1;

    return new_root;
}

avl_node_t *avl_rr_rotation(avl_node_t *tree)
{
    avl_node_t *new_root = tree->right;
    tree->right = new_root->left;
    new_root->left = tree;

    tree->height = max(avl_node_height(tree->left), avl_node_height(tree->right)) + 1;
    new_root->height = max(avl_node_height(new_root->left), avl_node_height(new_root->right)) + 1;

    return new_root;
}

avl_node_t *avl_lr_rotation(avl_node_t *tree)
{
    tree->left = avl_rr_rotation(tree->left);
    tree = avl_ll_rotation(tree);

    return tree;
}

avl_node_t *avl_rl_rotation(avl_node_t *tree)
{
    tree->right = avl_ll_rotation(tree->right);
    tree = avl_rr_rotation(tree);

    return tree;
}

avl_node_t *avl_search_node(avl_node_t *head, int num, int *comp_number)
{
    if (head == NULL)
        return NULL;
    else
    {
        *comp_number += 1;
        if (head->num == num)
            return head;
        else if (num > head->num)
            return avl_search_node(head->right, num, comp_number);
        else
            return avl_search_node(head->left, num, comp_number);
    }
}

void avl_traverse(avl_node_t *tree, void (*f)(avl_node_t*, void*), void *arg, char *order)
{
    if (tree == NULL)
        return;

    if (strcmp(order, "pre") == 0)
    {
        f(tree, arg);
        avl_traverse(tree->left, f, arg, order);
        avl_traverse(tree->right, f, arg, order);
    }
    else if (strcmp(order, "in") == 0)
    {
        avl_traverse(tree->left, f, arg, order);
        f(tree, arg);
        avl_traverse(tree->right, f, arg, order);
    }
    else if (strcmp(order, "post") == 0)
    {
        avl_traverse(tree->left, f, arg, order);
        avl_traverse(tree->right, f, arg, order);
        f(tree, arg);
    }
    else
        printf("Wrong way!\n"); 
}

void avl_node_print(avl_node_t *node, void *arg)
{
    FILE *f = arg;
    fprintf(f, "%d ", node->num);
}

int get_balance(avl_node_t *head)
{
    int balance = 0;
    if (head == NULL)
        balance = 0;
    else
        balance = avl_node_height(head->left) - avl_node_height(head->right);

    return balance;    
}

avl_node_t *avl_delete_node(avl_node_t *head, int num)
{
    if (head == NULL)
        return head;

    if (num < head->num)
        head->left = avl_delete_node(head->left, num);
    else if (num > head->num)
        head->right = avl_delete_node(head->right, num);
    else
    {
        // нет сыновей или только один
        if ((head->left == NULL) || (head->right == NULL))
        {
            avl_node_t *temp = head->left ? head->left : head->right;
 
            // нет сыновей
            if (temp == NULL)
            {
                temp = head;
                head = NULL;
            }
            // один сын
            else
                *head = *temp; // копирование

            free(temp);
        }
        // два сына
        else
        {
            avl_node_t *tmp = head->left;

            while (tmp && tmp->right != NULL)
                tmp = tmp->right;
            
            head->num = tmp->num;

            head->left = avl_delete_node(head->left, tmp->num);
        }
    }
 
    if (head != NULL)
    {
        head->height = max(avl_node_height(head->right), avl_node_height(head->left)) + 1;

        int balance = get_balance(head);

        // левый левый поворот
        if (balance > 1 && get_balance(head->left) >= 0)
            head = avl_ll_rotation(head);
        // правый правый поворот
        else if (balance < -1 && get_balance(head->left) <= 0)
            head = avl_rr_rotation(head);
        // левый правый поворот
        else if (balance > 1 && get_balance(head->left) < 0)
            head = avl_lr_rotation(head);
        // правый левый поворот
        else if (balance < -1 && get_balance(head->left) > 0)
            head = avl_rl_rotation(head);
    }
 
    return head;
}

int avl_create_from_bst(bst_node_t *head, avl_node_t **src)
{
    int rc = OK;
    if (head == NULL)
        rc = WRONG_ARGS;
    else
    {
        if (*src != NULL)
        {
            avl_free_tree(*src);
            *src = NULL;
        }
        bst_traverse(head, add_bst_to_avl, src, "pre");
        if (*src != NULL)
            rc = OK;
        else
            rc = NO_MEMORY;
    }
    
    return rc;
}

void add_bst_to_avl(bst_node_t *node, void *arg)
{
    avl_node_t **avl = arg;

    avl_node_t *tmp = avl_create_node(node->num);
    if (tmp != NULL)
        *avl = avl_add_node(*avl, tmp);
}

void avl_free_node(avl_node_t *node, void *arg)
{
    free(node);
}

void avl_free_tree(avl_node_t *head)
{
    avl_traverse(head, avl_free_node, NULL, "post");
}

