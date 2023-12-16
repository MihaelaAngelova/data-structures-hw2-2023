#include "catch2/catch_all.hpp"
#include "simulator-lib/StudentLinkedList.h"

TEST_CASE("empty list")
{
    StudentLinkedList sll;
    std::string expected = "";
    REQUIRE(sll.toString() == expected);
    REQUIRE(sll.isEmpty() == true);
    REQUIRE(sll.getSize() == 0);
}

TEST_CASE("insertAtEnd() works for empty lists")
{
    StudentLinkedList sll;
    Student student (1, 0, FRAUD, 2);
    std::string expected = "1";

    sll.insertAtEnd(student);

    REQUIRE(sll.toString() == expected);
    REQUIRE(sll.getSize() == 1);
}

TEST_CASE("insertAtEnd() works for a non-empty list")
{
    StudentLinkedList sll;
    Student student1 (1, 0, FRAUD, 2);
    Student student2 (2, 0, FRAUD, 2);
    Student student3 (3, 0, FRAUD, 2);
    std::string expected = "1 2 3";

    sll.insertAtEnd(student1);
    sll.insertAtEnd(student2);
    sll.insertAtEnd(student3);

    REQUIRE(sll.toString() == expected);
    REQUIRE(sll.getSize() == 3);
}

TEST_CASE("deleteFirst() doesn't do anything on empty lists")
{
    StudentLinkedList sll;
    std::string expected = "";

    sll.deleteFirst();

    REQUIRE(sll.toString() == expected);
    REQUIRE(sll.isEmpty() == true);
    REQUIRE(sll.getSize() == 0);
}

TEST_CASE("deleteFirst() works for a list with only one element")
{
    StudentLinkedList sll;
    Student student (1, 0, FRAUD, 2);
    sll.insertAtEnd(student);
    std::string expected = "";

    sll.deleteFirst();

    REQUIRE(sll.toString() == expected);
    REQUIRE(sll.isEmpty() == true);
    REQUIRE(sll.getSize() == 0);
}

TEST_CASE("deleteFirst() works for a list with many elements")
{
    StudentLinkedList sll;
    Student student1 (1, 0, FRAUD, 2);
    Student student2 (2, 0, FRAUD, 2);
    Student student3 (3, 0, FRAUD, 2);
    Student student4 (4, 0, FRAUD, 2);
    Student student5 (5, 0, FRAUD, 2);
    sll.insertAtEnd(student1);
    sll.insertAtEnd(student2);
    sll.insertAtEnd(student3);
    sll.insertAtEnd(student4);
    sll.insertAtEnd(student5);
    std::string expected = "2 3 4 5";

    sll.deleteFirst();

    REQUIRE(sll.toString() == expected);
    REQUIRE(sll.getSize() == 4);
}

TEST_CASE("leave() removes all the students with the given current minute")
{
    StudentLinkedList sll;
    size_t currentMinute = 42;
    Student student1 (1, 0, FRAUD, 2);
    student1.setLeavingMinute(currentMinute);
    Student student2 (2, 0, FRAUD, 2);
    student2.setLeavingMinute(50);
    Student student3 (3, 0, FRAUD, 2);
    student3.setLeavingMinute(currentMinute);
    Student student4 (4, 0, FRAUD, 2);
    student4.setLeavingMinute(100);
    Student student5 (5, 0, FRAUD, 2);
    student5.setLeavingMinute(currentMinute);
    sll.insertAtEnd(student1);
    sll.insertAtEnd(student2);
    sll.insertAtEnd(student3);
    sll.insertAtEnd(student4);
    sll.insertAtEnd(student5);
    std::string expectedList = "2 4";
    std::stringstream output;
    std::string expectedOutput = "42 1 exit\n42 3 exit\n42 5 exit\n";

    sll.leave(currentMinute, output);

    REQUIRE(sll.toString() == expectedList);
    REQUIRE(output.str() == expectedOutput);
    REQUIRE(sll.getSize() == 2);
}

