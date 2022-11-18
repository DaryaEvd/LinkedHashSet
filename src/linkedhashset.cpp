#include "linkedhashset.hpp"

// iterator

linkedhs::iterator::iterator(linkedhs::node *node) : ptrNode_(node) {}

element linkedhs::iterator::operator*() { return ptrNode_->data; }

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

bool linkedhs::iterator::operator==(
    const linkedhs::iterator &other) const {
    return (this->ptrNode_ == other.ptrNode_);
}

bool linkedhs::iterator::operator!=(
    const linkedhs::iterator &other) const {
    return !(*this == other);
}

linkedhs::iterator linkedhs::begin() const { 
    return iterator(head_); 
}

linkedhs::iterator linkedhs::end() const { 
    return iterator(0); 
}

// linkedhashset

linkedhs::linkedhs()
    : head_(nullptr), tail_(nullptr), insertedElements_(0) {

    vect_.resize(DEFAULT_VECTOR_CAPACITY_);

    existElem_.resize(DEFAULT_VECTOR_CAPACITY_);
}

linkedhs::~linkedhs() {
    while (head_ != nullptr) {
        node *next = head_->next;
        delete head_;
        head_ = next;
    }
}

void linkedhs::clear() {
    node *curr = head_;
    while (curr != nullptr) {
        node *tmp = curr;
        curr = curr->next;
        delete tmp;
    }

    head_ = nullptr;
    tail_ = nullptr;
    insertedElements_ = 0;
    vect_.resize(DEFAULT_VECTOR_CAPACITY_);

    existElem_.resize(DEFAULT_VECTOR_CAPACITY_);
}

size_t linkedhs::size() const { return insertedElements_; }

bool linkedhs::empty() const { return size() == 0; }

void linkedhs::swap(linkedhs &other) {
    std::swap(this->vect_, other.vect_);
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
    std::swap(this->insertedElements_, other.insertedElements_);

    // std::vector::swap(*this(other));
    // other.swap(*this);
   
    // vect_.resize(DEFAULT_VECTOR_CAPACITY_);
    // other.vect_.resize(DEFAULT_VECTOR_CAPACITY_);
    // std::swap(this->vect_.resize(DEFAULT_VECTOR_CAPACITY_),
    //            other.vect_.resize(DEFAULT_VECTOR_CAPACITY_));
    // size_t cap = this->vect_.capacity();
    // size_t otherCap = other.vect_.capacity();
    // // std::swap(this->vect_.capacity(), other.vect_.capacity());
    // std::vector::swap(this->capa)
}

void linkedhs::print() {
    if (!empty()) {
        node *tmp = head_;
        while (tmp != nullptr) {
            std::cout << tmp->data.name_ << " " << tmp->data.age_
                      << std::endl;
            tmp = tmp->next;
        }
    }
}

bool linkedhs::operator!=(const linkedhs &other) const {
    return !(*this == other);
}

linkedhs::linkedhs(const linkedhs &other)
    : head_(nullptr), tail_(nullptr), insertedElements_(0) {

    vect_.resize(DEFAULT_VECTOR_CAPACITY_);

    existElem_.resize(DEFAULT_VECTOR_CAPACITY_);

    for (auto it = other.begin(); it != other.end(); it++) {
        insert(*it);
    }
}

linkedhs &linkedhs::operator=(const linkedhs &other) {
    if (*this == other) {
        return *this;
    }

    clear();

    for (auto it = other.begin(); it != other.end(); it++) {
        insert(*it);
    }
    return *this;
}

bool linkedhs::operator==(const linkedhs &other) const {
    if (insertedElements_ != other.insertedElements_) {
        return false;
    }

    for (auto it = this->begin(); it != this->end(); it++) {
        if (!other.contains(*it)) {
            return false;
        }
    }

    return true;
}

long long linkedhs::countHash(const element &e) const {
    return e.hash() % vect_.capacity();
}

linkedhs::iterator linkedhs::find(const element &e) const {
    long long hashElem = countHash(e);

    if (vect_[hashElem] == nullptr) {
        return end();
    }

    for (auto iter = vect_.begin() + hashElem; iter < vect_.end();
                                                iter++) {
        if (vect_[hashElem] != nullptr) {

            if (*iter == vect_[hashElem] &&
                vect_[hashElem]->data == e &&
                existElem_[hashElem] == true) {
                return iterator(*iter);
            }

            hashElem = (hashElem + 1) % vect_.capacity();
        }
    }

    return end();
}

bool linkedhs::contains(const element &e) const {
    return find(e) != end();
}

void linkedhs::resize() {
    std::vector<node *> vectNew;
    vectNew.resize(vect_.capacity() * 2);

    existElem_.resize(vectNew.capacity()); 

    for (size_t i = 0; i < vect_.capacity() / 2; i++) {
        if (vect_[i] != nullptr) {
            long long newHashElem =
                vect_[i]->data.hash() % vect_.capacity();
            vectNew[newHashElem] = vect_[i];
        }
    }

    vect_.resize(DEFAULT_VECTOR_CAPACITY_);
    vect_ = vectNew;
}

void linkedhs::addToTheEndOfList(const linkedhs::node &e) {
    node *tmp = new node(e);

    if (insertedElements_ == 0) {
        head_ = tmp;
        tail_ = tmp;
    } else {
        // CR: simplify
        // tail_->next = tmp;
        // node *lastElem = tail_; 
        //     // store a pointer to the last elem in the list
        // tail_ = tmp;
        // tail_->prev = lastElem; // add elem to the end of the list

        tail_->next = tmp;
        tmp->prev = tail_;
        tail_ = tail_->next;
    }
}

bool linkedhs::insert(const element &e) {
    if (contains(e)) {
        return false;
    }
    if (insertedElements_ >=
        vect_.capacity() * DEFAULT_LOAD_FACTOR_) {
        resize();
    }

    long long hashElem = countHash(e);

    for (auto iter = vect_.begin() + hashElem; iter != vect_.end();
                                                        iter++) {
        if (vect_[hashElem] == nullptr ||
            existElem_[hashElem] == false) {

            existElem_[hashElem] = true;

            node *toInsert = new node(e);
            vect_[hashElem] = toInsert;
            addToTheEndOfList(*toInsert);
            insertedElements_++;
            return true;
        }
        hashElem = (hashElem + 1) % vect_.capacity();
    }
    vect_.resize(DEFAULT_VECTOR_CAPACITY_);
    return false;
}

void linkedhs::deleteNodeFromList(const element &e) {
    if (head_->data == e) {
        head_ = head_->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        } else {
            head_->prev = nullptr;
        }
        return;
    }

    else if (tail_->data == e) {
        tail_ = tail_->prev;
        tail_->next = nullptr;
        return;
    }

    node *tmp = head_;
    node *beforeTmp = head_;

    while (tmp->next != nullptr && tmp->data != e) {
        beforeTmp = tmp;
        tmp = tmp->next;
    }
    if (tmp->data == e) {
        beforeTmp->next = tmp->next;
        delete tmp;
    }
}

bool linkedhs::remove(const element &e) {
    long long hashElem = countHash(e);
    if (vect_[hashElem] == nullptr) {
        return false;
    }

    for (auto iter = vect_.begin() + hashElem; iter != vect_.end();
                                                        iter++) {
        if (vect_[hashElem] != nullptr) {
            if (vect_[hashElem]->data == e &&
                existElem_[hashElem] == true) {
                deleteNodeFromList(e);
                existElem_[hashElem] = false;

                insertedElements_--;
                return true;
            }
        }
        hashElem = (hashElem + 1) % vect_.capacity();
    }

    return false;
}
