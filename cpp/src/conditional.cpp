#include "conditional.h"
#include "noeud.h"
#include "lecture.h"
#include "impression.h"
#include "lecture.h"
#include "getnext.h"
#include "erreur.h"
#include "equivalent.h"
#include "fichier.h"
#include "etat.h"

[[nodiscard]] static Token get_x_token_or_active_char(char status)
{ 
	auto t = scanner.getX(status); 
	if (t.cmd == relax && t.chr == no_expand_flag)
		return Token(active_char, t.tok-cs_token_flag-active_base);
	return t;
}

static void changeiflimit(smallnumber l, ConditionalNode *p)
{
	if (p == condptr) 
		iflimit = l;
	else
	{
		auto q = condptr;
		while (true)
		{
			if (q == nullptr)
				confusion("if");
			if (q->link == p)
			{
				q->type = l;
				return;
			}
			next(q);
		}
	}
}

void conditional(char status, Token t)
{
	auto p = new ConditionalNode(curif);
	p->link = condptr; 
	p->if_line_field = ifline;
	condptr = p;
	curif = t.chr;
	iflimit = 1;
	ifline = line;
	auto savecondptr = condptr;
	smallnumber thisif = t.chr;
	halfword q;
	int r;
	bool b;
	switch (thisif)
	{
		case if_char_code:
		{
			t = get_x_token_or_active_char(status);
			int n = t.cmd > active_char || t.chr > 255 ? 256 : t.chr;
			t = get_x_token_or_active_char(status);
			if (t.cmd > active_char || t.chr > 255)
			{
				t.cmd = relax;
				t.chr = 256;
			}
			b = n == t.chr;
			break;
		}
		case if_cat_code:
		{
			t = get_x_token_or_active_char(status);
			int m = t.cmd > active_char || t.chr > 255 ? relax : t.cmd;
			t = get_x_token_or_active_char(status);
			if (t.cmd > active_char || t.chr > 255)
			{
				t.cmd = relax;
				t.chr = 256;
			}
			b = m == t.cmd;
			break;
		}
		case if_int_code:
		{
			int n = scanner.getInt(status);
			t = scanner.getXSkipSpace(status);
			if (t.tok >= other_token+'<' && t.tok <= other_token+'>')
				r = t.tok-other_token;
			else
			{
				backerror(t, "Missing = inserted for "+Token(if_test, if_int_code).cmdchr(), "I was expecting to see `<', `=', or `>'. Didn't.");
				r = '=';
			}
			switch (r)
			{
				case '<': 
					b = n < scanner.getInt(status);
					break;
				case '=': 
					b = n == scanner.getInt(status);
					break;
				case '>': 
					b = n > scanner.getInt(status);
			}
			break;
		}
		case if_dim_code:
		{
			int n = scanner.getNormalDimen(status);
			t = scanner.getXSkipSpace(status);
			if (t.tok >= other_token+'<' && t.tok <= other_token+'>')
				r = t.tok-other_token;
			else
			{
				backerror(t, "Missing = inserted for "+Token(if_test, if_dim_code).cmdchr(), "I was expecting to see `<', `=', or `>'. Didn't.");
				r = '=';
			}
			switch (r)
			{
				case '<': 
					b = n < scanner.getNormalDimen(status);
					break;
				case '=': 
					b = n == scanner.getNormalDimen(status);
					break;
				case '>': 
					b = n > scanner.getNormalDimen(status);
			}
			break;
		}
		case if_odd_code:
			b = scanner.getInt(status)%2;
			break;
		case if_vmode_code: 
			b = abs(mode) == vmode;
			break;
		case if_hmode_code: 
			b = abs(mode) == hmode;
			break;
		case if_mmode_code: 
			b = abs(mode) == mmode;
			break;
		case if_inner_code: 
			b = mode < 0;
			break;
		case if_void_code:
			b = box(scanner.getUInt8(status)) == nullptr;
			break;
		case if_hbox_code:
		{
			auto p = box(scanner.getUInt8(status));
			if (p == nullptr)
				b = false;
			else 
				b = p->type == hlist_node;
			break;
		}
		case if_vbox_code:
		{
			auto p = box(scanner.getUInt8(status));
			if (p == nullptr)
				b = false;
			else 
				b = p->type == vlist_node;
			break;
		}
		case ifx_code:
		{
			//Test if two tokens match
			t = scanner.next(normal);
			int n = t.cs;
			auto t2 = scanner.next(normal);
			if (t2.cmd != t.cmd)
				b = false;
			else 
				if (t2.cmd < call)
					b = t2.chr == t.chr;
				else
				{
					auto p = dynamic_cast<TokenList*>(t2.chr < hash_base ? eqtb_active[t2.chr-active_base].index : eqtb_cs[t2.chr-hash_base].index);
					auto q = dynamic_cast<TokenList*>(t.chr < hash_base ? eqtb_active[t.chr-active_base].index : eqtb_cs[t.chr-hash_base].index);
					if (p->list == q->list)
						b = true;
					/*else
					{
						while (p && q)
							if (p->token != q->token)
								p = nullptr;
							else
							{
								next(p);
								next(q);
							}
						b = p == nullptr && q == nullptr;
					}*/
				}
			break;
		}
		case if_eof_code:
			b = readopen[scanner.getUInt4(status)] == closed;
			break;
		case if_true_code: 
			b = true;
			break;
		case if_false_code: 
			b = false;
			break;
		case if_case_code:
		{
			int n = scanner.getInt(status);
			if (tracing_commands() > 1)
				diagnostic("{case "+std::to_string(n)+"}");
			while (n)
			{
				passtext();
				if (condptr == savecondptr)
					if (t.chr == or_code)
						n--;
					else
					{
						if (t.chr == fi_code)
						{
							ifline = condptr->if_line_field;
							curif = condptr->subtype;
							iflimit = condptr->type;
							removeNodeAtStart(condptr);
						}
						else
							iflimit = fi_code;
						return;
					}
				else 
					if (t.chr == fi_code)
					{
						ifline = condptr->if_line_field;
						curif = condptr->subtype;
						iflimit = condptr->type;
						removeNodeAtStart(condptr);
					}
			}
			changeiflimit(or_code, savecondptr);
			return;
		}
	}
	if (tracing_commands() > 1)
		diagnostic(b ? "{true}" : "{false}");
	if (b)
	{
		changeiflimit(else_code, savecondptr);
		return;
	}
	while (true)
	{
		passtext();
		if (condptr == savecondptr)
		{
			if (t.chr != or_code)
			{
				if (t.chr == fi_code)
				{
					ifline = condptr->if_line_field;
					curif = condptr->subtype;
					iflimit = condptr->type;
					removeNodeAtStart(condptr);
				}
				else
					iflimit = fi_code;
				return;
			}
			error("Extra "+esc("or"), "I'm ignoring this; it doesn't match any \\if.");
		}
		else 
			if (t.chr == 2)
			{
				ifline = condptr->if_line_field;
				curif = condptr->subtype;
				iflimit = condptr->type;
				removeNodeAtStart(condptr);
			}
	}
}


void passtext(void)
{
	int l = 0;
	skipline = line;
	while (true)
	{
		auto t = scanner.next(skipping);
		if (t.cmd == fi_or_else)
		{
			if (l == 0)
				break;
			if (t.chr == fi_code)
				l--;
		}
		else 
			if (t.cmd == if_test)
				l++;
	}
}
