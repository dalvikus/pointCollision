#include <iostream>
using namespace std;
#include "Interval.h"
#include "Node.h"
#include <assert.h>

int main(void)
{
#if 0
#if 0
#define H_MAX   2
#define V_MAX   3
    bool a[V_MAX][H_MAX] = {
        {0, 1},
        {1, 1},
        {1, 1},
    };
#else
#define H_MAX   3
#define V_MAX   2
    bool a[V_MAX][H_MAX] = {
        {0, 1, 1},
        {0, 1, 1},
    };
#endif
#else
#define H_MAX   16
#define V_MAX   16
    bool a[H_MAX][V_MAX] = {
        {1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    };
#endif
    Node   rootNode(Interval(0, H_MAX - 1), Interval(0, V_MAX - 1));
    for (int row = 0; row < V_MAX; ++row) {
        for (int col = 0; col < H_MAX; ++col) {
//          a[row][col] = 1;
            if (a[row][col]) {
                rootNode.add(col, row);
            }
        }
    }
    bool b[V_MAX][H_MAX];
    for (int row = 0; row < V_MAX; ++row) {
        for (int col = 0; col < H_MAX; ++col) {
            b[row][col] = rootNode.contains(col, row);
        }
    }
    for (int row = 0; row < V_MAX; ++row) {
        for (int col = 0; col < H_MAX; ++col) {
            cout << a[row][col] << "(" << b[row][col] << ") ";
            assert(a[row][col] == b[row][col]);
        }
        cout << endl;
    }
//  rootNode.walk(0);

    rootNode.simplify();
    bool c[V_MAX][H_MAX];
    for (int row = 0; row < V_MAX; ++row) {
        for (int col = 0; col < H_MAX; ++col) {
            c[row][col] = rootNode.contains2(col, row);
        }
    }
    for (int row = 0; row < V_MAX; ++row) {
        for (int col = 0; col < H_MAX; ++col) {
            cout << a[row][col] << "(" << c[row][col] << ") ";
            assert(a[row][col] == c[row][col]);
        }
        cout << endl;
    }
//  rootNode.walk(0);

    // test of copy constructor
    Node   n1 = rootNode;

    return 0;
}
