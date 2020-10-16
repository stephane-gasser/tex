#ifndef GETNEXT_H
#define GETNEXT_H

#include "globals.h"
#include "token.h"

enum scanner_status
{
	skipping = 1, //!< \a scanner_status when passing conditional text
	defining = 2, //!< \a scanner_status when reading a macro definition
	matching = 3, //!< \a scanner_status when reading macro arguments
	aligning = 4, //!< \a scanner_status when reading an alignment preamble
	absorbing = 5 //!< \a scanner_status when reading a balanced text
};

class GlueSpec;

class Scanner
{
	public:
		int val;
		int lev;
		GlueSpec *gl;
		TokenList *tk;
		void somethingInternal(char, smallnumber, bool, Token);
		Token next(char, bool = true);
		Token get(char status) { return next(status, false); }
		Token getSkipSpace(char status)
		{
			Token t;
			do
				t = get(status);
			while (t.tok == space_token);
			return t;
		}
		Token getX(char);
		Token getXSkipSpace(char status)
		{
			Token t;
			do
				t = getX(status);
			while (t.cmd == spacer);
			return t;
		}

		Token getXSkipSpaceAndEscape(char status)
		{
			Token t;
			do
				t = getX(status);
			while (t.cmd == spacer || t.cmd == escape);
			return t;
		}
		int getInt(char);
		int getUChar(char);
		int getUInt4(char);
		int getUInt8(char);
		int getUInt15(char);
		int getUInt27(char);
		void leftBrace(char);
		Token getBoxSpec(char, groupcode);
		Token getBoxSpec(char, groupcode, int);
		int getDimen(char, bool, bool, bool = false);
		int getNormalDimen(char status) { return getDimen(status, false, false); }
		bool isKeyword(char, const std::string &);
		void optionalEquals(char);
};


void passtext(void);

inline Scanner scanner;
inline halfword warningindex = 0;
inline bool forceeof = false;
inline int skipline;

#endif
