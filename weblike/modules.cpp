#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

string trim(const string &s)
{
	auto t = s;
	while (t[0] == ' ')
		t = t.substr(1);
	while (t.back() == ' ')
		t = t.substr(0, t.size()-1);
	while (t.find("  ") != string::npos)
		t.replace(t.find("  "), 2, " ");
	return t;
}

int main(void)
{
	ifstream eq("test.eq");
	map<string, string> equiv;
	for (string line, equ; getline(eq, line) && getline(eq, equ);)
		equiv[line] = equ;
	ifstream mod("test.mod");
	map<string, string> modules;
	string current;
	for (string line; getline(mod, line);)
		if (line.find("MODULE:") == 0)
			current = equiv[trim(line.substr(8))];
		else
		{
			auto pos = line.find("INSERT:");
			if (pos != string::npos)
				line = "INSERT: "+equiv[trim(line.substr(pos+8))];
			modules[current] += line+"\n";
		}
/*	ofstream out("test.mdl");
	for (auto &s: modules)
	{
		out << "{********************************************************************************************}\n";
		out << "MODULE: " << s.first << endl;
		out << "{********************************************************************************************}\n";
		out << s.second << endl;
	}*/
	ifstream in("test.pas");
	string pascal;
	for (string line; getline(in, line);)
		pascal += line+"\n";
	istringstream iss(pascal);
	bool insert = true;
	int n = 1;
	string output;
	while (insert)
	{
		insert = false;
		cout << "passe" << n << endl;
		for (string line; getline(iss, line);)
		{
			auto pos = line.find("INSERT:");
			if (pos != string::npos)
			{
				output += "(*INSERT "+equiv[trim(line.substr(pos+8))]+"*)"+modules[equiv[trim(line.substr(pos+8))]]+"(*FIN INSERT "+equiv[trim(line.substr(pos+8))]+"*)";
				insert = true;
			}
			else
				output += line+"\n";
		}
/*		if (n == 1)
			break;*/
		if (insert)
		{
			iss.clear();
			iss.str(output);
			output = "";
		}
		n++;
	}
	ofstream out("test.pcl");
	out << output;		
}
