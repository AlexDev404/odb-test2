// person.hxx
// copyright : not copyrighted - public domain
#pragma once
#include <string>
#include <cstddef> // std::size_t
#include <odb/core.hxx>     // (1)

#pragma db object           // (2)
class person
{
public:
    person (const std::string& first,
           const std::string& last,
           unsigned short age) : first_(first), last_(last), age_(age){
    }

    const std::string& first() const;
    const std::string& last() const;

    unsigned short age () const;
    void age (unsigned short);

private:
    friend class odb::access; // (4)
    person () {}              // (3)

    #pragma db id auto        // (5)
    unsigned long id_;        // (5)


    std::string first_;
    std::string last_;
    unsigned short age_;
};

#pragma db view object(person)
struct person_stat
{
#pragma db column("count(" + person::id_ + ")")
    std::size_t count;

#pragma db column("min(" + person::age_ + ")")
    unsigned short min_age;

#pragma db column("max(" + person::age_ + ")")
    unsigned short max_age;
};
