#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>
#include <string>
using namespace std;

// Exception class for invalid queue operations
class InvalidQueueOperation : public exception {
public:
    const char* what() const noexcept override {
        return "Invalid queue operation: Queue is empty.";
    }
};


struct Node {
    int x, y;
    Node* next;
    Node(int xVal, int yVal) : x(xVal), y(yVal), next(nullptr) {}
};

// Template Queue class (linked-list implementation)

class Queue {
private:
    Node* front = nullptr;
    Node* rear = nullptr; 

public:
    // Default constructor
    Queue() : front(nullptr), rear(nullptr) {}

    // Destructor
    ~Queue() {
        while (!IsEmpty()) {
            //Dequeue();
        }
    }

    // Add item to the back of the queue
    void Enqueue(const int x, const int y) {
        Node* newNode = new Node(x, y);
        if (IsEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        
    }

    

    // Check if queue is empty
    bool IsEmpty() const {
        return front == nullptr;
    }
};

#endif
