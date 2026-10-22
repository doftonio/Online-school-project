#include "../Header files/studyGroup.h"
#include "../Header files/student.h"
#include <iostream>
#include <algorithm>

StudyGroup::StudyGroup(std::string_view groupNum, int year, int capacity)
    : number(groupNum), courseYear(year), maxCapacity(capacity) {}

StudyGroup& StudyGroup::operator+=(Student* student) {
    if (student && static_cast<int>(students.size()) < maxCapacity &&
        std::ranges::find(students, student) == students.end()) {
        students.push_back(student);
    }
    return *this;
}

StudyGroup& StudyGroup::operator-=(Student* student) {
    std::erase(students, student);
    return *this;
}

Student* StudyGroup::findStudent(int studentId) const {
    for (auto* s : students) {
        if (s && s->getId() == studentId) {
            return s;
        }
    }
    return nullptr;
}

void StudyGroup::printInfo() const {
    std::cout << "Group " << number << " (Year: " << courseYear
              << ", Capacity: " << students.size() << "/" << maxCapacity << ")\n";
    for (const auto* s : students) {
        if (s) {
            std::cout << "  - ";
            s->printInfo();
        }
    }
}
