#include "../Header files/course.h"
#include <iostream>

Course::Course(int id, std::string_view title, std::string_view teacher, int lessons, int capacity)
    : courseTitle(title), teacherName(teacher), totalLessons(lessons), maxCapacity(capacity),
    currentStudentsCount(0), Id(id)
{
    if (maxCapacity > 0)
    {
        enrolledStudents.reserve(maxCapacity);
    }
}

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

bool Course::enrollStudent(const Student& student)
{
    if (currentStudentsCount >= maxCapacity)
    {
        std::cout << "Failed to enroll student " << student.getStudentName()
            << ": course limit reached (limit: " << maxCapacity << ").\n";
        return false;
    }

    for (int i = 0; i < currentStudentsCount; i++)
    {
        if (enrolledStudents[i] == student)
        {
            std::cout << "Student with ID " << student.getStudentId()
                << " is already enrolled in this course.\n";
            return false;
        }
    }

    enrolledStudents.push_back(student);
    currentStudentsCount++;

    std::cout << "Student " << student.getStudentName() << " successfully enrolled in \""
        << courseTitle << "\".\n";
    return true;
}

bool Course::enrollStudent(int id, std::string_view name)
{
    Student newStudent;
    newStudent.initStudent(id, name);
    return enrollStudent(newStudent);
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

Course& Course::operator+=(const Student& student)
{
    enrollStudent(student);
    return *this;
}

Course& Course::operator-=(const Student& student)
{
    removeStudent(student.getStudentId());
    return *this;
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

InteractiveCourse::InteractiveCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
    int exercises, int passingScore)
    : Course(id, title, teacher, lessons, capacity),
    totalExercises(exercises), autoCheckPassingScore(passingScore)
{
}

void InteractiveCourse::setTotalExercises(int exercises)
{
    if (exercises >= 0) totalExercises = exercises;
}

int InteractiveCourse::getTotalExercises() const
{
    return totalExercises;
}

int InteractiveCourse::getPassingScore() const
{
    return autoCheckPassingScore;
}

void InteractiveCourse::submitExercise(int studentId, bool passed)
{
    if (passed)
    {
        std::cout << "Exercise submitted and passed for student ID " << studentId << ".\n";
        recordTaskCompletion(studentId);
    }
    else
    {
        std::cout << "Exercise failed for student ID " << studentId << ".\n";
    }
}

int InteractiveCourse::calculateStudentProgress(int studentId) const
{
    int baseProgress = Course::calculateStudentProgress(studentId);
    if (baseProgress < 0) return -1;
    return baseProgress;
}

void InteractiveCourse::printFullCourseInfo() const
{
    std::cout << "\nCourse Information (Interactive Course):\n";
    std::cout << "Title: " << courseTitle << "\n";
    std::cout << "Instructor: " << teacherName << "\n";
    std::cout << "Theory lessons: " << totalLessons << "\n";
    std::cout << "Practice exercises: " << totalExercises << "\n";
    std::cout << "Passing score threshold: " << autoCheckPassingScore << "%\n";
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
                << " - auto-tests passed: " << enrolledStudents[i].getCompletedTasks()
                << ", progress: " << progress << "%\n";
        }
    }
    std::cout << std::endl;
}

WebinarCourse::WebinarCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
    std::string_view url, std::string_view schedule, int webinars)
    : Course(id, title, teacher, lessons, capacity),
    platformUrl(url), scheduleTime(schedule), totalWebinars(webinars)
{
}

std::string WebinarCourse::getPlatformUrl() const
{
    return platformUrl;
}

std::string WebinarCourse::getScheduleTime() const
{
    return scheduleTime;
}

int WebinarCourse::getTotalWebinars() const
{
    return totalWebinars;
}

void WebinarCourse::setPlatformUrl(std::string_view url)
{
    platformUrl = url;
}

void WebinarCourse::setScheduleTime(std::string_view schedule)
{
    scheduleTime = schedule;
}

