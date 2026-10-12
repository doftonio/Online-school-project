#include "../Header files/menu.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/exceptions.h"
#include <iostream>
#include <string>
#include <limits>

namespace {
    int readInt(std::string_view prompt) {
        int value = 0;
        while (true) {
            std::cout << prompt;
            if (std::cin >> value) {
                return value;
            }
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error: please enter an integer.\n";
        }
    }

    std::string readString(std::string_view prompt) {
        std::string str{};
        std::cout << prompt;
        std::cin >> str;
        return str;
    }

    void handleEnrollStudent(Faculty& faculty, const StudyGroup* group) {
        int id = readInt("Enter student ID: ");
        std::string first = readString("Enter first name: ");
        std::string last = readString("Enter last name: ");
        std::string middle = readString("Enter middle name ('-' if none): ");
        if (middle == "-") middle.clear();

        try {
            faculty.enrollStudentInGroup(id, first, last, middle, group->getNumber());
            std::cout << "Student successfully enrolled!\n";
        }
        catch (const AppException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    void handleExpelStudent(Faculty& faculty) {
        int id = readInt("Enter student ID to expel: ");
        try {
            faculty.expelStudent(id);
            std::cout << "Student successfully expelled.\n";
        }
        catch (const AppException& e) {
            std::cout << "Error: " << e.what() << "\n";
        }
    }

    void handleInspectStudent(const StudyGroup* group) {
        int id = readInt("Enter student ID: ");
        if (const Student* s = group->findStudent(id)) {
            std::cout << *s << "\n";
            inspectStudentInternals(*s);
        }
        else {
            std::cout << "Student with ID " << id << " was not found in the group.\n";
        }
    }

    void groupSubMenu(Faculty& faculty, const StudyGroup* group) {
        if (!group) return;

        int choice = -1;
        while (choice != 0) {
            std::cout << "\n--- GROUP MENU: " << group->getNumber() << " ---\n";
            std::cout << "1. View group members\n";
            std::cout << "2. Enroll new student\n";
            std::cout << "3. Expel student by ID\n";
            std::cout << "4. Find student and inspect (friend function)\n";
            std::cout << "0. Back to main menu\n";

            choice = readInt("Select an option: ");
            switch (choice) {
            case 1:
                group->printInfo();
                break;
            case 2:
                handleEnrollStudent(faculty, group);
                break;
            case 3:
                handleExpelStudent(faculty);
                break;
            case 4:
                handleInspectStudent(group);
                break;
            case 0:
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }
    }

    void handleCourseTeachers(const Faculty& faculty, Course* course, int choice) {
        if (choice == 2) {
            int tId = readInt("Enter faculty teacher ID: ");
            if (Teacher* t = faculty.findTeacher(tId)) {
                *course += t;
                std::cout << "Teacher " << t->getFullName() << " added to course.\n";
            }
            else {
                std::cout << "Teacher not found on the faculty.\n";
            }
        }
        else if (choice == 3) {
            int tId = readInt("Enter teacher ID to remove from course: ");
            *course -= tId;
            std::cout << "Teacher removed from course.\n";
        }
    }

    void handleAssignLecture(Course* course) {
        std::string gNum = readString("Enter group number: ");
        int lessons = readInt("Total lessons: ");
        int tId = readInt("Lecturer ID: ");
        int topics = readInt("Total topics: ");
        int hours = readInt("Academic hours: ");
        course->addActivityForGroup(gNum, std::make_unique<LectureActivity>(lessons, tId, topics, hours));
        std::cout << "Lectures successfully assigned!\n";
    }

    void handleAssignLab(Course* course) {
        std::string gNum = readString("Enter group number: ");
        int lessons = readInt("Total lessons: ");
        int tId = readInt("Lab instructor ID: ");
        int count = readInt("Total laboratory works: ");
        int minScore = readInt("Minimum passing score: ");
        course->addActivityForGroup(gNum, std::make_unique<LabActivity>(lessons, tId, count, minScore));
        std::cout << "Labs successfully assigned!\n";
    }

    void handleAssignPractice(Course* course) {
        std::string gNum = readString("Enter group number: ");
        int lessons = readInt("Total lessons: ");
        int tId = readInt("Practice instructor ID: ");
        int tests = readInt("Total tests: ");
        int tasks = readInt("Total practical tasks: ");
        int calcs = readInt("Total calculation works: ");
        course->addActivityForGroup(gNum, std::make_unique<PracticeActivity>(lessons, tId, tests, tasks, calcs));
        std::cout << "Practice successfully assigned!\n";
    }

    void handleAddLabGrade(Course* course) {
        std::string gNum = readString("Enter group number: ");
        int sId = readInt("Student ID: ");
        int val = readInt("Grade (1-10): ");
        int num = readInt("Lab work number: ");
        int d = readInt("Day: ");
        int m = readInt("Month: ");
        int y = readInt("Year: ");

        if (auto* act = dynamic_cast<LabActivity*>(course->findActivity(gNum, ActivityType::Lab))) {
            act->addGradeForStudent(sId, LabGrade(val, Date(d, m, y), num));
            std::cout << "Lab grade added.\n";
        }
        else {
            std::cout << "Lab activity not found for group " << gNum << ".\n";
        }
    }

    void handleAddPracticeGrade(Course* course) {
        std::string gNum = readString("Enter group number: ");
        int sId = readInt("Student ID: ");
        int val = readInt("Grade (1-10): ");
        int num = readInt("Work number: ");
        std::string type = readString("Work type (Test/Task/Calculation): ");
        int d = readInt("Day: ");
        int m = readInt("Month: ");
        int y = readInt("Year: ");

        if (auto* act = dynamic_cast<PracticeActivity*>(course->findActivity(gNum, ActivityType::Practice))) {
            act->addGradeForStudent(sId, PracticeGrade(val, Date(d, m, y), num, type));
            std::cout << "Practice grade added.\n";
        }
        else {
            std::cout << "Practice activity not found for group " << gNum << ".\n";
        }
    }

    void handleRemoveGrade(Course* course) {
        std::string gNum = readString("Enter group number: ");
        int sId = readInt("Student ID: ");
        int d = readInt("Day: ");
        int m = readInt("Month: ");
        int y = readInt("Year: ");
        Date targetDate(d, m, y);

        bool removed = false;
        if (auto* act = dynamic_cast<LabActivity*>(course->findActivity(gNum, ActivityType::Lab))) {
            removed = act->removeGradeForStudentByDate(sId, targetDate);
        }
        if (!removed) {
            if (auto* act = dynamic_cast<PracticeActivity*>(course->findActivity(gNum, ActivityType::Practice))) {
                removed = act->removeGradeForStudentByDate(sId, targetDate);
            }
        }

        if (removed) std::cout << "Grade for date " << targetDate << " successfully removed.\n";
        else std::cout << "Grade for the specified date was not found.\n";
    }

    void handleViewJournals(Course* course, int choice) {
        std::string gNum = readString("Enter group number: ");
        if (choice == 10) {
            if (const auto* act = dynamic_cast<const LabActivity*>(course->findActivity(gNum, ActivityType::Lab))) {
                printLabJournal(std::cout, *act);
            }
            else {
                std::cout << "Lab activity not found.\n";
            }
        }
        else if (choice == 11) {
            if (const auto* act = dynamic_cast<const PracticeActivity*>(course->findActivity(gNum, ActivityType::Practice))) {
                printPracticeJournal(std::cout, *act);
            }
            else {
                std::cout << "Practice activity not found.\n";
            }
        }
    }

    void courseSubMenu(const Faculty& faculty, Course* course) {
        if (!course) return;

        int choice = -1;
        while (choice != 0) {
            std::cout << "\n--- COURSE MENU: " << course->getTitle() << " (ID: " << course->getId() << ") ---\n";
            std::cout << "1. Full course information\n";
            std::cout << "2. Add teacher to course\n";
            std::cout << "3. Remove teacher from course\n";
            std::cout << "4. Assign lectures to group\n";
            std::cout << "5. Assign labs to group\n";
            std::cout << "6. Assign practice to group\n";
            std::cout << "7. Submit lab grade\n";
            std::cout << "8. Submit practice grade\n";
            std::cout << "9. Remove grade by date\n";
            std::cout << "10. View laboratory journal\n";
            std::cout << "11. View practice journal\n";
            std::cout << "0. Back to main menu\n";

            choice = readInt("Select an option: ");

            try {
                if (choice == 1) course->printFullCourseInfo();
                else if (choice == 2 || choice == 3) handleCourseTeachers(faculty, course, choice);
                else if (choice == 4) handleAssignLecture(course);
                else if (choice == 5) handleAssignLab(course);
                else if (choice == 6) handleAssignPractice(course);
                else if (choice == 7) handleAddLabGrade(course);
                else if (choice == 8) handleAddPracticeGrade(course);
                else if (choice == 9) handleRemoveGrade(course);
                else if (choice == 10 || choice == 11) handleViewJournals(course, choice);
                else if (choice != 0) std::cout << "Invalid choice.\n";
            }
            catch (const AppException& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
    }

    void handleFacultyTeachersMenu(Faculty& faculty) {
        std::cout << "\n--- Faculty Teachers (" << faculty.getTeachers().size() << ") ---\n";
        for (const auto& t : faculty.getTeachers()) {
            t->printInfo();
        }
        std::cout << "1. Add new teacher to staff\n0. Back\n";
        if (int sub = readInt("Choice: "); sub == 1) {
            int id = readInt("Teacher ID: ");
            std::string first = readString("First name: ");
            std::string last = readString("Last name: ");
            std::string middle = readString("Middle name ('-' if none): ");
            if (middle == "-") middle.clear();
            std::string dept = readString("Department: ");
            faculty.createTeacher(id, first, last, middle, dept);
            std::cout << "Teacher added to staff.\n";
        }
    }

    void handleFacultyGroupsMenu(Faculty& faculty) {
        std::cout << "\n--- Study Groups (" << faculty.getGroups().size() << ") ---\n";
        for (const auto& g : faculty.getGroups()) {
            std::cout << "Group #" << g->getNumber() << " (Year " << g->getCourseYear()
                << ", students: " << g->getStudents().size() << "/" << g->getMaxCapacity() << ")\n";
        }
        std::cout << "1. Create new group\n";
        std::cout << "2. Select group by number\n";
        std::cout << "0. Back\n";
        if (int sub = readInt("Choice: "); sub == 1) {
            std::string num = readString("Group number: ");
            int year = readInt("Year (1-5): ");
            int cap = readInt("Capacity: ");
            try {
                faculty.createGroup(num, year, cap);
                std::cout << "Group created.\n";
            }
            catch (const AppException& e) {
                std::cout << "Error: " << e.what() << "\n";
            }
        }
        else if (sub == 2) {
            std::string num = readString("Enter group number: ");
            if (const StudyGroup* g = faculty.findGroup(num)) {
                groupSubMenu(faculty, g);
            }
            else {
                std::cout << "Group not found.\n";
            }
        }
    }

    void handleFacultyCoursesMenu(Faculty& faculty) {
        std::cout << "\n--- Courses (" << faculty.getCourses().size() << ") ---\n";
        for (const auto& c : faculty.getCourses()) {
            std::cout << "ID: " << c->getId() << " | Title: " << c->getTitle()
                << " | Teachers: " << c->getTeachers().size() << "\n";
        }
        std::cout << "1. Create new course\n";
        std::cout << "2. Select course by ID\n";
        std::cout << "0. Back\n";
        if (int sub = readInt("Choice: "); sub == 1) {
            int id = readInt("Course ID: ");
            std::string title = readString("Course title: ");
            faculty.createCourse(id, title);
            std::cout << "Course created.\n";
        }
        else if (sub == 2) {
            int id = readInt("Enter course ID: ");
            if (Course* c = faculty.findCourse(id)) {
                courseSubMenu(faculty, c);
            }
            else {
                std::cout << "Course not found.\n";
            }
        }
    }
}

void runMainMenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n============================================\n";
        std::cout << "MAIN MENU: Faculty " << faculty.getName() << "\n";
        std::cout << "============================================\n";
        std::cout << "1. Faculty teachers\n";
        std::cout << "2. Study groups\n";
        std::cout << "3. Courses (disciplines)\n";
        std::cout << "4. Faculty summary\n";
        std::cout << "0. Exit\n";

        choice = readInt("Select menu item: ");

        switch (choice) {
        case 1:
            handleFacultyTeachersMenu(faculty);
            break;
        case 2:
            handleFacultyGroupsMenu(faculty);
            break;
        case 3:
            handleFacultyCoursesMenu(faculty);
            break;
        case 4:
            std::cout << "\n[Summary for Faculty " << faculty.getName() << "]\n"
                << "Teachers on staff:  " << faculty.getTeachers().size() << "\n"
                << "Study groups:       " << faculty.getGroups().size() << "\n"
                << "Courses running:    " << faculty.getCourses().size() << "\n";
            break;
        case 0:
            std::cout << "Exiting program.\n";
            break;
        default:
            std::cout << "Invalid option. Please try again.\n";
            break;
        }
    }
}