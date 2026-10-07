#include "../Header files/header.h"

void populateInitialData(CourseList& courseList)
{
    courseList.addCourse(std::make_unique<Course>(
        1, "C++ Programming", "Alex Sidorov", 10, 3));

    courseList.addCourse(std::make_unique<InteractiveCourse>(
        2, "Web Development Frontend", "Elena Kuznetsova", 8, 5, 25, 75));

    WebinarDetails webDetails{ "https://meet.google.com/xyz-abc", "Tue/Fri 18:30", 12 };
    courseList.addCourse(std::make_unique<WebinarCourse>(
        3, "DevOps & Cloud", "Maxim Ivanov", 12, 10, webDetails));

    courseList.addCourse(std::make_unique<MentoredCourse>(
        4, "Highload Backend Architecture", "Dmitry Petrov", 15, 2, "Ivan Mentor", 5));

    if (CourseNode* cppNode = courseList.getCoursePointerById(1))
    {
        cppNode->data->enrollStudent(5583001, "John Smith");
        cppNode->data->enrollStudent(5583002, "Anna Smirnova");
        cppNode->data->recordTaskCompletion(5583001);
        cppNode->data->recordTaskCompletion(5583001);
    }

    if (CourseNode* webNode = courseList.getCoursePointerById(2))
    {
        webNode->data->enrollStudent(5583002, "Anna Smirnova");
        webNode->data->enrollStudent(5583003, "Paul Kovalev");
        webNode->data->recordTaskCompletion(5583003);
    }
}

void verifyBasicOperations()
{
    Student s1(5583001, "John Smith", 6);
    Student s2(5583001, "John Smith (Duplicate ID)", 2);
    Student s3(5583002, "Anna Smirnova", 8);

    std::cout << s1 << "\n\n";
    std::cout << s2 << "\n\n";
    std::cout << s3 << "\n\n";

    std::cout << "s1 == s2: " << (s1 == s2) << "\n";
    std::cout << "s1 == s3: " << (s1 == s3) << "\n";
    std::cout << "s1 != s3: " << (s1 != s3) << "\n";

    std::cout << "s1 > s3 : " << (s1 > s3) << "\n";
    std::cout << "s1 < s3 : " << (s1 < s3) << "\n";
    std::cout << "s1 >= s3: " << (s1 >= s3) << "\n";
    std::cout << "s1 <= s3: " << (s1 <= s3) << "\n";

    inspectStudentInternals(s1);

    Course testCourse;
    testCourse.initCourse(10, "Software Engineering", "Dr. Miller", 12, 2);

    testCourse += s1;
    testCourse += s3;

    Student s4(5583004, "David Brown", 3);
    testCourse += s4;

    testCourse.printFullCourseInfo();

    testCourse -= s1;
    testCourse += s4;

    testCourse.printFullCourseInfo();
}

void demonstrateInheritance()
{
    Student testStudent1(6001, "Alice Cooper", 2);
    Student testStudent2(6002, "Bob Dylan", 1);

    // Пример работы InteractiveCourse: унаследованные и специализированные методы
    InteractiveCourse ic(101, "Python Algorithms", "G. Rossum", 8, 3, 20, 80);
    ic.enrollStudent(testStudent1);
    ic.submitExercise(6001, true);
    ic.submitExercise(6001, false);
    ic.printFullCourseInfo();

    // Пример работы WebinarCourse: унаследованные методы и расписание
    WebinarDetails semDetails{ "https://zoom.us/j/12345678", "Wed 19:00", 6 };
    WebinarCourse wc(102, "Machine Learning Seminars", "Andrew Ng", 6, 20, semDetails);
    wc.enrollStudent(testStudent2);
    wc.recordTaskCompletion(6002);
    wc.printFullCourseInfo();

    // Пример работы MentoredCourse: персональные ревью и лимит ментора
    MentoredCourse mc(103, "C++ Senior Mentorship", "B. Stroustrup", 14, 2, "Senior Oleg", 4);
    mc.enrollStudent(testStudent1);
    mc.conductReview(6001);
    mc.printFullCourseInfo();
}

int main()
{
    verifyBasicOperations();
    demonstrateInheritance();

    CourseList courseList;
    populateInitialData(courseList);

    mainMenu(courseList);

    return 0;
}