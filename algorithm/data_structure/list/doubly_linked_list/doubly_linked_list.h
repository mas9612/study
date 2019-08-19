#ifndef __DOUBLY_LINKED_LIST
#define __DOUBLY_LINKED_LIST

#include <stddef.h>

class ListNode {
    ListNode* next;
    ListNode* prev;
    int value;

   public:
    ListNode() : next(NULL), prev(NULL) {}

    int get_value() { return value; }
    void set_value(int value) { this->value = value; }
    ListNode* get_next() { return next; }
    void set_next(ListNode* next) { this->next = next; }
    ListNode* get_prev() { return prev; }
    void set_prev(ListNode* prev) { this->prev = prev; }
};

class DoublyLinkedList {
    ListNode* head;

   public:
    DoublyLinkedList() : head(NULL) {}
    ~DoublyLinkedList();

    void append_node(int);
    void insert_node(ListNode*, int);
    void delete_node(ListNode*);
    ListNode* search_node(int);

    void print_list();
};

#endif
