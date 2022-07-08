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
bool RESULT::PostOrder()
{
	if (!Tree)
	{
		return false;
	}
	stack<node*> first;

	first.push(Tree);
	node* left = nullptr;
	node* right = nullptr;

	while (!first.empty())
	{
		left = first.top()->left;
		right = first.top()->right;
		Postfix = first.top()->data + Postfix;
		first.pop();
		if (left)
			first.push(left);
		if (right)
			first.push(right);
		if (!first.empty())
			Postfix = " " + Postfix;
	}

	return true;
}
float Process(string operand, float op1, float op2)
{
	if (operand == "+")
		return op1 + op2;
	else if (operand == "-")
		return op1 - op2;
	else if (operand == "*")
		return op1 * op2;
	else if (operand == "^")
		return pow(op1, op2);
	else
		return op1 / op2;
}
float RESULT::Calculate(node* root)
{
	if (!root)
	{
		return false;
	}

	if (root->IsLeaf())
	{
		return stof(root->data);
	}

	float op1 = Calculate(root->left);
	float op2 = Calculate(root->right);

	if (root->data == "/" && op2 == 0)
	{
		ErrorFlag = true;
		return INT16_MAX;
	}

	return Process(root->data, op1, op2);
}

bool node::IsLeaf()
{
	return left == nullptr && right == nullptr;
}

void instruct() {
	cout << "\n--------------INSTRUCTION--------------\n";
	cout << "Pattern is: A.exe InputPath N Action OutputPath\n";
	cout << "in which:\n";
	cout << "\t∗ A.exe: Your execution '.exe' file.\n";
	cout << "\t∗ InputPath : Path to the 'input.txt' file.\n";
	cout << "\t∗ N : an integer, represent the number of expressions from the 'input.txt' file.\n";
	cout << "\t∗ Action : • - c : calculate the identified the expressions.\n";
}

vector<string> readFile(string path, int n) {
	vector<string> v;
	fstream file;
	file.open(path, ios::in);
	if (file.fail())
		return v;
	for (int i = 0; i < n && !file.eof(); i++) {
		string line;
		getline(file >> ws, line);
		v.push_back(line);
	}
	file.close();
	return v;
}

//bool writeFile(vector<string> output, string path) {
//	fstream file;
//	file.open(path, ios::out);
//	while (!output.empty()) {
//		file << output.back() << endl;
//		output.pop_back();
//	}
//	file.close();
//
//	return true;
//}

