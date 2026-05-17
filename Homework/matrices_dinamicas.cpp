#include <iostream>
#include <stdexcept>

using std::cout;

template <typename T>
struct Node{
    int row;
    int col;
    T value;

    Node<T>* next;

    Node(int r, int c, T val){
        row = r;
        col = c;
        value = val;
        next = nullptr;
    }
};

template <typename T>
class SparseMatrix{
private:
    int rows;
    int cols;

    Node<T>* head;

public:

    SparseMatrix(int r, int c){
        rows = r;
        cols = c;
        head = nullptr;
    }

    ~SparseMatrix(){
        clear();
    }

    void clear(){

        Node<T>* curr = head;

        while(curr != nullptr){

            Node<T>* temp = curr;
            curr = curr->next;

            delete temp;
        }

        head = nullptr;
    }

    void insert(int r, int c, T val){

        if(r < 0 || r >= rows || c < 0 || c >= cols)
            throw std::out_of_range("Posicion invalida");

        if(val == 0){
            remove(r, c);
            return;
        }

        Node<T>* curr = head;

        while(curr != nullptr){

            if(curr->row == r && curr->col == c){
                curr->value = val;
                return;
            }

            curr = curr->next;
        }

        Node<T>* node = new Node<T>(r, c, val);

        node->next = head;
        head = node;
    }

    void remove(int r, int c){

        Node<T>* curr = head;
        Node<T>* prev = nullptr;

        while(curr != nullptr){

            if(curr->row == r && curr->col == c){

                if(prev == nullptr){
                    head = curr->next;
                }
                else{
                    prev->next = curr->next;
                }

                delete curr;
                return;
            }

            prev = curr;
            curr = curr->next;
        }
    }

    bool search(int r, int c){

        Node<T>* curr = head;

        while(curr != nullptr){

            if(curr->row == r && curr->col == c)
                return true;

            curr = curr->next;
        }

        return false;
    }

    T operator()(int r, int c){

        if(r < 0 || r >= rows || c < 0 || c >= cols)
            throw std::out_of_range("Posicion invalida");

        Node<T>* curr = head;

        while(curr != nullptr){

            if(curr->row == r && curr->col == c)
                return curr->value;

            curr = curr->next;
        }

        return 0;
    }

    bool operator==(SparseMatrix<T>& other){

        if(rows != other.rows || cols != other.cols)
            return false;

        for(int i = 0; i < rows; i++){

            for(int j = 0; j < cols; j++){

                if((*this)(i,j) != other(i,j))
                    return false;
            }
        }

        return true;
    }

    SparseMatrix<T> operator+(SparseMatrix<T>& other){

        if(rows != other.rows || cols != other.cols)
            throw std::runtime_error("Estan mal las dimensiones");

        SparseMatrix<T> result(rows, cols);

        for(int i = 0; i < rows; i++){

            for(int j = 0; j < cols; j++){

                T val = (*this)(i,j) + other(i,j);

                if(val != 0)
                    result.insert(i, j, val);
            }
        }

        return result;
    }

    SparseMatrix<T> operator-(SparseMatrix<T>& other){

        if(rows != other.rows || cols != other.cols)
            throw std::runtime_error("Estan mal las dimensiones");

        SparseMatrix<T> result(rows, cols);

        for(int i = 0; i < rows; i++){

            for(int j = 0; j < cols; j++){

                T val = (*this)(i,j) - other(i,j);

                if(val != 0)
                    result.insert(i, j, val);
            }
        }

        return result;
    }

    SparseMatrix<T> transpose(){

        SparseMatrix<T> result(cols, rows);

        Node<T>* curr = head;

        while(curr != nullptr){

            result.insert(curr->col, curr->row, curr->value);

            curr = curr->next;
        }

        return result;
    }

    SparseMatrix<T> operator*(SparseMatrix<T>& other){

        if(cols != other.rows)
            throw std::runtime_error("Estan mal las dimensiones");

        SparseMatrix<T> result(rows, other.cols);

        for(int i = 0; i < rows; i++){

            for(int j = 0; j < other.cols; j++){

                T sum = 0;

                for(int k = 0; k < cols; k++){

                    sum += (*this)(i,k) * other(k,j);
                }

                if(sum != 0)
                    result.insert(i, j, sum);
            }
        }

        return result;
    }

    void print(){

        for(int i = 0; i < rows; i++){

            for(int j = 0; j < cols; j++){

                cout << (*this)(i,j) << " ";
            }

            cout << "\n";
        }

        cout << "\n";
    }
};

int main(){

    SparseMatrix<int> A(3,3);
    SparseMatrix<int> B(3,3);

    A.insert(0,0,1);
    A.insert(1,1,2);
    A.insert(2,2,3);

    B.insert(0,0,4);
    B.insert(1,1,5);
    B.insert(2,2,6);

    A.print();
    B.print();
    return 0;
}