#pragma once

/*	Created by Jonathan Bobrow on 1/23/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "poMesh2D.h"
#include "poShapeBasics2D.h"

class Handle : public poOvalShape
{
public:
	Handle(int, int);

	int x, y;
};

class MappingObject : public poObject
{
public:
	MappingObject(int _numRows, int _numColumns, poTexture* tex=NULL);
	virtual ~MappingObject();
	
	void loadPositions(std::string path="");
	void savePositions(std::string path="");
	
	void showHandles();
	void hideHandles();
	
	virtual void update();
	virtual void eventHandler(poEvent *event);
	virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
	
	poMesh2D	*mesh;
	
	std::vector<Handle *> handles;
};