#include "../Header files/faculty.h"
#include <algorithm>

Faculty::Faculty(std::string_view facultyName) : name(facultyName) {}

Teacher* Faculty::createTeacher(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view dept) {
    auto teacher = std::make_unique<Teacher>(id, first, last, middle, dept);
    Teacher* raw = teacher.get();
    allTeachers.push_back(std::move(teacher));
    return raw;
}

StudyGroup* Faculty::createGroup(std::string_view number, int year, int capacity) {
    auto grp = std::make_unique<StudyGroup>(number, year, capacity);
    StudyGroup* raw = grp.get();
    allGroups.push_back(std::move(grp));
    return raw;
}

Course* Faculty::createCourse(int id, std::string_view title) {
    auto c = std::make_unique<Course>(id, title);
    Course* raw = c.get();
    allCourses.push_back(std::move(c));
    return raw;
}

StudyGroup* Faculty::findGroup(std::string_view groupNum) const {
    for (const auto& g : allGroups) {
        if (g && g->getNumber() == groupNum) return g.get();
    }
    return nullptr;
}

Teacher* Faculty::findTeacher(int teacherId) const {
    for (const auto& t : allTeachers) {
        if (t && t->getId() == teacherId) return t.get();
    }
    return nullptr;
}

Course* Faculty::findCourse(int courseId) const {
    for (const auto& c : allCourses) {
        if (c && c->getId() == courseId) return c.get();
    }
    return nullptr;
}

Student* Faculty::findStudent(int studentId) const {
    for (const auto& s : allStudents) {
        if (s && s->getId() == studentId) return s.get();
    }
    return nullptr;
}

Student* Faculty::enrollStudentInGroup(int id, std::string_view first, std::string_view last, std::string_view middle, StudyGroup* group) {
    if (!group) return nullptr;
    auto student = std::make_unique<Student>(id, first, last, middle, 0);
    Student* raw = student.get();
    allStudents.push_back(std::move(student));
    *group += raw;
    return raw;
}

Student* Faculty::enrollStudentInGroup(int id, std::string_view first, std::string_view last, std::string_view middle, std::string_view groupNum) {
    StudyGroup* group = findGroup(groupNum);
    return enrollStudentInGroup(id, first, last, middle, group);
}

void Faculty::expelStudent(Student* student) {
    if (!student) return;

    for (const auto& course : allCourses) {
        if (course) {
            course->getGradeBook().removeAllGradesForStudent(student);
        }
    }

    for (const auto& grp : allGroups) {
        if (grp) {
            *grp -= student;
        }
    }

    std::erase_if(allStudents, [student](const std::unique_ptr<Student>& ptr) {
        return ptr.get() == student;
    });
}

void Faculty::expelStudent(int studentId) {
    Student* student = findStudent(studentId);
    if (student) {
        expelStudent(student);
    }
}
