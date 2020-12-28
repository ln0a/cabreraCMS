#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "macro.h"
#include "file.h"


// Returns the current line as a string
char *read_line(char filePath[], int lineNumber)
{
    FILE *fp;
	static char line[LINE_SIZE];
	int i = 0;

    fp = fopen(filePath, "r");

    if (fp != NULL) {
		while (fgets(line, LEN(line), fp) != NULL) {
			// Remove whitespace - trim_whitespace should be declare locally
			/* trim_whitespace(line); */
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
void trim_whitespace(char *str)
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


// Compare a specific line in file to tag, return index of item in array if match is found
// and -1 if no match is found
int cmp_str_to_arr(char line[], int tagsLength, int buffer, char tags[tagsLength][buffer])
{
	for (int i = 0; i < tagsLength; i++) {
		// Compare strings
		if (strcmp(line, tags[i]) == 0) {
			/* printf("%d %s\n", i, line); */
			return i;
		}
	}

	return -1;
}


// Loop through file to check for matching tags
void cmp_arr_in_file(char file[], int tagsLength, int buffer, char tags[tagsLength][buffer])
{
	int i = 0;
	int cmp;

	while (read_line(file, i) != NULL) {
		char line[LINE_SIZE + 1] = {0};
		strcpy(line, read_line(file, i));
		trim_whitespace(line);

		cmp_str_to_arr(line, tagsLength, BUFFER_SIZE, tags);

		i++;
	}
}
