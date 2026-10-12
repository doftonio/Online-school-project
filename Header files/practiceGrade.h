#pragma once
#include "grade.h"
#include <string>
#include <string_view>
#include <iostream>

class PracticeGrade : public Grade {
private:
    int number{ 1 };
    std::string workType{};

public:
    PracticeGrade() = default;
    PracticeGrade(int val, const Date& d, int workNum, std::string_view type);

    [[nodiscard]] int getNumber() const;
    [[nodiscard]] std::string getWorkType() const;

    friend std::ostream& operator<<(std::ostream& os, const PracticeGrade& g) {
        os << "[" << g.workType << " ¹" << g.number << ": " << g.getValue() << " á. (" << g.getDate() << ")]";
        return os;
    }
};