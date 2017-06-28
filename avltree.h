
/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/


#ifndef AVLTREE
#define AVLTREE

//-----------------------------------------------AVL TREE NODE-------------------------------------
template <class T>
class AVLTreeNode{
    //enable access to private data
    template<class Y> friend class AVLTree;

    //public data
public:

    //constructor given one item
    AVLTreeNode(T);

    //constructor given the item, left, and right
    AVLTreeNode(T, AVLTreeNode<T>*, AVLTreeNode<T>*);

    //constructor when given the item, left, right, and height
    AVLTreeNode(T, AVLTreeNode<T>*, AVLTreeNode<T>*, int);

    //get data
    T& getData();

    //private data
private:

    //pointers for the left and right
    AVLTreeNode<T>* left;
    AVLTreeNode<T>* right;
    //templated variable for the data inside the node
    T data;
    //variable for height
    int height;

};







//-----------------------------------------------AVL TREE CLASS---------------------------------------
template <class T>
class AVLTree{

    //public data
public:
    //rule of three:
    //1) copy constuctor
    AVLTree(const AVLTree<T> &);

    //2) overloaded assignment operator
    AVLTree<T>& operator=(const AVLTree<T> &);

    //3) destructor
    ~AVLTree();

    //public function for deleting the tree
    void clearTree();

    //default constructor
    AVLTree();

    //constructor given one element
    AVLTree(T);

    //searching an AVL Tree
    //bool search(T);

    //check to see if the tree is empty
    bool isEmpty();

    //get the height
    int getHeight(AVLTreeNode<T>*);

    //check to see if a value is in the tree
    bool contains(const T&);

    //public function for inserting an item
    void insert(const T&);

    //function that will return the maximum of two integers (this will be used wiith the height)
    int max(int, int);


    //function for getting the data in a tree, assuming it exists
    const T& getElement(const T&);


    //private data
private:
    //Node for the root of the AVL Tree
    AVLTreeNode<T>* root;

    //private overloaded copy constructor function for copying values
    void copyValues(AVLTreeNode<T> &, AVLTreeNode<T> &);

    //prviate function for recursive deletion
    void clearTree(AVLTreeNode<T>*);

    //private overloaded function for contains
    bool contains(const T&, AVLTreeNode<T>*);

    //private overloaded function for getting the data in a tree, assuming the element exists
    const T& getElement(const T&, AVLTreeNode<T>*);

    //private overloaded function for inserting
    void insert(const T&, AVLTreeNode<T>* &);

    //private rotation functions:
    //case 1
    void rotateWithLeftChild(AVLTreeNode<T>* &);
    //case 4
    void rotateWithRightChild(AVLTreeNode<T>* &);
    //case 2
    void doubleWithLeftChild(AVLTreeNode<T>* &);
    //case 3
    void doubleWithRightChild(AVLTreeNode<T>* &);



};






//--------------------------------------------AVL TREE IMPLEMENTATION------------------------------------

//default constructor:
template<typename T>
AVLTree<T>::AVLTree()
{
    //create a new AVL Tree but make the root null
    //root = NULL;

    root = nullptr;
}


//copy constructor
template<typename T>
AVLTree<T>::AVLTree(const AVLTree<T> &rhs)
{
    //make root NULL
    //root = NULL;
    root = nullptr;

    //call the private recursive copy constructor function:
    copyValues(*rhs.root, *root);

}

//overloaded assignment operator
template<typename T>
AVLTree<T>& AVLTree<T>::operator =(const AVLTree<T>& rhs)
{
    //make sure the left side is destructed if there is something there already
    //if (this->root != NULL)
    if (this->root != nullptr)
    {
        this->clearTree();
    }

    //make the root NULL
    //root = NULL;
    root = nullptr;

    //now copy the values
    copyValues(*rhs.root, *root);

}


