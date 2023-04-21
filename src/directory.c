#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#include "macro.h"

#include "directory.h"


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
int explore_directory(char path[], int n, int buffer, char arr[n][buffer])
{
	struct dirent *item;

	DIR *dir = opendir(path);

	if (dir == NULL) {
		printf("Could not open the current directory: %s.", path);
		return 1;
	}

	int i = 0;
	while ((item = readdir(dir)) != NULL && i < n) {
		// Add directories to array
		strcpy(arr[i], item->d_name);
		i++;
	}

	closedir(dir);

	if (i > 1) {
		qsort(arr, i, sizeof(arr[0]), compare_pointers);
	}


	return 0;
}


static int compare_pointers(const void *p, const void *q)
{
	const char *l = p;
	const char *r = q;
	int cmp;

	cmp = strcmp(l, r);

	return cmp;
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
int gen_clean_dir(char path[], int n, int buffer, char dirListOut[n][buffer])
{
	char dirListFull[BUFFER_SIZE][WORD_LENGTH] = {0};

	explore_directory(path, LEN(dirListFull), WORD_LENGTH, dirListFull);
	clean_dir_list(LEN(dirListFull), LEN(ignoredItems), buffer, WORD_LENGTH,
				 dirListFull, ignoredItems, dirListOut);

	return 0;
}
