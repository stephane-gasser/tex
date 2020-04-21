#include <fstream>
#include <sstream>

using namespace std;

int main()
{
/*	ifstream in("glue.pas");
	ofstream out("glue.cpp");*/
	ifstream in("tex.pas");
	ofstream out("tex.cpp");
	string section = "";
	for (string line; getline(in, line);)
	{
//		string original = line;
		// commentaires
		auto pos = line.find("{");
		if (pos != string::npos)
		{
			auto pos2 = line.find("}");
			line = line.substr(0, pos);
			string line2;
			while (pos2 == string::npos)
			{
				getline(in, line2);
//				original += "\n"+line2;
				pos2 = line2.find("}");
			}
		}
		// points-virgules perdus
		if (line == ";")
			line = "";
		// end
		pos = line.find("end.");
		if (pos != string::npos)
			line.replace(pos, 4, "}");
		pos = line.find("end;");
		if (pos != string::npos)
			line.replace(pos, 4, "}");
		pos = line.find(" end");
		if (pos != string::npos)
			line.replace(pos, 4, " }");
		// begin
		if (line == "begin")
			line = "{";
		pos = line.find(" begin");
		if (pos != string::npos)
			line.replace(pos, 6, " {");
		// record
		pos = line.find(" = record");
		if (pos != string::npos)
			line.replace(pos, 9, " = struct {");
		pos = line.find(" = packed record");
		if (pos != string::npos)
			line.replace(pos, 16, " = struct {");
		// case
		pos = line.find(" case ");
		if (pos != string::npos)
		{
			line.replace(pos, 4, " case (");
			pos = line.find(" of");
			line.replace(pos, 3, ") {");
		}
		// SECTION
		if (line.find("procedure") != string::npos)
			section = "procedure";
		if (line.find("const") != string::npos)
			section = "const";
		if (line.find("var") != string::npos)
			section = "var";
		// FIN
		out << line // << string(200-line.size(), ' ') << "/*" << original << "*/" 
		<< endl;
	}
}
