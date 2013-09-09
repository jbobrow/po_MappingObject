#pragma once

/*	Created by Jonathan Bobrow on 1/23/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "poMesh2D.h"
#include "poShapeBasics2D.h"

const poColor selected_color = poColor(1,0,1);
const poColor deselected_color = poColor(0,0,0,.1);

class MappingHandle : public poOvalShape
{
public:
	MappingHandle(int, int);

	int x, y;
	bool selected;
	
};

class MappingObject : public poObject
{
public:
	MappingObject(int _numRows, int _numColumns, poTexture* tex=NULL);
	virtual ~MappingObject();
	
	void loadPositions(std::string path = "positions.xml");
	void savePositions(std::string path = "positions.xml");
	
	void showHandles();
	void hideHandles();
	
	void moveSelectedHandles(poPoint p);
	
	virtual void update();
	virtual void drawAfter();
	virtual void eventHandler(poEvent *event);
	virtual void messageHandler(const std::string &msg, const poDictionary& dict=poDictionary());
	
	poMesh2D	*mesh;
	int numRows;
	int numCols;
	
	std::vector<MappingHandle *> handles;
};