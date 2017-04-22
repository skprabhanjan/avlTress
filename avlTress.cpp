
// AVL Tress Generic implementaion
// By Prabhanjan SK and Prajwal MR

#include <iostream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <string>
using namespace std;

// predicate function
struct stringLen{
    bool operator()(int x, int y) { return x < y; }
    bool operator()(string x, string y) { 
        return x.length() < y.length(); }
}stringLenLess; 



// Node Structure for Tree
template<typename T>
class avl_node{
public:
     T data;
     avl_node<T> *left;
     avl_node<T> *right;
     avl_node<T> *operator++();
     avl_node<T> *operator++(int);
     avl_node<T> *operator--();
     avl_node<T> *operator--(int);
};  
 
// AVL tree ADT
template<typename T,typename pred_t>
class avlTree{
    public:
        avl_node<T> *root;
        int height(avl_node<T> *);
        int diff(avl_node<T> *);
        avl_node<T> *rr_rotation(avl_node<T> *);
        avl_node<T> *ll_rotation(avl_node<T> *);
        avl_node<T> *lr_rotation(avl_node<T> *);
        avl_node<T> *rl_rotation(avl_node<T> *);
        avl_node<T>* balance(avl_node<T> *);
        avl_node<T> *insert(avl_node<T> *,T value,pred_t op);
        avl_node<T>* deleteNode(avl_node<T> *,T);
        avl_node<T>* findLeftMost(avl_node<T> *);
        avl_node<T>* findRightMost(avl_node<T> *);
        avl_node<T>* inOrderSuccessor(avl_node<T> *,pred_t op);
        avl_node<T>* inOrderPredecessor(avl_node<T> *,pred_t op);
        void print(avl_node<T> *,int); // recursive function
        void display(); // iterative function, that finds next inroder succesor and prints(++)
        void reverseDisplay(); // iterative function, that finds next inroder predecessor and prints(--)
        avl_node<T>* search(T);
        // void inorder(avl_node<T> *);
        // void preorder(avl_node<T> *);
        // void postorder(avl_node<T> *);
        avlTree(){
            root = NULL;
        }
};

 
/*
 * Main Contains Menu
 */
avlTree<string,stringLen> avl;  // Generic

int main(){
    char choice;
    string item,value,itemToBeDeleted; // Generic
    while (1){
        cout<<"\n---------------------"<<endl;
        cout<<"AVL Tree Implementation"<<endl;
        cout<<"\n---------------------"<<endl;
        cout<<"1.Insert Element into the tree"<<endl;
        cout<<"2.Delete Element from the tree"<<endl;
        cout<<"3.Display Balanced AVL Tree"<<endl;
        cout<<"4.Search"<<endl;
        cout<<"5.Find Inorder Successor"<<endl;
        cout<<"6.Find Inorder Predecessor"<<endl;
        cout<<"7.Display Inorder"<<endl;
        cout<<"8.Display Reverse Inorder"<<endl;
        // cout<<"3.InOrder traversal"<<endl;
        // cout<<"3.InOrder traversal"<<endl;
        // cout<<"4.PreOrder traversal"<<endl;
        // cout<<"5.PostOrder traversal"<<endl;
        cout<< "Press q to exit"<<endl;
        cout<<"Enter your Choice: ";
        cin>>choice;
        switch(choice){
        case '1':
               cout<<"Enter value to be inserted: ";
               cin>>value;
               avl.root = avl.insert(avl.root,value,stringLenLess);
               break;
         case '2':
               cout<<"Enter value to be deleted: ";
               cin>>itemToBeDeleted;
               if(avl.search(itemToBeDeleted) == 0){
                    cout << "The item does not exist in the tree";
               }
               else{
                    avl.root = avl.deleteNode(avl.root,itemToBeDeleted);
               }
               break;
        case '3':
                if (avl.root == NULL){
                    cout<<"Tree is Empty"<<endl;
                    continue;
                }
                cout<<"Balanced AVL Tree:"<<endl;
                avl.print(avl.root,1);
                break;
        case '4':
                cout<<"Enter value to be searched: ";
                cin>>value;
                cout << avl.search(value) << endl;
                break;
        case '5':
                cout<<"Enter value of node that you need to find the inOrderSuccessor of: ";
                cin>>value;
                if(avl.inOrderSuccessor(avl.search(value),stringLenLess) == 0){
                    cout << "Last Node, No in order successor" << endl;
                }
                else{
                    cout << avl.inOrderSuccessor(avl.search(value),stringLenLess)->data << endl;
                }
                break;
        case '6':
                cout<<"Enter value of node that you need to find the inOrderPredecessor of: ";
                cin>>value;
                if(avl.inOrderPredecessor(avl.search(value),stringLenLess) == 0){
                    cout << "No inOrderPredecessor" << endl;
                }
                else{
                    cout << avl.inOrderPredecessor(avl.search(value),stringLenLess)->data << endl;
                }
                break;
         case '7':
                avl.display();   
                break;
        case '8':
                avl.reverseDisplay();   
                break;
        case 'q':
                exit(1);    
                break;
        default:
                cout<<"Wrong Choice"<<endl;
        }
    }
    return 0;
}


