// PythonImageConsumer.cpp
// author: Johannes Wagner <wagner@hcm-lab.de>
// created: 2016/03/02
// Copyright (C) University of Augsburg, Lab for Human Centered Multimedia
//
// *************************************************************************************************
//
// This file is part of Social Signal Interpretation (SSI) developed at the 
// Lab for Human Centered Multimedia of the University of Augsburg
//
// This library is free software; you can redistribute itand/or
// modify it under the terms of the GNU General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or any laterversion.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FORA PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public
// License along withthis library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
//*************************************************************************************************

#include "PythonImageConsumer.h"
#include "PythonHelper.h"

#ifdef USE_SSI_LEAK_DETECTOR
#include "SSI_LeakWatcher.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

namespace ssi {

ssi_char_t *PythonImageConsumer::ssi_log_name = "pyimfilter";

PythonImageConsumer::PythonImageConsumer(const ssi_char_t *file)
	: PythonConsumer(file),
	_has_meta_data(false)
{
}

PythonImageConsumer::~PythonImageConsumer() {
}

void PythonImageConsumer::setMetaData(ssi_size_t size, const void *meta) {

	if (sizeof(_format_in) != size) 
	{
		ssi_err("meta data does not describe image format");
	}

	if (!_helper)
	{
		initHelper();
	}
	
	memcpy(&_format_in, meta, size);
	_has_meta_data = true;

	ssi_msg(SSI_LOG_LEVEL_BASIC, "format of input image '%dx%dx%dx%d'", _format_in.widthInPixels, _format_in.heightInPixels, _format_in.numOfChannels, _format_in.depthInBitsPerChannel / 8)

	_helper->setImageFormatIn(_format_in);
};

}

