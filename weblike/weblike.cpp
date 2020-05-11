#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;

static map<char, ofstream*> out;

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

bool smaller(const string &A, const string &B)
{
	auto a = trim(A), b = trim(B);
	auto posA = a.find("..."), posB = b.find("...");
	if (posA != string::npos)
	{
		if (posB != string::npos)
			return a.substr(0, std::min(posA, posB)) < b.substr(0, std::min(posA, posB));
		return a.substr(0, posA) < b.substr(0, posA);
	}
	if (posB != string::npos)
		return a.substr(0, posB) < b.substr(0, posB);
	return a < b;
}

string quote(const string &s, bool inQuote = false)
{
	string t;
	for (const char &c: s)
		switch (c)
		{
			case '\n':
				break;
			case '\"':
				inQuote = ~inQuote;
				t += "\'";
				break;
			case '\'':
				if (inQuote)
					t += "\'\'";
				else
					t += "\'";
				break;
			default:
				t += c;
		}
			
	return t;
}

string name(const string &s)
{
	if (s.size() && s[0] != ' ')
		return quote("\""+s+"\"");
	return quote("\""+s.substr(1)+"\"");
}

map<char, int> brace;
map<char, int> inQuote;

void write(char mode, const string &s)
{
	if (s == "`\\.{\\#\\{}\' ")
	{
		*(out[mode]) << "`\\.[\\#\\[]\' " << endl;
		return;
	}
	if (s == "`\\.\\}\' ")
	{
		*(out[mode]) << "`\\.\\]\' " << endl;
		return;
	}
	if (s == "\\{ ")
	{
		*(out[mode]) << "\\[" << endl;
		return;
	}
	if (s == "\\} ")
	{
		*(out[mode]) << "\\] " << endl;
		return;
	}
	if (s == "\\}, ")
	{
		*(out[mode]) << "\\], " << endl;
		return;
	}
	if (s == "\\}\'\'s*) ")
	{
		*(out[mode]) << "\\]\'\'s*) " << endl;
		return;
	}
	for (const char &c: s)
		switch (c)
		{
			case '{':
				if (inQuote[mode])
				{
					*(out[mode]) << "{";
					break;
				}
				if (brace[mode]++)
					*(out[mode]) << "[";
				else
					*(out[mode]) << "{";
				break;
			case '}':
				if (inQuote[mode])
				{
					*(out[mode]) << "}";
					break;
				}
				if (--brace[mode])
					*(out[mode]) << "]";
				else
					*(out[mode]) << "}";
				break;
			case '\'':
				if (!brace[mode])
				{
					inQuote[mode] = ~inQuote[mode];
				}
				*(out[mode]) << c;
				break;
			default:
				*(out[mode]) << c;
		}
}

