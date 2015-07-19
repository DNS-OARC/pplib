/*******************************************************************************
 * This file is part of "Patrick's Programming Library", Version 6 (PPL6).
 * Web: http://www.pfp.de/ppl/
 *
 * $Author$
 * $Revision$
 * $Date$
 * $Id$
 *
 *******************************************************************************
 * Copyright (c) 2010, Patrick Fedick <patrick@pfp.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the copyright holder nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
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
#ifdef HAVE_STDIO_H
#include <stdio.h>
#endif
#ifdef HAVE_STDLIB_H
#include <stdlib.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#endif
#ifdef HAVE_MATH_H
#include <math.h>
#endif

#include "ppl6-grafix.h"
#include "ppl6-tk.h"

using namespace ppl6;
using namespace ppl6::grafix;
using namespace ppl6::tk;

namespace ppl6 {
namespace grafix {

GFXEngineSoftware::GFXEngineSoftware()
{

}

GFXEngineSoftware::~GFXEngineSoftware()
{

}

bool GFXEngineSoftware::isInit() const
{
	return true;
}

CString GFXEngineSoftware::name() const
{
	return "Software";
}

bool GFXEngineSoftware::createSurface(CSurface &surface)
{
	if (surface.gfxEngine()!=NULL || surface.enginePrivate()!=NULL) {
		SetError(1061);
		return false;
	}
	printf ("Surface wird in Software erstellt\n");

	CImage *draw=new CImage(surface.width(),surface.height(),surface.rgbFormat());
	surface.setEnginePrivate(draw);
	surface.setGfxEngine(this);
	return true;
}

bool GFXEngineSoftware::destroySurface(CSurface &surface)
{
	if (surface.gfxEngine()!=this) {
		SetError(1073);
		return false;
	}
	CImage *draw=(CImage*)surface.enginePrivate();
	if (!draw) {
		SetError(1074);
		return false;
	}
	delete draw;
	surface.setEnginePrivate(NULL);
	surface.setGfxEngine(NULL);
	return true;
}

bool GFXEngineSoftware::lockSurface(CSurface &surface, CDrawable &draw)
{
	if (surface.gfxEngine()!=this) {
		SetError(1073);
		return false;
	}
	CImage *img=(CImage*)surface.enginePrivate();
	if (!img) {
		SetError(1074);
		return false;
	}
	draw=img->getDrawable();
	return true;
}

bool GFXEngineSoftware::unlockSurface(CSurface &surface)
{
	if (surface.gfxEngine()!=this) {
		SetError(1073);
		return false;
	}
	CImage *img=(CImage*)surface.enginePrivate();
	if (!img) {
		SetError(1074);
		return false;
	}
	return true;
}


} // EOF namespace grafix
} // EOF namespace ppl6
