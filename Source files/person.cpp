#include "../Header files/person.h"

Person::Person(std::string_view first, std::string_view last, std::string_view middle)
    : firstName(first), lastName(last), middleName(middle) {
}

std::string Person::getFirstName() const { return firstName; }
std::string Person::getLastName() const { return lastName; }
std::string Person::getMiddleName() const { return middleName; }

std::string Person::getFullName() const {
    if (middleName.empty()) return lastName + " " + firstName;
    return lastName + " " + firstName + " " + middleName;
}

void Person::setFirstName(std::string_view first) { firstName = first; }
void Person::setLastName(std::string_view last) { lastName = last; }
void Person::setMiddleName(std::string_view middle) { middleName = middle; }

void Person::printInfo() const {
    std::cout << getFullName();
}