#include "./.utils.h"

static size_t count(const char * str, const char * set, const char * xpt) {
    
    char    in = 0;
    size_t  div = 2;

    for (int i = 0; str[i]; i++) {

        if (str[i] == in)
            in = 0;
        else if (!in && strchr(xpt, str[i]))
            in = str[i];
        else if (!in && strchr(set, str[i]) && str[i + 1] && !strchr(set, str[i + 1]) && !strchr(xpt, str[i + 1]))
            div++;
    }

    return div;
}

static size_t setlen(const char *str, const char *set, const char *xtp)
{
	char	in = 0;
	size_t	i = 0;

	while (str && str[i]) {

		if (str[i] == in)
			in = 0;
		else if (!in && xtp && strchr(xtp, str[i]))
			in = str[i];
		else if (!in && set && strchr(set, str[i]))
			return i;
        i++;
	}

	return i;
}

static char ** except(const char * str, const char * set, const char * xpt) {

    size_t  i = 0;
    size_t  div = 0;
    size_t  len = 0;
    char ** tab = NULL;

    if (!(tab = (char **) calloc(count(str, set, xpt), sizeof(char *))))
        return NULL;

    while (strchr(set, str[i]))
        i++;

    while (str && str[i]) {

        len = setlen(&str[i], set, xpt);
        if (!len)
            len++;
        tab[div++] = substr(str, i, len);
        i += len;
        while (str[i] && strchr(set, str[i]))
            i++;
	}

    return tab;
}

static char ** noexcept(const char * str, const char * set) {

    size_t  div = 1;
    char ** tab = NULL;

    for (size_t i = 0; str[i]; i++)
		if (strchr(set, str[i]) && str[i + 1] && !strchr(set, str[i + 1]))
			div++;
    if (!(tab = (char **) calloc(div + 1, sizeof(char *))))
        return NULL;

    div = -1;
    for (size_t i = 0; str[i]; i++)
        if (!strchr(set, str[i]) && (strchr(set, str[i - 1]) || !i))
            tab[++div] = substr(str, i, sublen(&str[i], set));

    return tab;
}

char ** split(const char * str, const char * set, const char * xpt) {

    char ** tab;

    if (!str || !*str)
        return NULL;

    if (!set || !*set) {

        if (!(tab = (char **) calloc(2, sizeof(char *))))
            return NULL;
        *tab = strdup(str);
        return tab;
    }

    if (!xpt || !*xpt)
        return noexcept(str, set);
    return except(str, set, xpt);
}