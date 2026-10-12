#include "../Header files/student.h"

Student::Student(int studentId, std::string_view first, std::string_view last, std::string_view middle, int tasks)
    : Person(first, last, middle), id(studentId), completedTasks(tasks) {
}

int Student::getId() const { return id; }
std::string Student::getGroupNumber() const { return groupNumber; }
int Student::getCompletedTasks() const { return completedTasks; }

void Student::setGroupNumber(std::string_view group) { groupNumber = group; }
void Student::completeTask() { completedTasks++; }
void Student::setCompletedTasks(int tasks) { completedTasks = tasks; }

void Student::printInfo() const {
    std::cout << "Студент: " << getFullName()
        << " [ID: " << id
        << ", Группа: " << (groupNumber.empty() ? "N/A" : groupNumber)
        << ", Задач: " << completedTasks << "]\n";
}

bool Student::operator==(const Student& other) const { return id == other.id; }
auto Student::operator<=>(const Student& other) const { return completedTasks <=> other.completedTasks; }

void inspectStudentInternals(const Student& student) {
    std::cout << "[FRIEND FUNCTION inspectStudentInternals]\n"
        << "  -> private id: " << student.id << "\n"
        << "  -> private groupNumber: \"" << student.groupNumber << "\"\n"
        << "  -> private completedTasks: " << student.completedTasks << "\n";
}