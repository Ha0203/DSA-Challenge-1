#pragma once

#include <string>
#include <stack>
#include <iostream>
using namespace std;

struct node
{
    string data;
    node* left;
    node* right;
};

// Function List
node* buildExpressionTree(string infix);
void printTree(node* root);
void removeTree(node* &root);