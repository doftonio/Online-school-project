#pragma once
#include "grade.h"
#include <iostream>

class LabGrade : public Grade {
private:
    int number{ 1 };

public:
    LabGrade() = default;
    LabGrade(int val, const Date& d, int labNum);

    int getNumber() const;

    friend std::ostream& operator<<(std::ostream& os, const LabGrade& g) {
        os << "[Ырс. Й" << g.number << ": " << g.getValue() << " с. (" << g.getDate() << ")]";
        return os;
    }
};