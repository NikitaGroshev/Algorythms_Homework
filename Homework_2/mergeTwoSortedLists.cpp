#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) {
        return list2;
    }
    if (list2 == nullptr) {
        return list1;
    }
    ListNode* new_head;
    if (list1->val <= list2->val) {
        new_head = list1;
        list1 = list1->next;
    }
    else {
        new_head = list2;
        list2 = list2->next;
    }
    ListNode* ans = new_head;
    while(list1 && list2) {
        if (list1->val <= list2->val) {
            new_head->next = list1;
            list1 = list1->next;
            new_head = new_head->next;
        }
        else{
            new_head->next = list2;
            list2 = list2->next;
            new_head = new_head->next;
        }
    }
    if (list1 != nullptr) {
        while (list1) {
            new_head->next = list1;
            list1 = list1->next;
            new_head = new_head->next;
        }
    }
    if (list2 != nullptr) {
        while (list2) {
            new_head->next = list2;
            list2 = list2->next;
            new_head = new_head->next;
        }
    }
    return ans;
}

int main() {
    ListNode* lst1 = new ListNode(1);
    lst1->next = new ListNode(2);
    lst1->next->next = new ListNode(4);
    ListNode* lst2 = new ListNode(1);
    lst2->next = new ListNode(3);
    lst2->next->next = new ListNode(4);
    ListNode* head = mergeTwoLists(lst1, lst2);
    std::cout << "Merged list: ";
    while (head) {
        std::cout << head->val << " ";
        head = head->next;
    }
}