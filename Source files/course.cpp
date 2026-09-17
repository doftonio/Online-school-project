#include "../Header files/course.h"
#include <iostream>

void Course::initCourse(int id, const std::string& title, const std::string& teacher, int lessons, int capacity)
{
    courseTitle = title;
    teacherName = teacher;
    totalLessons = lessons;
    maxCapacity = capacity;
    Id = id;
    currentStudentsCount = 0;
    enrolledStudents.clear();

    if (maxCapacity > 0)
    {
        enrolledStudents.reserve(maxCapacity);
    }
}

int Course::getCourseId() const
{
    return Id;
}

std::string Course::getCourseTitle() const
{
    return courseTitle;
}

std::string Course::getTeacherName() const
{
    return teacherName;
}

int Course::getTotalLessons() const
{
    return totalLessons;
}

int Course::getMaxCapacity() const
{
    return maxCapacity;
}

int Course::getEnrolledCount() const
{
    return currentStudentsCount;
}

void Course::setTeacherName(const std::string& teacher)
{
    teacherName = teacher;
}

void Course::setTotalLessons(int lessons)
{
    if (lessons > 0) {
        totalLessons = lessons;
    }
}

bool Course::enrollStudent(int id, const std::string& name)
{
    if (currentStudentsCount >= maxCapacity)
    {
        std::cout << "\x1b[31mFailed to enroll student " << name
            << ": course limit reached (limit: " << maxCapacity << ").\x1b[0m" << std::endl;
        return false;
    }

    for (int i = 0; i < currentStudentsCount; i++)
    {
        if (enrolledStudents[i].getStudentId() == id)
        {
            std::cout << "\x1b[33mStudent with ID " << id
                << " is already enrolled in this course.\x1b[0m" << std::endl;
            return false;
        }
    }

    Student newStudent;
    newStudent.initStudent(id, name);
    enrolledStudents.push_back(newStudent);
    currentStudentsCount++;
    std::cout << "\x1b[32mStudent " << name << " successfully enrolled in \""
        << courseTitle << "\".\x1b[0m" << std::endl;
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
        std::cout << "\x1b[31mStudent with ID " << id
            << " was not found on this course.\x1b[0m" << std::endl;
        return false;
    }

    std::string deletedName = enrolledStudents[targetIndex].getStudentName();
    enrolledStudents.erase(enrolledStudents.begin() + targetIndex);
    currentStudentsCount--;
    std::cout << "\x1b[32mStudent " << deletedName
        << " has been removed from \"" << courseTitle << "\". Spot freed.\x1b[0m" << std::endl;
    return true;
}

void Course::recordTaskCompletion(int studentId)
{
    for (int i = 0; i < currentStudentsCount; i++)
    {
        if (enrolledStudents[i].getStudentId() == studentId)
        {
            enrolledStudents[i].completeTask();
            std::cout << "\x1b[32mCompleted task recorded for " << enrolledStudents[i].getStudentName()
                << ".\x1b[0m" << std::endl;
            return;
        }
    }
    std::cout << "\x1b[31mStudent with ID " << studentId
        << " was not found on this course.\x1b[0m" << std::endl;
}

int Course::calculateStudentProgress(int studentId) const
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

void Course::printFullCourseInfo() const
{
    std::cout << "\n\x1b[34mCourse Information:\x1b[0m" << std::endl;
    std::cout << "Title: \x1b[36m" << courseTitle << "\x1b[0m" << std::endl;
    std::cout << "Instructor: " << teacherName << std::endl;
    std::cout << "Total lessons: " << totalLessons << std::endl;
    std::cout << "Enrolled students: " << currentStudentsCount << " / " << maxCapacity << std::endl;

    if (currentStudentsCount == 0)
    {
        std::cout << "\x1b[33mNo students currently enrolled.\x1b[0m" << std::endl;
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
                << ", progress: \x1b[32m" << progress << "%\x1b[0m" << std::endl;
        }
    }
    std::cout << std::endl;
}

void CourseList::deleteNode(CourseNode* node)
{
    if (node == nullptr) return;

    if (node == head.get())
    {
        head = std::move(head->next);
        if (head != nullptr)
        {
            head->prev = nullptr;
        }
    }
    else
    {
        CourseNode* prevNode = node->prev;
        std::unique_ptr<CourseNode> nextNode = std::move(node->next);

        if (nextNode != nullptr)
        {
            nextNode->prev = prevNode;
        }

        if (prevNode != nullptr)
        {
            prevNode->next = std::move(nextNode);
        }
    }

    numberOfCourses--;
}

CourseNode* CourseList::getCoursePointerById(int targetId)
{
    CourseNode* current = head.get();
    while (current != nullptr)
    {
        if (current->data.getCourseId() == targetId)
        {
            return current;
        }
        current = current->next.get();
    }
    return nullptr;
}

void CourseList::addCourse(int id, const std::string& title, const std::string& teacher, int lessons, int capacity)
{
    auto newNode = std::make_unique<CourseNode>();
    newNode->data.initCourse(id, title, teacher, lessons, capacity);
    newNode->next = nullptr;
    newNode->prev = nullptr;

    if (head == nullptr)
    {
        head = std::move(newNode);
    }
    else
    {
        CourseNode* current = head.get();
        while (current->next != nullptr)
        {
            current = current->next.get();
        }
        newNode->prev = current;
        current->next = std::move(newNode);
    }

    numberOfCourses++;
}

bool CourseList::removeCourseById(int targetId)
{
    if (CourseNode* targetNode = getCoursePointerById(targetId))
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
        std::cout << "\x1b[33mNo courses available.\x1b[0m\n";
        return;
    }

    std::cout << "\n\x1b[34m--- Courses List (" << numberOfCourses << ") ---\x1b[0m\n";
    const CourseNode* current = head.get();
    while (current != nullptr)
    {
        std::cout << "ID: " << current->data.getCourseId()
            << " | Title: \x1b[36m" << current->data.getCourseTitle() << "\x1b[0m"
            << " | Students: " << current->data.getEnrolledCount() << "/" << current->data.getMaxCapacity()
            << std::endl;
        current = current->next.get();
    }
    std::cout << "------------------------------------\n";
}