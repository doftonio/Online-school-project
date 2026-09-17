#include "../Header files/course.h"
#include <iostream>

void Course::initCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity)
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

void Course::setTeacherName(std::string_view teacher)
{
    teacherName = teacher;
}

void Course::setTotalLessons(int lessons)
{
    if (lessons > 0) {
        totalLessons = lessons;
    }
}

bool Course::enrollStudent(int id, std::string_view name)
{
    if (currentStudentsCount >= maxCapacity)
    {
        std::cout << "Failed to enroll student " << name
            << ": course limit reached (limit: " << maxCapacity << ").\n";
        return false;
    }

    for (int i = 0; i < currentStudentsCount; i++)
    {
        if (enrolledStudents[i].getStudentId() == id)
        {
            std::cout << "Student with ID " << id
                << " is already enrolled in this course.\n";
            return false;
        }
    }

    Student newStudent;
    newStudent.initStudent(id, name);
    enrolledStudents.push_back(newStudent);
    currentStudentsCount++;

    std::cout << "Student " << name << " successfully enrolled in \""
        << courseTitle << "\".\n";
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
        std::cout << "Student with ID " << id << " was not found on this course.\n";
        return false;
    }

    std::string deletedName = enrolledStudents[targetIndex].getStudentName();
    enrolledStudents.erase(enrolledStudents.begin() + targetIndex);
    currentStudentsCount--;

    std::cout << "Student " << deletedName << " has been removed from \""
        << courseTitle << "\". Spot freed.\n";
    return true;
}

void Course::recordTaskCompletion(int studentId)
{
    for (int i = 0; i < currentStudentsCount; i++)
    {
        if (enrolledStudents[i].getStudentId() == studentId)
        {
            enrolledStudents[i].completeTask();
            std::cout << "Completed task recorded for " << enrolledStudents[i].getStudentName() << ".\n";
            return;
        }
    }

    std::cout << "Student with ID " << studentId << " was not found on this course.\n";
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
    std::cout << "\nCourse Information:\n";
    std::cout << "Title: " << courseTitle << "\n";
    std::cout << "Instructor: " << teacherName << "\n";
    std::cout << "Total lessons: " << totalLessons << "\n";
    std::cout << "Enrolled students: " << currentStudentsCount << " / " << maxCapacity << "\n";

    if (currentStudentsCount == 0)
    {
        std::cout << "No students currently enrolled.\n";
    }
    else {
        std::cout << "Student list:\n";
        for (int i = 0; i < currentStudentsCount; i++)
        {
            int progress = calculateStudentProgress(enrolledStudents[i].getStudentId());
            std::cout << "  " << i + 1 << ". "
                << enrolledStudents[i].getStudentName()
                << " (ID: " << enrolledStudents[i].getStudentId() << ")"
                << " - tasks completed: " << enrolledStudents[i].getCompletedTasks()
                << ", progress: " << progress << "%\n";
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

const CourseNode* CourseList::getCoursePointerById(int targetId) const
{
    const CourseNode* current = head.get();
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

void CourseList::addCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity)
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

void CourseList::displayListOfCourses() const
{
    if (head == nullptr)
    {
        std::cout << "No courses available.\n";
        return;
    }

    std::cout << "\n--- Courses List (" << numberOfCourses << ") ---\n";
    const CourseNode* current = head.get();
    while (current != nullptr)
    {
        std::cout << "ID: " << current->data.getCourseId()
            << " | Title: " << current->data.getCourseTitle()
            << " | Students: " << current->data.getEnrolledCount() << "/"
            << current->data.getMaxCapacity() << "\n";
        current = current->next.get();
    }
    std::cout << "------------------------------------\n";
}