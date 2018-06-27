/*
 * This file contains helper functions
 * for all the binary tree related operations.
 */

#include "utilities.h"

/*
 * Preorder tree traversal
 */
void preorder_traverse(bt_node *root) {
    if (root == NULL) {
        return;
    }
    printf("%d ", root->value);
    preorder_traverse(root->left);
    preorder_traverse(root->right);
}

/*
 * Inorder tree traversal
 */
void inorder_traverse(bt_node *root) {
    if (root == NULL) {
        return;
    }
    inorder_traverse(root->left);
    printf("%d ", root->value);
    inorder_traverse(root->right);
}

/*
 * Postorder tree traversal
 */
void postorder_traverse(bt_node *root) {
    if (root == NULL) {
        return;
    }
    postorder_traverse(root->left);
    postorder_traverse(root->right);
    printf("%d ", root->value);
}

/*
 * Levelorder tree traversal
 */
void levelorder_traverse(bt_node *root) {
    /* We use queue for traversal. */
    queue_t *queue = (queue_t*)malloc(sizeof(queue_t));

    /* Enqueue root first */
    enqueue(queue, root);

    while(!isEmpty(queue)) {
        bt_node *temp = dequeue(queue);
        printf("%d ", temp->value);
        if(temp->left) {
            enqueue(queue, temp->left);
        }
        if(temp->right) {
            enqueue(queue, temp->right);
        }
    }
    return;
}

/*
 * Levelorder tree traversal with each level printed
 * on different line.
 */
void levelorder_differentline(bt_node *root) {
    queue_t *queue = (queue_t*)malloc(sizeof(queue_t));
    int queue_size = 0;

    enqueue(queue, root);
    queue_size = getSize(queue);

    while(!isEmpty(queue)) {
        for(int i=0; i<queue_size; i++) {
            bt_node *temp = dequeue(queue);
            printf("%d ", temp->value);
            if(temp->left) {
                enqueue(queue, temp->left);
            }
            if(temp->right) {
                enqueue(queue, temp->right);
            }
        }
        printf("\n");
        queue_size = getSize(queue);
    }
    return;
}

/*
 * Levelorder in zigzag order
 */
void levelorder_zigzag(bt_node *root) {
    /* We use recursive approach here. We maintain a bool for directions
     * such that if it is false, then we print left to right else otherwise.
     * We also get height of tree and for each level, we call the recursive
     * function to print.
     */
    bool direction_flag = false;
    int tree_height = getHeightTree(root);

    for(int level=0; level<tree_height; level++) {
        printTreeZigzag(root, level, direction_flag);
        printf("/n");
        direction_flag = !direction_flag;
    }
}

void printTreeZigzag(bt_node *root, int level, bool direction_flag) {
    if(level == 0) {
        printf("%d ", root->value);
        return;
    }
    if(direction_flag) {
        if(root->right) {
            printTreeZigzag(root->right, level-1, direction_flag);
        }
        if(root->left) {
            printTreeZigzag(root->left, level-1, direction_flag);
        }
    } else {
        if(root->left) {
            printTreeZigzag(root->left, level-1, direction_flag);
        }
        if(root->right) {
            printTreeZigzag(root->right, level-1, direction_flag);
        }
    }
    return;
}

