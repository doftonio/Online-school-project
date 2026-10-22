#include "../Header files/menu.h"
#include "../Header files/faculty.h"
#include "../Header files/course.h"
#include "../Header files/teacher.h"
#include "../Header files/student.h"
#include "../Header files/studyGroup.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/lectureActivity.h"
#include <iostream>
#include <string>
#include <memory>
#include <limits>

static int readInt(const std::string& prompt) {
    std::cout << prompt;
    int val = 0;
    while (!(std::cin >> val)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Please enter an integer: ";
    }
    return val;
}

static std::string readString(const std::string& prompt) {
    std::cout << prompt;
    std::string val;
    std::cin >> val;
    return val;
}

void handleAddTeacher(Faculty& faculty) {
    std::cout << "\n--- Add New Teacher ---\n";
    int id = readInt("Enter Teacher ID: ");
    std::string first = readString("Enter First Name: ");
    std::string last = readString("Enter Last Name: ");
    std::string middle = readString("Enter Middle Name: ");
    std::string dept = readString("Enter Department: ");

    faculty.createTeacher(id, first, last, middle, dept);
    std::cout << "Teacher added successfully.\n";
}

void handleCreateGroup(Faculty& faculty) {
    std::cout << "\n--- Create Study Group ---\n";
    std::string num = readString("Enter Group Number: ");
    int year = readInt("Enter Study Year: ");
    int cap = readInt("Enter Max Capacity: ");

    faculty.createGroup(num, year, cap);
    std::cout << "Group created successfully.\n";
}

void handleEnrollStudent(Faculty& faculty) {
    std::cout << "\n--- Enroll Student in Group ---\n";
    std::string groupNum = readString("Enter Target Group Number: ");
    StudyGroup* group = faculty.findGroup(groupNum);
    if (!group) {
        std::cout << "Group not found!\n";
        return;
    }

    int id = readInt("Enter Student ID: ");
    std::string first = readString("Enter First Name: ");
    std::string last = readString("Enter Last Name: ");
    std::string middle = readString("Enter Middle Name: ");

    if (faculty.enrollStudentInGroup(id, first, last, middle, group)) {
        std::cout << "Student enrolled successfully.\n";
    } else {
        std::cout << "Failed to enroll student (group might be full or invalid).\n";
    }
}

void handleExpelStudent(Faculty& faculty) {
    std::cout << "\n--- Expel Student from Faculty ---\n";
    int id = readInt("Enter Student ID to expel: ");
    Student* student = faculty.findStudent(id);
    if (!student) {
        std::cout << "Student with ID " << id << " not found.\n";
        return;
    }
    faculty.expelStudent(student);
    std::cout << "Student expelled and removed from all groups and gradebooks.\n";
}

void handleCreateCourse(Faculty& faculty) {
    std::cout << "\n--- Create New Course ---\n";
    int id = readInt("Enter Course ID: ");
    std::string title = readString("Enter Course Title: ");

    faculty.createCourse(id, title);
    std::cout << "Course created successfully.\n";
}

void handleAssignTeacherToCourse(Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Assign Teacher to Course ---\n";
    int teacherId = readInt("Enter Teacher ID: ");
    Teacher* teacher = faculty.findTeacher(teacherId);
    if (!teacher) {
        std::cout << "Teacher with ID " << teacherId << " not found.\n";
        return;
    }
    *course += teacher;
    std::cout << "Teacher assigned to course via operator+=.\n";
}

void handleRemoveTeacherFromCourse(Course* course) {
    if (!course) return;
    std::cout << "\n--- Remove Teacher from Course ---\n";
    int teacherId = readInt("Enter Teacher ID to remove: ");
    *course -= teacherId;
    std::cout << "Teacher removed from course via operator-=(int).\n";
}

void handleAddActivityToCourse(Faculty& /*faculty*/, Course* course) {
    if (!course) return;
    std::cout << "\n--- Add Activity to Course (Polymorphic) ---\n"
              << "1. Lecture Activity\n"
              << "2. Lab Activity\n"
              << "3. Practice Activity\n"
              << "Select type: ";
    int typeChoice = readInt("");
    int lessons = readInt("Enter number of lessons: ");
    int teacherId = readInt("Enter Teacher ID for this activity: ");

    if (typeChoice == 1) {
        int topics = readInt("Enter topics count: ");
        int hours = readInt("Enter lecture hours: ");
        course->addActivity(std::make_unique<LectureActivity>(lessons, teacherId, topics, hours));
        std::cout << "Lecture activity added polymorphically.\n";
    } else if (typeChoice == 2) {
        int labs = readInt("Enter total labs count: ");
        int minScore = readInt("Enter minimum passing score: ");
        course->addActivity(std::make_unique<LabActivity>(lessons, teacherId, labs, minScore));
        std::cout << "Lab activity added polymorphically.\n";
    } else if (typeChoice == 3) {
        int tests = readInt("Enter tests count: ");
        int tasks = readInt("Enter tasks count: ");
        int calcs = readInt("Enter calculations count: ");
        course->addActivity(std::make_unique<PracticeActivity>(lessons, teacherId, tests, tasks, calcs));
        std::cout << "Practice activity added polymorphically.\n";
    } else {
        std::cout << "Invalid activity type choice.\n";
    }
}

