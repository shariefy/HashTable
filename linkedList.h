#include<iostream>
#include<memory>
#include<exception>


using namespace std;

class NoSuchElement: public exception{
    const char* what()const noexcept  override{
        return "NO SUCH ELEMENT !!";
    }
};

template<class T>
struct Node{
    T data ;
    unique_ptr<Node<T>> next ;

    Node() : data(T()) , next(nullptr){}
    Node(const T& data) : data(data) , next(nullptr){}
    ~Node() = default;
    
};

template <class T>
class LinkedList{
    unique_ptr<Node<T>> root ;
    int size ;

    public:
    LinkedList(): root(nullptr), size(0){}
    ~LinkedList() = default ;
    void append(const T& data);
    void printList() const;
    void removeNode(const T& data);
    bool findNode(const T& data) const ;
    bool isEmpty() const ;
    int length() const ;
    const T& lastNode() const ;
    void addFirst(const T& data);

    class Iterator ;

    Iterator begin() const { return Iterator(root.get()) ;}
    Iterator end() const { return Iterator(nullptr) ;}

    class Iterator{
        Node<T>* p_list ;

        public:

            Iterator(Node<T>* node):p_list(node){}

            T& operator*(){return p_list->data ;}

            Iterator& operator++(){
                p_list = p_list->next.get();
                return *this ;
            }

            bool operator==(Iterator& other){
                return p_list == other.p_list;
            }

             bool operator!=(Iterator& other){
                return !(p_list == other.p_list);
            }
    };
};



template<class T>
void LinkedList<T>::append(const T& data){
    if(root.get() == nullptr){
        root = make_unique<Node<T>>(data);
        size++;
        return;
    }
        
    
    unique_ptr<Node<T>> toAdd = make_unique<Node<T>>(data);
    Node<T>* temp = root.get();

    while (temp->next != nullptr)
    {
        temp = temp->next.get();
    }

    temp->next = move(toAdd);
    size++;
}

template<class T>
void LinkedList<T>::printList() const {
    Node<T>* temp = root.get();

    while (temp != nullptr) {
        cout << temp->data << " -> ";
        temp = temp->next.get();
    }

    cout << "nullptr" << endl;
}

template<class T>
bool LinkedList<T>::findNode(const T& data) const {
    Node<T>* temp = root.get();
    bool isFound = false;

    

    while (temp != nullptr && !isFound)
    {
        if(temp->data == data)
            isFound = true ;
        
        temp = temp->next.get();
    }

    return isFound ;
}

template<class T>
void LinkedList<T>::removeNode(const T& data){

    if((!findNode(data) )|| root == nullptr)
        throw NoSuchElement();
    Node<T>* temp = root.get();

    if(root.get()->data == data){
        root = move(root.get()->next);
        size--;
        return;
    }
        

    while (temp->next != nullptr)
    {
        if(temp->next.get()->data == data)
            {
                temp->next = move(temp->next.get()->next);
                size--;
                return ;
            }
        temp = temp->next.get();
    }
    
    
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    if(size == 0)
        return true;
    return false;
}

template <class T>
int LinkedList<T>::length() const{
    return size;
}

template<class T>
const T& LinkedList<T>::lastNode() const{

    Node<T>* temp = root.get();

    if(root == nullptr)
        throw NoSuchElement();

    while (temp->next.get() != nullptr)
    {
        temp = temp->next.get();
    }
    
    return temp->data ;
}

template<class T>
void LinkedList<T>::addFirst(const T& data){
    unique_ptr<Node<T>> newNode = make_unique<Node<T>>(data);

    if(root == nullptr)
        root = move(newNode);
    else{
        newNode->next = move(root);
        root = move(newNode);
    }
    size++;
}




