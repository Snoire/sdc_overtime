#include <stdlib.h>

struct pair {
    void *first;
    void *second;
};

double *malloc_double(double x)
{
	double *ret = malloc(sizeof(double));
	*ret = x;
	return ret;
}

struct pair *pair_for_double_type(double x, double y)
{
	struct pair *ret = malloc(sizeof(struct pair));
	ret->first = malloc_double(x);
	ret->second = malloc_double(y);
	return ret;
}

struct chain_node {
    struct chain_node *prev;
    struct chain_node *next;
    void *shape;
};

struct chain_node *create_chain_node(void)
{
	struct pair *left_hole = malloc(sizeof(struct pair));
	left_hole->first = pair_for_double_type(1.0, 1.0);
	left_hole->second = malloc_double(0.5);

	struct pair *right_hole = malloc(sizeof(struct pair));
	right_hole->first = pair_for_double_type(9.0, 1.0);
	right_hole->second = malloc_double(0.5);

	struct pair *holes = malloc(sizeof(struct pair));
	holes->first = left_hole;
	holes->second = right_hole;

	struct pair *body = pair_for_double_type(10.0, 1.0);

	struct pair *shape = malloc(sizeof(struct pair));
	shape->first = body;
	shape->second = holes;

	struct chain_node *ret = malloc(sizeof(struct chain_node));
	ret->prev = NULL;
	ret->next = NULL;
	ret->shape = shape;
	return ret;
}

int main()
{
	struct chain_node *head = create_chain_node();
	struct chain_node *tail = head;
	for (int i = 0; i < 1000; i++) {
		struct chain_node *new_tail = create_chain_node();
		tail->next = new_tail;
		new_tail->prev = tail;
		tail = new_tail;
	}
	tail->next = head;
	head->prev = tail;

	return 0;
}
