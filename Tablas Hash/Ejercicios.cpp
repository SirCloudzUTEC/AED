#include <iostream>
#include <functional>
#include <stdexcept>
#include <random>
#include <string>
#include <utility>
#include <cmath>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

// ============================================================
// HASH BASE
// Convierte cualquier Key en un size_t usando std::hash
// ============================================================
template <typename Key>
size_t base_hash(const Key& key) {
    return std::hash<Key>{}(key);
}

// ============================================================
// 1) HASH POR DIVISIÓN
// h(k) = k mod m
// ============================================================
template <typename Key>
class DivisionHash {
public:
    size_t operator()(const Key& key, size_t tableSize) const {
        return base_hash(key) % tableSize;
    }
};

// ============================================================
// 2) HASH POR MULTIPLICACIÓN
// h(k) = floor( m * frac(kA) )
// ============================================================
template <typename Key>
class MultiplicationHash {
private:
    double A;

public:
    explicit MultiplicationHash(double a = 0.6180339887) : A(a) {
        if (A <= 0.0 || A >= 1.0) {
            throw invalid_argument("A debe cumplir 0 < A < 1");
        }
    }

    size_t operator()(const Key& key, size_t tableSize) const {
        size_t k = base_hash(key);
        double x = k * A;
        double fractional = x - floor(x);
        return static_cast<size_t>(floor(tableSize * fractional));
    }
};

// ============================================================
// 3) HASH UNIVERSAL
// h(k) = ((a*k + b) mod p) mod m
// ============================================================
template <typename Key>
class UniversalHash {
private:
    size_t a;
    size_t b;
    size_t p;

public:
    explicit UniversalHash(size_t prime = 1000003) : p(prime) {
        if (p < 2) {
            throw invalid_argument("p debe ser un primo >= 2");
        }

        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<size_t> distA(1, p - 1);
        uniform_int_distribution<size_t> distB(0, p - 1);

        a = distA(gen);
        b = distB(gen);
    }

    size_t operator()(const Key& key, size_t tableSize) const {
        size_t k = base_hash(key);
        return ((a * k + b) % p) % tableSize;
    }

    size_t getA() const { return a; }
    size_t getB() const { return b; }
    size_t getP() const { return p; }
};

// ============================================================
// TABLA HASH CON CHAINING
// - Lista simplemente enlazada por bucket
// - Inserción en cabeza
// - Rehash al exceder maxFillFactor
// - FillFactor = elements / (capacity * k)
// ============================================================
template <typename Key, typename Value, typename HashPolicy = DivisionHash<Key>>
class HashTable {
private:
    // -----------------------------
    // Nodo de lista simplemente enlazada
    // -----------------------------
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v, Node* n = nullptr)
            : key(k), value(v), next(n) {}
    };

    Node** table;               // arreglo de punteros a listas
    size_t capacity;            // tamaño de la tabla
    size_t numElements;         // número total de elementos
    size_t maxCollisionK;       // k del PDF
    double maxFillFactor;       // 0.5
    HashPolicy hashFunction;

private:
    // Libera todos los nodos
    void clearBuckets() {
        for (size_t i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current != nullptr) {
                Node* temp = current;
                current = current->next;
                delete temp;
            }
            table[i] = nullptr;
        }
    }

    // Inicializa tabla vacía
    void initTable(size_t cap) {
        capacity = cap;
        table = new Node*[capacity];
        for (size_t i = 0; i < capacity; ++i) {
            table[i] = nullptr;
        }
    }

    // Inserta nodo directamente en cabeza sin verificar fill factor
    void insertNodeAtHead(const Key& key, const Value& value) {
        size_t index = hashFunction(key, capacity);
        Node* newNode = new Node(key, value, table[index]);
        table[index] = newNode;
        ++numElements;
    }

    // Rehash: duplica capacidad y reubica todos los elementos
    void rehash() {
        size_t oldCapacity = capacity;
        Node** oldTable = table;

        initTable(capacity * 2);
        numElements = 0;

        for (size_t i = 0; i < oldCapacity; ++i) {
            Node* current = oldTable[i];
            while (current != nullptr) {
                insertNodeAtHead(current->key, current->value);
                Node* temp = current;
                current = current->next;
                delete temp;
            }
        }

        delete[] oldTable;
    }

    // Decide si, después de insertar uno más, se supera el fill factor
    bool needsRehashAfterNextInsertion() const {
        double projectedFill =
            static_cast<double>(numElements + 1) /
            static_cast<double>(capacity * maxCollisionK);

        return projectedFill > maxFillFactor;
    }

