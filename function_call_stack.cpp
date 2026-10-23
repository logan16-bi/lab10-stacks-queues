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
 * newNode->next must receive the old top, which is the loadSchedule node, before
 * top changes. top is the only pointer that knows where loadSchedule is. If I did
 * top = newNode first, the old address would be gone, and then newNode->next = top
 * would make the new node point to itself. loadSchedule and main would be lost in
 * memory and the stack could not return to them.
 *
 * D2 — Returning from a function
 * After main, loadSchedule, and formatSchedule are pushed in that order, list the
 * order in which three successful pop calls must return their names. Explain LIFO.
 * Answer:
 * The three pops return formatSchedule, then loadSchedule, then main. LIFO means
 * last in, first out. formatSchedule was pushed last, so it is at top and leaves
 * first. After each pop, top moves to the next node, so the next most recent
 * function is the one that leaves. main was pushed first, so it leaves last.
 *
 * D3 — Destructor order
 * Why must the destructor save a next-node address before deleting the current node?
 * Answer:
 * After delete, the node's memory is released, so reading its next pointer is not
 * safe. The address of the next node has to be saved before the delete (in this
 * code, top moves to top->next first). Without that, the destructor loses the rest
 * of the nodes and cannot release them, and that is a memory leak.
 *
 */
