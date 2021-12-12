//***********************************************************************************************
//NielsenPlugs: Modules for VCV Rack by Jens Peter Nielsen
//
//See ./LICENSE.md for all licenses
//***********************************************************************************************


#include "NielsenPlugs.hpp"


Plugin *pluginInstance;


void init(Plugin *p) {
	pluginInstance = p;

	readThemeAndContrastFromDefault();

	p->addModel(modelBlankPanel);
}

