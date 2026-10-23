/*
 * Course: COEN 2220 - Programming 2
 * Name: Logan N. Ramirez Rodriguez
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic queue of tutoring requests
 * Due date: 10/23/2026
 */

#include <iostream>
#include <string>
using namespace std;

class TutoringQueue
{
private:
    struct Node
    {
        string studentId; // Store one student waiting for tutoring.
        Node *next;       // Point to the student immediately behind this one.
    };

    Node *front; // Point to the student who must be served next.
    Node *rear;  // Point to the student most recently added.

public:
    TutoringQueue()
    {
        front = nullptr;
        rear = nullptr;
    }

    ~TutoringQueue()
    {
        while (front != nullptr)
        {
            Node *nodeToDelete = front;
            front = front->next; // Advance before releasing the current node.
            delete nodeToDelete;
        }

        rear = nullptr;
    }

    bool isEmpty() const
    {
        return front == nullptr;
    }

    void enqueue(const string& newStudentId);
    bool dequeue(string& servedStudentId);
};

int main()
{
    cout << boolalpha;

    TutoringQueue tutoringQueue;
    string studentId;

    tutoringQueue.enqueue("TU-301");
    tutoringQueue.enqueue("TU-318");
    tutoringQueue.enqueue("TU-327");

    tutoringQueue.dequeue(studentId);
    cout << "Served student: " << studentId << endl;
    tutoringQueue.dequeue(studentId);
    cout << "Served student: " << studentId << endl;

    tutoringQueue.dequeue(studentId);
    cout << "Served student: " << studentId << endl;
    cout << "Queue empty: " << tutoringQueue.isEmpty() << endl;

    tutoringQueue.enqueue("TU-340");
    tutoringQueue.dequeue(studentId);
    cout << "Served student after empty queue: " << studentId << endl;

    return 0;
}

void TutoringQueue::enqueue(const string& newStudentId)
{
    Node *newNode = new Node;
    newNode->studentId = newStudentId;
    newNode->next = nullptr;

    if (rear == nullptr)
    {
        front = newNode;
        rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }
}

bool TutoringQueue::dequeue(string& servedStudentId)
{
    bool served = false;

    if (front != nullptr)
    {
        Node *nodeToDelete = front;
        servedStudentId = front->studentId;
        front = front->next;

        if (front == nullptr)
        {
            rear = nullptr;
        }

        delete nodeToDelete;
        served = true;
    }

    return served;
}

/*
 * Analysis Answers
 *
 * E1 — First arrival
 * Why must the first call to enqueue assign newNode to both front and rear?
 * Answer:
 * When the queue is empty there is no front or rear yet, so the first node is both
 * the first and the last one in line. Both pointers have to point to it, otherwise
 * the queue would not work correctly for the next enqueue.
 *
 * E2 — Last departure
 * After dequeue removes the only remaining node, what must happen to rear and why?
 * Answer:
 * rear has to become nullptr. If the last node is removed and rear stays the same,
 * it would point to a node that was already deleted. Setting it to nullptr leaves
 * the queue clean and empty, ready for the next arrival.
 *
 * E3 — FIFO evidence
 * List the expected service order for TU-301, TU-318, and TU-327. Explain why this
 * differs from the return order of the function-call stack in Part D.
 * Answer:
 * The order is TU-301, TU-318 and TU-327, the same order they arrived. In the stack
 * the last one in was the first one out, but in the queue the first one in is the
 * first one out, because a queue serves from the front and a stack removes from the
 * top.
 *
 */
