#include <vector>
#include <string>
#include <iostream>
using namespace std;

template <typename T>
class LinkedList {
public:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node() {
            next = nullptr;
            prev = nullptr;
        }

        Node(T value) {
            data = value;
            next = nullptr;
            prev = nullptr;
        }

    };

    LinkedList() {
        numNodes = 0;
        head = NULL;
        tail = NULL;
    }

    LinkedList(const LinkedList<T>& list) {
        head = NULL;
        tail = NULL;

        for (unsigned int i = 0; i < list.NodeCount(); i++) {
            this->AddTail(list[i]);
        }

        numNodes = list.NodeCount();
    }

    LinkedList<T>& operator=(const LinkedList<T>& rhs) {
        //bool rhsBigger;
        //if (rhs.NodeCount() > this->numNodes) { rhsBigger = true } else { rhsBigger = false }

        for (unsigned int i = 0; i < rhs.NodeCount(); i++) {
            if (i == this->numNodes) {
                this->AddTail(rhs[i]);
            }
            else {
                Node* iterator = this->head;
                for (unsigned int j = 0; j < i; j++) {
                    iterator = iterator->next;
                }

                iterator->data = rhs[i];
            }
        }

        this->numNodes = rhs.NodeCount();
        return *this;
    }

    ~LinkedList() {
        Node* currentNode = head;
        while (currentNode) {
            Node* upcomingNode = currentNode->next;
            delete currentNode;
            currentNode = upcomingNode;
        }
    }

    unsigned int NodeCount() const {
        return numNodes;
    }

    void AddHead(const T& value) {
        numNodes++;
        if (head) {
            Node* newHead = new Node(value);
            newHead->next = head;
            head->prev = newHead;
            head = newHead;
        } else {
            Node* newHead = new Node(value);
            head = newHead;
        }
        
    }

    void AddTail(const T& value) {
        numNodes++;
        Node* newTail = new Node;
        newTail->data = value;
        newTail->next = nullptr;
        

        if (head == NULL) {
            head = newTail;
            head->next = tail;
        }
        else if (head->next == nullptr) {
            tail = newTail;
            tail->next = nullptr;
            tail->prev = head;
            head->next = tail;
        }
        else {
            Node* iterable = head;

            while (iterable->next) {
                iterable = iterable->next;
            }

            iterable->next = newTail;
            newTail->prev = iterable;
            tail = newTail;

        }
    }

    void PrintForward() const {
        Node* currentNode = head;

        while (currentNode != nullptr) {
            cout << currentNode->data << endl;
            currentNode = currentNode->next;
        }
    }

    void PrintReverse() const {
        Node* currentNode = tail;
        Node* iteratingNode = head;

        while (currentNode != head) {
            if (currentNode != nullptr) {
                cout << currentNode->data << endl;
                for (unsigned int i = 0; i < numNodes; i++) {

                    if (iteratingNode->next == currentNode) {
                        currentNode = iteratingNode;
                        iteratingNode = head;
                        break;
                    }
                    else { iteratingNode = iteratingNode->next; }
                }
            }
            else {
                for (unsigned int i = 0; i < numNodes; i++) {

                    if (iteratingNode->next == currentNode) {
                        currentNode = iteratingNode;
                        iteratingNode = head;
                        break;
                    }

                    else { iteratingNode = iteratingNode->next; }
                }
            }
        }
        cout << head->data << endl;
    }

    void AddNodesHead(const T* value, unsigned int count) {
        for (unsigned int i = count; i > 0; i--) {
            LinkedList::AddHead(*(value + i - 1));
        }
    }

    void AddNodesTail(const T* value, unsigned int count) {
        for (unsigned int i = 0; i < count; i++) {
            LinkedList::AddTail(*(value + i));
        }
    }

    Node* Head() {
        return head;
    }

    const Node* Head() const {
        return head;
    }

    Node* Tail() {
        return tail;
    }

    const Node* Tail() const {
        return tail;
    }

    Node* GetNode(unsigned int index) {
        Node* iterator = head;
        for (unsigned int i = 0; i < index; i++) {
            iterator = iterator->next;
        }
        
        if (iterator == nullptr) {
            throw out_of_range("Index is out of range");
        }

        return iterator;
    }

    const Node* GetNode(unsigned int index) const {
        Node* iterator = head;
        for (unsigned int i = 0; i < index; i++) {
            iterator = iterator->next;
        }

        if (iterator == nullptr) {
            throw out_of_range("Index is out of range");
        }

        return iterator;
    }

    T& operator[](unsigned int index) {
        Node* iterator = head;

        if (index >= numNodes) {
            throw out_of_range("Index is out of range");
        }

        for (unsigned int i = 0; i < index; i++) {
            iterator = iterator->next;
        }

        return iterator->data;
    }

    const T& operator[](unsigned int index) const {
        Node* iterator = head;

        if (index >= numNodes) {
            throw out_of_range("Index is out of range");
        }

        for (unsigned int i = 0; i < index; i++) {
            iterator = iterator->next;
        }

        return iterator->data;
    }

    Node* Find(const T& value) {
        bool matchFound = false;
        Node* iterator = head;

        while (matchFound == false) {
            if (iterator->data == value) {
                matchFound = true;
            }
            else if (iterator == tail) {
                iterator = iterator->next;
                matchFound = true;
            }
            else {
                iterator = iterator->next;
            }
        }

        return iterator;
    }

    const Node* Find(const T& value) const {
        bool matchFound = false;
        Node* iterator = head;

        while (matchFound == false) {
            if (iterator->data == value) {
                matchFound = true;
            }
            else if (iterator == tail) {
                iterator = iterator->next;
                matchFound = true;
            }
            else {
                iterator = iterator->next;
            }
        }

        return iterator;
    }

    void FindAll(vector<Node*>& outData, const T& value) const {
        Node* iterator = head;

        for (unsigned int i = 0; i < numNodes; i++) {
            if (iterator->data == value) {
                outData.push_back(iterator);
            }

            iterator = iterator->next;
        }
    }

    void InsertBefore(Node* node, const T& value) {
        Node* newNode = new Node(value);
        newNode->prev = node->prev;
        node->prev->next = newNode;
        node->prev = newNode;
        newNode->next = node;
        numNodes++;
    }

    void InsertAfter(Node* node, const T& value) {
        Node* newNode = new Node(value);
        newNode->next = node->next;
        node->next = newNode;
        newNode->prev = node;
        numNodes++;
    }

    void InsertAt(const T& value, unsigned int index) {
        if (index > numNodes) {
            throw out_of_range("The index is out of range");
        }

        if (index == 0) {
            LinkedList<T>::AddHead(value);
        }
        else if (index == numNodes) {
            LinkedList<T>::AddTail(value);
        } else {
            Node* prevNode = head;
            for (unsigned int i = 0; i < index; i++) {
                prevNode = prevNode->next;
            }
            LinkedList<T>::InsertBefore(prevNode, value);
        }        
    }

    bool operator==(const LinkedList<T>& rhs) {
        bool same = true;

        if (this->numNodes != rhs.NodeCount()) {
            same = false;
        }

        for (unsigned int i = 0; i < this->numNodes; i++) {
            T spot1 = LinkedList<T>::operator[](i);
            T spot2 = rhs[i];

            if (spot1 != spot2) {
                same = false;
            }
        }
        return same;
    }

    bool RemoveHead() {
        if (numNodes == 0) {
            return false;
        } else if (head->next == nullptr) {
            delete head;
            head = NULL;
            tail = NULL;
            numNodes--;
            return true;
        }
        else {
            head->next->prev = nullptr;
            Node* dummy = head->next;
            delete head;
            head = dummy;
            numNodes--;
            return true;
        }
    }

    bool RemoveTail() {
        if (numNodes == 0) {
            return false;
        }
        else if (tail->prev == nullptr) {
            delete tail;
            tail = NULL;
            head = NULL;
            numNodes--;
            return true;
        }
        else {
            tail->prev->next = nullptr;
            Node* dummy = tail->prev;
            delete tail;
            tail = dummy;
            numNodes--;
            return true;
        }
    }

    unsigned int Remove(const T& value) {
        unsigned int numIndicies = 0;
        Node* iterator = head;

        for (unsigned int i = 0; i < numNodes; i++) {
            if (iterator->data == value) {
                iterator = iterator->next;
                LinkedList<T>::RemoveAt(i);
                numIndicies++;
                i--;
            }
            else {
                iterator = iterator->next;
            }
        }
        return numIndicies;
    }

    bool RemoveAt(unsigned int index) {
        if (index >= numNodes) {
            return false;
        }

        Node* iterator = head;

        for (unsigned int i = 0; i < index; i++) {
            iterator = iterator->next;
        }

        iterator->prev->next = iterator->next;
        iterator->next->prev = iterator->prev;
        delete iterator;
        numNodes--;
        return true;
    }

    void Clear() {
        Node* iterator = head;
        while (iterator) {
            Node* upcomingNode = iterator->next;
            delete iterator;
            iterator = upcomingNode;
        }
        head = NULL;
        tail = NULL;
        numNodes = 0;
    }

    void PrintForwardRecursive(const Node* node) const {
        if (node == tail) {
            cout << node->data << endl;
        } else {
            cout << node->data << endl;
            LinkedList<T>::PrintForwardRecursive(node->next);
            
        }
    }

    void PrintReverseRecursive(const Node* node) const {
        if (node == head) {
            cout << node->data << endl;
        }
        else {
            cout << node->data << endl;
            LinkedList<T>::PrintReverseRecursive(node->prev);
        }
    }

private:
    unsigned int numNodes;
    Node* head;
    Node* tail;

};