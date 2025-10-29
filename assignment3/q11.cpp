#include <iostream>
class Node {
public:
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insertAtBeginning(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
        std::cout << "Inserted " << data << std::endl;
    }

    void deleteNode(int key) {
        if (!head) {
            std::cout << "List is empty. Cannot delete." << std::endl;
            return;
        }

        if (head->data == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            std::cout << "Deleted " << key << std::endl;
            return;
        }

        Node *current = head;
        Node *prev = nullptr;

        while(current != nullptr) {
            prev = current;
            current = current->next;
        }
        
        if(current == nullptr) {
            printf("Node not found");
            return;
        }
        Node* temp = current->next;
        current->next = current->next->next;
        delete temp;
        std::cout << "Deleted " << key << std::endl;
    }

    void display() const {
        Node* current = head;
        if (!current) {
            std::cout << "List is empty." << std::endl;
            return;
        }
        std::cout << "Linked List: ";
        while (current) {
            std::cout << current->data;
            if (current->next) {
                std::cout << " -> ";
            }
            current = current->next;
        }
        std::cout << std::endl;
    }
    
    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
    }
};