template<typename T>
 avl_node<T>* avl_node<T>::operator++(){ // pre
                *this  =  *avl.inOrderSuccessor(this,stringLenLess);
                return this;                
}

template<typename T>
avl_node<T>* avl_node<T>::operator++(int){ // post
                avl_node<T> *temp = this;
                ++(*this);
                return temp;     
}

template<typename T>
 avl_node<T>* avl_node<T>::operator--(){ // pre
                *this  =  *avl.inOrderPredecessor(this,stringLenLess);
                return this;                
}

template<typename T>
avl_node<T>* avl_node<T>::operator--(int){ // post
                avl_node<T> *temp = this;
                --(*this);
                return temp;      
}

 
// Height of tree
template<typename T, typename pred_t>
int avlTree<T,pred_t>::height(avl_node<T> *temp){
    int h = 0;
    if (temp != NULL){
        int l_height = height (temp->left);
        int r_height = height (temp->right);
        int max_height = max (l_height, r_height);
        h = max_height + 1;
    }
    return h;
}
 
// Height Difference to calculate balance factor
template<typename T,typename pred_t>
int avlTree<T,pred_t>::diff(avl_node<T> *temp){
    int l_height = height (temp->left);
    int r_height = height (temp->right);
    int b_factor= l_height - r_height;
    return b_factor;
}
 

//Right Right Rotation, on balance factor 
template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::rr_rotation(avl_node<T> *parent){
    avl_node<T> *temp;
    temp = parent->right;
    parent->right = temp->left;
    temp->left = parent;
    return temp;
}

//Left Left Rotation, on balance factor 
template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::ll_rotation(avl_node<T> *parent){
    avl_node<T> *temp;
    temp = parent->left;
    parent->left = temp->right;
    temp->right = parent;
    return temp;
}

//Left Right Rotation, on balance factor 
template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::lr_rotation(avl_node<T> *parent){
    avl_node<T> *temp;
    temp = parent->left;
    parent->left = rr_rotation (temp);
    return ll_rotation (parent);
}
 
//Right Left Rotation, on balance factor 
template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::rl_rotation(avl_node<T> *parent){
    avl_node<T> *temp;
    temp = parent->right;
    parent->right = ll_rotation (temp);
    return rr_rotation (parent);
}
 
// Checking for balance of the tree and performing rotation if balance is lost based on balance factor
template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::balance(avl_node<T> *temp){
    int bal_factor = diff (temp);
    if (bal_factor > 1){
        printf("\n\n");
        printf("Balance Lost\n");
        if (diff (temp->left) > 0){
            printf("Performing LL\n");
            temp = ll_rotation (temp);
        }
        else{
            printf("Performing LR\n");
            temp = lr_rotation (temp);
        }
    }
    else if (bal_factor < -1){
        printf("\n\n");
        printf("Balance Lost\n");
        if (diff (temp->right) > 0){
            printf("Performing RL\n");
            temp = rl_rotation (temp);
        }
        else{
            printf("Performing RR\n");
            temp = rr_rotation (temp);
        }
    }
    return temp;
}
 
// Insert an element into the Tree, check balance after insertion
template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::insert(avl_node<T> *root,T value,pred_t op){
    if (root == NULL){
        root = new avl_node<T>;
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        return root;
    }
    if (op(value,root->data)){
        root->left = insert(root->left, value,op);
        root = balance (root);
    }
    else{
        root->right = insert(root->right, value,op);
        root = balance (root);
    }
    return root;
}

// Find the left most node
template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::findLeftMost(avl_node<T> *node){
    avl_node<T> *current = node;
     while (current->left != NULL)
        current = current->left;
    return current;
}

