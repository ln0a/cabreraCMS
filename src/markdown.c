#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmark.h>

#include "projects.h"

#include "markdown.h"



// Convert markdown formatted text to html
int md_to_html(char *input, int inputLen, char **output)
{
	*output = cmark_markdown_to_html(input, strlen(input), 0);

	return 0;
}
