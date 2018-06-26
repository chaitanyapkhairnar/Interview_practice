/*
 * This File contains Top 20 most common Linked List questions.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Linked list node structure
typedef struct node {
    int val;
    struct node *next;
}node;

// Tree node structure
typedef struct tree_node {
    int val;
    struct tree_node *left;
    struct tree_node *right;
}tree_node;

// Helper function to create a new linked list node
node* new_node(int val) {
    node *temp = (node*)malloc(sizeof(node));
    temp->val = val;
    temp->next = NULL;
    return temp;
}

// Helper function to print the list
void print_list(node *root) {
    if(!root) {
        return;
    }
    printf("The current list is:\n");
    while(root) {
        printf("%d ", root->val);
        root = root->next;
    }
    printf("\n");
}

/************************** Questions **************************/

/* 1. Get the middle node of given linked list */
node* GetMiddle(node *root) {
    node *slow = root, *fast = root, *prev = NULL;
    int len = 0;
    if(!root) {
        printf("List is empty.\n");
        return NULL;
    }
    if(!root->next) {
        printf("Single element in the list.\n");
        return NULL;
    }
    while(fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
        len = len+2;
        if(!fast) {
            len = len-1;
            break;
        }
    }
    // If the length of list is even, fast will be pointing to NULL and
    // slow will be pointing to second mid. If the length of list is
    // odd, fast will be pointing to last node and slow will be
    // pointing to mid element.
    if(len%2) {
        printf("List is of even length. First middle element is %d and "
               "second middle element is %d\n", prev->val, slow->val);
    } else {
        printf("List is of odd length. Middle Element is %d\n", slow->val);
    }
    return slow;
}

/* 2. Merge two sorted lists */
node* MergeSortedLists(node *list1, node *list2) {
    node *new_list;
    if(!list1) {
        return list2;
    }
    if(!list2) {
        return list1;
    }
    if(list1->val < list2->val) {
        new_list = list1;
        new_list->next = MergeSortedLists(list1->next, list2);
    } else {
        new_list = list2;
        new_list->next = MergeSortedLists(list1, list2->next);
    }
    return new_list;
}

/* 3. Delete middle element of list */
void DeleteMiddle(node *root) {
    if(!root) {
        return;
    }
    if(!root->next) {
        return;
    }

    node *slow = root, *fast = root, *prev = NULL;
    while(fast->next) {
        fast = fast->next->next;
        prev = slow;
        slow = slow->next;
        if(!fast) {
            break;
        }
    }
    /* Now slow is pointing to the node to be deleted. */
    prev->next = slow->next;
    slow->next = NULL;
    free(slow);
    slow = NULL;
    return;
}

/* 4. Remove duplicate elements from sorted list */
void RemoveDuplicatesSorted(node *root) {
    if(!root) {
        return;
    }
    if(!root->next) {
        return;
    }
    node *start=root, *end=root->next;
    while(end) {
        while(end->val == start->val) {
            end = end->next;
            if(!end) {
                break;
            }
        }
        start->next = end;
        start = end;
        if(!start) {
            break;
        }
        end = start->next;
    }
    return;
}

/* 5. Add 1 to a number represented as a linked list. Assume head node of list
 * represents units digit of number.
 */
node* AddOneToList(node *root, int carry) {
    if(!root) {
        node *temp = new_node(1);
        return temp;
    }
    if(root->val < 9) {
        root->val = root->val + 1;
        return root;
    } else {
        root->val = 0;
        root->next = AddOneToList(root->next, 1);
    }
    return root;
}

/* 6. Add given digit to a number represented as a linked list. Assume head node of list
 * represents units digit of number.
 */
node* AddDigitToList(node *root, int digit) {
    if(!root) {
        node *temp = new_node(digit);
        return temp;
    }
    if(((root->val) + digit) < 10) {
        root->val = root->val + digit;
        return root;
    } else {
        int carry;
        int sum = root->val + digit;
        carry = sum/10;
        root->val = sum%10;
        root->next = AddDigitToList(root->next, carry);
    }
    return root;
}

/* 7. Reverse a Linked list. */
node* ReverseList(node *root) {
    if(!root) {
        return root;
    }
    if(!root->next) {
        return root;
    }
    node *prev=NULL, *curr=root, *next=NULL;

    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    root = prev;
    return root;
}

