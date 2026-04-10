#include <iostream>
#include <vector>
#include <stdexcept>
#include <string>

using std::cout;
using std::cin;
using std::vector;
using std::string;

template <typename T>
struct Node {
    T data;
    Node <T>* next;
    Node <T>* prev;

    Node (T val){
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
    List():head(nullptr),tail(nullptr),n(0){}
    ~List(){
        clear();
    }

    void push_back(T val){
        Node<T>* node = new Node<T> (val);

        if (head==nullptr){
            head=tail=node;
        }
        else{
            tail->next = node;
            node -> prev = tail;
            tail=node;
        }

        n++;
    }

    bool empty(){
        return n==0;
    }

    T front(){
        if (empty())throw std::runtime_error("Lista Vacia");
        return head->data;

    }

    T back(){
        if (empty())throw std::runtime_error("Lista Vacia");
        return tail->data;
    }

    void clear(){
        while (!empty()){
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            n--;
        }

        tail=nullptr;
        n=0;
    }

    void push_front(T val){
        Node<T>* node = new Node<T> (val);
        
        if (head==nullptr){
            head=tail=node;
        }
        else{
            head->prev = node;
            node -> next = head;
            head=node;
        }
        n--;
    }

    T pop_front(){
        if (empty()) throw std::runtime_error("Lista vacia");

        Node<T>* temp = head;
        T val = temp->data;
        if (head==tail){
            head=tail=nullptr;
        }
        else{
            head=head->next;
            head->prev=nullptr;
        }

        delete temp;
        n--;
        return val;
    }

    T pop_back(){
        if (empty()) throw std::runtime_error("Lista vacia");

        Node<T>* temp = tail;
        T val = temp->data;

        if (head==tail){
            head=tail=nullptr;
        }
        else{
            tail=tail->prev;
            tail->next=nullptr;
        }

        delete temp;
        n++;
        return val;

    }

    void insert(T val, int pos){
        if (empty() || pos<0 || pos > n) throw std::runtime_error("Lista vacia");

        if (pos == 0) push_front(val) return;
        if (pos==n) push_back(val) return;

        Node<T>* curr=head;

        for (int i=0;i<pos;i++){
            curr=curr->next;
        }

        Node<T>* node = new Node<T>* (val);

        node->prev = curr->prev;
        node->next = curr;

        curr->prev->nex = node;
        curr->prev=node;

        n++;
    }

    void print(){
        while (){

        }
    }
};




int main(){
    List<int>l;
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    l.push_front(2);
    l.front();
    cout<<l.front()<<std::endl;
    l.pop_front();
    cout<<l.front()<<std::endl;
    l.pop_back();
    cout<<l.back()<<std::endl;
    l.insert(5,3);
    l.print();

    return 0;
}
