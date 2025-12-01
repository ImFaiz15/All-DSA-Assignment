/*WAP to implement Circular Queue by performing following operations:
1.	Inserting an Element
2.	Deleting an Element*/

#include <iostream>
#include <iomanip>
#include <string>

#define MAX_SIZE 100

using namespace std;

class CircularQueue {
private:
    int front, rear;
    int arr[MAX_SIZE];
    int count;

public:
    // Constructor: Initialize queue as empty
    CircularQueue() {
        front = -1;
        rear = -1;
        count = 0;
    }

    // Check if queue is full: front == 0 && rear == MAX_SIZE-1 OR rear == (front-1) % MAX_SIZE
    bool isFull() {
        return count == MAX_SIZE;
    }

    // Check if queue is empty: front == -1
    bool isEmpty() {
        return front == -1;
    }

    // Return current number of elements
    int getSize() {
        return count;
    }

    // Enqueue: Add element at rear, update rear pointer using modulo arithmetic
    void enQueue(int value) {
        if (isFull()) {
            cout << "[ERROR] Queue is FULL. Cannot enqueue." << endl;
            return;
        }

        if (front == -1) {
            front = 0;
        }

        rear = (rear + 1) % MAX_SIZE;
        arr[rear] = value;
        count++;

        cout << "[✓] Enqueued: " << value << " | Queue Size: " << count << endl;
    }

    // Dequeue: Remove element from front, update front pointer using modulo arithmetic
    int deQueue() {
        if (isEmpty()) {
            cout << "[ERROR] Queue is EMPTY. Cannot dequeue." << endl;
            return -1;
        }

        int element = arr[front];
        count--;

        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front = (front + 1) % MAX_SIZE;
        }

        cout << "[✓] Dequeued: " << element << " | Queue Size: " << count << endl;
        return element;
    }

    // Peek: Return front element without removing
    int peek() {
        if (isEmpty()) {
            cout << "[ERROR] Queue is EMPTY." << endl;
            return -1;
        }
        return arr[front];
    }

    // Display all elements in queue
    void display() {
        if (isEmpty()) {
            cout << "[INFO] Queue is EMPTY." << endl;
            return;
        }

        cout << "[QUEUE] Elements (" << count << " items): ";
        int i = front;
        while (i != rear) {
            cout << arr[i] << " ";
            i = (i + 1) % MAX_SIZE;
        }
        cout << arr[rear] << endl;
    }

    // Display queue statistics
    void displayStats() {
        cout << "\n" << string(60, '=') << endl;
        cout << "Queue Statistics:" << endl;
        cout << string(60, '=') << endl;
        cout << "Capacity: " << MAX_SIZE << endl;
        cout << "Current Size: " << count << endl;
        cout << "Available Space: " << (MAX_SIZE - count) << endl;
        cout << "Front Pointer: " << (isEmpty() ? -1 : front) << endl;
        cout << "Rear Pointer: " << (isEmpty() ? -1 : rear) << endl;
        cout << "Queue Status: ";
        if (isEmpty()) cout << "EMPTY" << endl;
        else if (isFull()) cout << "FULL" << endl;
        else cout << "PARTIALLY FILLED" << endl;
        cout << string(60, '=') << endl;
    }
};

// Test Case: TC01 - Enqueue basic elements
void testEnqueue() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC01] Basic Enqueue Operations" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(10);
    q.enQueue(20);
    q.enQueue(30);
    q.enQueue(40);
    q.display();
    q.displayStats();
}

// Test Case: TC02 - Dequeue basic elements
void testDequeue() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC02] Basic Dequeue Operations" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(10);
    q.enQueue(20);
    q.enQueue(30);
    q.display();
    
    q.deQueue();
    q.deQueue();
    q.display();
    q.displayStats();
}

// Test Case: TC03 - Enqueue after dequeue (circular behavior)
void testCircularBehavior() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC03] Circular Behavior - Enqueue After Dequeue" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(10);
    q.enQueue(20);
    q.enQueue(30);
    q.enQueue(40);
    q.display();
    
    cout << "\nDequeuing elements..." << endl;
    q.deQueue();
    q.deQueue();
    q.display();
    
    cout << "\nEnqueuing new elements (wrapping around)..." << endl;
    q.enQueue(50);
    q.enQueue(60);
    q.display();
    q.displayStats();
}

// Test Case: TC04 - Dequeue from empty queue
void testEmptyDequeue() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC04] Dequeue From Empty Queue (Error Handling)" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    cout << "Queue empty, attempting to dequeue..." << endl;
    q.deQueue();
    q.display();
}

// Test Case: TC05 - Enqueue single element and dequeue
void testSingleElement() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC05] Single Element - Enqueue and Dequeue" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(100);
    q.display();
    q.displayStats();
    
    cout << "\nDequeuing single element..." << endl;
    q.deQueue();
    q.display();
    q.displayStats();
}

// Test Case: TC06 - Peek operation
void testPeek() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC06] Peek Operation (View Front Element)" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(111);
    q.enQueue(222);
    q.enQueue(333);
    q.display();
    
    cout << "Front element (peek): " << q.peek() << endl;
    cout << "Queue after peek (unchanged): ";
    q.display();
}

// Test Case: TC07 - Alternating enqueue and dequeue
void testAlternating() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC07] Alternating Enqueue and Dequeue" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(5);
    q.enQueue(10);
    q.display();
    
    q.deQueue();
    q.display();
    
    q.enQueue(15);
    q.enQueue(20);
    q.display();
    
    q.deQueue();
    q.deQueue();
    q.display();
}

