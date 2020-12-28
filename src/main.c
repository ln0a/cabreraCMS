#include <stdio.h>
#include "main.h"


int main(void)
{
	char inFile[] = "templates/index_template.html";
	char outFile[] = "cabrera.html";


	// Check what template tags are available
	index_template_tags(inFile);

	// Generate projects structures and fill with content
	gen_projects();

	// Build html file from template file
	gen_html_from_template(LEN(inFile), inFile, LEN(outFile), outFile,
						   LEN(templateTags), BUFFER_SIZE, templateTags);

	return 0;
}
