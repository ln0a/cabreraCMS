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
int explore_directory(char path[], int buffer, int n, char arr[buffer][n])
{
	struct dirent *item;

	DIR *dir = opendir(path);

	if (dir == NULL) {
		printf("Could not open the current directory.");
		return 1;
	}

	int i = 0;
	while ((item = readdir(dir)) != NULL) {
		// Add directories to array
		strcpy(arr[i], item->d_name);
		i++;
	}

	closedir(dir);
	return 0;
}


// Remove ignored items from directory list
int clean_dir_list(int inLen, int ignoredLen, int outLen, int buffer,
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

	return 0;
}


// Search directory, generate project list array and clean
int gen_clean_dir(char path[], int buffer, int n, char dirListOut[buffer][n])
{
	char dirListFull[BUFFER_SIZE][WORD_LENGTH];

	explore_directory(path, LEN(dirListFull), WORD_LENGTH, dirListFull);
	clean_dir_list(LEN(dirListFull), LEN(ignoredItems), n, WORD_LENGTH,
				 dirListFull, ignoredItems, dirListOut);

	return 0;
}
