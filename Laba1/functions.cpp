#include "header.h"
#include <iostream>

Student::Student() {
    studentId = 0;
    studentName = "";
    completedTasks = 0;
}

void Student::initStudent(int id, std::string name) {
    studentId = id;
    studentName = name;
    completedTasks = 0;
}

int Student::getStudentId() {
    return studentId;
}

std::string Student::getStudentName() {
    return studentName;
}

int Student::getCompletedTasks() {
    return completedTasks;
}

void Student::setStudentName(std::string name) {
    studentName = name;
}

void Student::completeTask() {
    completedTasks++;
}

void Student::resetTasks() {
    completedTasks = 0;
}

void Student::printInfo() {
    std::cout << "Студент: \033[36m" << studentName << "\033[0m"
        << ", номер билета: " << studentId
        << ", выполнено заданий: \033[32m" << completedTasks << "\033[0m" << std::endl;
}

Course::Course() {
    courseTitle = "";
    teacherName = "";
    totalLessons = 0;
    maxCapacity = 0;
    currentStudentsCount = 0;
    enrolledStudents = nullptr;
}

Course::~Course() {
    if (enrolledStudents != nullptr) {
        delete[] enrolledStudents;
        enrolledStudents = nullptr;
    }
}

void Course::initCourse(std::string title, std::string teacher, int lessons, int capacity) {
    if (enrolledStudents != nullptr) {
        delete[] enrolledStudents;
        enrolledStudents = nullptr;
    }

    courseTitle = title;
    teacherName = teacher;
    totalLessons = lessons;
    maxCapacity = capacity;
    currentStudentsCount = 0;

    if (maxCapacity > 0) {
        enrolledStudents = new Student[maxCapacity];
    }
}

std::string Course::getCourseTitle() {
    return courseTitle;
}

std::string Course::getTeacherName() {
    return teacherName;
}

int Course::getTotalLessons() {
    return totalLessons;
}

int Course::getMaxCapacity() {
    return maxCapacity;
}

int Course::getEnrolledCount() {
    return currentStudentsCount;
}

void Course::setTeacherName(std::string teacher) {
    teacherName = teacher;
}

void Course::setTotalLessons(int lessons) {
    if (lessons > 0) {
        totalLessons = lessons;
    }
}

bool Course::enrollStudent(int id, std::string name) {
    if (currentStudentsCount >= maxCapacity) {
        std::cout << "\033[31mНе удалось записать студента " << name
            << ": группа уже набрана (лимит " << maxCapacity << " чел).\033[0m" << std::endl;
        return false;
    }

    for (int i = 0; i < currentStudentsCount; i++) {
        if (enrolledStudents[i].getStudentId() == id) {
            std::cout << "\033[33mСтудент с номером билета " << id
                << " уже числится в этой группе.\033[0m" << std::endl;
            return false;
        }
    }

    enrolledStudents[currentStudentsCount].initStudent(id, name);
    currentStudentsCount++;
    std::cout << "\033[32mСтудент " << name << " успешно зачислен на курс \""
        << courseTitle << "\".\033[0m" << std::endl;
    return true;
}

bool Course::removeStudent(int id) {
    int targetIndex = -1;

    for (int i = 0; i < currentStudentsCount; i++) {
        if (enrolledStudents[i].getStudentId() == id) {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) {
        std::cout << "\033[31mСтудент с номером билета " << id
            << " не найден на курсе.\033[0m" << std::endl;
        return false;
    }

    std::string deletedName = enrolledStudents[targetIndex].getStudentName();

    for (int i = targetIndex; i < currentStudentsCount - 1; i++) {
        enrolledStudents[i] = enrolledStudents[i + 1];
    }

    currentStudentsCount--;
    std::cout << "\033[32mСтудент " << deletedName
        << " отчислен с курса \"" << courseTitle << "\". Место освобождено.\033[0m" << std::endl;
    return true;
}

void Course::recordTaskCompletion(int studentId) {
    for (int i = 0; i < currentStudentsCount; i++) {
        if (enrolledStudents[i].getStudentId() == studentId) {
            enrolledStudents[i].completeTask();
            std::cout << "\033[32mСтуденту " << enrolledStudents[i].getStudentName()
                << " засчитано выполненное задание.\033[0m" << std::endl;
            return;
        }
    }
    std::cout << "\033[31mСтудент с номером билета " << studentId
        << " не найден среди участников курса.\033[0m" << std::endl;
}

int Course::calculateStudentProgress(int studentId) {
    if (totalLessons <= 0) {
        return 0;
    }

    for (int i = 0; i < currentStudentsCount; i++) {
        if (enrolledStudents[i].getStudentId() == studentId) {
            int progress = (enrolledStudents[i].getCompletedTasks() * 100) / totalLessons;
            if (progress > 100) {
                return 100;
            }
            return progress;
        }
    }
    return -1; 
}

void Course::printFullCourseInfo() {
    std::cout << "\n\033[34mИнформация о курсе:\033[0m" << std::endl;
    std::cout << "Название: \033[36m" << courseTitle << "\033[0m" << std::endl;
    std::cout << "Преподаватель: " << teacherName << std::endl;
    std::cout << "План занятий: " << totalLessons << std::endl;
    std::cout << "Заполненность группы: " << currentStudentsCount << " из " << maxCapacity << " мест" << std::endl;

    if (currentStudentsCount == 0) {
        std::cout << "\033[33mНа курс пока никто не записался.\033[0m" << std::endl;
    }
    else {
        std::cout << "Список учащихся:" << std::endl;
        for (int i = 0; i < currentStudentsCount; i++) {
            int progress = calculateStudentProgress(enrolledStudents[i].getStudentId());
            std::cout << "  " << i + 1 << ". "
                << enrolledStudents[i].getStudentName()
                << " (билет №" << enrolledStudents[i].getStudentId() << ")"
                << " — сдано: " << enrolledStudents[i].getCompletedTasks()
                << ", освоено: \033[32m" << progress << "%\033[0m" << std::endl;
        }
    }
    std::cout << std::endl;
}