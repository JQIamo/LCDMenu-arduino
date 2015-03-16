/*
   LCDMenuItem.h - LCD Menu navigator
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
 

#ifndef LCD_MENU_ITEM_H
#define LCD_MENU_ITEM_H


 //! Defines maximum number of menus at a given level
#define MAX_IMMEDIATE_CHILDREN 16


//! Enumerate action types
/*!
	Define interaction types. You are responsible for 
*/
enum menu_action_t 
	{ LEFT_ACTION, RIGHT_ACTION, PUSH_ACTION, HOLD_ACTION };


//! Typedef for LCD display text
typedef char * dtext_t[2];

//! Typedef for menu action callback.
typedef void (* ActionCallback)(dtext_t, menu_action_t);


//! Typedef for callback to write text to LCD display.
/*!
	This defines a callback type for writing text to LCD display.
	Argument takes a 2-element array of strings.
	
*/
typedef void (* WriteLCDCallback)(dtext_t);


//! Enum for menu state.
/*!
	MENU_NAV: Interpret actions as navigation actions
	MENU_EDIT: Interpret actions as edit actions.
*/
enum menu_state_t { MENU_NAV, MENU_EDIT };


//! LCD Menu item.
/*!
	Class definition for a menu entry.
*/
class LCDMenuItem
{
	public:
	
	//! Constructor for LCDMenuItem
	/*!
		Creates a menu item.
		
		\sa LCDMenu
	*/
	LCDMenuItem(LCDMenuItem * parent, int index);
	
	
	//! Adds an action callback function to the given menu
	/*!
		Default action is to scroll to the next sibling (left/right),
		or traverse downwards on a push action.
		
		If the menu item is designed for actual user input, rather than
		navigation, you will need to register an action callback. This is a 
		function you have defined somewhere in your Arduino sketch; it takes
		a single argument (menu_action_t action), and must return a displaytext
		object dtext_t for the LCD to render.
		
		For example, you might define something like
		
		```
		dtext_t 
		```
		
		\sa ActionCallback, menu_action_t, dtext_t
	*/
	void addActionCallback(ActionCallback callback);
	
	
	//! Executes the action callback for the given LCDMenuItem.
	void executeActionCallback(dtext_t displaytext, menu_action_t action);
	
	//! Test if action callback has been assigned.
	/*!
		\sa addActionCallback, executeActionCallback
	*/
	bool hasActionCallback();
	
	//! Test if menu item has parent (ie, is it root?)
	bool hasParent();
	
	//! Returns the number of sibling menu items.
	int siblingCount();
	
	//! Returns the number of child menu items.
	int childrenCount();
	
	//! Returns the index of menu item.
	int getIndex();
	
	//! Returns pointer to the parent menu item.
	LCDMenuItem * getParent();
	
	//! Returns pointer to the child menu item in the given index.
	LCDMenuItem * getChild(int index);
	
	//! Adds a child menu item
	void addChild(LCDMenuItem * child, int index);
	
	private:
	
		//! Number of children menus
		int _numChildren;
		
		//! Default display text
		dtext_t _displayText;
		
		//! Pointer to parent item
		/*!
			Pointer to the parent of the given LCDMenuItem.
		*/
		LCDMenuItem * _parent;
		
		//! Pointer list of immediate children
		/*!
			would probably be better to do this via realloc
		*/
		LCDMenuItem * _children[MAX_IMMEDIATE_CHILDREN];
		
		//! Index of the LCDMenuItem.
		/*!
			The LCDMenuItem index defines which order it is displayed amongst
			its siblings.
		*/
		int _index;
		
		//! Callback action pointer
		ActionCallback * _actionCallback;
		
		


};

#endif