void WebinarCourse::printFullCourseInfo() const
{
    std::cout << "\nCourse Information (Webinar Course):\n";
    std::cout << "Title: " << courseTitle << "\n";
    std::cout << "Instructor: " << teacherName << "\n";
    std::cout << "Platform URL: " << platformUrl << "\n";
    std::cout << "Schedule: " << scheduleTime << "\n";
    std::cout << "Total webinars: " << totalWebinars << "\n";
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
                << " - attended sessions: " << enrolledStudents[i].getCompletedTasks()
                << ", progress: " << progress << "%\n";
        }
    }
    std::cout << std::endl;
}

MentoredCourse::MentoredCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
    std::string_view mentor, int reviewsLimit)
    : Course(id, title, teacher, lessons, capacity),
    mentorName(mentor), maxReviewsPerStudent(reviewsLimit), totalReviewsConducted(0)
{
}

std::string MentoredCourse::getMentorName() const
{
    return mentorName;
}

int MentoredCourse::getMaxReviews() const
{
    return maxReviewsPerStudent;
}

int MentoredCourse::getTotalReviewsConducted() const
{
    return totalReviewsConducted;
}

void MentoredCourse::setMentorName(std::string_view mentor)
{
    mentorName = mentor;
}

void MentoredCourse::conductReview(int studentId)
{
    for (int i = 0; i < currentStudentsCount; i++)
    {
        if (enrolledStudents[i].getStudentId() == studentId)
        {
            totalReviewsConducted++;
            enrolledStudents[i].completeTask();
            std::cout << "Mentor " << mentorName << " approved project for "
                << enrolledStudents[i].getStudentName() << ".\n";
            return;
        }
    }
    std::cout << "Student with ID " << studentId << " not found for review.\n";
}

bool MentoredCourse::enrollStudent(const Student& student)
{
    constexpr int MAX_MENTOR_LOAD = 5;
    if (currentStudentsCount >= MAX_MENTOR_LOAD)
    {
        std::cout << "Cannot enroll in Mentored Course: mentor workload limit ("
            << MAX_MENTOR_LOAD << " students) reached for " << mentorName << ".\n";
        return false;
    }
    return Course::enrollStudent(student);
}

bool MentoredCourse::enrollStudent(int id, std::string_view name)
{
    Student newStudent;
    newStudent.initStudent(id, name);
    return enrollStudent(newStudent);
}

void MentoredCourse::printFullCourseInfo() const
{
    std::cout << "\nCourse Information (Mentored Course):\n";
    std::cout << "Title: " << courseTitle << "\n";
    std::cout << "Instructor: " << teacherName << "\n";
    std::cout << "Mentor: " << mentorName << "\n";
    std::cout << "Reviews quota: " << maxReviewsPerStudent << "\n";
    std::cout << "Reviews conducted: " << totalReviewsConducted << "\n";
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
                << " - reviews passed: " << enrolledStudents[i].getCompletedTasks()
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
        if (current->data && current->data->getCourseId() == targetId)
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
        if (current->data && current->data->getCourseId() == targetId)
        {
            return current;
        }
        current = current->next.get();
    }
    return nullptr;
}

void CourseList::addCourse(std::unique_ptr<Course> newCourse)
{
    if (!newCourse) return;

    auto newNode = std::make_unique<CourseNode>();
    newNode->data = std::move(newCourse);
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

void CourseList::addCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity)
{
    addCourse(std::make_unique<Course>(id, title, teacher, lessons, capacity));
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

    std::cout << "\nCourses List (" << numberOfCourses << "):\n";
    const CourseNode* current = head.get();
    while (current != nullptr)
    {
        if (current->data)
        {
            std::cout << "ID: " << current->data->getCourseId()
                << " | Title: " << current->data->getCourseTitle()
                << " | Students: " << current->data->getEnrolledCount() << "/"
                << current->data->getMaxCapacity() << "\n";
        }
        current = current->next.get();
    }
}