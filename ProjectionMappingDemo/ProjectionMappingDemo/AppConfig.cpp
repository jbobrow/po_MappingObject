/////////////////////////////////////////
//
// pocode application configuration
//
/////////////////////////////////////////


#include "poApplication.h"
#include "ProjectionMappingDemoApp.h"

poObject *createObjectForID(uint uid) {
	return new ProjectionMappingDemoApp();
}

void setupApplication() {
	lookUpAndSetPath("resources");
	applicationCreateWindow(0, WINDOW_TYPE_NORMAL, "ProjectionMappingDemo", 100, 100, 800, 600);
}

void cleanupApplication() {
}