#include<iostream>
#include"linkedList.h"
#include<vector>
#include<functional>
#include<exception>

#define GOOD_LOAD_FACTOR 0.75

class KEY_ALREADY_EXISTS : public exception{
    public:
    const char* what() const noexcept override{
        return "KEY_ALREADY_EXISTS";
    }
};

template <class T>
class HashTable{        //Chaning
    private:
        LinkedList<T>* table ;
        double loadFactor ;
        int num_of_keys ;
        int table_size;
        
        
    public:
        HashTable();
        HashTable(int initial_table_size);
        ~HashTable();
        void insert(const T& key);
        bool remove(const T& key);
        bool find(const T& key) const;
        void printHashTable() const;
        
        
    private:
        int find_next_prime(int prime);
        bool is_prime(int n);
        int hashFunction(const T& key);
        void calculateLoadFactor() ;
        void resize();
};

template<class T>
bool HashTable<T>::is_prime(int n){
    for(int i=2 ; i*i<=n ;i++)
        if(n%i == 0)
            return false ;
    return true ;
}

template<class T>
int HashTable<T>::find_next_prime(int prime){
    int next_prime = prime;

    while (1)
    {
        prime++;
        if(is_prime(prime)){
            next_prime = prime ;
            break;
        }
    }
    return next_prime ;
}
template <class T>
HashTable<T>::HashTable():table(new LinkedList<T>[11]) , table_size(11) , num_of_keys(0) {
    calculateLoadFactor();
}

template <class T>
HashTable<T>::HashTable(int initial_table_size): table(new LinkedList<T>[initial_table_size]), table_size(initial_table_size) , num_of_keys(0) {
    calculateLoadFactor();
}

template <class T>
HashTable<T>::~HashTable() {

    delete [] table ;
    
}

template <class T>
int HashTable<T>:: hashFunction(const T& key){
    hash<T> my_hash;
    return my_hash(key) % table_size ;
}

template<class T>
 void HashTable<T>::calculateLoadFactor() { 
    loadFactor = static_cast<double>(num_of_keys) / table_size; 
 }

template<class T>
void HashTable<T>::resize() {
    if (loadFactor > GOOD_LOAD_FACTOR){
        int oldSize = table_size;
        int newSize = find_next_prime(table_size * 2); 
        table_size = newSize; 

        LinkedList<T>* newTable = new LinkedList<T>[newSize];  

        for (int i = 0; i < oldSize; ++i) {
            for (const auto& key : table[i]) {
                int newIndex = hashFunction(key);
                newTable[newIndex].append(key);
            }
        }

        delete[] table;
        table = newTable;
         
    }
}
template <class T>
bool HashTable<T>::find(const T& key) const{
    
    for(int i=0 ; i<table_size ; i++)
        if(table[i].findNode(key))
            return true ;
    return false ;

}

template <class T>
void HashTable<T>::insert(const T& key){
    if(find(key))
        throw KEY_ALREADY_EXISTS();
    int index = hashFunction(key);
    table[index].addFirst(key);
    num_of_keys++;
    calculateLoadFactor();
    resize();
    
}

template <class T>
bool HashTable<T>::remove(const T& key){
    if(!find(key))
        return false ;

    int index = hashFunction(key);
    table[index].removeNode(key);
    num_of_keys-- ;
    return true ;
}

template<class T>
 void HashTable<T>:: printHashTable() const{
    for(int i=0 ; i<table_size ; i++){
            cout<<i<<" ";
            table[i].printList();
    }
 }
