#include <iostream>

struct student {
    /*default constructor for struct student*/
    student();

    /*constructor with parameters for struct student*/
    student(unsigned age, std::string name);

    /*  сomparison operator==
        returns true if students are equal
        returns false if students aren't equal
    */
    bool operator==(const student &other) const;

    /*  сomparison operator!=
        returns true if students aren't equal
        returns false if students are equal
    */
    bool operator!=(const student &other) const;

    /*  retutns a value of hash*/
    long long hash() const;

    unsigned age_;
    std::string name_;
};
