/* testutils.h - utilities used when writing test suites for om.
 *
 * ----START-LICENCE----
 * Copyright 2000 Dialog Corporation
 * 
 * This program is free software; you can redistribute it and/or 
 * modify it under the terms of the GNU General Public License as 
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
 * USA
 * -----END-LICENCE-----
 */

#ifndef OM_HGUARD_TESTUTILS_H
#define OM_HGUARD_TESTUTILS_H

#include "testsuite.h"
#include <om/om.h>

// ######################################################################
// Useful display operators

inline ostream &
operator<<(ostream &os, const OmMSetItem &mitem)
{
    os << mitem.wt << " " << mitem.did;
    return os;
}

inline ostream &
operator<<(ostream &os, const OmMSet &mset)
{
    copy(mset.items.begin(), mset.items.end(),
	 ostream_iterator<OmMSetItem>(os, "\n"));
    return os;
}

inline ostream &
operator<<(ostream &os, const OmESetItem &item)
{
    cout << item.tname;
    return os;
}

inline ostream &
operator<<(ostream &os, const vector<unsigned int> &ints)
{
    copy(ints.begin(), ints.end(),
	 ostream_iterator<unsigned int>(os, ", "));
    return os;
}


// ######################################################################
// Useful comparison operators

inline bool
mset_range_is_same(const OmMSet &mset1, unsigned int first1,
		   const OmMSet &mset2, unsigned int first2,
		   unsigned int count)
{
    TEST_AND_EXPLAIN(mset1.items.size() >= first1 + count - 1,
		     "mset1 is too small: expected at least " <<
		     (first1 + count - 1) << " items." << endl);

    TEST_AND_EXPLAIN(mset2.items.size() >= first2 + count - 1,
		     "mset2 is too small: expected at least " <<
		     (first2 + count - 1) << " items." << endl);

    for (unsigned int i=0; i<count; ++i) {
	if ((mset1.items[first1+i].wt != mset2.items[first2+i].wt) ||
	    (mset1.items[first1+i].did != mset2.items[first2+i].did)) {
	    return false;
	}
    }
    return true;
}

inline bool
mset_range_is_same_weights(const OmMSet &mset1, unsigned int first1,
			   const OmMSet &mset2, unsigned int first2,
			   unsigned int count)
{   
    TEST_AND_EXPLAIN(mset1.items.size() >= first1 + count - 1,
		     "mset1 is too small: expected at least " <<
		     (first1 + count - 1) << " items." << endl);

    TEST_AND_EXPLAIN(mset2.items.size() >= first2 + count - 1,
		     "mset2 is too small: expected at least " <<
		     (first2 + count - 1) << " items." << endl);


    for (unsigned int i=0; i<count; ++i) {
	if (mset1.items[first1+i].wt != mset2.items[first2+i].wt) {
	    return false;
	}
    }
    return true;
}

bool operator==(const OmMSet &first, const OmMSet &second)
{   
    if ((first.mbound != second.mbound) ||
	(first.max_possible != second.max_possible) ||
	(first.items.size() != second.items.size())) {
	return false;
    }
    if(first.items.size() == 0) return true;
    return mset_range_is_same(first, 0, second, 0, first.items.size());
}


// ######################################################################
// Useful test macros

/// Check size of mset is as expected
#define TEST_MSET_SIZE(a, b) TEST_AND_EXPLAIN(((a).items.size() == (b)), \
	"MSet `"STRINGIZE(a)"' is not of expected size: was `" << \
	(a).items.size() << "' expected `" << (b) << "': " << endl << \
	"Full mset was: " << endl << (a) << endl)

#endif  // OM_HGUARD_TESTUTILS_H
