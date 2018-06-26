#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Tree node
typedef struct tree_node {
    int val;
    struct tree_node* left;
    struct tree_node* right;
}tree_node;

// Node for linked list which represents stack
typedef struct node {
    int val;
    struct node *next;
}node;

// Stack node to store tree nodes
typedef struct stack_tree_node {
    struct tree_node *tree;
    struct stack_tree_node *next;
}stack_tree_node;

// New node for tree
tree_node* new_tree_node(int val) {
    tree_node *temp = (tree_node*)malloc(sizeof(tree_node));
    temp->val = val;
    temp->right = NULL;
    temp->left = NULL;
    return temp;
}

void stack_push_tree(stack_tree_node **top, tree_node *tree) {
    stack_tree_node *new_node = (stack_tree_node*)malloc(sizeof(stack_tree_node));
    new_node->tree = tree;
    if(!*top) {
        new_node->next = NULL;
        *top = new_node;
        return;
    } else {
        new_node->next = *top;
        *top = new_node;
        return;
    }
}

tree_node* stack_pop_tree(stack_tree_node **top) {
    if(!*top) {
        printf("Stack is Empty.\n");
        return NULL;
    }
    stack_tree_node *temp = *top;
    *top = (*top)->next;
    tree_node *tree = temp->tree;
    temp->next = NULL;
    free(temp);
    temp = NULL;
    return tree;
}

tree_node* stack_peep_tree(stack_tree_node *top) {
    if(!top) {
        printf("Stack is Empty.\n");
        return NULL;
    }
    return top->tree;
}

void stack_push(node **top, int val) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->val = val;
    if(!*top) {
        new_node->next = NULL;
        *top = new_node;
        return;
    } else {
        new_node->next = *top;
        *top = new_node;
        return;
    }
}

int stack_pop(node **top) {
    if(!*top) {
        printf("Stack is Empty.\n");
        return -1;
    }
    node *temp = *top;
    *top = (*top)->next;
    int val = temp->val;
    temp->next = NULL;
    free(temp);
    temp = NULL;
    return val;
}

int stack_peep(node *top) {
    if(!top) {
        printf("Stack is Empty.\n");
        return -1;
    }
    return top->val;
}

void print_stack(node *top) {
    if(!top) {
        return;
    }
    node *temp = top;
    printf("Current Stack is:\n");
    while(temp) {
        printf("%d ", temp->val);
        temp = temp->next;
    }
    printf("\n");
    return;
}

int stack_len(node *top) {
    if(!top) {
        return 0;
    }
    int count = 0;
    while(top) {
        count++;
        top = top->next;
    }
    return count;
}

/*
 * 1. Simplify the path: Given a string as it would be in a typical cd command
 *    like "/a/b/../../c/", return a string with simplified path like "/c"
 *
 *    Here we have to consider multiple things as below:
 *    1. If we have multiple consecutive '/', ignore them
 *    2. If we have '..' then it means go back one path.
 *    3. If we have '.' then do nothing.
 *    4. If we have '/' in the end of string, ignore it.
 *
 *    Our algo is, first we parse the string and do following:
 *    1. If we encounter a '/' then keep going forward until we get next
 *       char which is not a '/'.
 *    2. If we get a '.' check the next char. If it is also a '.' then pop the
 *       element from the stack. Check if stack is empty before popping. If empty,
 *       then print warning and ignore.
 *    3. If we get a '.' and next char is not a '.', then do nothing.
 *    4. If we get a alphabet, then push this into stack.
 *    5. Finally check if stack is empty or not. If empty, return a '/'
 *       If not, then create a string by popping the elements from stack
 *       and reverse this string and return it.
 */
