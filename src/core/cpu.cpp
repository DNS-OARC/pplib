/*******************************************************************************
 * This file is part of "Patrick's Programming Library", Version 7 (PPL7).
 * Web: http://www.pfp.de/ppl/
 *
 * $Author$
 * $Revision$
 * $Date$
 * $Id$
 *
 *******************************************************************************
 * Copyright (c) 2013, Patrick Fedick <patrick@pfp.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *    1. Redistributions of source code must retain the above copyright notice, this
 *       list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright notice,
 *       this list of conditions and the following disclaimer in the documentation
 *       and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDER AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************/



#include "prolog.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _WIN32
#include <strings.h>
#include <ctype.h>
#endif

#include "ppl7.h"

#ifdef HAVE_X86_ASSEMBLER
extern "C" {
	ppluint32 PPL7_GetASMBits();
	ppluint32 PPL7_GetCpuCaps();
}
#else
static ppluint32 PPL7_GetCpuCaps()
{
	return 0;
}

static ppluint32 PPL7_GetASMBits()
{
	return sizeof(void*);
}
#endif

namespace ppl7 {


static ppluint32 myCPUCaps=0;
static ppluint32 myBits=0;



String binaryString(ppluint64 value)
{
	String ret;
	for (int i=63;i>=0;i--) {
		if (value&((ppluint64)1<<i)) ret+="1";
		else ret+="0";
	}
	return ret;
}


ppluint32 GetCPUCaps (CPUCaps &cpu)
{
	if (myBits==0) {
		myCPUCaps=PPL7_GetCpuCaps();
		myBits=PPL7_GetASMBits();
	}
	cpu.caps=myCPUCaps;
	cpu.bits=myBits;
	return myCPUCaps;
}

ppluint32 GetCPUCaps ()
{
	if (myBits==0) {
		myCPUCaps=PPL7_GetCpuCaps();
		myBits=PPL7_GetASMBits();
	}
	return myCPUCaps;
}

} // end of namespace ppl

