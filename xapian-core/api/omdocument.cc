/* omdocument.cc: class for performing a match
 *
 * ----START-LICENCE----
 * Copyright 1999,2000 BrightStation PLC
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

#include <om/omdocument.h>
#include "om/omtypes.h"
#include "refcnt.h"
#include "document.h"
#include "omdocumentinternal.h"

//////////////////////////////////
// implementation of OmDocument //
//////////////////////////////////

OmDocument::OmDocument(OmDocument::Internal *internal_) : internal(internal_)
{
}

OmKey
OmDocument::get_key(om_keyno key) const
{
    // create our own RefCntPtr in case another thread assigns new internals
    RefCntPtr<LeafDocument> myptr = internal->ptr;
    return myptr->get_key(key);
}

OmData
OmDocument::get_data() const
{
    // create our own RefCntPtr in case another thread assigns new internals
    RefCntPtr<LeafDocument> myptr = internal->ptr;
    return myptr->get_data();
}

void
OmDocument::operator=(const OmDocument &other)
{
    // pointers are reference counted.
    internal->ptr = other.internal->ptr;
}

OmDocument::OmDocument(const OmDocument &other)
	: internal(0)
{
    internal = new Internal(*other.internal);
}

OmDocument::~OmDocument()
{
    delete internal;
}

std::string
OmDocument::get_description() const
{
    // FIXME - return document contents
    return "OmDocument()";
}
