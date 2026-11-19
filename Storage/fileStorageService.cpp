#include "fileStorageService.h"
#include "../Header files/teacher.h"
#include "../Header files/course.h"
#include "../Header files/courseActivity.h"
#include "../Header files/lectureActivity.h"
#include "../Header files/labActivity.h"
#include "../Header files/practiceActivity.h"
#include "../Exceptions/exceptions.h"
#include <fstream>
#include <filesystem>
#include <charconv>
#include <format>
#include <memory>
#include <utility>

void FileStorageService::validateFilePath(std::string_view filePath) {
    if (filePath.empty()) {
        throw FileStorageException("File path cannot be empty.");
    }
}

std::string FileStorageService::resolveStoragePath(std::string_view filePath) {
    if (filePath.empty()) {
        return {};
    }
    const std::filesystem::path rawPath{filePath};
    if (!rawPath.has_parent_path()) {
        return (std::filesystem::path{STORAGE_DIR} / rawPath).generic_string();
    }
    return rawPath.generic_string();
}

void FileStorageService::ensureDirectoryForFile(std::string_view filePath) {
    const std::filesystem::path targetPath{filePath};
    const std::filesystem::path parentDir = targetPath.parent_path();
    if (!parentDir.empty() && !std::filesystem::exists(parentDir)) {
        std::error_code ec;
        std::filesystem::create_directories(parentDir, ec);
        if (ec) {
            throw FileStorageException(std::format(
                R"(Cannot create storage directory "{}": {}.)", parentDir.string(), ec.message()));
        }
    }
}

void FileStorageService::validateField(std::string_view value, std::string_view fieldName) {
    if (value.contains('|') || value.contains('\n') || value.contains('\r')) {
        throw FileStorageException(std::format(
            R"(Field "{}" contains forbidden delimiter '|' or newline character.)", fieldName));
    }
}

std::vector<std::string> FileStorageService::splitRecord(std::string_view line, char delimiter) {
    std::vector<std::string> tokens;
    std::size_t start = 0;
    while (true) {
        const std::size_t pos = line.find(delimiter, start);
        if (pos == std::string_view::npos) {
            tokens.emplace_back(line.substr(start));
            break;
        }
        tokens.emplace_back(line.substr(start, pos - start));
        start = pos + 1;
    }
    return tokens;
}

int FileStorageService::parseIntField(std::string_view token, std::size_t lineNumber, std::string_view fieldName) {
    int value = 0;
    const auto* first = token.data();
    const auto* last = token.data() + token.size();
    const auto [ptr, ec] = std::from_chars(first, last, value);
    if (ec != std::errc{} || ptr != last || token.empty()) {
        throw FileStorageException(std::format(
            R"(Line {}: invalid integer value "{}" for field "{}".)", lineNumber, token, fieldName));
    }
    return value;
}

void FileStorageService::parseTeacherRecord(Faculty& targetFaculty, const std::vector<std::string>& tokens, std::size_t lineNumber) {
    if (tokens.size() != 6) {
        throw FileStorageException(std::format("Line {}: malformed TEACHER record (expected 6 fields).", lineNumber));
    }
    const int id = parseIntField(tokens[1], lineNumber, "teacherId");
    targetFaculty.createTeacher(id, tokens[2], tokens[3], tokens[4], tokens[5]);
}

void FileStorageService::parseCourseRecord(Faculty& targetFaculty, const std::vector<std::string>& tokens, std::size_t lineNumber) {
    if (tokens.size() != 3) {
        throw FileStorageException(std::format("Line {}: malformed COURSE record (expected 3 fields).", lineNumber));
    }
    const int id = parseIntField(tokens[1], lineNumber, "courseId");
    targetFaculty.createCourse(id, tokens[2]);
}

