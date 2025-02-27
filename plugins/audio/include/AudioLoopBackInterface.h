// AudioLoopBackInterface.h
// author: Johannes Wagner <wagner@hcm-lab.de>
// created: 15/6/2018
// Copyright (C) University of Augsburg, Lab for Human Centered Multimedia
//
// *************************************************************************************************
//
// This file is part of Social Signal Interpretation (SSI) developed at the 
// Lab for Human Centered Multimedia of the University of Augsburg
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
//*************************************************************************************************

#pragma once

#ifndef SSI_AUDIO_AUDIOLOOPBACKINTERFACE_H
#define SSI_AUDIO_AUDIOLOOPBACKINTERFACE_H

typedef unsigned char BYTE;

namespace ssi
{
	class AudioLoopBackInterface
	{
	public:
		virtual ~AudioLoopBackInterface() {}
		virtual int CopyData(const BYTE* Data, const int NumFramesAvailable) = 0;
	};
}

#endif