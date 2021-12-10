//***********************************************************************************************
//NielsenPlugs: Modules for VCV Rack by Jens Peter Nielsen
//
//See ./LICENSE.md for all licenses
//***********************************************************************************************


#include "Components.hpp"


// Variations on existing knobs, lights, etc
// ----------------------------------------

// Screws
// ----------

void DynamicSVGScrew::addFrame(std::shared_ptr<Svg> svg) {
	frames.push_back(svg);
    if(frames.size() == 1) {
        setSvg(svg);
	}
}

void DynamicSVGScrew::refreshForTheme() {
	int newMode = isDark(mode) ? 1 : 0;
	if (newMode != oldMode) {
        if (newMode > 0 && !frameAltName.empty()) {// JIT loading of alternate skin
			frames.push_back(APP->window->loadSvg(frameAltName));
			frameAltName.clear();// don't reload!
		}
        setSvg(frames[newMode]);
        oldMode = newMode;
    }
}

void DynamicSVGScrew::step() {
	refreshForTheme();
	SvgWidget::step();
}


// Svg Widgets
// ----------

void DisplayBackground::draw(const DrawArgs& args) {
	if (isDark(mode)) {
		nvgBeginPath(args.vg);
		NVGpaint grad = nvgLinearGradient(args.vg, 0, 0, 0, box.size.y, colTopD, colBotD);	
		nvgRoundedRect(args.vg, -1.5f, -1.5f, box.size.x + 3.0f, box.size.y + 3.0f, 5.0f);
		nvgFillPaint(args.vg, grad);
		nvgFill(args.vg);
	}

	NVGcolor backgroundColor = nvgRGB(0x38, 0x38, 0x38); 
	NVGcolor borderColor = nvgRGB(0x10, 0x10, 0x10);
	nvgBeginPath(args.vg);
	nvgRoundedRect(args.vg, 0.0, 0.0, box.size.x, box.size.y, 5.0f);
	nvgFillColor(args.vg, backgroundColor);
	nvgFill(args.vg);
	nvgStrokeWidth(args.vg, 1.0);
	nvgStrokeColor(args.vg, borderColor);
	nvgStroke(args.vg);
}
