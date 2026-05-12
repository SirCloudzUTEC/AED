#include <vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;

    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class Solution {
public:

    vector<ListNode*> minHeap;

    void subir(int pos) {

        while (pos > 0) {

            int padre = (pos - 1) / 2;

            if (minHeap[padre]->val <= minHeap[pos]->val) {
                break;
            }

            swap(minHeap[padre], minHeap[pos]);

            pos = padre;
        }
    }

    void bajar(int pos) {

        while (true) {

            int izq = 2 * pos + 1;
            int der = 2 * pos + 2;

            int menor = pos;

            if (izq < minHeap.size() &&
                minHeap[izq]->val < minHeap[menor]->val) {
                menor = izq;
            }

            if (der < minHeap.size() &&
                minHeap[der]->val < minHeap[menor]->val) {
                menor = der;
            }

            if (menor == pos) {
                break;
            }

            swap(minHeap[pos], minHeap[menor]);

            pos = menor;
        }
    }

    void insertar(ListNode* nodo) {

        minHeap.push_back(nodo);

        subir(minHeap.size() - 1);
    }

    ListNode* sacarMin() {

        ListNode* menor = minHeap[0];

        minHeap[0] = minHeap.back();

        minHeap.pop_back();

        if (!minHeap.empty()) {
            bajar(0);
        }

        return menor;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {

        for (ListNode* cabeza : lists) {

            if (cabeza != nullptr) {
                insertar(cabeza);
            }
        }

        ListNode dummy;

        ListNode* actual = &dummy;

        while (!minHeap.empty()) {

            ListNode* nodo = sacarMin();

            actual->next = nodo;

            actual = actual->next;

            if (nodo->next != nullptr) {
                insertar(nodo->next);
            }
        }

        return dummy.next;
    }
};