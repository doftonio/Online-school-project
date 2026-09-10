#include "header.h"
#include <iostream>
#include <string>

int main() {
    setlocale(LC_ALL, "Russian");

    std::cout << "\033[34mПроверка базовых операций с объектами:\033[0m\n";

    Student singleStudent;
    singleStudent.initStudent(101, "Иван Иванов");
    singleStudent.printInfo();
    singleStudent.setStudentName("Иван Петров");
    std::cout << "Имя после изменения: \033[36m" << singleStudent.getStudentName() << "\033[0m\n\n";

    Course cppCourse;
    cppCourse.initCourse("Программирование на C++", "Александр Владимирович Сидоров", 10, 2);

    Course webCourse;
    webCourse.initCourse("Веб-разработка", "Елена Сергеевна Кузнецова", 8, 5);

    std::cout << "\033[34mЗачисление на курс C++ с ограничением в 2 места:\033[0m\n";
    cppCourse.enrollStudent(101, "Иван Петров");
    cppCourse.enrollStudent(102, "Анна Смирнова");
    cppCourse.enrollStudent(103, "Павел Ковалев"); // Ошибка лимита

    std::cout << "\n\033[34mЗачисление студентов на курс по веб-разработке:\033[0m\n";
    webCourse.enrollStudent(102, "Анна Смирнова");
    webCourse.enrollStudent(103, "Павел Ковалев");

    std::cout << "\n\033[34mФиксация сданных заданий:\033[0m\n";
    cppCourse.recordTaskCompletion(101);
    cppCourse.recordTaskCompletion(101);
    cppCourse.recordTaskCompletion(102);

    webCourse.recordTaskCompletion(103);

    std::cout << "\n\033[34mТекущее состояние групп:\033[0m\n";
    cppCourse.printFullCourseInfo();
    webCourse.printFullCourseInfo();

    int userChoice = -1;
    while (userChoice != 0) {
        std::cout << "\033[33mУправление курсом C++:\033[0m\n";
        std::cout << "1. Записать нового студента\n";
        std::cout << "2. Отчислить студента с курса\n";
        std::cout << "3. Отметить выполнение задания\n";
        std::cout << "4. Назначить нового преподавателя\n";
        std::cout << "5. Показать ведомость группы\n";
        std::cout << "0. Завершить программу\n";
        std::cout << "Выберите действие: ";
        std::cin >> userChoice;

        switch (userChoice) {
        case 1: {
            int studentId;
            std::string studentName;
            std::cout << "Введите номер студенческого билета: ";
            std::cin >> studentId;
            std::cin.ignore();
            std::cout << "Введите фамилию и имя студента: ";
            std::getline(std::cin, studentName);
            cppCourse.enrollStudent(studentId, studentName);
            break;
        }
        case 2: {
            int studentId;
            std::cout << "Введите номер билета студента для отчисления: ";
            std::cin >> studentId;
            cppCourse.removeStudent(studentId);
            break;
        }
        case 3: {
            int studentId;
            std::cout << "Введите номер билета студента: ";
            std::cin >> studentId;
            cppCourse.recordTaskCompletion(studentId);
            break;
        }
        case 4: {
            std::string newTeacherName;
            std::cin.ignore();
            std::cout << "Введите ФИО нового преподавателя: ";
            std::getline(std::cin, newTeacherName);
            cppCourse.setTeacherName(newTeacherName);
            std::cout << "\033[32mПреподаватель курса обновлен.\033[0m\n";
            break;
        }
        case 5:
            cppCourse.printFullCourseInfo();
            break;
        case 0:
            std::cout << "Работа с программой завершена.\n";
            break;
        default:
            std::cout << "\033[31mТакого пункта в меню нет, повторите ввод.\033[0m\n";
            break;
        }
        std::cout << "\n";
    }

    return 0;
}