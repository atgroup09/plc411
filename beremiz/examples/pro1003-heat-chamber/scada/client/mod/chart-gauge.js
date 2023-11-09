/*	JAVASCRIPT DOCUMENT
*
*
*	TEXT CODING - UTF-8
*
*	BEST VIEWED WITH A:
*		- tabulation  - 4,
*		- font family - monospace 10.
*/


/*   Library: gauge charts.
*
*    Copyright (C) 2015  ATgroup09 (atgroup09@gmail.com)
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

/*	Class:	demo-chart
*	Input:
*			DivID_in	- ID of DIV-node container.	[STRING]
*/
function ChartGauge(DivID_in)
{
	//Public properties
	
	//* chart data	[NUMBER]
	this.Data		= 0;
	
	//* chart options	[OBJECT]
	this.Options	= null;
	
	
	//Private properties
	
	//* chart	[OBJECT]
	var Chart		= null;
	
	//* chart DIV-container	[OBJECT]
	var ChartDIV	= null;
	
	
	//Methods
	
	//Method:	set tooltip title.
	//Input:
	//			title_in - title value.	[STRING || NULL]
	//Output:
	//
	this.setTooltipTitle = function(title_in)
		{
			if(typeof title_in == "string" && ChartDIV)
			{
				ChartDIV.attr("title", title_in);
			}
		};
	
	//Method:	refresh the chart.
	//Input:
	//			none.
	//Output:
	//
	this.reDraw = function()
		{
			if(Chart)
			{
				Chart.reInitialize([[this.Data]], this.Options);
				Chart.replot();
			}
		};
	
	//Method:	send request to responder-script by AJAX (JSON-format of returned data only!).
	//Input:
	//			Settings_in - list of AJAX-settings.	[OBJECT]
	//Output:
	//
	this.ajax = function(Settings_in)
		{
			if(typeof Settings_in == "object")
			{
				if(Settings_in) $.ajax(Settings_in);
			}
		};
		
	//Method:	init. chart.
	//Input:
	//			none.
	//Output:
	//
	this.init = function()
		{
			if(ChartDIV)
			{
				if(typeof this.Data == "number" && this.Options)
				{
					Chart = $.jqplot(DivID_in, [[this.Data]], this.Options);
				}
			}
		};
		
	
	//Constructor
	
	if(typeof DivID_in == "string")
	{
		ChartDIV = $("#" + DivID_in);
	}
	
	
	//Inheritance
}


//** METHODS IN THE PROTOTYPE


//** CLASS INHERITANCE

