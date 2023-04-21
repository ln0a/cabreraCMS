#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "macro.h"
#include "file.h"
#include "projects.h"
#include "tags.h"
#include "strings.h"
#include "html.h"

#include "template.h"



// Generate the output html file from template.html and project structs
int gen_html_from_template(int m, char templatePath[m], int n, char outputPath[n], int projectIndex)
{
	FILE *output;

	char outputHTML[TEXT_LENGTH] = {0};

	// Open working files
	output = fopen(outputPath, "w");

	// Loop through template file
	int i = 0;
	while (read_line(templatePath, i) != NULL) {
		char line[LINE_SIZE] = {0};
		strcpy(line, read_line(templatePath, i));
		trim_whitespace(line);

		char *cmsTagString;
		if (parse_html_tag(line, &cmsTagString) == 1) {
		}
		else {
			cmsTagString = "";
		}

		// Check if line contains a template tag
		int templateTagIndex;
		templateTagIndex = cmp_str_to_arr(cmsTagString,
										  LEN(templateTags), BUFFER_SIZE, templateTags);

		if (templateTagIndex != -1) {
			switch (templateTagIndex) {
				// projects_index
				case 0:
					strcat(outputHTML, "<ul class=\"projects_index\">\n");

					for (int i = projectsCount - 1; i > 0; i--) {
						/* printf("%s %s\n", ProjectsArr[i].date.dateStr, ProjectsArr[i].title); */

						strcat(outputHTML, "<a id=\"");
						strcat(outputHTML, ProjectsArr[i].hyphenatedTitle);
						strcat(outputHTML, "\" class=\"project_item\" href=\"");
						/* strcat(outputHTML, ProjectsArr[i].hyphenatedTitle); */
						strcat(outputHTML, ProjectsArr[i].path);
						strcat(outputHTML, "\">\n");

						strcat(outputHTML, "<li class=\"title\">");
						strcat(outputHTML, ProjectsArr[i].unhyphenatedTitle);
						strcat(outputHTML, "</li>\n");

						strcat(outputHTML, "<li class=\"date\">");
						strcat(outputHTML, ProjectsArr[i].date.dateStr);
						strcat(outputHTML, "</li>\n");

						strcat(outputHTML, "</a>\n");

					}

					strcat(outputHTML, "</ul>\n");

					break;

				// projects_tags
				case 1:
					strcat(outputHTML, "<ul class=\"projects_tags\">\n");

					// copy global tags into output
					for (int i = 0; i < globalTagNum; i++) {
						strcat(outputHTML, "<li project-tag=\"");
						strcat(outputHTML, globalTagsHyphenated[i]);
						strcat(outputHTML, "\">");
						strcat(outputHTML, globalTags[i]);
						strcat(outputHTML, "</li>\n");
					}

					strcat(outputHTML, "</ul>");

					break;

				// projects_gallery
				case 2:
					strcat(outputHTML, "<ul class=\"projects_gallery\">\n");

					for (int i = 0; i < projectsCount; i++) {
						char content[TEXT_LENGTH] = {0};

						gen_html_gallery_item(i, LEN(content), content);
						strcat(outputHTML, content);
					}

					strcat(outputHTML, "</ul>\n");

					break;

				// project
				case 3:
					// Single file mode
					if (outputMode == 0) {
						// loop through all projects
						for (int i = 0; i < projectsCount; i++) {
							char content[TEXT_LENGTH] = {0};

							strcat(outputHTML, "<li id=\"");
							strcat(outputHTML, ProjectsArr[i].hyphenatedTitle);
							strcat(outputHTML, "\" class=\"project\">");
							strcat(outputHTML, "\n");

							gen_html_project_item(i, LEN(templateTagsIndex), templateTagsIndex,
												LEN(content), content);
							strcat(outputHTML, content);

							strcat(outputHTML, "</li>\n");
						}
					}
					// Multi file Mode
					else {
						char content[TEXT_LENGTH] = {0};

						strcat(outputHTML, "<li id=\"");
						strcat(outputHTML, ProjectsArr[i].hyphenatedTitle);
						strcat(outputHTML, "\" class=\"project\">");
						strcat(outputHTML, "\n");

						gen_html_project_item(projectIndex, LEN(templateTagsIndex), templateTagsIndex,
											LEN(content), content);
						strcat(outputHTML, content);

						strcat(outputHTML, "</li>\n");
					}

					break;

				// project_gallery
				case 6:
					strcat(outputHTML, "<ul id=\"project_gallery\">\n");

					char content[TEXT_LENGTH] = {0};
					gen_html_gallery_item(projectIndex, LEN(content), content);
					strcat(outputHTML, content);

					strcat(outputHTML, "</ul>\n");
					break;

				default:
					break;
			}

		}
		else {
			// Concat current line onto outputHTML
			strcat(outputHTML, line);
		}

		i++;
	}


	// Copy outputHTML into output file
	fprintf(output, "%s", outputHTML);

	// Close files
	fclose(output);

	return 0;
}


