#include "student.hpp"

#include <math.h>

student::student()
    : age_(0), name_("null") {}

student::student(unsigned age, std::string name)
    : age_(age), name_(name) {}

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