char* simplifyPath(char *path) {
    if(!path) {
        return NULL;
    }
    int len = strlen(path);
    if(len == 0) {
        return NULL;
    }
    node *top = NULL;
    int i = 0;
    while(i < len) {
        // If a /, then proceed
        if(path[i] == '/') {
            i++;
        }
        // If a ., then see if next is also a .
        // If not, proceed, if yes then pop
        if(path[i] == '.') {
            if(i<len-1 && path[i+1] != '.') {
                i++;
            } else {
                stack_pop(&top);
                i = i+2;
            }
        }
        // If a char, then push into stack
        if(path[i] >= 'a' && path[i] <= 'z') {
            stack_push(&top, path[i]);
            i++;
        }
    }

    // Now we build a string to return from the stack
    int s_len = stack_len(top);
    if(s_len == 0) {
        // Stack is empty. So return '/'
        char *ret_emp = (char*)malloc(sizeof(char)*1);
        ret_emp[0] = '/';
        return ret_emp;
    }
    char *ret = (char*)malloc(sizeof(char)*s_len);
    int j;
    for(j=s_len-1; j>=0; j--) {
        ret[j] = (char)stack_pop(&top);
    }
    return ret;
}

/*
 * 2. Tree traversals interative using stack
 *    Do a Inorder tree traversal without recursion
 */
void InorderIterative(tree_node *root) {
    if(!root) {
        return;
    }
    // Initialize a stack
    stack_tree_node *top=NULL;
    // Push root into stack to start with
    stack_push_tree(&top, root);
    
    // Start a loop while stack is not empty
    while(top) {
        tree_node *temp = stack_peep_tree(top);
        while(temp->left) {
            temp = temp->left;
            stack_push_tree(&top, temp);
        }
        temp = stack_pop_tree(&top);
        printf("%d ", temp->val);
        while(!temp->right) {
            if(!top) {
                return;
            }
            temp = stack_pop_tree(&top);
            printf("%d ", temp->val);
        }
        stack_push_tree(&top, temp->right);
    }
}

/*
 * 3. Next greater Element: Given a list of temperatures
 *    return a list of number of days each day has to wait for warmer
 *    temperature.
 *
 *    Basically this is a next greater element question. For each element in
 *    the array, we need to find out the index of next greater element in it.
 *
 *    We use stack. We push first element of the list in the stack and then
 *    we iterate for rest of the list. For each element in the list, pop the
 *    stack and compare the popped element with the current element. If current
 *    element is greater than popped element, then the next greater element of
 *    popped element is current element. We keep popping till we get popped
 *    element greater than current element. In this case, we push back that element
 *    and come out of loop. Then we push the current element in the stack and
 *    continue to iterate for rest of the list. At the end of the list, the elements
 *    which are still in stack have no next greater element.
 *
 *    We need to keep track of indices also, so we use special stack node structure
 *    for this case.
 */
typedef struct nxt_grtr_node {
    int temp;
    int index;
    struct nxt_grtr_node *next;
}nxt_grtr_node;

void nxtGrtrPush(nxt_grtr_node **top, int temp, int index) {
    nxt_grtr_node *new_node = (nxt_grtr_node*)malloc(sizeof(nxt_grtr_node));
    new_node->temp = temp;
    new_node->index = index;
    if(!*top) {
        new_node->next = NULL;
        *top = new_node;
    } else {
        new_node->next = *top;
        *top = new_node;
    }
}

nxt_grtr_node* nxtGrtrPop(nxt_grtr_node **top) {
    if(!*top) {
        return NULL;
    }
    nxt_grtr_node *tempo = *top;
    *top = (*top)->next;
    tempo->next = NULL;
    return tempo;
}

int* nextWarmerDay(int *list, int len) {
    nxt_grtr_node *top = NULL;
    nxt_grtr_node *prev;
    if(!list || len == 0) {
        return NULL;
    }
    int i;
    int *result = (int*)malloc(sizeof(int)*len);

    // Push the first element in the stack
    nxtGrtrPush(&top, list[0], 0);

    // Iterate rest of the list
    for(i=1; i<len; i++) {
        int curr_temp = list[i];
        prev = nxtGrtrPop(&top);
        // If stack is not empty
        if(prev) {
            while(prev->temp < curr_temp) {
                result[prev->index] = (i - prev->index);
                prev = nxtGrtrPop(&top);
                if(!prev) {
                    break;
                }
            }
            // At this point, we have prev which is greater than curr
            // so push this back
            if(prev) {
                nxtGrtrPush(&top, prev->temp, prev->index);
            }
        }
        // Lastly, push the current element in the stack
        nxtGrtrPush(&top, curr_temp, i);
    }

    // Now for all the elements still in the stack, we put -1
    // in the result as they are not going to see warmer day
    prev = nxtGrtrPop(&top);
    while(prev) {
        result[prev->index] = -1;
        prev = nxtGrtrPop(&top);
    }
    return result;
}

