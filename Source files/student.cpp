#include "../Header files/student.h"
#include <iostream>

Student::Student(int studentId, std::string_view first, std::string_view last, std::string_view middle, int tasks)
    : Person(first, last, middle), id(studentId), completedTasks(tasks) {}

void Student::printInfo() const {
    std::cout << "Student [ID: " << id << "] " << getFullName()
              << " | Completed tasks: " << completedTasks << "\n";
}

void Student::inspectStudentInternals(const Student& other) const {
    std::cout << "Inspect student [ID: " << other.id << "], tasks: " << other.completedTasks << "\n";
}

void inspectStudentInternals(const Student& s) {
    s.printInfo();
}

void inspectStudentInternals(const Student& s1, const Student& s2) {
    s1.printInfo();
    s2.printInfo();
}
