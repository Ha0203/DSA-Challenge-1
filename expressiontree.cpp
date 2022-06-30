#include "expressiontree.h"

// Implementation
// Build
void modifyInfix(string& infix) {
    int pos = 0;
    for (int i = 0; i < infix.size(); i++)
        if (infix[i] != ' ') {
            infix[pos] = infix[i];
            pos++;
        }
    infix.erase(pos);
    infix = "(" + infix + ")";
}

int getPriority(string c) {
    if (c == "^")
        return 3;
    if (c == "*" || c == "/")
        return 2;
    if (c == "+" || c == "-")
        return 1;
    return 0;
}

node* createNode(string key) {
    node* newNode = new node;
    newNode->data = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

node* buildExpressionTree(string infix) {
    modifyInfix(infix);
    stack<string> strStack;
    stack<node*> nodeStack;
    node *tmp, *tmp1, *tmp2;

    for (int i = 0; i < infix.size(); i++) {
        if (infix[i] == '(')
            strStack.push(infix.substr(i, 1));
        else if (isdigit(infix[i])) {
            int numdigit = 1;
            for (int j = i + 1; j < infix.size(); j++)
                if (isdigit(infix[j]) || infix[j] == '.')
                    numdigit++;
                else
                    break;
            tmp = createNode(infix.substr(i, numdigit));
            nodeStack.push(tmp);
            i = i + numdigit - 1;
        }
        else if (getPriority(infix.substr(i, 1)) > 0) {
            while (!strStack.empty() && strStack.top() != "(" && infix[i] != '^' && getPriority(strStack.top()) >= getPriority(infix.substr(i, 1))) {
                tmp = createNode(strStack.top());
                strStack.pop();
                tmp1 = nodeStack.top();
                nodeStack.pop();
                tmp2 = nodeStack.top();
                nodeStack.pop();
                tmp->left = tmp2;
                tmp->right = tmp1;
                nodeStack.push(tmp);
            }
            strStack.push(infix.substr(i, 1));
        }
        else if (infix[i] == ')') {
            while (!strStack.empty() && strStack.top() != "(") {
                tmp = createNode(strStack.top());
                strStack.pop();
                tmp1 = nodeStack.top();
                nodeStack.pop();
                tmp2 = nodeStack.top();
                nodeStack.pop();
                tmp->left = tmp2;
                tmp->right = tmp1;
                nodeStack.push(tmp);
            }
            strStack.pop();
        }
    }
    tmp = nodeStack.top();
    return tmp;
}

// Print
void print2DUtil(node* root, int space) {
    if (root == NULL)
        return;
    space += 10;
    print2DUtil(root->right, space);
    cout << endl;
    for (int i = 10; i < space; i++)
        cout<<" ";
    cout << root->data << endl;
    print2DUtil(root->left, space);
}

void printTree(node* root) {
    cout << "-----------------------------------------------------------------------------------------------" << endl;
    print2DUtil(root, 0);
    cout << "-----------------------------------------------------------------------------------------------" << endl;
}

// Delete
void removeTree(node* &root) {
    if (root == NULL)
        return;
    removeTree(root->left);
    removeTree(root->right);
    delete root;
}