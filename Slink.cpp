#include <bits/stdc++.h>
using namespace std;

template<class E>
struct Node {
    E element;
    Node<E> *next;
    Node(E e = E(), Node<E> *n = nullptr) : element(e), next(n) {}
};

template<class E>
class SList {
protected:
    Node<E> *head;
    Node<E> *tail;
    int size;

public:
    SList() : head(nullptr), tail(nullptr), size(0) {};
    void print() const {
        for (Node<E> *p = head; p != nullptr; p = p->next) {
            cout << p->element << " ";
        }
        cout << endl;
    }

    Node<E>* & getLink(int i) {
        if (i < 0 || i >= size) {
            cout<<"Index out of range";
        }
        Node<E> *current = head;
        for (int j = 0; j < i; ++j) {
            current = current->next;
        }
        return current;
    }

    Node<E>* & searchLink(const E &e) {
        Node<E> *current = head;
        while (current != nullptr && current->element != e) {
            current = current->next;
        }
        return current;
    }

    bool find(const E &e) const {
        Node<E> *current = head;
        while (current != nullptr) {
            if (current->element == e) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void addFirst(const E &e) {
        Node<E> *v = new Node<E>(e);
        v->next = head;
        head = v;
        if (size == 0) {
            tail = v;
        }
        size++;
    }

    void addLast(const E &e) {
        Node<E> *v = new Node<E>(e);
        if (size == 0) {
            head = tail = v;
        } else {
            tail->next = v;
            tail = v;
        }
        size++;
    }

    void add(int i, const E &e) {
        if (i < 0 || i > size) {
            cout<<"Index out of range";
        }

        if (i == 0) {
            addFirst(e);
        } else if (i == size) {
            addLast(e);
        } else {
            Node<E> *prev = getLink(i - 1);
            Node<E> *v = new Node<E>(e);
            v->next = prev->next;
            prev->next = v;
            size++;
        }
    }

    void removeFirst() {
        if (!head) {
            cout<<"Danh sach rong";
        }
        Node<E> *t = head;
        head = head->next;
        delete t;
        size--;
        if (size == 0) {
            tail = nullptr;
        }
    }

    void removeLast() {
        if (!head) {
            cout<<"Danh sach rong";
        }
        if (size == 1) {
            removeFirst();
        } else {
            Node<E> *current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            current->next = nullptr;
            tail = current;
            size--;
        }
    }

    void remove(int i) {
        if (i < 0 || i >= size) {
            cout<<"Index out of range";
        }

        if (i == 0) {
            removeFirst();
        } else if (i == size - 1) {
            removeLast();
        } else {
            Node<E> *prev = getLink(i - 1);
            Node<E> *t = prev->next;
            prev->next = t->next;
            delete t;
            size--;
        }
    }

    void removeKey(const E &e) {
        if (!head) {
            return;
        }
        if (head->element == e) {
            removeFirst();
        } else {
            Node<E> *prev = head;
            Node<E> *current = head->next;
            while (current != nullptr) {
                if (current->element == e) {
                    prev->next = current->next;
                    delete current;
                    size--;
                    return;
                }
                prev = current;
                current = current->next;
            }
        }
    }

    void replace(int i, const E &e) {
        if (i < 0 || i >= size) {
            cout<<"Index out of range";
        }
        Node<E> *node = getLink(i);
        node->element = e;
    }

    void replaceKey(const E &key) {
        Node<E> *current = head;
        while (current != nullptr) {
            if (current->element == key) {
                current->element = key;
            }
            current = current->next;
        }
    }

    void clear() {
        while (head != nullptr) {
            Node<E> *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        size = 0;
    }

    virtual ~SList() {
        clear();
    }

    E front() const {
        if (!head) {
            cout<<"Danh sach rong";
        }
        return head->element;
    }

    E back() {
        if (!tail) {
           cout<<"Danh sach rong";
        }
        return tail->element;
    }

    E getElement(int i) {
        if (i < 0 || i >= size) {
           cout<<"Index out of range";
        }
        Node<E> *node = getLink(i);
        return node->element;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    SList(const SList<E> &other) : head(nullptr), tail(nullptr), size(0) {
        for (Node<E> *current = other.head; current != nullptr; current = current->next) {
            addLast(current->element);
        }
    }

    const SList<E> & operator= (const SList<E> &other) {
        if (this == &other) {
            return *this;
        }

        clear();
        for (Node<E> *current = other.head; current != nullptr; current = current->next) {
            addLast(current->element);
        }

        return *this;
    }
};

int main() {
    SList<int> e;
    e.addFirst(2);
    e.addFirst(3);
    e.addLast(22);
    e.print();
    // // Test other methods
    cout << "Front: " << e.front() << endl;
    cout << "Back: " << e.back() << endl;
    cout << "Size: " << e.getSize() << endl;
    cout << "Is empty: " << (e.isEmpty() ? "Yes" : "No") << endl;

    return 0;
}
