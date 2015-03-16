/*
   LCDMenuItem.cpp - LCD Menu navigator
   Created by Neal Pisenti, 2013
   JQI - Strontium - UMD

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */
 
#include "LCDMenuItem.h"
 
LCDMenuItem::LCDMenuItem(LCDMenuItem * parent, int index) :
	_parent(0),
	_index(0),
	_numChildren(0),
	_displayText({"Menu Item", ""}),
	_actionCallback(0)
{

	_index = index;
	_parent = parent;
	
	// check that parent not Null; add as child menu
	if(_parent != 0){
		_parent->addChild(this, index);
	}
 	
}


void LCDMenuItem::addActionCallback(ActionCallback callback){
	_actionCallback = &callback;
}

void LCDMenuItem::executeActionCallback(dtext_t displayText, menu_action_t action){
	// verify there is an associated action callback
	if (this->hasActionCallback()){
		// execute said callback function.
		(*_actionCallback)(displayText, action);
	}
}

bool LCDMenuItem::hasActionCallback(){
	// check if _actionCallback is null ptr
	return (_actionCallback != 0);
}

int LCDMenuItem::siblingCount(){
	int siblings = 0;
	if (this->hasParent()){	// check if parent is null; ie, root level
		siblings = _parent->childrenCount();
	}
	return siblings;
}

int LCDMenuItem::childrenCount(){
	return _numChildren;
}

int LCDMenuItem::getIndex(){
	return _index;
}

bool LCDMenuItem::hasParent(){
	return (_parent != 0);
}

LCDMenuItem * LCDMenuItem::getParent(){
	return _parent;
}

LCDMenuItem * LCDMenuItem::getChild(int index){
	// better not pass bad index!
	return _children[index];
}

void LCDMenuItem::addChild(LCDMenuItem * child, int index){
	// Adds the pointer to the list, and increments numChildren.
	_children[index] = child;
	_numChildren += 1;
}