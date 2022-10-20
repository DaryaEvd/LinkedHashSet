#include <iostream>
#include <vector>

struct student {
    student(unsigned age, std::string name);
    student();
    bool operator==(const student & other) const;
    bool operator!=(const student & other) const;
    long long hash() const;
    unsigned age_;
    std::string name_;
};

typedef student element;

class linkedhs {
    typedef struct node{
        element data;
        node *prev;
        node *next;

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
        explicit iterator(node *node);

        iterator(const iterator& other) = default;

        element operator*();

        iterator operator++(int); //post increment
        iterator operator++();//pre increment

        iterator operator--(int); //post increment
        iterator operator--(); //pre increment

        bool operator==(const iterator & other) const;
        bool operator!=(const iterator & other) const;

    private:
        friend class linkedhs;
        node *ptrNode_;
    };

    iterator begin();
    iterator end();

    iterator find(const element & e) const;

    linkedhs();
    ~linkedhs();

    linkedhs(const linkedhs & other); //todo: add
    linkedhs & operator=(const linkedhs & other);

    bool insert(const element & e);
    bool remove(const element & e);

    bool deleteNodeFromList(const element &e);

    void addToList(const element & e);
    bool containsHash(const long long hash) const;

    void swap(linkedhs & other);

    size_t size() const;
    bool empty() const;

    bool contains(const element & e) const;

    bool operator==(const linkedhs & other) const;
    bool operator!=(const linkedhs & other) const;

    void clear();

    void print();
};