//private recursive function that will copy the values into a new root
template<typename T>
void AVLTree<T>::copyValues(AVLTreeNode<T> &rhs, AVLTreeNode<T> &lhs)
{
    //make sure rhs is not NULL
    //if (&rhs != NULL)
    if (&rhs != nullptr)
    {
        //recursively copy left subtree
        copyValues(**&rhs.left, *&lhs);
        //recursively copy the right subtree
        copyValues(**&rhs.right, *&lhs);
        //insert(rhs.data, *&lhs);
        this->insert(rhs.data);
    }
}


//constructor given one element
template<typename T>
AVLTree<T>::AVLTree(T first)
{
    //set the first element by creating a new node
    //the left and right pointers will be made null inside of this function call
    root = new AVLTreeNode<T>(first);

}

//destructor
template<typename T>
AVLTree<T>::~AVLTree()
{
    //call the public deletion function
    clearTree();
}

//public function that will call overloaded private function for deletion
template<typename T>
void AVLTree<T>::clearTree()
{
    //call private recursive delete function
    clearTree(root);
}

//recursive function for deletion
template<typename T>
void AVLTree<T>::clearTree(AVLTreeNode<T>* node)
{
    //make sure the node is not null
    //if (node != NULL)
    if (node != nullptr)
    {
        //send the left node through recursively
        clearTree(node->left);
        //send the right node through recursively
        clearTree(node->right);
        //now delete the node
        delete node;
    }
}

//check to see if the tree is empty
template<typename T>
bool AVLTree<T>::isEmpty()
{
    //return true or false depending on if the root is null
    //return root == NULL;
    return root == nullptr;
}

//get the height
template<typename T>
int AVLTree<T>::getHeight(AVLTreeNode<T>* node)
{
    //check to see if the node is NULL
    //if (node == NULL)
    if (node == nullptr)
    {
        //return -1 if the node is NULL
        return -1;
    }
    //otherwise
    else
    {
        //return the height for all other cases
        return node->height;
    }
}

//get data in tree assuming it exists
template<typename T>
const T& AVLTree<T>::getElement(const T &getVal)
{
    return getElement(getVal, root);
}

//private overloaded function for getting the data in the tree
template<typename T>
const T& AVLTree<T>::getElement(const T &val, AVLTreeNode<T>* node)
{
    //check to see if the node is nullptr
    if (node == nullptr)
    {
        //end the function and return an empty T item
        T elem;
        return elem;
    }
    //check to see if the value is less than the given node
    else if (val < node->data)
    {
        //go down the left sub-tree
        return getElement(val, node->left);
    }
    //check to see if the value is greater than the given node
    else if (val > node->data)
    {
        //go down the right subtree
        return getElement(val, node->right);
    }
    //else statement where it return true because the element was found
    else if (val == node->data)
    {
        //T elementVal = val;

        return node->data;
    }
}


//public contains function
template<typename T>
bool AVLTree<T>::contains(const T &find)
{
    //call the overloaded private contains function and look for the value
    return contains(find, root);
}

//private overloaded contains function
template<typename T>
bool AVLTree<T>::contains(const T &value, AVLTreeNode<T>* node)
{
    //check to see if the node is NULL
    //if(node == NULL)
    if (node == nullptr)
    {
        //end the function and return false
        return false;
    }
    //check to see if the value is less than the given node
    else if (value < node->data)
    {
        //go down the left sub-tree
        return contains(value, node->left);
    }
    //check to see if the value is greater than the given node
    else if (value > node->data)
    {
        //go down the right subtree
        return contains(value, node->right);
    }
    //else statement where it return true because the element was found
    else if (value == node->data)
    {
        return true;
    }

}

//function that finds the max of two integers
template<typename T>
int AVLTree<T>::max(int left, int right)
{
    //use simple ternary conditional:
    return left > right ? left : right;
}


//public insert function
template<typename T>
void AVLTree<T>::insert(const T& val)
{
    //call the private function
    insert(val, root);
}


