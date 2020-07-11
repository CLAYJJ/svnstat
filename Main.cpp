#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
// svn url -r {start}:{end} -v --diff > svn.log
using string = std::string;

int main(int argc, char** argv) {
	if (argc != 4) {
		std::cout << "Usage: svnstat.exe <svn url> <start date> <end date>\n";
		return -1;
	}
	string command = "svn log ";
	command.append(argv[1]).append(" -r {").append(argv[2])
		.append("}:{").append(argv[3]).append("} -v --diff > svn.log");
	system(command.c_str());


	std::ifstream f("svn.log");
	string line;
	string flag = "------------------------------------------------------------------------";
	string before, name;
	int a, b;
	std::unordered_map<string, int> ret;
	while (getline(f, line)) {
		if (line == flag) {
			before = flag;
			continue;
		}
		if (before == flag) {
			before = line;
			a = line.find('|', 0);
			b = line.find('|', a+1);
			name = line.substr(a+1, b-a-1);
			continue;
		}
		if (line.size() > 2 && line.at(0) == '+' && line.at(1) != '+') {
			before = line;
			ret[name] = ret[name] + 1;
		} 
	}
	for (auto it = std::begin(ret); it != std::end(ret); ++it) {
		std::cout << it->first << ": " << it->second << "\n";
	}
	return 0;
}