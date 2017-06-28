

/*
* Assignment: Final Project
* Description: This project will assess static code
* Date: 12-6-2016
* Name of Programmer: Jeremy Brachle
* Student Number: 46659942
* Course Number: 2341-802
* Lab Section: N11
*/



#ifndef LINKED_LIST
#define LINKED_LIST

//---------------------------------------------LIST NODE-----------------------------------
template <class T>
class ListNode{
    template<class Y> friend class LinkedList; //enable access to private data
public:

//Add functionality here to provide access to the ListNode Object.

//default constructor
ListNode();

//constructor when given a type for the first argument
ListNode(T);

//to compare if head and tail are equal
bool operator==(ListNode<T>&);

private:

    //pointer to the next element
    ListNode<T>*next;
    //pointer to the previous element
    ListNode<T>*prev;
    //the actual data within a given node
    T data;
};

//--------------------------------------------LINKED LIST---------------------------------
template<class T>
//class LinkedList: public ListNode<T>{
class LinkedList{
    //template <class Y> friend class ListNode;
public:

    //default constructor
    LinkedList();
    //constructor given an object to instantiate at the first slot
    LinkedList(T);
    //Rule of 3: Copy Constrcutor
    LinkedList(const LinkedList<T>&);

    //add an element when given the index
    void add(T, int);
    //add an element to the front
    void addToFront(T);
    //add an element to the back
    void addToBack(T);
    //returns the value given a subscript
    T get(int);
    //returns the current size of the Linked List
    int size();
    //removes an item from a given index
    T remove(int);
    //for stack implementation
    T removeLast();
    //for queue implementation
    T removeFirst();
    //returns true if no elements, false if there is at least one element
    bool isEmpty() const;
    //returns true/false if an element is in the list
    bool isAnElement(T);
    //returns true/false if there is an element beyond the given one
    bool isNext(T);
    //returns the value of the next element if it exists
    T getNext(T);
    //return the index of the given element (-1 if it does not exist)
    int getIndex(T);

    //to see if two linked lists are equal
    bool operator==(LinkedList<T>);

    //return head pointer data
    T getFirst();
    //return tail pointer data
    T getLast();

    //Rule of 3: Destructor
    ~LinkedList();

    //return the data given a subscript
    T& operator[] (int);
    //Rule of 3: Assignment Operator
    LinkedList<T>& operator=(LinkedList<T>&);

private:

    //List Node Pointer for the first element
    ListNode<T>*head;
    //List Node Pointer for the last element
    ListNode<T>*tail;
    //the number of individual items in the Linked List
    int num_elements = 0;

};

//-------------------------------------------LINKED LIST IMPLEMENTATION--------------------------------------


//Write your implementation here
//Linked List

//default constructor
template<typename T>
LinkedList<T>::LinkedList()
{
    //make head null
    head = NULL;
    //make tail null
    tail = NULL;
    //number of elements is zero
    num_elements = 0;

}

//constructor given object
template<typename T>
LinkedList<T>::LinkedList(T obj)
{
    //create a new node at the head with this value
    head = new ListNode<T>(obj);
    //make the tail equal the head
    tail = head;
    //set the data of tail
    tail->data = obj;
    //set the pointers
    head->next = nullptr;
    head->prev = nullptr;
    tail->next = nullptr;
    tail->prev = nullptr;
    //increment the number of elements
    num_elements++;
}

//destructor
template<typename T>
LinkedList<T>::~LinkedList()
{
    //if the first element is not already null
    if (head != nullptr)
    {
        //make a temporary List Node Pointer value for deleting
        ListNode<T>* curr = head;
        //if the temp value is not null
        while (curr != nullptr)
        {
            //make a temporary ListNode Pointer value for traversing next
            ListNode<T>* temp = curr->next;
            //delete it
            delete curr;
            //increment
            curr = temp;
        }
        //set equal to null
        head = nullptr;
        tail = nullptr;

    }

}

