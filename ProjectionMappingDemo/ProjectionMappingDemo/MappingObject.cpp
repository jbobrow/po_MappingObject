#include "MappingObject.h"
#include "poApplication.h"

Handle::Handle(int x, int y)
:	poOvalShape(10,10,50)
,	x(x)
,	y(y)
{
	fillColor = poColor::red;
}


MappingObject::MappingObject(int _numRows, int _numColumns, poTexture *tex)
{
	mesh = new poMesh2D(_numRows, _numColumns, tex);
	addChild(mesh);
	
	for(int y = 0; y < _numRows; y++){
		for(int x = 0; x < _numColumns; x++){
			Handle *handle = new Handle(x, y);
			
			float xPos = (x / (float)_numColumns) * tex->getWidth();
			float yPos = (y / (float)_numRows) * tex->getHeight();
						  
			handle->position = poPoint(xPos, yPos, 0.f);
			handle->addEvent(PO_MOUSE_DOWN_INSIDE_EVENT, this);
			handle->addEvent(PO_MOUSE_DRAG_INSIDE_EVENT, this);
			handles.push_back(handle);
			addChild(handles.back());
		}
	}
	
	addEvent(PO_MOUSE_UP_EVENT,  this);
}


MappingObject::~MappingObject() 
{
}


void MappingObject::update() 
{
}


void MappingObject::loadPositions(std::string path)
{
	poDictionary positions;
	char filename[256];
	sprintf(filename, "%s%s", path.c_str(), "positions.xml");
	positions.read(filename);
	
	for(int i=0; i<handles.size(); i++){
		poPoint p = positions.getPoint(poToString(i));
		handles[i]->position = p;
		mesh->points[i] = p;
	}
}


void MappingObject::savePositions(std::string path)
{
	poDictionary positions;
	for(int i=0; i<handles.size(); i++){
		positions.set(poToString(i), handles[i]->position);
	}
	
	char filename[256];
	sprintf(filename, "%s%s", path.c_str(), "positions.xml");
	positions.write(filename);
}


void MappingObject::showHandles()
{
	for(int i=0; i<handles.size(); i++){
		handles[i]->visible = true;
	}
}


void MappingObject::hideHandles()
{
	for(int i=0; i<handles.size(); i++){
		handles[i]->visible = false;
	}
}


void MappingObject::eventHandler(poEvent *event)
{
	Handle *h = (Handle *) event->source;
	
	switch (event->type) {
		case PO_MOUSE_DOWN_INSIDE_EVENT:
			break;
		
		case PO_MOUSE_DRAG_INSIDE_EVENT:
		{
			h->position = objectToLocal(event->source, event->localPosition);
			
			int idx = h->y * mesh->numColumns + h->x;
			mesh->points[idx] = h->position;
			
			break;
		}
		case PO_MOUSE_UP_EVENT:
			break;
			
		default:
			break;
	}
}

void MappingObject::messageHandler(const std::string &msg, const poDictionary& dict) 
{
}