// Generate html output of project based on available tags
int gen_html_project_item(int index, int n, int tagsIndex[n], int buffer, char output[buffer])
{
	for (int i = 0; i < n; i++) {
		switch (i) {
			// project_tags
			case 4:
				if (tagsIndex[i] == 1) {
					strcat(output, "<ul class=\"project_tags\">\n");

					for (int j = 0; j < ProjectsArr[index].tagsCount; j++) {
						strcat(output, "<li project-tag=\"");
						strcat(output, ProjectsArr[index].tagsHyphenated[j]);
						strcat(output, "\">");
						strcat(output, ProjectsArr[index].tags[j]);
						strcat(output, "</li>\n");
					}

					strcat(output, "</ul>\n");
				}

				break;

			// project_text
			case 5:
				if (tagsIndex[i] == 1) {
					strcat(output, "<ul class=\"project_text\">\n");

					strcat(output, "<div class=\"description\">\n");
					strcat(output, ProjectsArr[index].textHTML);
					strcat(output, "</div>\n");

					strcat(output, "<ul class=\"data\">\n");
					strcat(output, ProjectsArr[index].dataHTML);
					strcat(output, "</ul>\n");

					strcat(output, "</ul>\n");
				}
				break;

		}
	}

	return 0;
}


int gen_html_gallery_item (int index, int buffer, char output[buffer])
{

	strcat(output, "<ul id=\"");
	strcat(output, ProjectsArr[index].hyphenatedTitle);
	strcat(output, "\" class=\"project_gallery\">\n");

	for (int i = 0; i < ProjectsArr[index].visualContentCount; i++) {
		strcat(output, "<li id=\"");
		strcat(output, ProjectsArr[index].VisualContentArr[i].file);
		strcat(output, "\" class=\"image_wrapper\">\n");

		strcat(output, "<img src=\"");
		strcat(output, ProjectsArr[index].path);
		strcat(output, "img/");
		strcat(output, ProjectsArr[index].VisualContentArr[i].filename);
		strcat(output, "\" loading=\"lazy\">\n");

		strcat(output, "<p>");
		strcat(output, ProjectsArr[index].VisualContentArr[i].filename);
		strcat(output, "</p>\n");

		strcat(output, "</li>\n");
	}

	strcat(output, "</ul>\n");

	return 0;
}


// Loop through template file and declare if tag exists with 1 or 0
// in templateTagsIndex global array
void index_template_tags(char *template)
{
	int i = 0;
	int cmp;

	char *cmsTagString = "";
	char **tokens;

	// Loop through template file
	while (read_line(template, i) != NULL) {
		// Reset line string on each loop
		char line[LINE_SIZE + 1] = {0};

		strcpy(line, read_line(template, i));
		trim_whitespace(line);

		if (parse_html_tag(line, &cmsTagString) == 1) {
		}
		else {
			cmsTagString = "";
		}
		/* printf("%s\n", cmsTagString); */

		// Returns index of item in array that matches string
		// -1 if not matched
		cmp = cmp_str_to_arr(cmsTagString, LEN(templateTags), BUFFER_SIZE, templateTags);

		// Loop through template tags
		for (int j = 0; j < LEN(templateTagsIndex); j++) {
			// index matches
			if (cmp == j) {
				templateTagsIndex[j] = 1;
			}
		}

		i++;
	}

	/* for (int i = 0; i < LEN(templateTagsIndex); i++) { */
	/* 	printf("%d ", templateTagsIndex[i]); */
	/* } */
	/* printf("%d\n", LEN(templateTagsIndex)); */
}
