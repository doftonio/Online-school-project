#ifndef MENU_H
#define MENU_H

class Faculty;
class Course;

void runMainMenu(Faculty& faculty);

void showFacultySubmenu(Faculty& faculty);
void showTeachersSubmenu(Faculty& faculty);
void showGroupsSubmenu(Faculty& faculty);
void showCoursesSubmenu(Faculty& faculty);
void showCourseDetailsSubmenu(Faculty& faculty, const Course* course);

void handleCourseActivities(const Course* course);
void handleAddGrade(const Course* course);
void handleRemoveGrade(const Course* course);
void handlePrintGrades(const Course* course);

#endif // MENU_H
