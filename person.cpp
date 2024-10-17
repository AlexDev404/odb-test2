#include "person.hpp"

const std::string& person::first() const {
    return this->first_;
}

const std::string& person::last() const {
    return this->last_;
}

unsigned short person::age() const {
    return this->age_;
}

void person::age(unsigned short age) {
    this->age_ = age;
}
