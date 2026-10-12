#include "../Header files/studentContainers.h"
#include <algorithm>

StudentLabGradesContainer::StudentLabGradesContainer(int id) : studentId(id) {}

int StudentLabGradesContainer::getStudentId() const { return studentId; }
const std::vector<LabGrade>& StudentLabGradesContainer::getGrades() const { return grades; }

void StudentLabGradesContainer::addGrade(const LabGrade& grade) {
    grades.push_back(grade);
}

bool StudentLabGradesContainer::removeGradeByDate(const Date& targetDate) {
    auto it = std::find_if(grades.begin(), grades.end(),
        [&targetDate](const LabGrade& g) { return g.getDate() == targetDate; });

    if (it != grades.end()) {
        grades.erase(it);
        return true;
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
    auto it = std::find_if(grades.begin(), grades.end(),
        [&targetDate](const PracticeGrade& g) { return g.getDate() == targetDate; });

    if (it != grades.end()) {
        grades.erase(it);
        return true;
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