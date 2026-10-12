#include "../Header files/faculty.h"
#include <algorithm>
#include <stdexcept>

Faculty::Faculty(std::string_view facultyName) : name(facultyName) {}

std::string Faculty::getName() const { return name; }

Teacher* Faculty::createTeacher(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept) {
    allTeachers.push_back(std::make_unique<Teacher>(id, first, last, middle, dept));
    return allTeachers.back().get();
}

StudyGroup* Faculty::createGroup(std::string_view number, int year, int capacity) {
    allGroups.push_back(std::make_unique<StudyGroup>(number, year, capacity));
    return allGroups.back().get();
}

Course* Faculty::createCourse(int id, std::string_view title) {
    allCourses.push_back(std::make_unique<Course>(id, title));
    return allCourses.back().get();
}

StudyGroup* Faculty::findGroup(std::string_view groupNum) const {
    for (const auto& g : allGroups) {
        if (g->getNumber() == groupNum) return g.get();
    }
    return nullptr;
}

Student* Faculty::enrollStudentInGroup(int id, std::string_view first, std::string_view last,
    std::string_view middle, std::string_view groupNum)
{
    StudyGroup* group = findGroup(groupNum);
    if (!group) {
        throw std::runtime_error("Группа " + std::string(groupNum) + " не найдена на факультете.");
    }

    for (const auto& s : allStudents) {
        if (s->getId() == id) {
            throw std::invalid_argument("Студент ID " + std::to_string(id) + " уже существует.");
        }
    }

    allStudents.push_back(std::make_unique<Student>(id, first, last, middle));
    Student* studentPtr = allStudents.back().get();
    *group += studentPtr;
    return studentPtr;
}

void Faculty::expelStudent(int studentId) {
    auto studentIt = std::find_if(allStudents.begin(), allStudents.end(),
        [studentId](const std::unique_ptr<Student>& s) { return s->getId() == studentId; });

    if (studentIt == allStudents.end()) {
        throw std::runtime_error("Студент ID " + std::to_string(studentId) + " не найден на факультете.");
    }

    std::string groupNum = (*studentIt)->getGroupNumber();
    if (!groupNum.empty()) {
        if (StudyGroup* group = findGroup(groupNum)) {
            *group -= studentId;
        }
    }

    allStudents.erase(studentIt);
}