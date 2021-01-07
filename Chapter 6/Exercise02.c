#include <stdio.h>
#include <ctype.h>

#define TOKSIZ 512

#define ENDOFF 0
#define SQUOTE 01
#define DQUOTE 0x02
#define DIGITS 3
#define WORDS  4
#define TOKENS 5
#define ENDOFP 6

const char *stype[] = {
	"ENDOFF", "SQUOTE", "DQUOTE", "DIGITS", 
	"WORDS", "TOKENS", "ENDOFP"
};

const char *keywords[] = {
	"char", "const", "double", "float",
	"int", "long", "register", "short",
	"signed", "unsigned",
};

const char test[] = {
	'H', '\?', '\\', 'N'
};


int main(void)
{
	int type;
	char token[TOKSIZ];
	
	while ((type = gettoken(token)) != ENDOFF) {
		if (type == TOKENS)
			printf("[%s] %c\n", stype[type], *token);
		else
			printf("[%s] %s\n", stype[type], token);

		/*
		if (type == TOKENS && *token == '#')
			while (gettoken(token) != ENDOFP);
		
		sleep(1);
		*/
	}

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
	} while (isalnum(ch = getchar()));
	ungetc(ch, stdin);
	
	*tok = '\0';

	return WORDS;
}
