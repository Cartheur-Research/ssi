// ControlButton.h
// author: Johannes Wagner <wagner@hcm-lab.de>
// created: 2008/05/26
// Copyright (C) University of Augsburg, Lab for Human Centered Multimedia
//
// *************************************************************************************************
//
// This file is part of Social Signal Interpretation (SSI) developed at the 
// Lab for Human Centered Multimedia of the University of Augsburg
//
// This library is free software; you can redistribute itand/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 3 of the License, or any laterversion.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FORA PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along withthis library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
//*************************************************************************************************

#ifndef SSI_CONTROL_CONTROLBUTTON_H
#define SSI_CONTROL_CONTROLBUTTON_H

#include "SSI_Define.h"

#ifndef SSI_USE_SDL

#include "base/IObject.h"
#include "ioput/option/OptionList.h"
#include "event/EventAddress.h"
#include "base/IWindow.h"
#include "graphic/Button.h"

namespace ssi {

class ControlButton : public SSI_IRunnableObject, public Button::ICallback {

public:

	class Options : public OptionList {

	public:

		Options ()
		: value(true) {

			pos[0] = 0;
			pos[1] = 0;
			pos[2] = 100;
			pos[3] = 100;

			setLabel("");
			setTitle("Button");
			setId("");
			setMessage("reset");

			addOption ("label", &label, SSI_MAX_CHAR, SSI_CHAR, "button label");
			addOption ("title", &title, SSI_MAX_CHAR, SSI_CHAR, "window title");			
			addOption ("pos", &pos, 4, SSI_INT, "position of check box on screen [posx,posy,width,height]");
			addOption ("id", id, SSI_MAX_CHAR, SSI_CHAR, "object id(s) (if several separate by comma)");
			addOption ("message", message, SSI_MAX_CHAR, SSI_CHAR, "message name (if 'reset', an RESET notification is sent)");			
		}

		void setLabel(const ssi_char_t *string) {
			if (string) {
				ssi_strcpy(this->label, string);
			}
		}
		void setTitle(const ssi_char_t *string) {
			if (string) {
				ssi_strcpy(this->title, string);
			}
		}
		void setId (const ssi_char_t *string) {			
			if (string) {
				ssi_strcpy(this->id, string);
			}
		}
		void setMessage(const ssi_char_t *string) {
			if (string) {
				ssi_strcpy(this->message, string);
			}
		}
		void setPos (int x, int y, int width, int height) {
			pos[0] = x;
			pos[1] = y;
			pos[2] = width;
			pos[3] = height;
		}

		ssi_char_t label[SSI_MAX_CHAR];
		ssi_char_t title[SSI_MAX_CHAR];
		int pos[4];
		ssi_char_t id[SSI_MAX_CHAR];
		ssi_char_t message[SSI_MAX_CHAR];			
		bool value;
	};

public:

	static const ssi_char_t *GetCreateName() { return "ControlButton"; };
	static IObject *Create(const ssi_char_t *file) { return new ControlButton(file); };
	~ControlButton();

	static ssi_char_t *ssi_log_name;
	int ssi_log_level;

	Options *getOptions() { return &_options; };
	const ssi_char_t *getName() { return GetCreateName(); };
	const ssi_char_t *getInfo() { return "Button to send messages to other objects."; };

	bool start();
	bool stop();

	bool notify(INotify::COMMAND::List command, const ssi_char_t *message);

protected:

	ControlButton (const ssi_char_t *file = 0);
	ControlButton::Options _options;
	ssi_char_t *_file;

	IWindow *_window;
	Button *_button;

	ssi_size_t _n_targets;
	IObject **_targets;	
	ssi_char_t **_target_ids;
	bool *_ready;

	void update ();
};

}

#endif

#endif