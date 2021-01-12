#include <stdio.h>

#define WORDSIZ 128

struct nlist {
	struct nlist *next;
	char *name;
	char *defn;
};

struct nlist *lookup(char *);
struct nlist *install(char *, char *);
int undef(char *);

int main(void)
{
	struct nlist *np;
	char defn[WORDSIZ], name[WORDSIZ];
	int select;

	while (1) {
		printf("1. Install\n"
			   "2. Lookup\n"
			   "3. Undef\n"
			   "choose: ");


		scanf("%d", &select);
		switch(select) {
		case 1:
			printf("name, defn: ");
			scanf("%s %s", name, defn);
			install(name, defn);
			break;
		
		case 2:
			printf("name: ");
			scanf("%s", name);

			np = lookup(name);
			if (np != NULL)
				printf("defn: %s \n", np->defn);
			else
				printf("defn not found\n");
			break;

		case 3:
			printf("name: ");
			scanf("%s", name);

			if (undef(name)) {
				printf("undef %s \n", name);
			} else {
				printf("can't found %s \n", name);
			}
			break;

		default: return 0;
		} printf("\n");
	}

	return 1;
}

#define HASHSIZE 101

static struct nlist *hashtab[HASHSIZE];

unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;

	return hashval % HASHSIZE;
}

#include <string.h>

struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np;

	return NULL;
}

#include <stdlib.h>

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;
	char *strdup(const char *);

	if ((np = lookup(name)) == NULL) {
		np = (struct nlist *) malloc(sizeof(struct nlist));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;

		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else {
		free((void *) np->defn);
	}

	if ((np->defn = strdup(defn)) == NULL)
		return NULL;

	return np;
}

int undef(char *name)
{
	struct nlist *cur, *prev;
	unsigned hashval = hash(name);

	for (prev = NULL, cur = hashtab[hashval]; cur != NULL; prev = cur, cur = cur->next)
		if (strcmp(name, cur->name) == 0) break;

	if (cur == NULL) 
		return 0;

	free(cur->name);
	free(cur->defn);

	if (prev) {
		prev->next = cur->next;
	} else {
		hashtab[hashval] = cur->next;
	}

	return 1;
}
