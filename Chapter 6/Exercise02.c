#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TOKSIZ 512

#define KWDSIZ (sizeof(keywords) / sizeof(keywords[0]))

#define ENDOFF 0
#define SQUOTE 01
#define DQUOTE 0x02
#define DIGITS 3
#define WORDS  4
#define TOKENS 5
#define ENDOFP 6

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
}; 

int is_keywords(char word[]);

struct tnode *addtree(struct tnode *, char * , int );
void treeprint(struct tnode * , int );

const char *stype[] = {
	"ENDOFF", "SQUOTE", "DQUOTE", "DIGITS", 
	"WORDS", "TOKENS", "ENDOFP"
};

const char *keywords[] = {
	"char", "const", "double", "float",
	"int", "long", "register", "short", "static",
	"signed", "unsigned", "void"
};

int main(int argc, char *argv[])
{
	int type, i, length;
	char token[TOKSIZ], check[TOKSIZ];
	struct tnode *root = NULL;

	if (argc == 2)
		length = atoi(argv[1]);
	else
		length = 6;
	
	while ((type = gettoken(token)) != ENDOFF) {
		if (type == TOKENS && *token == '#')
			while (gettoken(token) != ENDOFP);

		/*
		if (type == TOKENS)
			printf("[%s] %c\n", stype[type], *token);
		else
			printf("[%s] %s\n", stype[type], token);
		*/

		if (is_keywords(token)) {
			for (type = gettoken(token);
				 type == TOKENS || is_keywords(token);
				 type = gettoken(token));

			gettoken(check);

			if (*check == '(') continue;
			if (!strcmp(token, "struct")) continue;

			root = addtree(root, token, length);
			/* printf("keyword: %s\n", token); */
			
			if (*check == ',' || *check == '[') {		
				if (*check == '[')
					do gettoken(token); while(*token != ']');

				for (type = gettoken(token);
					 *token != ';';
					 type = gettoken(token)) 
				{
					if (*token == '[')
						do gettoken(token); while(*token != ']');
					if (*token == ')') break;

					if (is_keywords(token)) continue;
					if (type != WORDS) continue;

					root = addtree(root, token, length);

					/* printf("word: %s\n", token); */
				}
			}
		} else {
			if (!strcmp(token, "struct")) {
				/* skip struct tag name */
				gettoken(token);

				/* find struct variable name */
				for (type = gettoken(token);
					 type == TOKENS || is_keywords(token);
					 type = gettoken(token)) 
				{
					if (*token == '{' || *token == ';') 
						break;
				}

				if (*token == '{' || *token == ';')
					continue;

				gettoken(check);
				if (*check == '(') continue;
				else root = addtree(root, token, length);

				/* printf("struct: %s\n", token); */
			}
		}
	}

	treeprint(root, length);

	return 0;
}

int gettoken(char tok[])
{
	static int EOP = 0; /* End of preprocessor */
	int ch, ck;

	*tok = '\0';

	/* skip all white-space */
	if (!EOP)
		while (isspace(ch = getchar())) ;
	else do {
		ch = getchar();
		if (ch == '\\')
			getchar(), ch = getchar();
		if (ch == '\n') {
			EOP = 0;
			return ENDOFP;
		}
	} while (isspace(ch));

	/* skip comment */
	ck = EOF;
	if (ch == '/' && (ck = getchar()) == '*')
		while (!(getchar() == '*' && getchar() == '/')) ;
	else if (ck != EOF) ungetc(ck, stdin);

	/* treat a single quote as a token */
	if (ch == '\'') {
		*tok++ = ch;
		if ((*tok++ = getchar()) == '\\')
			*tok++ = getchar();
		*tok++ = getchar();

		*tok = '\0';

		return SQUOTE;
	}

	/* treat a double quote as a token */
	if (ch == '\"') {
		*tok++ = ch;
		while ((*tok = getchar()) != '\"')
			if (*tok++ == '\\')
				*tok++ = getchar();

		*++tok = '\0';

		return DQUOTE;
	}

	/* treat the whole number as a single token */
	if (isdigit(ch)) {
		*tok++ = ch;

		if (ch == '0') {
			ch = getchar();

			if (!isdigit(ch)) {
				if (ch == 'x' || ch == 'X')
					*tok++ = ch;
				else {
					ungetc(ch, stdin);
					*tok = '\0';
					return DIGITS;
				}
			} else ungetc(ch, stdin);
		}

		if (ch == 'x' || ch == 'X')
			while (isxdigit(ch = getchar()))
				*tok++ = ch;
		else
			while (isdigit(ch = getchar()))
				*tok++ = ch;

		ungetc(ch, stdin);

		*tok = '\0';

		return DIGITS;
	}

	if (!isalpha(ch) && ch != '_') {
		*tok = ch;

		if (ch == '#') EOP = 1;
		if (ch == EOF)
			return ENDOFF;
		else
			return TOKENS;
	}

	*tok = ch;

	do {
		*tok++ = ch;
	} while (isalnum(ch = getchar()) || ch == '_');
	ungetc(ch, stdin);
	
	*tok = '\0';

	return WORDS;
}

int is_keywords(char word[])
{ 
	int i;

	for (i = 0; i < KWDSIZ; i++)
		if (!strcmp(word, keywords[i]))
			return 1;

	return 0;
}

struct tnode *talloc(void);
char *strdup(char * );

struct tnode *addtree(struct tnode *p, char *w, int len)
{
	int cond;

	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strncmp(w, p->word, len)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w, len);
	else
		p->right = addtree(p->right, w, len);

	return p;
}

void treeprint(struct tnode *p, int len)
{
	if (p != NULL) {
		treeprint(p->left, len);

		if (p->count > 1) {
			char f = p->word[len],
				 l = p->word[len + 1];

			p->word[len] = '-';
			p->word[len + 1] = '\0';
			printf("%4d %s \n", p->count, p->word);

			p->word[len] = f;
			p->word[len + 1] = l;
		}

		treeprint(p->right, len);
	}
}

#include <stdlib.h>

struct tnode *talloc(void)
{
	return (struct tnode *)malloc(sizeof(struct tnode));
}
