#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tidy.h>
#include <tidybuffio.h>

#include "macro.h"
#include "file.h"
#include "strings.h"

#include "macro.h"

#include "html.h"



// Parses HTML tag to find cms tag
// Returns 1 if match found and -1 if no match found
int parse_html_tag(char* element, char **cmsTagString) {
	struct HTML_Tag Tag;
	Tag = EmptyTag;

	strcpy(Tag.string, element);

	clean_html_tag(WORD_LENGTH, Tag.string, Tag.cleanString);
	Tag.attributeCount = parse_html_components(WORD_LENGTH, LEN(Tag.attributes),
											   Tag.cleanString,
											   Tag.htmlTag, Tag.attributes);

	// Only pass tags with attibutes: class, tags, etc.
	if (Tag.attributeCount > 0) {
		for (int i = 0; i < Tag.attributeCount; i++) {
			int tagMatch = parse_html_tag_attribute(Tag.attributes[i], &Tag.tagString);

			if (tagMatch == 1) {
				/* printf("success %s", Tag.tagString); */
				*cmsTagString = Tag.tagString;
				return 1;
			}

			/* printf(" %s ", Tag.attributes[i]); */
		}

		/* printf("\n"); */
	}

	return -1;
}

// Clean tag deliminators for HTML tag
int clean_html_tag(int buffer, char string[buffer], char cleanString[buffer]) {
	int i = 0;
	int j = 0;

	if (string[i] == tagDelim[0]) {
		// Check if not a closing tag </ >
		if (string[i+1] != tagClose) {
			// Loop until >
			while (string[i] != tagDelim[1]) {
				// Don't copy <
				if (string[i] == tagDelim[0]) {

					i++;
				} else {
					cleanString[j++] = string[i++];
				}
			}
		}
	}

	/* printf("%s\n", cleanString); */

	return 0;
}

// Split up HTML tag components into ID and attributes array
// Returns component count
int parse_html_components(int buffer, int x,
						  char input[buffer],
						  char id[buffer], char attributes[x][buffer]) {
	int j = 0;

	char tempString[WORD_LENGTH] = {0};

	char** tokens;
	tokens = str_split(input, ' ');

	if (tokens) {
		for (int i = 0; *(tokens + i); i++) {
			// Tag ID
			if (i == 0) {
				strcpy(id, *(tokens + i));
			}
			else {
				strcpy(tempString, *(tokens + i));
				trim_whitespace(tempString);

				strcpy(attributes[j], tempString);
				j++;
			}

			free(*(tokens + i));
		}

		free(tokens);
	}

	return j;
}

// Find HTL tag attributes that match to 'tag'
// Modifies tagString pointer
// Returns 1 if matched
int parse_html_tag_attribute(char *attr, char **tagString) {
	char** tokens;
	tokens = str_split(attr, '=');

	if (tokens) {
		for (int i = 0; *(tokens + i); i++) {
			if (strcmp(*(tokens + i), "tag") == 0) {
				char *tag;
				tag = *(tokens + i + 1);

				trim_quotes(tag);
				*tagString = tag;

				/* printf("%s\n", tag); */

				free(*(tokens + i));
				free(tokens);

				return 1;
			}

			free(*(tokens + i));
		}

		free(tokens);
	}

	return 0;
}


// Tidy HTML for output *EXPERIMENTAL*
int tidy_html(char *in, char *out)
{
	char *bufferOutput;

	TidyBuffer output = {0};
	TidyBuffer errbuf = {0};
	int rc = -1;
	Bool ok;

	TidyDoc tdoc = tidyCreate();                     // Initialize "document"
	printf( "Tidying:\t%s\n", in );

	ok = tidyOptSetBool( tdoc, TidyXhtmlOut, yes );  // Convert to XHTML
	if ( ok )
		rc = tidySetErrorBuffer( tdoc, &errbuf );      // Capture diagnostics
	if ( rc >= 0 )
		rc = tidyParseString( tdoc, in );           // Parse the input
	if ( rc >= 0 )
		rc = tidyCleanAndRepair( tdoc );               // Tidy it up!
	if ( rc >= 0 )
		rc = tidyRunDiagnostics( tdoc );               // Kvetch
	if ( rc > 1 )                                    // If error, force output.
		rc = ( tidyOptSetBool(tdoc, TidyForceOutput, yes) ? rc : -1 );
	if ( rc >= 0 )
		rc = tidySaveBuffer( tdoc, &output );          // Pretty Print


	if ( rc >= 0 )
	{
		if ( rc > 0 )
			printf( "\nDiagnostics:\n\n%s", errbuf.bp );
		printf( "\nAnd here is the result:\n\n%s", output.bp );
		tidySaveFile( tdoc, out );
	}
	else
		printf( "A severe error (%d) occurred.\n", rc );

	tidyBufFree( &output );
	tidyBufFree( &errbuf );
	tidyRelease( tdoc );
	return rc;
}
