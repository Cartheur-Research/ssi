// OsOSIntensity.h
// author: Andrew Sadek <andrew.sadek.se@gmail.com>
// created: 2012/04/27 
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

// based on code of openSMILE 1.0.1
// http://opensmile.sourceforge.net/

/*F******************************************************************************
 *
 * openSMILE - open Speech and Music Interpretation by Large-space Extraction
 *       the open-source Munich Audio Feature Extraction Toolkit
 * Copyright (C) 2008-2009  Florian Eyben, Martin Woellmer, Bjoern Schuller
 *
 *
 * Institute for Human-Machine Communication
 * Technische Universitaet Muenchen (TUM)
 * D-80333 Munich, Germany
 *
 *
 * If you use openSMILE or any code from openSMILE in your research work,
 * you are kindly asked to acknowledge the use of openSMILE in your publications.
 * See the file CITING.txt for details.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 ******************************************************************************E*/

/**

Provides Wave form OSIntensity.

*/

#pragma once

#ifndef SSI_OPENSMILE_OSIntensity_H
#define SSI_OPENSMILE_OSIntensity_H

#include "base/IFeature.h"
#include "OSTools.h"
#include "ioput/option/OptionList.h"
#include <iostream>
#include <fstream>
using namespace std;

namespace ssi {

	class OSIntensity : public IFeature {


public:

	class Options : public OptionList {

	public: 
			
		Options():
			intensity(1),loudness(0) {

			addOption ("intensity",&intensity, 1, SSI_INT,"1 = enable the output of intensity I (mean of squared input values multiplied by a Hamming window)");
			addOption ("loudness",&loudness, 1, SSI_INT,"1 = enable the output of loudness L : L = (I/I0)^0.3 ; I0 = 0.000001 (for sample values normalised to the range -1..1)");
				
		};

		ssi_size_t intensity;
		ssi_size_t loudness;
		
	};

public:

	static const ssi_char_t *GetCreateName () { return "OSIntensity"; };
	static IObject *Create (const ssi_char_t *file) { return new OSIntensity (file); };
	~OSIntensity ();

	OSIntensity::Options *getOptions () { return &_options; };
	const ssi_char_t *getName () { return GetCreateName (); };
	const ssi_char_t *getInfo () { return "This component computes simplified frame OSIntensity (narrow band approximation)."; };

	void transform_enter (ssi_stream_t &stream_in,
		ssi_stream_t &stream_out,
		ssi_size_t xtra_stream_in_num = 0,
		ssi_stream_t xtra_stream_in[] = 0);
	void transform (ITransformer::info info,
		ssi_stream_t &stream_in,
		ssi_stream_t &stream_out,
		ssi_size_t xtra_stream_in_num = 0,
		ssi_stream_t xtra_stream_in[] = 0);
	void transform_flush (ssi_stream_t &stream_in,
		ssi_stream_t &stream_out,
		ssi_size_t xtra_stream_in_num = 0,
		ssi_stream_t xtra_stream_in[] = 0);

	ssi_size_t getSampleDimensionOut (ssi_size_t sample_dimension_in) {

		if (sample_dimension_in != 1) {
			ssi_err ("dimension != 1 not supported");
			return 0;
		}
		
		ssi_size_t n = 0;

		if(_options.intensity)
			n++;
		if(_options.loudness)
			n++;

		return n;	
	}

	ssi_size_t getSampleBytesOut (ssi_size_t sample_bytes_in) {
		return sample_bytes_in;
	}

	ssi_type_t getSampleTypeOut (ssi_type_t sample_type_in) {

		if (sample_type_in != SSI_REAL) {
			ssi_err ("type %s not supported", SSI_TYPE_NAMES[sample_type_in]);
			return SSI_UNDEF;
		}

		return SSI_REAL;
	}
	
protected:

	OSIntensity (const ssi_char_t *file = 0);
	OSIntensity::Options _options;
	ssi_char_t *_file;
	double I0;
	double *hamWin;
    long nWin;
    double winSum;
    
	
};

}

#endif