void FileStorageService::parseCourseTeacherRecord(const Faculty& targetFaculty, const std::vector<std::string>& tokens, std::size_t lineNumber) {
    if (tokens.size() != 3) {
        throw FileStorageException(std::format("Line {}: malformed COURSE_TEACHER record (expected 3 fields).", lineNumber));
    }
    const int courseId = parseIntField(tokens[1], lineNumber, "courseId");
    const int teacherId = parseIntField(tokens[2], lineNumber, "teacherId");
    Course* course = targetFaculty.getCourse(courseId);
    Teacher* teacher = targetFaculty.getTeacher(teacherId);
    *course += teacher;
}

void FileStorageService::parseActivityRecord(const Faculty& targetFaculty, const std::vector<std::string>& tokens, std::size_t lineNumber) {
    if (tokens.size() < 6) {
        throw FileStorageException(std::format("Line {}: malformed ACTIVITY record.", lineNumber));
    }
    const int courseId = parseIntField(tokens[1], lineNumber, "courseId");
    const std::string_view actType = tokens[2];
    const int lessons = parseIntField(tokens[3], lineNumber, "lessonsCount");
    const int teacherId = parseIntField(tokens[4], lineNumber, "teacherId");

    Course* course = targetFaculty.getCourse(courseId);
    Teacher* teacher = targetFaculty.getTeacher(teacherId);

    if (actType == "LECTURE") {
        if (tokens.size() != 7) {
            throw FileStorageException(std::format("Line {}: malformed LECTURE activity record.", lineNumber));
        }
        const int topics = parseIntField(tokens[5], lineNumber, "topicsCount");
        const int hours = parseIntField(tokens[6], lineNumber, "lectureHours");
        course->addActivity(std::make_unique<LectureActivity>(lessons, teacher, topics, hours));
    } else if (actType == "LAB") {
        if (tokens.size() != 7) {
            throw FileStorageException(std::format("Line {}: malformed LAB activity record.", lineNumber));
        }
        const int labsCount = parseIntField(tokens[5], lineNumber, "labsCount");
        const int minScore = parseIntField(tokens[6], lineNumber, "minPassingScore");
        course->addActivity(std::make_unique<LabActivity>(lessons, teacher, labsCount, minScore));
    } else if (actType == "PRACTICE") {
        if (tokens.size() != 8) {
            throw FileStorageException(std::format("Line {}: malformed PRACTICE activity record.", lineNumber));
        }
        const int tests = parseIntField(tokens[5], lineNumber, "testsCount");
        const int tasks = parseIntField(tokens[6], lineNumber, "tasksCount");
        const int calcs = parseIntField(tokens[7], lineNumber, "calculationsCount");
        course->addActivity(std::make_unique<PracticeActivity>(lessons, teacher, tests, tasks, calcs));
    } else {
        throw FileStorageException(std::format(R"(Line {}: unknown activity type "{}".)", lineNumber, actType));
    }
}

void FileStorageService::applyRecord(Faculty& targetFaculty, bool& hasFacultyHeader, const std::vector<std::string>& tokens, std::size_t lineNumber) {
    const std::string_view recordType = tokens[0];

    if (recordType == "FACULTY") {
        if (tokens.size() != 2) {
            throw FileStorageException(std::format("Line {}: malformed FACULTY record.", lineNumber));
        }
        if (hasFacultyHeader) {
            throw FileStorageException(std::format("Line {}: duplicate FACULTY header record.", lineNumber));
        }
        targetFaculty = Faculty(tokens[1]);
        hasFacultyHeader = true;
        return;
    }

    if (!hasFacultyHeader) {
        throw FileStorageException(std::format(R"(Line {}: "{}" record precedes FACULTY header.)", lineNumber, recordType));
    }

    if (recordType == "TEACHER") {
        parseTeacherRecord(targetFaculty, tokens, lineNumber);
    } else if (recordType == "COURSE") {
        parseCourseRecord(targetFaculty, tokens, lineNumber);
    } else if (recordType == "COURSE_TEACHER") {
        parseCourseTeacherRecord(targetFaculty, tokens, lineNumber);
    } else if (recordType == "ACTIVITY") {
        parseActivityRecord(targetFaculty, tokens, lineNumber);
    } else {
        throw FileStorageException(std::format(R"(Line {}: unknown record tag "{}".)", lineNumber, recordType));
    }
}

