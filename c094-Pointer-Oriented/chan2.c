#include <stdlib.h>

struct chain_node {
    struct chain_node *prev;
    struct chain_node *next;
    void *shape;
};

int main()
{
	struct chain_node *head = malloc(sizeof(struct chain_node));
	struct chain_node *tail = head;

	for (int i = 0; i < 1000; i++) {
		struct chain_node *new_tail = malloc(sizeof(struct chain_node));
		tail->next = new_tail;
		new_tail->prev = tail;
		tail = new_tail;
	}

	tail->next = head;
	head->prev = tail;

    return 0;
}
