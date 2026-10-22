#include "../Header files/faculty.h"
#include "../Header files/teacher.h"
#include "../Header files/student.h"
#include "../Header files/studyGroup.h"
#include "../Header files/course.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/menu.h"
#include <iostream>
#include <memory>

int main() {
    Faculty faculty("Faculty of Computer Systems and Networks");

    Teacher* t1 = faculty.createTeacher(101, "Alexey", "Sidorov", "Ivanovich", "SEIT");
    Teacher* t2 = faculty.createTeacher(102, "Elena", "Kuznetsova", "Vasilyevna", "IIT");
    Teacher* t3 = faculty.createTeacher(103, "Mikhail", "Gromov", "Petrovich", "Higher Math");

    StudyGroup* g1 = faculty.createGroup("550501", 2, 30);
    faculty.enrollStudentInGroup(1, "Ivan", "Ivanov", "Ivanovich", g1);
    faculty.enrollStudentInGroup(2, "Petr", "Petrov", "Petrovich", g1);
    faculty.enrollStudentInGroup(3, "Anna", "Sidorova", "Alexandrovna", g1);

    Course* course = faculty.createCourse(1, "Object-Oriented Programming");
    *course += t1;
    *course += t2;
    *course += t3;

    course->addActivity(std::make_unique<LectureActivity>(16, t1, 8, 32));
    course->addActivity(std::make_unique<LabActivity>(16, t2, 8, 4));
    course->addActivity(std::make_unique<PracticeActivity>(16, t3, 4, 12, 6));

    if (const auto* labAct = static_cast<const LabActivity*>(course->findActivity(ActivityType::Lab)); labAct) {
        std::cout << "Lab Activity initialized successfully: " << labAct->getTitle() << "\n";
    }

    runMainMenu(faculty);
    return 0;
}
