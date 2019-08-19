#include "doubly_linked_list.h"
#include <iostream>

DoublyLinkedList::~DoublyLinkedList() {
    ListNode* node = head;
    while (node != NULL) {
        ListNode* current = node;
        node = node->get_next();
        delete current;
    }
}

void DoublyLinkedList::append_node(int value) {
    ListNode* node = new ListNode;
    node->set_value(value);

    if (head == NULL) {
        head = node;
    } else {
        ListNode *ptr1 = head, *ptr2;
        while (ptr1 != NULL) {
            ptr2 = ptr1;
            ptr1 = ptr1->get_next();
        }

        ptr2->set_next(node);
        node->set_prev(ptr2);
    }
}

void DoublyLinkedList::insert_node(ListNode* node, int value) {
    if (node == NULL)
        return;

    ListNode* new_node = new ListNode;
    new_node->set_value(value);

    ListNode* prev = node->get_prev();
    prev->set_next(new_node);
    new_node->set_prev(prev);

    new_node->set_next(node);
    node->set_prev(new_node);
}

void DoublyLinkedList::delete_node(ListNode* node) {
    if (node == NULL)
        return;

    ListNode* ptr = head;
    while (ptr != NULL) {
        if (ptr == node) {
            ListNode* prev = ptr->get_prev();
            ListNode* next = ptr->get_next();
            if (prev != NULL)
                prev->set_next(next);
            if (next != NULL)
                next->set_prev(prev);

            // if node which will be deleted is the head node, move head to the
            // second node
            if (ptr == head)
                head = next;

            delete ptr;
            break;
        }
        ptr = ptr->get_next();
    }
}

ListNode* DoublyLinkedList::search_node(int value) {
    if (head == NULL)
        return NULL;

    ListNode* node = head;
    while (node != NULL) {
        if (node->get_value() == value)
            return node;

        node = node->get_next();
    }

    return NULL;
}

void DoublyLinkedList::print_list() {
    ListNode* node = head;
    if (node != NULL) {
        std::cout << node->get_value();
        node = node->get_next();
    }

    while (node != NULL) {
        std::cout << ' ' << node->get_value();
        node = node->get_next();
    }
    std::cout << '\n';
}