int main()
{
	int moduleNb = 0;
	ifstream in("../tex.web");
	ofstream txt("test.txt");
	ofstream pas("test.pas");
	ofstream def("test.def");
	ofstream mod("test.mod");
	ofstream form("test.for");
	out['T'] = &txt;
	out['P'] = &pas;
	out['D'] = &def;
	out['M'] = &mod;
	out['F'] = &form;
	char mode = 'T'; // limbo
	set<string> moduleNames;
	for (string line; getline(in, line);)
	{
		line = quote(line);
		while (line.find("@^") != string::npos)
		{
			auto deb = line.find("@^");
			auto fin = line.find("@>");
			line.replace(deb, fin-deb+2, "(*"+quote(line.substr(deb+2, fin-deb-2), true)+"*)");
		}
		while (line.find("@.") != string::npos)
		{
			auto deb = line.find("@.");
			auto fin = line.find("@>");
			line.replace(deb, fin-deb+2, "(*"+quote(line.substr(deb+2, fin-deb-2), true)+"*)");
		}
		while (line.find("@:") != string::npos)
		{
			auto deb = line.find("@:");
			auto fin = line.find("@>");
			line.replace(deb, fin-deb+2, "(*"+quote(line.substr(deb+2, fin-deb-2), true)+"*)");
		}
		while (line.find("@t") != string::npos)
		{
			auto deb = line.find("@t");
			auto fin = line.find("@>");
			auto l = line.substr(deb+2, fin-deb-2);
			line.replace(deb, fin-deb+2, "(*"+quote(line.substr(deb+2, fin-deb-2), true)+"*)");
		}
		istringstream iss(line);
		for (string word; getline(iss, word, ' ');)
		{
			while (word.find("@'") != string::npos)
			{
				auto pos = word.find("@'");
				if (pos > 1 && word.substr(pos-1, 2) == "@@")
					break;
				string before = word.substr(0, pos);
				string after = word.substr(pos+2);
				istringstream iss2(after);
				int i;
				string end;
				iss2 >> oct >> i >> end;
				word = before+to_string(i)+end;
			}
			while (word.find("@\"") != string::npos)
			{
				auto pos = word.find("@\"");
				if (pos > 1 && word.substr(pos-1, 2) == "@@")
					break;
				string before = word.substr(0, pos);
				string after = word.substr(pos+2);
				istringstream iss2(after);
				int i;
				string end;
				iss2 >> hex >> i >> end;
				word = before+to_string(i)+end;
			}
			while (word.find("@@") != string::npos)
				word.replace(word.find("@@"), 2, "@");
			while (word.find("@&") != string::npos)
				word.replace(word.find("@&"), 2, "");
			while (word.find("@\\") != string::npos)
				word.replace(word.find("@\\"), 2, "");
			while (word.find("@\\") != string::npos)
				word.replace(word.find("@\\"), 2, "\n");
			while (word.find("@/") != string::npos)
				word.replace(word.find("@/"), 2, "\n");
			while (word.find("@#") != string::npos)
				word.replace(word.find("@#"), 2, "\n\n");
			while (word.find("@|") != string::npos)
				word.replace(word.find("@|"), 2, "");
			while (word.find("@!") != string::npos)
				word.replace(word.find("@!"), 2, "");
			while (word.find("@?") != string::npos)
				word.replace(word.find("@?"), 2, " ");
			while (word.find("@+") != string::npos)
				word.replace(word.find("@+"), 2, "");
			while (word.find("@;") != string::npos)
				word.replace(word.find("@;"), 2, ";");
			while (word.find("@,") != string::npos)
				word.replace(word.find("@,"), 2, " ");
			if (mode == 'P')
			{
				while (word.find("@$") != string::npos)
					word.replace(word.find("@$"), 2, "117275187");
				while (word.find("@{") != string::npos)
					word.replace(word.find("@{"), 2, "(*");
				while (word.find("@}") != string::npos)
					word.replace(word.find("@}"), 2, "*)");
				while (word.find("@&") != string::npos)
					word.replace(word.find("@&"), 2, "");
			}
			if (word == "@")
			{
				if (mode != 'T' && (inQuote[mode] || brace[mode]))
				{
					cerr << ":" << endl;
					return 1;
				}
				mode = 'T'; // tex
				moduleNb++;
				write(mode, "\nMODULE"+to_string(moduleNb)+"\n");
			}
			else if (word.substr(0, 2) == "@*")
			{
				if (mode != 'T' && (inQuote[mode] || brace[mode]))
				{
					cerr << ":" << endl;
					return 1;
				}
				mode = 'T'; // tex
				moduleNb++;
				write(mode, "\nSPECIAL MODULE "+to_string(moduleNb)+":  ");
				if (word != "@*")
					write(mode, word.substr(2)+" ");
				getline(iss, word);
				write(mode, word+"\n");
				break;
			}
			else if (word.substr(0, 2) == "@d")
			{
				mode = 'D'; // definition
				if (word != "@d")
					write(mode, word.substr(2)+" ");
			}
			else if (word.substr(0, 2) == "@f")
			{
				mode = 'F'; // format
				if (word != "@f")
					write(mode, word.substr(2)+" ");
			}
			else if (word.substr(0, 2) == "@p")
			{
				mode = 'P'; // pascal
				write(mode, "\n(***PASCAL module "+to_string(moduleNb)+"***)\n");
				if (word != "@p")
					write(mode, word.substr(2)+" ");
			}
			else if (word.find("@<") != string::npos)
			{
				ostringstream oss;
				write(mode, word.substr(0, word.find("@<")));
				word = word.substr(word.find("@<")+2);
				if (word.find("@>") != string::npos)
				{
					oss << word.substr(0, word.find("@>")) << " ";
					word = word.substr(word.find("@>")+2);
				}
				else
				{
					oss << word << " ";
					getline(iss, word);
					while (word.find("@>") == string::npos)
					{
						oss << word << " ";
						getline(in, word);
					}
					oss << word.substr(0, word.find("@>")) << endl;
					word = word.substr(word.find("@>")+2);
				}
				moduleNames.insert(name(oss.str()));
				if (word == "=")
				{
					mode = 'M'; // module
					write(mode, "MODULE: "+name(oss.str())+"\n");
					write(mode, "(*PASCAL module "+to_string(moduleNb)+"*)");
				}
				else
				{
					write(mode, "\nINSERT: "+name(oss.str())+"\n");
					iss.clear();
					iss.str(word);
				}
			}
			else
			{
				write(mode, word+" ");
			}
		}
		write(mode, "\n");
	}
	vector<string> modules;
	for (auto &s: moduleNames)
		modules.push_back(s);
	stable_sort(modules.begin(), modules.end(), smaller);
	modules.push_back("ZZZZ"); // dummy
	auto n = modules.size();
	string big = modules[0];
	map<string, string> equiv;
	for (size_t i = 0, j = 0; i < n-1; i++)
		if (smaller(modules[i], modules[i+1]))
		{
			for (; j <= i; j++)
				equiv[modules[j]] = big;
			big = modules[i+1];
		}
		else // equivalentes
		{
			if (modules[i+1].size() > big.size())
				big = modules[i+1];
		}
	modules.pop_back();
	ofstream eq("test.eq");
	for (auto &s: modules)
		eq << trim(s) << endl << trim(equiv[s]) << endl;
}

