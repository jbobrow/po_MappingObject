/*	Created by Bruce Drummond on 11/7/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"

#include "MappingObject.h"
#include "poFBO.h"

class ProjectionMappingDemoApp : public po::Object {
public:
	ProjectionMappingDemoApp();
	virtual ~ProjectionMappingDemoApp();
	
    virtual void update();
    
    virtual void draw();
	
    virtual void eventHandler(po::Event *event);
	
    virtual void messageHandler(const std::string &msg, const po::Dictionary& dict=po::Dictionary(), const po::Object *sender=NULL);
private:
	po::Object *container;
	
	MappingObject *map;
	
	po::RectShape *image;
	po::FBO		*imageFBO;
};

