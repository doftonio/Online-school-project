#include "../Header files/faculty.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/menu.h"
#include <iostream>

void populateDemoData(Faculty& faculty) {
    Teacher* tLec = faculty.createTeacher(101, "Alexey", "Sidorov", "Ivanovich", "SEIT");
    Teacher* tLab = faculty.createTeacher(102, "Elena", "Kuznetsova", "Vasilyevna", "IIT");
    Teacher* tPr = faculty.createTeacher(103, "Mikhail", "Gromov", "Petrovich", "Higher Math");

    faculty.createGroup("550501", 2, 25);
    faculty.createGroup("550502", 2, 25);
    faculty.enrollStudentInGroup(1001, "Egor", "Evseenko", "Sergeevich", "550501");
    faculty.enrollStudentInGroup(1002, "Ivan", "Petrov", "Alexeevich", "550501");
    faculty.enrollStudentInGroup(1003, "Anna", "Smirnova", "Igorevna", "550502");

    Course* oop = faculty.createCourse(1, "Object-Oriented Programming");
    *oop += tLec;
    *oop += tLab;
    *oop += tPr;

    oop->addActivityForGroup("550501", std::make_unique<LectureActivity>(16, 101, 8, 32));
    oop->addActivityForGroup("550501", std::make_unique<LabActivity>(12, 102, 6, 60));
    oop->addActivityForGroup("550501", std::make_unique<PracticeActivity>(8, 103, 2, 4, 1));

    if (auto* labAct = dynamic_cast<LabActivity*>(oop->findActivity("550501", ActivityType::Lab))) {
        labAct->addGradeForStudent(1001, LabGrade(9, Date(12, 10, 2026), 1));
        labAct->addGradeForStudent(1001, LabGrade(8, Date(19, 10, 2026), 2));
        labAct->addGradeForStudent(1002, LabGrade(7, Date(12, 10, 2026), 1));
    }
}

int main() {
    Faculty faculty("FCAD BSUIR");

    populateDemoData(faculty);
    runMainMenu(faculty);

    return 0;
}