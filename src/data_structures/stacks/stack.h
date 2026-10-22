#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    int size;

public:
    // Constructor
    Stack() : topNode(nullptr), size(0) {}

    // Destructor
    ~Stack() {
        clear();
    }

    // clear(): empties the stack
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }

    // isEmpty(): returns true if the stack is empty
    bool isEmpty() const {
        return topNode == nullptr;
    }

    // push(item): puts item at the top of the stack
    void push(const T& item) {
        Node* newNode = new Node(item);
        newNode->next = topNode;
        topNode = newNode;
        size++;
    }

    // pop(): removes and returns the topmost item in the stack
    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack underflow: cannot pop from an empty stack.");
        }
        Node* temp = topNode;
        T poppedValue = temp->data;
        topNode = topNode->next;
        delete temp;
        size--;
        return poppedValue;
    }

    // top(): returns the topmost item without removing it
    T top() const {
        if (isEmpty()) {
            throw runtime_error("Stack is empty: cannot retrieve top.");
        }
        return topNode->data;
    }

    // For debug/testing purposes: display the stack
    void display() const {
        Node* current = topNode;
        while (current) {
            cout << " | " << current->data << " | " << endl;
            current = current->next;
        }
        cout << endl;
    }

    // Get the number of items in the stack
    int getSize() const {
        return size;
    }

    void bubbleSort() {
        if (size < 2) return;

        // Step 1: Move stack elements to vector
        vector<T> tempVec;
        while (!isEmpty()) {
            tempVec.push_back(pop());
        }

        // Step 2: Bubble sort on vector
        for (int i = 0; i < tempVec.size() - 1; ++i) {
            for (int j = 0; j < tempVec.size() - i - 1; ++j) {
                if (tempVec[j] > tempVec[j + 1]) {
                    swap(tempVec[j], tempVec[j + 1]);
                }
            }
        }

        // Step 3: Push sorted elements back (largest on top)
        for (int i = 0; i < tempVec.size(); ++i) {
            push(tempVec[i]);
        }
    }


};

bool isBalancedExpression(const std::string& expr) {
    Stack<std::string> stack;

    for (size_t i = 0; i < expr.length(); ++i) {
        char ch = expr[i];

        // Handle comment start
        if (ch == '/' && i + 1 < expr.length() && expr[i + 1] == '*') {
            stack.push("/*");
            ++i; // skip next '*'
        }

        // Handle opening brackets
        else if (ch == '(' || ch == '{' || ch == '[' || ch == '<') {
            stack.push(std::string(1, ch));
        }

        // Handle quote
        else if (ch == '"') {
            if (!stack.isEmpty() && stack.top() == "\"") {
                stack.pop(); // close quote
            } else {
                stack.push("\"");
            }
        }

        // Handle comment end
        else if (ch == '*' && i + 1 < expr.length() && expr[i + 1] == '/') {
            if (!stack.isEmpty() && stack.top() == "/*") {
                stack.pop();
                ++i; // skip '/'
            } else {
                return false; // unmatched comment close
            }
        }

        // Handle closing brackets
        else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') {
            if (stack.isEmpty()) return false;
            std::string topChar = stack.pop();

            if ((ch == ')' && topChar != "(") ||
                (ch == '}' && topChar != "{") ||
                (ch == ']' && topChar != "[") ||
                (ch == '>' && topChar != "<")) {
                return false;
            }
        }
    }

    return stack.isEmpty();
}


void addLargeNumbers(const string& num1, const string& num2){
    Stack<int> stack1, stack2, sumStack;

    // Store digits of num1 in stack1
    for (char digit : num1) {
        if (isdigit(digit))
            stack1.push(digit - '0');
    }

    // Store digits of num2 in stack2
    for (char digit : num2) {
        if (isdigit(digit))
            stack2.push(digit - '0');
    }

    int carry = 0;

    while(!stack1.isEmpty() || !stack2.isEmpty()){
        int digit1 = stack1.isEmpty() ? 0 : stack1.pop();
        int digit2 = stack2.isEmpty() ? 0 : stack2.pop();

        int result = digit1 + digit2 + carry;
        sumStack.push(result % 10);
        carry = result / 10;

    }

    if (carry > 0){
        sumStack.push(carry);
    }

    cout << "sum: ";
    while(!sumStack.isEmpty()){
        cout << sumStack.pop();
    }

    cout << endl;

}


int evaluatePostfix(const string& postfix) {
    Stack<int> stack;

    for (char c : postfix){
        if(isdigit(c)){
            stack.push(c - '0');
        }else{
            int b = stack.pop();
            int a = stack.pop();
            switch(c){
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;

            }
        }
    }
    return stack.pop();
}


int precedence(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

bool isOperand(char c) {
    return isalnum(c);
}

string infixToPostfixArrows(const string& infix) {
    Stack<char> stack;
    string postfix;

    for (char c : infix) {
        if (isOperand(c)) {
            postfix += c;
        } else if (c == '(') {
            stack.push(c);
        } else if (c == ')') {
            while (!stack.isEmpty() && stack.top() != '(') {
                postfix += stack.pop();
            }
            stack.pop();  // pop '('
        } else if (isOperator(c)) {
            while (!stack.isEmpty() && precedence(c) <= precedence(stack.top())) {
                postfix += stack.pop();
            }
            stack.push(c);
        }
    }

    while (!stack.isEmpty()) {
        postfix += stack.pop();
    }

    return postfix;
}






string infixToPostfix(const string& infix) {
    Stack<char> opStack;
    string postfix = "";

    for(char c : infix){
        if(isspace(c)) continue;
        if(isalnum(c)){
            postfix += c;
        }
        else if(isOperator(c)){
            while(!opStack.isEmpty() && precedence(opStack.top()) >= precedence(c)){
                postfix += opStack.pop();
            }
            opStack.push(c);
        }
    }


    while(!opStack.isEmpty()){
        postfix += opStack.pop();
    }
    return postfix;

}



#endif // STACK_H
