#include "studyGroup.h"
#include "student.h"
#include <iostream>
#include <algorithm>

StudyGroup::StudyGroup(std::string_view groupNum, int year, int capacity)
    : number(groupNum), courseYear(year), maxCapacity(capacity) {}

StudyGroup& StudyGroup::operator+=(Student* student) {
    if (student && static_cast<int>(students.size()) < maxCapacity) {
        if (std::find(students.begin(), students.end(), student) == students.end()) {
            students.push_back(student);
        }
    }
    return *this;
}

StudyGroup& StudyGroup::operator-=(Student* student) {
    std::erase(students, student);
    return *this;
}

void StudyGroup::printInfo() const {
    std::cout << "Группа " << number << " (Курс: " << courseYear
              << ", Вместимость: " << students.size() << "/" << maxCapacity << ")\n";
    for (const auto* s : students) {
        if (s) {
            std::cout << "  - ";
            s->printInfo();
        }
    }
}
