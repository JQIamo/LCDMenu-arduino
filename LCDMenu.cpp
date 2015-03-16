/*
   LCDMenu.cpp - LCD Menu navigator
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
 
 
#include "LCDMenu.h"
//#include "LCDMenuItem.h" 

//LCDMenuItem * menuRoot

LCDMenu::LCDMenu(LCDMenuItem * root, WriteLCDCallback lcdCallback){
	_root = root;
	_currentMenu = _root;
	_menu_state = MENU_NAV;
	_lcdCallback = &lcdCallback;

}


void LCDMenu::buildNavigationTree(){

} 
	
void LCDMenu::action(menu_action_t action){
	// create displaytext object
	dtext_t displayText = {"",""};
	if (_currentMenu->hasActionCallback()){
		// pass displayText to callback for currentMenu
		_currentMenu->executeActionCallback(displayText, action);
	} else {
	
		// default action
	}
	
	// pass display text to the write LCD function
	(*_lcdCallback)(displayText);
}
	
LCDMenuItem * LCDMenu::getRoot(){
	return _root;
}
	
void LCDMenu::setRoot(LCDMenuItem * root){
	_root = root;
}
	
LCDMenuItem * LCDMenu::getCurrentMenu(){
	return _currentMenu;
}
	
void LCDMenu::setCurrentMenu(LCDMenuItem * menu){
	_currentMenu = menu;
}
	
menu_state_t LCDMenu::getMenuState(){
	return _menu_state;
}
	
void LCDMenu::setMenuState(menu_state_t menu_state){
	_menu_state = menu_state;
}

void LCDMenu::advanceNext(){
	//LCDMenuItem * nextMenu;
	LCDMenuItem * parent = _currentMenu->getParent();
	int siblingCount = _currentMenu->siblingCount();
	int currentIndex = _currentMenu->getIndex();
	int nextIndex;
	if (currentIndex + 1 >= siblingCount){
		nextIndex = 0;
	} else {
		nextIndex = currentIndex + 1;
	}
	
	_currentMenu = _currentMenu->getChild(nextIndex); 
	

}

void LCDMenu::advancePrevious(){
	
	LCDMenuItem * parent = _currentMenu->getParent();
	int siblingCount = _currentMenu->siblingCount();
	int currentIndex = _currentMenu->getIndex();
	int nextIndex;
	if (currentIndex + 1 >= siblingCount){
		nextIndex = 0;
	} else {
		nextIndex = currentIndex + 1;
	}
	
	_currentMenu = _currentMenu->getChild(nextIndex); 
}

void LCDMenu::advanceParent(){
	if (_currentMenu->hasParent()){
		_currentMenu = _currentMenu->getParent();
	}
}

void LCDMenu::advanceChild(){
	_currentMenu = _currentMenu->getChild(0);
}