public:
    // -----------------------------
    // Constructor
    // -----------------------------
    explicit HashTable(size_t initialCapacity = 5,
                       size_t k = 3,
                       double maxFF = 0.5,
                       const HashPolicy& hp = HashPolicy())
        : table(nullptr),
          capacity(0),
          numElements(0),
          maxCollisionK(k),
          maxFillFactor(maxFF),
          hashFunction(hp) {
        if (initialCapacity == 0) {
            throw invalid_argument("La capacidad inicial debe ser > 0");
        }
        if (k == 0) {
            throw invalid_argument("k debe ser > 0");
        }
        if (maxFF <= 0.0) {
            throw invalid_argument("maxFillFactor debe ser > 0");
        }

        initTable(initialCapacity);
    }

    // -----------------------------
    // Destructor
    // -----------------------------
    ~HashTable() {
        clearBuckets();
        delete[] table;
    }

    // -----------------------------
    // Evitar copias accidentales
    // -----------------------------
    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    // -----------------------------
    // INSERT
    // Si la key existe, actualiza valor
    // Si no existe, inserta en cabeza
    // -----------------------------
    void insert(const Key& key, const Value& value) {
        size_t index = hashFunction(key, capacity);

        // Si ya existe, actualizamos
        Node* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value;
                return;
            }
            current = current->next;
        }

        // Verificamos rehash antes de insertar nuevo elemento
        if (needsRehashAfterNextInsertion()) {
            rehash();
            index = hashFunction(key, capacity);
        }

        // Inserción en cabeza
        Node* newNode = new Node(key, value, table[index]);
        table[index] = newNode;
        ++numElements;
    }

    // -----------------------------
    // SEARCH
    // Retorna puntero al valor o nullptr
    // -----------------------------
    Value* search(const Key& key) {
        size_t index = hashFunction(key, capacity);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }
        return nullptr;
    }

    const Value* search(const Key& key) const {
        size_t index = hashFunction(key, capacity);
        Node* current = table[index];

        while (current != nullptr) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }
        return nullptr;
    }

    // -----------------------------
    // REMOVE
    // Retorna true si eliminó
    // -----------------------------
    bool remove(const Key& key) {
        size_t index = hashFunction(key, capacity);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current != nullptr) {
            if (current->key == key) {
                if (prev == nullptr) {
                    table[index] = current->next;
                } else {
                    prev->next = current->next;
                }
                delete current;
                --numElements;
                return true;
            }
            prev = current;
            current = current->next;
        }

        return false;
    }

    // -----------------------------
    // Utilidades
    // -----------------------------
    bool contains(const Key& key) const {
        return search(key) != nullptr;
    }

    size_t size() const {
        return numElements;
    }

    size_t getCapacity() const {
        return capacity;
    }

    size_t getK() const {
        return maxCollisionK;
    }

    double getFillFactor() const {
        // Fórmula del PDF:
        // FillFactor = #elements / (capacity * k)
        return static_cast<double>(numElements) /
               static_cast<double>(capacity * maxCollisionK);
    }

    double getMaxFillFactor() const {
        return maxFillFactor;
    }

    bool empty() const {
        return numElements == 0;
    }

    // Longitud de la lista en un bucket específico
    size_t bucketSize(size_t index) const {
        if (index >= capacity) {
            throw out_of_range("Índice de bucket fuera de rango");
        }

        size_t count = 0;
        Node* current = table[index];
        while (current != nullptr) {
            ++count;
            current = current->next;
        }
        return count;
    }

    // Imprimir tabla
    void print() const {
        cout << "-----------------------------------------\n";
        cout << "Capacity      : " << capacity << "\n";
        cout << "Elements      : " << numElements << "\n";
        cout << "k             : " << maxCollisionK << "\n";
        cout << "FillFactor    : " << getFillFactor() << "\n";
        cout << "MaxFillFactor : " << maxFillFactor << "\n";
        cout << "-----------------------------------------\n";

        for (size_t i = 0; i < capacity; ++i) {
            cout << "[" << i << "] -> ";
            Node* current = table[i];
            while (current != nullptr) {
                cout << "(" << current->key << ", " << current->value << ") -> ";
                current = current->next;
            }
            cout << "nullptr\n";
        }
        cout << "-----------------------------------------\n";
    }
};

class Solution{
public:
// Solucion a alto nivel: 
    // 1. Crear una Hash Table
    // 2. Recorrer arreglo y buscar nuevos elementos y sus complementos
    // 3. Insertar el indice del elemento actual y buscamos si su complemento
    // esta en la HashTable

    // vector<int> twoSum(vector<int> nums, int target){
    //     vector<int> salida;
    //     UniversalHash<int> uh(1000003);
    //     HashTable<int, int, DivisionHash<int>> hashtable(1,3);

    //     for (int i=0;i<nums.size();i++){
    //         if (hashtable.contains(nums[i])){
    //             if (hashtable.contains(target % nums[i] )){
    //                 salida.push_back(i);
    //             }
    //         }
    //         else{
    //             hashtable.insert(1,nums[i]);
    //         }
    //     }

