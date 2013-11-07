#pragma once

/*	Created by Jonathan Bobrow on 3/28/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "poShapeBasics2D.h"

class poMesh2D : public po::Object
{
public:
    poMesh2D(int rows, int columns, po::Texture* tex);
    void draw();
	
    int numRows, numColumns;
	std::vector<po::Point> points, coords;
	std::vector<uint16_t> indices;
	po::Texture* texture;
};