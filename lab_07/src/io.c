#include "../inc/io.h"

/*
Функция заполнения графа с клавиатуры
Выход: граф
*/
graph_t *input_graph(void)
{
    int V = 0, E = 0;

    // Ввод числа вершин
    printf("Input number of nodes. V = ");
    while (scanf("%d", &V) != 1 || V < 2)
    {
        clean_stdin();
        printf("Incorrent input! V = ");
    }

    // Ввод числа граней
    printf("Input number of edges. E = ");
    while (scanf("%d", &E) != 1 || E < 1)
    {
        clean_stdin();
        printf("Incorrent input! E = ");
    }

    // Инициализация графа
    graph_t *graph = create_graph(V, E);

    printf("Input edges of the graph. Nodes must belong to [0, V - 1].\n");
    
    // Чтение граней
    int read = 0;
    while (read < E)
    {
        int rc1 = 0, rc2 = 0;
        int beg = 0, end = 0;

        printf("Input beginning: ");
        rc1 = scanf("%d", &beg);
        if (rc1 == 1 && beg > -1 && beg < V)
        {
            printf("Input ending: ");
            rc2 = scanf("%d", &end);
            if (rc2 == 1 && end > -1 && end < V)
            {
                printf("Success! Read %d edges.\n", read + 1);
                graph->edge[read].src = beg;
	            graph->edge[read].dest = end;
                read++;
            }
            else
            {
                printf("Wrong input!\n");
                clean_stdin();
            }

        }
        else
        {
            printf("Wrong input!\n");
            clean_stdin();
        }
    }

    return graph;
}

/*
Функция чтения мусора из потока ввода
*/
void clean_stdin()
{
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

/*
Преобразование вершин рёбер в текст
*/
void graph_to_dot(graph_t *tree, void *param)
{
    FILE *f = param;
    for (int i = 0; i < tree->E; i++)
    {
        fprintf(f, "%d -> %d [dir=none];\n", tree->edge[i].src, tree->edge[i].dest);
    }
}

/*
Экспорт графа в формат dot
*/
void graph_export_to_dot(FILE *f, const char *tree_name, graph_t *graph)
{
    fprintf(f, "digraph %s {\n", tree_name);

    graph_to_dot(graph, f);

    fprintf(f, "}\n");
}

/*
Вывод dot в файл
*/
void graph_output_dot(graph_t *graph)
{
    if (graph == NULL)
        printf("No tree yet!\n");
    else
    {
        FILE *file = fopen("graph.gv", "w");

        graph_export_to_dot(file, "Graph", graph);

        fclose(file);

        system("./build_graph.bat");
        system("start \"1.png\"");
    }
}

/*
Печать приветственного сообщения
*/
void print_welcome()
{
    printf("Welcome! This programme perfoms operations on\n");
    printf("connected graphs and check, how many edges should be\n");
    printf("removed to make graph disconnected by minimum loss.\n");
    printf("In other words, this programme solves the min-cut problem.\n");
}

/*
Меню
*/
void print_menu()
{
    printf("\n+-----------------------------------------------------------+\n");
    printf("| Choose your option!                                       |\n");
    printf("|                                                           |\n");
    printf("| 1  - Input graph                                          |\n");
    printf("| 2  - Open graph image                                     |\n");
    printf("| 3  - See how many edges to delete to disconnect the graph |\n");
    printf("| 0  - Exit                                                 |\n");
    printf("+-----------------------------------------------------------+\n");
    printf("\nYour choice: ");
}
