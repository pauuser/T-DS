#include <stdio.h>
#include <stdlib.h>

#include "../inc/karger.h"
#include "../inc/io.h"

int main(void)
{
    setbuf(stdout, NULL);
	print_welcome();

    // Ввод графа
	graph_t *graph = NULL;

    int choice = -1;
	do
	{
		print_menu();
		if (scanf("%d", &choice) != 1)
		{
			printf("Wrong input!\n");
			clean_stdin();
		}
		else if (choice == 1)
		{
			if (graph)
				graph_free(&graph);

			graph = input_graph();
		}
		else if (choice == 2)
		{
			if (graph)
				graph_output_dot(graph);
			else
				printf("No graph!\n");
		}
		else if (choice == 3)
		{
			if (graph)
				karger(graph);
			else
				printf("No graph!\n");
		}
		else if (choice != 0)
			printf("Wrong input!\n");
	} 
	while (choice != 0);

	graph_free(&graph);	

	return 0;
}