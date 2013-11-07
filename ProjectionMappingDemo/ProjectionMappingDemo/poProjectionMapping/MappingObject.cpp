#include "MappingObject.h"
#include "poApplication.h"

MappingHandle::MappingHandle(int x, int y)
:	po::OvalShape(10,10,30)
,	x(x)
,	y(y)
,	selected(false)
{
	fillColor = deselected_color;
	index = 0;
}


MappingObject::MappingObject(int _numRows, int _numColumns, po::Texture *tex):
numRows(_numRows),
numCols(_numColumns)
{
	mesh = new poMesh2D(_numRows, _numColumns, tex);
	addChild(mesh);
	
	for(int y = 0; y < numRows; y++){
		for(int x = 0; x < numCols; x++){
			MappingHandle *handle = new MappingHandle(x, y);
			
			float xPos = (x / (float)numCols) * tex->getWidth();
			float yPos = (y / (float)numRows) * tex->getHeight();
						  
			handle->position = po::Point(xPos, yPos, 0.f);
			handle->index = y * numCols + x;
			handle->addEvent(po::MOUSE_DOWN_INSIDE_EVENT, this);
			handle->addEvent(po::MOUSE_DRAG_INSIDE_EVENT, this);
            handle->visible = false;
			handles.push_back(handle);
			addChild(handles.back());
		}
	}
	
	addEvent(po::MOUSE_UP_EVENT,  this);
	addEvent(po::KEY_DOWN_EVENT, this);
	
	index_selected = -1;
}


MappingObject::~MappingObject() 
{
}


void MappingObject::update() 
{
}

void MappingObject::drawAfter(){
	if(handles[0]->visible){
		po::setColor(0,1,1,.8);	// dull cyan grid
		po::setLineWidth(1);
		for(int i=0; i<handles.size(); i++)
		{
			MappingHandle* handle = handles[i];
			po::Point& handle_pos = handle->position;

			if(handle->y > 0){
				int index = (handle->y-1)*numCols + handle->x;
				po::Point pos = handles[index]->position;
				po::drawLine(handle_pos, pos);
			}

			if(handle->x > 0){
				int index = handle->y*numCols + handle->x - 1;
				po::Point pos = handles[index]->position;
				po::drawLine(handle_pos, pos);
			}
		}
	}
}

void MappingObject::loadPositions(std::string path)
{
	po::Dictionary positions;
	positions.read(path);
	
	for(int i=0; i<handles.size(); i++){
		po::Point p = positions.getPoint(po::toString(i));
		handles[i]->position = p;
		mesh->points[i] = p;
	}
}


void MappingObject::savePositions(std::string path)
{
	po::Dictionary positions;
	for(int i=0; i<handles.size(); i++){
		positions.set(po::toString(i), handles[i]->position);
	}
	
	positions.write(path);
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


void MappingObject::updateSelectedHandle()
{	
	// deselect all handles
	for(int i=0; i<handles.size(); i++){
		handles[i]->selected = false;
		handles[i]->fillColor = deselected_color;
	}
	
	handles[index_selected]->selected = true;
	handles[index_selected]->fillColor = selected_color;
}


void MappingObject::moveSelectedHandles(po::Point p)
{
	for(int i=0; i<handles.size(); i++){
		MappingHandle *h = handles[i];
		
		if(h->selected){
			h->position+=p;
		
			int idx = h->y * mesh->numColumns + h->x;
			mesh->points[idx] = h->position;
		}
	}
}


void MappingObject::eventHandler(po::Event *event)
{
	MappingHandle *h = (MappingHandle *) event->source;
	
	switch (event->type) {
		case po::MOUSE_DOWN_INSIDE_EVENT:
			// deselect all handles
			for(int i=0; i<handles.size(); i++){
				handles[i]->selected = false;
				handles[i]->fillColor = deselected_color;
			}
			
			// select the clicked on handle
			h->selected = !h->selected;
			if(h->selected){
				h->fillColor = selected_color;
				index_selected = h->index;
			}
			else
				h->fillColor = deselected_color;
			
			break;
		
		case po::MOUSE_DRAG_INSIDE_EVENT:
		{
			h->position = objectToLocal(event->source, event->localPosition);
			
			int idx = h->y * mesh->numColumns + h->x;
			mesh->points[idx] = h->position;
			
			break;
		}
		case po::MOUSE_UP_EVENT:
			break;
			
		case po::KEY_DOWN_EVENT:
		{
			switch (event->keyCode) {
					
				// OS X
				case po::LEFT_ARROW:		moveSelectedHandles(po::Point(-1,0));	break;
				case po::RIGHT_ARROW:	moveSelectedHandles(po::Point(1,0));	break;
				case po::DOWN_ARROW:		moveSelectedHandles(po::Point(0,1));	break;
				case po::UP_ARROW:		moveSelectedHandles(po::Point(0,-1));	break;
				
				// WINDOWS
				case 37:	moveSelectedHandles(po::Point(-1,0));	break;
				case 39:	moveSelectedHandles(po::Point(1,0));	break;
				case 40:	moveSelectedHandles(po::Point(0,1));	break;
				case 38:	moveSelectedHandles(po::Point(0,-1));	break;
					
				default:
					break;
			}
			
			switch (event->keyChar) {

				case ',':	if(index_selected > 0)
								index_selected -= 1;
							updateSelectedHandle();
							break;
					
				case '.':	if(index_selected < numCols*numRows-1)
								index_selected += 1;
							updateSelectedHandle();
							break;
					
				case '<':	if(index_selected-numCols > 0)
								index_selected -= numCols;
							updateSelectedHandle();
							break;
					
				case '>':	if(index_selected+numCols < numCols*numRows-1)
								index_selected += numCols;
							updateSelectedHandle();
							break;
					
				default:
					break;
			}
			
			if(event->keyChar == 'C') {
				// deselect all selected handles
				for(int i=0; i<handles.size(); i++){
					handles[i]->selected = false;
					handles[i]->fillColor = deselected_color;
				}
			}
		}
			
		default:
			break;
	}
}

void MappingObject::messageHandler(const std::string &msg, const po::Dictionary& dict)
{
}
