#include "markdown.h"


// Convert markdown formatted text to html
int md_to_html(int n, char line[n][WORD_LENGTH + 1])
{
	convert_md_link_to_html();

	return 0;
}


// Convert links into html format
int convert_md_link_to_html()
{
	// <a> tag deliniator
	char aTag[5][WORD_LENGTH] = {{"<a href="}, {"\""}, {"\""}, {">"}, {"</a>"}};
	// md link deliniaor
	char mdTag[3][8] = {{"("}, {")["}, {"]"}};

	return 0;
}
