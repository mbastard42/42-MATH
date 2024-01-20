#include "./.utils.h"

size_t sublen(const char * str, const char * set) {

    size_t len = 0;

    while (str && *str && str[len] && !strchr(set, str[len]))
        len++;
    return len;
}

char * substr(const char *str, const size_t start, const size_t len) {

	char * dst;

	if (!str || !*str || !len || !(dst = (char *) calloc(len + 1, sizeof(char))))
		return (NULL);
	memmove(dst, str + start, len);

	return dst;
}