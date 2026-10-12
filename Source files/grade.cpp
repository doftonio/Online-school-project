#include "../Header files/grade.h"

Grade::Grade(int val, const Date& d) : value(val), date(d) {}

int Grade::getValue() const { return value; }
Date Grade::getDate() const { return date; }