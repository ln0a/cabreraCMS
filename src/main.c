#include <stdio.h>
#include "main.h"


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

	printf("\n%d tags available.\n\n", LEN(template_tags));


	// Read each line in a file individually until EOF
	printf("Matched tags:\n");
	cmp_arr_in_file(inFile, LEN(template_tags), BUFFER_SIZE, template_tags);
	printf("\n");


	gen_projects();

	return 0;
}
