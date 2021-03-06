#include <stdlib.h>

struct pair {
    void *first;
    void *second;
};

struct chain_node {
    struct chain_node *prev;
    struct chain_node *next;
    void *shape;
};

struct chain_node *create_chain_node(void)
{
	double *left_x = malloc(sizeof(double));
	double *left_y = malloc(sizeof(double));
	*left_x = 1.0;
	*left_y = 1.0;
	struct pair *left_center = malloc(sizeof(struct pair));
	left_center->first = left_x;
	left_center->second = left_y;
	double *left_radius = malloc(sizeof(double));
	*left_radius = 0.5;
	struct pair *left_hole = malloc(sizeof(struct pair));
	left_hole->first = left_center;
	left_hole->second = left_radius;

	double *right_x = malloc(sizeof(double));
	double *right_y = malloc(sizeof(double));
	*right_x = 9.0;
	*right_y = 1.0;
	struct pair *right_center = malloc(sizeof(struct pair));
	right_center->first = right_x;
	right_center->second = right_y;
	double *right_radius = malloc(sizeof(double));
	*right_radius = 0.5;
	struct pair *right_hole = malloc(sizeof(struct pair));
	right_hole->first = right_center;
	right_hole->second = right_radius;

	struct pair *holes = malloc(sizeof(struct pair));
	holes->first = left_hole;
	holes->second = right_hole;

	struct pair *body = malloc(sizeof(struct pair));
	double *width = malloc(sizeof(double));
	*width = 10.0;
	double *height = malloc(sizeof(double));
	*height = 2.0;
	body->first = width;
	body->second = height;

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
