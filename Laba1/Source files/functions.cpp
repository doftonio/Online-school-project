#include "header.h"
#include <iostream>

Student::Student() 
{
    studentId = 0;
    studentName = "";
    completedTasks = 0;
}

void Student::initStudent(int id, std::string name) 
{
    studentId = id;
    studentName = name;
    completedTasks = 0;
}

int Student::getStudentId() 
{
    return studentId;
}

std::string Student::getStudentName()
{
    return studentName;
}

int Student::getCompletedTasks() 
{
    return completedTasks;
}

void Student::setStudentName(std::string name) 
{
    studentName = name;
}

void Student::completeTask()
{
    completedTasks++;
}

void Student::resetTasks() 
{
    completedTasks = 0;
}

void Student::printInfo() 
{
    std::cout << "Student: \033[36m" << studentName << "\033[0m"
        << ", Student ID: " << studentId
        << ", completed tasks: \033[32m" << completedTasks << "\033[0m" << std::endl;
}

Course::Course() 
{
    courseTitle = "";
    teacherName = "";
    totalLessons = 0;
    maxCapacity = 0;
    currentStudentsCount = 0;
    enrolledStudents = nullptr;
}

Course::~Course() 
{
    if (enrolledStudents != nullptr) 
    {
        delete[] enrolledStudents;
        enrolledStudents = nullptr;
    }
}

void Course::initCourse(std::string title, std::string teacher, int lessons, int capacity) 
{
    if (enrolledStudents != nullptr) 
    {
        delete[] enrolledStudents;
        enrolledStudents = nullptr;
    }

    courseTitle = title;
    teacherName = teacher;
    totalLessons = lessons;
    maxCapacity = capacity;
    currentStudentsCount = 0;

    if (maxCapacity > 0) 
    {
        enrolledStudents = new Student[maxCapacity];
    }
}

std::string Course::getCourseTitle() 
{
    return courseTitle;
}

std::string Course::getTeacherName() 
{
    return teacherName;
}

int Course::getTotalLessons() 
{
    return totalLessons;
}

int Course::getMaxCapacity() 
{
    return maxCapacity;
}

int Course::getEnrolledCount() 
{
    return currentStudentsCount;
}

void Course::setTeacherName(std::string teacher) 
{
    teacherName = teacher;
}

void Course::setTotalLessons(int lessons)
{
    if (lessons > 0) {
        totalLessons = lessons;
    }
}

bool Course::enrollStudent(int id, std::string name) 
{
    if (currentStudentsCount >= maxCapacity) 
    {
        std::cout << "\033[31mFailed to enroll student " << name
            << ": course limit reached (limit: " << maxCapacity << ").\033[0m" << std::endl;
        return false;
    }

    for (int i = 0; i < currentStudentsCount; i++)
    {
        if (enrolledStudents[i].getStudentId() == id) 
        {
            std::cout << "\033[33mStudent with ID " << id
                << " is already enrolled in this course.\033[0m" << std::endl;
            return false;
        }
    }

    enrolledStudents[currentStudentsCount].initStudent(id, name);
    currentStudentsCount++;
    std::cout << "\033[32mStudent " << name << " successfully enrolled in \""
        << courseTitle << "\".\033[0m" << std::endl;
    return true;
}

bool Course::removeStudent(int id) 
{
    int targetIndex = -1;

    for (int i = 0; i < currentStudentsCount; i++)
    {
        if (enrolledStudents[i].getStudentId() == id) 
        {
            targetIndex = i;
            break;
        }
    }

    if (targetIndex == -1) 
    {
        std::cout << "\033[31mStudent with ID " << id
            << " was not found on this course.\033[0m" << std::endl;
        return false;
    }

    std::string deletedName = enrolledStudents[targetIndex].getStudentName();

    for (int i = targetIndex; i < currentStudentsCount - 1; i++) 
    {
        enrolledStudents[i] = enrolledStudents[i + 1];
    }

    currentStudentsCount--;
    std::cout << "\033[32mStudent " << deletedName
        << " has been removed from \"" << courseTitle << "\". Spot freed.\033[0m" << std::endl;
    return true;
}

void Course::recordTaskCompletion(int studentId) 
{
    for (int i = 0; i < currentStudentsCount; i++) 
    {
        if (enrolledStudents[i].getStudentId() == studentId) 
        {
            enrolledStudents[i].completeTask();
            std::cout << "\033[32mCompleted task recorded for " << enrolledStudents[i].getStudentName()
                << ".\033[0m" << std::endl;
            return;
        }
    }
    std::cout << "\033[31mStudent with ID " << studentId
        << " was not found on this course.\033[0m" << std::endl;
}

int Course::calculateStudentProgress(int studentId)
{
    if (totalLessons <= 0)
    {
        return 0;
    }

    for (int i = 0; i < currentStudentsCount; i++) 
    {
        if (enrolledStudents[i].getStudentId() == studentId) 
        {
            int progress = (enrolledStudents[i].getCompletedTasks() * 100) / totalLessons;
            if (progress > 100) 
            {
                return 100;
            }
            return progress;
        }
    }
    return -1;
}

void Course::printFullCourseInfo() 
{
    std::cout << "\n\033[34mCourse Information:\033[0m" << std::endl;
    std::cout << "Title: \033[36m" << courseTitle << "\033[0m" << std::endl;
    std::cout << "Instructor: " << teacherName << std::endl;
    std::cout << "Total lessons: " << totalLessons << std::endl;
    std::cout << "Enrolled students: " << currentStudentsCount << " / " << maxCapacity << std::endl;

    if (currentStudentsCount == 0) 
    {
        std::cout << "\033[33mNo students currently enrolled.\033[0m" << std::endl;
    }
    else {
        std::cout << "Student list:" << std::endl;
        for (int i = 0; i < currentStudentsCount; i++) 
        {
            int progress = calculateStudentProgress(enrolledStudents[i].getStudentId());
            std::cout << "  " << i + 1 << ". "
                << enrolledStudents[i].getStudentName()
                << " (ID: " << enrolledStudents[i].getStudentId() << ")"
                << " — tasks completed: " << enrolledStudents[i].getCompletedTasks()
                << ", progress: \033[32m" << progress << "%\033[0m" << std::endl;
        }
    }
    std::cout << std::endl;
}