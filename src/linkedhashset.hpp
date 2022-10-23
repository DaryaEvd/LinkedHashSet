#include "student.hpp"

#include <vector>

typedef student element;

class linkedhs {
    typedef struct node{
        element data;
        node *prev;
        node *next;

        /*default constructor for struct node*/
        node();

    } node;

    std::vector <element> vect;
    size_t capacityVector;

    node *head_;
    node *tail_;
    size_t lengthList_;

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
    iterator begin();

     /*returns a pointer to the last element in the list*/
    iterator end();

    /*returns an iterator pointing to the node with e */
    iterator find(const element &e) const;

    /*default constructor for linkedhs*/
    linkedhs();

    /*destructor*/
    ~linkedhs();

    /*copy constructor for linkedhs*/
    linkedhs(const linkedhs &other);

    /*assignment operator for linkedhs */
    linkedhs &operator=(const linkedhs &other);
    
    /*  
        returns true if the list has an element with such hash
        returns false if the list hasn't an element with such hash
    */
    bool containsHash(const long long hash) const;

    /*  returns true if the element e exist in the list
        returns false if the element e doesn't exist in the list
    */
    bool contains(const element &e) const;

    /*adds element e to the list*/
    void addToList(const element &e);

    /*  inserts element e to the list 
        returns true if e was added to the list
        returns false if e already exists in the list
    */
    bool insert(const element &e);

    /*  removes element e from the list 
        returns true if e was deleted to the list
        returns false if e doesn't exist in the list
    */
    bool remove(const element &e);

    /*  deletes a node from the list
        returns true if the node was deleted
        returns false if the node wasn't deleted
    */
    bool deleteNodeFromList(const element&e);   

    /* swaps the linked hash sets*/
    void swap(linkedhs &other);
    
    /*  сomparison operator==
        returns true if objects are equal in the list
        returns false if objects aren't equal in the list
    */
    bool operator==(const linkedhs &other) const;

    /*  сomparison operator!=
        returns true if objects aren't equal in the list
        returns false if objects are equal in the list
    */ 
    bool operator!=(const linkedhs &other) const;
   
    /* returns the number of elements in the list */
    size_t size() const;
    
    /*  returns true if the list is empty
        returns false if the list isn't empty
    */
    bool empty() const;    
    
    /* removes all of the elements from the set*/
    void clear();

    /* prints the set*/
    void print();
};
