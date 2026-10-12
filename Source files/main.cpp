#include "../Header files/faculty.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/menu.h"
#include <iostream>

void populateDemoData(Faculty& faculty) {
    // 1. Штат преподавателей
    Teacher* tLec = faculty.createTeacher(101, "Алексей", "Сидоров", "Иванович", "ПОИТ");
    Teacher* tLab = faculty.createTeacher(102, "Елена", "Кузнецова", "Васильевна", "ИИТ");
    Teacher* tPr = faculty.createTeacher(103, "Михаил", "Громов", "Петрович", "ВМ");

    // 2. Группы и студенты
    faculty.createGroup("550501", 2, 25);
    faculty.createGroup("550502", 2, 25);
    faculty.enrollStudentInGroup(1001, "Егор", "Евсеенко", "Сергеевич", "550501");
    faculty.enrollStudentInGroup(1002, "Иван", "Петров", "Алексеевич", "550501");
    faculty.enrollStudentInGroup(1003, "Анна", "Смирнова", "Игоревна", "550502");

    // 3. Курс
    Course* oop = faculty.createCourse(1, "Объектно-Ориентированное Программирование");
    *oop += tLec;
    *oop += tLab;
    *oop += tPr;

    // 4. Активности для группы 550501
    oop->addActivityForGroup("550501", std::make_unique<LectureActivity>(16, 101, 8, 32));
    oop->addActivityForGroup("550501", std::make_unique<LabActivity>(12, 102, 6, 60));
    oop->addActivityForGroup("550501", std::make_unique<PracticeActivity>(8, 103, 2, 4, 1));

    // 5. Оценки
    if (auto* labAct = dynamic_cast<LabActivity*>(oop->findActivity("550501", ActivityType::Lab))) {
        labAct->addGradeForStudent(1001, LabGrade(9, Date(12, 10, 2026), 1));
        labAct->addGradeForStudent(1001, LabGrade(8, Date(19, 10, 2026), 2));
        labAct->addGradeForStudent(1002, LabGrade(7, Date(12, 10, 2026), 1));
    }
}

int main() {
    setlocale(LC_ALL, "Russian");
    Faculty faculty("ФКП БГУИР");

    // Предзаполнение базовыми данными для удобства тестирования
    populateDemoData(faculty);

    // Запуск консольного интерфейса управления
    runMainMenu(faculty);

    return 0;
}