//copy constructor
template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T> &rhs)
{
    //make sure rhs is not empty
    if (rhs.num_elements != 0)
    {
        //if rhs only has one element
        if (rhs.num_elements == 1)
        {
            //create a new node at the head with this value
            head = new ListNode<T>(rhs.head->data);
            //make the tail equal the head
            tail = head;
            tail->data = rhs.head->data;
            head->next = nullptr;
            head->prev = nullptr;
            tail->next = nullptr;
            tail->prev = nullptr;
            num_elements = rhs.num_elements;
        }
        //if rhs only has two elements
        else if (rhs.num_elements == 2)
        {
            //create new node for head
            head = new ListNode<T>(rhs.head->data);
            //create new node for tail
            tail = new ListNode<T>(rhs.tail->data);
            head->prev = nullptr;
            head->next = tail;
            head->next->prev = head;
            tail->next = nullptr;
            tail->prev = head;
            tail->prev->next = tail;
            //update size
            num_elements = rhs.num_elements;
        }
        //for all other sizes
        else if (rhs.num_elements > 2)
        {

            //create new node for head
            head = new ListNode<T>(rhs.head->data);
            head->prev = nullptr;
            //temporary node for traversing rhs
            ListNode<T>* temp = rhs.head->next;
            //temporary node for traversing THIS
            ListNode<T>* curr = head;
            //loop though and set equal the pointers
            while (temp->next != nullptr)
            {
                //make a new list node pointer
                curr->next = new ListNode<T>(temp->data);
                curr->next->prev = curr;
                curr = curr->next;

                temp = temp->next;
            }
            curr->next = new ListNode<T>(temp->data);
            curr->next->prev = curr;
            curr = curr->next;
            curr->next = nullptr;
            tail = curr;
            //update size
            num_elements = rhs.num_elements;
        }

    }
    else //if rhs is null
    {
        num_elements = 0;
        head = NULL;
        tail = NULL;
    }
}



//overloaded assignment operator
template<typename T>
LinkedList<T>& LinkedList<T>::operator= (LinkedList<T>& rhs)
{
    //make sure no self assignment
    if (&rhs != this)
    {
        //make sure rhs is not empty
        if (rhs.num_elements != 0)
        {

            //check to see if left is not null
            if (num_elements != 0)
            {
                //if the first element is not already null, then delete it
                if (head != nullptr)
                {
                    //make a temporary List Node Pointer value for deleting
                    ListNode<T>* curr = head;
                    //if the temp value is not null
                    while (curr != nullptr)
                    {
                        //make a temporary ListNode Pointer value for traversing next
                        ListNode<T>* temp = curr->next;
                        //delete it
                        delete curr;
                        //increment
                        curr = temp;
                    }
                    //set equal to null
                    head = nullptr;
                    tail = nullptr;
                }
            }
            //if rhs only has one element
            if (rhs.num_elements == 1)
            {
                //create a new node at the head with this value
                head = new ListNode<T>(rhs.head->data);
                tail = head;
                tail->data = rhs.head->data;
                head->next = nullptr;
                head->prev = nullptr;
                tail->next = nullptr;
                tail->prev = nullptr;
                //update size
                num_elements = rhs.num_elements;
            }
            //if rhs only has two elements
            else if (rhs.num_elements == 2)
            {
                //create new node for head
                head = new ListNode<T>(rhs.head->data);
                //create new node for tail
                tail = new ListNode<T>(rhs.tail->data);
                head->prev = nullptr;
                head->next = tail;
                head->next->prev = head;
                tail->next = nullptr;
                tail->prev = head;
                tail->prev->next = tail;
                //update size
                num_elements = rhs.num_elements;
            }
            //for all other sizes
            else if (rhs.num_elements > 2)
            {
                //create new node for head
                head = new ListNode<T>(rhs.head->data);
                head->prev = nullptr;
                //temporary node for traversing rhs
                ListNode<T>* temp = rhs.head->next;
                //temporary node for traversing THIS
                ListNode<T>* curr = head;
                //loop though and set equal the pointers
                while (temp->next != nullptr)
                {
                    //make a new list node
                    curr->next = new ListNode<T>(temp->data);
                    curr->next->prev = curr;
                    curr = curr->next;
                    temp = temp->next;
                }
                //tail node
                curr->next = new ListNode<T>(temp->data);
                curr->next->prev = curr;
                curr = curr->next;
                curr->next = nullptr;
                tail = curr;
                //update size
                num_elements = rhs.num_elements;
            }

        }
        else //if rhs is null
        {
            num_elements = 0;
            head = NULL;
            tail = NULL;
        }

    }
    else
    {
        return *this; //return the given value if self assignment
    }
}

