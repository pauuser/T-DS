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
    }

    return head;
}

bst_node_t *bst_search_node(bst_node_t *head, int num)
{
    if (head == NULL)
        return NULL;
    else
    {
        if (head->num == num)
            return head;
        else if (num > head->num)
            return bst_search_node(head->right, num);
        else
            return bst_search_node(head->left, num);
    }
}

void bst_traverse(bst_node_t *tree, void (*f)(bst_node_t*, void*), void *arg, char *order)
{
    if (tree == NULL)
        return;

    if (strcmp(order, "pre"))
    {
        f(tree, arg);
        bst_traverse(tree->left, f, arg, order);
        bst_traverse(tree->right, f, arg, order);
    }
    else if (strcmp(order, "in"))
    {
        bst_traverse(tree->left, f, arg, order);
        f(tree, arg);
        bst_traverse(tree->right, f, arg, order);
    }
    else if (strcmp(order, "post"))
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
    if (num == head->num)
    {
        free(head);
        head = NULL;
    }
    while (head != NULL)
    {
        if (num < head->num)
        {
            // если левого сына головы нужно удалить
            if (head->left != NULL && head->left->num == num)
            {
                // удаление левого сына головы
                // если у него только правый сын
                if (head->left->left == NULL && head->left->right != NULL)
                {
                    bst_node_t *tmp = head->left->right;
                    free(head->left);
                    head->left = tmp;
                }
                // если у него только левый сын
                else if (head->left->right == NULL && head->left->left != NULL)
                {
                    bst_node_t *tmp = head->left->left;
                    free(head->left);
                    head->left = tmp;
                }
                // терминальная вершина
                else if (head->left->right == NULL && head->left->left == NULL)
                {
                    free(head->left);
                    head->left = NULL;
                }
                // есть оба сына, ищем максимум в левом сыне
                else
                {
                    bst_node_t *tmp = head->left->left;
                    // если у левого сына нет правых потомков
                    if (tmp->right == NULL)
                    {
                        free(head->right);
                        head->right = tmp;
                    }
                    else
                    {
                        // ищем предпоследний элемент, чтобы в нём затереть указатель
                        while (tmp->right != NULL && tmp->right->right != NULL)
                            tmp = tmp->right;
                        // приделываем укзаатели на сыновей удаляемой вершины
                        tmp->right->right = head->left->right;
                        tmp->right->left = head->left->left;

                        // удаляем вершину
                        free(head->left);

                        // вставляем подготовленную и удаляем ссылку из предпоследнего
                        head->left = tmp->right;
                        tmp->right = NULL;
                    }
                }
            }
            else
                head = head->left;
        }
        else
        {
            // если правый сын головы надо удалить
            if (head->right != NULL && head->right->num == num)
            {
                // удаление правого
                // есть только правый сын
                if (head->right->left == NULL && head->right->right != NULL)
                {
                    bst_node_t *tmp = head->right->right;
                    free(head->right);
                    head->right = tmp;
                }
                // есть только левый сын
                else if (head->right->right == NULL && head->right->left != NULL)
                {
                    bst_node_t *tmp = head->right->left;
                    free(head->right);
                    head->right = tmp;
                }
                // терминальная вершина
                else if (head->right->right == NULL && head->right->left == NULL)
                {
                    free(head->right);
                    head->right = NULL;
                }
                // есть оба сына, тогда ищем максимум в левом сыне
                else
                {
                    bst_node_t *tmp = head->right->left;
                    // если у левого сына нет правых потомков
                    if (tmp->right == NULL)
                    {
                        free(head->right);
                        head->right = tmp;
                    }
                    else
                    {
                        // ищем предпоследний элемент, чтобы в нём затереть указатель
                        while (tmp->right != NULL && tmp->right->right != NULL)
                            tmp = tmp->right;
                        // приделываем укзаатели на сыновей удаляемой вершины
                        tmp->right->right = head->right->right;
                        tmp->right->left = head->right->left;

                        // удаляем вершину
                        free(head->right);

                        // вставляем подготовленную и удаляем ссылку из предпоследнего
                        head->right = tmp->right;
                        tmp->right = NULL;
                    }
                }
            }
            else
                head = head->right;
        }
    }

    return head;
}
