//find(), remove() DOESN'T WORK :(
#include "new_lhs.hpp"

//iterator

linkedhs::iterator::iterator(linkedhs::node *node)
    : ptrNode_(node) {}

element linkedhs::iterator::operator*() {
    return ptrNode_->data;
}

linkedhs::iterator linkedhs::iterator::operator++(int) {
    iterator tmp(ptrNode_);
    ptrNode_ = ptrNode_->next;
    return tmp;
}

linkedhs::iterator linkedhs::iterator::operator++() {
    if (ptrNode_->next != nullptr) {
        ptrNode_ = ptrNode_->next;
    }
    return *this;
}

linkedhs::iterator linkedhs::iterator::operator--(int) {
    iterator tmp(ptrNode_);
    ptrNode_ = ptrNode_->prev;
    return tmp;
}

linkedhs::iterator linkedhs::iterator::operator--() {
    if (ptrNode_->prev != nullptr) {
        ptrNode_ = ptrNode_->prev;
    }
    return *this;
}

bool linkedhs::iterator::operator==
        (const linkedhs::iterator &other) const {

    return (this->ptrNode_ == other.ptrNode_);
}

bool linkedhs::iterator::operator!=
        (const linkedhs::iterator &other) const {
    return !(*this == other);
}

linkedhs::iterator linkedhs::begin() const{
    return iterator(head_);
}

linkedhs::iterator linkedhs::end() const {  
    return iterator(tail_);
}

//linkedhashset

linkedhs::linkedhs()
    : capacityVector_(DEFAULT_VECTOR_CAPACITY_),
        head_(nullptr), tail_(nullptr), insertedElements_(0) {
    vect_.resize(capacityVector_); 
}

linkedhs::~linkedhs() {
    while (head_ != nullptr) {
        node *next = head_->next;
        delete head_;
        head_ = next;
    }

    for (size_t i = 0; i < capacityVector_; i++){
        if(vect_[i] != nullptr){
            delete vect_[i];
        }
    }
    delete [] vect_;
}

size_t linkedhs::size() const{
    return insertedElements_;
}

bool linkedhs::empty() const{
    return size() == 0;
}
void linkedhs::swap(linkedhs &other) {
    std::swap(this->vect_, other.vect_);
    std::swap(this->insertedElements_, other.insertedElements_);
    std::swap(this->capacityVector_, other.capacityVector_);
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
}

void linkedhs::print() {
    if (!empty()) {
        node *tmp = head_;
        while (tmp != nullptr) {
            std::cout << tmp->data.name_ << " " << tmp->data.age_ << std::endl;
            tmp = tmp->next;
        }
    }
}

void linkedhs::clear(){
    node *curr = head_;
    while (curr != nullptr){
        node *tmp = curr;
        curr = curr->next;
        delete tmp;
    }

    // CR: clear vect_ DONE
    for (size_t i = 0; i < capacityVector_; i++){
        if(vect_[i] != nullptr){
            delete vect_[i];
        }
    }
    delete [] vect_;

    head_ = nullptr;
    tail_ = nullptr;
    insertedElements_ = 0;
}

long long linkedhs::countHash(const element &e) const{
    return e.hash() % capacityVector_;
}

linkedhs::iterator linkedhs::find(const element &e) const {
    long long hash = countHash(e);    
    
    /* it's O(n) yeah?
    while(it != endList){  
        if(&(*it) == vect_[hash] && ((*it)) == e){
            return it;
        }
        it++;
    }    
    if(&(*it) == vect_[hash] && ((*it)) == e){ //check the last elem
        return it;
    }
    if(vect_[hash] == nullptr){ //if not exists
        return end();
    }    
    return iterator(it); //will iterator return end()?
    //return end(); //prev line is the same?
    */

    if(vect_[hash] == nullptr){
        return end();
    }
    auto iter = vect_.begin() + hash;
    for (iter; iter < vect_.end(); iter++){
        if( *iter == vect_[hash] && *iter == &e){
          // CR: return iterator(*iter);
            return iter; // can't return :(
        }
    }
    return  iter; // can't return :(
}

bool linkedhs::contains(const element &e) const {
    return find(e) != end();
}

// CR: use insert inside DONE       
linkedhs::linkedhs(const linkedhs &other)
    :   capacityVector_(DEFAULT_VECTOR_CAPACITY_),
        insertedElements_(0),
        head_(nullptr), tail_(nullptr){
    
    for (auto it = other.begin(); it != other.end(); it++){
        element e = *it;
        insert(e);
    }    
}

