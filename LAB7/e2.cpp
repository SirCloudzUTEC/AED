#include <vector>
#include <unordered_map>
#include <functional>
using namespace std;

struct Heap {
    // almacena pares (frecuencia, valor)
    vector<pair<int,int>> data;
    function<bool(pair<int,int>, pair<int,int>)> cmp;

    Heap(function<bool(pair<int,int>, pair<int,int>)> cmp) : cmp(cmp) {}

    int left(int i)   { return 2*i + 1; }
    int right(int i)  { return 2*i + 2; }
    int parent(int i) { return (i - 1) / 2; }

    void heapify_up(int i) {
        while (i > 0 && cmp(data[i], data[parent(i)])) {
            swap(data[i], data[parent(i)]);
            i = parent(i);
        }
    }

    void heapify_down(int i) {
        int n = data.size(), best = i;
        int l = left(i), r = right(i);
        if (l < n && cmp(data[l], data[best])) best = l;
        if (r < n && cmp(data[r], data[best])) best = r;
        if (best != i) {
            swap(data[i], data[best]);
            heapify_down(best);
        }
    }

    void push(pair<int,int> val) {
        data.push_back(val);
        heapify_up(data.size() - 1);
    }

    void pop() {
        swap(data[0], data.back());
        data.pop_back();
        if (!data.empty()) heapify_down(0);
    }

    pair<int,int> top() { return data[0]; }
    int size()  { return data.size(); }
};

vector<int> topKFrequent(vector<int>& nums, int k) {
    // Paso 1: contar frecuencias
    unordered_map<int,int> freq;
    for (int x : nums) freq[x]++;

    // min-heap por frecuencia: el menos frecuente queda en la raíz
    auto cmp = [](pair<int,int> a, pair<int,int> b) {
        return a.first < b.first; // menor frecuencia = más prioritario en min-heap
    };
    Heap h(cmp);

    // Paso 2: mantener ventana de tamaño k
    for (auto& [val, f] : freq) {
        h.push({f, val});
        if (h.size() > k) h.pop(); // descarta el menos frecuente
    }

    // Paso 3: extraer resultados
    vector<int> res;
    while (!h.data.empty()) {
        res.push_back(h.top().second);
        h.pop();
    }
    return res;
}