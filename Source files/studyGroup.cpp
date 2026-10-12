#include "../Header files/studyGroup.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

StudyGroup::StudyGroup(std::string_view groupNum, int year, int capacity)
    : number(groupNum), courseYear(year), maxCapacity(capacity) {
    if (capacity <= 0) {
        throw std::invalid_argument("Вместимость группы должна быть положительной.");
    }
}

std::string StudyGroup::getNumber() const { return number; }
int StudyGroup::getCourseYear() const { return courseYear; }
int StudyGroup::getMaxCapacity() const { return maxCapacity; }
const std::vector<Student*>& StudyGroup::getStudents() const { return students; }

StudyGroup& StudyGroup::operator+=(Student* student) {
    if (!student) {
        throw std::invalid_argument("Попытка привязать к группе nullptr.");
    }
    if (static_cast<int>(students.size()) >= maxCapacity) {
        throw std::overflow_error("Группа " + number + " заполнена!");
    }
    for (const auto* s : students) {
        if (s->getId() == student->getId()) {
            throw std::invalid_argument("Студент ID " + std::to_string(student->getId()) + " уже в этой группе.");
        }
    }
    students.push_back(student);
    student->setGroupNumber(number);
    return *this;
}

StudyGroup& StudyGroup::operator-=(int studentId) {
    auto it = std::find_if(students.begin(), students.end(),
        [studentId](const Student* s) { return s && s->getId() == studentId; });

    if (it == students.end()) {
        throw std::runtime_error("Студент ID " + std::to_string(studentId) + " не найден в группе " + number);
    }
    (*it)->setGroupNumber("");
    students.erase(it);
    return *this;
}

Student* StudyGroup::findStudent(int studentId) const {
    for (auto* s : students) {
        if (s && s->getId() == studentId) return s;
    }
    return nullptr;
}

void StudyGroup::printInfo() const {
    std::cout << "Группа №" << number
        << " (" << courseYear << "-й курс, студентов: "
        << students.size() << "/" << maxCapacity << ")\n";
    for (const auto* s : students) {
        std::cout << "   * " << *s << "\n";
    }
}