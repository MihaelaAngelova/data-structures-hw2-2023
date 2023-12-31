#include "bar-simulator.h"
#include "Student.h"
#include "StudentLinkedList.h"
#include <cstring>
#include <string>
#include <sstream>

///
/// @brief Simulate the student bar problem
///
/// @param input
///   The stream, which contains the simulation commands
/// @param output
///   The stream, where the steps of simulation have to be printed.
///


Major strToMajor(std::string str) {
    if(str == "Fraud") {
        return FRAUD;
    } else if(str == "International Schemes") {
        return INTERNATIONALSCHEMES;
    } else if(str == "Creative Nihilism") {
        return CREATIVENIHILISM;
    } else if(str == "Subjective Researches") {
        return SUBJECTIVEREACHES;
    } else if(str == "File Analizis") {
        return FILEANALIZIS;
    } else if(str == "Micromanagement") {
        return MICROMANAGEMENT;
    } else if(str == "Applied Materialization") {
        return APPLIEDMATERIALIZATION;
    } else if(str == "Subjectivistics") {
        return SUBJECTIVISTICS;
    } else if(str == "Magnetism and Clearing") {
        return MAGNETISMANDCLEARING;
    } else throw incorrect_simulation("Major not found!");
}

Student studentUpdate(std::istream& input) {
    size_t indexOfFirstSpace;
    size_t indexOfSecondSpace;
    size_t indexOfLastSpace;
    size_t spaces = 0;

    std::string line;
    std::getline(input, line);

    for(char i : line) { // count spaces
        if(i == ' ') {
            spaces++;
        }
    }

    if(spaces < 3 || spaces > 5) { // wrong input
        throw incorrect_simulation("Not enough student data!");
    }

    size_t currSpaces = 0;
    for(size_t i = 0; i < line.size(); i++) { // set indexes of every relevant space
        if (line[i] == ' ') {
            currSpaces++;
            if(currSpaces == 1) {
                indexOfFirstSpace = i;
            } else if(currSpaces == 2) {
                indexOfSecondSpace = i;
            } else if(currSpaces == spaces) {
                indexOfLastSpace = i;
            }
        }
    }

    std::string fnString = line.substr(0, indexOfFirstSpace); // substr of the data
    std::string minuteString = line.substr(indexOfFirstSpace + 1, indexOfSecondSpace - indexOfFirstSpace - 1);
    std::string majorString = line.substr(indexOfSecondSpace + 1, indexOfLastSpace - indexOfSecondSpace - 1);
    std::string durationString = line.substr(indexOfLastSpace + 1);

    // SET INPUT VALUES
    int fnInt = stoi(fnString);
    if (fnInt < 0) {
        throw incorrect_simulation("Invalid value for fn: " + fnString);
    }

    int minuteInt = stoi(minuteString);
    if (minuteInt < 0) {
        throw incorrect_simulation("Invalid value for minute: " + minuteString);
    }

    Major major = strToMajor(majorString);

    int durationInt = stoi(durationString);
    if (durationInt < 0) {
        throw incorrect_simulation("Invalid value for duration: " + durationString);
    }

    Student student((size_t)fnInt, (size_t)minuteInt, major, (size_t)durationInt); // update student data
    return student;
}

void simulate_bar(std::istream& input, std::ostream& output)
{
    size_t K; // capacity
    size_t G; // max group size
    size_t N; // number of students

    std::string firstLine;
    std::getline(input, firstLine);

    if(firstLine.empty()) {
        throw incorrect_simulation("Empty input!");
    }

    std::stringstream firstLineStream(firstLine);
    firstLineStream >> K >> G >> N;

    if(G > K) {
        throw std::runtime_error("Group size is bigger than the bar capacity!");
    }

    if(N == 0) {
        return;
    }

    if(K <= 0) {
        throw std::runtime_error("No space in bar!");
    }

    StudentLinkedList allStudents; // a list of all students that should be manipulated
    size_t currentMinute = 0;

    while(N-- > 0) {
        Student s = studentUpdate(input);
        allStudents.insertAtEnd(s);
    }

    StudentLinkedList studentsWaiting; // a list of the queue of students
    StudentLinkedList studentsInBar; // a list of the students in the bar with max size K

    while(!allStudents.isEmpty() || !studentsInBar.isEmpty()) {
        // LEAVE THE BAR
        studentsInBar.leave(currentMinute, output); // check if some of the students should leave the bar at this exact minute

        // WAIT IN FRONT OF THE BAR
        while(allStudents.getSize() > 0 && (allStudents.getFirstStudent().getMinute() == currentMinute)) {
            // while there still are students who should show up and if one of them arrives at the current minute
            studentsWaiting.insert(allStudents.getFirstStudent(), G); // move the student into the queue
            // with other students
            allStudents.deleteFirst(); // remove the student from the list with students who should show up
            // this way I can move students from one structure to another in order to track their actions easily
        }

        // ENTER THE BAR
        if(studentsInBar.getSize() < K) { // if there is enough space for someone to enter the bar
            studentsWaiting.enter(studentsInBar, K, currentMinute, G, output);
        }

        currentMinute++; // track the minutes
    }
}
