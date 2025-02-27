// ISOverSample.h
// author: Johannes Wagner <wagner@hcm-lab.de>
// created: 2011/03/02
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

#pragma once

#ifndef SSI_MODEL_ISOVERSAMPLE_H
#define SSI_MODEL_ISOVERSAMPLE_H

#include "base/ISamples.h"

namespace ssi {

class ISOverSample : public ISamples {

public:

enum Strategy {
	RANDOM = 0,
	SMOTE
};

public:

	ISOverSample (ISamples *samples);
	~ISOverSample ();	

	void setSeed(ssi_size_t seed);

	bool setOver (Strategy strategy);
	bool setOver (ssi_size_t class_id, ssi_size_t add_n_samples, Strategy strategy);
	bool setOver (ssi_size_t n_classes, ssi_size_t *add_n_samples, Strategy strategy);

	void reset () { _samples.reset (); _next_over_count = 0; };
	ssi_sample_t *get (ssi_size_t index);
	ssi_sample_t *next (); 

	ssi_size_t getSize () { return _n_samples + _n_over; };
	ssi_size_t getSize (ssi_size_t class_id) { return _samples.getSize (class_id) + _n_over_per_class[class_id]; };

	ssi_size_t getClassSize () { return _samples.getClassSize (); };
	const ssi_char_t *getClassName (ssi_size_t class_id) { return _samples.getClassName (class_id); };
	
	ssi_size_t getUserSize () { return _samples.getUserSize (); };
	const ssi_char_t *getUserName (ssi_size_t user_id) { return _samples.getUserName (user_id); };

	ssi_size_t getStreamSize () { return _samples.getStreamSize (); };
	ssi_stream_t getStream (ssi_size_t index) { return _samples.getStream (index); };

	bool hasMissingData () { return _samples.hasMissingData (); };
	bool supportsShallowCopy () { return _samples.supportsShallowCopy (); };

	void setSmoteK (ssi_size_t k) {
		_smote_k = k;
	}

protected:

	static ssi_char_t *ssi_log_name;

	void release ();

	ISamples &_samples;	
	ssi_size_t _n_samples;
	ssi_size_t _n_over;
	ssi_size_t _n_classes;
	ssi_size_t *_n_over_per_class;
	ssi_sample_t *_over;
	ssi_size_t _next_over_count;

	ssi_size_t _smote_k;

	bool doDuplicate ();
	bool doSmote ();

	ssi_size_t _seed;

};

}

#endif
