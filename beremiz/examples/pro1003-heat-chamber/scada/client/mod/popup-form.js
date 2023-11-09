/*	JAVASCRIPT DOCUMENT
*
*
*	TEXT CODING - UTF-8
*
*	BEST VIEWED WITH A:
*		- tabulation  - 4,
*		- font family - monospace 10.
*/


/*   Module: popup form.
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
*		- form.js:
*			~ jsForm().
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

/*	Class:	popup form.
*	Input:
*			IDIn - ID of popup form.
*	Note:
*
*			HTML-structure of PopupDialog
*
*			<!-- popup form -->
*			<div data-role="popup" id="PopupForm" data-overlay-theme="a" data-theme="a" data-dismissible="true" style="max-width:640px;">
*				<div data-role="header" data-theme="b">
*					<h1>---</h1>
*				</div>
*				<div role="main" class="ui-content">
*					<div class="ui-space-separator"></div>
*					<form id="DataForm"></form>
*					<div class="ui-space-separator"></div>
*					<button type="button" class="ui-btn ui-corner-all ui-shadow ui-btn-b ui-btn-icon-left ui-icon-check">Сохранить</button>
*				</div>
*			</div>
*/
function jsPopupForm(IDIn)
{
	//Public properties
	
	
	//Private properties
	
	//* ID		[STRING]
	var ID 			= null;
	
	//* Nodes	[OBJECT || NULL]
	var MainNode	= null;
	var TitleNode	= null;
	var FormNode	= null;
	
	//* The result of done functionality	[BOOLEAN]
	var CheckFunc	= false;
	
	//* Dialog structure	[STRING]
	var TAG__TITLE	= "h1";
	var TAG__FORM	= "form";
	
	
	//Methods
	
	//Public Method: Show form.
	//Input:
	//			none.
	//Output:
	//			none.
	//Note:
	//
	this.show = function()
	{
		if(CheckFunc && MainNode)
		{
			MainNode.popup("open");
		}
	};
	
	//Public Method: Set title.
	//Input:
	//			TitleIn	- dialog title.	[STRING || NULL]
	//Output:
	//			none.
	//Note:
	//
	this.setTitle = function(TitleIn)
	{
		if(CheckFunc && TitleNode)
		{
			var Buff = ((typeof TitleIn == "string") ? TitleIn : "");
			TitleNode.text(Buff);
		}
	};
	
	//Public Method: Get jForm.
	//Input:
	//			none.
	//Output:
	//			get object of class jForm.	[OBJECT || NULL]
	//
	this.get_jForm = function()
	{
		var Res = null;
		
		if(CheckFunc && FormNode)
		{
			Res = new jsForm(null);
			Res.initNode(FormNode);
		}
		
		return (Res);
	};
	
	//Public Method: Init.
	//Input:
	//			IDIn - dialog ID.	[STRING]
	//Output:
	//			none.
	//
	this.init = function(IDIn)
	{
		ID			= null;
		MainNode	= null;
		TitleNode	= null;
		FormNode	= null;
		
		if(CheckFunc && typeof IDIn == "string")
		{
			ID = IDIn;
			MainNode = $("#" + IDIn);
			
			if(MainNode)
			{
				TitleNode = MainNode.find(TAG__TITLE);
				FormNode  = MainNode.find(TAG__FORM);
			}
		}
	};
	
	
	//Constructor
	
	if(typeof jsForm == "function")
	{
		CheckFunc = true;
	}
	
	this.init(IDIn);
}


//** METHODS IN THE PROTOTYPE


//** CLASS INHERITANCE

