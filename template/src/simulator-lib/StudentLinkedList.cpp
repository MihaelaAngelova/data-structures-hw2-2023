#include "StudentLinkedList.h"

bool StudentLinkedList::isEmpty()const {
    return !head;
}

void StudentLinkedList::insertAt(size_t pos, Student student) {
    if(pos == 0) {
        if(isEmpty()) {
            Node* node = new Node{student, nullptr};
            head = node;
            tail = node;
        } else {
            Node* node = new Node{student, head};
            tail = head;
            head = node;
        }
    } else {
        if(pos > size) {
            throw std::runtime_error("Index out of range!");
        }
        if(pos == size) {
            tail->next = new Node{student, nullptr};
            tail = tail->next;
        } else {
            Node* temp = head;
            while(pos-- > 1) { // one index before the one we want to insert at
                temp = temp->next;
            }
            temp->next = new Node{student, temp->next};
        }
    }
    size++;
}

void StudentLinkedList::insertAtEnd(Student student) {
    insertAt(size, student);
}

void StudentLinkedList::deleteFirst() {
    if(isEmpty()) {
        throw std::runtime_error("Empty list!");
    }

    if(head->next) {
        Node* temp = head->next;
        delete head;
        head = temp;
    } else {
        delete head;
        head = nullptr;
        tail = nullptr;
    }

    size--;
}

size_t StudentLinkedList::getSize()const {
    return size;
}

void StudentLinkedList::leave(size_t& currentMinute, std::ostream& output) {
    if(isEmpty()) return;
    Node* temp = head;
    while(temp) {
        Node* next = temp->next;
        if(temp->getStudent().getLeavingMinute() == currentMinute) {
            output << currentMinute  << " " << temp->getStudent().getFN() << " exit" << std::endl;
            deleteNode(temp);
        }
        temp = next;
    }
}

Student& StudentLinkedList::getFirstStudent()const {
    return head->getStudent();
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
            if(student.getMajor() == temp->getStudent().getMajor()) {
                size_t count = 1;
                while(temp->next && (student.getMajor() == temp->next->getStudent().getMajor())) {
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
    Major major = head->getStudent().getMajor();
    if(size == 1) {
        temp->student.setLeavingMinute(currentMinute + temp->getStudent().getDuration());
        other.insertAtEnd(temp->getStudent());
        output << currentMinute << " " << temp->getStudent().getFN() << " enter" << std::endl;
        deleteFirst();
        return;
    }
    while(temp && other.getSize() < otherCapacity) { // for every group in the current list (queue of students waiting to enter the bar)
        Node* headOfGroup = temp;
        major = temp->getStudent().getMajor();
        // save the first node of the current group
        while(temp->next && count < maxGroupSize) { // find current group size
            temp = temp->next;
            if(temp->getStudent().getMajor() == major) {
                count++;
            }
        }
        if(count <= otherCapacity - other.getSize()) { // if there is enough space
            temp = headOfGroup;
            while(count-- > 0) {
                Node* next = temp->next;
                temp->student.setLeavingMinute(currentMinute + temp->getStudent().getDuration());
                other.insertAtEnd(temp->getStudent());
                output << currentMinute << " " << temp->getStudent().getFN() << " enter" << std::endl;
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
