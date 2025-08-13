#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct dir_node
{
	char *dir; /*e.g/usr/local/bin*/
	struct dir_node *next; /*points to the next node*/
} directory;

int main(void)
{
	char *path = getenv("PATH"); /*get the value of PATH*/
	char *value = path;  /* Make a copy of PATH since strtok modifies the string */
  int i = 0;
	directory *head = NULL;
	directory *current; /*copy of head node*/
		
	/*tokenise PATH into directories*/
	char *portion = strtok(value, ":"); /*First token*/
	
	while (portion != NULL)
	{
			/*create a new node to store each directory*/
			directory *new_node = malloc(sizeof(directory));
			if (new_node == NULL)
			{
				perror("malloc");
				free(value);
				return 1;
			}
			
			/*initialise new_node*/
			new_node->dir = strdup(portion); /*store an independent copy of each directory*/
			new_node->next = NULL;
			
			/*Link to linked list*/
			if (head == NULL) /*if list is empty, first node becomes head*/
			{
				head = new_node;
				current = head;
			}
			else
			{
				current->next = new_node; /*link the new node to the list*/
				current = current->next; /*what is this*/
			}
				/*Get next token*/
				portion = strtok(NULL, ":");
	}
	
    /* Print the linked list */
    printf("Directories in PATH:\n");
    current = head;
    while (current != NULL)
    {
        printf("%s\n", current->dir);
        current = current->next;
    }

    /* Free allocated memory */
    current = head;
    while (current != NULL)
    {
        directory *temp = current;
        free(current->dir);
        current = current->next;
        free(temp);
    }

    free(value); /* Free the copy of PATH */
	
	return (0);
}
