#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <string_view>

class Person {
private:
    std::string firstName;
    std::string lastName;
    std::string middleName;

public:
    Person() = default;
    Person(std::string_view first, std::string_view last, std::string_view middle)
        : firstName(first), lastName(last), middleName(middle) {}
    virtual ~Person() = default;

    const std::string& getFirstName() const noexcept { return firstName; }
    const std::string& getLastName() const noexcept { return lastName; }
    const std::string& getMiddleName() const noexcept { return middleName; }

    std::string getFullName() const {
        return lastName + " " + firstName + " " + middleName;
    }

    virtual void printInfo() const = 0;
};

#endif // PERSON_H
