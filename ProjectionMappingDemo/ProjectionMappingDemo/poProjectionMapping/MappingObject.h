#pragma once

/*	Created by Jonathan Bobrow on 1/23/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "poObject.h"
#include "poMesh2D.h"
#include "poShapeBasics2D.h"

const po::Color selected_color = po::Color(1,0,1);
const po::Color deselected_color = po::Color(0,0,0,.1);

class MappingHandle : public po::OvalShape
{
public:
	MappingHandle(int, int);

	int index;
	int x, y;
	bool selected;
};

class MappingObject : public po::Object
{
public:
	MappingObject(int _numRows, int _numColumns, po::Texture* tex=NULL);
	virtual ~MappingObject();
	
	void loadPositions(std::string path = "positions.xml");
	void savePositions(std::string path = "positions.xml");
	
	void showHandles();
	void hideHandles();
	
	void updateSelectedHandle();
	void moveSelectedHandles(po::Point p);
	
	virtual void update();
	virtual void drawAfter();
	virtual void eventHandler(po::Event *event);
	virtual void messageHandler(const std::string &msg, const po::Dictionary& dict=po::Dictionary());
	
	poMesh2D	*mesh;
	int numRows;
	int numCols;
	
	int index_selected;
	
	std::vector<MappingHandle *> handles;
};