#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "main.h"


int main(int argc, char *argv[])
{
	int opt;
	char *inputFile = defaultInputFile;
	char *outputFile = defaultOutputFile;
	char *help =
		"CabreraCMS Version 0.1\n"
		"\n"
		"Usage: cabreraCMS [option1] [file1] [option2] [file2] [options...]\n"
		"\n"
		"Options:\n"
		"-i <file> define template filename (defaults to templates/index_template.html)\n"
		"-o <file> define output filename (defaults to index.html)\n"
		"-v        view verbose output\n"
		"-h        see this help page again\n";


	// Go through program arguments
	while ((opt = getopt(argc, argv, "i:o:vh")) != -1) {
		switch(opt) {
			case 'i':
				inputFile = optarg;
				break;
			case 'o':
				outputFile = optarg;
				break;
			case 'v':
				verboseMode = 1;
				break;
			case 'h':
			default:
				printf("%s", help);
				break;
		}
	}


	// Check what template tags are available
	index_template_tags(inputFile);

	// Generate projects structures and fill with content
	gen_projects();

	// Build html file from template file
	gen_html_from_template(strlen(inputFile), inputFile, strlen(outputFile), outputFile,
						   LEN(templateTags), BUFFER_SIZE, templateTags);


	return 0;
}
