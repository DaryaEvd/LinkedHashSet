#ifndef LINKED_HASH_SET_
#define LINKED_HASH_SET_

#include "student.hpp"

#include <vector>

typedef student element;

class linkedhs {
    
private:
    struct node;

public:
    class iterator {
    public:
        /*constructor with parameter for iterator*/
        explicit iterator(node *node);

        /*assignment operator for iterator*/
        iterator(const iterator &other) = default;

        /*dereference operator for iterator*/
        element operator*();

        /*postfix increment operator for iterator*/
        iterator operator++(int);
        /*prefix increment operator for iterator*/
        iterator operator++();

        /*postfix decrement operator for iterator*/
        iterator operator--(int);
        /*prefic decrement operator for iterator*/
        iterator operator--();

        /*  сomparison operator==
            returns true if objects are equal in iterator
            returns false if objects aren't equal in iterator
        */
        bool operator==(const iterator &other) const;

        /*  сomparison operator!=
            returns true if objects aren't equal in iterator
            returns false if objects are equal in iterator
        */
        bool operator!=(const iterator &other) const;

    private:
        friend class linkedhs;
        node *ptrNode_;
    };

    /*returns a pointer to the first element in the list*/
    // CR: order of iteration
    iterator begin() const;

    /*returns a pointer to the last element in the list*/
    iterator end() const;

    /*  if node is found
        returns an iterator pointing to the node with e
        otherwise returns end()
    */
    iterator find(const element &e) const;

    linkedhs();

    // CR: private
    /*construstor with parametr size*/
    linkedhs(int size);

    ~linkedhs();

    // CR: independent copy
    linkedhs(const linkedhs &other);

    // CR: clear linkedhs & independent copy
    linkedhs &operator=(const linkedhs &other);

    /*
        finds a necessary poosition 
        otherwise returns -1
    */
    int FindPos(const element &e) const;

    bool contains(const element &e) const;

    /*adds element e to the end of the list*/
    // void addToTheEndOfList(const element &e);
    void addToTheEndOfList(node *e);

    /*  inserts element e to the linkedhs
        returns true if e was added to the linkedhs
        returns false if e already exists in the linkedhs
    */
    bool insert(const element &e);

    /*
        increments capacityin 2 times,
        recalculate hashes of elements and
        moves them to container with doubled capacity
    */
   // CR: private
    void rehash();

    /*  removes element e from the list
        returns true if e was deleted to the list
        returns false if e doesn't exist in the list
    */
    bool remove(const element &e);

    // CR: private
    /*  deletes a node from the list */
    void deleteNodeFromList( const node *e);

    void swap(linkedhs &other);

    /*  сomparison operator==
        returns true if objects are equal in the list
        returns false if objects aren't equal in the list
    */
   // CR
    bool operator==(const linkedhs &other) const;

    bool operator!=(const linkedhs &other) const;

    size_t size() const;

    bool empty() const;

    // CR: private
    /*clears nodes in the list*/
    void ClearNodes();

    void clear();

    /* prints linked hash set in order of addition*/
    void print();

private:
    std::vector<node *> vect_;
    std::vector<bool> existElem_;

    node *head_;
    node *tail_;
    size_t insertedElements_;

    constexpr static double DEFAULT_LOAD_FACTOR_ = 0.65;
    constexpr static size_t DEFAULT_VECTOR_CAPACITY_ = 16;

    /*returns hash of the element*/
    long long countHash(const element &e) const;

    struct node {
        element data;
        node *prev;
        node *next;

        /*default constructor for struct node*/
        node() : prev(nullptr), next(nullptr) {}

        /*constructor for struct node with paremeters*/
        node(element dataNew)
            : data(dataNew), prev(nullptr), next(nullptr){};
    };
};

#endif // LINKED_HASH_SET_
