#include "../inc/utils.h"

size_t	sublen(const char * str, const char * set) {

    size_t len = 0;

    while (str && str[len] && !strchr(set, str[len]))
        len++;
    return len;
}

char *	substr(const char * str, const size_t start, const size_t len) {

	char * dst;

	if (!str || !*str || !len)
		return (NULL);

	if  (!(dst = (char *) calloc(len + 1, sizeof(char)))) {
		errno = ENOMEM; perror("substr()"); return (NULL);
	}
	
	memmove(dst, str + start, len);

	return dst;
}

char *	cleanstr(const char * str, const char * set) {

	size_t len = strlen(str);

	for (size_t i = 0; str && str[i]; i++)
		if (strchr(set, str[i]))
			len--;

	char * dst;
	
	if (!(dst = (char *) calloc(len + 1, sizeof(char)))) {
		errno = ENOMEM; perror("cleanstr()"); return (NULL);
	}

	for (size_t i = 0, j = 0; str && str[i]; i++)
		if (!strchr(set, str[i]))
			dst[j++] = str[i];

	return dst;
}

char ** split(const char * str, const char * set) {

    size_t  div = 1;
    char ** tab = NULL;

    for (size_t i = 0; str[i]; i++)
        if (strchr(set, str[i]) && str[i + 1] && !strchr(set, str[i + 1]))
            div++;

    if (!(tab = (char **) calloc(div + 1, sizeof(char *)))) {
        errno = ENOMEM; perror("split()"); return NULL;
    }
    
    div = 0;
    for (size_t i = 0; str[i]; i++)
        if (!strchr(set, str[i]) && (!i || strchr(set, str[i - 1])))
            tab[div++] = substr(str, i, sublen(&str[i], set));

    return tab;
}

void    freetab(char ** tab) {

    size_t  i = 0;

    while (tab && tab[i])
        free(tab[i++]);
    if (tab)
        free(tab);
}
