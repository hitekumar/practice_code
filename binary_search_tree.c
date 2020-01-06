#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*
 * Basic BST
 * 1. insert node
 * 2. find node
 * 3. delete node
 * 4. print tree
 */


typedef struct node {
    int key;
    struct node *l;
    struct node *r;
} tree_node_t;

void insert_node(tree_node_t *n, tree_node_t **root)
{
    if (*root == NULL)
    {
        *root = n;
        printf("Inserting %d\n", n->key);
        return;
    }
    if (n->key < (*root)->key)
    {
        insert_node(n, &(*root)->l);
    }
    else
    {
        insert_node(n, &(*root)->r);
    }
}

tree_node_t * get_node(int key)
{
    tree_node_t *n = malloc(sizeof(tree_node_t));
    if (n == NULL)
    {
        printf("Malloc failed\n");
        return NULL;
    }
    n->key = key;
    n->l = NULL;
    n->r = NULL;
    return n;
}

tree_node_t * find_node(int key, tree_node_t *root)
{
    if (root == NULL)
        return NULL;
    if (root->key == key)
        return root;
    if (key < root->key)
        find_node(key,root->l);
    else
        find_node(key,root->r);
}

tree_node_t * find_min(tree_node_t *root)
{
    if(root->l == NULL)
        return root;
    find_min(root->l);
}

tree_node_t *delete_node(int key, tree_node_t *root)
{
    if (root == NULL)
        return NULL;
    if (key < root->key)
        root->l = delete_node(key,root->l);
    else if (key > root->key)
        root->r = delete_node(key,root->r);
    // root is the node to delete
    else
    {
        // Node is a leaf 
        if (root->l == NULL && root->r == NULL)
        {
            free(root);
            return NULL;
        }
        // Node with left or right subtree
        if (root->l == NULL)
        {
            tree_node_t *tmp = find_min(root->r);
            root->key = tmp->key;
            root->r = delete_node(tmp->key,root->r);
        }
        else if (root->r == NULL)
        {
            tree_node_t * tmp = find_min(root->l);
            root->key = tmp->key;
            root->l = delete_node(tmp->key, root->l);
        }
        // Node with both subtrees present
        else
        {
            tree_node_t *tmp = find_min(root->r);
            root->key = tmp->key;
            root->r = delete_node(tmp->key,root->r);
        }    
    }
    return root;   

}

void print_tree_in_order(tree_node_t * root)
{
    if (root == NULL)
        return;
    print_tree_in_order(root->l);
    printf("%d ", root->key);
    print_tree_in_order(root->r);
}
int main(int argc, char **argv)
{
    tree_node_t *tree_root = NULL;
    tree_node_t *tmp;

    insert_node(get_node(8), &tree_root);
    insert_node(get_node(10), &tree_root);
    insert_node(get_node(4), &tree_root);
    insert_node(get_node(14), &tree_root);
    insert_node(get_node(11), &tree_root);
    insert_node(get_node(2), &tree_root);

    print_tree_in_order(tree_root); printf("\n");

    tmp = find_node(10,tree_root);
    if (tmp != NULL)
        printf("Found %d\n", tmp->key);
    else
        printf("Key not found %d\n", 10);
    tmp = find_node(12,tree_root);
    if (tmp != NULL)
        printf("Found %d\n", tmp->key);
    else
        printf("Key not found %d\n", 12);
    printf("Deleting %d\n", 8);
    delete_node(8,tree_root);

    print_tree_in_order(tree_root); printf("\n");

}