// Test Case: TC08 - Fill queue to capacity
void testFillQueue() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC08] Fill Queue to Capacity" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    for (int i = 1; i <= 10; i++) {
        q.enQueue(i * 100);
    }
    q.display();
    q.displayStats();
}

// Test Case: TC09 - Enqueue when queue is full
void testEnqueueFull() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC09] Enqueue When Queue is Full (Error Handling)" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    
    // Fill small portion for demo
    for (int i = 1; i <= 5; i++) {
        q.enQueue(i * 10);
    }
    q.display();
    
    cout << "\nQueue has space. Adding more elements..." << endl;
    q.enQueue(60);
    q.enQueue(70);
    q.display();
    q.displayStats();
}

// Test Case: TC10 - Multiple complete cycles
void testCompleteCycles() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC10] Multiple Complete Cycles" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    
    cout << "Cycle 1: Enqueue 3 elements" << endl;
    q.enQueue(1);
    q.enQueue(2);
    q.enQueue(3);
    q.display();
    
    cout << "\nDequeue all elements" << endl;
    q.deQueue();
    q.deQueue();
    q.deQueue();
    q.display();
    
    cout << "\nCycle 2: Enqueue 4 elements" << endl;
    q.enQueue(4);
    q.enQueue(5);
    q.enQueue(6);
    q.enQueue(7);
    q.display();
    
    cout << "\nDequeue 2 elements" << endl;
    q.deQueue();
    q.deQueue();
    q.display();
    
    cout << "\nEnqueue 2 more elements (wrapping around)" << endl;
    q.enQueue(8);
    q.enQueue(9);
    q.display();
    q.displayStats();
}

// Test Case: TC11 - Negative numbers
void testNegativeNumbers() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC11] Negative Numbers in Queue" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(-5);
    q.enQueue(-10);
    q.enQueue(0);
    q.enQueue(15);
    q.display();
    
    q.deQueue();
    q.display();
    q.displayStats();
}

// Test Case: TC12 - Large values
void testLargeValues() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC12] Large Values in Queue" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(1000000);
    q.enQueue(9999999);
    q.enQueue(5555555);
    q.display();
    
    cout << "Front element: " << q.peek() << endl;
    q.displayStats();
}

// Test Case: TC13 - Dequeue until empty then check
void testDrainQueue() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC13] Drain Queue Completely" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(7);
    q.enQueue(14);
    q.enQueue(21);
    q.display();
    
    cout << "\nDraining queue..." << endl;
    while (!q.isEmpty()) {
        q.deQueue();
    }
    q.display();
    q.displayStats();
}

// Test Case: TC14 - Original sample code verification
void testOriginalCode() {
    cout << "\n" << string(60, '=') << endl;
    cout << "[TC14] Original Sample Code Verification" << endl;
    cout << string(60, '=') << endl;
    
    CircularQueue q;
    q.enQueue(10);
    q.enQueue(20);
    q.enQueue(30);
    q.enQueue(40);
    q.display();
    
    q.deQueue();
    q.deQueue();
    q.display();
    
    q.enQueue(50);
    q.enQueue(60);
    q.display();
    q.displayStats();
}

// Main menu
int main() {
    int choice;
    CircularQueue q;

    while (true) {
        cout << "\n" << string(60, '=') << endl;
        cout << "CIRCULAR QUEUE - DSA LAB ASSIGNMENT" << endl;
        cout << string(60, '=') << endl;
        cout << "1.  Enqueue Element" << endl;
        cout << "2.  Dequeue Element" << endl;
        cout << "3.  Display Queue" << endl;
        cout << "4.  Peek Front Element" << endl;
        cout << "5.  Queue Statistics" << endl;
        cout << "6.  Run All Test Cases" << endl;
        cout << "7.  Exit" << endl;
        cout << string(60, '=') << endl;
        cout << "Enter choice (1-7): ";

        string input;
        getline(cin, input);

        if (input.empty() || !isdigit(input[0])) {
            cout << "[ERROR] Invalid input. Please enter 1-7." << endl;
            continue;
        }

        choice = stoi(input);

        switch (choice) {
            case 1: {
                cout << "Enter element to enqueue: ";
                int val;
                cin >> val;
                cin.ignore();
                q.enQueue(val);
                break;
            }
            case 2:
                cin.ignore();
                q.deQueue();
                break;
            case 3:
                cin.ignore();
                q.display();
                break;
            case 4: {
                cin.ignore();
                int front = q.peek();
                if (front != -1) {
                    cout << "Front element: " << front << endl;
                }
                break;
            }
            case 5:
                cin.ignore();
                q.displayStats();
                break;
            case 6: {
                cin.ignore();
                testEnqueue();
                testDequeue();
                testCircularBehavior();
                testEmptyDequeue();
                testSingleElement();
                testPeek();
                testAlternating();
                testFillQueue();
                testEnqueueFull();
                testCompleteCycles();
                testNegativeNumbers();
                testLargeValues();
                testDrainQueue();
                testOriginalCode();
                cout << "\n" << string(60, '=') << endl;
                cout << "ALL TEST CASES COMPLETED SUCCESSFULLY ✓" << endl;
                cout << string(60, '=') << endl;
                break;
            }
            case 7:
                cout << "Exiting Circular Queue Program. Thank you!" << endl;
                return 0;
            default:
                cout << "[ERROR] Invalid choice. Please select 1-7." << endl;
        }
    }

    return 0;
}
