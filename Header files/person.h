#pragma once
#include <string>
#include <string_view>
#include <iostream>

class Person {
private:
    std::string firstName{};
    std::string lastName{};
    std::string middleName{};

public:
    Person() = default;
    Person(std::string_view first, std::string_view last, std::string_view middle = "");
    virtual ~Person() = default;

    [[nodiscard]] std::string getFirstName() const;
    [[nodiscard]] std::string getLastName() const;
    [[nodiscard]] std::string getMiddleName() const;

    [[nodiscard]] virtual std::string getFullName() const;

    void setFirstName(std::string_view first);
    void setLastName(std::string_view last);
    void setMiddleName(std::string_view middle);

    virtual void printInfo() const;
};