int getHeightTree(bt_node *root) {
    if(!root) {
        return 0;
    }
    int leftHeight = getHeightTree(root->left);
    int rightHeight = getHeightTree(root->right);
    
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

/*
 * Vertical order traversal
 */
void vertical_order(bt_node *root) {
    /* We have to print the tree in vertical order here.
     * The idea is to pass -1 to left node and +1 to right
     * node. Now, to avoid negative numbers, we should use some
     * number for root so that by the time we reach leaf node,
     * our number does not go negative. So for this, we first get
     * height of tree and then the max range numbers can be are
     * from -(height-1) to +(height-1). So we use the number
     * (height-1) as initial number. We maintain a linked list
     * to store the node values for each vertical layer and then
     * finally print it.
     */
    int treeHeight = getHeightTree(root);
    int verticalLevel = treeHeight-1;
    
    ll_node **list = (ll_node**)malloc(sizeof(ll_node*)*2*verticalLevel);
    for(int i=0; i<2*verticalLevel; i++) {
        list[i] = NULL;
    }

    getVerticalOrder(root, verticalLevel, &list);

    /* Now print all the lists */
    for(int i=0; i<2*verticalLevel; i++){
        ll_node *temp = list[i];
        while(temp) {
            printf("%d ", temp->value);
            temp = temp->next;
        }
        printf("\n");
    }
}

void getVerticalOrder(bt_node *root, int verticalLevel, ll_node ***list) {
    if(!root) {
        return;
    }
    
    /* Now add node to the list */
    if(*list[verticalLevel] == NULL) {
        *list[verticalLevel] = newNode(root->value);
    } else {
        ll_node *temp = newNode(root->value);
        ll_node *temp2 = *list[verticalLevel];
        while(temp2->next) {
            temp2 = temp2->next;
        }
        temp2->next = temp;
    }

    /* Now recursively call for left and right childs */
    if(root->left) {
        getVerticalOrder(root->left, verticalLevel-1, list);
    }
    if(root->right) {
        getVerticalOrder(root->right, verticalLevel+1, list);
    }
    return;
}

/*
 * Kth smallest element in the tree
 */
bt_node* kthSmallest(bt_node *root, int k) {
    /* 
     * We do a inorder traversal and keep on decrementing k and return
     * the node when k reaches 0.
     */
    stack_t *stack = NULL;
    bt_node *p = root;

    if(!p) {
        return;
    }

    while(!isEmpty(stack) || p != NULL) {
        if(p) {
            stack_push(stack, p);
            p = p->left;
        } else {
            bt_node *temp = stack_pop(stack);
            k--;
            if(k == 0) {
                return temp;
            }
            p = temp->right;
        }
    }
}

/*
 * Validate Binary search tree
 */
bool isBst(bt_node *root) {
    int min = -1;
    int max = -1;

    return checkIfBst(root, min, max);
}

bool checkIfBst(bt_node *root, int min, int max) {
    if(!root) {
        return true;
    }
    
    if(min == -1 && max == -1) {
        bool left = checkIfBst(root->left, min, root->data);
        bool right = checkIfBst(root->right, root->data, max);
        return (left & right);
    }

    if(min == -1) {
        if(root->data > max) {
            return false;
        }
    }

    if(max == -1) {
        if(root->data <= min) {
            return false;
        }
    }

    if(min != -1 && max != -1) {
        if(root->data <= min || root->data > max) {
            return false;
        }
    }

    bool left = checkIfBst(root->left, min, root->data);
    bool right = checkIfBst(root->right, root->data, max);
    return (left & right);
}

/*
 * Sum path: Given a binary tree and sum, return true if there is path from
 *           root to leaf with given sum.
 */
bool hasSumPath(bt_node *root, int sum) {
    /*
     * We use BFS here. We use 1 queue to store the tree nodes and another one
     * to store the sum values. We check if we reached a leaf node and see if
     * we got the sum to return true.
     */
    if(!root) {
        return false;
    }

    queue_t node_queue, sum_queue;

    enqueue(node_queue, root);
    enqueue(sum_queue, root->value);

    while(!isEmpty(node_queue)) {
        bt_node *currNode = dequeue(node_queue);
        int currSum = dequeue(sum_queue);
        if(!currNode->left && !currNode->right && currSum == sum) {
            return true;
        }

        if(currNode->left) {
            enqueue(node_queue, currNode->left);
            enqueue(sum_queue, currSum + currNode->left->value);
        }
        if(currNode->right) {
            enqueue(node_queue, currNode->right);
            enqueue(sum_queue, currSum + currNode->right->value);
        }
    }

    return false;
}

/*
 * BST Iterator: Implement an iterator for BST which has 2 APIs next() and
 * hasNext(). next() should return next smaller element and hasNext() should
 * return true if an element smaller than current element is present.
 */

/* We use stack to store tree elements in it in inorder fashion. next() will
 * return the top element in stack and hasNext() will check if stack is empty
 */
stack_t *nodes_stack;
void bstIterator(bt_node *root) {
    while(root) {
        stack_push(nodes_stack, root);
        root = root->left;
    }
}

bool bstIteratorHasNext(void) {
    return (!isEmpty(nodes_stack));
}

bt_node* bstIteratorNext(void) {
    bt_node *result = stack_pop(nodes_stack);
    bt_node *temp = result;
    if(temp->right) {
        temp = temp->right;
        while(temp) {
            stack_push(nodes_stack, temp);
            temp = temp->left;
        }
    }
    return result;
}

/*
 * Lowest common ancestor of BST
 */
bt_node* lcaBST(bt_node *root, int l, int r) {
    /*
     * Here assumption is l < r. We check where l and r lie as compared to
     * the root and recursively call the function accordingly. If both lie
     * on different sides or one of them is equal to root then root is the
     * LCA.
     */
    if(!root) {
        return NULL;
    }
    if(root->value > l && root->value > r) {
        return lcaBST(root->left, l, r);
    }
    if(root->value < l && root->value < r) {
        return lcaBST(root->right, l, r);
    }

    return root;
}

/*
 * Lowest common ancestor of Binary Tree (Not BST)
 */
bt_node* lcaBT(bt_node *root, int l, int r) {
    /*
     * Now we do not have a binary search tree. So the properties of BST do not
     * apply. So we search in both left and right subtree for the nodes. If we
     * find nodes in both the subtrees, we return root. If not, then we return
     * that subtree node which has both nodes in it.
     */
    if(!root) {
        return NULL;
    }

    if(root->value == l || root->value == r) {
        return root;
    }

    bt_node *left = lcaBT(root->left, l, r);
    bt_node *right = lcaBT(root->right, l, r);

    if(left && right) {
        return root;
    }
    if(!left && !right) {
        return NULL;
    }
    if(!left) {
        return right;
    } else {
        return left;
    }
}

/*
 * Inorder successor and predecessor
 */
void predecessorSuccessor(bt_node *root, bt_node **pre, bt_node **sc, int key) {
    if(!root) {
        return;
    }

    if(root->value == key) {
        if(root->left) {
            root = root->left;
            while(root->right) {
                root = root->right;
            }
            *pre = root;
        }
        if(root->right) {
            root = root->right;
            while(root->left) {
                root = root->left;
            }
            *sc = root;
        }
        return;
    }

    if(root->value > key) {
        *sc = root;
        predecessorSuccessor(root->left, pre, sc, key);
    } else {
        *pre = root;
        predecessorSuccessor(root->right, pre, sc, key);
    }
}

/*
 * Create a new tree node.
 */
bt_node* bt_new_node(int val) {
    bt_node *new_node = NULL;

    new_node = (bt_node*)malloc(sizeof(bt_node));
    if (!new_node) {
        printf("Error in allocating memory to new node. Returning.");
        return NULL;
    }
    new_node->value = val;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

/*
 * Insert node on left.
 */
bt_node* bt_insert_left(bt_node *root, int val) {
    bt_node *new_node;

    new_node = bt_new_node(val);
    if(!root->left) {
        root->left = new_node;
        return root;
    } else {
        new_node->left = root->left;
        root->left = new_node;
        return root;
    }
}

/*
 * Insert node on right.
 */
bt_node* bt_insert_right(bt_node *root, int val) {
    bt_node *new_node;

    new_node = bt_new_node(val);
    if(!root->right) {
        root->right = new_node;
        return root;
    } else {
        new_node->right = root->right;
        root->right = new_node;
        return root;
    }
}
