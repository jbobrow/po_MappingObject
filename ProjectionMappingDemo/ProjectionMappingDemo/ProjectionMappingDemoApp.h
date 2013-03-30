/*	Created by Jonathan Bobrow on 1/23/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "MappingObject.h"
#include "poFBO.h"

class ProjectionMappingDemoApp : public poObject {
public:
	ProjectionMappingDemoApp();
	virtual ~ProjectionMappingDemoApp();
	
    virtual void update();
    
    virtual void draw();
	
    virtual void eventHandler(poEvent *event);
	
    virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
	
	MappingObject *map;
	
	poRectShape *image;
	poFBO		*imageFBO;
};

