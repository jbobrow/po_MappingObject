/*	Created by Jonathan Bobrow on 1/23/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "ProjectionMappingDemoApp.h"
#include "poApplication.h"
#include "poCamera.h"


// APP CONSTRUCTOR. Create all objects here.
ProjectionMappingDemoApp::ProjectionMappingDemoApp() {
	addModifier(new poCamera2D(poColor::black));
	
	image = new poRectShape("ghostly_02_grid.png");
	addChild(image);
	
	poFBO* imageFBO = new poFBO(image->getWidth(),image->getHeight());
	image->addModifier(imageFBO);
		
	map = new MappingObject(20, 20, imageFBO->getColorTexture());
	map->position = poPoint(50,50);
	addChild(map);
	
	addEvent(PO_KEY_DOWN_EVENT, this);
}

// APP DESTRUCTOR. Delete all objects here.
ProjectionMappingDemoApp::~ProjectionMappingDemoApp() {
}

// UPDATE. Called once per frame. Animate objects here.
void ProjectionMappingDemoApp::update() {
	
}

// DRAW. Called once per frame. Draw objects here.
void ProjectionMappingDemoApp::draw() {
	
}

// EVENT HANDLER. Called when events happen. Respond to events here.
void ProjectionMappingDemoApp::eventHandler(poEvent *event) {
	
	if( event->type == PO_KEY_DOWN_EVENT ){
		if( event->keyChar == 'S')
			map->savePositions();
		if( event->keyChar == 'L')
			map->loadPositions();
		if( event->keyChar == 'h')
			map->hideHandles();
		if( event->keyChar == 'H')
			map->showHandles();
		if( event->keyChar == ' ') {
			
			// How about a dot of a random diameter
			float diameter = poRand(20,100);
			poOvalShape *shape = new poOvalShape(diameter,diameter,50);
			shape->position.set(poRand(0, image->getWidth()), poRand(0, image->getHeight()), 0);
			shape->fillColor = blendColors(poColor::orange , poColor::random(), .8);
			
			// Don't forget to add it to the canvas
			image->addChild(shape);
			
			
			// What the heck, let's make this dots animate
			shape->scaleTween
				.set(poPoint(2.f,2.f,1))
				.setDuration(1.f)
				.setRepeat(PO_TWEEN_REPEAT_PINGPONG)
				.setTweenFunction(PO_TWEEN_SINUS_INOUT_FUNC)
				.start();
				// Too much? Probably.
		}
	}
}

// MESSAGE HANDLER. Called from within the app. Use for message passing.
void ProjectionMappingDemoApp::messageHandler(const std::string &msg, const poDictionary& dict) {
	
}
