#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "directory.h"
#include "macro.h"

/*********************************************\

  DIRECTORY STRUCTURE (2 LEVELS):

  projects               >  project1  >  .txt
  { self-defined: }         project2     .img
  about                     project3     .png
  contact                   ...          .mp4
  etc.                      ...          ...
  { ignore following: }     ...
  src
  templates
  cabreraCMS

\********************************************/



// Explore directory structure and add to array
int exploreDirectory(char path[], int buffer, int n, char arr[buffer][n])
{
	struct dirent *item;

	DIR *dir = opendir(path);

	if (dir == NULL) {
		printf("Could not open the current directory.");
		return 0;
	}

	int i = 0;
	while ((item = readdir(dir)) != NULL) {
		// Add directories to rootDirList array
		strcpy(arr[i], item->d_name);
		i++;
	}

	closedir(dir);
	return 1;
}


// Remove ignored items from directory list
int cleanDirList(int inLen, int ignoredLen, int outLen, int buffer,
				 char arrIn[inLen][buffer],
				 char arrIgnored[ignoredLen][buffer],
				 char arrOut[outLen][buffer])
{
	int index, k = 0;

	for (int i=0; i < inLen; i++) {
		index = 0;
		for (int j=0; j < ignoredLen; j++) {
			if (strcmp(arrIn[i], arrIgnored[j]) != 0) {
				// Strings are not the same
				index++;
			}
		}

		// No match has been found
		if (index == ignoredLen) {
			strcpy(arrOut[k], arrIn[i]);
			k++;
		}
	}

	return 1;
}


// Search directory, generate project list array and clean
int cleanDirectory(char path[], int buffer, int n, char dirListOut[buffer][n])
{
	char dirListFull[BUFFER_SIZE][WORD_LENGTH];

	exploreDirectory(path, LEN(dirListFull), WORD_LENGTH, dirListFull);
	cleanDirList(LEN(dirListFull), LEN(ignoredItems), n, WORD_LENGTH,
				 dirListFull, ignoredItems, dirListOut);

	return 1;
}
