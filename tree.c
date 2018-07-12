#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* BinaryTree Node */
typedef struct tree_node {
    int val;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

/* Global definitions for Queue */
typedef struct queue_node {
    struct tree_node *node;
    struct queue_node *next;
}queue_node;

queue_node *front=NULL, *end=NULL;

/* Enqueue and Dequeue APIs */
void enqueue(tree_node *node) {
    queue_node *new_node = (queue_node*)malloc(sizeof(queue_node));
    new_node->node = node;
    new_node->next = NULL;
    if(front) {
        front->next = new_node;
    }
    if(!end) {
        end = new_node;
    }
    front = new_node;
}

tree_node* dequeue(void) {
    if(!end) {
        return NULL;
    }
    tree_node *temp = end->node;
    end = end->next;
    return temp;
}

/* Queue Size and Queue Empty APIs */
bool queue_empty(void) {
    if(!end) {
        return true;
    } else {
        return false;
    }
}

int queue_size(void) {
    queue_node *temp = end;
    int count=0;
    if(!end || !front) {
        return count;
    }
    while(temp) {
        temp = temp->next;
        count++;
    }
    return count;
}

/* Tree Operations */

tree_node* InsertNode(tree_node *root, int val) {
    if(root == NULL) {
        tree_node *temp = (tree_node *)malloc(sizeof(tree_node));
        temp->val = val;
        temp->right = NULL;
        temp->left = NULL;
        return temp;
    } else if (val <= root->val) {
        root->left = InsertNode(root->left, val);
    } else {
        root->right = InsertNode(root->right, val);
    }
    return root;
}

/* To get the inorder successor of the given value node in the tree */
tree_node* InorderSuccessor(tree_node *root, int val, tree_node *successor) {
    if(!root) {
        return NULL;
    }
    if(val < root->val) {
        successor = InorderSuccessor(root->left, val, root);
    } else if(val > root->val) {
        successor = InorderSuccessor(root->right, val, successor);
    } else {
        if(root->right) {
            root = root->right;
            while(root->left) {
                root = root->left;
            }
            successor = root;
        }
    }
    return successor;
}

/* To search for a node with given value in the tree */
tree_node* SearchNode(tree_node *root, int val) {
    if(!root) {
        return NULL;
    }
    if(root->val == val) {
        return root;
    }
    if(val > root->val) {
        return SearchNode(root->right, val);
    } else {
        return SearchNode(root->left, val);
    }
}

tree_node* MinVal(tree_node *node) {
    if(!node) {
        return NULL;
    }
    node = node->right;
    while(node->left) {
        node = node->left;
    }
    return node;
}

/* To Delete a node with given value from the tree */
tree_node* DeleteNode(tree_node *root, int val) {
    if(!root) {
        printf("Tree is empty.\n");
        return NULL;
    }
    tree_node *temp = NULL;
    if(val > root->val) {
        root->right = DeleteNode(root->right, val);
    } else if(val < root->val) {
        root->left = DeleteNode(root->left, val);
    } else {
        if(!root->left) {
            temp = root->right;
            root = NULL;
            free(root);
            return temp;
        }
        if(!root->right) {
            temp = root->left;
            root = NULL;
            free(root);
            return temp;
        }
        tree_node *successor = MinVal(root);
        root->val = successor->val;
        root->right = DeleteNode(root->right, successor->val);
    }
    return root;
}

/* Depth first Traversals */

void InOrderTree(tree_node *root) {
    if(!root) {
        return;
    }
    InOrderTree(root->left);
    printf("%d ", root->val);
    InOrderTree(root->right);
}

void PreOrderTree(tree_node *root) {
    if(!root) {
        return;
    }
    printf("%d ", root->val);
    PreOrderTree(root->left);
    PreOrderTree(root->right);
}

void PostOrderTree(tree_node *root) {
    if(!root) {
        return;
    }
    PostOrderTree(root->left);
    PostOrderTree(root->right);
    printf("%d ", root->val);
}

/* Bredth First Traversal */

void BfsTree(tree_node *root) {
    if(!root) {
        printf("Tree is Empty\n");
        return;
    }

    tree_node *temp=NULL;
    enqueue(root);
    while(!queue_empty()) {
        temp = dequeue();
        printf("%d ", temp->val);
        
        if(temp->left) {
            enqueue(temp->left);
        }
        if(temp->right) {
            enqueue(temp->right);
        }
    }
}

/* Bredth First Traversal Line by Line */

void BfsTreeLine(tree_node *root) {
    if(!root) {
        printf("Tree is Empty\n");
        return;
    }

    tree_node *temp=NULL;
    enqueue(root);
    int count, i;
    while(!queue_empty()) {
        count = queue_size();
        for(i=0; i<count; i++) {
            temp = dequeue();
            printf("%d ", temp->val);

            if(temp->left) {
                enqueue(temp->left);
            }
            if(temp->right) {
                enqueue(temp->right);
            }
        }
        printf("\n");
    }
}

/* Convert a given tree to its mirror image */
void mirror(tree_node *root) {
    if(root == NULL) {
        return;
    }
    
    /* We use post-order here. */
    mirror(root->left);
    mirror(root->right);

    /* Now, swap the nodes */
    tree_node *temp = root->left;
    root->left = root->right;
    root->right = temp;

    return root;
}

int main(void) {
    
/*
 *          5
 *     2        9
 *  1     3  7     10
 * 0       4  8      11
 *
 */
    
    tree_node *root=NULL;
    tree_node *successor=NULL;
    root = InsertNode(root, 5);
    root = InsertNode(root, 2);
    root = InsertNode(root, 3);
    root = InsertNode(root, 9);
    root = InsertNode(root, 1);
    root = InsertNode(root, 7);
    root = InsertNode(root, 8);
    root = InsertNode(root, 10);
    root = InsertNode(root, 0);
    root = InsertNode(root, 4);
    root = InsertNode(root, 11);

    printf("Inorder representation of tree is:\n");
    InOrderTree(root);
    printf("\n\n");

    printf("Preorder representation of tree is:\n");
    PreOrderTree(root);
    printf("\n\n");

    printf("Postorder representation of tree is:\n");
    PostOrderTree(root);
    printf("\n\n");

    printf("Level order representation of tree is:\n");
    BfsTree(root);
    printf("\n\n");

    printf("Level order representation of tree line by line is:\n");
    BfsTreeLine(root);
    printf("\n\n");

    printf("Inorder successor of %d is %d\n\n",
            8, InorderSuccessor(root, 8, successor)->val);

    printf("Inorder representation of tree is:\n");
    InOrderTree(root);
    printf("\n");

    printf("Deleting Node with value 5\n");
    root = DeleteNode(root, 5);
    printf("Inorder representation of tree is:\n");
    InOrderTree(root);
    printf("\n");

    printf("Level order representation of tree line by line is:\n");
    BfsTreeLine(root);
    printf("\n");
    return 0;
}
