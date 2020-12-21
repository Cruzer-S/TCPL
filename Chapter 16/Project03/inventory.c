#include <stdio.h>
#include "readline.h"

#define NAME_LEN 25
#define MAX_PARTS 100

struct part {
	int number;
	char name[NAME_LEN + 1];
	int on_hand;
};

int find_part(struct part *inventory, int number, int num_parts);
void insert(struct part *inventory, int *num_parts);
void search(struct part *inventory, int num_parts);
void update(struct part *inventory, int num_parts);
void print(struct part *inventory, int num_parts);

int main(void)
{
	int num_parts = 0;
	struct part inventory[MAX_PARTS];

	char code;

	for (;;) {
		printf("Enter operation code: ");
		scanf(" %c", &code);
		while(getchar() != '\n');

		switch (code) {
		case 'i': insert(inventory, &num_parts);
				  break;
		case 's': search(inventory, num_parts);
				  break;
		case 'u': update(inventory, num_parts);
				  break;
		case 'p': print(inventory, num_parts);
				  break;
		case 'q': return 0;
		default: printf("Illegal code \n");
		}
		printf("\n");
	}
}

int find_part(struct part *inventory, int number, int num_parts)
{
	for (int i = 0; i < num_parts; i++)
		if (inventory[i].number == number)
			return i;

	return -1;
}

void insert(struct part *inventory, int *num_parts)
{
	struct part new_part;

	if (*num_parts == MAX_PARTS) {
		printf("Database is full; can't add more parts. \n");
		return ;
	}

	printf("Enter part number: ");
	scanf("%d", &new_part.number);

	if (find_part(inventory, new_part.number, *num_parts) >= 0) {
		printf("Part already exists. \n");
		return ;
	}

	printf("Enter part name: ");
	read_line(new_part.name, NAME_LEN);
	printf("Enter quantity on hand: ");
	scanf("%d", &new_part.on_hand);

	int offset;
	for ( offset = 0; offset < *num_parts; offset++) 
		if (inventory[offset].number > new_part.number) break;

	for (int k = *num_parts; k > offset; k--)
		inventory[k] = inventory[k - 1];

	inventory[offset] = new_part;

	(*num_parts)++;
}

void search(struct part *inventory, int num_parts)
{
	int i, number;

	printf("Enter part number: ");
	scanf("%d", &number);
	i = find_part(inventory, number, num_parts);

	if (i >= 0) {
		printf("Part number: %s \n", inventory[i].name);
		printf("Quantity on hand: %d \n", inventory[i].on_hand);
	} else {
		printf("Part not found. \n");
	}
}

void update(struct part *inventory, int num_parts)
{
	int i, number, change;

	printf("Enter part number: ");
	scanf("%d", &number);
	i = find_part(inventory, number, num_parts);
	if (i >= 0) {
		printf("Enter change in quantity on hand: ");
		scanf("%d", &change);
		inventory[i].on_hand += change;
	} else {
		printf("Part not found. \n");
	}
}

void print(struct part *inventory, int num_parts)
{
	printf("Part Number    Part Name                         "
		   "Quantity on Hand\n");

	for (int i = 0; i < num_parts; i++)
		printf("%7d        %-25s%11d\n",
				inventory[i].number,
				inventory[i].name,
				inventory[i].on_hand);
}
