#ifndef SIMPLE_CMAKE_TEMPLATE_STUDENT_H
#define SIMPLE_CMAKE_TEMPLATE_STUDENT_H

#include <cstdio>

enum Major {
    FRAUD,
    INTERNATIONALSCHEMES,
    CREATIVENIHILISM,
    SUBJECTIVEREACHES,
    FILEANALIZIS,
    MICROMANAGEMENT,
    APPLIEDMATERIALIZATION,
    SUBJECTIVISTICS,
    MAGNETISMANDCLEARING
};

class Student {
private:
    size_t fn;
    size_t arrivalMinute;
    Major major;
    size_t duration;
    size_t leavingMinute;
public:
    Student(size_t fn, size_t minute, Major major, size_t duration);
    size_t getMinute()const;
    size_t getLeavingMinute()const;
    size_t getFN()const;
    Major getMajor()const;
    size_t getDuration();
    void setLeavingMinute(size_t leavingMinute_);
};


#endif //SIMPLE_CMAKE_TEMPLATE_STUDENT_H