std::string FileStorageService::saveState(const Faculty& faculty, std::string_view filePath) {
    validateFilePath(filePath);
    const std::string resolvedPath = resolveStoragePath(filePath);
    ensureDirectoryForFile(resolvedPath);
    validateField(faculty.getName(), "Faculty::name");

    std::ofstream outFile{resolvedPath, std::ios::out | std::ios::trunc};
    if (!outFile.is_open()) {
        throw FileStorageException(std::format(R"(Cannot open file "{}" for writing.)", resolvedPath));
    }

    outFile << std::format("FACULTY|{}\n", faculty.getName());

    for (const auto& t : faculty.getTeachers()) {
        if (!t) continue;
        validateField(t->getFirstName(), "Teacher::firstName");
        validateField(t->getLastName(), "Teacher::lastName");
        validateField(t->getMiddleName(), "Teacher::middleName");
        validateField(t->getDepartment(), "Teacher::department");

        outFile << std::format("TEACHER|{}|{}|{}|{}|{}\n",
                               t->getId(),
                               t->getFirstName(),
                               t->getLastName(),
                               t->getMiddleName(),
                               t->getDepartment());
    }

    for (const auto& c : faculty.getCourses()) {
        if (!c) continue;
        validateField(c->getTitle(), "Course::title");
        outFile << std::format("COURSE|{}|{}\n", c->getId(), c->getTitle());
    }

    for (const auto& c : faculty.getCourses()) {
        if (!c) continue;
        for (const auto* t : c->getTeachers()) {
            if (!t) continue;
            outFile << std::format("COURSE_TEACHER|{}|{}\n", c->getId(), t->getId());
        }
    }

    for (const auto& c : faculty.getCourses()) {
        if (!c) continue;
        for (const auto& act : c->getActivities()) {
            if (!act) continue;
            outFile << act->serializeRecord(c->getId()) << "\n";
        }
    }

    outFile.flush();
    if (outFile.fail() || outFile.bad()) {
        throw FileStorageException(std::format(R"(Write error occurred while saving state to "{}".)", resolvedPath));
    }

    return resolvedPath;
}

std::string FileStorageService::loadState(Faculty& faculty, std::string_view filePath) {
    validateFilePath(filePath);
    const std::string resolvedPath = resolveStoragePath(filePath);

    std::ifstream inFile{resolvedPath, std::ios::in};
    if (!inFile.is_open()) {
        throw FileStorageException(std::format(R"(Cannot open file "{}" for reading.)", resolvedPath));
    }

    Faculty tempFaculty("Temporary");
    bool hasFacultyHeader = false;
    std::string line;
    std::size_t lineNumber = 0;

    while (std::getline(inFile, line)) {
        ++lineNumber;
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        if (line.empty()) {
            continue;
        }
        const auto tokens = splitRecord(line, '|');
        applyRecord(tempFaculty, hasFacultyHeader, tokens, lineNumber);
    }

    if (inFile.bad()) {
        throw FileStorageException(std::format(R"(I/O error occurred while reading file "{}".)", resolvedPath));
    }

    if (!hasFacultyHeader) {
        throw FileStorageException(std::format(R"(File "{}" is empty or missing FACULTY header.)", resolvedPath));
    }

    faculty = std::move(tempFaculty);
    return resolvedPath;
}

std::pair<int, int> FileStorageService::calculateFacultyWorkload(const Faculty& faculty) {
    int totalContactHours = 0;
    int totalSelfStudyHours = 0;
    for (const auto& c : faculty.getCourses()) {
        if (!c) continue;
        for (const auto& act : c->getActivities()) {
            if (!act) continue;
            totalContactHours += act->calculateHours();
            totalSelfStudyHours += act->calculateSelfStudyHours();
        }
    }
    return {totalContactHours, totalSelfStudyHours};
}

