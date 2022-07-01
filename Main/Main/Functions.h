#pragma once

#include <string>
#include <stack>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;

struct node
{
    string data;
    node* left = nullptr;
    node* right = nullptr;
    bool IsLeaf();
};

struct RESULT
{
    node* Tree = nullptr;
    float Result = 0;
    char Error = 'E';
    bool ErrorFlag = false;
    string Postfix = "";

    bool PostOrder();
    float Calculate(node* root);
};

// Function List
node* buildExpressionTree(string infix);
void printTree(node* root);
void removeTree(node*& root);
bool checkInfix(string infix); 
float Process(string operand, float op1, float op2);