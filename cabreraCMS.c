#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_SIZE 512
#define LINE_SIZE 512
#define LEN(arr) ((int) (sizeof (arr) / sizeof (arr)[0]))

char *readLine(char filePath[], int lineNumber);
void trimwhitespace(char *str);
int compareLineToTags(char line[], int tagsLength, int buffer, char tags[tagsLength][buffer]);



int main(void)
{
	char inFile[] = "templates/index_template.html";
	char outFile[] = "projects/test_project_3/out.txt";

	char template_tags[][BUFFER_SIZE] = {
		"<ul id=\"projects_container\">",
		"<ul id=\"projects_tags\">",
		"<li id=\"NAME_OF_PROJECT\" class=\"project\">",
		"<ul id=\"project_tags\">",
		"<ul id=\"project_gallery\">",
	};
	int tagsLength = LEN(template_tags);

	printf("\n\n%d tags available.\n\n", tagsLength);


	// Read each line in a file individually until EOF
	int i = 0;
	while (readLine(inFile, i) != NULL) {
		compareLineToTags(readLine(inFile, i), tagsLength, BUFFER_SIZE, template_tags);
		i++;
	}

	return 0;
}


// Returns the current line as a string
char *readLine(char filePath[], int lineNumber)
{
    FILE *fp;
	static char line[LINE_SIZE];
	int i = 0;

    fp = fopen(filePath, "r");

    if (fp != NULL) {
		while (fgets(line, LEN(line), fp) != NULL) {
			// Remove whitespace
			trimwhitespace(line);
			if (i == lineNumber) {
				fclose(fp);
				return line; // Return desired line
			}
			else {
				i++;
			}
		}
		fclose(fp);
    }
    else {
        printf("File cannot be opened\n");
    }

	return 0;
}


// Trim the leading / trailing whitespace of a string
void trimwhitespace(char *str)
{
    int index, i;

	// Trim leading white spaces
    index = 0;
    while(str[index] == ' ' || str[index] == '\t' || str[index] == '\n') {
        index++;
    }

    // Shift all trailing characters to its left
    i = 0;
    while(str[i + index] != '\0') {
        str[i] = str[i + index];
        i++;
    }
    str[i] = '\0'; // Terminate string with NULL

	// Trim trailing white spaces
    i = 0;
    index = -1;
    while(str[i] != '\0') {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n') {
            index = i;
        }
        i++;
    }

    // Mark the next character to last non white space character as NULL
    str[index + 1] = '\0';
}


// Compare a specific line in file to tag
int compareLineToTags(char line[], int tagsLength, int buffer, char tags[tagsLength][buffer])
{
	for (int i=0; i < tagsLength; i++) {
		// Compare strings
		if (strcmp(line, tags[i]) == 0) {
			printf("success %d %s\n", i, line);
			return 1;
		}
		else {
			printf("        %d %s\n", i, line);
		}
	}

	return 0;
}
