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
 * When the queue is empty, front and rear are both nullptr. The first student is
 * the first one to be served and also the last one in line, so the new node is both
 * the front and the rear. If only rear is set, front stays nullptr and the queue
 * still looks empty. If only front is set, rear stays nullptr, so the next enqueue
 * thinks the queue is empty and the new node does not get linked behind the first one.
 *
 * E2 — Last departure
 * After dequeue removes the only remaining node, what must happen to rear and why?
 * Answer:
 * rear must become nullptr. When the last node is removed, front becomes nullptr
 * but rear still points to the node that was deleted. That would be a dangling
 * pointer. Setting rear to nullptr makes the empty queue consistent, so the next
 * enqueue treats it like a first arrival instead of using the deleted node.
 *
 * E3 — FIFO evidence
 * List the expected service order for TU-301, TU-318, and TU-327. Explain why this
 * differs from the return order of the function-call stack in Part D.
 * Answer:
 * The service order is TU-301, TU-318, TU-327, the same order they arrived. This
 * is FIFO: the queue removes from front, where the oldest student is. The
 * function-call stack returned formatSchedule, loadSchedule, main, which is the
 * reverse of how they were pushed. A stack removes from top, where the newest
 * item is, so the last one in comes out first.
 *
 */
