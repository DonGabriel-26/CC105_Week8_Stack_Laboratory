
#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack
{
private:
    struct Node
    {
        T data;
        Node* next;
    };

    Node* top;
    int count;

public:
    Stack()
    {
        top = nullptr;
        count = 0;
    }

    ~Stack()
    {
        while (top != nullptr)
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }

        count = 0;
    }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void push(T value)
    {
        Node* newNode = new Node;

        newNode->data = value;
        newNode->next = top;

        top = newNode;
        count++;
    }

    bool pop(T& value)
    {
        if (isEmpty())
        {
            return false;
        }

        Node* temp = top;

        value = temp->data;
        top = top->next;

        delete temp;
        count--;

        return true;
    }

    bool peek(T& value) const
    {
        if (isEmpty())
        {
            return false;
        }

        value = top->data;

        return true;
    }

    bool isEmpty() const
    {
        return top == nullptr;
    }

    int size() const
    {
        return count;
    }
};

#endif

