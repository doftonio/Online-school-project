#include "../Header files/menu.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/exceptions.h"
#include <iostream>
#include <string>
#include <limits>

namespace {
    int readInt(std::string_view prompt) {
        int value = 0;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                return value;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Ошибка: введите целое число.\n";
        }
    }

    std::string readString(std::string_view prompt) {
        std::string str{};
        std::cout << prompt;
        std::cin >> str;
        return str;
    }

    void handleEnrollStudent(Faculty& faculty, const StudyGroup* group) {
        int id = readInt("Введите ID студента: ");
        std::string first = readString("Введите имя: ");
        std::string last = readString("Введите фамилию: ");
        std::string middle = readString("Введите отчество ('-' если нет): ");
        if (middle == "-") middle.clear();

        try {
            faculty.enrollStudentInGroup(id, first, last, middle, group->getNumber());
            std::cout << "Студент успешно зачислен!\n";
        }
        catch (const AppException& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }

    void handleExpelStudent(Faculty& faculty) {
        int id = readInt("Введите ID студента для отчисления: ");
        try {
            faculty.expelStudent(id);
            std::cout << "Студент успешно отчислен.\n";
        }
        catch (const AppException& e) {
            std::cout << "Ошибка: " << e.what() << "\n";
        }
    }

    void handleInspectStudent(const StudyGroup* group) {
        int id = readInt("Введите ID студента: ");
        if (const Student* s = group->findStudent(id)) {
            std::cout << *s << "\n";
            inspectStudentInternals(*s);
        }
        else {
            std::cout << "Студент с ID " << id << " не найден в группе.\n";
        }
    }

    void groupSubMenu(Faculty& faculty, const StudyGroup* group) {
        if (!group) return;

        int choice = -1;
        while (choice != 0) {
            std::cout << "\n--- МЕНЮ ГРУППЫ: " << group->getNumber() << " ---\n";
            std::cout << "1. Просмотр состава группы\n";
            std::cout << "2. Зачислить нового студента\n";
            std::cout << "3. Отчислить студента по ID\n";
            std::cout << "4. Найти студента и инспектировать (friend-функция)\n";
            std::cout << "0. Назад в главное меню\n";

            choice = readInt("Выберите опцию: ");
            switch (choice) {
            case 1:
                group->printInfo();
                break;
            case 2:
                handleEnrollStudent(faculty, group);
                break;
            case 3:
                handleExpelStudent(faculty);
                break;
            case 4:
                handleInspectStudent(group);
                break;
            case 0:
                break;
            default:
                std::cout << "Неверный выбор. Повторите попытку.\n";
                break;
            }
        }
    }

    void handleCourseTeachers(const Faculty& faculty, Course* course, int choice) {
        if (choice == 2) {
            int tId = readInt("Введите ID преподавателя факультета: ");
            if (Teacher* t = faculty.findTeacher(tId)) {
                *course += t;
                std::cout << "Преподаватель " << t->getFullName() << " добавлен на курс.\n";
            }
            else {
                std::cout << "Преподаватель не найден на факультете.\n";
            }
        }
        else if (choice == 3) {
            int tId = readInt("Введите ID преподавателя для удаления с курса: ");
            *course -= tId;
            std::cout << "Преподаватель удален с курса.\n";
        }
    }

    void handleAssignLecture(Course* course) {
        std::string gNum = readString("Введите номер группы: ");
        int lessons = readInt("Количество занятий: ");
        int tId = readInt("ID лектора: ");
        int topics = readInt("Количество тем: ");
        int hours = readInt("Академических часов: ");
        course->addActivityForGroup(gNum, std::make_unique<LectureActivity>(lessons, tId, topics, hours));
        std::cout << "Лекции успешно назначены!\n";
    }

    void handleAssignLab(Course* course) {
        std::string gNum = readString("Введите номер группы: ");
        int lessons = readInt("Количество занятий: ");
        int tId = readInt("ID преподавателя лаб: ");
        int count = readInt("Количество лабораторных: ");
        int minScore = readInt("Минимальный проходной балл: ");
        course->addActivityForGroup(gNum, std::make_unique<LabActivity>(lessons, tId, count, minScore));
        std::cout << "Лабораторные успешно назначены!\n";
    }

    void handleAssignPractice(Course* course) {
        std::string gNum = readString("Введите номер группы: ");
        int lessons = readInt("Количество занятий: ");
        int tId = readInt("ID преподавателя практик: ");
        int tests = readInt("Количество К/Р: ");
        int tasks = readInt("Количество практических задач: ");
        int calcs = readInt("Количество расчетов: ");
        course->addActivityForGroup(gNum, std::make_unique<PracticeActivity>(lessons, tId, tests, tasks, calcs));
        std::cout << "Практика успешно назначена!\n";
    }

    void handleAddLabGrade(Course* course) {
        std::string gNum = readString("Введите номер группы: ");
        int sId = readInt("ID студента: ");
        int val = readInt("Оценка (1-10): ");
        int num = readInt("Номер лабораторной работы: ");
        int d = readInt("День: ");
        int m = readInt("Месяц: ");
        int y = readInt("Год: ");

        if (auto* act = dynamic_cast<LabActivity*>(course->findActivity(gNum, ActivityType::Lab))) {
            act->addGradeForStudent(sId, LabGrade(val, Date(d, m, y), num));
            std::cout << "Оценка за лабораторную добавлена.\n";
        }
        else {
            std::cout << "Лабораторная активность не найдена.\n";
        }
    }

    void handleAddPracticeGrade(Course* course) {
        std::string gNum = readString("Введите номер группы: ");
        int sId = readInt("ID студента: ");
        int val = readInt("Оценка (1-10): ");
        int num = readInt("Номер работы: ");
        std::string type = readString("Тип работы (КР/Практика/Расчет): ");
        int d = readInt("День: ");
        int m = readInt("Месяц: ");
        int y = readInt("Год: ");

        if (auto* act = dynamic_cast<PracticeActivity*>(course->findActivity(gNum, ActivityType::Practice))) {
            act->addGradeForStudent(sId, PracticeGrade(val, Date(d, m, y), num, type));
            std::cout << "Оценка за практику добавлена.\n";
        }
        else {
            std::cout << "Практическая активность не найдена.\n";
        }
    }

    void handleRemoveGrade(Course* course) {
        std::string gNum = readString("Введите номер группы: ");
        int sId = readInt("ID студента: ");
        int d = readInt("День: ");
        int m = readInt("Месяц: ");
        int y = readInt("Год: ");
        Date targetDate(d, m, y);

        bool removed = false;
        if (auto* act = dynamic_cast<LabActivity*>(course->findActivity(gNum, ActivityType::Lab))) {
            removed = act->removeGradeForStudentByDate(sId, targetDate);
        }
        if (!removed) {
            if (auto* act = dynamic_cast<PracticeActivity*>(course->findActivity(gNum, ActivityType::Practice))) {
                removed = act->removeGradeForStudentByDate(sId, targetDate);
            }
        }

        if (removed) std::cout << "Оценка за дату " << targetDate << " успешно удалена.\n";
        else std::cout << "Оценка за указанную дату не найдена.\n";
    }

    void handleViewJournals(Course* course, int choice) {
        std::string gNum = readString("Введите номер группы: ");
        if (choice == 10) {
            if (const auto* act = dynamic_cast<const LabActivity*>(course->findActivity(gNum, ActivityType::Lab))) {
                printLabJournal(std::cout, *act);
            }
            else {
                std::cout << "Лабораторная активность не найдена.\n";
            }
        }
        else if (choice == 11) {
            if (const auto* act = dynamic_cast<const PracticeActivity*>(course->findActivity(gNum, ActivityType::Practice))) {
                printPracticeJournal(std::cout, *act);
            }
            else {
                std::cout << "Практическая активность не найдена.\n";
            }
        }
    }

    void courseSubMenu(Faculty& faculty, Course* course) {
        if (!course) return;

        int choice = -1;
        while (choice != 0) {
            std::cout << "\n--- МЕНЮ КУРСА: " << course->getTitle() << " (ID: " << course->getId() << ") ---\n";
            std::cout << "1. Полная информация о курсе\n";
            std::cout << "2. Добавить преподавателя на курс\n";
            std::cout << "3. Удалить преподавателя с курса\n";
            std::cout << "4. Назначить лекции группе\n";
            std::cout << "5. Назначить лабораторные группе\n";
            std::cout << "6. Назначить практику группе\n";
            std::cout << "7. Выставить оценку за лабораторную\n";
            std::cout << "8. Выставить оценку за практику\n";
            std::cout << "9. Удалить оценку по дате\n";
            std::cout << "10. Просмотр журнала лабораторных\n";
            std::cout << "11. Просмотр журнала практик\n";
            std::cout << "0. Назад в главное меню\n";

            choice = readInt("Выберите опцию: ");

            try {
                if (choice == 1) course->printFullCourseInfo();
                else if (choice == 2 || choice == 3) handleCourseTeachers(faculty, course, choice);
                else if (choice == 4) handleAssignLecture(course);
                else if (choice == 5) handleAssignLab(course);
                else if (choice == 6) handleAssignPractice(course);
                else if (choice == 7) handleAddLabGrade(course);
                else if (choice == 8) handleAddPracticeGrade(course);
                else if (choice == 9) handleRemoveGrade(course);
                else if (choice == 10 || choice == 11) handleViewJournals(course, choice);
                else if (choice != 0) std::cout << "Неверный выбор.\n";
            }
            catch (const AppException& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
        }
    }

    void handleFacultyTeachersMenu(Faculty& faculty) {
        std::cout << "\n--- Преподаватели (" << faculty.getTeachers().size() << ") ---\n";
        for (const auto& t : faculty.getTeachers()) {
            t->printInfo();
        }
        std::cout << "1. Добавить нового преподавателя в штат\n0. Назад\n";
        if (int sub = readInt("Выбор: "); sub == 1) {
            int id = readInt("ID преподавателя: ");
            std::string first = readString("Имя: ");
            std::string last = readString("Фамилия: ");
            std::string middle = readString("Отчество ('-' если нет): ");
            if (middle == "-") middle.clear();
            std::string dept = readString("Кафедра: ");
            faculty.createTeacher(id, first, last, middle, dept);
            std::cout << "Преподаватель добавлен в штат.\n";
        }
    }

    void handleFacultyGroupsMenu(Faculty& faculty) {
        std::cout << "\n--- Учебные группы (" << faculty.getGroups().size() << ") ---\n";
        for (const auto& g : faculty.getGroups()) {
            std::cout << "Группа №" << g->getNumber() << " (Курс " << g->getCourseYear()
                << ", студентов: " << g->getStudents().size() << "/" << g->getMaxCapacity() << ")\n";
        }
        std::cout << "1. Создать новую группу\n";
        std::cout << "2. Выбрать группу по номеру\n";
        std::cout << "0. Назад\n";
        int sub = readInt("Выбор: ");
        if (sub == 1) {
            std::string num = readString("Номер группы: ");
            int year = readInt("Курс (1-5): ");
            int cap = readInt("Вместимость: ");
            try {
                faculty.createGroup(num, year, cap);
                std::cout << "Группа создана.\n";
            }
            catch (const AppException& e) {
                std::cout << "Ошибка: " << e.what() << "\n";
            }
        }
        else if (sub == 2) {
            std::string num = readString("Введите номер группы: ");
            if (const StudyGroup* g = faculty.findGroup(num)) {
                groupSubMenu(faculty, g);
            }
            else {
                std::cout << "Группа не найдена.\n";
            }
        }
    }

    void handleFacultyCoursesMenu(Faculty& faculty) {
        std::cout << "\n--- Курсы (" << faculty.getCourses().size() << ") ---\n";
        for (const auto& c : faculty.getCourses()) {
            std::cout << "ID: " << c->getId() << " | Название: " << c->getTitle()
                << " | Преподавателей: " << c->getTeachers().size() << "\n";
        }
        std::cout << "1. Создать новый курс\n";
        std::cout << "2. Выбрать курс по ID\n";
        std::cout << "0. Назад\n";
        int sub = readInt("Выбор: ");
        if (sub == 1) {
            int id = readInt("ID курса: ");
            std::string title = readString("Название курса: ");
            faculty.createCourse(id, title);
            std::cout << "Курс создан.\n";
        }
        else if (sub == 2) {
            int id = readInt("Введите ID курса: ");
            if (Course* c = faculty.findCourse(id)) {
                courseSubMenu(faculty, c);
            }
            else {
                std::cout << "Курс не найден.\n";
            }
        }
    }
}

void runMainMenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n============================================\n";
        std::cout << "ГЛАВНОЕ МЕНЮ: Факультет " << faculty.getName() << "\n";
        std::cout << "============================================\n";
        std::cout << "1. Преподаватели факультета\n";
        std::cout << "2. Учебные группы факультета\n";
        std::cout << "3. Курсы (дисциплины)\n";
        std::cout << "4. Общая сводка факультета\n";
        std::cout << "0. Выход\n";

        choice = readInt("Выберите пункт меню: ");

        switch (choice) {
        case 1:
            handleFacultyTeachersMenu(faculty);
            break;
        case 2:
            handleFacultyGroupsMenu(faculty);
            break;
        case 3:
            handleFacultyCoursesMenu(faculty);
            break;
        case 4:
            std::cout << "\n[Сводка по факультету " << faculty.getName() << "]\n"
                << "Преподавателей в штате: " << faculty.getTeachers().size() << "\n"
                << "Групп сформировано:     " << faculty.getGroups().size() << "\n"
                << "Курсов запущено:        " << faculty.getCourses().size() << "\n";
            break;
        case 0:
            std::cout << "Завершение работы программы.\n";
            break;
        default:
            std::cout << "Неверный пункт. Повторите попытку.\n";
            break;
        }
    }
}