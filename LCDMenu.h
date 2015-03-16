/*
   LCDMenu.h - LCD Menu navigator
   Created by Neal Pisenti, 2015
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
 
 
#ifndef LCD_MENU_H
#define LCD_MENU_H


#include "Arduino.h"
#include "LCDMenuItem.h"

class LCDMenu 
{

	public:
	
	//! Constructor for LCDMenu object
	/*!	Creates an LCDMenu object.
			
			
		\sa LCDMenuItem, WriteLCDCallback
	*/
	LCDMenu(LCDMenuItem * root, WriteLCDCallback lcdCallback);
	
	//! Builds a navigation tree for the given menu.
	/*!
		Essentially, adds in "back" menu items as needed.
	*/
	void buildNavigationTree(); 
	
	//! Initiate menu action
	/*!
		You are responsible for calling this! This depends on how you have the
		UI interface wired for your particular application.
		
		For example, you might have a rotary encoder. In the `void loop(){..}`
		portion of your code, you check for each of the action types, eg, :
		
		```
		if (encPos > lastPos){
			menu.action(RIGHT_ACTION);
			lastPos = encPos
		} else if { ...}
		```
	*/
	void action(menu_action_t action);
	
	//! Getter method for _root
	LCDMenuItem * getRoot();
	
	//! Setter method for _root
	void setRoot(LCDMenuItem * root);
	
	//! Getter method for _menu_state
	LCDMenuItem * getCurrentMenu();
	
	//! Setter method for _current_menu
	void setCurrentMenu(LCDMenuItem * menu);
	
	//! Getter method for _menu_state
	menu_state_t getMenuState();
	
	//! Setter method for _menu_state
	void setMenuState(menu_state_t menu_state);
	
	//! Advance _currentMenu to the next LCDMenuItem
	/*!
		Advances the pointer _currentMenu to the next menu item at the same
		level.
	*/
	void advanceNext();
	
	//! Advance _currentMenu to the previous LCDMenuItem
	/*!
		Advances the pointer _currentMenu to the previous menu item at the same
		level.
	*/
	void advancePrevious();
	
	//! Advance _currentMenu to the parent LCDMenuItem
	/*!
		Advances the pointer _currentMenu to the parent menu item.
	*/
	void advanceParent();
	
	//! Advance _currentMenu to the LCDMenuItem's child
	/*!
		Advances the pointer _currentMenu to the first child menu item.
	*/
	void advanceChild();
	
	
	private:
		//! LCD Callback function; used to write to LCD.
		WriteLCDCallback * _lcdCallback;
	
		//! Root of LCDMenu
		/*!
			Root LCDMenuItem for the LCDMenu.
			
			\sa getRoot, setRoot, LCDMenuItem
		*/
		LCDMenuItem * _root;
		
		//! Current menu item
		/*!
			Variable to keep track of currently displayed menu.
			
			\sa getCurrentMenu, setCurrentMenu, LCDMenuItem
		*/
		LCDMenuItem * _currentMenu;
		
		//! State variable for current menu item.
		/*!
			_menu_state is a state variable, which is used to decide how 
			LCDMenu should interpret a given action. For example, a PUSH_ACTION
			in the context of navigation defaults to "traverse the hierarchy," 
			whereas it means "save the entered state" in the context of 
			editing a menu item.
			
			Default callback functions interpret PUSH_ACTION as either
			traverse/edit, and LEFT_ACTION/RIGHT_ACTION as scroll or
			change menu state. To change menu state, you must register a 
			valid callback function, see LCDMenuItem::addActionCallback.
			
			
			\sa menu_state_t, menu_action_t, _currentMenu, 
			LCDMenuItem::addActionCallback
		*/
		menu_state_t _menu_state;
		
		

};

#endif