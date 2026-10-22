#include "student.h"
#include <iostream>

Student::Student(int studentId, std::string_view first, std::string_view last, std::string_view middle, int tasks)
    : Person(first, last, middle), id(studentId), completedTasks(tasks) {}

void Student::printInfo() const {
    std::cout << "Студент [ID: " << id << "] " << getFullName()
              << " | Выполнено заданий: " << completedTasks << "\n";
}