//Find Right Most Node
template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::findRightMost(avl_node<T> *node){
    avl_node<T> *current = node;
     while (current->right != NULL)
        current = current->right;
    return current;
}


// Delete a node, check balance after deletion
template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::deleteNode(avl_node<T> *root, T key){
    if (root == NULL) return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);

    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    else{
            if (root->left == NULL) {
                avl_node<T> *temp = root->right;
                free(root);
                return temp;
            }
            else if (root->right == NULL){
                avl_node<T> *temp = root->left;
                free(root);
                return temp;
            }
            avl_node<T> *temp = findLeftMost(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    root = balance(root);
    return root;
}
 

// Display function , prints * for the root
template<typename T,typename pred_t>
void avlTree<T,pred_t>::print(avl_node<T> *r,int l){    
    int i;
    if(!r) return ;
    print(r->right,l+1);
    if(l==1){
        // print * for root
        cout << "*";
    }
    for(i=0;i<l;++i)
        cout << " ";
    cout << r->data << endl;
    print(r->left,l+1);
}

// Searches for an element passed
template<typename T,typename pred_t>
avl_node<T>* avlTree<T,pred_t>::search( T value){    
    avl_node<T> *temp = root;
    while(temp != NULL){
            if (temp->data == value)
                break;
            if (value > temp->data)
                temp = temp->right;
            else if (value < temp->data)
                temp = temp->left;
         }
    return temp;
}
template<typename T,typename pred_t>
void avlTree<T,pred_t>::display(){
    avl_node<T> *first = findLeftMost(root);
    avl_node<T> *tempFirst;
    tempFirst->data = first->data;
    avl_node<T> *last = findRightMost(root);
    while(first->data != last->data){
        cout << first->data << " ";
        (*first)++;
    }
     cout << first->data << " "; // Last element
     first->data = tempFirst->data; // Restore the value back
}

template<typename T,typename pred_t>
void avlTree<T,pred_t>::reverseDisplay(){
    avl_node<T> *first = findRightMost(root);
    avl_node<T> *tempFirst;
    tempFirst->data = first->data;
    avl_node<T> *last = findLeftMost(root);
    while(first->data != last->data){
        cout << first->data << " ";
        (*first)--;
    }
     cout << first->data << " "; // Last element
     first->data = tempFirst->data; // Restore the value back
}

// Display without using ++
// template<typename T,typename pred_t>
// void avlTree<T,pred_t>::display(){
 // avl_node<T> temp;
    // temp++;
    //cout << first->data << " ";
    // while(first!=NULL){
    //     first = inOrderSuccessor(first);
    //     if(first==0){}
    //     else{
    //         cout<< first->data << " ";
    //     }
    // }
//}

template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::inOrderPredecessor(avl_node<T> *n,pred_t op){
    avl_node<T> *temp = avl.root;
    if( n->left != NULL )
        return findRightMost(n->left);
 
    avl_node<T> *pre = NULL;
 
    while (temp != NULL){
        if (op(n->data,temp->data)){
            temp = temp->left;
        }
        else if(n->data!=temp->data && !op(n->data,temp->data)){
             pre = temp;
             temp = temp->right;
        }
        else
           break;
    }
    return pre;
}

template<typename T,typename pred_t>
avl_node<T> *avlTree<T,pred_t>::inOrderSuccessor(avl_node<T> *n,pred_t op){
    avl_node<T> *temp = root;
    if( n->right != NULL )
        return findLeftMost(n->right);
 
    avl_node<T> *succ = NULL;
 
    while (temp != NULL){
        if (op(n->data,temp->data)){
            succ = temp;
            temp = temp->left;
        }
        else if (n->data!=temp->data && !op(n->data,temp->data))
            temp = temp->right;
        else
           break;
    }
    return succ;
}

//Inorder Traversal of AVL Tree

// void avlTree::inorder(avl_node *tree){
//     if (tree == NULL)
//         return;
//     inorder (tree->left);
//     cout<<tree->data<<"  ";
//     inorder (tree->right);
// }

// Preorder Traversal of AVL Tree

// void avlTree::preorder(avl_node *tree){
//     if (tree == NULL)
//         return;
//     cout<<tree->data<<"  ";
//     preorder (tree->left);
//     preorder (tree->right);
// }
 
// Postorder Traversal of AVL Tree

// void avlTree::postorder(avl_node *tree){
//     if (tree == NULL)
//         return;
//     postorder ( tree ->left );
//     postorder ( tree ->right );
//     cout<<tree->data<<"  ";
// }