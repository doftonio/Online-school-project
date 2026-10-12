#include "../Header files/teacher.h"

Teacher::Teacher(int teacherId, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept)
    : Person(first, last, middle), id(teacherId), department(dept) {
}

int Teacher::getId() const { return id; }
std::string Teacher::getDepartment() const { return department; }

void Teacher::printInfo() const {
    std::cout << "Teacher: " << getFullName()
        << " [ID: " << id << ", Department: " << department << "]\n";
}

bool Teacher::operator==(const Teacher& other) const { return id == other.id; }