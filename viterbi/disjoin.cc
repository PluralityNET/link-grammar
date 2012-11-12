/*************************************************************************/
/* Copyright (c) 2012 Linas Vepstas <linasvepstas@gmail.com>             */
/* All rights reserved                                                   */
/*                                                                       */
/* Use of the Viterbi parsing system is subject to the terms of the      */
/* license set forth in the LICENSE file included with this software.    */
/* This license allows free redistribution and use in source and binary  */
/* forms, with or without modification, subject to certain conditions.   */
/*                                                                       */
/*************************************************************************/

#include "compile.h"

namespace link_grammar {
namespace viterbi {

/**
 * Convert dictionary-normal form into disjunctive normal form.
 * That is, convert the mixed-form dictionary entries into a disjunction
 * of a list of conjoined connectors.  The goal of this conversion is to
 * simplify the parsing algorithm.
 */

Atom* disjoin(Atom* mixed_form)
{
	AtomType intype = mixed_form->get_type();
	if ((OR != intype) && (AND != intype))
		return mixed_form;

	const Link* junct = dynamic_cast<Link*>(mixed_form);
	if (OR == intype)
	{
		const OutList& oset = junct->get_outgoing_set();
		size_t sz = junct->get_arity();
		OutList new_oset;
		for(int i=0; i<sz; i++)
		{
			Atom* norm = disjoin(oset[i]);
			new_oset.push_back(norm);
		}
		// Link* new_or = Or(new_oset);
	}

	return NULL;
}


} // namespace viterbi
} // namespace link-grammar

