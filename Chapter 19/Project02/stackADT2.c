#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stackADT2.h"


struct stack_type {
	Item *contents;
	int top;
	int size;
};

static void terminate(const char *message)
{
	printf("%s \n", message);
	exit(EXIT_FAILURE);
}

Stack create(int size)
{
	Stack s = malloc(sizeof(struct stack_type));
	if (s == NULL)
		terminate("Error in create: stack could not be created.");
	s->contents = malloc(size * sizeof(Item));
	if (s->contents == NULL) {
		free(s);
		terminate("Error in create: stack could not be created.");
	}

	s->top = 0;
	s->size = size;

	return s;
}

void destroy(Stack s)
{
	free(s->contents);
	free(s);
}

void make_empty(Stack s)
{
	s->top = 0;
}

bool is_empty(Stack s)
{
	return s->top == 0;
}

bool is_full(Stack s)
{
	return s->top == s->size;
}

void push(Stack s, Item i)
{
	if (is_full(s)) {
		Item *new_contents = malloc(sizeof(Item) * s->size * 2);
		if (new_contents == NULL)
			terminate("Error in push: out of memory.");

		memcpy(new_contents, s->contents, sizeof(Item) * s->size);
		free(s->contents);
		s->contents = new_contents;
		s->size *= 2;
	}

	s->contents[s->top++] = i;
}

Item pop(Stack s)
{
	if (is_empty(s))
		terminate("Error in pop: stack is empty.");

	return s->contents[--s->top];
}
