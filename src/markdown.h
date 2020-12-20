#ifndef MARKDOWN_H
#define MARKDOWN_H


#include "macro.h"

int md_to_html(int n, char line[n][WORD_LENGTH + 1]);
int convert_md_link_to_html();


#endif
