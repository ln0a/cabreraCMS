#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tags.h"
#include "macro.h"
#include "projects.h"
#include "file.h"
#include "strings.h"


// Generate project tags
int gen_project_tags(int index)
{
	char** tokens;

	char tagsFile[] = "tags.txt";
	char path[PATH_LENGTH];

	char tagsStr[LINE_SIZE];
	char projectTags[10][WORD_LENGTH] = {0};

	// Concatonate project path with tag file path
	strcpy(path, projectsArr[index].path);
	strcat(path, tagsFile);

	// Read tags file and split tags by deliminator ','
	strcpy(tagsStr, read_line(path, 0));
	tokens = str_split(tagsStr, ',');

	if (tokens) {
		for (int i = 0; *(tokens + i); i++) {
			int duplicate = 0;

			// Add tag to local project tags array
			strcpy(projectsArr[index].tags[i], *(tokens + i));
			trim_whitespace(projectsArr[index].tags[i]);

			// Loop though global tags to find duplicates
			for (int j = 0; j < LEN(globalTags); j++) {
				// A duplicate is found
				if (strcmp(globalTags[j], *(tokens + i)) == 0) {
					duplicate = 1;
				}
			}

			// If there are no duplicates then add tag
			if (!duplicate) {
				strcpy(globalTags[globalTagNum], *(tokens + i));
				trim_whitespace(globalTags[globalTagNum]);
				globalTagNum++;
			}

			free(*(tokens + i));
		}

		free(tokens);
	}

	return 0;
}