//is empty
template<typename T>
bool LinkedList<T>::isEmpty() const
{
    //std::cout<<"Is Empty\n";
    if (num_elements == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//size of the linked list
template<typename T>
int LinkedList<T>::size()
{
    return num_elements;
}

//return true/false if there is an element beyond the given one
template<typename T>
bool LinkedList<T>::isNext(T val)
{
    //check to see if the given value is the last element
    if (this->isAnElement(val) && val == tail->data)
    {
        //return false if the value exists and if it is the last element
        return false;
    }
    //check to see if the value is not the last element
    else if (this->isAnElement(val) && (!(val == tail->data)))
    {
        return true;
    }
    //if the item is not even in the linked list
    else if (this->isAnElement(val) == false)
    {
        //return false
        return false;
    }

}


//return true/false if an element is in the list
template<typename T>
bool LinkedList<T>::isAnElement(T val)
{
    //make a temp ListNode pointer for traversing
    ListNode<T>* temp = head;
    //loop through the LinkedList
    while(temp->next != nullptr)
    {
        //check every element to see if equals the desired one
        if (temp->data == val)
        {
            return true;
        }
        //if not, increment
        temp = temp->next;
    }
    //check the last element
    if (temp->data == val)
    {
        return true;
    }
    //return false if element is not found
    else
        return false;
}


//return the value of the next element if it exists
template<typename T>
T LinkedList<T>::getNext(T val)
{
    //loop through and find the value and return the next element if there is one, otherwise return val
    //make a temp ListNode pointer for iterating
    ListNode<T>* temp = head;

    //loop while there is a next
    while (temp->next != nullptr)
    {
        //if the given value is the one the loop is at and there IS a next value
        if (temp->data == val)
        {
            //return the next value since it exists
            temp = temp->next;
            return temp->data;
        }
        temp = temp->next;
    }
    //if control reaches the end, that means there is not next value, so just return val
    return val;
}

//return the data given a subscript
template<typename T>
T& LinkedList<T>::operator [](int subScript)
{
    ListNode<T>* temp = head; //temp value for traversing the list

    if (head == nullptr) //if list is empty
    {
        //do nothing
    }
    else if (subScript == 0) //if they want the first element
    {
        return this->head->data;
    }
    else if (subScript == (this->size() - 1)) //if they want the last element
    {
        return this->tail->data;
    }
    else if (subScript > 0 && subScript < (this->size() - 1))//if the number falls between the beginning and the end
    {
        for (int i = 0; i < subScript; i ++) //loop through until the desired value is found
        {
            temp = temp->next;
        }
        return temp->data;
    }

}

//get function:
template<typename T>
T LinkedList<T>::get(int loc)
{
    //temp value for traversing
    ListNode<T>* temp = head;

    //if empty
    if (head == 0x0)
    {
        return NULL;
    }
    //if they want the first value
    else if (loc == 0)
    {
        return this->head->data;
    }
    //if they want the last value
    else if (loc == (this->size() - 1))
    {
        return this->tail->data;
    }
    //if the number is anywhere between the beginning and the end
    else if (loc > 0 && loc < (this->size() - 1))
    {
        for (int i = 0; i < loc; i ++)
        {
            temp = temp->next;
        }
        return temp->data;
    }
}

//return the data in the head pointer
template<typename T>
T LinkedList<T>::getFirst()
{
    return this->head->data;
}

//return the data in the tail pointer
template<typename T>
T LinkedList<T>::getLast()
{
    return this->tail->data;
}


//remove a particular element
template<typename T>
T LinkedList<T>::remove(int loc)
{
    //if the list is empty
    if (head == nullptr)
    {
        //do nothing
    }
    //if there is only one element
    else if (*head == *tail)
    {
        T temp = head->data;
        //only need to delete one
        delete head;
        //delete tail;
        head = nullptr;
        tail = nullptr;
        //decrement the number of elements
        num_elements--;
        //return the data
        return temp;
    }
    else if (loc == 0 && !(*head == *tail)) //if the first element is desired
    {
        //if there are only two values in the list
        if (this->size() == 2)
        {
            //make a variable for the data in head
            T sTemp = head->data;
            //delete the head
            delete head;
            //head = nullptr;
            head = tail;
            head->data = tail->data;
            tail->prev = nullptr;
            head->prev = nullptr;
            head->next = nullptr;
            //decrement the number of elements
            num_elements--;
            //return the data
            return sTemp;
        }
        else //if more than two
        {
            //make a variable for the next node
            ListNode<T>* temp = head->next;
            //make a variable for the data
            T sTemp = head->data;
            //delete the head node
            delete head;
            head = temp;
            head->prev = nullptr;
            head->next->prev = head;
            //decrement the number of elements
            num_elements--;
            //return the data
            return sTemp;
        }
    }
    //if the last value is wanted
    else if (loc == this->size() -1)
    {
        //if there are only two elements
        if (this->size() == 2)
        {
            //make a variable for the data
            T sTemp = tail->data;
            //delete the tail node
            delete tail;
            tail = nullptr;
            tail = head;
            tail->data = head->data;
            head->next = nullptr;
            tail->prev = nullptr;
            //decrement the number of elements
            num_elements--;
            //return the data
            return sTemp;
        }
        //if more than two
        else
        {
            //make a variable for th tail data
            T temp = tail->data;
            //make a variable for the new tail
            ListNode<T>* sTemp = tail->prev;
            sTemp->next = nullptr;
            delete tail;
            tail = sTemp;
            //tail = tail->prev;
            tail->next = nullptr;
            tail->prev->next = tail;
            //decrement the number of elements
            num_elements--;
            //return the data
            return temp;
        }
    }
    //if between the front and end
    else if (loc > 0 && loc < (this->size() - 1))
    {
        //make a variable for traversing
        ListNode<T>* curr = head;
        for (int i = 0; i<loc; i ++)
        {
            //update position
            curr = curr->next;
        }
        //make a variable for the new current variable
        ListNode<T>* temp = curr;
        T sTemp = curr->data;
        //delete temp;
        curr->next->prev = curr->prev;
        curr->prev->next = curr->next;
        delete temp;
        //decrement the number of elements
        num_elements--;
        //return the data
        return sTemp;
    }
}

//remove first
template<typename T>
T LinkedList<T>::removeFirst()
{
    //call the remove function but with the first element
    //redo for not depending on size
    return this->remove(0);
}

//remove last
template<typename T>
T LinkedList<T>::removeLast()
{
    //call the remove function but with the last element
    //redo for not depending on size
    return this->remove(this->size() - 1);
}


//insert at any location
template<typename T>
void LinkedList<T>::add(T val, int loc)
{
    //check to see if insertion at the front
    if (loc == 0)
    {
        this->addToFront(val);
    }
    //check to see if insertion at the back
    else if(loc == this->size())
    {
        this->addToBack(val);
    }
    //if the insertion is anywhere in between
    else if (loc > 0 && loc < this->size())
    {
        //make a variable for traversing
        ListNode<T>* curr = head;
        for (int i = 0; i<loc; i ++)
        {
            //increment position
            curr = curr->next;
        }
        //create a  new node
            ListNode<T>* temp = new ListNode<T>(val);
            temp->next = curr;
            temp->prev = curr->prev;
            curr->prev->next = temp;
            curr->prev = temp;
            //increment the number of elements
            num_elements++;
    }
}

//add an item to the back of the list
template<typename T>
void LinkedList<T>::addToBack(T item)
{
    //if the list is already empty
    if (head == nullptr)
    {
        //make a new node
        head = new ListNode<T>(item);
        tail = head;
        //increment the number of elements
        num_elements++;
    }
    //if there is only one element
    else if (*head == *tail)
    {
        //make a new node
        tail = new ListNode<T>(item);

        head->next = tail;
        tail->prev = head;

        //increment the number of elements
        num_elements++;
    }

    //add if more than one element
    else if (!(*head == *tail))
    {
        //for traversing the list from beginning
        ListNode<T>* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        //new node to be inserted
        ListNode<T>* n = new ListNode<T>(item);
        //increment the number of elements
        num_elements++;
        tail = n;
        tail->next = nullptr;
        tail->prev = current;
        current->next = tail;
    }
}


//add an item to the front of the list
template<typename T>
void LinkedList<T>::addToFront(T item)
{
    //if the list is already empty
    if (head == nullptr)
    {
        //create a new node
        head = new ListNode<T>(item);
        tail = head;
        //increment the number of elements
        num_elements++;
    }
    //if only on item
    else if (*head == *tail)
    {
        //create a new node
        head = new ListNode<T>(item);
        tail->prev = head;
        head->next = tail;
        //increment the number of elements
        num_elements++;
    }

    //add if more than one element
    else if (!(*head == *tail))
    {
        //value for traversing
        ListNode<T>* current = tail;
        while (current->prev != nullptr)
        {
            current = current->prev;
        }
        //new node to be inserted
        ListNode<T>* n = new ListNode<T>(item);
        //increment the number of elements
        num_elements++;
        head = n;
        head->prev = nullptr;
        head->next = current;
        current->prev = head;
    }
}

//boolean equality operator to see if two linked lists are equivalent
template<typename T>
bool LinkedList<T>::operator ==(LinkedList<T> rhs)
{
    //make sure the lists aren't empty
    if (this->head == nullptr && rhs.head == nullptr)
    {
        return true;
    }
    //if one of the lists are empty
    else if (this->head == nullptr || rhs.head == nullptr)
    {
        return false;
    }
    //if the sizes are not equal
    else if (this->size() != rhs.size())
    {
        return false;
    }
    //if the sizes are both 1
    else if (this->size() == 1)
    {
        if (this->head->data == rhs.head->data)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    //if the sizes are greater than 1
    else
    {
        //make node variables for traversing
        ListNode<T>* currentL = this->head;
        ListNode<T>* currentR = rhs.head;
        //while
        while (currentL->next != nullptr)
        {
            if (!(currentL->data == currentR->data))
            {
                return false;
            }
            else
            {
                currentL = currentL->next;
                currentR = currentR->next;
            }
        }
        //check the last node
        if (!(currentL->data == currentR->data))
        {
            return false;
        }
        else
        {
            return true;
        }
    }
}



//-------------------------------------------LIST NODE IMPLEMENTATION-----------------------------------
//List Node:

//default constructor
template<typename T>
ListNode<T>::ListNode()
{
    //make both null
    next = nullptr;
    prev = nullptr;
}

//constructor when given an object
template<typename T>
ListNode<T>::ListNode(T object)
{
    //data will equal the given value
    data = object;
    next = nullptr;
    prev = nullptr;
}

//boolean equality operator
template<typename T>
bool ListNode<T>::operator ==(ListNode<T>& rhs)
{
    //check to see if data, next, and prev are all equal
    if (data == rhs.data && next == rhs.next && prev == rhs.prev)
    {
        return true;
    }
    else
    {
        return false;
    }
}




#endif
