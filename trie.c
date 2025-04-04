#include <stdio.h>
#include <assert.h>

#define ARRAY_LENGTH(xs) sizeof(xs) / sizeof(xs[0])

typedef struct Node Node;

struct Node {
    struct Node* children[256];
};

#define NODE_POOL_CAPACITY 1024
Node node_pool[NODE_POOL_CAPACITY] = {0};
size_t pool_size = 0;

Node* allocate_node() {
    assert(pool_size < NODE_POOL_CAPACITY);
    return &node_pool[pool_size++];
}

void insert_text(Node* root, const char* text) {
    if (*text == '\0' || text == NULL) {
        return;
    }

    assert(root != NULL);

    size_t index = *text;
    if (root->children[index] == NULL) {
        root->children[index] = allocate_node();
    }
    insert_text(root->children[index], text + 1);
}

void dump_dot(Node* root) {
    size_t index = root - node_pool;

    for (size_t i=0; i<sizeof(root->children) / sizeof(root->children[0]); ++i) {
        if (root->children[i] != NULL) {
            size_t child_index = root->children[i] - node_pool;
            printf("    Node%zu -> Node%zu [label=%c];\n", index, child_index, (char) i);
            dump_dot(root->children[i]);
        }
    }
}

int main(void) {
    struct Node* root = allocate_node();
    insert_text(root, "hello");
    insert_text(root, "helium");

    printf("digraph Root {\n");
    dump_dot(root);
    printf("}\n");

    return 0;
}
