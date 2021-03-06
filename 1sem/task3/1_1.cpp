#include <iostream>

using std::cout;
using std::cin;

//BST v0.1.2
template <typename T>
class BST{
public:
    BST();
    ~BST();

    void    insert(T val);
    void    clear();
    void    print();

    bool    deleteByKey(T key);
    bool    find(T key);

    T       findMin();
    T       findMax();

private:
    struct Node{
        Node *  left;
        Node *  right;
        T       val;
    };

    Node *  root_;

    void    clearRec(Node *node);
    void    printRec(Node * node, int depth);
    void    deleteNode(Node * & node);

    Node *  findNode(T key);
};

/****************************MAIN*********************************************/

int main(){
    BST <int> bst;
    int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        bst.insert(x);
    }
    bst.print();
}

/****************************BST**********************************************/

// Public:

template <typename T>
BST<T>::BST():
        root_(NULL)
{}



template <typename T>
BST<T>::~BST(){
    clear();
}



template <typename T>
void BST<T>::insert(T val){
    Node * tmp = new Node;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->val = val;

    if(root_ == NULL){
        root_ = tmp;
        return;
    }

    Node * node = root_;
    while(val < node->val && node->left != NULL
          || val > node->val && node->right != NULL){
        node = (val < node->val)?(node->left):(node->right);
    }
    if(val < node->val)
        node->left = tmp;
    else
        node->right = tmp;
}



template <typename T>
void BST<T>::clear(){
    clearRec(root_);
    root_ = NULL;
}



template <typename T>
void BST<T>::print(){
    printRec(root_, 0);
}



template <typename T>
bool BST<T>::deleteByKey(T key){
    Node * node = root_;
    Node * parent = NULL;
    while(key != node->val
          && (key < node->val && node->left != NULL
              || key > node->val && node->right != NULL)){
        parent = node;
        node = (key <= node->val)?(node->left):(node->right);
    }
    if(node->val != key)
        return false;
    if(node != root_)
        deleteNode((key <= parent->val)?(parent->left):(parent->right));
    else
        deleteNode(root_);
    return true;
}



template <typename T>
bool BST<T>::find(T key){
    return (findNode(key) != NULL);
}



template <typename T>
T BST<T>::findMax(){
    Node * node = root_;
    while(node->right != NULL)
        node = node->right;
    return node->val;
}



template <typename T>
T BST<T>::findMin(){
    Node * node = root_;
    while(node->left != NULL)
        node = node->left;
    return node->val;
};

// Private:

template <typename T>
void BST<T>::printRec(Node * node, int depth){
    if(node == NULL)
        return;
    printRec(node->left, depth + 1);
    cout << node->val << ' ';
    printRec(node->right, depth + 1);
}



template <typename T>
void BST<T>::clearRec(Node * node){
    if(node == NULL)
        return;
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}



template <typename T>
void BST<T>::deleteNode(Node * & node){
    if(node->right == NULL){
        Node * tmp = node->left;
        delete node;
        node = tmp;
    }
    else if(node->left == NULL){
        Node * tmp = node->right;
        delete node;
        node = tmp;
    }
    else{
        Node * minParent = node;
        Node * min = node->right;
        while(min->left != NULL){
            minParent = min;
            min = min->left;
        }
        if(min == node->right)
            minParent->right = min->right;
        else
            minParent->left = min->right;
        min->left = node->left;
        min->right = node->right;
        delete node;
        node = min;
    }
}



template <typename T>
typename BST<T>::Node * BST<T>::findNode(T key){
    Node * node = root_;
    while(node != NULL && node->val != key){
        node = (key <= node->val)?(node->left):(node->right);
    }
    return node;
}