TEST_CASE("leave() removes no students with the given current minute")
{
    StudentLinkedList sll;
    size_t currentMinute = 20;
    Student student1 (1, 0, FRAUD, 2);
    student1.setLeavingMinute(42);
    Student student2 (2, 0, FRAUD, 2);
    student2.setLeavingMinute(50);
    Student student3 (3, 0, FRAUD, 2);
    student3.setLeavingMinute(42);
    Student student4 (4, 0, FRAUD, 2);
    student4.setLeavingMinute(100);
    Student student5 (5, 0, FRAUD, 2);
    student5.setLeavingMinute(42);
    sll.insertAtEnd(student1);
    sll.insertAtEnd(student2);
    sll.insertAtEnd(student3);
    sll.insertAtEnd(student4);
    sll.insertAtEnd(student5);
    std::string expectedList = "1 2 3 4 5";
    std::stringstream output;
    std::string expectedOutput = "";

    sll.leave(currentMinute, output);

    REQUIRE(sll.toString() == expectedList);
    REQUIRE(output.str() == expectedOutput);
    REQUIRE(sll.getSize() == 5);
}

TEST_CASE("leave() removes no students when the list is empty")
{
    StudentLinkedList sll;
    size_t currentMinute = 20;
    std::string expectedList = "";
    std::stringstream output;
    std::string expectedOutput = "";

    sll.leave(currentMinute, output);

    REQUIRE(sll.toString() == expectedList);
    REQUIRE(output.str() == expectedOutput);
    REQUIRE(sll.getSize() == 0);
}

TEST_CASE("insert() works for an empty list")
{
    StudentLinkedList sll;
    Student student(1, 0, FRAUD, 2);
    size_t maxGroupSize = 1;
    std::string expectedList = "1";

    sll.insert(student, maxGroupSize);

    REQUIRE(sll.toString() == expectedList);
    REQUIRE(sll.getSize() == 1);
}

TEST_CASE("insert() works if no space in groups with the same major")
{
    StudentLinkedList sll;
    Student student1(1, 0, FRAUD, 2);
    Student student2(2, 0, FRAUD, 2);
    Student student3(3, 0, SUBJECTIVISTICS, 2);
    Student student4(4, 0, SUBJECTIVISTICS, 2);
    sll.insertAtEnd(student1);
    sll.insertAtEnd(student2);
    sll.insertAtEnd(student3);
    sll.insertAtEnd(student4);
    size_t maxGroupSize = 2;
    Student studentToPut(5, 0, FRAUD, 2);
    std::string expectedList = "1 2 3 4 5";

    sll.insert(studentToPut, maxGroupSize);

    REQUIRE(sll.toString() == expectedList);
    REQUIRE(sll.getSize() == 5);
}

TEST_CASE("insert() works if there are no groups with the same major")
{
    StudentLinkedList sll;
    Student student1(1, 0, FRAUD, 2);
    Student student2(2, 0, FRAUD, 2);
    Student student3(3, 0, SUBJECTIVISTICS, 2);
    Student student4(4, 0, SUBJECTIVISTICS, 2);
    sll.insertAtEnd(student1);
    sll.insertAtEnd(student2);
    sll.insertAtEnd(student3);
    sll.insertAtEnd(student4);
    size_t maxGroupSize = 2;
    Student studentToPut(5, 0, MAGNETISMANDCLEARING, 2);
    std::string expectedList = "1 2 3 4 5";

    sll.insert(studentToPut, maxGroupSize);

    REQUIRE(sll.toString() == expectedList);
    REQUIRE(sll.getSize() == 5);
}

TEST_CASE("insert() works if there is enough space in a group with his major")
{
    StudentLinkedList sll;
    Student student1(1, 0, FRAUD, 2);
    Student student2(2, 0, FRAUD, 2);
    Student student3(3, 0, SUBJECTIVISTICS, 2);
    Student student4(4, 0, SUBJECTIVISTICS, 2);
    sll.insertAtEnd(student1);
    sll.insertAtEnd(student2);
    sll.insertAtEnd(student3);
    sll.insertAtEnd(student4);
    size_t maxGroupSize = 3;
    Student studentToPut(5, 0, FRAUD, 2);
    std::string expectedList = "1 2 5 3 4";

    sll.insert(studentToPut, maxGroupSize);

    REQUIRE(sll.toString() == expectedList);
    REQUIRE(sll.getSize() == 5);
}

TEST_CASE("enter() works for an empty queue")
{
    StudentLinkedList queue;
    StudentLinkedList bar;
    size_t maxGroupSize = 1;
    size_t barCapacity = 1;
    size_t currentMinute = 42;
    std::string expectedQueue = "";
    std::string expectedBar = "";
    std::stringstream output;
    std::string expectedOutput = "";

    queue.enter(bar, barCapacity, currentMinute, maxGroupSize, output);

    REQUIRE(queue.toString() == expectedQueue);
    REQUIRE(bar.toString() == expectedBar);
    REQUIRE(output.str() == expectedOutput);
}

