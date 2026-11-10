#include "../Header files/menu.h"
#include "../Header files/faculty.h"
#include "../Header files/course.h"
#include "../Header files/teacher.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/collection.h"
#include "../Exceptions/exceptions.h"
#include <iostream>
#include <string>
#include <memory>
#include <limits>
#include <vector>

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

static std::string readLine(const std::string& prompt) {
    std::cout << prompt;
    std::string val;
    std::cin >> std::ws;
    std::getline(std::cin, val);
    return val;
}

void handleAddTeacher(Faculty& faculty) {
    std::cout << "\n--- Add New Teacher (via operator>>) ---\n";
    try {
        Teacher tempTeacher;
        std::cin >> tempTeacher;

        const Teacher* created = faculty.createTeacher(
            tempTeacher.getId(),
            tempTeacher.getFirstName(),
            tempTeacher.getLastName(),
            tempTeacher.getMiddleName(),
            tempTeacher.getDepartment()
        );

        if (created) {
            std::cout << "Teacher added successfully: " << *created << "\n";
        }
    } catch (const DuplicateEntityException& ex) {
        std::cout << "[Duplicate Error] " << ex.what() << "\n";
    } catch (const InvalidInputDataException& ex) {
        std::cout << "[Validation Error] " << ex.what() << "\n";
    } catch (const AppException& ex) {
        std::cout << "[System Error] " << ex.what() << "\n";
    }
}

void handleFindTeacherByDepartment(const Faculty& faculty) {
    std::cout << "\n--- Find Teachers by Department (Member Method findIndex) ---\n";
    try {
        std::string dept = readLine("Enter department name: ");
        if (dept.empty()) {
            throw InvalidInputDataException("Department query cannot be empty.");
        }

        const auto& teachers = faculty.getTeachers();
        const auto indices = teachers.findIndex([&dept](const std::unique_ptr<Teacher>& t) {
            return t && t->getDepartment() == dept;
        });

        if (indices.empty()) {
            std::cout << "No teachers found for department \"" << dept << "\".\n";
            return;
        }

        std::cout << "Found " << indices.size() << " teacher(s) in department \"" << dept << "\":\n";
        for (std::size_t idx : indices) {
            std::cout << "  [" << idx << "] " << *(teachers.get(idx)) << "\n";
        }
    } catch (const AppException& ex) {
        std::cout << "[Search Error] " << ex.what() << "\n";
    }
}

void handleCreateCourse(Faculty& faculty) {
    std::cout << "\n--- Create New Course ---\n";
    try {
        int id = readInt("Enter Course ID: ");
        std::string title = readLine("Enter Course Title: ");

        const Course* created = faculty.createCourse(id, title);
        if (created) {
            std::cout << "Course created successfully: " << *created << "\n";
        }
    } catch (const DuplicateEntityException& ex) {
        std::cout << "[Duplicate Error] " << ex.what() << "\n";
    } catch (const InvalidInputDataException& ex) {
        std::cout << "[Validation Error] " << ex.what() << "\n";
    } catch (const AppException& ex) {
        std::cout << "[System Error] " << ex.what() << "\n";
    }
}

void handleFindCourseByTitle(const Faculty& faculty) {
    std::cout << "\n--- Find Courses by Title Keyword (Free Function findByCriterion) ---\n";
    try {
        std::string titleQuery = readLine("Enter search keyword in title: ");
        if (titleQuery.empty()) {
            throw InvalidInputDataException("Course title keyword cannot be empty.");
        }

        const auto matches = findByCriterion(faculty.getCourses(), [&titleQuery](const std::unique_ptr<Course>& c) {
            return c && c->getTitle().contains(titleQuery);
        });

        if (matches.empty()) {
            std::cout << "No courses found matching \"" << titleQuery << "\".\n";
            return;
        }

        std::cout << "Found " << matches.size() << " course(s) matching \"" << titleQuery << "\":\n";
        for (const auto* coursePtr : matches) {
            if (coursePtr && *coursePtr) {
                std::cout << "  - " << **coursePtr << "\n";
            }
        }
    } catch (const AppException& ex) {
        std::cout << "[Search Error] " << ex.what() << "\n";
    }
}

void handleAssignTeacherToCourse(const Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Assign Teacher to Course ---\n";
    try {
        int teacherId = readInt("Enter Teacher ID: ");
        Teacher* teacher = faculty.getTeacher(teacherId);
        *course += teacher;
        std::cout << "Teacher successfully assigned via operator+=\n";
    } catch (const EntityNotFoundException& ex) {
        std::cout << "[Not Found Error] " << ex.what() << "\n";
    } catch (const CapacityExceededException& ex) {
        std::cout << "[Capacity Limit Error] " << ex.what() << "\n";
    } catch (const DuplicateEntityException& ex) {
        std::cout << "[Duplicate Assignment Error] " << ex.what() << "\n";
    } catch (const InvalidInputDataException& ex) {
        std::cout << "[Validation Error] " << ex.what() << "\n";
    } catch (const AppException& ex) {
        std::cout << "[System Error] " << ex.what() << "\n";
    }
}

