#include "../Header files/studentContainers.h"

StudentLabGradesContainer::StudentLabGradesContainer(int id) : studentId(id) {}

int StudentLabGradesContainer::getStudentId() const { return studentId; }
const std::vector<LabGrade>& StudentLabGradesContainer::getGrades() const { return grades; }

void StudentLabGradesContainer::addGrade(const LabGrade& grade) {
    grades.push_back(grade);
}

bool StudentLabGradesContainer::removeGradeByDate(const Date& targetDate) {
    for (size_t i = 0; i < grades.size(); ++i) {
        if (grades[i].getDate() == targetDate) {
            grades.erase(grades.begin() + i);
            return true;
        }
    }
    return false;
}

double StudentLabGradesContainer::getAverageScore() const {
    if (grades.empty()) return 0.0;
    int sum = 0;
    for (const auto& g : grades) sum += g.getValue();
    return static_cast<double>(sum) / grades.size();
}

std::ostream& operator<<(std::ostream& os, const StudentLabGradesContainer& c) {
    os << "ID " << c.studentId << " | ќценки: ";
    if (c.grades.empty()) {
        os << "нет";
    }
    else {
        for (const auto& g : c.grades) os << g << " ";
    }
    os << " | —р. балл: " << c.getAverageScore();
    return os;
}

StudentPracticeGradesContainer::StudentPracticeGradesContainer(int id) : studentId(id) {}

int StudentPracticeGradesContainer::getStudentId() const { return studentId; }
const std::vector<PracticeGrade>& StudentPracticeGradesContainer::getGrades() const { return grades; }

void StudentPracticeGradesContainer::addGrade(const PracticeGrade& grade) {
    grades.push_back(grade);
}

bool StudentPracticeGradesContainer::removeGradeByDate(const Date& targetDate) {
    for (size_t i = 0; i < grades.size(); ++i) {
        if (grades[i].getDate() == targetDate) {
            grades.erase(grades.begin() + i);
            return true;
        }
    }
    return false;
}

double StudentPracticeGradesContainer::getAverageScore() const {
    if (grades.empty()) return 0.0;
    int sum = 0;
    for (const auto& g : grades) sum += g.getValue();
    return static_cast<double>(sum) / grades.size();
}

std::ostream& operator<<(std::ostream& os, const StudentPracticeGradesContainer& c) {
    os << "ID " << c.studentId << " | ќценки: ";
    if (c.grades.empty()) {
        os << "нет";
    }
    else {
        for (const auto& g : c.grades) os << g << " ";
    }
    os << " | —р. балл: " << c.getAverageScore();
    return os;
}