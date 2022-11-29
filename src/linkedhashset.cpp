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

linkedhs::iterator linkedhs::begin() const { return iterator(head_); }

linkedhs::iterator linkedhs::end() const { return iterator(nullptr); }

// linkedhashset

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

linkedhs::linkedhs() : linkedhs(DEFAULT_VECTOR_CAPACITY_) {}

linkedhs::linkedhs(size_t capacity)
    : vect_(capacity),
      existElem_(capacity), head_(nullptr),
      tail_(nullptr), insertedElements_(0) {}

linkedhs::~linkedhs() { clearNodes(); }

void linkedhs::clearNodes() {
    while (head_ != nullptr) {
        node *tmp = head_;
        head_ = head_->next;
        delete tmp;
    }
}

void linkedhs::clear() {

    clearNodes();

    std::vector<node *>(DEFAULT_VECTOR_CAPACITY_).swap(vect_);
    std::vector<bool>(DEFAULT_VECTOR_CAPACITY_).swap(existElem_);

    head_ = nullptr;
    tail_ = nullptr;
    insertedElements_ = 0;
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

bool linkedhs::operator!=(const linkedhs &other) const {
    return !(*this == other);
}

linkedhs::linkedhs(const linkedhs &other) : linkedhs(DEFAULT_VECTOR_CAPACITY_) {
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

bool linkedhs::contains(const element &e) const {
    return find(e) != end();
}

void linkedhs::rehash() {
    linkedhs lhs(vect_.capacity() * 2);
    for (size_t i = 0; i < vect_.capacity(); i++) {
        if (existElem_[i] == false) {
            continue;
        }
        lhs.insert(vect_[i]->data);
    }
    this->swap(lhs);
}

void linkedhs::addToTheEndOfList(linkedhs::node *e) {
    if (insertedElements_ == 0) {
        head_ = e;
        tail_ = e;
    } else {
        tail_->next = e;
        e->prev = tail_;
        tail_ = tail_->next;
    }
}

void linkedhs::deleteNodeFromList(const linkedhs::node *e) {
    if (head_ == e) {
        head_ = e->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        } else {
            head_->prev = nullptr;
        }
    }

    else if (tail_ == e) {
        tail_ = e->prev;
        tail_->next = nullptr;
    }

    else {
        if (e->prev != nullptr) {
            e->prev->next = e->next;
        }

        if (e->next != nullptr) {
            e->next->prev = e->prev;
        }
    }
    delete e;
}

int linkedhs::findPos(const element &e) const {
    const long long hashElem = countHash(e);
    if (vect_[hashElem] == nullptr) {
        return -1;
    }

    int idx = hashElem;
    for (int i = 0; i < vect_.capacity(); i++) {
        if (vect_[idx] != nullptr) {
            if (vect_[idx]->data == e && existElem_[idx] == true) {
                return idx;
            }
        }
        idx = (idx + 1) % vect_.capacity();
    }
    return -1;
}

linkedhs::iterator linkedhs::find(const element &e) const {
    const int idx = findPos(e);
    return idx == -1 ? end() : iterator(vect_[idx]);
}

bool linkedhs::insert(const element &e) {
    if (contains(e)) {
        return false;
    }
    if (insertedElements_ >=
        vect_.capacity() * DEFAULT_LOAD_FACTOR_) {
        rehash();
    }

    const long long hashElem = countHash(e);
    int idx = hashElem;

    for (int i = 0; i < vect_.capacity(); i++) {
        if (existElem_[idx] == false) {

            node *toInsert = new node(e);
            vect_[idx] = toInsert;
            addToTheEndOfList(toInsert);

            existElem_[idx] = true;
            insertedElements_++;
            return true;
        }
        idx = (idx + 1) % vect_.capacity();
    }
    return false;
}

bool linkedhs::remove(const element &e) {

    int pos = findPos(e);
    if (pos == -1) {
        return false;
    }

    deleteNodeFromList(vect_.at(pos));
    vect_[pos] = nullptr;
    existElem_[pos] = false;
    insertedElements_--;

    for (int i = 0; i < vect_.capacity(); i++) {
        int nextPos = (pos + 1) % vect_.capacity();
        if (existElem_[nextPos] == false || nextPos == pos) {
            break;
        }

        int hashNextPos =
            vect_[nextPos]->data.hash() % vect_.capacity();

        if (hashNextPos <= pos) {
            vect_[pos] = vect_[nextPos];
            pos = nextPos;
        }
    }
    return true;
}
