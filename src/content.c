#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "content.h"
#include "macro.h"
#include "file.h"
#include "projects.h"
#include "strings.h"


// Reads description.txt for project description
int gen_description(int index)
{
	char line[TEXT_LENGTH + 1] = {0};

	// create description.txt path
	char path[PATH_LENGTH + 1];
	strcpy(path, projectsArr[index].path);
	strcat(path, "description.md");
	/* strcat(path, "text.md"); */

	// read file
	int i = 0;
	while (read_line(path, i) != NULL) {
		// copy string into project structure
		strcat(line, read_line(path, i));
		i++;
	}

	/* printf("%s\n", line); */

	// Split description text
	split_description(index, LEN(line), line);

	for (int i = 0; i < BUFFER_SIZE; i++)
		printf("%s ", projectsArr[index].text[i]);
	printf("\n");

	return 0;
}


// Split description text into array of strings
int split_description(int index, int n, char text[n])
{
	char** tokens;
	tokens = str_split(text, ' ');

	if (tokens) {
		for (int i = 0; *(tokens + i); i++) {
			strcpy(projectsArr[index].text[i], *(tokens + i));
			free(*(tokens + i));
		}

		free(tokens);
	}

	return 0;
}
