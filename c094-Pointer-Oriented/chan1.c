struct chain_node {
    struct chain_node *prev;
    struct chain_node *next;
    void *shape;
};

int main()
{
    struct chain_node a, b, c;

    a.next = &b;
    b.prev = &a;

    b.next = &c;
    c.prev = &b;

    c.next = &a;
    a.prev = &c;

    return 0;
}
