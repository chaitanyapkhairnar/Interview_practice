/*
 * This file contains the problems asked in previous Microsoft
 * Interviews.
 */

1. Given a linked list having two pointers in each node. The first one points
   to the next node of the list, however the other pointer is random and can
   point to any node of the list. Write a program that clones the given list
   in O(1) space, i.e., without any extra space.

A. 1. Create a copy of node 1 and put it between node 1 and 2. Create a copy
      of node 2 and place it between node 2 and 3 and so on. For last node,
      create a copy and put it next to last node at the end.
   2. Now we copy the random pointers from original list to copy list. For
      each node, we do, orig_node->next->rand = orig_node->rand->next.
      Here orig_node->next->rand means the rand pointer of copy node
      and orig_node->rand->next means the copy node corresponding to
      the original node. (because we are putting copy node after original
      list).
   3. Finally, we seperate the original and copy lists by doing
      copy_node = orig_node->next;
      orig_node->next = orig_node->next->next;
      copy_node->next = copy_node->next->next;
      Make sure that last node of orig list points to NULL.
   4. Return the copy list head.

   Time complexity is O(n) and Space required is O(1).

ll_node* cloneList(ll_node *orig_head) {
    if(!orig_head) {
        return NULL;
    }
    ll_node *head = orig_head;

    /* Create a copy node for each orig node */
    while(head) {
        ll_node *temp_copy = newNode(head->val);
        temp_copy->next = head->next;
        head->next = temp_copy;
        head = temp_copy->next;
    }

    /* Now clone the rand pointers */
    head = orig_head;
    while(head && head->next) {
        head->next->rand = head->rand->next;
        head = head->next->next;
    }

    /* Now seperate the lists */
    ll_node *copy_head = orig_head->next;
    ll_node *copy_temp;
    head = orig_head;
    while(head && head->next) {
        copy_temp = head->next;
        head->next = head->next->next;
        if(copy_temp->next) {
            copy_temp->next = copy_temp->next->next;
        }
        head = head->next;
        copy_temp = copy_temp->next;
    }

    return copy_head;
}

2. Find Lowest common ancestor of a binary tree. (Not BST).
A  We use recursion here. We first check if the node is equal to any of the
   given nodes whose ancestor needs to be found out. If yes, return this
   node. The we call recursion for node->left and for node->right. Then we
   check if both these are true. If yes, we return the node as one given
   node is present in node->left and another is present in node->right
   so this node is the common ancestor. If not, then we return that
   node whichever is non NULL. We can extend this approach for n-ary tree
   too.

   Time complexity is O(n) where n is number of nodes in the tree.
   
tree_node* LCABinaryTree(tree_node *root, int val1, int val2) {
    if(!root) {
        return NULL;
    }

    if(root->val == val1 || root->val == val2) {
        return root;
    }

    tree_node *leftLCA = LCABinaryTree(root->left, val1, val2);
    tree_node *rightLCA = LCABinaryTree(root->right, val1, val2);

    if(leftLCA && rightLCA) {
        return root;
    } else if(leftLCA) {
        return leftLCA;
    } else {
        return rightLCA;
    }
}

A  Another way to do this is to get path to val1 from root and get path to val2
   from root and then traverse this path until the values are equal. The last
   equal node is the LCA. We can use this approach for n-ary tree. To find the
   path, we use DFS to find the path and array to store the path.

3. Given a root to a binary tree, clone it and return the root of clone.
A  This can be done by using DFS by simple recursion way.
tree_node* cloneTree(tree_node *root) {
    if(!root) {
        return NULL;
    }
    tree_node *clone = newNode(root->val);
    clone->left = cloneTree(root->left);
    clone->right = cloneTree(root->right);

    return clone;
}

4. Given a string of characters, return the run length encoded string.
A  Run length encoding for string aaabcccccddd is a3b1c5d3. We create
   a new string of length equal to given string. Then we traverse the
   given string and for each char, we first copy it to our dest string
   and start another iterator j from i+1 and keep incrementing it while
   str[i]==str[j] and also increment the count. Finally, we do i=j and
   write this count into the string. We use a char array to first store
   this integer count into, then we copy this char array to our result
   string. We use sprintf to copy int count to char array.

   Time complexity is O(n)
   
char* runLengthEncode(char *str) {
    if(!str) {
        return NULL;
    }
    int len = strlen(str);
    char count[100];
    int k=0, c=1;
    char *res = (char*)malloc(sizeof(char)*len);
    
    for(int i=0; i<len; i++) {
        int j=i+1;
        res[k] = str[i];
        k++;
        while(str[i] == str[j]) {
            c++;
            j++;
        }
        i=j;

        sprintf(count, "%d", c);
        int count_len = 0;
        while(c) {
            c = c/10;
            count_len++;
        }

        for(int z=0; z<count_len; z++) {
            res[k] = count[z];
            k++;
        }
    }
    res[k] = '\0';
    return res;
}

5. Design an API for contact search in phonebook. Which datastructure will you
   use?
A  We use Trie to store all the contacts and their info. Each node will
   represent a char of name of contact and the node where the contact name is
   complete will have a eof flag set to true along with other info such as
   contact name, contact number, contact address, etc. Whenever an user starts
   typing characters to search for a contact, we start traversing the trie
   from root. We traverse till the node with the char last entered by user.
   From here, we will walk through all the child nodes till we reach eof node
   and return the contact info in the form of a list. This will act as
   suggestion to the user.

