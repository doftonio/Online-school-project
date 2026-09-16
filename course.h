#pragma once
#include <string>
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
    Student* enrolledStudents;
    //add course id and ways to set id and get it

public:

    Course();
    ~Course();

    void initCourse(int Id, std::string title, std::string teacher, int lessons, int capacity);
    std::string getCourseTitle();
    std::string getTeacherName();
    int getTotalLessons();
    int getMaxCapacity();
    int getEnrolledCount();
    int getCourseId();

    void setTeacherName(std::string teacher);
    void setTotalLessons(int lessons);

    bool enrollStudent(int id, std::string name);
    bool removeStudent(int id);
    void recordTaskCompletion(int studentId);
    int calculateStudentProgress(int studentId);

    void printFullCourseInfo();
};


struct CourseNode
{
    Course data;
    CourseNode* next{};
    CourseNode* prev{};
};

class CourseList
{
    CourseNode* head;
    int numberOfCourses;

public:
    void addCourse(int id, std::string title, std::string teacher, int lessons, int capacity);
    void deleteNode(CourseNode* node);
    bool removeCourseById(int);

    CourseList();
    ~CourseList();

    void displayListOfCourses();
    CourseNode* getCoursePointerById(int);
};