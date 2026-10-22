#include "teacher.h"
#include <iostream>

Teacher::Teacher(int teacherId, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept)
    : Person(first, last, middle), id(teacherId), department(dept) {}

void Teacher::printInfo() const {
    std::cout << "Преподаватель [ID: " << id << "] " << getFullName()
              << " | Кафедра: " << department << "\n";
}
