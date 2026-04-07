#include <bits/stdc++.h>
#include <iostream>
#include <string>

using namespace std;

/* -------- Código base (renombrado a solucion) -------- */
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    vector<ListNode*> solucion(ListNode* head, int k) {
        int len = 0;
        ListNode* copia = head;

        while (copia) {
            len++;
            copia = copia->next;
        }

        copia = head;

        vector<int> long_matriz(k, len / k);
        for (int i = 0; i < len % k; i++) {
            long_matriz[i]++;
        }

        vector<ListNode*> salida(k, nullptr);

        for (int i = 0; i < k; i++) {
            if (long_matriz[i] == 0) {
                salida[i] = nullptr;
                continue;
            }

            salida[i] = copia;

            for (int j = 1; j < long_matriz[i]; j++) {
                copia = copia->next;
            }

            ListNode* sig = copia->next;
            copia->next = nullptr;
            copia = sig;
        }

        return salida;
    }
};

/* -------- Helpers para tests -------- */
ListNode* buildList(const vector<int>& a) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int x : a) { tail->next = new ListNode(x); tail = tail->next; }
    return dummy.next;
}

vector<int> flatten(const vector<ListNode*>& parts) {
    vector<int> out;
    for (auto* p : parts) {
        for (auto* cur = p; cur; cur = cur->next) out.push_back(cur->val);
    }
    return out;
}

vector<int> sizesOf(const vector<ListNode*>& parts) {
    vector<int> s;
    for (auto* p : parts) {
        int c = 0;
        for (auto* cur = p; cur; cur = cur->next) c++;
        s.push_back(c);
    }
    return s;
}

/* Valida:
   - concatenación == lista original
   - suma tamaños == n
   - tamaños no crecen (no-increasing)
   - max-min <= 1
*/
void validate_constraints(const vector<int>& original, int k, const vector<ListNode*>& parts) {
    // 1) cantidad de partes
    assert((int)parts.size() == k);

    // 2) concatenación en orden
    vector<int> cat = flatten(parts);
    assert(cat == original);

    // 3) tamaños
    vector<int> sz = sizesOf(parts);
    int sum = accumulate(sz.begin(), sz.end(), 0);
    assert(sum == (int)original.size());

    // 4) no-increasing
    for (int i = 1; i < (int)sz.size(); ++i) {
        assert(sz[i-1] >= sz[i]);
    }

    // 5) diferencia máx-min <= 1
    int mx = 0, mn = INT_MAX;
    for (int x : sz) { mx = max(mx, x); mn = min(mn, x); }
    if (k > 0) assert(mx - mn <= 1);
}

void expect_sizes(const vector<ListNode*>& parts, const vector<int>& expected) {
    vector<int> got = sizesOf(parts);
    // Si expected.size() < k, se completa implícitamente con ceros al final
    assert(got.size() == expected.size());
    assert(got == expected);
}

void freeParts(vector<ListNode*>& parts) {
    for (auto* p : parts) {
        while (p) { ListNode* q = p->next; delete p; p = q; }
    }
}

/* Ejecuta un test con construcción, llamado, validación y liberado. */
void run_test(
    int id, const vector<int>& listVals, int k,
    const vector<vector<int>>& expectedPartsVals /* vacío si no verificas valores exactos */,
    const vector<int>& expectedSizes /* vacío si no verificas tamaños exactos */
) {
    ListNode* head = buildList(listVals);
    Solution sol;
    auto parts = sol.solucion(head, k);

    cout << "Test " << id << " ... ";

    // Validación de restricciones generales
    validate_constraints(listVals, k, parts);

    // Validación de contenido exacto (opcional por test)
    if (!expectedPartsVals.empty()) {
        // Ensambla para comparar
        vector<vector<int>> got;
        for (auto* p : parts) {
            vector<int> vv;
            for (auto* cur = p; cur; cur = cur->next) vv.push_back(cur->val);
            got.push_back(vv);
        }
        assert(got == expectedPartsVals);
    }

    // Validación de tamaños exactos (opcional por test)
    if (!expectedSizes.empty()) {
        expect_sizes(parts, expectedSizes);
    }

    cout << "OK\n";
    freeParts(parts);
}

/* -------- 10 tests -------- */
int main() {
    // 1) n=10, k=3 -> tamaños: 4,3,3
    run_test(1, {1,2,3,4,5,6,7,8,9,10}, 3,
             {{1,2,3,4},{5,6,7},{8,9,10}}, {4,3,3});

    // 2) n=3, k=5 -> 1,1,1,0,0
    run_test(2, {10,20,30}, 5,
             {{10},{20},{30},{},{}} , {1,1,1,0,0});

    // 3) n=0, k=3 -> 0,0,0
    run_test(3, {}, 3,
             {{},{},{}}, {0,0,0});

    // 4) n=5, k=1 -> 5
    run_test(4, {7,8,9,10,11}, 1,
             {{7,8,9,10,11}}, {5});

    // 5) n=5, k=5 -> 1,1,1,1,1 (cada nodo una parte)
    run_test(5, {1,2,3,4,5}, 5,
             {{1},{2},{3},{4},{5}}, {1,1,1,1,1});

    // 6) n=7, k=2 -> 4,3
    run_test(6, {1,2,3,4,5,6,7}, 2,
             {{1,2,3,4},{5,6,7}}, {4,3});

    // 7) n=1, k=4 -> 1,0,0,0
    run_test(7, {42}, 4,
             {{42},{},{},{}}, {1,0,0,0});

    // 8) n=9, k=4 -> 3,2,2,2
    run_test(8, {1,2,3,4,5,6,7,8,9}, 4,
             {{1,2,3},{4,5},{6,7},{8,9}}, {3,2,2,2});

    // 9) n=8, k=3 -> 3,3,2
    run_test(9, {5,6,7,8,9,10,11,12}, 3,
             {{5,6,7},{8,9,10},{11,12}}, {3,3,2});

    // 10) n=6, k=4 -> 2,2,1,1
    run_test(10, {9,8,7,6,5,4}, 4,
             {{9,8},{7,6},{5},{4}}, {2,2,1,1});

    cout << "Todos los tests pasaron. 🎯\n";
    return 0;
}