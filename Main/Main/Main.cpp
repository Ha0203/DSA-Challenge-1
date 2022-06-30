#include"Functions.h"

void instruct() {

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
int main(int argc, char* argv[])
{
	/*if (argc != 5) {
		cout << "Fail" << endl;
		instruct();
		return 0;
	}
	if (atoi(argv[2]) <= 0) {
		cout << "Fail" << endl;
		instruct();
		return 0;
	}
	vector<string> exp = readFile(argv[1], atoi(argv[2]));
	if (argv[3] == "-c") {
		
	}
	else if (argv[3] == "-t") {

	}*/

	char* s = new char[2]{ '-', 'c'};

	if (s == "-c")
		cout << 1;
	return 0;
}