void FileStorageService::writeTeachersSection(std::ostream& out, const Faculty& faculty) {
    out << "1. FACULTY TEACHERS ROSTER\n"
        << "------------------------------------------------------------\n";
    if (faculty.getTeachers().empty()) {
        out << "  (No teachers registered)\n";
        return;
    }
    for (const auto& t : faculty.getTeachers()) {
        if (!t) continue;
        out << std::format("  [ID: {}] {} | Department: {}\n",
                           t->getId(), t->getFullName(), t->getDepartment());
    }
}

void FileStorageService::writeCourseDetails(std::ostream& out, const Course& course) {
    out << std::format("\nCourse [ID: {}]: {}\n", course.getId(), course.getTitle());
    out << "  Assigned Teachers:\n";
    if (course.getTeachers().empty()) {
        out << "    - None\n";
    } else {
        for (const auto* t : course.getTeachers()) {
            if (!t) continue;
            out << std::format("    - [ID: {}] {} ({})\n",
                               t->getId(), t->getFullName(), t->getDepartment());
        }
    }

    out << "  Activities:\n";
    if (course.getActivities().empty()) {
        out << "    - None\n";
        return;
    }
    for (const auto& act : course.getActivities()) {
        if (!act) continue;
        out << act->formatReportLine() << "\n";
    }
}

void FileStorageService::writeCoursesSection(std::ostream& out, const Faculty& faculty) {
    out << "\n2. COURSES AND EDUCATIONAL ACTIVITIES\n"
        << "------------------------------------------------------------\n";
    if (faculty.getCourses().empty()) {
        out << "  (No courses registered)\n";
        return;
    }
    for (const auto& c : faculty.getCourses()) {
        if (!c) continue;
        writeCourseDetails(out, *c);
    }
}

void FileStorageService::patchReportSize(std::ostream& out, std::streampos sizeFieldPos) {
    if (const std::streampos endPos = out.tellp();
        sizeFieldPos != std::streampos{-1} && endPos != std::streampos{-1}) {
        const auto totalBytes = static_cast<std::size_t>(endPos);
        out.seekp(sizeFieldPos);
        out << std::format("Report Size (bytes) : {:08}\n", totalBytes);
        out.seekp(endPos);
    }
}

std::string FileStorageService::exportReport(const Faculty& faculty, std::string_view filePath) {
    validateFilePath(filePath);
    const std::string resolvedPath = resolveStoragePath(filePath);
    ensureDirectoryForFile(resolvedPath);

    std::fstream reportFile{resolvedPath, std::ios::out | std::ios::trunc};
    if (!reportFile.is_open()) {
        throw FileStorageException(std::format(R"(Cannot open report file "{}" for writing.)", resolvedPath));
    }

    reportFile << "============================================================\n"
               << "               ONLINE SCHOOL SYSTEM REPORT\n"
               << "============================================================\n";

    const std::streampos sizeFieldPos = reportFile.tellp();
    const auto [totalContactHours, totalSelfStudyHours] = calculateFacultyWorkload(faculty);

    reportFile << "Report Size (bytes) : 00000000\n";
    reportFile << std::format("Faculty Name        : {}\n", faculty.getName());
    reportFile << std::format("Registered Teachers : {}\n", faculty.getTeachers().size());
    reportFile << std::format("Registered Courses  : {}\n", faculty.getCourses().size());
    reportFile << std::format("Total Contact Hours : {}\n", totalContactHours);
    reportFile << std::format("Total Self-Study Hrs: {}\n", totalSelfStudyHours);
    reportFile << "============================================================\n\n";

    writeTeachersSection(reportFile, faculty);
    writeCoursesSection(reportFile, faculty);

    reportFile << "\n============================================================\n"
               << "                       END OF REPORT\n"
               << "============================================================\n";

    patchReportSize(reportFile, sizeFieldPos);

    reportFile.flush();
    if (reportFile.fail() || reportFile.bad()) {
        throw FileStorageException(std::format(R"(Write error occurred while generating report "{}".)", resolvedPath));
    }

    return resolvedPath;
}
