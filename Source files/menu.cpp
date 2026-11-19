#include "../Header files/menu.h"
#include "../Header files/faculty.h"
#include "../Header files/course.h"
#include "../Header files/teacher.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/collection.h"
#include "../Storage/fileStorageService.h"
#include "../Storage/logger.h"
#include "../Exceptions/exceptions.h"
#include <iostream>
#include <string>
#include <string_view>
#include <initializer_list>
#include <memory>
#include <limits>
#include <utility>
#include <vector>
#include <format>

namespace {

void clearStreamState() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(std::string_view prompt) {
    std::cout << prompt;
    int val = 0;
    while (!(std::cin >> val)) {
        clearStreamState();
        std::cout << "Invalid input. Please enter an integer: ";
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;
}

std::string readLine(std::string_view prompt) {
    std::cout << prompt;
    std::string val;
    std::getline(std::cin, val);
    return val;
}

std::string readLineWithDefault(std::string_view prompt, std::string_view defaultValue) {
    std::cout << std::format("{} [default: {}]: ", prompt, defaultValue);
    std::string val;
    std::getline(std::cin, val);
    if (val.empty()) {
        return std::string(defaultValue);
    }
    return val;
}

int promptMenuChoice(std::initializer_list<std::string_view> options, std::string_view exitLabel = "Back") {
    std::size_t index = 1;
    for (std::string_view option : options) {
        std::cout << std::format("{}. {}\n", index++, option);
    }
    std::cout << std::format("0. {}\n", exitLabel);
    return readInt("Select: ");
}

void triggerAutoSave(const Faculty& faculty, std::string_view actionDescription) {
    try {
        const std::string savedPath = FileStorageService::saveState(faculty, FileStorageService::AUTOSAVE_FILE);
        Logger::info(std::format(R"({} | Auto-saved state to "{}".)", actionDescription, savedPath));
    } catch (const AppException& ex) {
        Logger::error(std::format("Auto-save failed after {}: {}", actionDescription, ex.what()));
        std::cout << "[Auto-Save Warning] " << ex.what() << "\n";
    }
}

template <typename Action>
void executeMenuAction(std::string_view context, Action&& action, bool resetStreamOnFail = false) {
    try {
        std::forward<Action>(action)();
    } catch (const DuplicateEntityException& ex) {
        if (resetStreamOnFail && std::cin.fail()) clearStreamState();
        Logger::warn(std::format("{}: {}", context, ex.what()));
        std::cout << "[Duplicate Error] " << ex.what() << "\n";
    } catch (const EntityNotFoundException& ex) {
        if (resetStreamOnFail && std::cin.fail()) clearStreamState();
        Logger::warn(std::format("{}: {}", context, ex.what()));
        std::cout << "[Not Found Error] " << ex.what() << "\n";
    } catch (const CapacityExceededException& ex) {
        if (resetStreamOnFail && std::cin.fail()) clearStreamState();
        Logger::warn(std::format("{}: {}", context, ex.what()));
        std::cout << "[Capacity Limit Error] " << ex.what() << "\n";
    } catch (const InvalidInputDataException& ex) {
        if (resetStreamOnFail && std::cin.fail()) clearStreamState();
        Logger::warn(std::format("{}: {}", context, ex.what()));
        std::cout << "[Validation Error] " << ex.what() << "\n";
    } catch (const FileStorageException& ex) {
        if (resetStreamOnFail && std::cin.fail()) clearStreamState();
        Logger::error(std::format("{}: {}", context, ex.what()));
        std::cout << "[Storage Error] " << ex.what() << "\n";
    } catch (const AppException& ex) {
        if (resetStreamOnFail && std::cin.fail()) clearStreamState();
        Logger::error(std::format("{}: {}", context, ex.what()));
        std::cout << "[System Error] " << ex.what() << "\n";
    }
}

std::pair<std::unique_ptr<CourseActivity>, std::string_view> createActivityFromInput(int typeChoice, int lessons, Teacher* teacher) {
    if (typeChoice == 1) {
        const int topics = readInt("Enter topics count: ");
        const int hours = readInt("Enter lecture hours: ");
        return {std::make_unique<LectureActivity>(lessons, teacher, topics, hours), "Lecture"};
    }
    if (typeChoice == 2) {
        const int labs = readInt("Enter total labs count: ");
        const int minScore = readInt("Enter minimum passing score: ");
        return {std::make_unique<LabActivity>(lessons, teacher, labs, minScore), "Lab"};
    }
    if (typeChoice == 3) {
        const int tests = readInt("Enter tests count: ");
        const int tasks = readInt("Enter tasks count: ");
        const int calcs = readInt("Enter calculations count: ");
        return {std::make_unique<PracticeActivity>(lessons, teacher, tests, tasks, calcs), "Practice"};
    }
    throw InvalidInputDataException("Invalid activity type choice.");
}

}

void handleAddTeacher(Faculty& faculty) {
    std::cout << "\n--- Add New Teacher (via operator>>) ---\n";
    executeMenuAction("Failed to add teacher", [&faculty]() {
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
            triggerAutoSave(faculty, std::format("Added teacher ID {}", created->getId()));
        }
    }, true);
}

