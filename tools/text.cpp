#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ifstream in("../cpp/tex.pool");
	int num = 256;
	do
	{
		char d = in.get();
		if (d == '*')
			break;
		d -= '0';
		char u = in.get()-'0';
		int n = d*10+u;
		string s;
		for (int i = 0; i < n; i++)
			s += in.get();
		cout << "texte[\"" << s << "\"] = " << num++ << ";\n";
		in.ignore();
	} while (true);
}
