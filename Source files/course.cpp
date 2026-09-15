#include "../Header files/header.h"
#include <iostream>

Course::Course()
{
    courseTitle = "";
    teacherName = "";
    totalLessons = 0;
    maxCapacity = 0;
    Id = 0;
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

void Course::initCourse(int id, std::string title, std::string teacher,
    int lessons, int capacity)
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
    Id = id;
    currentStudentsCount = 0;

    if (maxCapacity > 0)
    {
        enrolledStudents = new Student[maxCapacity];
    }
}

int Course::getCourseId()
{
    return Id;
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
                << " - tasks completed: " << enrolledStudents[i].getCompletedTasks()
                << ", progress: \033[32m" << progress << "%\033[0m" << std::endl;
        }
    }
    std::cout << std::endl;
}
CourseList::CourseList()
{
    head = nullptr;
    numberOfCourses = 0;
}

CourseList::~CourseList()
{
    while (head != nullptr)
    {
        deleteNode(head);
    }
}

void CourseList::deleteNode(CourseNode* node)
{
    if (node == nullptr) return;

    if (node == head)
    {
        head = node->next;
    }

    if (node->prev != nullptr)
    {
        node->prev->next = node->next;
    }

    if (node->next != nullptr)
    {
        node->next->prev = node->prev;
    }

    delete node;
    numberOfCourses--;
}

CourseNode* CourseList::getCoursePointerById(int targetId)
{
    CourseNode* current = head;
    while (current != nullptr)
    {
        if (current->data.getCourseId() == targetId)
        {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void CourseList::addCourse(int id, std::string title, std::string teacher, int lessons, int capacity)
{
    
    CourseNode* newNode = new CourseNode();
    newNode->data.initCourse(id, title, teacher, lessons, capacity); 
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr)
    {
        head = newNode;
    }
    else
    {
        CourseNode* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
    }

    numberOfCourses++;
}

bool CourseList::removeCourseById(int targetId)
{
    CourseNode* targetNode = getCoursePointerById(targetId);
    if (targetNode != nullptr)
    {
        deleteNode(targetNode);
        return true;
    }
    return false;
}

void CourseList::displayListOfCourses()
{
    if (head == nullptr)
    {
        std::cout << "\033[33mNo courses available.\033[0m\n";
        return;
    }

    std::cout << "\n\033[34m--- Courses List (" << numberOfCourses << ") ---\033[0m\n";
    CourseNode* current = head;
    while (current != nullptr)
    {
        std::cout << "ID: " << current->data.getCourseId()
            << " | Title: \033[36m" << current->data.getCourseTitle() << "\033[0m"
            << " | Students: " << current->data.getEnrolledCount() << "/" << current->data.getMaxCapacity()
            << std::endl;
        current = current->next;
    }
    std::cout << "------------------------------------\n";
}