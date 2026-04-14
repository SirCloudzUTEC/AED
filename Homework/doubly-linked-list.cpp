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
        Node<T>* temp = head;
        int cont = 0;
        while (temp != nullptr){
            if (cont == pos){
                Node<T>* next = temp->next;
                Node<T>* prev = temp->prev;

                if (next){
                    
                }
            }

            temp = temp->next;
            cont++;
        }


    }

    void remove(int pos){
        Node<T>* temp = head;
        int cont=0;
        while (temp !=nullptr){
            if (cont == pos){
                Node<T>* next = temp->next;
                Node<T>* prev = temp->prev;
                
                if (next!=nullptr){
                    next->prev = prev;
                }
                else{
                    tail = prev;
                }

                if (prev!=nullptr){
                    prev->next = next;
                }
                else{
                    head = next;
                }

                delete temp;
                n--;
                return;
            }

            cont++;
            temp = temp->next;
        }
        

    }

    int size(){
        Node<T>* curr=head;
        int cont=0;
        while (curr!=nullptr){
            cont++;
            curr = curr->next;
        }

        delete curr;
        return cont;
    }


    void print(){
        Node<T>* curr = head;
        while(curr != nullptr){
            cout<< curr->data <<" ";
            curr = curr->next;
        }

        delete curr;
        cout<<"\n";
    }

    void print_reverse(){
        Node<T>* curr = tail;
        while (curr!=nullptr){
            cout<<curr->data<<" ";
            curr = curr->prev;
        }

        delete curr;
        cout<<"\n";
    }

    void reverse(){
        Node<T>* curr=tail;
        Node<T>* tempHead = head;
        while (curr != nullptr){
            tempHead = curr;

            tempHead = tempHead ->next;
            curr= curr->prev;
        }

    }
};




int main(){
    List<int>l;
    l.push_back(3);
    l.push_back(4);
    l.push_back(5);

    l.push_front(2);
    //l.reverse();
    //l.reverse();
    l.remove(1);
    l.remove(1);
    l.print();



    return 0;
}
