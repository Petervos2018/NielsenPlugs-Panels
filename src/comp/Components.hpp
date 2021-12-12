//***********************************************************************************************
//NielsenPlugs: Modules for VCV Rack by Jens Peter Nielsen
//
//See ./LICENSE.md for all licenses
//***********************************************************************************************

#pragma once

#include "rack.hpp"
#include "PanelTheme.hpp"

using namespace rack;

extern Plugin *pluginInstance;


static const int colDelta = 50;
static const NVGcolor colTop = nvgRGB(128 - colDelta, 128 - colDelta, 128 - colDelta);
static const NVGcolor colBot = nvgRGB(128 + colDelta, 128 + colDelta, 128 + colDelta);

static const int colDeltaD = 30;
static const NVGcolor colTopD = nvgRGB(128 - colDeltaD, 128 - colDeltaD, 128 - colDeltaD);
static const NVGcolor colBotD = nvgRGB(128 + colDeltaD, 128 + colDeltaD, 128 + colDeltaD);

// Helpers
// ----------------------------------------

// Dynamic widgets
template <class TDynamicScrew>
TDynamicScrew* createDynamicScrew(Vec pos, int* mode) {
	TDynamicScrew *dynScrew = createWidget<TDynamicScrew>(pos);
	dynScrew->mode = mode;
	dynScrew->refreshForTheme();// all TDynamicScrew must have this
	return dynScrew;
}


// Variations on existing knobs, lights, etc
// ----------------------------------------

// Screws
// ----------

struct DynamicSVGScrew : SvgWidget {
    int* mode = NULL;
    int oldMode = -1;
    std::vector<std::shared_ptr<Svg>> frames;
	std::string frameAltName;

    void addFrame(std::shared_ptr<Svg> svg);
    void addFrameAlt(std::string filename) {frameAltName = filename;}
	void refreshForTheme();
    void step() override;
};


struct IMScrew : DynamicSVGScrew {
	IMScrew() {
		addFrame(APP->window->loadSvg(asset::system("res/ComponentLibrary/ScrewSilver.svg")));
		addFrameAlt(asset::system("res/ComponentLibrary/ScrewBlack.svg"));
	}
};


// Svg Widgets
// ----------

struct DisplayBackground : TransparentWidget {
	int* mode = NULL;
	DisplayBackground(Vec(_pos), Vec(_size), int* _mode) {
		box.size = _size;
		box.pos = _pos; 
		mode = _mode;
	}
	void draw(const DrawArgs& args) override;
};


