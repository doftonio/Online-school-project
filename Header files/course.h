#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include "student.h"

class Course
{
private:
    std::string courseTitle{};
    std::string teacherName{};
    int totalLessons{ 0 };
    int maxCapacity{ 0 };
    int currentStudentsCount{ 0 };
    int Id{ 0 };
    std::vector<Student> enrolledStudents{};

public:
    Course() = default;
    ~Course() = default;
    Course(const Course& other) = default;
    Course& operator=(const Course& other) = default;
    Course(Course&& other) noexcept = default;
    Course& operator=(Course&& other) noexcept = default;

    void initCourse(int Id, std::string_view title, std::string_view teacher, int lessons, int capacity);
    std::string getCourseTitle() const;
    std::string getTeacherName() const;
    int getTotalLessons() const;
    int getMaxCapacity() const;
    int getEnrolledCount() const;
    int getCourseId() const;

    void setTeacherName(std::string_view teacher);
    void setTotalLessons(int lessons);

    bool enrollStudent(int id, std::string_view name);
    bool removeStudent(int id);
    void recordTaskCompletion(int studentId);
    int calculateStudentProgress(int studentId) const;

    void printFullCourseInfo() const;
};

struct CourseNode
{
    Course data{};
    std::unique_ptr<CourseNode> next{ nullptr };
    CourseNode* prev{ nullptr };
};

class CourseList
{
    std::unique_ptr<CourseNode> head{ nullptr };
    int numberOfCourses{ 0 };

public:
    CourseList() = default;
    ~CourseList() = default;
    CourseList(const CourseList&) = delete;
    CourseList& operator=(const CourseList&) = delete;
    CourseList(CourseList&&) noexcept = default;
    CourseList& operator=(CourseList&&) noexcept = default;

    void addCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity);
    void deleteNode(CourseNode* node);
    bool removeCourseById(int targetId);

    void displayListOfCourses() const;
    CourseNode* getCoursePointerById(int targetId);
    const CourseNode* getCoursePointerById(int targetId) const;
};