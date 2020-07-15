#include "getstringsstarted.h"
#include "makestring.h"
#include "fichier.h"
#include <iostream>
#include "texte.h" 

constexpr int stringvacancies = 8000;
constexpr char poolname[] = "tex.pool";

//! Initializes the string pool,
//! but returns |false| if something goes wrong.
bool getstringsstarted(void)
{
	strings.resize(256);
	for (int k = 0; k < 256; k++)
	{
		if (k < ' ' || k > '~')
		{
			strings[k] = "^^";
			if (k < 64)
				strings[k] += char(k+64);
			else 
				if (k < 128)
					strings[k] += char(k-64);
				else
				{
					int l = k/16;
					strings[k] += char(l < 10 ? l+'0' : l+'a'-10);
					l = k%16;
					strings[k] += char(l < 10 ? l+'0' : l+'a'-10);
				}
		}
		else
			strings[k] = char(k);
	}
	nameoffile = poolname;
	if (!aopenin(poolfile))
	{
		std::cout << "! I can't read TEX.POOL." << std::endl;
		aclose(poolfile);
		return false;
	}
	bool c = false;
	do
	{
		if (poolfile.eof())
		{
			std::cout << "! TEX.POOL has no check sum.'" << std::endl;
			aclose(poolfile);
			return false;
		}
		//characters input from \a pool_file
		char m = poolfile.get();
		char n = poolfile.get();
		if (m == '*') // checksum
		{
			int a = 0; // accumulator for check sum
			int k = 1;
			while (true)
			{
				if (n < '0' || n> '9')
				{
					std::cout << "! TEX.POOL check sum doesn't have nine digits." << std::endl;
					aclose(poolfile);
					return false;
				}
				a = 10*a+n-'0';
				if (k == 9)
					break;
				k++;
				n = poolfile.get();
			}
			if (a != 117275187)
			{
				std::cout << "! TEX.POOL doesn't match; TANGLE me again." << std::endl;
				aclose(poolfile);
				return false;
			}
			c = true;
		}
		else
		{
			if (m < '0' || m > '9' || n < '0' || n > '9')
			{
				std::cout << "! TEX.POOL line doesn't begin with two digits." << std::endl;
				aclose(poolfile);
				return false;
			}
			std::string s;
			int l = (m-'0')*10+n-'0';
			for (int k = 1; k <= l; k++)
			{
				if (poolfile.peek() == '\n')
					m = ' ';
				else
					m = poolfile.get();
				s += m;
			}
			std::string dummy;
			getline(poolfile, dummy);
			strings.push_back(s);
		}
	} while (!c);
	aclose(poolfile);
	return true;
}

