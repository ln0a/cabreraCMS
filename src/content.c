#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "file.h"
#include "projects.h"
#include "directory.h"
#include "strings.h"
#include "markdown.h"

#include "content.h"


// Reads description.txt for project description
int gen_description(int index)
{
	// create description.txt path
	int fileCount = 0;
	char path[BUFFER_SIZE][PATH_LENGTH + 1];
	// Initialise paths
	for (int i = 0; i < LEN(path); i++) {
		strcpy(path[i], ProjectsArr[index].path);
	}

	// check project directory for description text file
	char dirContent[BUFFER_SIZE][WORD_LENGTH];
	explore_directory(ProjectsArr[index].path, LEN(dirContent), WORD_LENGTH, dirContent);
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

	// Copy read file into line
	while (read_line(path[fileCount], i) != NULL) {
		strcat(line, read_line(path[fileCount], i));
		i++;
	}

	// Copy full description into project structures char*
	ProjectsArr[index].text = line;

	// Convert md to html
	md_to_html(ProjectsArr[index].text, strlen(ProjectsArr[index].text),
			   &ProjectsArr[index].textHTML);

	return 0;
}


// Reads data.txt for project description
int gen_data(int index)
{
	// create description.txt path
	int fileCount = 0;
	char path[BUFFER_SIZE][PATH_LENGTH + 1];
	// Initialise paths
	for (int i = 0; i < LEN(path); i++) {
		strcpy(path[i], ProjectsArr[index].path);
	}

	// check project directory for description text file
	char dirContent[BUFFER_SIZE][WORD_LENGTH];
	explore_directory(ProjectsArr[index].path, LEN(dirContent), WORD_LENGTH, dirContent);
	char textFileNames[4][WORD_LENGTH] = {{"data.md"}, {"data.txt"}};

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
	fileCount = 1; // hacky reset to data.md

	// Copy read file into line
	while (read_line(path[fileCount], i) != NULL) {
		strcat(line, read_line(path[fileCount], i));
		i++;
	}

	// Copy full description into project structures char*
	ProjectsArr[index].data = line;

	// Convert md to html
	md_to_html(ProjectsArr[index].data, strlen(ProjectsArr[index].data),
			   &ProjectsArr[index].dataHTML);

	return 0;
}


// Fill projects with file paths of images
int gen_visual_content(int index)
{
	int count = 0;

	char path[PATH_LENGTH] = {0};
	strcat(path, ProjectsArr[index].path);
	strcat(path, "img/");

	char directoryContents[VISUAL_BUFFER][PATH_LENGTH] = {0};
	gen_clean_dir(path,
				  LEN(directoryContents), LEN(directoryContents[0]), directoryContents);


	for (int i = 0; i < LEN(directoryContents); i++) {
		char fullFilename[WORD_LENGTH];
		strcpy(fullFilename, directoryContents[i]);

		char splitFilename[2][WORD_LENGTH] = {0};
		split_filename(index, i, LEN(directoryContents[i]), directoryContents[i],
					   LEN(splitFilename), LEN(splitFilename[i]), splitFilename);

		// Check if format matches text files and skip
		if (strcmp(splitFilename[1], "txt") == 0 ||
			strcmp(splitFilename[1], "org") == 0 ||
			strcmp(splitFilename[1], "html") == 0 ||
			strcmp(splitFilename[1], "md") == 0
			) {}
		else {
			// Check for image formats
			if (strcmp(splitFilename[1], "jpg") == 0 ||
				strcmp(splitFilename[1], "jpeg") == 0 ||
				strcmp(splitFilename[1], "png") == 0 ||
				strcmp(splitFilename[1], "gif") == 0
				) {
				// Copy full file name in project
				strcpy(ProjectsArr[index].VisualContentArr[count].filename, fullFilename);

				count++;
			}
		}
	}

	// Store the count of visual content into project
	ProjectsArr[index].visualContentCount = count;

	return 0;
}


// Split filename by '.'
int split_filename(int index, int j, int m, char filename[m],
				   int n, int buffer, char outArr[n][buffer])
{
	char** tokens;
	tokens = str_split(filename, '.');

	if (tokens) {
		for (int i = 0; *(tokens + i); i++) {
			strcpy(outArr[i], *(tokens + i));
			free(*(tokens + i));
		}

		free(tokens);
	}

	return 0;
}