void handleAddGradeToCourse(Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Add Grade for Student ---\n";
    int studentId = readInt("Enter Student ID: ");
    Student* student = faculty.findStudent(studentId);
    if (!student) {
        std::cout << "Student not found.\n";
        return;
    }

    std::cout << "Choose activity: 1. Lab, 2. Practice: ";
    int actChoice = readInt("");
    ActivityType actType = (actChoice == 1) ? ActivityType::Lab : ActivityType::Practice;
    CourseActivity* act = course->findActivity(actType);
    if (!act) {
        std::cout << "Activity not found in this course.\n";
        return;
    }

    int score = readInt("Enter grade value (1-10): ");
    int day = readInt("Enter day: ");
    int month = readInt("Enter month: ");
    int year = readInt("Enter year: ");
    int workNum = readInt("Enter work number: ");

    course->getGradeBook().addGrade(student, act, Grade(score, Date(day, month, year), workNum));
    student->completeTask();
    std::cout << "Grade added and student completed task counter updated.\n";
}

void handleRemoveGradeFromCourse(Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Remove Grade ---\n";
    int studentId = readInt("Enter Student ID: ");
    const Student* student = faculty.findStudent(studentId);
    if (!student) {
        std::cout << "Student not found.\n";
        return;
    }

    int day = readInt("Enter date day: ");
    int month = readInt("Enter date month: ");
    int year = readInt("Enter date year: ");

    CourseActivity* labAct = course->findActivity(ActivityType::Lab);
    bool removed = course->getGradeBook().removeGradeByDate(student, labAct, Date(day, month, year));
    if (removed) {
        std::cout << "Grade removed successfully.\n";
    } else {
        std::cout << "Grade not found on that date.\n";
    }
}

void showCourseDetailsSubmenu(Faculty& faculty, Course* course) {
    if (!course) return;
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Course: " << course->getTitle() << " (ID: " << course->getId() << ") ===\n"
                  << "1. Print full course info & activities (Polymorphic)\n"
                  << "2. Assign teacher to course (*course += teacher)\n"
                  << "3. Remove teacher from course (*course -= id)\n"
                  << "4. Add activity to course (Polymorphic)\n"
                  << "5. Add grade for student\n"
                  << "6. Remove grade by date\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) course->printFullCourseInfo();
        else if (choice == 2) handleAssignTeacherToCourse(faculty, course);
        else if (choice == 3) handleRemoveTeacherFromCourse(course);
        else if (choice == 4) handleAddActivityToCourse(faculty, course);
        else if (choice == 5) handleAddGradeToCourse(faculty, course);
        else if (choice == 6) handleRemoveGradeFromCourse(faculty, course);
    }
}

void showTeachersSubmenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- Faculty Teachers (" << faculty.getTeachers().size() << ") ---\n";
        for (const std::unique_ptr<Teacher>& t : faculty.getTeachers()) {
            if (t) t->printInfo();
        }
        std::cout << "1. Add new teacher\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) handleAddTeacher(faculty);
    }
}

void showGroupsSubmenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- Faculty Groups (" << faculty.getGroups().size() << ") ---\n";
        for (const std::unique_ptr<StudyGroup>& g : faculty.getGroups()) {
            if (g) g->printInfo();
        }
        std::cout << "1. Create new group\n"
                  << "2. Enroll student in group\n"
                  << "3. Expel student from faculty\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) handleCreateGroup(faculty);
        else if (choice == 2) handleEnrollStudent(faculty);
        else if (choice == 3) handleExpelStudent(faculty);
    }
}

void showCoursesSubmenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- Faculty Courses (" << faculty.getCourses().size() << ") ---\n";
        for (const std::unique_ptr<Course>& c : faculty.getCourses()) {
            if (c) std::cout << "ID: " << c->getId() << " | Title: " << c->getTitle() << "\n";
        }
        std::cout << "1. Create new course\n"
                  << "2. Open course management\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) {
            handleCreateCourse(faculty);
        } else if (choice == 2) {
            int cId = readInt("Enter course ID: ");
            Course* c = faculty.findCourse(cId);
            if (c) {
                showCourseDetailsSubmenu(faculty, c);
            } else {
                std::cout << "Course with ID " << cId << " not found.\n";
            }
        }
    }
}

void runMainMenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n========================================\n"
                  << "   Online School System: " << faculty.getName() << "\n"
                  << "========================================\n"
                  << "1. Teachers Management\n"
                  << "2. Study Groups & Students Management\n"
                  << "3. Courses & Activities Management\n"
                  << "0. Exit\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) showTeachersSubmenu(faculty);
        else if (choice == 2) showGroupsSubmenu(faculty);
        else if (choice == 3) showCoursesSubmenu(faculty);
    }
}
