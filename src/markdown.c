#include <stdlib.h>
#include <stdio.h>
#include <cmark.h>

#include "strings.h"
#include "projects.h"

#include "markdown.h"



// Convert markdown formatted text to html
int md_to_html(int index)
{
	projectsArr[index].html = cmark_markdown_to_html(projectsArr[index].text, WORD_LENGTH, 0);
	printf("%s", projectsArr[index].html);

	return 0;
}
