#pragma once

/*	Created by Jonathan Bobrow on 3/28/13.
 *	Copyright 2013 __MyCompanyName__. All rights reserved.
 */

#include "poShapeBasics2D.h"

class poMesh2D : public poObject
{
public:
    poMesh2D(int rows, int columns, poTexture* tex);
    void draw();
	
    int numRows, numColumns;
	std::vector<poPoint> points, coords;
	std::vector<uint16_t> indices;
	poTexture* texture;
};