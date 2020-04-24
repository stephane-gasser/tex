#include "getstringsstarted.h"
#include "makestring.h"
#include "aopenin.h"
#include "aclose.h"
#include <iostream> 

bool getstringsstarted(void)
{
	poolptr = 0;
	strptr = 0;
	strstart[0] = 0;
	for (int k = 0; k < 256; k++)
	{
		if (k < 32 || k > 126)
		{
			strpool[poolptr++] = '^';
			strpool[poolptr++] = '^';
			if (k < 64)
				strpool[poolptr++] = k+64;
			else 
				if (k < 128)
					strpool[poolptr++] = k-64;
				else
				{
					int l = k/16;
					strpool[poolptr++] = l < 10 ? l+'0' : l+'a'-10;
					l = k%16;
					strpool[poolptr++] = l < 10 ? l+'0' : l+'a'-10;
				}
		}
		else
			strpool[poolptr++] = k;
		g = makestring();
	}
	nameoffile = poolname;
	if (aopenin(poolfile))
	{
		c = false;
		do
		{
			if (poolfile.eof())
			{
				std::cout << "! TEX.POOL has no check sum.'" << std::endl;
				aclose(poolfile);
				return false;
			}
			char m = poolfile.get();
			char n = poolfile.get();
			if (m == '*') // checksum
			{
				int a = 0;
				int k = 1;
				while (true)
				{
					if (xord[n] < '0' || xord[n] > '9')
					{
						std::cout << "! TEX.POOL check sum doesn''t have nine digits." << std::endl;
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
					std::cout << "! TEX.POOL doesn''t match; TANGLE me again." << std::endl;
					aclose(poolfile);
					return false;
				}
				c = true;
			}
			else
			{
				if (xord[m] < '0' || xord[m] > '9' || xord[n] < '0' || xord[n] > '9')
				{
					std::cout << "! TEX.POOL line doesn''t begin with two digits." << std::endl;
					aclose(poolfile);
					return false;
				}
				int l = (xord[m]-'0')*10+xord[n]-'0';
				if (poolptr+l+stringvacancies > poolsize)
				{
					std::cout << "! You have to increase POOLSIZE." << std::endl;
					aclose(poolfile);
					return false;
				}
				for (int k = 1; k <= l; k++)
				{
					if (poolfile.peek() != '\n')
						m = ' ';
					else
						m = poolfile.get();
					strpool[poolptr++] = xord[m];
				}
				std::string dummy;
				getline(poolfile, dummy);
				g = makestring();
			}
		} while (!c);
		aclose(poolfile);
		return true;
	}
	else
	{
		std::cout << "! I can''t read TEX.POOL." << std::endl;
		aclose(poolfile);
		return false;
	}
}

