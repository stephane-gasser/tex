#ifndef ETAT_H
#define ETAT_H

#include "globals.h"
#include "token.h"
#include "noeud.h"

class liststaterecord
{
	public:
		int modefield; // -203..203
		LinkedNode *headfield, *tailfield;
		int pgfield, mlfield;
		memoryword auxfield;
};

inline std::vector<liststaterecord> nest(1);
inline liststaterecord curlist;
	inline auto &aux = curlist.auxfield; //!< auxiliary data about the current list
		inline int& prev_depth = aux.int_; //!< the name of \a aux in vertical mode
		inline halfword& space_factor = aux.hh.lh; //!< part of \a aux in horizontal mode
		inline halfword& clang = aux.hh.rh;  //!< the other part of \a aux in horizontal mode
	inline auto &head = curlist.headfield; //!< header node of current list
	inline auto &tail = curlist.tailfield; //!< final node on current list
	inline int& mode = curlist.modefield; //!< current mode
	inline int& prev_graf = curlist.pgfield; //!< number of paragraph lines accumulated
	inline int& mode_line = curlist.mlfield; //!< source file line number at beginning of list

class instaterecord
{
	public:
		quarterword statefield, indexfield;
		halfword startfield;
		halfword locfield, limitfield;
		std::string namefield;
};

inline std::vector<instaterecord> inputstack(1);
inline instaterecord curinput;
	inline auto &start = curinput.startfield; //!< starting position in \a buffer
	inline auto &limit = curinput.limitfield; //!< end of current line in \a buffer
	inline auto &param_start = limit; //!< base of macro parameters in \a param_stack
	inline auto &loc = curinput.locfield; //!< location of first unread character in \a buffer
	inline auto &state = curinput.statefield; //!< current scanner state
	inline auto &index = curinput.indexfield; //!< reference for buffer information
	inline auto &token_type = index; //!< type of current token list
	inline auto &name = curinput.namefield; //!< name of the current file

void popnest(void);
void pushnest(void);
void pop_input(void);
void push_input(void);
void backinput(Token);
void startinput(void);

inline void tail_append(LinkedNode*q) { appendAtEnd(tail, q); }

#endif
