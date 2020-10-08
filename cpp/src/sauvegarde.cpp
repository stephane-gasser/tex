#include "sauvegarde.h"
#include "erreur.h"
#include "etat.h"
#include "equivalent.h"

enum save_type
{ 
	restore_old_value = 0, //!< \a save_type when a value should be restored later
	restore_zero = 1, //!< \a save_type when an undefined entry should be restored
	insert_token = 2, //!< \a save_type when a token is being saved for later use
	level_boundary = 3 //!< \a save_type corresponding to beginning of group
};

void MemoryNode::eqsave(quarterword l)
{
	if (l == level_zero)
		savestack.push_back(new MemoryNode(restore_zero, level_zero, this));
	else
	{
		savestack.push_back(this);
		savestack.push_back(new MemoryNode(restore_old_value, l, this));
	}
}

void saveforafter(halfword token)
{
	if (curlevel > level_one)
		savestack.push_back(new MemoryNode(insert_token, level_zero, token));
}

static AnyNode *curboundary = nullptr; // 0..savesize

void newsavelevel(groupcode c)
{
	if (curlevel == 255)
		overflow("grouping levels", 255);
	savestack.push_back(new MemoryNode(level_boundary, curgroup, curboundary));
	curboundary = savestack.back();
	curlevel++;
	curgroup = c;
}

void unsave(void)
{
	if (curlevel <= level_one)
	{
		confusion("curlevel");
		return;
	}
	curlevel--;
	while (true)
	{
		auto m = savestack.back();
		savestack.pop_back();
		switch (m->type)
		{
			case level_boundary:
				curgroup = m->level;
				curboundary = m->index;
				return;
			case insert_token:
				backinput(m->int_);
				break;
			case restore_old_value:
			{
				auto slevel = m->level;
				auto sindex = dynamic_cast<MemoryNode*>(m->index);
				m = savestack.back();
				savestack.pop_back();
				if (sindex->level != level_one)
				{
					sindex->type = m->type;
					sindex->level = m->level;
					sindex->index = m->index;
					sindex->int_ = m->int_;
				}
				if (sindex->index)
					sindex->eqdestroy();
				else 
					if (sindex->level != level_one) //dans xeqlevel
						sindex->level = slevel;//xeqlevel[p] = l;
				break;
			}
			case restore_zero:
			{
				auto sindex = dynamic_cast<MemoryNode*>(m->index);
				if (sindex->level != level_one)
				{
					sindex->type = undefined_cs;
					sindex->level = level_zero;
					sindex->index = nullptr;
					sindex->int_ = 0;
				}
			}
		}
	}	
}
