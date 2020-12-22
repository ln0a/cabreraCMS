#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "content.h"
#include "macro.h"
#include "file.h"
#include "projects.h"
#include "directory.h"
#include "strings.h"
#include "markdown.h"


// Reads description.txt for project description
int gen_description(int index)
{
	// create description.txt path
	int fileCount = 0;
	char path[BUFFER_SIZE][PATH_LENGTH + 1];
	// Initialise paths
	for (int i = 0; i < LEN(path); i++) {
		strcpy(path[i], projectsArr[index].path);
	}

	// check project directory for description text file
	char dirContent[BUFFER_SIZE][WORD_LENGTH];
	explore_directory(projectsArr[index].path, LEN(dirContent), WORD_LENGTH, dirContent);
	char textFileNames[4][WORD_LENGTH] = {{"description.md"}, {"description.txt"},
										  {"text.md"}, {"text.txt"}};

	// Find file name match
	for (int i = 0; i < LEN(dirContent); i++) {
		for (int j = 0; j < LEN(textFileNames); j++) {
			// Strings match
			if (strcmp(dirContent[i], textFileNames[j]) == 0) {
				fileCount++; // increment found text file counter
				strcat(path[fileCount], textFileNames[j]);
				break;
			}
		}
	}

	// Send error if file not found
	if (fileCount == 0) {
		printf("No description file found.");
		return 1;
	}

	// Read file
	int i = 0;
	char line[TEXT_LENGTH + 1] = {0};
	fileCount = 1; // hacky reset to description.md

	while (read_line(path[fileCount], i) != NULL) {
		strcat(line, read_line(path[fileCount], i));
		i++;
	}

	// Copy full description into project structure
	projectsArr[index].text = line;

	// Split description text NOT NEEDED
	/* split_description(index, LEN(line), line); */

	for (int i = 0; i < LEN(projectsArr[index].textSplit[i]); i++)
		printf("%s ", projectsArr[index].textSplit[i]);
	printf("\n");


	// Convert md to html
	md_to_html(index);


	return 0;
}


// Split description text into array of strings
int split_description(int index, int n, char text[n])
{
	char** tokens;
	tokens = str_split(text, ' ');

	if (tokens) {
		for (int i = 0; *(tokens + i); i++) {
			strcpy(projectsArr[index].textSplit[i], *(tokens + i));
			free(*(tokens + i));
		}

		free(tokens);
	}

	return 0;
}
