#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

#include <iostream>
#include <stdexcept>
#include <memory>
#include <functional>

template <typename T>
class SingleLinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* last;
    int count;

    Node* merge(Node* left, Node* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->data <= right->data) {
            left->next = merge(left->next, right);
            return left;
        } else {
            right->next = merge(left, right->next);
            return right;
        }
    }

    void split(Node* source, Node** front, Node** back) {
        if (!source || !source->next) {
            *front = source;
            *back = nullptr;
            return;
        }

        Node* slow = source;
        Node* fast = source->next;

        while (fast) {
            fast = fast->next;
            if (fast) {
                slow = slow->next;
                fast = fast->next;
            }
        }

        *front = source;
        *back = slow->next;
        slow->next = nullptr;
    }

    void mergeSort(Node** headRef) {
        Node* h = *headRef;
        if (!h || !h->next)
            return;

        Node* left;
        Node* right;

        split(h, &left, &right);
        mergeSort(&left);
        mergeSort(&right);

        *headRef = merge(left, right);
    }

public:
    // Constructor
    SingleLinkedList() : head(nullptr), last(nullptr), count(0) {}

    // Destructor
    ~SingleLinkedList() {
        clear();
    }

    // Copy constructor
    SingleLinkedList(const SingleLinkedList& other) : head(nullptr), last(nullptr), count(0) {
        for (Node* curr = other.head; curr != nullptr; curr = curr->next) {
            push_back(curr->data);
        }
    }

    // Move constructor
    SingleLinkedList(SingleLinkedList&& other) noexcept
        : head(other.head), last(other.last), count(other.count) {
        other.head = nullptr;
        other.last = nullptr;
        other.count = 0;
    }

    // Copy assignment operator
    SingleLinkedList& operator=(const SingleLinkedList& other) {
        if (this != &other) {
            SingleLinkedList temp(other);
            std::swap(head, temp.head);
            std::swap(last, temp.last);
            std::swap(count, temp.count);
        }
        return *this;
    }

    // Move assignment operator
    SingleLinkedList& operator=(SingleLinkedList&& other) noexcept {
        if (this != &other) {
            clear();
            head = other.head;
            last = other.last;
            count = other.count;
            other.head = nullptr;
            other.last = nullptr;
            other.count = 0;
        }
        return *this;
    }

    void push_front(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
        if (!last) last = newNode;
        ++count;
    }

    void push_back(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = last = newNode;
        } else {
            last->next = newNode;
            last = newNode;
        }
        ++count;
    }

    void insert_at(int index, const T& value) {
        if (index < 0 || index > count) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            push_front(value);
            return;
        }
        if (index == count) {
            push_back(value);
            return;
        }

        Node* curr = head;
        for (int i = 0; i < index - 1; ++i) {
            curr = curr->next;
        }

        Node* newNode = new Node(value);
        newNode->next = curr->next;
        curr->next = newNode;
        ++count;
    }

    bool pop_front() {
        if (!head) return false;
        Node* temp = head;
        head = head->next;
        delete temp;
        if (!head) last = nullptr;
        --count;
        return true;
    }

    bool pop_back() {
        if (!head) return false;
        if (!head->next) {
            delete head;
            head = last = nullptr;
            count = 0;
            return true;
        }

        Node* curr = head;
        while (curr->next != last) {
            curr = curr->next;
        }

        delete last;
        last = curr;
        last->next = nullptr;
        --count;
        return true;
    }

    bool remove(const T& value) {
        if (!head) return false;

        if (head->data == value) {
            return pop_front();
        }

        Node* curr = head;
        while (curr->next && curr->next->data != value) {
            curr = curr->next;
        }

        if (!curr->next) return false;

        Node* temp = curr->next;
        curr->next = temp->next;
        if (temp == last) {
            last = curr;
        }
        delete temp;
        --count;
        return true;
    }

    bool contains(const T& value) const {
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            if (curr->data == value) return true;
        }
        return false;
    }

    int indexOf(const T& value) const {
        int index = 0;
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            if (curr->data == value) return index;
            ++index;
        }
        return -1;
    }

    void forEach(const std::function<void(T&)>& func) {
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            func(curr->data);
        }
    }

    void forEachConst(const std::function<void(const T&)>& func) const {
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            func(curr->data);
        }
    }

    void print() const {
        for (Node* curr = head; curr != nullptr; curr = curr->next) {
            std::cout << curr->data;
            if (curr->next) std::cout << " -> ";
        }
        std::cout << " -> nullptr" << std::endl;
    }

    void clear() {
        while (pop_front());
    }

    bool empty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }

    void sort() {
        mergeSort(&head);
        // Update last pointer
        if (head) {
            last = head;
            while (last->next) {
                last = last->next;
            }
        }
    }

    void bubbleSort() {
        if (!head || !head->next) return;

        bool swapped;
        do {
            swapped = false;
            Node* curr = head;
            Node* prev = nullptr;

            while (curr && curr->next) {
                if (curr->data > curr->next->data) {
                    Node* temp = curr->next;
                    curr->next = temp->next;
                    temp->next = curr;

                    if (prev) {
                        prev->next = temp;
                    } else {
                        head = temp;
                    }

                    if (!curr->next) {
                        last = curr;
                    }

                    prev = temp;
                    swapped = true;
                } else {
                    prev = curr;
                    curr = curr->next;
                }
            }
        } while (swapped);
    }

    T& at(int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        Node* curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }

    const T& at(int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }
        Node* curr = head;
        for (int i = 0; i < index; ++i) {
            curr = curr->next;
        }
        return curr->data;
    }

    T& front() {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    const T& front() const {
        if (!head) throw std::runtime_error("List is empty");
        return head->data;
    }

    T& back() {
        if (!last) throw std::runtime_error("List is empty");
        return last->data;
    }

    const T& back() const {
        if (!last) throw std::runtime_error("List is empty");
        return last->data;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* curr = head;
        last = head;  // Current head will become last

        while (curr) {
            Node* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        head = prev;
    }
};

#endif // SINGLE_LINKED_LIST_H