/* 8. Reverse a Linked List in groups of given size */
node* ReverseListGroups(node *root, int size) {
    if(!root) {
        return root;
    }
    int count = 0;
    node *prev=NULL, *curr=root, *next=NULL;
    while(curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
        if(count == size) {
            break;
        }
    }
    root->next = ReverseListGroups(curr, size);

    return prev;
}

/* 9. Detect the loop in Linked list and return the node at which there is
 * a cycle. */
node* DetectLoopAndRemoveIt(node *root) {
    if(!root) {
        return NULL;
    }
    if(!root->next) {
        return NULL;
    }
    node *slow=root, *fast=root;
    node *prev=NULL;
    while(1) {
        fast = fast->next->next;
        slow = slow->next;
        if(!fast || !fast->next) {
            printf("No loop present in the list.\n");
            return NULL;
        }
        if(slow == fast) {
            printf("Loop present in the list.\n");
            slow = root;
            while(slow!=fast) {
                prev = fast;
                slow = slow->next;
                fast = fast->next;
            }
            prev->next = NULL;
            return slow;
        }
    }
}

/* 10. Find nth node from the end of list */
node* NthNode(node *root, int n) {
    if(!root) {
        printf("List is empty.\n");
        return NULL;
    }
    node *front=root, *back=root;
    int count = 0;
    while(front) {
        while(count < n) {
            front = front->next;
            count++;
            if(!front) {
                printf("List is short than n\n");
                return NULL;
            }
        }
        back = back->next;
        front = front->next;
    }
    return back;
}

