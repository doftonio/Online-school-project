#include "../Header files/faculty.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include <iostream>

int main() {
    setlocale(LC_ALL, "Russian");
    Faculty faculty("ФКП БГУИР");

    // 1. Создание преподавателей факультета
    Teacher* tLec = faculty.createTeacher(101, "Алексей", "Сидоров", "Иванович", "ПОИТ");
    Teacher* tLab = faculty.createTeacher(102, "Елена", "Кузнецова", "Васильевна", "ИИТ");
    Teacher* tPr = faculty.createTeacher(103, "Михаил", "Громов", "Петрович", "ВМ");

    // 2. Создание группы и зачисление студентов (StudyGroup::operator+=)
    faculty.createGroup("550501", 2, 25);
    faculty.enrollStudentInGroup(1001, "Егор", "Евсеенко", "Сергеевич", "550501");
    faculty.enrollStudentInGroup(1002, "Иван", "Петров", "Алексеевич", "550501");

    // 3. Создание дисциплины и наполнение пула преподавателей (Course::operator+=)
    Course* oop = faculty.createCourse(1, "Объектно-Ориентированное Программирование");
    *oop += tLec;
    *oop += tLab;
    *oop += tPr;

    // 4. Добавление по одной активности каждого типа
    oop->addActivityForGroup("550501", std::make_unique<LectureActivity>(16, 101, 8, 32));
    oop->addActivityForGroup("550501", std::make_unique<LabActivity>(12, 102, 6, 60));
    oop->addActivityForGroup("550501", std::make_unique<PracticeActivity>(8, 103, 2, 4, 1));

    // 5. Выставление и удаление оценок в журналах
    Date d1(12, 10, 2026);
    Date d2(19, 10, 2026);

    if (auto* labAct = dynamic_cast<LabActivity*>(oop->findActivity("550501", ActivityType::Lab))) {
        labAct->addGradeForStudent(1001, LabGrade(9, d1, 1));
        labAct->addGradeForStudent(1001, LabGrade(8, d2, 2));
        labAct->addGradeForStudent(1002, LabGrade(6, d1, 1));

        std::cout << "\n";
        printLabJournal(std::cout, *labAct);

        // Удаление оценки по дате
        labAct->removeGradeForStudentByDate(1001, d1);
        std::cout << "\nПосле удаления оценки за 12.10.2026 у студента 1001:\n";
        printLabJournal(std::cout, *labAct);
    }

    // 6. Проверка работы friend-функции инспектирования Student
    if (StudyGroup* g = faculty.findGroup("550501")) {
        if (Student* s = g->findStudent(1001)) {
            inspectStudentInternals(*s);
        }
    }

    // 7. Сводная карточка курса
    oop->printFullCourseInfo();

    // 8. Отчисление студента (StudyGroup::operator-=)
    faculty.expelStudent(1002);
    faculty.findGroup("550501")->printInfo();

    return 0;
}