#include "../Header files/studyGroup.h"
#include "../Header files/exceptions.h"
#include <format>
#include <iostream>

StudyGroup::StudyGroup(std::string_view groupNum, int year, int capacity)
    : number(groupNum), courseYear(year), maxCapacity(capacity) {
    if (capacity <= 0) {
        throw InvalidOperationException("Вместимость группы должна быть положительной.");
    }
}

std::string StudyGroup::getNumber() const { return number; }
int StudyGroup::getCourseYear() const { return courseYear; }
int StudyGroup::getMaxCapacity() const { return maxCapacity; }
std::span<const Student* const> StudyGroup::getStudents() const { return students; }

StudyGroup& StudyGroup::operator+=(Student* student) {
    if (!student) {
        throw InvalidOperationException("Попытка привязать к группе nullptr.");
    }
    if (static_cast<int>(students.size()) >= maxCapacity) {
        throw CapacityExceededException(std::format("Группа {} заполнена!", number));
    }
    for (const auto* s : students) {
        if (s->getId() == student->getId()) {
            throw DuplicateEntityException(std::format("Студент ID {} уже в этой группе.", student->getId()));
        }
    }
    students.push_back(student);
    student->setGroupNumber(number);
    return *this;
}

StudyGroup& StudyGroup::operator-=(int studentId) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i] && students[i]->getId() == studentId) {
            students[i]->setGroupNumber("");
            students.erase(students.begin() + i);
            return *this;
        }
    }
    throw EntityNotFoundException(std::format("Студент ID {} не найден в группе {}", studentId, number));
}

Student* StudyGroup::findStudent(int studentId) {
    for (auto* s : students) {
        if (s && s->getId() == studentId) return s;
    }
    return nullptr;
}

const Student* StudyGroup::findStudent(int studentId) const {
    for (const auto* s : students) {
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