#include "chaine.h"
#include "equivalent.h"
#include "erreur.h"
#include "fichier.h"
#include <iostream>
#include <map>

int cur_length(void) { return currentString.size(); }
void append_char(ASCIIcode c) { currentString += c; } //!< put \a ASCII_code # at the end of \a str_pool
static bool hash_is_full(void) { return hashused == hash_base; } //! test if all positions are occupied


halfword idlookup(const std::string &s, bool nonewcontrolsequence)
{
	static std::map<std::string, halfword> numero;
	if (numero.find(s) != numero.end())
		return numero[s];
	if (nonewcontrolsequence)
		return undefined_control_sequence;
	if (hash_is_full())
		overflow("hash size", hash_size);
	numero[s] = --hashused;
	strings.push_back(s);
	eqtb_cs[hashused-hash_base].text = s;
	return hashused;
}

constexpr int stringvacancies = 8000;
constexpr char poolname[] = "tex.pool";

//! Initializes the string pool,
//! but returns |false| if something goes wrong.
bool getstringsstarted(void)
{
	for (int k = 0; k < ' '; k++)
		strings.push_back("^^"+char(k+64));
	for (int k = ' '; k <= '~'; k++)
		strings.push_back(std::string(1 ,char(k)));
	strings.push_back("^^"+char(127-64));
	for (int k = 128; k < 256; k++)
	{
		int l = k/16, m = k%16;
		strings.push_back("^^"+char(l < 10 ? l+'0' : l+'a'-10)+char(m < 10 ? m+'0' : m+'a'-10));
	}
	static alphafile poolfile;
	if (!aopenin(poolfile, poolname))
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