    //     return salida;
    // }
 
    vector<int> twoSum(vector<int> nums, int target){
        HashTable<int, int, DivisionHash<int>> hashtable(5,3,0.5);

        for (int i=0;i<nums.size();i++){
            int need = target - nums[i];
            int* idx = hashtable.search(need);
            if (idx != nullptr)
                return {*idx,i};
            hashtable.insert(nums[i],i);
        }
        return {};
    }

    int cuadratic(int a){
        int sum = 0;
        while (a>0){
            int digito = a%10;
            sum += digito*digito;
            a/=10;
        }
        return sum;
    }

    bool isHappy(int n) {
        HashTable<int,bool> seen;
        while (n!=1){
            if (seen.contains(n)){
                return false;
            }
            seen.insert(n, true);
            n=cuadratic(n);
        }
        return true;
    }

    // La fija es devolver la longitud del sub array mas largo. Todo eso siguiendo el patron del subarraySum
    // Este codigo es usando el unordered map, el cual no esta permitido en labs
    int subarraySum_noHacer(vector<int>& a, int k) {
        int n = a.size();
        unordered_map<int,int> mp;
        int cnt = 0;
        int s=0;
        mp[0]++;
        for (int i=0;i<n;++i){
            s+=a[i];
            int t = s- k;
            if (mp[t]!=0){
                cnt += mp[t];
            }
            mp[s]++;
        }
        return cnt; 
    }
    // Resuelto usando el Hash Entregado por el profe
    int subarraySum_prof(vector<int>& a, int k) {
        HashTable<int, int> diccionario;
        int cont=0, sumatoria=0;
        diccionario.insert(0,1); // Base inicializadora

        for (int i = 0; i < a.size(); i++){
            sumatoria += a[i];
            int prev = sumatoria - k;

            int* frecuencia = diccionario.search(prev); 
            if(frecuencia != nullptr){
                cont+=*frecuencia;
            }

            int* current = diccionario.search(sumatoria);
            if (current != nullptr){
                diccionario.insert(sumatoria, *current + 1);
            }   
            else{
                diccionario.insert(sumatoria,1);
            }
        
        }

        return cont;
    }

    int longestSubarraySumK(vector<int>& a, int k) {
        HashTable<int,int> map;
        int longest = 0, sumatoria = 0;
        map.insert(0,-1);

        for (int i = 0 ; i < a.size(); ++i){
            sumatoria += a[i];

            int current = sumatoria - k;

            int* idx = map.search(current);
            if (idx != nullptr){
                int len = i - *idx;
                if (len > longest ){
                    longest = len;
                }
            }

            if (map.search(sumatoria) == nullptr){
                map.insert(sumatoria, i);
            }

        }

        return longest;
    }

    // Fija para parcial
    // El array tiene 0 y 1. Hallar la longitud del subarray mas largo de 0 1.
};

class SolutionContainsDuplicate {
public:
    bool containsDuplicate(vector<int>& nums) {
        HashTable<int, int, DivisionHash<int>> hashtable(5,3,0.5);

        for (int i=0;i<nums.size();i++){
            if(hashtable.search(nums[i])){
                return true;
            }
            hashtable.insert(nums[i],nums[i]);
        }
        return false;
    }
};

class SolutionValidAnagram {
public:
    // 1. Crear tabla hash
    // 2. Recorrer S y agregarlo un key (indice) y value (cantidad de veces
    // Que se repite esa letra)
    // 3. Recorrer T y eliminar cada palabra que se halle en T y en S
    bool isAnagram(string s, string t) {
        HashTable<int, int, DivisionHash<int>> mapa(5,3,0.5);
        
        //Recorremos S
        for (int i=0;i<s.length();i++){
            if (mapa.search(s[i]) == nullptr){
                mapa.insert(s[i],1);
            }
            else{   
                (*mapa.search(s[i]))++;
            }
        }

        //Recorremos T
        for (int i=0;i<t.length();i++){
            if (mapa.search(t[i]) == nullptr){
                return false;
            }
            else{
               (*mapa.search(s[i]))--; 
            }
        }

        return true;
    }
};



int main() {

    Solution s;
    vector<int> a = {1, 2, 3, 2, 5};
    int k = 5;
    cout << s.longestSubarraySumK(a, k) << endl;

    a = {1, -1, 5, -2, 3};
    k = 3;
    cout << s.longestSubarraySumK(a, k) << endl;

    a = {-2, -1, 2, 1};
    k = 1;
    cout << s.longestSubarraySumK(a, k) << endl;

    a = {3, 1, 0, 1, 8, 2, 3, 6};
    k = 5;
    cout << s.longestSubarraySumK(a, k) << endl;

    a = {1, 2, 3};
    k = 7;
    cout << s.longestSubarraySumK(a, k) << endl;

    return 0;
}
