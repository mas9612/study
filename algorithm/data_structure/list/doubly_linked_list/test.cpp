#include <iostream>
#include "doubly_linked_list.h"

using namespace std;

int main() {
    DoublyLinkedList list;

    list.append_node(0);
    list.append_node(2);
    list.append_node(3);

    ListNode* node = list.search_node(2);
    list.insert_node(node, 1);

    list.append_node(5);
    node = list.search_node(5);
    list.insert_node(node, 4);

    list.delete_node(node);
    node = list.search_node(0);
    list.delete_node(node);

    cout << "\n===== test =====\n";
    cout << "got:\n";
    list.print_list();
    cout << "expected:\n";
    cout << "1 2 3 4\n";
    cout << "================\n\n";
}
