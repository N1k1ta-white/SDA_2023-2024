//
// Created by Nikita on 10.09.2024.
//
#pragma once

#ifndef HW_LISTNODE_H
#define HW_LISTNODE_H

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

#endif //HW_LISTNODE_H
