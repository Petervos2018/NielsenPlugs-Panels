//***********************************************************************************************
//NielsenPlugs
//Based on code from the Fundamental and AudibleInstruments plugins by Andrew Belt and Modules for VCV Rack by Marc Boulé
//See ./LICENSE.md for all licenses
//***********************************************************************************************

#pragma once

#include "rack.hpp"
#include "comp/Components.hpp"

using namespace rack;

extern Plugin *pluginInstance;

extern Model *modelBlankPanel;

// General constants
static const NVGcolor displayColOn = nvgRGB(0xaf, 0xd2, 0x2c);

// General objects

struct VecPx : Vec {
	// temporary method to avoid having to convert all px coordinates to mm; no use when making a new module (since mm is the standard)
	static constexpr float scl = 5.08f / 15.0f;
	VecPx(float _x, float _y) {
		x = mm2px(_x * scl);
		y = mm2px(_y * scl);
	}
};


struct RefreshCounter {
	// Note: because of stagger, and asyncronous dataFromJson, should not assume this processInputs() will return true on first run
	// of module::process()
	static const unsigned int displayRefreshStepSkips = 256;
	static const unsigned int userInputsStepSkipMask = 0xF;// sub interval of displayRefreshStepSkips, since inputs should be more responsive than lights
	// above value should make it such that inputs are sampled > 1kHz so as to not miss 1ms triggers
	
	unsigned int refreshCounter = (random::u32() % displayRefreshStepSkips);// stagger start values to avoid processing peaks when many Geo and Impromptu modules in the patch
	
	bool processInputs() {
		return ((refreshCounter & userInputsStepSkipMask) == 0);
	}
	bool processLights() {// this must be called even if module has no lights, since counter is decremented here
		refreshCounter++;
		bool process = refreshCounter >= displayRefreshStepSkips;
		if (process) {
			refreshCounter = 0;
		}
		return process;
	}
};

struct InstantiateExpanderItem : MenuItem {
	Module* module;
	Model* model;
	Vec posit;
	void onAction(const event::Action &e) override;
};
