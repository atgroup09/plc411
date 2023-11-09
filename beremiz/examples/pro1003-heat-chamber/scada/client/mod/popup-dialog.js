/*	JAVASCRIPT DOCUMENT
*
*
*	TEXT CODING - UTF-8
*
*	BEST VIEWED WITH A:
*		- tabulation  - 4,
*		- font family - monospace 10.
*/


/*   Module: popup dialog.
*
*    Copyright (C) 2016  ATgroup09 (atgroup09@gmail.com)
*
*    The JavaScript code in this page is free software: you can
*    redistribute it and/or modify it under the terms of the GNU
*    General Public License (GNU GPL) as published by the Free Software
*    Foundation, either version 3 of the License, or (at your option)
*    any later version.  The code is distributed WITHOUT ANY WARRANTY;
*    without even the implied warranty of MERCHANTABILITY or FITNESS
*    FOR A PARTICULAR PURPOSE.  See the GNU GPL for more details.
*
*    As additional permission under GNU GPL version 3 section 7, you
*    may distribute non-source (e.g., minimized or compacted) forms of
*    that code without the copy of the GNU GPL normally required by
*    section 4, provided you include this license notice and a URL
*    through which recipients can access the Corresponding Source.
*/


/*	Depending on the:
*
*		- global variables: none.
*
*
*		- libraries: none.
*
*
*		- CSS: none.
*/


/*	Global variables:
*
*
*
*	Functions:
*
*
*
*	Classes:
*
*
*
*	Methods in the prototype: none.
*
*
*	Class inheritance: none.
*
*
*	Initialization of global variables:
*
*/


//** GLOBAL VARIABLES


//** FUNCTIONS


//** CLASSES

/*	Class:	popup dialog.
*	Input:
*			IDIn - dialog ID.
*	Note:
*
*			HTML-structure of PopupDialog
*
*			<!-- popup dialog -->
*			<div data-role="popup" id="PopupDialog" data-overlay-theme="a" data-theme="a" data-dismissible="false" style="max-width:640px;">
*				<div data-role="header" data-theme="b">
*					<h1>---</h1>
*				</div>
*			<div role="main" class="ui-content">
*				<div class="ui-space-separator"></div>
*					<h4 class="ui-title">---</h4>
*					<div class="ui-space-separator"></div>
*					<a href="#" class="ui-btn ui-corner-all ui-shadow ui-btn-b" data-rel="back">Закрыть</a>
*				</div>
*			</div>
*
*			<!--  popup basic -->
*			<div data-role="popup" id="PopupBasic" data-position-to="window" data-overlay-theme="a" data-theme="b" class="ui-content">
*				Text
*			</div>
*/
function jsPopupDialog(IDIn)
{
	//Public properties
	
	
	//Private properties
	
	//* Dialog ID		[STRING]
	var ID = null;
	
	//* Dialog Nodes	[OBJECT || NULL]
	var Node = null;
	var TitleNode = null;
	var TextNode = null;
	
	//* The result of done functionality	[BOOLEAN]
	var CheckFunc = false;
	
	//* Dialog structure	[STRING]
	var CHILD_TAG__TITLE = "h1";
	var CHILD_TAG__TEXT  = "h4";
	
	
	//Methods
	
	//Public Method: Show popup dialog.
	//Input:
	//			TitleIn	- dialog title;	[STRING || NULL]
	//			TextIn	- dialog text.	[STRING || NULL]
	//Output:
	//			none.
	//Note:
	//
	this.show = function(TitleIn, TextIn)
	{
		if(CheckFunc && Node)
		{
			var Buff = null;
			
			if(TitleNode)
			{
				Buff = ((typeof TitleIn == "string") ? TitleIn : "");
				TitleNode.text(Buff);
			}
			
			if(TextNode)
			{
				Buff = ((typeof TextIn == "string") ? TextIn : "");
				TextNode.text(Buff);
			}
			
			Node.popup("open");
		}
	};
	
	//Public Method: Show popup basic dialog.
	//Input:
	//			TextIn - dialog text.	[STRING || NULL]
	//Output:
	//			none.
	//Note:
	//
	this.showBasic = function(TextIn)
	{
		if(CheckFunc && Node)
		{
			var Buff = ((typeof TextIn == "string") ? TextIn : "");
			Node.text(Buff);
			Node.popup("open");
		}
	};
	
	//Public Method: Init.
	//Input:
	//			IDIn - dialog ID.	[STRING]
	//Output:
	//			none.
	//
	this.init = function(IDIn)
	{
		ID        = null;
		Node      = null;
		TitleNode = null;
		TextNode  = null;
		
		if(CheckFunc && typeof IDIn == "string")
		{
			ID = IDIn;
			Node = $("#" + IDIn);
			
			if(Node)
			{
				TitleNode = Node.find(CHILD_TAG__TITLE);
				TextNode  = Node.find(CHILD_TAG__TEXT);
			}
		}
	};
	
	
	//Constructor
	
	CheckFunc = true;
	this.init(IDIn);
}


//** METHODS IN THE PROTOTYPE


//** CLASS INHERITANCE

