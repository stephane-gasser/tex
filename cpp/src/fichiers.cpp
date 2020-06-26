#include "fichier.h"

//! Close a text file.
void aclose(alphafile& f)
{
  f.close();
}

//! Close a binary file.
void bclose(bytefile& f)
{
  f.close();
}

//! Close a word file.
void wclose(wordfile& f)
{
  f.close();
}

//! Open a text file for input.
bool aopenin(alphafile& f)
{
	f.open(nameoffile, std::ios_base::in);
	return f.is_open();
}

//! Open a text file for output.
bool aopenout(alphafile& f)
{
	f.open(nameoffile, std::ios_base::out);
	return f.is_open();
}

//! Open a binary file for input.
bool bopenin(bytefile& f)
{
	f.open(nameoffile, std::ios_base::in);
	return f.is_open();
}

//! Open a binary file for output.
bool bopenout(bytefile& f)
{
	f.open(nameoffile, std::ios_base::out);
	return f.is_open();
}

bool wopenin(wordfile& f)
{
	f.open(nameoffile, std::ios_base::in);
	return f.is_open();
}

bool wopenout(wordfile& f)
{
	f.open(nameoffile, std::ios_base::out);
	return f.is_open();
}
