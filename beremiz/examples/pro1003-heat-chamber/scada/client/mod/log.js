/*	JAVASCRIPT DOCUMENT
*
*
*	TEXT CODING - UTF-8
*
*	BEST VIEWED WITH A:
*		- tabulation  - 4,
*		- font family - monospace 10.
*/


/*   Module: log.
*
*    Copyright (C) 2018  ATgroup09 (atgroup09@gmail.com)
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


//** GLOBAL VARIABLES


//** FUNCTIONS


//** CLASSES

/*
@brief  Class: Log.
@param  TableIdIn - ID of table.	[STRING]
@return None.
*/
function jsLog(TableIdIn)
{
	//Public properties
	
	/*
	@brief Public option: The maximum limit of rows.	[NUMBER]
	*/
	this.LimRows = 30;
	
	/*
	@brief Public option: Allow to rotate of rows by maximum limit.	[BOOLEAN]
	*/
	this.AllowRotate = true;
	
	/*
	@brief Public option: Allow to use of current DateTime stamp.	[BOOLEAN]
	*/
	this.AllowCurrentStamp = true;
	
	/*
	@brief Public option: ID of case-node.	[STRING]
	*/
	this.CaseID = null;
	
	
	//Private properties
	
	/*
	@brief Private option: ID of table.	[STRING]
	*/
	var TableId = null;
	
	/*
	@brief Private option: Nodes.	[OBJECT]
	*/
	var TableNode = null;
	var TableBody = null;
	
	/*
	@brief Private option: Check result.	[BOOLEAN]
	*/
	var CheckFunc = false;
	
	
	//Methods
	
	/*
	@brief  Public Method: Rotate rows.
	@param  None.
	@return None.
	*/
	this.rotate = function()
	{
		if(CheckFunc && TableBody && this.AllowRotate && typeof this.LimRows == "number")
		{
			while(TableBody.find("tr").length > this.LimRows)
			{
				TableBody.find("tr:last").remove();
			}
		}
	};
	
	/*
	@brief  Public Method: Add message.
	@param  StampIn   - DateTime stamp;		 [STRING || NULL]
	@param  TargetIn  - the name of target;	 [STRING || NULL]
	@param  MessageIn - message;			 [STRING || NUMBER || NULL]
	@param  ColorIn   - row background color: [STRING || NULL]
						= "none" (by default)
						= "red"
						= "yellow"
						= "green"
						= "blue"
	@return None.
	*/
	this.add = function(StampIn, TargetIn, MessageIn, ColorIn)
	{
		if(CheckFunc && TableBody)
		{
			var Stamp = ((typeof StampIn == "string") ? StampIn : null);
			if(!Stamp && this.AllowCurrentStamp) Stamp = (new Date()).format("isoDateTimeNorm");
			
			var Color  = null;
			var Colors = { red:"#ff0000;color:#ffffff;text-shadow:none;", yellow:"#ffff00;", green:"#90ee90", blue:"#0000ff;color:#ffffff;text-shadow:none;" };
			
			if(typeof ColorIn == "string")
			{
				if(typeof Colors[ColorIn] == "string") Color = Colors[ColorIn];
			}
			
			var Tr = $(((Color) ? '<tr style="background-color:' + Color + '">' : '<tr>')
					 +		'<td class="ui-log-stamp">' + Stamp + '</td>'
					 +		'<td class="ui-log-target">' + ((typeof TargetIn == "string") ? TargetIn : "---") + '</td>'
					 +		'<td class="ui-log-text">' + ((typeof MessageIn == "string" || typeof MessageIn == "number") ? MessageIn : "---") + '</td>'
					 + '</tr>'
					   );
			
			TableBody.prepend(Tr);
			this.rotate();
		}
	};
	
	/*
	@brief  Public Method: Toggle visibility of Log-case.
	@param  StateIn  - visibility state:	         [STRING || NUMBER || BOOLEAN || OBJECT || NULL]
					 =   0 || false || NULL - hide,
					 = > 0 || true || !NULL - show
	@return None.
	*/
	this.toggleCase = function(StateIn)
	{
		if(CheckFunc && typeof this.CaseID == "string")
		{
			var CaseNode = $(("#" + this.CaseID));
			
			if(CaseNode)
			{
				var fl = false;
			
				if(typeof StateIn == "number")
				{
					fl = ((StateIn > 0) ? true : false);
				}
				else if(typeof StateIn == "string")
				{
					fl = ((StateIn.length > 0) ? true : false);
				}
				else if(typeof StateIn == "boolean")
				{
					fl = StateIn;
				}
				else if(typeof StateIn == "object")
				{
					if(StateIn) fl = true;
				}
				
				CaseNode.toggle(fl);
			}
		}
	};
	
	/*
	@brief  Public Method: Toggle visibility of Log-case.
	@param  None.
	@return None.
	*/
	this.isCaseVisible = function()
	{
		if(CheckFunc && typeof this.CaseID == "string")
		{
			var CaseNode = $(("#" + this.CaseID));
			
			if(CaseNode)
			{
				return (CaseNode.is(':visible'));
			}
		}
		
		return (false);
	};
	
	/*
	@brief  Public Method: Init.
	@param  TableIdIn - ID of table.	[STRING]
	@return None.
	*/
	this.init = function(TableIdIn)
	{
		TableId   = null;
		TableNode = null;
		
		if(CheckFunc && typeof TableIdIn == "string")
		{
			TableId   = TableIdIn;
			TableNode = $("#" + TableId);
			
			if(TableNode)
			{
				TableBody = TableNode.find("tbody");
			}
		}
	};
	
	
	//Constructor
	
	CheckFunc = true;
	this.init(TableIdIn);
}


//** METHODS IN THE PROTOTYPE


//** CLASS INHERITANCE

