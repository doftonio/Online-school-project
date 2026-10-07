#pragma once
#include <string>
#include <string_view>
#include <vector>
#include <memory>
#include "student.h"

struct WebinarDetails
{
    std::string_view platformUrl{};
    std::string_view scheduleTime{};
    int totalWebinars{ 0 };
};

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

protected:
    void printEnrolledStudentsList(std::string_view taskLabel) const;

public:
    Course() = default;
    Course(int id, std::string_view title, std::string_view teacher, int lessons, int capacity);
    virtual ~Course() = default;

    Course(const Course& other) = default;
    Course& operator=(const Course& other) = default;
    Course(Course&& other) noexcept = default;
    Course& operator=(Course&& other) noexcept = default;

    virtual void initCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity);

    std::string getCourseTitle() const;
    std::string getTeacherName() const;
    int getTotalLessons() const;
    int getMaxCapacity() const;
    int getEnrolledCount() const;
    int getCourseId() const;

    void setTeacherName(std::string_view teacher);
    void setTotalLessons(int lessons);

    virtual bool enrollStudent(const Student& student);
    virtual bool enrollStudent(int id, std::string_view name);
    virtual bool removeStudent(int id);
    void recordTaskCompletion(int studentId);

    virtual int calculateStudentProgress(int studentId) const;

    Course& operator+=(const Student& student);
    Course& operator-=(const Student& student);

    virtual void printFullCourseInfo() const;
};

class InteractiveCourse : public Course
{
private:
    int totalExercises{ 0 };
    int autoCheckPassingScore{ 70 };

public:
    InteractiveCourse() = default;
    InteractiveCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
        int exercises, int passingScore);

    void setTotalExercises(int exercises);
    int getTotalExercises() const;
    int getPassingScore() const;

    void submitExercise(int studentId, bool passed);

    int calculateStudentProgress(int studentId) const override;
    void printFullCourseInfo() const override;
};

class WebinarCourse : public Course
{
private:
    std::string platformUrl{};
    std::string scheduleTime{};
    int totalWebinars{ 0 };

public:
    WebinarCourse() = default;
    WebinarCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
        const WebinarDetails& details);

    std::string getPlatformUrl() const;
    std::string getScheduleTime() const;
    int getTotalWebinars() const;

    void setPlatformUrl(std::string_view url);
    void setScheduleTime(std::string_view schedule);

    void printFullCourseInfo() const override;
};

class MentoredCourse : public Course
{
private:
    std::string mentorName{};
    int maxReviewsPerStudent{ 3 };
    int totalReviewsConducted{ 0 };

public:
    MentoredCourse() = default;
    MentoredCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity,
        std::string_view mentor, int reviewsLimit);

    std::string getMentorName() const;
    int getMaxReviews() const;
    int getTotalReviewsConducted() const;

    void setMentorName(std::string_view mentor);

    void conductReview(int studentId);

    bool enrollStudent(const Student& student) override;
    bool enrollStudent(int id, std::string_view name) override;

    void printFullCourseInfo() const override;
};

struct CourseNode
{
    std::unique_ptr<Course> data{ nullptr };
    std::unique_ptr<CourseNode> next{ nullptr };
    CourseNode* prev{ nullptr };
};

class CourseList
{
private:
    std::unique_ptr<CourseNode> head{ nullptr };
    int numberOfCourses{ 0 };

public:
    CourseList() = default;
    ~CourseList() = default;
    CourseList(const CourseList&) = delete;
    CourseList& operator=(const CourseList&) = delete;
    CourseList(CourseList&&) noexcept = default;
    CourseList& operator=(CourseList&&) noexcept = default;

    void addCourse(std::unique_ptr<Course> newCourse);
    void addCourse(int id, std::string_view title, std::string_view teacher, int lessons, int capacity);
    void deleteNode(CourseNode* node);
    bool removeCourseById(int targetId);

    void displayListOfCourses() const;
    CourseNode* getCoursePointerById(int targetId);
    const CourseNode* getCoursePointerById(int targetId) const;
};