void handleFindTeacherByDepartment(const Faculty& faculty) {
    std::cout << "\n--- Find Teachers by Department (Member Method findIndex) ---\n";
    executeMenuAction("Teacher search failed", [&faculty]() {
        const std::string dept = readLine("Enter department name: ");
        if (dept.empty()) {
            throw InvalidInputDataException("Department query cannot be empty.");
        }

        const auto& teachers = faculty.getTeachers();
        const auto indices = teachers.findIndex([&dept](const std::unique_ptr<Teacher>& t) {
            return t && t->getDepartment() == dept;
        });

        if (indices.empty()) {
            std::cout << std::format(R"(No teachers found for department "{}".)" "\n", dept);
            return;
        }

        std::cout << std::format(R"(Found {} teacher(s) in department "{}":)" "\n", indices.size(), dept);
        for (std::size_t idx : indices) {
            std::cout << "  [" << idx << "] " << *(teachers.get(idx)) << "\n";
        }
    });
}

void handleCreateCourse(Faculty& faculty) {
    std::cout << "\n--- Create New Course ---\n";
    executeMenuAction("Failed to create course", [&faculty]() {
        const int id = readInt("Enter Course ID: ");
        const std::string title = readLine("Enter Course Title: ");

        const Course* created = faculty.createCourse(id, title);
        if (created) {
            std::cout << "Course created successfully: " << *created << "\n";
            triggerAutoSave(faculty, std::format(R"(Created course ID {} ("{}"))", created->getId(), created->getTitle()));
        }
    });
}

void handleFindCourseByTitle(const Faculty& faculty) {
    std::cout << "\n--- Find Courses by Title Keyword (Free Function findByCriterion) ---\n";
    executeMenuAction("Course search failed", [&faculty]() {
        const std::string titleQuery = readLine("Enter search keyword in title: ");
        if (titleQuery.empty()) {
            throw InvalidInputDataException("Course title keyword cannot be empty.");
        }

        const auto matches = findByCriterion(faculty.getCourses(), [&titleQuery](const std::unique_ptr<Course>& c) {
            return c && c->getTitle().contains(titleQuery);
        });

        if (matches.empty()) {
            std::cout << std::format(R"(No courses found matching "{}".)" "\n", titleQuery);
            return;
        }

        std::cout << std::format(R"(Found {} course(s) matching "{}":)" "\n", matches.size(), titleQuery);
        for (const auto* coursePtr : matches) {
            if (coursePtr && *coursePtr) {
                std::cout << "  - " << **coursePtr << "\n";
            }
        }
    });
}

void handleAssignTeacherToCourse(const Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Assign Teacher to Course ---\n";
    executeMenuAction("Failed to assign teacher", [&faculty, course]() {
        const int teacherId = readInt("Enter Teacher ID: ");
        Teacher* teacher = faculty.getTeacher(teacherId);
        *course += teacher;
        std::cout << "Teacher successfully assigned via operator+=\n";
        triggerAutoSave(faculty, std::format("Assigned teacher ID {} to course ID {}", teacherId, course->getId()));
    });
}

void handleRemoveTeacherFromCourse(const Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Remove Teacher from Course ---\n";
    executeMenuAction("Failed to remove teacher", [&faculty, course]() {
        const int teacherId = readInt("Enter Teacher ID to remove: ");
        *course -= teacherId;
        std::cout << "Teacher removed successfully via operator-=(int).\n";
        triggerAutoSave(faculty, std::format("Removed teacher ID {} from course ID {}", teacherId, course->getId()));
    });
}

void handleAddActivityToCourse(const Faculty& faculty, Course* course) {
    if (!course) return;
    std::cout << "\n--- Add Activity to Course (Polymorphic) ---\n"
              << "1. Lecture Activity\n"
              << "2. Lab Activity\n"
              << "3. Practice Activity\n";
    executeMenuAction("Failed to add activity", [&faculty, course]() {
        const int typeChoice = readInt("Select type: ");
        const int lessons = readInt("Enter number of lessons: ");
        const int teacherId = readInt("Enter Teacher ID for this activity: ");
        Teacher* teacher = faculty.getTeacher(teacherId);

        auto [activity, label] = createActivityFromInput(typeChoice, lessons, teacher);
        course->addActivity(std::move(activity));
        std::cout << label << " activity added polymorphically.\n";
        triggerAutoSave(faculty, std::format("Added {} activity to course ID {}", label, course->getId()));
    });
}

