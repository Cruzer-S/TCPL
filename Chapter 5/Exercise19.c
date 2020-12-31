#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define MAXOUTPUT 1000 

enum {
	NAME, PARENS, BRACKETS
};

void dcl(void);
int dirdcl(void);

int gettoken(void);
int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[MAXOUTPUT];

void dcl_parser(void)
{
	while (gettoken() != EOF) {
		strcpy(datatype, token);
		out[0] = '\0';

		dcl();
		if (tokentype != '\n') {
			printf("tokentype: %c\n", tokentype);
			printf("syntax error\n");
			continue;
		}

		printf("%s: %s %s\n", name, out, datatype);
	}
}

void dcl_analyzer(void)
{
	int type, count;

	char out[MAXTOKEN];
	char temp[MAXOUTPUT];

	count = 0;
	while (gettoken() != EOF) {
		strcpy(out, token);
		while ((type = gettoken()) != '\n') {
			if (type != '*') {
				if (count > 0) {
					strcpy(temp, "(");
					while (count-- > 0)
						strcat(temp, "*");
					strcat(temp, out);
					strcat(temp, ")");
					strcpy(out, temp);
				}
				count = 0;
			} else count++;

			if (type == PARENS || type == BRACKETS) {
				strcat(out, token);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else if (type != '*') {
				printf("invalid input at %s \n", token);
			}
		}
		printf("%s\n", out);
	}
}

int main(void)
{
	dcl_analyzer();

	return 0;
}

int getch(void);
void ungetch(int );
void flush(void);

int gettoken(void)
{
	char *p = token;
	int c;

	while ((c = getch()) == ' ' || c == '\t') ;

	if (c == '(') {
		if ((c = getch()) == ')') {
			strcpy(token, "()");
			return tokentype = PARENS;
		} else {
			ungetch(c);
			return tokentype = '(';
		}
	} else if (c == '[') {
		for (*p++ = c; (*p++ = getch()) != ']'; ) ;

		*p = '\0';
		return tokentype = BRACKETS;
	} else if (isalpha(c)) {
		for (*p++ = c; isalnum(c = getch()); *p++ = c) ;

		*p = '\0';
		ungetch(c);
		return tokentype = NAME;
	}
	
	return tokentype = c;
}

void dcl(void)
{
	int ns;

	for (ns = 0; gettoken() == '*'; )
		ns++;

	if(!dirdcl()) {
		printf("failed to convert declaration %c\n", tokentype);
		tokentype = '\0';
		flush();

		return ;
	}

	while (ns-- > 0)
		strcat(out, " pointer to");
}

int dirdcl(void)
{
	int type;

	if (tokentype == '(') {
		dcl();

		if (tokentype != ')') {
			printf("error: missing ) \n");
			return 0;
		}
	} else if (tokentype == NAME)
		strcpy(name, token);
	else {
		printf("error: expected name or (dcl)\n");
		return 0;
	}

	if ((type = gettoken()) == PARENS || type == BRACKETS) {	
		do {
			if (type == PARENS) 
				strcat(out, " function returning");
			else {
				strcat(out, " array");
				strcat(out, token);
				strcat(out, " of");
			}
		} while ((type = gettoken()) == PARENS || type == BRACKETS) ;

		return 1;
	}

	if (tokentype != '\n') return 0;
	
	return 1;
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void)
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
	if (bufp >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufp++] = c;
}

void flush(void)
{
	while (getch() != '\n') ;
}
