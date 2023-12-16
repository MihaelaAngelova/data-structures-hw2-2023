#include "StudentLinkedList.h"

bool StudentLinkedList::isEmpty()const {
    return !head;
}

void StudentLinkedList::insertAtEnd(Student student) {
    if(isEmpty()) {
        head = new Node{student, nullptr};
        tail = head;
    } else {
        tail->next = new Node{student, nullptr};
        tail = tail->next;
    }
    size++;
}

void StudentLinkedList::deleteFirst() {
    deleteNode(head);
}

size_t StudentLinkedList::getSize()const {
    return size;
}

void StudentLinkedList::leave(size_t& currentMinute, std::ostream& output) {
    if(isEmpty()) return;
    Node* temp = head;
    while(temp) {
        Node* next = temp->next;
        if(temp->student.getLeavingMinute() == currentMinute) {
            output << currentMinute  << " " << temp->student.getFN() << " exit" << std::endl;
            deleteNode(temp);
        }
        temp = next;
    }
}

Student& StudentLinkedList::getFirstStudent()const {
    return head->student;
}

void StudentLinkedList::insert(const Student& student, size_t maxGroupSize){
    Node* temp = head;
    while(temp) { // find where to insert the student
        if(student.getMajor() == temp->student.getMajor()) { // found a student with the same major
            size_t count = 1;
            while(temp->next && (student.getMajor() == temp->next->student.getMajor())) {
                // find the count of the consecutive students with the same major
                count++;
                temp = temp->next;
            }
            if(count < maxGroupSize) { // put the student behind them if there is enough space for him
                temp->next = new Node{student, temp->next};
                if(tail == temp) { // update tail
                    tail = temp->next;
                }
                size++;
                return;
            }
        }
        temp = temp->next;
    }
    insertAtEnd(student); // if there is still no available group, just put the student at the end of the list
}

void StudentLinkedList::enter(StudentLinkedList& studentsInBar, size_t barCapacity, size_t currentMinute, size_t maxGroupSize, std::ostream& output) {
    // "this" is used for the studentsWaiting list
    size_t count = 1;
    Node* temp = head;

    while(temp && studentsInBar.getSize() < barCapacity) { // for every group in the current list (queue of students waiting to enter the bar)
        Node* headOfGroup = temp;
        Major major = temp->student.getMajor();
        // save the first node of the current group
        while(temp->next && count < maxGroupSize) { // find current group size
            temp = temp->next;
            if(temp->student.getMajor() == major) {
                count++;
            }
        }

        if(count <= barCapacity - studentsInBar.getSize()) { // if there is enough space
            temp = headOfGroup;
            while(count-- > 0) { // insert the group into the bar list AND delete it from the current list of waiting students
                Node* next = temp->next;
                temp->student.setLeavingMinute(currentMinute + temp->student.getDuration());
                studentsInBar.insertAtEnd(temp->student);
                output << currentMinute << " " << temp->student.getFN() << " enter" << std::endl;
                deleteNode(temp);
                temp = next;
            }
        } else {
            temp = temp->next;
        }
        count = 1;
    }
}

void StudentLinkedList::deleteNode(Node* node) {
    if (!head || !node) return;

    if (head == node) {
        head = head->next;
        if (!head) {
            tail = nullptr;
        }
    } else {
        Node* temp = head;
        while (temp->next && temp->next != node) {
            temp = temp->next;
        }

        if (temp->next) {
            temp->next = temp->next->next;
            if (tail == node) {
                tail = temp;
            }
        }
    }
    delete node;
    size--;
}