void handleRemoveTeacherFromCourse(Course* course) {
    if (!course) return;
    std::cout << "\n--- Remove Teacher from Course ---\n";
    try {
        int teacherId = readInt("Enter Teacher ID to remove: ");
        *course -= teacherId;
        std::cout << "Teacher removed successfully via operator-=(int).\n";
    } catch (const EntityNotFoundException& ex) {
        std::cout << "[Not Found Error] " << ex.what() << "\n";
    } catch (const InvalidInputDataException& ex) {
        std::cout << "[Validation Error] " << ex.what() << "\n";
    } catch (const AppException& ex) {
        std::cout << "[System Error] " << ex.what() << "\n";
    }
}

void handleAddActivityToCourse(const Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Add Activity to Course (Polymorphic) ---\n"
              << "1. Lecture Activity\n"
              << "2. Lab Activity\n"
              << "3. Practice Activity\n"
              << "Select type: ";
    try {
        int typeChoice = readInt("");
        int lessons = readInt("Enter number of lessons: ");
        int teacherId = readInt("Enter Teacher ID for this activity: ");
        Teacher* teacher = faculty.getTeacher(teacherId);

        if (typeChoice == 1) {
            int topics = readInt("Enter topics count: ");
            int hours = readInt("Enter lecture hours: ");
            course->addActivity(std::make_unique<LectureActivity>(lessons, teacher, topics, hours));
            std::cout << "Lecture activity added polymorphically.\n";
        } else if (typeChoice == 2) {
            int labs = readInt("Enter total labs count: ");
            int minScore = readInt("Enter minimum passing score: ");
            course->addActivity(std::make_unique<LabActivity>(lessons, teacher, labs, minScore));
            std::cout << "Lab activity added polymorphically.\n";
        } else if (typeChoice == 3) {
            int tests = readInt("Enter tests count: ");
            int tasks = readInt("Enter tasks count: ");
            int calcs = readInt("Enter calculations count: ");
            course->addActivity(std::make_unique<PracticeActivity>(lessons, teacher, tests, tasks, calcs));
            std::cout << "Practice activity added polymorphically.\n";
        } else {
            std::cout << "Invalid activity type choice.\n";
        }
    } catch (const EntityNotFoundException& ex) {
        std::cout << "[Not Found Error] " << ex.what() << "\n";
    } catch (const InvalidInputDataException& ex) {
        std::cout << "[Validation Error] " << ex.what() << "\n";
    } catch (const AppException& ex) {
        std::cout << "[System Error] " << ex.what() << "\n";
    }
}

void showCourseDetailsSubmenu(const Faculty& faculty, Course* course) {
    if (!course) return;
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Course: " << course->getTitle() << " (ID: " << course->getId() << ") ===\n"
                  << "1. Print full course info & activities (Polymorphic)\n"
                  << "2. Assign teacher to course (*course += teacher)\n"
                  << "3. Remove teacher from course (*course -= id)\n"
                  << "4. Add activity to course (Polymorphic)\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) course->printFullCourseInfo();
        else if (choice == 2) handleAssignTeacherToCourse(faculty, course);
        else if (choice == 3) handleRemoveTeacherFromCourse(course);
        else if (choice == 4) handleAddActivityToCourse(faculty, course);
    }
}

void showTeachersSubmenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- Faculty Teachers (" << faculty.getTeachers().size() << ") ---\n";
        for (const auto& t : faculty.getTeachers()) {
            if (t) t->printInfo();
        }
        std::cout << "1. Add new teacher\n"
                  << "2. Find teachers by department (Collection::findIndex)\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) handleAddTeacher(faculty);
        else if (choice == 2) handleFindTeacherByDepartment(faculty);
    }
}

void showCoursesSubmenu(Faculty& faculty) {
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n--- Faculty Courses (" << faculty.getCourses().size() << ") ---\n";
        for (const auto& c : faculty.getCourses()) {
            if (c) std::cout << "ID: " << c->getId() << " | Title: " << c->getTitle() << "\n";
        }
        std::cout << "1. Create new course\n"
                  << "2. Open course management\n"
                  << "3. Find courses by title keyword (findByCriterion)\n"
                  << "0. Back\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) {
            handleCreateCourse(faculty);
        } else if (choice == 2) {
            try {
                int cId = readInt("Enter course ID: ");
                Course* c = faculty.getCourse(cId);
                showCourseDetailsSubmenu(faculty, c);
            } catch (const EntityNotFoundException& ex) {
                std::cout << "[Not Found Error] " << ex.what() << "\n";
            }
        } else if (choice == 3) {
            handleFindCourseByTitle(faculty);
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
                  << "2. Courses & Activities Management\n"
                  << "0. Exit\n"
                  << "Select: ";
        choice = readInt("");
        if (choice == 1) showTeachersSubmenu(faculty);
        else if (choice == 2) showCoursesSubmenu(faculty);
    }
}
