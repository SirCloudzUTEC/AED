#include <iostream>
#include <stdexcept>

using std::cout;

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
class List{
private:
    Node<T>* head;
    Node<T>* tail;
    int n;

public:
    List(){
        head = nullptr;
        tail = nullptr;
        n = 0;
    }

    ~List(){
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

        return tail->data;
    }

    void push_front(T val){
        Node<T>* node = new Node<T>(val);

        if(empty()){
            head = tail = node;
        }
        else{
            node->next = head;
            head->prev = node;
            head = node;
        }

        n++;
    }

    void push_back(T val){
        Node<T>* node = new Node<T>(val);

        if(empty()){
            head = tail = node;
        }
        else{
            tail->next = node;
            node->prev = tail;
            tail = node;
        }

        n++;
    }

    T pop_front(){
        if(empty())
            throw std::runtime_error("Lista vacia");

        Node<T>* temp = head;
        T val = temp->data;

        if(head == tail){
            head = tail = nullptr;
        }
        else{
            head = head->next;
            head->prev = nullptr;
        }

        delete temp;
        n--;

        return val;
    }

    T pop_back(){
        if(empty())
            throw std::runtime_error("Lista vacia");

        Node<T>* temp = tail;
        T val = temp->data;

        if(head == tail){
            head = tail = nullptr;
        }
        else{
            tail = tail->prev;
            tail->next = nullptr;
        }

        delete temp;
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
        Node<T>* curr = head;
        Node<T>* temp = nullptr;

        while(curr != nullptr){
            temp = curr->prev;
            curr->prev = curr->next;
            curr->next = temp;
            curr = curr->prev;
        }

        temp = head;
        head = tail;
        tail = temp;
    }

    void sort(){
        if(n <= 1)
            return;

        bool swapped;

        do{
            swapped = false;
            Node<T>* curr = head;

            while(curr->next != nullptr){

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
        Node<T>* curr = head;

        while(curr != nullptr){
            cout << curr->data << " ";
            curr = curr->next;
        }

        cout << "\n";
    }

    void print_reverse(){
        Node<T>* curr = tail;

        while(curr != nullptr){
            cout << curr->data << " ";
            curr = curr->prev;
        }

        cout << "\n";
    }
};

int main(){

    List<int> l;

    l.push_back(5);
    l.push_back(2);
    l.push_back(8);
    l.push_front(1);

    l.print();

    l.sort();
    l.print();

    l.reverse();
    l.print();

    cout << l[2] << "\n";

    cout << l.pop_front() << "\n";
    cout << l.pop_back() << "\n";

    l.print();

    return 0;
}