void handleManualSave(const Faculty& faculty) {
    std::cout << "\n--- Manual Save System State ---\n";
    executeMenuAction("Manual save failed", [&faculty]() {
        const std::string inputPath = readLineWithDefault("Enter save file name or path", FileStorageService::DEFAULT_MANUAL_FILE);
        const std::string savedPath = FileStorageService::saveState(faculty, inputPath);
        Logger::info(std::format(R"(Manual save completed to "{}".)", savedPath));
        std::cout << std::format(R"(System state successfully saved to "{}".)" "\n", savedPath);
    });
}

void handleManualLoad(Faculty& faculty) {
    std::cout << "\n--- Manual Load System State ---\n";
    executeMenuAction("Manual load failed", [&faculty]() {
        const std::string inputPath = readLineWithDefault("Enter save file name or path", FileStorageService::DEFAULT_MANUAL_FILE);
        const std::string loadedPath = FileStorageService::loadState(faculty, inputPath);
        Logger::info(std::format(R"(Manual load completed from "{}".)", loadedPath));
        std::cout << std::format(R"(System state successfully restored from "{}".)" "\n", loadedPath);
        triggerAutoSave(faculty, std::format(R"(Synchronized autosave after loading "{}")", loadedPath));
    });
}

void handleExportReport(const Faculty& faculty) {
    std::cout << "\n--- Export Text Report ---\n";
    executeMenuAction("Report export failed", [&faculty]() {
        const std::string inputPath = readLineWithDefault("Enter report file name or path", FileStorageService::DEFAULT_REPORT_FILE);
        const std::string reportPath = FileStorageService::exportReport(faculty, inputPath);
        Logger::info(std::format(R"(Text report exported to "{}".)", reportPath));
        std::cout << std::format(R"(Text report successfully generated at "{}".)" "\n", reportPath);
    });
}

void handleViewLog() {
    executeMenuAction("Log view failed", []() {
        const auto entries = Logger::readEntries(Logger::DEFAULT_LOG_FILE);
        std::cout << "\n--- System Event Log (" << Logger::DEFAULT_LOG_FILE << ") ---\n";
        if (entries.empty()) {
            std::cout << "(log is empty)\n";
            return;
        }
        for (const auto& entry : entries) {
            std::cout << entry << "\n";
        }
    });
}

void showCourseDetailsSubmenu(const Faculty& faculty, Course* course) {
    if (!course) return;
    int choice = -1;
    while (choice != 0) {
        std::cout << "\n=== Course: " << course->getTitle() << " (ID: " << course->getId() << ") ===\n";
        choice = promptMenuChoice({
            "Print full course info & activities (Polymorphic)",
            "Assign teacher to course (*course += teacher)",
            "Remove teacher from course (*course -= id)",
            "Add activity to course (Polymorphic)"
        });
        if (choice == 1) course->printFullCourseInfo();
        else if (choice == 2) handleAssignTeacherToCourse(faculty, course);
        else if (choice == 3) handleRemoveTeacherFromCourse(faculty, course);
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
        choice = promptMenuChoice({
            "Add new teacher",
            "Find teachers by department (Collection::findIndex)"
        });
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
        choice = promptMenuChoice({
            "Create new course",
            "Open course management",
            "Find courses by title keyword (findByCriterion)"
        });
        if (choice == 1) {
            handleCreateCourse(faculty);
        } else if (choice == 2) {
            executeMenuAction("Failed to open course", [&faculty]() {
                const int cId = readInt("Enter course ID: ");
                Course* c = faculty.getCourse(cId);
                showCourseDetailsSubmenu(faculty, c);
            });
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
                  << "========================================\n";
        choice = promptMenuChoice({
            "Teachers Management",
            "Courses & Activities Management",
            "Save state to file (Manual Save)",
            "Load state from file (Manual Load)",
            "Export text report",
            "View system event log"
        }, "Exit");
        if (choice == 1) showTeachersSubmenu(faculty);
        else if (choice == 2) showCoursesSubmenu(faculty);
        else if (choice == 3) handleManualSave(faculty);
        else if (choice == 4) handleManualLoad(faculty);
        else if (choice == 5) handleExportReport(faculty);
        else if (choice == 6) handleViewLog();
    }
}
