/*	JAVASCRIPT DOCUMENT
*
*
*	TEXT CODING - UTF-8
*
*	BEST VIEWED WITH A:
*		- tabulation  - 4,
*		- font family - monospace 10.
*/


/*   Module: workspace.
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
*		- libraries:
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

/*	Class:	workspace.
*	Input:
*			none.
*/
function jsWorkspace()
{
	//Public properties
	
	//* languages
	this.LANG__RU			= "ru";
	this.LANG__EN			= "en";
	
	//* language					[STRING]
	this.Lang				= this.LANG__RU;
	
	//* ID of Placeholder			[STRING || NULL]
	this.PlaceholderID		= null;
	
	//* ID of Placeholder Title		[STRING || NULL]
	this.PlaceholderTitleID	= null;
	
	//* ID of DataTable box		[STRING || NULL]
	//** <table>...</table>
	this.DataTableBoxID		= null;
	
	//* Path to localization file for DataTable	[STRING || NULL]
	this.DataTableLangFile	= null;
	
	
	//Private properties
	
	//* The result of done functionality	[BOOLEAN]
	var CheckFunc 			= false;
	
	//* DataTable		[OBJECT || NULL]
	var oDataTable			= null;
	
	//* jsMenu		[OBJECT || NULL]
	var oMenu				= null;
	
	//* jsPopupDialog	[OBJECT || NULL]
	var oPopupDialog		= null;
	
	//* jsPopupForm		[OBJECT || NULL]
	var oPopupForm			= null;
	
	
	//Methods
	
	//Public Method: Get Node by ID.
	//Input:
	//			NodeIDIn - Node ID.	[STRING]
	//Output:
	//			Node or NULL.	[OBJECT || NULL]
	//
	this.getNodeByID = function(NodeIDIn)
	{
		var Res = null;
		
		if(typeof NodeIDIn == "string")
		{
			if(!is_empty(NodeIDIn))
			{
				Res = $("#" + NodeIDIn);
			}
		}
		
		return (Res);
	};
	
	//Public Method: Hide node.
	//Input:
	//			NodeIn - node.	[OBJECT]
	//Output:
	//			none.
	//
	this.hide = function(NodeIn)
	{
		if(typeof NodeIn == "object")
		{
			if(NodeIn)
			{
				if(NodeIn.is(":visible")) NodeIn.hide();
			}
		}
	};
	
	//Public Method: Show node.
	//Input:
	//			NodeIn - node.	[OBJECT]
	//Output:
	//			none.
	//
	this.show = function(NodeIn)
	{
		if(typeof NodeIn == "object")
		{
			if(NodeIn)
			{
				if(!NodeIn.is(":visible")) NodeIn.show();
			}
		}
	};
	
	//Public Method: Hide Placeholder.
	//Input:
	//			none.
	//Output:
	//			none.
	//
	this.hidePlaceholder = function()
	{
		var Placeholder = this.getNodeByID(this.PlaceholderID);
		if(Placeholder) Placeholder.hide();
	};
	
	//Public Method: Show Placeholder.
	//Input:
	//			none.
	//Output:
	//			none.
	//
	this.showPlaceholder = function()
	{
		var Placeholder = this.getNodeByID(this.PlaceholderID);
		if(Placeholder) Placeholder.show();
	};
	
	//Public Method: Set Placeholder title.
	//Input:
	//			TitleIn - Placeholder title.	[STRING ||NULL]
	//Output:
	//			none.
	//
	this.setPlaceholderTitle = function(TitleIn)
	{
		var PlaceholderTitle = getNodeByID(this.PlaceholderTitleID);
		
		if(PlaceholderTitle)
		{
			var Title = ((typeof TitleIn == "string") ? TitleIn : "");
			PlaceholderTitle.text(Title);
		}
	};
	
	//Public Method: Clear DataTable.
	//Input:
	//			none.
	//Output:
	//			none.
	//
	this.clearDataTable = function()
	{
		if(oDataTable)
		{
			oDataTable.destroy();
			oDataTable.empty();
		}
	};
	
	//Public Method: Refresh DataTable.
	//Input:
	//			DataIn - data.	[OBJECT || NULL]
	//Output:
	//			none.
	//Note:
	//			DataIn["columns"] - list of column titles:
	//								= [ { data: "col1", title: "N", orderable: true },
	//									{ data: "col2", title: "Value", orderable: false },
	//									{ data: "col3", title: "Note", orderable: false }
	//								   ];
	//
	//			DataIn["data"] - list of data:
	//								= [ { "col1": 1, "col2": "1.1", "note": "---" },
	//									{ "col1": 2, "col2": "2.0", "note": "---" },
	//									...
	//								   ];
	//
	this.refreshDataTable = function(DataIn)
	{
		this.clearDataTable();
		
		if(typeof DataIn == "object")
		{
			if(DataIn)
			{
				if(typeof DataIn["columns"] != "undefined")
				{
					var DataTableBox = this.getNodeByID(this.DataTableBoxID);
					
					if(DataTableBox)
					{
						var DataTableOptions = DataIn;
						oDataTable = DataTableBox.DataTable(DataTableOptions);
					}
				}
			}
		}
	};
	
	//Public Method: Send request via AJAX.
	//Input:
	//			OptionsIn - AJAX-options.	[OBJECT]
	//Output:
	//			none.
	//
	this.ajax = function(OptionsIn)
	{
		if(typeof OptionsIn == "object")
		{
			if(OptionsIn) $.ajax(OptionsIn);
		}
	};
	
	//Public Method: Init. Menu.
	//Input:
	//			MenuIDIn - Menu ID;	[STRING]
	//			MenuOptionsIn - Options of Menu.	[OBJECT || NULL]
	//Output:
	//			none.
	//
	this.initMenu = function(MenuIDIn, MenuOptionsIn)
	{
		oMenu = null;
		
		if(CheckFunc && typeof MenuIDIn == "string")
		{
			if(!is_empty(MenuIDIn))
			{
				oMenu = new jsMenu(MenuIDIn);
				if(typeof MenuOptionsIn == "object") oMenu.Options = MenuOptionsIn;
				oMenu.initItems();
			}
		}
	};
	
	//Public Method: Init. PopupDialog.
	//Input:
	//			PopupDialogIDIn - PopupDialog ID.	[STRING]
	//Output:
	//			none.
	//
	this.initPopupDialog = function(PopupDialogIDIn)
	{
		oPopupDialog = null;
		
		if(CheckFunc && typeof PopupDialogIDIn == "string")
		{
			if(!is_empty(PopupDialogIDIn))
			{
				oPopupDialog = new jsPopupDialog(PopupDialogIDIn);
			}
		}
	};
	
	//Public Method: Init. PopupForm.
	//Input:
	//			PopupFormIDIn - PopupForm ID.	[STRING]
	//Output:
	//			none.
	//
	this.initPopupForm = function(PopupFormIDIn)
	{
		oPopupForm = null;
		
		if(CheckFunc && typeof PopupFormIDIn == "string")
		{
			if(!is_empty(PopupFormIDIn))
			{
				oPopupForm = new jsPopupForm(PopupFormIDIn);
			}
		}
	};
	
	
	//Constructor
	
	if(typeof is_empty == "function")
	{
		CheckFunc = true;
	}
}


//** METHODS IN THE PROTOTYPE


//** CLASS INHERITANCE

