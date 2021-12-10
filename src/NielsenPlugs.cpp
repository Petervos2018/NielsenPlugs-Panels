//***********************************************************************************************
//Impromptu Modular: Modules for VCV Rack by Marc Boulé
//
//Based on code from the Fundamental and AudibleInstruments plugins by Andrew Belt 
//and graphics from the Component Library by Wes Milholen 
//See ./LICENSE.md for all licenses
//See ./res/fonts/ for font licenses
//***********************************************************************************************


#include "NielsenPlugs.hpp"


Plugin *pluginInstance;


void init(Plugin *p) {
	pluginInstance = p;

	readThemeAndContrastFromDefault();

	p->addModel(modelBlankPanel);
}

