#ifndef third_h
#define third_h

//node structure. it can carry an integer value and a ptr to the next node
typedef struct node
{
    int val;
    struct node * next;
} node_t;

void print_list(node_t * head);
void push(node_t ** head, int v);
void del(node_t ** head, int v);

#endif /* third_h */