TEST_CASE("enter() handles leaving students when there is space for the first group")
{
    StudentLinkedList queue;
    StudentLinkedList bar;
    size_t maxGroupSize = 2;
    size_t barCapacity = 2;
    size_t currentMinute = 42;

    Student student1(1, 0, FRAUD, 2);
    Student student2(2, 0, FRAUD, 2);
    Student student3(3, 0, FRAUD, 2);
    Student student4(4, 0, FRAUD, 2);

    queue.insertAtEnd(student1);
    queue.insertAtEnd(student2);
    queue.insertAtEnd(student3);
    queue.insertAtEnd(student4);

    std::string expectedQueue = "3 4";
    std::string expectedBar = "1 2";
    std::stringstream output;

    queue.enter(bar, barCapacity, currentMinute, maxGroupSize, output);

    REQUIRE(queue.toString() == expectedQueue);
    REQUIRE(bar.toString() == expectedBar);
    REQUIRE(output.str() == "42 1 enter\n42 2 enter\n");
}

TEST_CASE("enter() handles leaving students when there is space for the second group")
{
    StudentLinkedList queue;
    StudentLinkedList bar;
    size_t maxGroupSize = 3;
    size_t barCapacity = 2;
    size_t currentMinute = 42;

    Student student1(1, 0, FRAUD, 2);
    Student student2(2, 0, FRAUD, 2);
    Student student3(3, 0, FRAUD, 2);
    Student student4(4, 0, MICROMANAGEMENT, 2);

    queue.insertAtEnd(student1);
    queue.insertAtEnd(student2);
    queue.insertAtEnd(student3);
    queue.insertAtEnd(student4);

    std::string expectedQueue = "1 2 3";
    std::string expectedBar = "4";
    std::stringstream output;

    queue.enter(bar, barCapacity, currentMinute, maxGroupSize, output);

    REQUIRE(queue.toString() == expectedQueue);
    REQUIRE(bar.toString() == expectedBar);
    REQUIRE(output.str() == "42 4 enter\n");
}

TEST_CASE("enter() handles leaving students when there is space for two groups")
{
    StudentLinkedList queue;
    StudentLinkedList bar;
    size_t maxGroupSize = 2;
    size_t barCapacity = 3;
    size_t currentMinute = 42;

    Student student1(1, 0, FRAUD, 2);
    Student student2(2, 0, FRAUD, 2);
    Student student3(3, 0, MICROMANAGEMENT, 2);
    Student student4(4, 0, MICROMANAGEMENT, 2);
    Student student5(5, 0, INTERNATIONALSCHEMES, 2);


    queue.insertAtEnd(student1);
    queue.insertAtEnd(student2);
    queue.insertAtEnd(student3);
    queue.insertAtEnd(student4);
    queue.insertAtEnd(student5);

    std::string expectedQueue = "3 4";
    std::string expectedBar = "1 2 5";
    std::stringstream output;

    queue.enter(bar, barCapacity, currentMinute, maxGroupSize, output);

    REQUIRE(queue.toString() == expectedQueue);
    REQUIRE(bar.toString() == expectedBar);
    REQUIRE(output.str() == "42 1 enter\n42 2 enter\n42 5 enter\n");
}

TEST_CASE("leave() handles leaving students when bar has space for all groups")
{
    StudentLinkedList sll;
    StudentLinkedList bar;
    size_t maxGroupSize = 2;
    size_t barCapacity = 4;
    size_t currentMinute = 42;

    Student student1(1, 0, FRAUD, 2);
    Student student2(2, 0, FRAUD, 2);
    Student student3(3, 0, FRAUD, 2);
    Student student4(4, 0, FRAUD, 2);

    sll.insertAtEnd(student1);
    sll.insertAtEnd(student2);
    sll.insertAtEnd(student3);
    sll.insertAtEnd(student4);

    std::string expectedQueue = "";
    std::string expectedBar = "1 2 3 4";
    std::stringstream output;

    sll.enter(bar, barCapacity, currentMinute, maxGroupSize, output);

    REQUIRE(sll.toString() == expectedQueue);
    REQUIRE(bar.toString() == expectedBar);
    REQUIRE(output.str() == "42 1 enter\n42 2 enter\n42 3 enter\n42 4 enter\n");
}