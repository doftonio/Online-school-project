#include <string>
class Student;

class Course {
private:
    std::string courseTitle;
    std::string teacherName;
    int totalLessons;
    int maxCapacity;
    int currentStudentsCount;
    Student* enrolledStudents;

public:
    Course();
    ~Course();

    void initCourse(std::string title, std::string teacher, int lessons, int capacity);
    std::string getCourseTitle();
    std::string getTeacherName();
    int getTotalLessons();
    int getMaxCapacity();
    int getEnrolledCount();

    void setTeacherName(std::string teacher);
    void setTotalLessons(int lessons);

    bool enrollStudent(int id, std::string name);
    bool removeStudent(int id);
    void recordTaskCompletion(int studentId);
    int calculateStudentProgress(int studentId);

    void printFullCourseInfo();
};