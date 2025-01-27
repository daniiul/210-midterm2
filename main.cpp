// COMSC-210 | Midterm 1 | Daniil Malakhov
// IDE used: Codeblocks
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class Person
{
private:
    string name;
public:
    Person()
    {
        ifstream inputFile("names.txt");

        if(!inputFile.is_open())
        {
            cout << "Error! Can't open File!";
        }

        vector<string> names;
        string temp;
        while(getline(inputFile, temp))
        {
            names.push_back(temp);
        }
        int length = names.size();

        int value = rand() % (length) ;
        name = names[value];
    }

    string getName() { return name;}
};

class DoublyLinkedList {
private:
    struct Node {
        Person *person;
        Node* prev;
        Node* next;
        Node(Person* pe, Node* p = nullptr, Node* n = nullptr) {
            person = pe;
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void insert_after(Person *p, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(p);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_person(string n) {
        if (!head) return;

        Node* temp = head;

        while (temp && n.compare(temp->person->getName()))
            temp = temp->next;

        if (!temp) return;

        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;

        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;

        delete temp;
    }

    void delete_pos(int pos) {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        if (pos == 1) {
            pop_front();
            return;
        }

        Node* temp = head;

        for (int i = 1; i < pos; i++){
            if (!temp) {
                cout << "Position doesn't exist." << endl;
                return;
            }
            else
                temp = temp->next;
        }
        if (!temp) {
            cout << "Position doesn't exist." << endl;
            return;
        }

        if (!temp->next) {
            pop_back();
            return;
        }

        Node* tempPrev = temp->prev;
        tempPrev->next = temp->next;
        temp->next->prev = tempPrev;
        delete temp;
    }

    void push_back(Person* p) {
        Node* newNode = new Node(p);
        if (!tail)
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Person* p) {
        Node* newNode = new Node(p);
        if (!head)
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void pop_front() {

        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node * temp = head;

        if (head->next) {
            head = head->next;
            head->prev = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    void pop_back() {
        if (!tail) {
            cout << "List is empty." << endl;
            return;
        }
        Node * temp = tail;

        if (tail->prev) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
            head = tail = nullptr;
        delete temp;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << "            " << current->person->getName()<< endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty." << endl;
            return;
        }
        while (current) {
            cout << current->person->getName() << " ";
            current = current->prev;
        }
        cout << endl;
    }
    string front_name()
    {
        return head->person->getName();
    }
    string back_name()
    {
        return tail->person->getName();
    }
    int length_of_list()
    {
        Node* temp = head;
        int len;
        while(temp)
        {
            temp = temp->next;
            len++;
        }
        return len;
    }
    string name_at_pos(int pos)
    {
        Node* temp = head;
        for (int i = 0; i < pos && temp; ++i)
            temp = temp->next;

        return temp->person->getName();
    }
};

int main() {

    srand(time(0));

    DoublyLinkedList list;

    string fr;
    string bc;

    for(int j = 1; j < 5; j++)
    {

        Person *temp = new Person();
        list.push_back(temp);
    }

    cout << "Store opens: " << endl;
    list.print();


    for(int i = 1; i <= 20; i++)
    {

        cout << "Time step # " << i << endl;


        int prob = rand() % 100 + 1;  // returns random number 1-100
        if (prob <= 20)
        {
            cout <<  "      " << list.back_name() << " (at rear) has left the line" << endl;
            list.pop_back();
        }
        if (prob <= 60)
        {
            Person *temp = new Person();
            string na = temp->getName();
            list.push_back(temp);
            cout << "      " << na << " joins the line" << endl;
        }
        if (prob <= 40) {
            cout <<  "      " << list.front_name() << " is served" << endl;
            list.pop_front();
        }
        if (prob <= 10)
        {
            int value = rand() % (list.length_of_list());
            cout <<  "      " << list.name_at_pos(value) << " has left the line" << endl;
            list.delete_pos(value + 1);
        }
        if (prob <= 10)
        {
            Person *temp = new Person();
            string na = temp->getName();
            cout <<  "      " << na << " (vip) joins the front of the line" << endl;
            list.push_front(temp);
        }
        cout << "      Resulting line so far: " << endl;
        list.print();
    }



    return 0;
}
