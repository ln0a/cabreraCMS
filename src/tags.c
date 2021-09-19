#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "projects.h"
#include "file.h"
#include "strings.h"

#include "tags.h"


// Generate project tags
int gen_project_tags(int index)
{
	char** tokens;

	char tagsFile[] = "tags.md";
	char path[PATH_LENGTH];

	char tagsStr[LINE_SIZE];
	char projectTags[100][WORD_LENGTH] = {0};

	// Concatonate project path with tag file path
	strcpy(path, ProjectsArr[index].path);
	strcat(path, tagsFile);

	// Read tags file and split tags by deliminator ','
	strcpy(tagsStr, read_line(path, 0));
	tokens = str_split(tagsStr, ',');

	if (tokens) {
		for (int i = 0; *(tokens + i); i++) {
			int duplicate = 0;

			// Add tag to local project tags array
			strcpy(ProjectsArr[index].tags[i], *(tokens + i));
			trim_whitespace(ProjectsArr[index].tags[i]);
			ProjectsArr[index].tagsCount++;

			// Loop though global tags to find duplicates
			for (int j = 0; j < LEN(globalTags); j++) {
				char tempTag[WORD_LENGTH];
				strcpy(tempTag, *(tokens + i));
				trim_whitespace(tempTag);

				// A duplicate is found
				if (strcmp(globalTags[j], tempTag) == 0) {
					duplicate = 1;
				}
			}

			// If there are no duplicates then add tag
			if (duplicate == 0) {
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
