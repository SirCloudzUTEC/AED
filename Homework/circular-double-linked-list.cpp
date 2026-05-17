#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
struct Node{
    T data;
    Node<T>* next;
    Node<T>* prev;

    Node(T val){
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

template <typename T>
class CircularDoubleList{
private:
    Node<T>* head;
    int n;

public:
    CircularDoubleList(){
        head = nullptr;
        n = 0;
    }

    ~CircularDoubleList(){
        clear();
    }

    bool empty(){
        return n == 0;
    }

    int size(){
        return n;
    }

    T front(){
        if(empty())
            throw std::runtime_error("Lista vacia");

        return head->data;
    }

    T back(){
        if(empty())
            throw std::runtime_error("Lista vacia");

        return head->prev->data;
    }

    void push_front(T val){

        Node<T>* node = new Node<T>(val);

        if(empty()){
            node->next = node;
            node->prev = node;
            head = node;
        }
        else{

            Node<T>* tail = head->prev;

            node->next = head;
            node->prev = tail;

            tail->next = node;
            head->prev = node;

            head = node;
        }

        n++;
    }

    void push_back(T val){

        Node<T>* node = new Node<T>(val);

        if(empty()){
            node->next = node;
            node->prev = node;
            head = node;
        }
        else{

            Node<T>* tail = head->prev;

            node->next = head;
            node->prev = tail;

            tail->next = node;
            head->prev = node;
        }

        n++;
    }

    T pop_front(){

        if(empty())
            throw std::runtime_error("Lista vacia");

        Node<T>* temp = head;
        T val = temp->data;

        if(n == 1){
            head = nullptr;
        }
        else{

            Node<T>* tail = head->prev;

            head = head->next;

            head->prev = tail;
            tail->next = head;
        }

        delete temp;
        n--;

        return val;
    }

    T pop_back(){

        if(empty())
            throw std::runtime_error("Lista vacia");

        Node<T>* tail = head->prev;
        T val = tail->data;

        if(n == 1){
            delete tail;
            head = nullptr;
        }
        else{

            Node<T>* newTail = tail->prev;

            newTail->next = head;
            head->prev = newTail;

            delete tail;
        }

        n--;

        return val;
    }

    T operator[](int index){

        if(index < 0 || index >= n)
            throw std::out_of_range("Indice invalido");

        Node<T>* curr = head;

        for(int i = 0; i < index; i++){
            curr = curr->next;
        }

        return curr->data;
    }

    void clear(){

        while(!empty()){
            pop_front();
        }
    }

    void reverse(){

        if(n <= 1)
            return;

        Node<T>* curr = head;

        do{

            Node<T>* temp = curr->next;
            curr->next = curr->prev;
            curr->prev = temp;

            curr = temp;

        }while(curr != head);

        head = head->next;
    }

    void sort(){

        if(n <= 1)
            return;

        bool swapped;

        do{

            swapped = false;
            Node<T>* curr = head;

            for(int i = 0; i < n - 1; i++){

                if(curr->data > curr->next->data){

                    T temp = curr->data;
                    curr->data = curr->next->data;
                    curr->next->data = temp;

                    swapped = true;
                }

                curr = curr->next;
            }

        }while(swapped);
    }

    void print(){

        if(empty()){
            cout << "\n";
            return;
        }

        Node<T>* curr = head;

        do{
            cout << curr->data << " ";
            curr = curr->next;
        }while(curr != head);

        cout << "\n";
    }

    void print_reverse(){

        if(empty()){
            cout << "\n";
            return;
        }

        Node<T>* curr = head->prev;
        Node<T>* tail = curr;

        do{
            cout << curr->data << " ";
            curr = curr->prev;
        }while(curr != tail);

        cout << "\n";
    }
};

int main(){

    CircularDoubleList<int> l;

    l.push_back(4);
    l.push_back(21);

    l.print();

    return 0;
}