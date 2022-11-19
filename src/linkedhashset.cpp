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
    return iterator(nullptr); 
}

// linkedhashset

linkedhs::linkedhs()
    : vect_(DEFAULT_VECTOR_CAPACITY_), existElem_(DEFAULT_VECTOR_CAPACITY_), head_(nullptr), tail_(nullptr), insertedElements_(0) {
}

linkedhs::~linkedhs() {
    // CR: clear
    while (head_ != nullptr) {
        node *next = head_->next;
        delete head_;
        head_ = next;
    }
}

void linkedhs::clear() {
    node *curr = head_;
    // CR: clear_nodes()
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
    std::swap(this->existElem_, other.existElem_);
    std::swap(this->head_, other.head_);
    std::swap(this->tail_, other.tail_);
    std::swap(this->insertedElements_, other.insertedElements_);
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
    // CR: doesn't start from the beginning
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
    // int idx = find_pos(e); return idx == -1 ? end() : iterator(vect_[idx]);
}

int find_pos(const element & e) {
  // return -1;
  // ...rest of the code...
  // return hashElem;
}

bool linkedhs::contains(const element &e) const {
    return find(e) != end();
}

void linkedhs::resize() {
    // linkedhs lhs(vect_.capacity() * 2);
    // for (size_t i = 0; i < vect_.capacity() / 2; i++) {
    //   if (!existElem_[i]) continue;
    //   lhs.insert(vect_[i]->data);
    // }
    // this->swap(lhs);

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

    vect_ = vectNew;
}

void linkedhs::addToTheEndOfList(const linkedhs::node &e) {
    node *tmp = new node(e);

    if (insertedElements_ == 0) {
        head_ = tmp;
        tail_ = tmp;
    } 
    else {
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

    // size_t idx = hashElem;
    // while (true) {
    //   node * cur = vect_[idx];
    //   if (cur != nullptr) {
        
    //   }
    //   idx = (hashElem + 1) % vect_.capacity();
    // }

    auto iter = vect_.begin() + hashElem;
    for (; iter != vect_.end(); iter++) {
        if (vect_[hashElem] == nullptr ||
            existElem_[hashElem] == false) {

            existElem_[hashElem] = true;

            node *toInsert = new node(e);
            vect_[hashElem] = toInsert;
            // CR: reuse toInsert
            addToTheEndOfList(*toInsert);
            insertedElements_++;
            return true;
        }
        hashElem = (hashElem + 1) % vect_.capacity();
    }
    vect_.resize(DEFAULT_VECTOR_CAPACITY_);
    return false;
}

// CR: delete using node*
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
    // CR: O(n)
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
    // CR: use find_pos
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