void linkedhs::resize(){
    capacityVector_ = capacityVector_ * 2;
    std::vector <element*> vectNew;
    for (int i = 0; i < capacityVector_ / 2; i++){
        if(vect_[i] != nullptr){
            long long newHashElem = vect_[i]->hash() % capacityVector_;
            vectNew[newHashElem] = vect_[i];
        }   
    }

    for(size_t i = 0; i < capacityVector_ / 2; i++){
        delete vect_[i];
    }

    //              ??
    // for (iterator it = begin(); it != end(); it++){
    //     element e = *it;
    //     insert(e);        
    // }
}

void linkedhs::addToTheEndOfList(element * e) {
    // CR: node(e, ...);
    node *tmp = new node();
    // CR: use ctor with params
    tmp->data = e; //add elem to list 
    tmp->next = nullptr;
    tmp->prev = nullptr;

    if (insertedElements_ == 0) {
        head_ = tmp;
        tail_ = tmp;
    }
    else{ 
        // CR: simplify
        tail_->next = tmp;
        node *lastElem = tail_; //store a pointer to the last elem in the list
        tail_ = tmp;
        tail_->prev = lastElem; //add elem to the end of the list
    }
}

bool linkedhs::insert(const element &e){
    if (contains(e)) { 
        return false;
    } 
    if (insertedElements_ >= capacityVector_ * DEFAULT_LOAD_FACTOR_) {
        resize();
    }
    size_t hashElem = countHash(e);  

    while(vect_[hashElem]){
      // CR: handle out of bounds
        hashElem++;
    }
    element * toInsert = new element(e);
    vect_[hashElem] = toInsert;
    // *vect_[hashElem] = e;
    addToTheEndOfList(toInsert);
    insertedElements_++;
    return true;
}

/*
//order of insertion doesn't matter 
linkedhs hs1;
hs1.insert(a1);
hs1.insert(a2);

linkedhs hs2;
hs2.insert(a2);
hs2.insert(a1);

hs2 == hs1 // returns true
----------

linkedhs hs1;
for (1000 elements) {
  hs1.insert(e);
}
for (999 elements) {
  hs1.remove(e);
}

linkedhs hs2;
hs2.insert(e);
*/
// CR: implement as O(n)
 
bool linkedhs::operator==(const linkedhs &other) const{
    if(insertedElements_ != other.insertedElements_){
        return false;
    }

    for (auto it = this->begin(); it != this->end(); it++){
        // CR: copy?
        element e = *it;
        if(!other.contains(e)){
            return false;
        }
    }

    // CR: do we need it?
    for (auto it = other.begin(); it != other.end(); it++){
        element e = *it;
        if(!this->contains(e)){
            return false;
        }
    }
    return true;
}

linkedhs &linkedhs::operator=(const linkedhs &other){
    // CR: *this != other
    capacityVector_ = other.capacityVector_;
    insertedElements_ = other.insertedElements_;

    if(vect_ == other.vect_){
        return *this;
    }

    clear(); 
    
    for (auto it  = other.begin(); it != other.end(); it++){
        element e = * it;
        insert(e);
    }    
    return *this;
}

// CR: struct entry:
// - element
// - node_ *

//how to remember a position in the list of the node
//which we wanna delete ?
//how to find a position(=cell) of node we wanna kill ?

bool linkedhs::remove(const element &e) {
    //old code. not right
    /*
    iterator current = find(e);
    if (current.ptrNode_->next == nullptr) {//last elem 
        node *tmp = current.ptrNode_->prev;
        tmp->next = nullptr;
        tail_ = tmp;
        delete current.ptrNode_;
        return true;
    }
    if (current.ptrNode_->prev == nullptr) {//first elem
        node *tmp = current.ptrNode_->next;
        tmp->prev = nullptr;
        head_ = tmp;
        delete current.ptrNode_;
        return true;
    }
    //between first and last elements of the list
    if (current.ptrNode_->next != nullptr && current.ptrNode_->prev != nullptr) {
        node *tmpNext = current.ptrNode_->next;
        node *tmpPrev = current.ptrNode_->prev;
        tmpNext->prev = tmpPrev;
        tmpPrev->next = tmpNext;
        delete current.ptrNode_;
        return true;
    }
    return false;
    */
   
    long long hash = countHash(e);
    if(vect_[hash] == nullptr){
        return false;
    }

    //delete vect_[hash];

    // for (iterator it = begin() + hash; it != end(); it++){
    //    // if()
    // }

    //smth like pseudocode
    // iterator beginList(head_);
    // iterator endList(tail_);
   
    /*
    for(iterator it = beginList; it != endList; it ++){
        
        if(it == e){            
            pos = ... ; //remember this pos;
        }
        // 3 cases: remove elem from: the begin/end of list, (begin, end)
    }
    */

    return true;
}
