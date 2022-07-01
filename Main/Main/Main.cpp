#include"Functions.h"

void instruct() {
	cout << "\n--------------INSTRUCTION--------------\n";
	cout << "Pattern is: A.exe InputPath N Action OutputPath\n";
	cout << "in which:\n";
	cout << "\t∗ A.exe: Your execution '.exe' file.\n";
	cout << "\t∗ InputPath : Path to the 'input.txt' file.\n";
	cout << "\t∗ N : an integer, represent the number of expressions from the 'input.txt' file.\n";
	cout << "\t∗ Action : • - c : calculate the identified the expressions.\n";
}
vector<string> readFile(string path,int n) {
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
bool writeFile(vector<string> output, string path) {
	fstream file;
	file.open(path, ios::out);
	while (!output.empty()) {
		file << output.back() << endl;
		output.pop_back();
	}
	file.close();

	return true;
}

bool writeFile(vector<RESULT> result, string path, string mode)
{
	ofstream file;
	file.open(path);
	bool first = true;

	if(!file.is_open())
	{
		return false;
	}

	if(mode == "-t")
	{
		for(const auto &i : result)
		{
			if(first)
				first = false;
			else 
				file << endl;
			if(i.ErrorFlag)
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
		for(const auto &i : result)
		{
			if(first)
				first = false;
			else 
				file << endl;
			if(i.ErrorFlag)
			{
				file << i.Error;
			}
			else 
			{
				file << i.Result;
			}
		}
	}

	file.close();
	return true;
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

		for(const auto &i : input)
		{
			temp = new RESULT;
			if(checkInfix(i))
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

		if(writeFile(result, argv[4], argv[3]))
		{
			cout << "Calculate Successfull!\n";
		}
		else
		{
			cout << "Invalid FILE/PATH name\n";
		}

		for(auto &i : result)
			removeTree(i.Tree);
	}
	else if ((string)argv[3] == "-t") {
		//Hàm trả về vector các string postfix
		cout << "convert" << endl;
		vector<RESULT> result;
		RESULT* temp = nullptr;

		for(const auto &i : input)
		{
			temp = new RESULT;
			if(checkInfix(i))
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

		if(writeFile(result, argv[4], argv[3]))
		{
			cout << "Transfer Successfull!\n";
		}
		else
		{
			cout << "Invalid FILE/PATH name\n";
		}

		for(auto &i : result)
			removeTree(i.Tree);
	}
	else {
		cout << "Fail" << endl;
		instruct();
		return 0;
	}
	return 0;
}