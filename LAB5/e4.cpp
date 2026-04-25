#include <iostream>
#include <functional>
#include <stdexcept>
#include <random>
#include <string>
#include <utility>
#include <vector>
#include <cmath>

using namespace std;

// ============================================================
// HASH BASE
// Convierte cualquier Key en un size_t usando std::hash
// ============================================================
//Convertir llave cualquiera a hash base usando std::hash, que es una función de hash general para tipos estándar y personalizados (si se especializa).
// Convierte a numero entero.

template <typename Key>
size_t base_hash(const Key& key) {
    return std::hash<Key>{}(key);
}

// ============================================================
// 1) HASH POR DIVISIÓN: No es óptima ya que suele generar muchas colisiones.
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
// 2) HASH POR MULTIPLICACIÓN: Suele ser la óptima para encontrar un índice en la tabla hash y genera menos colisiones.
// h(k) = floor( m * frac(kA) )
// ============================================================
template <typename Key>
class MultiplicationHash {
private:
    double A;
public:
    explicit MultiplicationHash(double a = 0.6180339887) : A(a) {
        if (A <= 0.0 || A >= 1.0)
            throw invalid_argument("A debe cumplir 0 < A < 1");
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
class UniversalHash { // Esta compuesto por números primos grandes como p, y dos números aleatorios (a y b) con 1 <= a < p y 0 <= b < p, las cuales serviran como constantes. 
private:
    size_t a, b, p;
public:
    explicit UniversalHash(size_t prime = 1000003) : p(prime) {
        if (p < 2) throw invalid_argument("p debe ser un primo >= 2");

        //Lo de acá es para generar a y b aleatorios dentro de los rangos requeridos usando el generador de números aleatorios de C++11.
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
// DEFAULT VALUE HELPER
// Devuelve el valor por defecto según el tipo de Value.
// Especializable. Cubre int, bool, string, vector<T>.

// IMPORTANCIA:
//“Si la clave no existe, permite que se cree automáticamente con un valor inicial correcto”

// ============================================================
template <typename Value>
Value default_value() { return Value{}; }          // Fallback genérico

template <> inline int    default_value<int>()    { return 0; }
template <> inline bool   default_value<bool>()   { return false; }
template <> inline string default_value<string>() { return ""; }

// Para vector<T> el Value{} ya devuelve vector vacío, así que el fallback alcanza.

// ============================================================
// HASH TABLE CON CHAINING  +  operator[]  +  Iterador range-for
// - Lista simplemente enlazada por bucket
// - Inserción en cabeza
// - Rehash al exceder maxFillFactor
// - FillFactor = elements / (capacity * k)
// ============================================================
template <typename Key, typename Value, typename HashPolicy = DivisionHash<Key>>
class HashTable {
private:
    // -------------------------
    // Nodo de lista simplemente enlazada
    // -------------------------
    struct Node {
        Key   key;
        Value value;
        Node* next;
        Node(const Key& k, const Value& v, Node* n = nullptr)
            : key(k), value(v), next(n) {}
    };

    Node**     table;              // arreglo de punteros a listas
    size_t     capacity;           // tamaño de la tabla   
    size_t     numElements;        // número total de elementos
    size_t     maxCollisionK;      // k del PDF
    double     maxFillFactor;      // 0.5
    HashPolicy hashFunction;

    // -------------------------
    // Helpers internos
    // -------------------------

    // Libera todos los nodos
    void clearBuckets() {
        for (size_t i = 0; i < capacity; ++i) {
            Node* cur = table[i];
            while (cur) { Node* tmp = cur; cur = cur->next; delete tmp; }
            table[i] = nullptr;
        }
    }

    // Inicializa tabla vacía
    void initTable(size_t cap) {
        capacity = cap;
        table = new Node*[capacity]();   // value-init → nullptr
    }

    // Inserta nodo directamente en cabeza sin verificar fill factor
    void insertNodeAtHead(const Key& key, const Value& value) {
        size_t idx = hashFunction(key, capacity);
        table[idx] = new Node(key, value, table[idx]);
        ++numElements;
    }

    // Rehash: duplica capacidad y reubica todos los elementos
    void rehash() {
        size_t    oldCap   = capacity;
        Node**    oldTable = table;
        initTable(capacity * 2);
        numElements = 0;
        for (size_t i = 0; i < oldCap; ++i) {
            Node* cur = oldTable[i];
            while (cur) {
                insertNodeAtHead(cur->key, cur->value);
                Node* tmp = cur; cur = cur->next; delete tmp;
            }
        }
        delete[] oldTable;
    }

    // Decide si, después de insertar uno más, se supera el fill factor
    bool needsRehashAfterNextInsertion() const {
        return static_cast<double>(numElements + 1) /
               static_cast<double>(capacity * maxCollisionK) > maxFillFactor;
    }

    // Busca o crea el nodo para una key (usado por operator[])
    Node* findOrCreate(const Key& key) {
        size_t idx = hashFunction(key, capacity);
        Node*  cur = table[idx];
        while (cur) {
            if (cur->key == key) return cur;
            cur = cur->next;
        }
        // No existe → insertar con valor por defecto
        if (needsRehashAfterNextInsertion()) {
            rehash();
            idx = hashFunction(key, capacity);
        }
        table[idx] = new Node(key, default_value<Value>(), table[idx]);
        ++numElements;
        return table[idx];
    }

public:
    // ============================================================
    // CONSTRUCTOR / DESTRUCTOR
    // ============================================================
    explicit HashTable(size_t initialCapacity = 5,
                       size_t k    = 3,
                       double maxFF = 0.5,
                       const HashPolicy& hp = HashPolicy())
        : table(nullptr), capacity(0), numElements(0),
          maxCollisionK(k), maxFillFactor(maxFF), hashFunction(hp)
    {
        if (initialCapacity == 0) throw invalid_argument("Capacidad inicial debe ser > 0");
        if (k == 0)               throw invalid_argument("k debe ser > 0");
        if (maxFF <= 0.0)         throw invalid_argument("maxFillFactor debe ser > 0");
        initTable(initialCapacity);
    }

    // -----------------------------
    // Destructor
    // -----------------------------
    ~HashTable() { clearBuckets(); delete[] table; }

    
    // -----------------------------
    // Evitar copias accidentales
    // -----------------------------
    HashTable(const HashTable&)            = delete;
    HashTable& operator=(const HashTable&) = delete;

    // ============================================================
    // INSERT
    // Si la key existe, actualiza valor
    // Si no existe, inserta en cabeza
    // ============================================================
    void insert(const Key& key, const Value& value) {
        size_t idx = hashFunction(key, capacity);
        
        // Si ya existe, actualizamos
        Node*  cur = table[idx];
        while (cur) {
            if (cur->key == key) { cur->value = value; return; }
            cur = cur->next;
        }

        // Verificamos rehash antes de insertar nuevo elemento
        if (needsRehashAfterNextInsertion()) {
            rehash();
            idx = hashFunction(key, capacity);
        }

        // Inserción en cabeza
        table[idx] = new Node(key, value, table[idx]);
        ++numElements;
    }

    // ============================================================
    // SEARCH
    // Retorna puntero al valor o nullptr
    // ============================================================
    Value* search(const Key& key) {
        size_t idx = hashFunction(key, capacity);
        for (Node* cur = table[idx]; cur; cur = cur->next)
            if (cur->key == key) return &cur->value;
        return nullptr;
    }

    const Value* search(const Key& key) const {
        size_t idx = hashFunction(key, capacity);
        for (Node* cur = table[idx]; cur; cur = cur->next)
            if (cur->key == key) return &cur->value;
        return nullptr;
    }

    // ============================================================
    // REMOVE
    // Retorna true si eliminó
    //Devuelve booleano para saber si la eliminación fue exitosa o no (si la key no existe, no se elimina nada y retorna false)
    // ============================================================
    bool remove(const Key& key) { 
        size_t idx  = hashFunction(key, capacity);
        Node*  cur  = table[idx];
        Node*  prev = nullptr;
        while (cur) {
            if (cur->key == key) {
                (prev ? prev->next : table[idx]) = cur->next;
                delete cur;
                --numElements;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    // ============================================================
    // OPERATOR[]  — acceso STL-like
    //
    // ht[key]          -> devuelve referencia al value (crea si no existe)
    // ht[key] = v      -> asigna
    // ht[key]++        -> incrementa (funciona porque es referencia)
    // ht[key] += x     -> funciona igual
    // ============================================================
    Value& operator[](const Key& key) {
        return findOrCreate(key)->value;
    }

    // ============================================================
    // ITERADOR  — permite  for (auto [k, v] : ht)
    // ============================================================
    struct Entry {
        const Key& key;
        Value&     value;
    };

    struct Iterator {
        Node**  table;
        size_t  capacity;
        size_t  bucket;
        Node*   node;

        void advance() {
            while (bucket < capacity && node == nullptr) {
                ++bucket;
                if (bucket < capacity) node = table[bucket];
            }
        }

        Entry operator*() const { return {node->key, node->value}; }

        Iterator& operator++() {
            node = node->next;
            if (!node) {
                // cadena agotada → buscar siguiente bucket no vacío
                ++bucket;
                node = nullptr;
                while (bucket < capacity && !table[bucket]) ++bucket;
                if (bucket < capacity) node = table[bucket];
            }
            return *this;
        }

        bool operator!=(const Iterator& o) const {
            return bucket != o.bucket || node != o.node;
        }
    };

    Iterator begin() {
        for (size_t i = 0; i < capacity; ++i) {
            if (table[i]) return Iterator{table, capacity, i, table[i]};
        }
        return end();
    }

    Iterator end() {
        return Iterator{table, capacity, capacity, nullptr};
    }

    // ============================================================
    // UTILIDADES
    // ============================================================
    bool   contains(const Key& key) const { return search(key) != nullptr; }
    size_t size()        const { return numElements; }
    size_t getCapacity() const { return capacity; }
    size_t getK()        const { return maxCollisionK; }
    bool   empty()       const { return numElements == 0; }

    double getFillFactor() const {
        // Fórmula del PDF:
        // FillFactor = #elements / (capacity * k)
        return static_cast<double>(numElements) /
               static_cast<double>(capacity * maxCollisionK);
    }

    double getMaxFillFactor() const { return maxFillFactor; }

    // Longitud de la lista en un bucket específico
    size_t bucketSize(size_t index) const {
        if (index >= capacity) throw out_of_range("Bucket fuera de rango");
        size_t count = 0;
        for (Node* c = table[index]; c; c = c->next) ++count;
        return count;
    }

    void print() const {
        cout << "-----------------------------------------\n";
        cout << "Capacity      : " << capacity      << "\n";
        cout << "Elements      : " << numElements   << "\n";
        cout << "k             : " << maxCollisionK << "\n";
        cout << "FillFactor    : " << getFillFactor()    << "\n";
        cout << "MaxFillFactor : " << maxFillFactor      << "\n";
        cout << "-----------------------------------------\n";
        for (size_t i = 0; i < capacity; ++i) {
            cout << "[" << i << "] -> ";
            for (Node* c = table[i]; c; c = c->next)
                cout << "(" << c->key << ", " << c->value << ") -> ";
            cout << "nullptr\n";
        }
        cout << "-----------------------------------------\n";
    }
};

class Solution {
public:
    bool almostIsomorphic(string s, string t, int k) {
        // TODO: PROGRAMAR
        HashTable<char, int> dictS;
        HashTable<char, int> dictT;
        for(int i = 0; i< t.size(); i++){
            dictS[s[i]]++;
        }

        for(int i = 0; i< s.size(); i++){
            dictT[t[i]]++;
        }

        for(int i= 0; i< s.size(); i++){
            if(dictS[i] != dictT[i]){
                if(k==0){ return false;}
                k--;
            }
        }

        return true;
    }
};

struct TestCase {
    string s;
    string t;
    int k;
    bool expected;
    string description;
};

void runTests() {
    Solution sol;

    vector<TestCase> tests = {
        {"egg", "add", 0, true,  "Caso clásico isomorfo"},
        {"foo", "bar", 0, false, "No isomorfo sin errores permitidos"},
        {"foo", "bar", 1, true,  "No isomorfo con 1 error permitido"},
        {"paper", "title", 0, true, "Mapeo consistente con repeticiones"},
        {"ab", "cc", 0, false, "Dos caracteres distintos apuntan al mismo carácter"},
        {"ab", "cc", 1, true,  "Conflicto inverso permitido con k = 1"},
        {"aaa", "abc", 2, true, "Un carácter apunta a varios, pero se permiten 2 errores"},
        {"aaa", "abc", 1, false, "Un carácter apunta a varios y k no alcanza"},
        {"abababab", "cdcdcdcd", 0, true, "Patrón repetitivo válido"},
        {"a", "z", 0, true, "Caso borde de longitud 1"}
    };

    int passed = 0;

    for (int i = 0; i < tests.size(); i++) {
        bool result = sol.almostIsomorphic(
            tests[i].s,
            tests[i].t,
            tests[i].k
        );

        cout << "Test " << i + 1 << ": ";

        if (result == tests[i].expected) {
            cout << "PASO";
            passed++;
        } else {
            cout << "FALLO";
        }

        cout << " | " << tests[i].description << endl;
        cout << "  Entrada: s = \"" << tests[i].s
             << "\", t = \"" << tests[i].t
             << "\", k = " << tests[i].k << endl;

        cout << "  Esperado: " << boolalpha << tests[i].expected
             << ", Obtenido: " << result << endl;

        cout << "-----------------------------------" << endl;
    }

    cout << "Resultado final: " << passed << " / "
         << tests.size() << " tests pasaron." << endl;
}

int main() {
    runTests();
    return 0;
}