bool writeFile(vector<RESULT> result, string path, string mode)
{
	ofstream file;
	file.open(path);
	bool first = true;

	if (!file.is_open())
	{
		return false;
	}

	if (mode == "-t")
	{
		for (const auto& i : result)
		{
			if (first)
				first = false;
			else
				file << endl;
			if (i.ErrorFlag)
			{
				file << i.Error;
			}
			else
			{
				file << i.Postfix;
			}
		}
	}
	else
	{
		for (const auto& i : result)
		{
			if (first)
				first = false;
			else
				file << endl;
			if (i.ErrorFlag)
			{
				file << i.Error;
			}
			else
			{
				file << fixed << setprecision(2) << i.Result;
			}
		}
	}

	file.close();
	return true;
}

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
	node* tmp, * tmp1, * tmp2;

	for (int i = 0; i < infix.size(); i++) {
		if (infix[i] == '(' || infix[i] == '[' || infix[i] == '{')
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
			while (!strStack.empty() && strStack.top() != "(" && strStack.top() != "[" && strStack.top() != "{" && infix[i] != '^' && getPriority(strStack.top()) >= getPriority(infix.substr(i, 1))) {
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
		else if (infix[i] == ')' || infix[i] == ']' || infix[i] == '}') {
			while (!strStack.empty() && strStack.top() != "(" && strStack.top() != "[" && strStack.top() != "{") {
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
		cout << " ";
	cout << root->data << endl;
	print2DUtil(root->left, space);
}

void printTree(node* root) {
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	print2DUtil(root, 0);
	cout << "-----------------------------------------------------------------------------------------------" << endl;
}

// Delete
void removeTree(node*& root) {
	if (root == NULL)
		return;
	removeTree(root->left);
	removeTree(root->right);
	delete root;
	root = NULL;
}
bool checkInfix(string infix) {
	stack<char>s;
	bool isoperator = 0; //The loop is not for operator, loop for operand
	for (int i = 0; i < infix.length();) {
		if (infix[i] == '(' || infix[i] == '[' || infix[i] == '{') {
			s.push(infix[i]);
			i++;
			continue;
		}
		//Number
		else if (isdigit(infix[i])) {
			if (isoperator == 1)
				return 0;
			isoperator = 1;
			bool isfloat = 0;
			int numdedigit = 0;
			while (isdigit(infix[i]) || infix[i] == '.') {
				if (isfloat == 1)
					numdedigit++;
				if (infix[i] == '.')
					isfloat = 1;
				if (numdedigit > 2)
					return 0;
				i++;
			}
		}
		else if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/' || infix[i] == '^') {
			if (isoperator == 0)
				return 0;
			isoperator = 0;
			i++;
		}
		else
			return 0;
		//Check synthesis
		if (i >= infix.length())
			break;
		while (i < infix.length() && infix[i] != ' ') {
			if (infix[i] != ')' && infix[i] != ']' && infix[i] != '}')
				return 0;
			else {
				if (s.empty())
					return 0;
				if (infix[i] == ')' && s.top() != '(')
					return 0;
				else if (infix[i] == ']' && s.top() != '[')
					return 0;
				else if (infix[i] == '}' && s.top() != '{')
					return 0;
				s.pop();
				i++;
			}
		}
		i++;
	}
	if (!s.empty())
		return 0;
	return 1;
}
int main(int argc, char* argv[])
{
	if (argc != 5) {
		cout << "Fail" << endl;
		instruct();
		return 0;
	}
	if (atoi(argv[2]) <= 0) {
		cout << "Fail" << endl;
		instruct();
		return 0;
	}
	vector<string> input = readFile((string)argv[1], atoi(argv[2]));
	if ((string)argv[3] == "-c") {
		//Hàm trả về vector các string results
		cout << "calculate" << endl;
		vector<RESULT> result;
		RESULT* temp = nullptr;

		for (const auto& i : input)
		{
			temp = new RESULT;
			if (checkInfix(i))
			{
				temp->Tree = buildExpressionTree(i);
				temp->Result = temp->Calculate(temp->Tree);
			}
			else
			{
				temp->ErrorFlag = true;
			}
			result.push_back(*temp);
			delete temp;
		}

		if (writeFile(result, argv[4], argv[3]))
		{
			cout << "Calculate Successfull!\n";
		}
		else
		{
			cout << "Invalid FILE/PATH name\n";
		}

		for (auto& i : result)
			removeTree(i.Tree);
	}
	else if ((string)argv[3] == "-t") {
		//Hàm trả về vector các string postfix
		cout << "convert" << endl;
		vector<RESULT> result;
		RESULT* temp = nullptr;

		for (const auto& i : input)
		{
			temp = new RESULT;
			if (checkInfix(i))
			{
				temp->Tree = buildExpressionTree(i);
				temp->PostOrder();
			}
			else
			{
				temp->ErrorFlag = true;
			}
			result.push_back(*temp);
			delete temp;
		}

		if (writeFile(result, argv[4], argv[3]))
		{
			cout << "Transfer Successfull!\n";
		}
		else
		{
			cout << "Invalid FILE/PATH name\n";
		}

		for (auto& i : result)
			removeTree(i.Tree);
	}
	else {
		cout << "Fail" << endl;
		instruct();
		return 0;
	}
	return 0;
}