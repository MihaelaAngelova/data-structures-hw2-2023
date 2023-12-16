#ifndef SIMPLE_CMAKE_TEMPLATE_STUDENTLINKEDLIST_H
#define SIMPLE_CMAKE_TEMPLATE_STUDENTLINKEDLIST_H

#include "Student.h"
#include <iostream>

struct Node {
    Student student;
    Node* next;
    Node(Student student, Node* next): student(student), next(next) {}
    Student& getStudent() {
        return student;
    }
};

class StudentLinkedList {
private:
    Node* head;
    Node* tail;
    size_t size;
public:
    StudentLinkedList(): head(nullptr), tail(nullptr), size(0) {}
    bool isEmpty()const;
    void insertAtEnd(Student student);
    void deleteFirst();
    size_t getSize()const;
    void leave(size_t& currentMinute, std::ostream& output);
    Student& getFirstStudent()const;
    void insert(const Student& student, size_t maxGroupSize);
    void enter(StudentLinkedList& other, size_t otherCapacity, size_t currentMinute, size_t maxGroupSize, std::ostream& output);
    void deleteNode(Node* node);
};


#endif //SIMPLE_CMAKE_TEMPLATE_STUDENTLINKEDLIST_H