/* 11. Check if the List is Palindrome */
bool IsPalindrome(node *head) {
    node *slow = head, *fast = head;
    node *second_half, *prev_of_slow = head;
    node *midnode = NULL;
    bool res = true;

    if (head!=NULL && head->next!=NULL) {
        /* Get the middle of the list */
        while (fast != NULL && fast->next != NULL) {
            fast = fast->next->next;

            /* We need previous of the slow for
             linked lists  with odd elements */
            prev_of_slow = slow;
            slow = slow->next;
        }
        /* fast will be NULL only when there are even elements in list.
           And it is not NULL for odd elements. We need to skip the middle node
           for odd case and store it somewhere so that we can restore the
           original list */
        if (fast != NULL) {
            midnode = slow;
            slow = slow->next;
        }

        // Now reverse the second half and compare it with first half
        second_half = slow;
        prev_of_slow->next = NULL;
        second_half = ReverseList(second_half);
        node *temp1 = head, *temp2 = second_half;
        while(temp1 && temp2) {
            if(temp1->val != temp2->val) {
                res = false;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }

        /* Construct the original list back */
        second_half = ReverseList(second_half);

        // If there was a mid node (odd size case) which
        // was not part of either first half or second half.
        if (midnode != NULL) {
            prev_of_slow->next = midnode;
            midnode->next = second_half;
        }
        else {
            prev_of_slow->next = second_half;
        }
    }
    return res;
}

/* 12. Check if the given two lists intersect and if yes, return the node
 * of intersection */
node* IntersectionOfList(node *list1, node *list2) {
    if(!list1 || !list2) {
        return NULL;
    }
    int len1=1, len2=1;
    node *temp1=list1, *temp2=list2;
    // Get the last node of both the lists to check if they intersect
    // or not. Get lengths also during this.
    while(temp1->next) {
        temp1 = temp1->next;
        len1++;
    }
    while(temp2->next) {
        temp2 = temp2->next;
        len2++;
    }
    if(temp1 != temp2) {
        // Last nodes of the lists are not same, so they do not
        // intersect.
        return NULL;
    }

    // If last nodes of both lists are same, that means they intersect.
    // Now get the diff of lengths and move the pointer of longer list
    // ahead by diff amount of nodes.
    int diff=len1-len2;
    temp1 = list1;
    temp2 = list2;
    if(diff < 0) {
        diff = abs(diff);
        for(int i=0; i<diff; i++) {
            temp2 = temp2->next;
        }
    } else {
        for(int i=0; i<diff; i++) {
            temp1 = temp1->next;
        }
    }

    // Now both the pointers are at same distance from end on their respective
    // lists. Now we traverse both together and check for intersection for each
    // step.
    while(temp1 && temp2) {
        if(temp1 == temp2) {
            return temp1;
        }
        temp1 = temp1->next;
        temp2 = temp2->next;
    }
    // We never reach here.
    return NULL;
}

/* 13. Delete the complete list */
void DeleteList(node *root) {
    while(root) {
        node *temp = root->next;
        root->next = NULL;
        free(root);
        root = temp;
    }
    return;
}

/* 14. Merge 2nd list into 1st list at alternate positions only when there is
 *     a place in 1st list. Rest nodes in list 2 should remain there with the head
 *     pointer modified.
 */
void MergeListsAlternate(node **list1, node **list2) {
    if(!*list1 || !*list2) {
        return;
    }
    node *list1_prev, *list1_curr, *list2_curr, *list2_nxt;

    list1_prev = *list1;
    list1_curr = (*list1)->next;
    list2_curr = *list2;
    list2_nxt = list2_curr->next;

    while(list1_curr) {
        list1_prev->next = list2_curr;
        list2_curr->next = list1_curr;
        list2_curr = list2_nxt;
        if(!list2_curr) {
            break;
        }
        list2_nxt = list2_curr->next;
        list1_prev = list1_curr;
        if(!list1_prev) {
            break;
        }
        list1_curr = list1_prev->next;
    }
    //Update the head of list2
    *list2 = list2_curr;
    return;
}

/* 15. Delete the last occurance of the given key from the given list. */
void DeleteLastOccurance(node *root, int key) {
    if(!root) {
        return;
    }
    node *temp, *last_occ = NULL;
    temp = root;
    while(temp) {
        if(temp->val == key) {
            last_occ = temp;
        }
        temp = temp->next;
    }
    if(!last_occ) {
        printf("Key not found\n");
        return;
    }

    // We have found the node in which the key has last occurance. Now we have to
    // delete this node. But we do not have previous node info. So what we do is
    // copy the next node value into present node and delete the next node. Remember
    // this concept.
    temp = last_occ->next;
    last_occ->val = temp->val;
    last_occ->next = temp->next;
    temp->next = NULL;
    free(temp);
    return;
}

/* 16. Rotate list anticlockwise by given value */

/* 17. Convert Sorted list to BST */

/* 18. Flatten Binary Tree to List:
 *     Flatten the tree such that the list is in preorder order.
 *     We make left of each node null so that the node now has only
 *     right pointer and thus it can be represented as list where right means
 *     next. We do it in place. The idea is, for each node starting from root, check
 *     if it has a left child. If yes, then get the rightmost child of this left child
 *     and put the entire right subtree of current node to this rightmost child's right.
 *     Then move entire left subtree of current node to right and make left null.
 *     We do this because, in preorder, the node previous of current node is the rightmost
 *     child node of left child of present node.
 */
void FlattenBstPreorder(tree_node *root) {
    if(!root) {
        return;
    }
    while(root) {
        if(root->left) {
            tree_node *rightmost = root->left;
            while(rightmost->right) {
                rightmost = rightmost->right;
            }
            rightmost->right = root->right;
            root->right = root->left;
            root->left = NULL;
        }
        root = root->right;
    }
    return;
}

/*
 * Another way to flatten the tree is to flatten using extra space recursively.
 * Here, we create three lists say list1, list2, list3. Say we want to flatten 
 * the tree Inorder.So first recursively call flatten function for root->left 
 * and store it in list1, then store the current root->val in list2. This list 
 * has single node. Then in list3, store the return value of flatten func for 
 * root->right. Now append these lists such that list1->list2->list3. And 
 * return the correct head. This is more general method to flatten the tree and 
 * can be done for any order traversal.
 */
node* FlattenBstGeneral(tree_node *root) {
    if(!root) {
        return NULL;
    }
    node *list1 = NULL, *list2 = NULL, *list3 = NULL;
    list1 = FlattenBstGeneral(root->left);
    list2 = new_node(root->val);
    list3 = FlattenBstGeneral(root->right);

    // Append the lists.
    list2->next = list3;

    if(!list1) {
        return list2;
    }
    node *temp = list1;
    while(temp->next) {
        temp = temp->next;
    }
    temp->next = list2;
    return list1;
}

/*
 * One more way for flattening the tree is flatten it to double linked list such
 * that left will be prev and right will be next.
 *
 * We convert BST to Double Linked List in Inorder fashion.
 * For each node, we see if left child exists, then recursively call the function 
 * for left child and store the returned value in say left. now find the rightmost 
 * child of this left and this will be the inorder predessesor of our root. so link 
 * root->left to this predessesor and predessesor->right.
 * Now see if root->right exists. If yes follow same procedure above but now we find 
 * inorder successor and link it to our root. Finally we return root. Then in another
 * function, we move root to leftmost node which is now the head of our double linked
 * list.
 * Note: we are using tree_node only here to represent both bst as well as double linked list.
 */
tree_node* Flatten(tree_node *root) {
    if(!root) {
        return NULL;
    }
    if(root->left) {
        tree_node *left = Flatten(root->left);
        while(left && left->right) {
            left = left->right;
        }
        root->left = left;
        if(left) {
            left->right = root;
        }
    }
    if(root->right) {
        tree_node *right = Flatten(root->right);
        while(right && right->left) {
            right = right->left;
        }
        root->right = right;
        if(right) {
            right->left = root;
        }
    }
    return root;
}

tree_node* FlattenBstToDll(tree_node *root) {
    if(!root) {
        return NULL;
    }
    tree_node *temp = Flatten(root);
    while(temp->left) {
        temp = temp->left;
    }
    return temp;
}

/* 19. MergeSort List */

/* 20. Flatten a nested list */

/* Main drive function to test the functionalities. */
int main(void) {
    node *list1, *temp1;
    list1 = new_node(0);

    node *list2, *temp2;
    list2 = new_node(2);

    node *duplicateList, *temp3;
    duplicateList = new_node(1);

    temp1 = list1;
    temp2 = list2;
    temp3 = duplicateList;

    for(int i=1; i<19; i=i+2) {
        temp1->next = new_node(i);
        if(temp1->next) {
            temp1 = temp1->next;
        }
    }

    for(int i=4; i<23; i=i+2) {
        temp2->next = new_node(i);
        if(temp2->next) {
            temp2 = temp2->next;
        }
    }

    for(int i=2; i<11; i++) {
        for(int j=0; j<i; j++) {
            temp3->next = new_node(i);
            if(temp3->next) {
                temp3 = temp3->next;
            }
        }
    }

    print_list(list1);
    print_list(list2);

    /* Merge two lists in alternate pattern */
    printf("\nMerging below two lists\n");
    print_list(list1);
    print_list(list2);
    MergeListsAlternate(&list1, &list2);
    printf("\nLists after the merge are\n");
    print_list(list1);
    print_list(list2);
    
    /* Reverse the list */
    printf("\nReverse of list1 is:\n");
    list1 = ReverseList(list1);
    print_list(list1);

    list1 = ReverseList(list1);

    /* Reverse list in groups */
    printf("\nReverse of list1 in groups of 3 is:\n");
    list1 = ReverseListGroups(list1, 3);
    print_list(list1);

    /* Middle element */
    GetMiddle(list1);

    /* Delete the middle element */
    DeleteMiddle(list1);
    printf("After deleting the middle element\n");
    print_list(list1);

    /* Merge sorted lists */
    node *merged_list = MergeSortedLists(list1, list2);
    print_list(merged_list);

    /* Remove Duplicates from sorted list */
    printf("\nTesting removal of duplicate nodes from the list\n");
    print_list(duplicateList);
    RemoveDuplicatesSorted(duplicateList);
    print_list(duplicateList);

    /* Add 1 to a number represented by the list */
    node *number = new_node(9);
    number->next = new_node(9);
    number->next->next = new_node(8);
    number->next->next->next = new_node(9);
    printf("\nTesting adding 1 to a number represented by list.\n");
    print_list(number);
    number = AddOneToList(number, 0);
    print_list(number);

    printf("\nTesting adding digit 9 to a number represented by list.\n");
    print_list(number);
    number = AddDigitToList(number, 9);
    print_list(number);

    printf("\nTesting adding digit 9 to a number represented by list.\n");
    print_list(number);
    number = AddDigitToList(number, 9);
    print_list(number);

    /* Determine loop in the list */
    printf("\nDetecting loop in list1.\n");
    DetectLoopAndRemoveIt(list1);

    node *loop_list = new_node(1);
    node *temp = loop_list;
    node *loop_node = NULL;
    for(int i=2; i<21; i++) {
        temp->next = new_node(i);
        temp = temp->next;
        if(i == 13) {
            loop_node = temp;
        }
    }
    temp->next = loop_node;

    printf("\nDetecting loop in loop_list.\n");
    temp = NULL;
    temp = DetectLoopAndRemoveIt(loop_list);
    if(temp) {
        printf("Loop was at node: %d\n", temp->val);
    }
    printf("After loop removal, ");
    print_list(loop_list);


    return 0;
}
