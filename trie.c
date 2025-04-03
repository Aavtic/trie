#include <stdio.h>
#include <assert.h>

typedef struct Node Node;

struct Node {
    Node *children[256];
};

#define POOL_CAPACITY 1024
Node node_pool[POOL_CAPACITY] = {0};
size_t node_pool_count = 0;

Node* allocate_node(void) {
    assert(node_pool_count < POOL_CAPACITY);
    return &node_pool[node_pool_count++];
}

void insert_node(Node* root, const char* str) {
    if (*str == '\0' || str == NULL) {
        return;
    }

    assert(root != NULL);

    size_t index = (int) *str;

    if (root->children[index] == NULL)
        root->children[index] = allocate_node();

    insert_node(root->children[index], str + 1);
}

int main(void) {
    Node* root = allocate_node();
    insert_node(root, "hello");

    return 0;
}
