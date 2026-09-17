#pragma once
#include <string>
#include <memory>

class Student;

class Course
{
private:
    std::string courseTitle;
    std::string teacherName;
    int totalLessons;
    int maxCapacity;
    int currentStudentsCount;
    int Id;
    std::unique_ptr<Student[]> enrolledStudents;

public:
    Course();
    ~Course() = default;
    Course(const Course& other);
    Course& operator=(const Course& other);
    Course(Course&& other) noexcept = default;
    Course& operator=(Course&& other) noexcept = default;

    void initCourse(int Id, const std::string& title, const std::string& teacher, int lessons, int capacity);
    std::string getCourseTitle() const;
    std::string getTeacherName() const;
    int getTotalLessons() const;
    int getMaxCapacity() const;
    int getEnrolledCount() const;
    int getCourseId() const;

    void setTeacherName(const std::string& teacher);
    void setTotalLessons(int lessons);

    bool enrollStudent(int id, const std::string& name);
    bool removeStudent(int id);
    void recordTaskCompletion(int studentId);
    int calculateStudentProgress(int studentId);

    void printFullCourseInfo();
};

struct CourseNode
{
    Course data;
    std::unique_ptr<CourseNode> next{};
    CourseNode* prev{};
};

class CourseList
{
    std::unique_ptr<CourseNode> head;
    int numberOfCourses;

public:
    CourseList();
    ~CourseList() = default;
    CourseList(const CourseList&) = delete;
    CourseList& operator=(const CourseList&) = delete;
    CourseList(CourseList&&) noexcept = default;
    CourseList& operator=(CourseList&&) noexcept = default;

    void addCourse(int id, const std::string& title, const std::string& teacher, int lessons, int capacity);
    void deleteNode(CourseNode* node);
    bool removeCourseById(int targetId);

    void displayListOfCourses();
    CourseNode* getCoursePointerById(int targetId);
};