#include "linkedhashset.hpp"

#include <initializer_list>
#include <iostream>
#include <math.h>

#define DEFAULT_LOAD_FACTOR 0.75
#define DEFAULT_VECTOR_CAPACITY 16

student::student(unsigned age, std::string name)
        : age_(age), name_(std::move(name)) {};

student::student()
        : age_(0), name_("null") {};

bool student::operator==(const student &other) const {
    return this->age_ == other.age_ && this->name_ == other.name_;
}

bool student::operator!=(const student &other) const {
    return !(*this == other);
}

long long student::hash() const {
    long long h = 0;
    int p = 31;
    for (char c: name_) {
        h += (c - 'a' + 1) * p;
        p *= 31;
    }
    h = p * h + age_;
    return (long long) abs(h);
}

linkedhs::linkedhs()
        : capacityVector(DEFAULT_VECTOR_CAPACITY),
          head_(nullptr), tail_(nullptr), lengthList_(0) {

    vect.resize(capacityVector);
    //std::cout <<"linkedhs ctor" << std::endl;
};

linkedhs::~linkedhs() {
    while (head_ != nullptr) {
        node *next = head_->next;
        delete head_;
        head_ = next;
    }
    //std::cout << "linkedhs dtor" <<std::endl;
};

size_t linkedhs::size() const {
    return (lengthList_);
}

bool linkedhs::empty() const {
    return (lengthList_ == 0);
}

//overloading =
//a.operator=(b) ~ a=b
linkedhs &linkedhs::operator=(const linkedhs &other) {
    this->capacityVector = other.capacityVector;
    this->head_ = other.head_;
    this->tail_ = other.tail_;
    this->lengthList_ = other.lengthList_;
    this->vect = other.vect;
    return *this;
}

bool linkedhs::containsHash(const long long hash) const {
    return (vect[hash].age_ != 0 && vect[hash].name_ != "null");
}

linkedhs::iterator::iterator(linkedhs::node *node)
        : ptrNode_(node) {};

void linkedhs::addToList(const element &e) {
    node *tmp = new node;
    tmp->data = e; //add elem to list
    tmp->next = nullptr;
    tmp->prev = nullptr;
    if (lengthList_ == 0) {
        head_ = tmp;
        tail_ = tmp;
    } else {
        node *current = head_;
        node *parent = current;
        while (current != nullptr) {
            parent = current;
            current = current->next;
        }
        parent->next = tmp;
        tmp->prev = tail_;
        tail_ = tmp; //add elem in the end of list
    }
}

bool linkedhs::remove(const element &e) {
    deleteNodeFromList(e);
    vect[e.hash() % capacityVector].name_ = "null";
    vect[e.hash() % capacityVector].age_ = 0;
    return false;
}

bool linkedhs::deleteNodeFromList(const element &e) {
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
}

bool linkedhs::insert(const element &e) {
    if (lengthList_ >= capacityVector * DEFAULT_LOAD_FACTOR) {
        capacityVector = lengthList_ * 2;
        vect.resize(capacityVector);
    }
    size_t hashElem = e.hash() % capacityVector;
    if (contains(e)) { //if we already have elem in list, don't add it to the list
        return false;
    }
    if (!containsHash(hashElem)) {
        if (hashElem > vect.capacity())
            vect.resize(hashElem + 1);
        vect[hashElem] = e;
        addToList(e); 
        lengthList_++;  
        return true;
    } 
    else{    
        hashElem++;
        while (containsHash(hashElem)) //open addressing collission
            hashElem++;
        vect.resize(hashElem + 1);
        vect[hashElem] = e;
        addToList(e);
        lengthList_++;
    }
    return true;
}

linkedhs::iterator linkedhs::find(const element &e) const {
    iterator beginList(head_);
    iterator endList(tail_);
    iterator it = beginList;
    if (lengthList_ == 0) {
        it.ptrNode_ = nullptr;
        return it;
    }
    while (it != endList) {
        if (it.ptrNode_->data == e) {
            return it; //return ptr to node, where student exist
        }
        it++;
    }
    //check the last elem
    if (it.ptrNode_->data == e) {
        return it;
    }
    it.ptrNode_ = nullptr;
    return it;// didn't find elem e
}

bool linkedhs::contains(const element &e) const {
    iterator tmp = find(e);
    return (tmp.ptrNode_ != nullptr);
}

void linkedhs::swap(linkedhs &other) {
    std::swap(this->vect, other.vect);
    std::swap(this->lengthList_, other.lengthList_);
    std::swap(this->capacityVector, other.capacityVector);
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
}

linkedhs::node::node()
        : prev(nullptr), next(nullptr) {};

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

linkedhs::iterator linkedhs::begin() {
    return iterator(head_);
}

linkedhs::iterator linkedhs::end() {
    return iterator(tail_);
}

void linkedhs::print() {
    if (lengthList_ != 0) {
        node *tmp = head_;
        while (tmp != nullptr) {
            std::cout << tmp->data.name_ << " " << tmp->data.age_ << std::endl;
            tmp = tmp->next;
        }
    }
}
