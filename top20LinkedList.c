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

        // If there was a mid node (odd size case) which                                         // was not part of either first half or second half.
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
