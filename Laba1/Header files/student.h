#include <string>
class Student {
private:
    int studentId;
    std::string studentName;
    int completedTasks;

public:
    Student();

    void initStudent(int id, std::string name);
    int getStudentId();
    std::string getStudentName();
    int getCompletedTasks();

    void setStudentName(std::string name);
    void completeTask();
    void resetTasks();

    void printInfo();
};
