#include "hash.h"

// LOOK FOR THE COMMENTS IN THE .H 
// TO UNDERSTAND WHAT EACH FUNCTION MUST DO

Hash::Hash(int tablesize, int (*hf) (std::string) ) {
 // CONSTRUTOR 
    this->_hash_func = hf;
    //this->_table = *(new std::vector<std::forward_list<std::string>>(tablesize));
    this->_table.resize(tablesize);
}

int Hash::add(std::string str, int &collisions) { 
    collisions = 0;
    if(this->contains(str, collisions)) return 0;
    this->_table[this->hash(str)].push_front(str);
    return 1;
}//add

int Hash::remove(std::string str, int &collisions) { 
    collisions = 0;
    for(std::string s : this->_table[this->hash(str)]){
        collisions++;
        if(s == str){
            this->_table[this->hash(str)].remove(s);
            return 1;
        }
    }
    return 0;
}//remove


int Hash::hash(std::string str) { 
    return this->_hash_func(str);
}//hash
    
int Hash::contains(std::string str, int &collisions) { 
    collisions = 0;
    for(std::string s : this->_table[this->hash(str)]){
        collisions++;
        if(s == str)
            return 1;
    }
    return 0;
}//contains


int Hash::worst_case() {
    int m = 0;
    for(std::forward_list<std::string> l : this->_table){
        int tam = 0;
        for(std::string s : l) tam++;
        m = std::max(m, tam);
    }
    return m;
}//worst_case

int Hash::size() {
    int m = 0;
    for(std::forward_list<std::string> l : this->_table){
        int tam = 0;
        for(std::string s : l) tam++;
        m += tam;
    }
    return m;    
}//size

