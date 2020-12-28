#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cmark.h>

#include "projects.h"

#include "markdown.h"



// Convert markdown formatted text to html
int md_to_html(int index)
{
	ProjectsArr[index].html = cmark_markdown_to_html(ProjectsArr[index].text, strlen(ProjectsArr[index].text), 0);
	/* printf("%s", ProjectsArr[index].html); */

	return 0;
}
