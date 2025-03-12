#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

ListNode* DeleteDuplicates(ListNode* head) {
    if (head == nullptr) {
        return head;
    }
    ListNode* ptr_slow = head;
    ListNode* ptr_fast = head->next;
    ListNode* ptr_prev = nullptr;
    while (ptr_slow->next)
    {
        if (ptr_slow->val == ptr_fast->val && ptr_prev == nullptr) {
            while (ptr_fast != nullptr && ptr_slow->val == ptr_fast->val) {
                ptr_fast = ptr_fast->next;
            }
            head = ptr_fast;
            ptr_slow = ptr_fast;
            if (ptr_fast == nullptr) {
                return head;
            }
            ptr_fast = ptr_fast->next;
        }
        else if (ptr_slow->val == ptr_fast->val) {
            while (ptr_fast != nullptr && ptr_slow->val == ptr_fast->val) {
                ptr_fast = ptr_fast->next;
            }
            ptr_prev->next = ptr_fast;
            ptr_slow = ptr_fast;
            if (ptr_fast == nullptr) {
                return head;
            }
            ptr_fast = ptr_fast->next;
        }
        else {
            ptr_prev = ptr_slow;
            ptr_slow = ptr_slow->next;
            ptr_fast = ptr_fast->next;
        }
    }
    return head;
}

int main() {
    ListNode* head = new ListNode(0);
    head->next = new ListNode(1);
    head->next->next = new ListNode(1);
    head->next->next->next = new ListNode(2);
    head->next->next->next->next = new ListNode(3);
    ListNode* new_head = DeleteDuplicates(head);
    std::cout << "Elements of list: ";
    while (new_head) {
        std::cout << new_head->val << " ";
        new_head = new_head->next;
    }
}