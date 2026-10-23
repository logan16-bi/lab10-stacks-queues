/*
 * Course: COEN 2220 - Programming 2
 * Name: Logan N. Ramirez Rodriguez
 * Lab: Lab 10 - Stacks & Queues
 * Description: Practice - a dynamic stack of active function calls
 * Due date: 10/23/2026
 */

#include <iostream>
#include <string>
using namespace std;

class FunctionCallStack
{
private:
    struct Node
    {
        string functionName;
        Node *next;
    };

    Node *top;

public:
    FunctionCallStack();
    ~FunctionCallStack();
    bool isEmpty() const;
    void push(const string& newFunctionName);
    bool pop(string& removedFunctionName);
    bool peek(string& topFunctionName) const;
};

int main()
{
    cout << boolalpha;

    FunctionCallStack callStack;
    string functionName;

    callStack.push("main");
    callStack.push("loadSchedule");
    callStack.push("formatSchedule");

    callStack.peek(functionName);
    cout << "Current function: " << functionName << endl;

    callStack.pop(functionName);
    cout << "Returned from function: " << functionName << endl;
    callStack.pop(functionName);
    cout << "Returned from function: " << functionName << endl;
    callStack.pop(functionName);
    cout << "Returned from function: " << functionName << endl;

    cout << "Stack empty: " << callStack.isEmpty() << endl;

    bool popSucceeded = callStack.pop(functionName);
    cout << "Pop from empty stack succeeded: " << popSucceeded << endl;

    return 0;
}

FunctionCallStack::FunctionCallStack()
{
    top = nullptr;
}

FunctionCallStack::~FunctionCallStack()
{
    while (top != nullptr)
    {
        Node *nodeToDelete = top;
        top = top->next;
        delete nodeToDelete;
    }
}

bool FunctionCallStack::isEmpty() const
{
    return top == nullptr;
}

void FunctionCallStack::push(const string& newFunctionName)
{
    Node *newNode = new Node;
    newNode->functionName = newFunctionName;
    newNode->next = top;
    top = newNode;
}

bool FunctionCallStack::pop(string& removedFunctionName)
{
    bool removed = false;

    if (top != nullptr)
    {
        Node *nodeToDelete = top;
        removedFunctionName = top->functionName;
        top = top->next;
        delete nodeToDelete;
        removed = true;
    }

    return removed;
}

bool FunctionCallStack::peek(string& topFunctionName) const
{
    bool found = false;

    if (top != nullptr)
    {
        topFunctionName = top->functionName;
        found = true;
    }

    return found;
}

/*
 * Analysis Answers
 *
 * D1 — Adding formatSchedule
 * When push("formatSchedule") executes, what must newNode->next receive before top
 * changes? Explain why reversing those two assignments would lose the previous top.
 * Answer:
 * newNode->next has to get the old top first, so the new node stays connected to the
 * rest of the stack. If top is changed first, the old top is lost and the rest of
 * the nodes can no longer be reached.
 *
 * D2 — Returning from a function
 * After main, loadSchedule, and formatSchedule are pushed in that order, list the
 * order in which three successful pop calls must return their names. Explain LIFO.
 * Answer:
 * They come out as formatSchedule, loadSchedule and main. LIFO means the last one
 * pushed is the first one to come out, so the most recent function returns first and
 * main, the first one pushed, returns last.
 *
 * D3 — Destructor order
 * Why must the destructor save a next-node address before deleting the current node?
 * Answer:
 * Once a node is deleted its memory is gone, so the destructor can't use it to find
 * the next one. The next address has to be saved first so it can keep going through
 * the rest of the nodes without losing them.
 *
 */