/*
 * 4. Asteroid Collision: Given an array of asteroids where value means the size
 *    of asteroid and sign (+/-) means direction (right/left). If there are asteroids
 *    moving in opposite direction, collision will happen and after collision, larger
 *    asteroid remains. If size is same, both are destroyed. Return array after all
 *    collisions.
 *
 *    We use stack here. We traverse the given array and for each +ve element, we
 *    push it into stack. When we get a -ve element, we see if stack is empty. If
 *    empty, this element goes into our result array. If not empty, then we compare
 *    the absolute value of this element with the popped element. if popped element
 *    is greater, we push it back into stack and continue our iteration. If popped
 *    element is smaller, we keep popping the elements until we get a greater element.
 *    Finally after we have traversed the entire length, all the elements present in
 *    the stack go to our result array.
 *
 *    NOT IMPLEMENTING THIS AS IT IS STRAIGHTFORWARD TO IMPLEMENT
 */

/*
 * 5. Remove K letters from the given string so that it becomes minimum number
 *    A string is given which represents a number. We have to remove k chars from
 *    the string so that it represents minimum possible number.
 *
 *    The main concept is, while traversing from left to right, if we remove the
 *    first digit which is greater than its next digit, then the remaining number
 *    becomes minimum. If we do this for k times, we get the solution. To do it in O(n)
 *    we use stack. First we push the first char into stack. Then from next char onwards
 *    for each char, if stack is empty, push it and continue, else, pop the element
 *    and check if popped element is greater than current. If yes, then keep popping
 *    until popped element is smaller than current or the value k is reached.
 *    (We decrement k for each pop). If the popped element is smaller, push it back in
 *    and push current element and continue. In the end of strlen, if k == 0,
 *    we build string by popping all elements from stack and return reverse of this
 *    string. If k is not reached, we pop k elements from stack and then build the
 *    string with remaining elements in the stack.
 */

/*
 * 6. Sort a stack with only push and pop operations.
 *    Here we use 1 additional stack say temp_stack. The algo is: while givenStack
 *    is not empty, pop the element. If temp_stack is empty, push this element to
 *    temp_stack. If not empty, then while top of temp_stack is greater than our
 *    popped element, pop from temp_stack and push it to orignal stack. Finally push
 *    our original popped element to temp stack. Keep doing this till original stack
 *    becomes empty. At this time, temp_stack has all the elements sorted.
 */

int main(void) {
    /* Simplify paths */
    char path[18] = "/../../..//../../\0";
    printf("\nThe given path is: %s\n", path);
    char *simplified_path = simplifyPath(path);
    printf("The simplified path is: %s\n", simplified_path);

    /* Iterative Inorder */
    tree_node *root = (tree_node*)malloc(sizeof(tree_node));
    root->val = 3;
    root->left = new_tree_node(2);
    root->right = new_tree_node(4);
    root->left->left = new_tree_node(1);
    root->right->right = new_tree_node(5);
    printf("Inorder traversal of tree is:\n");
    InorderIterative(root);
    printf("\n");

    /* Next warmer day */
    int list[8] = {73, 74, 75, 71, 69, 72, 76, 73};
    printf("\nList of temperatures is:\n");
    for(int i=0; i<8; i++) {
        printf("%d ", list[i]);
    }
    printf("\n");
    int *result = nextWarmerDay(list, 8);
    printf("\nList of next warmer day is:\n");
    for(int i=0; i<8; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}
