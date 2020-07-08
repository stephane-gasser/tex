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
	/*poolptr = 0;
	strptr = 0;
	strstart[0] = 0;*/
	for (int k = 0; k < 256; k++)
	{
		if (k < ' ' || k > '~')
		{
			append_char('^');
			append_char('^');
			if (k < 64)
				append_char(k+64);
			else 
				if (k < 128)
					append_char(k-64);
				else
				{
					int l = k/16;
					append_char(l < 10 ? l+'0' : l+'a'-10);
					l = k%16;
					append_char(l < 10 ? l+'0' : l+'a'-10);
				}
		}
		else
			append_char(k);
		makestring();
	}
	nameoffile = poolname;
	if (!aopenin(poolfile))
	{
		std::cout << "! I can't read TEX.POOL." << std::endl;
		aclose(poolfile);
		return false;
	}
	c = false;
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
				if (xord[n] < '0' || xord[n] > '9')
				{
					std::cout << "! TEX.POOL check sum doesn't have nine digits." << std::endl;
					aclose(poolfile);
					return false;
				}
				a = 10*a+xord[n]-'0';
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
			if (xord[m] < '0' || xord[m] > '9' || xord[n] < '0' || xord[n] > '9')
			{
				std::cout << "! TEX.POOL line doesn't begin with two digits." << std::endl;
				aclose(poolfile);
				return false;
			}
			int l = (xord[m]-'0')*10+xord[n]-'0';
			/*if (poolptr+l+stringvacancies > poolsize)
			{
				std::cout << "! You have to increase POOLSIZE." << std::endl;
				aclose(poolfile);
				return false;
			}*/
			for (int k = 1; k <= l; k++)
			{
				if (poolfile.peek() == '\n')
					m = ' ';
				else
					m = poolfile.get();
				append_char(xord[m]);
			}
			std::string dummy;
			getline(poolfile, dummy);
			makestring();
		}
	} while (!c);
	aclose(poolfile);
	return true;
}

