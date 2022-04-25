#include <iostream>
#include <algorithm>
#include "arraylist.h"
#include <vector>
#include "p2.h"
#include "LinkedList.h"
#include "stack.h"
using std::cout;
using std::cin;
using std::endl;
using qimg::ArrayList;
#include "binary_tree.h"
#include <windows.h>
#include <list>
#include <forward_list>
#include <memory>
#include <set>
#include "my_deque.h"
int main()
{
    qimg::list<int> ls{1,2,3,4,5};
    for (const auto &item: ls) {
        cout << item << " ";
    }
    return 0;
}