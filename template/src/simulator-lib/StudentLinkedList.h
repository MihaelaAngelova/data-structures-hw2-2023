#ifndef SIMPLE_CMAKE_TEMPLATE_STUDENTLINKEDLIST_H
#define SIMPLE_CMAKE_TEMPLATE_STUDENTLINKEDLIST_H

#include "Student.h"
#include <iostream>
#include <cstring>

struct Node {
    Student student;
    Node* next;
    Node(Student student, Node* next): student(student), next(next) {}
    Node(Student student): student(student) {}
};

class StudentLinkedList {
private:
    Node* head;
    Node* tail;
    size_t size;
    void deleteNode(Node* node);
public:
    StudentLinkedList(): head(nullptr), tail(nullptr), size(0) {}
    StudentLinkedList(const StudentLinkedList& other); // copy constructor
    StudentLinkedList& operator=(const StudentLinkedList& other); // operator=
    ~StudentLinkedList(); // destructor
    bool isEmpty()const;
    void insertAtEnd(Student student);
    void deleteFirst();
    size_t getSize()const;
    void leave(size_t& currentMinute, std::ostream& output);
    Student& getFirstStudent()const;
    void insert(const Student& student, size_t maxGroupSize);
    void enter(StudentLinkedList& studentsInBar, size_t barCapacity, size_t currentMinute, size_t maxGroupSize, std::ostream& output);

    /// For debug and testing purposes
    std::string toString() const;
};


#endif //SIMPLE_CMAKE_TEMPLATE_STUDENTLINKEDLIST_H
