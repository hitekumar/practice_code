/* 
 * AVL Tree implementation
 */

#include <stdio.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
    struct node *parent;
    int height;
}

struct avl_tree
{
    struct node *root;
}

int max(int a, int b)
{
    return a > b ? a:b;
}

struct node * get_node(void)
{
    ret = (struct node *) malloc(sizeof(struct node));
    if (!ret)
    {
        printf("Node allocation failed\n");
    }
    return ret;
}

int get_height(struct node *root)
{
    int l_height = 0;
    int r_height = 0;
    if (root->left)
    {
        l_height = get_height(root->left);
    }
    if (root->right)
    {
        r_height = get_height(root->right);
    }

    return (1 + max(l_height,r_height));
}

void insert(struct node *root, int key)
{
    if (root == NULL)
    {
        root = get_node();
        root->key = key;
        root->left = NULL;
        root->right = NULL;
        height = get_height(root);
    }
    if (key < root->key)
    {
        insert(root->left, key);
    }
    else
    {
        insert(root->right, key);
    }

}

void print_tree(struct node *root)
{
    if(root == NULL)
    {
        return
    }
    printf("key = %d, height=%d\n", root->key, root->height);
    print_tree(root->left);
    print_tree(root->right);

}

int main(int argc, char ** argv)
{
    struct avl_tree tree;
    insert(tree->root, 3);
    insert(tree->root, 4);
    insert(tree->root, 5);
    insert(tree->root, 6);


}
























