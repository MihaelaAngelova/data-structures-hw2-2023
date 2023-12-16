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
    if(isEmpty()) {
        Node* node = new Node{student, nullptr};
        head = node;
        tail = node;
        size++;
    } else {
        Node* temp = head;
        while(temp) {
            if(student.getMajor() == temp->student.getMajor()) {
                size_t count = 1;
                while(temp->next && (student.getMajor() == temp->next->student.getMajor())) {
                    count++;
                    temp = temp->next;
                }
                if(count < maxGroupSize) {
                    temp->next = new Node{student, temp->next};
                    if(tail == temp) {
                        tail = temp->next;
                    }
                    size++;
                    return;
                }
            }
            temp = temp->next;
        }
        tail->next = new Node{student, nullptr};
        tail = tail->next;
        size++;
    }
}

void StudentLinkedList::enter(StudentLinkedList& other, size_t otherCapacity, size_t currentMinute, size_t maxGroupSize, std::ostream& output) {
    if(isEmpty()) return;
    size_t count = 1;
    Node* temp = head;
    if(size == 1) {
        temp->student.setLeavingMinute(currentMinute + temp->student.getDuration());
        other.insertAtEnd(temp->student);
        output << currentMinute << " " << temp->student.getFN() << " enter" << std::endl;
        deleteFirst();
        return;
    }
    while(temp && other.getSize() < otherCapacity) { // for every group in the current list (queue of students waiting to enter the bar)
        Node* headOfGroup = temp;
        Major major = temp->student.getMajor();
        // save the first node of the current group
        while(temp->next && count < maxGroupSize) { // find current group size
            temp = temp->next;
            if(temp->student.getMajor() == major) {
                count++;
            }
        }

        if(count <= otherCapacity - other.getSize()) { // if there is enough space
            temp = headOfGroup;
            while(count-- > 0) {
                Node* next = temp->next;
                temp->student.setLeavingMinute(currentMinute + temp->student.getDuration());
                other.insertAtEnd(temp->student);
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
    if(!head) {
        return;
    }

    if(!node) {
        return;
    }

    Node* temp = head;
    if(head == node) {
        temp = head->next;
        delete head;
        head = temp;
        if (!head) {
            tail = nullptr;
        }
        size--;
        return;
    }

    while(temp->next) {
        if(temp->next == node) {
            if(tail == temp->next) {
                tail = temp;
            }
            temp->next = temp->next->next;
            delete node;
            size--;
            return;
        }
        temp = temp->next;
    }
}