6. Implement memcpy.
A  memcpy copies the X bytes data from source address to destination address.
   format of memcpy is memcpy(dst, src, X). dst and src are of void pointer
   type and X is int value representing bytes. A simple way to approach is
   first typecase src and dst to char pointers because char is 1 byte size.
   Then start a for loop for X and copy data from src to dst as below

void memcpy(void *dst, void *src, int size) {
    char *csrc = (char*)src;
    char *cdst = (char*)dst;

    for(int i=0; i<size; i++) {
        cdst[i] = csrc[i];
    }
}

   But the problem faced is in the case where there is overlap of address
   between src and dst. So, to tackle this, from the addresses and size,
   we figure out where is the overlap? Is it in the end part or in the start
   part. If it is in the end part, we start copying from end to first. If it
   is in the first part, then we start copying from first to end. Here first
   and end part refers to the src address. So overlap in the end part of src
   address means that end of src overlaps first of dst. So, it is better to
   start copying from the end of src and work our way up.

7. Multiple Reader Single Writer problem and how to use lock to solve this?
A  See the link below for detailed explanation
   https://en.wikipedia.org/wiki/Readers%E2%80%93writers_problem

8. Given a list of commands like up, down, front, back, etc. and an initial
   position in x,y corordinates, return the final position. How would you
   handle undo? How will you use classes for this? What type of design pattern
   is this?
A  We can define actions in a dictionary which will return a x,y coordinate
   to be added to our current coordinates for that particular action. e.g.
   UP will return -1,0 which means if we are at x,y and UP action is called,
   then after this action, out new position will be x-1,y. Once we have this,
   we read the list of actions, and for each action, we update our x,y.

   Now, to handle undo, we use stack. For each action read from the list,
   we update x,y and also push this action to stack. If undo is called, we
   pop the top element of the stack and now do a reverse action. Basically,
   we get the x,y coordinates for this popped action from dictionary and
   multiple this with -1 and then update our present co-ordinates.

   We can use command design pattern here. We define an abstract class
   command which has only 1 pure virtual function execute().
   Now, we define derived classes of this command class for each action
   like class up, class undo_up, class down, class undo_down, ...
   For each of these classes, we have x and y coordinates as member
   variables and we set these in the constructor. They define the
   execute() function according to their action. execute() function
   does not take any arguments but returns x and y coordinates.
   execute for UP class will return x-1,y. Similary, for undo_up,
   it will return x+1,y. Now in main function, we read the first
   command and create an object of that command with x,y and call
   x,y = execute(). Now with this new x,y we create object of next
   action read and call execute on it. We continue doing it. See command
   pattern on geeks for geeks for more info.

9. Given a linked list, move all even elements before the odd elements
   while maintaining the order.
A  We first get the last node of the linked list. Then we traverse from the
   start of the list and while we get odd value elements in the list, we
   keep moving them to the end. When we get first even element, we update
   head to point to this element and then for each node, we check if it is
   odd. If yes, we move this node to the end and continue.

void segregateEvenOdd(struct Node **head_ref)
{
    struct Node *end = *head_ref;
    struct Node *prev = NULL;
    struct Node *curr = *head_ref;
 
    /* Get pointer to the last node */
    while (end->next != NULL)
        end = end->next;
 
    struct Node *new_end = end;
 
    /* Consider all odd nodes before the first even node
       and move then after end */
    while (curr->data %2 != 0 && curr != end)
    {
        new_end->next = curr;
        curr = curr->next;
        new_end->next->next = NULL;
        new_end = new_end->next;
    }
 
    // 10->8->17->17->15
    /* Do following steps only if there is any even node */
    if (curr->data%2 == 0)
    {
        /* Change the head pointer to point to first even node */
        *head_ref = curr;
 
        /* now current points to the first even node */
        while (curr != end)
        {
            if ( (curr->data)%2 == 0 )
            {
                prev = curr;
                curr = curr->next;
            }
            else
            {
                /* break the link between prev and current */
                prev->next = curr->next;
 
                /* Make next of curr as NULL  */
                curr->next = NULL;
 
                /* Move curr to end */
                new_end->next = curr;
 
                /* make curr as new end of list */
                new_end = curr;
 
                /* Update current pointer to next of the moved node */
                curr = prev->next;
            }
        }
    }
 
    /* We must have prev set before executing lines following this
       statement */
    else prev = curr;
 
    /* If there are more than 1 odd nodes and end of original list is
      odd then move this node to end to maintain same order of odd
      numbers in modified list */
    if (new_end!=end && (end->data)%2 != 0)
    {
        prev->next = end->next;
        end->next = NULL;
        new_end->next = end;
    }
    return;
}

10. Multiply 2 matrices.
A   Assume first matrix is A[i][k] and second matrix is B[k][j]. So result
    matrix will be R[i][j]. First we check if number of rows of B is equal to
    number of columns of A. If not, return as multiplication is not possible.
    Now, we have 3 loops to calculate the result matrix. Time complexity is
    O(n^3).

    int** multiply(int **A, int ar, int ac, int **B, int br, int bc) {
        if(br != ac) {
            return NULL;
        }

        int **R = (int**)malloc(sizepf(int*)*ar);
        for(int i=0; i<ar; i++) {
            R[i] = (int*)malloc(sizeof(int)*bc);
        }

        for(int i=0; i<ar; i++) {
            for(int j=0; j<bc; j++) {
                R[i][j] = 0;
                for(int k=0; k<ac; k++) {
                    R[i][j] += A[i][k]*B[k][j];
                }
            }
        }
        return R;
    }

11. If most of the elements in the matrices are 0, how to optimize the
    multiplication of these matrices? Also how to save the space?
A   This is the example of sparce matrix.

