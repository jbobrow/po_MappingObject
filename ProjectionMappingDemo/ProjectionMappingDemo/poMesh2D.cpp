#include "poMesh2D.h"
#include "poShader.h"
#include "poOpenGLState.h"

#include <boost/assign.hpp>

poMesh2D::poMesh2D(int r, int c, poTexture* tex)
:	numRows(r)
,	numColumns(c)
,	points(r*c)
,	coords(r*c)
,	texture(tex)
{
	int step_x = tex->getWidth() / (float)c;
	int step_y = tex->getHeight() / (float)r;
	
	for(int y=0; y<r; y++) {
		for(int x=0; x<c; x++) {
			points[y*c+x] = poPoint(x*step_x, y*step_y, 0);
			coords[y*c+x] = poPoint(x/(float)(c-1), 1 - y/(float)(r-1), 0);
		}
	}
	
	using namespace boost::assign;
	
	for(int y=0; y<r-1; y++) {
		for(int x=0; x<c-1; x++) {
			uint16_t a = y * c + x;
			uint16_t b = (y+1) * c + x;
			uint16_t c1 = y * c + (x+1);
			uint16_t d = (y+1) * c + (x+1);
			indices += a, b, c1, d, c1, b;
		}
	}
}

void poMesh2D::draw() {
	po::setColor(1.f,1.f,1.f,1.f);
	po::useTexture(texture->getUid(), false);
	po::useTex2DShader();
	po::updateActiveShader();

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(poPoint), &points[0].x);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(poPoint), &coords[0].x);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
	
	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}





