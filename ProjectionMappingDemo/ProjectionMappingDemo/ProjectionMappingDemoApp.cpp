/*	Created by Bruce Drummond on 11/7/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "ProjectionMappingDemoApp.h"
#include "poApplication.h"
#include "poCamera.h"


// APP CONSTRUCTOR. Create all objects here.
ProjectionMappingDemoApp::ProjectionMappingDemoApp() {
	addModifier(new po::Camera2D(po::Color::black));
	
	po::lookUpAndSetPath("Resources");
	
	image = new po::RectShape("ghostly_02_small.png");
	addChild(image);
	
	po::FBO* imageFBO = new po::FBO(image->getWidth(),image->getHeight());
	image->addModifier(imageFBO);
	
	container = new po::Object();
	container->position.set(50,50,0);
	addChild(container);
	
	map = new MappingObject(20, 20, imageFBO->getColorTexture());
	container->addChild(map);
	
	addEvent(po::KEY_DOWN_EVENT, this);
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
void ProjectionMappingDemoApp::eventHandler(po::Event *event) {
	if( event->type == po::KEY_DOWN_EVENT ){
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
			float diameter = po::Rand(20,100);
			po::OvalShape *shape = new po::OvalShape(diameter,diameter,50);
			shape->position.set(po::Rand(0, image->getWidth()), po::Rand(0, image->getHeight()), 0);
			shape->fillColor = blendColors(po::Color::orange , po::Color::random(), .8);
			
			// Don't forget to add it to the canvas
			image->addChild(shape);
			
			
			// What the heck, let's make this dots animate
			shape->scaleTween
			.set(po::Point(2.f,2.f,1))
			.setDuration(1.f)
			.setRepeat(po::TWEEN_REPEAT_PINGPONG)
			.setTweenFunction(po::TWEEN_SINUS_INOUT_FUNC)
			.start();
			// Too much? Probably.
		}
	}
}

// MESSAGE HANDLER. Called from within the app. Use for message passing.
void ProjectionMappingDemoApp::messageHandler(const std::string &msg, const po::Dictionary& dict, const po::Object *sender) {
	
}
