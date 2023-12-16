#include "Student.h"

Student::Student(size_t fn, size_t minute, Major major, size_t duration): fn(fn), arrivalMinute(minute), major(major), duration(duration), leavingMinute(0) {}

size_t Student::getMinute()const {
    return arrivalMinute;
}

size_t Student::getLeavingMinute()const {
    return leavingMinute;
}

size_t Student::getFN()const {
    return fn;
}

Major Student::getMajor()const {
    return major;
}

size_t Student::getDuration() {
    return duration;
}

void Student::setLeavingMinute(size_t leavingMinute_) {
    leavingMinute = leavingMinute_;
}