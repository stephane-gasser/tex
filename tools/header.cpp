#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;


int main()
{
	for(auto& p: fs::directory_iterator("../split"))
	{
		auto path = p.path();
		cout << path.native() << endl;
		ifstream in(path);
		string head;
		getline(in, head);
		cout << head << endl;
		if (head.find("procedure") == 0)
		{
			head.replace(0, 9, "void");
			head = head.substr(0, head.size()-1);
		}
		else if (head.find("function") == 0)
		{
			auto pos = head.find_last_of(":");
			auto type = head.substr(pos+2);
			head = head.substr(0, pos);
			type = type.substr(0, type.size()-1);
			if (type == "boolean")
				type = "bool";
			if (type == "integer")
				type = "int";
			head.replace(0, 8, type);
		}
		if (head.find("(") == string::npos)
			head += "(void)";
		else
		{
			auto parenth = head.substr(head.find("("));
			head = head.substr(0, head.find("(")+1);
			parenth = parenth.substr(1, parenth.size()-2);
			istringstream iss(parenth);
			for (string param; getline(iss, param, ';');)
			{
				auto pos = param.find(":");
				auto vars = param.substr(0, pos);
				if (vars[0] == ' ')
					vars = vars.substr(1);
				auto type = param.substr(pos+2);
				if (type == "boolean")
					type = "bool";
				if (type == "integer")
					type = "int";
				if (vars.substr(0, 4) == "var ")
				{
					vars = vars.substr(4);
					type += "&";
				}
				istringstream iss2(vars);
				for (string var; getline(iss2, var, ',');)
					head += type+" "+var+", ";
			}
			head = head.substr(0, head.size()-2);
			head += ")";
		}
		cout << head << endl << endl;
/*		ofstream out("../cpp/"+path.stem().native()+".h");
		out << "#include \"globals.h\"" << endl;
		out << head << ";" << endl;*/
		ofstream out("../cpp/"+path.stem().native()+".cpp");
		out << "#include \""<< path.stem().native() << ".h\"" << endl;
		out << head << endl;
		
		for (string line; getline(in, line);)
			out << line << endl;
	}
}
