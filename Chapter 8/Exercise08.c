#include <stdio.h>

void *malloc(unsigned );
void free(void *);
void bfree(void *, unsigned );

int main(int argc, char *argv[])
{
	int rand(void), *arr, i,
		atoi(const char *);

	arr = (int *)malloc(sizeof(int) * (argc - 1));
	if (!arr) return 1;

	for (i = 0; *++argv; i++)
		arr[i] = atoi(*argv);

	while (--i >= 0)
		printf("%d ", arr[i]);

	free(arr);

	return 0;
}

#define NALLOC 1024

typedef long Align;

union header {
	struct {
		union header *next;
		unsigned size;
	} s;

	Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *malloc(unsigned nbytes)
{
	Header *p, *prevp;
	Header *morecore(unsigned );
	unsigned nunits;

	nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
	if (nunits <= 1 || nunits >= NALLOC)
		return NULL;

	if ((prevp = freep) == NULL) {
		base.s.next = freep = prevp = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.next; ; prevp = p, p = p->s.next)
	{
		if (p->s.size >= nunits) {
			if (p->s.size == nunits)
				prevp->s.next = p->s.next;
			else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;

			return (void *)(p + 1);
		}
		
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

Header *morecore(unsigned nu)
{
	char *cp, *sbrk(int );
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;

	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) -1)
		return NULL;

	up = (Header *) cp;
	up->s.size = nu;
	free((void *)(up + 1));

	return freep;
}

void free(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1; /* point to block header */
	for (p = freep; !(bp > p && bp < p->s.next); p = p->s.next)
		if (p >= p->s.next && (bp > p || bp < p->s.next))
			break;

	if (bp + bp->s.size == p->s.next) { /* join to upper nbr */
		bp->s.size += p->s.next->s.size;
		bp->s.next = p->s.next->s.next;
	} else {
		bp->s.next = p->s.next;
	}

	if (p + p->s.size == bp) { /* join to lower nbr */
		p->s.size += bp->s.size;
		p->s.next = bp->s.next;
	} else {
		p->s.next = bp;
	}

	freep = p;
}

void bfree(void *p, unsigned n)
{
	Header *hp;
	unsigned nunits;

	if (n < sizeof(Header) * 2)
		return ;

	nunits = (n + sizeof(Header) - 1) / sizeof(Header) + 1;

	hp = (Header *) p;
	hp->s.size = nunits;
	free((void *)(hp + 1));
}