//private insertion function
template<typename T>
void AVLTree<T>::insert(const T& value, AVLTreeNode<T>* &node)
{
    //check to see if the node is null
    //if (node == NULL)
    if (node == nullptr)
    {
        node = new AVLTreeNode<T>(value, nullptr, nullptr);
    }
    //check to see if it is less than root
    else if (value < node->data)
    {
        //call insert recursively going down the left substree
        insert(value, node->left);

        //check to see if the balance factor is greater than 2
        //if it is, we need to determine the type of rotation
        if (getHeight(node->left) - getHeight(node->right) == 2)
        {
            //check for the type of rotation
            if (value < node->left->data)
            {
                //case 1 rotation
                rotateWithLeftChild(node);
            }
            else
            {
                //case 2 rotation
                doubleWithLeftChild(node);
            }
        }
    }
    //check to see if the value is greater than the root
    else if (value > node->data)
    {
        //call insert recursively going down the right substree
        insert(value, node->right);

        //check to see if the balance factor is greater than 2
        //if it is, we need to determine the type of rotation
        if (getHeight(node->right) - getHeight(node->left) == 2)
        {
            //check for the type of rotation
            if (value > node->right->data)
            {
                //case 4 rotation
                rotateWithRightChild(node);
            }
            else
            {
                //case 3 rotation
                doubleWithRightChild(node);
            }
        }
    }
    //ignore duplicate values
    else
    {
        //do nothing
    }

    //update the new heights
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
}

//case 1 rotation
template<typename T>
void AVLTree<T>::rotateWithLeftChild(AVLTreeNode<T>* &k2)
{
    //make a variable for k1 which will never be null
    AVLTreeNode<T>* k1 = k2->left;
    //perform rotation:
    k2->left = k1->right;
    k1->right = k2;
    //fix heights:
    k2->height = max(getHeight(k2->left), getHeight(k2->right)) + 1;
    k1->height = max(getHeight(k1->left), k2->height) + 1;
    //fix pointers
    k2 = k1;
}

//case 4 rotation
template<typename T>
void AVLTree<T>::rotateWithRightChild(AVLTreeNode<T>* &k1)
{
    //make a variable for k2 which will never be null
    AVLTreeNode<T>* k2 = k1->right;
    //perform rotation:
    k1->right = k2->left;
    k2->left = k1;
    //fix heights:
    k1->height = max(getHeight(k1->left), getHeight(k1->right)) + 1;
    k2->height = max(getHeight(k2->right), k1->height) + 1;
    //fix pointers
    k1 = k2;
}

//case 2 rotation
template<typename T>
void AVLTree<T>::doubleWithLeftChild(AVLTreeNode<T>* &k3)
{
    //since case 2 is just a case 4 followed by a case 1, we just need to call those functions
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

//case 3 rotation
template<typename T>
void AVLTree<T>::doubleWithRightChild(AVLTreeNode<T>* &k1)
{
    //since case 3 is just a case 1 followed by a case 4, we just need to call those functions
    rotateWithLeftChild(k1->right);
    rotateWithRightChild(k1);
}







//---------------------------------------------AVL TREE NODE IMPLEMENTATION--------------------------------

//constructor given one element
template<typename T>
AVLTreeNode<T>::AVLTreeNode(T item)
{
    //set the first item
    data = item;

    //make the pointers null
    left = nullptr;
    right = nullptr;

    //make the height zero
    height = 0;
}

//constructor given one item, left and right
template<typename T>
AVLTreeNode<T>::AVLTreeNode(T item, AVLTreeNode<T>* leftChild, AVLTreeNode<T>* rightChild)
{
    //set the item
    data = item;

    //set the left and right pointers
    left = leftChild;
    right = rightChild;

    //set the height to be zero
    height = 0;
}

//constructor when given one item, left, right, and the height
template<typename T>
AVLTreeNode<T>::AVLTreeNode(T item, AVLTreeNode<T>* leftChild, AVLTreeNode<T>* rightChild, int givenHeight)
{
    //set the item
    data = item;

    //set the left and right pointers
    left = leftChild;
    right = rightChild;

    //set the height
    height = givenHeight;
}

//get the data in the pointer
template<typename T>
T& AVLTreeNode<T>::getData()
{
    return data;
}



#endif // AVLTREE

