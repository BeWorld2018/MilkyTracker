/*
 *  ppui/sdl/DisplayDeviceFB_SDL.h
 *
 *  Copyright 2009 Peter Barth
 *
 *  This file is part of Milkytracker.
 *
 *  Milkytracker is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Milkytracker is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Milkytracker.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  12/5/14 - Dale Whinham
 *    - Port to SDL2
 *
 */

/////////////////////////////////////////////////////////////////
//
//	Our display device
//
/////////////////////////////////////////////////////////////////
#ifndef __DISPLAYDEVICEFB_H__
#define __DISPLAYDEVICEFB_H__

#include "DisplayDevice_SDL.h"

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 2
#endif

#if defined(AMIGA_SAGA_PIP)
struct Screen;

#define SAGA_PAGES 3
#endif

class PPDisplayDeviceFB : public PPDisplayDevice
{
private:
	bool needsTemporaryBuffer;
	pp_uint8* temporaryBuffer;
	pp_uint32 temporaryBufferPitch, temporaryBufferBPP;
	pp_int32 bpp;
	SDL_Color palette[256];

#if defined(AMIGA_SAGA_PIP)
	struct Screen * 	pubScreen;
	void * 				unalignedSAGABuffers[3];
	void * 				alignedSAGABuffers[3];
	pp_uint32 			currentSAGAPage;
#endif

	// used for rotating coordinates etc.
	void postProcess(const PPRect& r);

public:
	PPDisplayDeviceFB(
#if !SDL_VERSION_ATLEAST(2, 0, 0)
					  SDL_Surface*& screen,
#endif
					  pp_int32 width,
					  pp_int32 height,
					  pp_int32 scaleFactor,
					  pp_int32 bpp,
					  bool fullScreen,
					  Orientations theOrientation = ORIENTATION_NORMAL,
					  bool swapRedBlue = false);

	virtual ~PPDisplayDeviceFB();

	virtual bool supportsScaling() const { return true; }
#if SDL_VERSION_ATLEAST(2, 0, 0)
	virtual void setSize(const PPSize& size);
#endif
	virtual void setPalette(PPColor * palette);
#if defined(AMIGA_SAGA_PIP)
	virtual void setSAGAPiPSize();
#endif

	virtual PPGraphicsAbstract* open();
	virtual void close();

	void update();
	void update(const PPRect& r);
#if SDL_VERSION_ATLEAST(2, 0, 0)
protected:
	SDL_Surface* theSurface;
	SDL_Texture* theTexture;
	SDL_Renderer* theRenderer;
#endif
};

#endif
