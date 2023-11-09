/*	JAVASCRIPT DOCUMENT
*
*
*	TEXT CODING - UTF-8
*
*	BEST VIEWED WITH A:
*		- tabulation  - 4,
*		- font family - monospace 10.
*/


/*   Module: linear chart.
*
*    Copyright (C) 2016-2019  ATgroup09 (atgroup09@gmail.com)
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

//* data ID of chart tooltip	[NUMBER]
var G_CHART_LINEAR_TOOLTIP_DATA_ID		= null;

//* series ID of chart tooltip	[NUMBER]
var G_CHART_LINEAR_TOOLTIP_SERIES_ID	= null;


//** FUNCTIONS

/*	Function:	get string of date values from msec.
*	   Input:
*				msec_in - time in msec.	[NUMBER]
*	  Output:
*				string of date values or NULL.	[STRING || NULL]
*       Note:
*/
function ChartLinearGetDateStrFromMsec(msec_in)
{
	if(typeof msec_in == "number")
	{
		var _date    = new Date(msec_in);
		var _year    = _date.getFullYear();
		var _month   = ((_date.getMonth() < 10) ? "0" + (_date.getMonth()+1) : (_date.getMonth()+1));
		var _day     = ((_date.getDate() < 10) ? "0" + _date.getDate() : _date.getDate());
		
		return (_year + "-" + _month + "-" + _day);
	}
	
	return null;
}


/*	Function:	get string of time values from msec.
*	   Input:
*				msec_in - time in msec.	[NUMBER]
*	  Output:
*				string of time values or NULL.	[STRING || NULL]
*       Note:
*/
function ChartLinearGetTimeStrFromMsec(msec_in)
{
	if(typeof msec_in == "number")
	{
		var _date    = new Date(msec_in);
		var _hours   = ((_date.getHours() < 10) ? "0" + _date.getHours() : _date.getHours());
		var _minutes = ((_date.getMinutes() < 10) ? "0" + _date.getMinutes() : _date.getMinutes());
		var _seconds = ((_date.getSeconds() < 10) ? "0" + _date.getSeconds() : _date.getSeconds());
		
		return (_hours + ":" + _minutes + ":" + _seconds);
	}
	
	return null;
}


/*	Function:	get time stamp from date, hours and minutes.
*	   Input:
*				date_in		- Date-object (null for current date);	[OBJECT]
*				hours_in	- hours;	[NUMBER]
*				minutes_in	- minutes.	[NUMBER]
*	  Output:
*				time stamp or 0.	[NUMBER]
*       Note:
*/
function ChartLinearGetTimeStamp(date_in, hours_in, minutes_in)
{
	var _date = null;
	
	if(typeof date_in == "object")
	{
		if(date_in) _date = date_in;
	}
	
	if(!_date) _date = new Date();
	
	if(typeof hours_in == "number")
	{
		if(hours_in >= 0)
		{
			if(hours_in < 24) _date.setHours(hours_in);
		}
	}
	
	if(typeof minutes_in == "number")
	{
		if(minutes_in >= 0)
		{
			if(minutes_in < 60) _date.setMinutes(minutes_in);
		}
	}
	
	_date.setSeconds(0);
	
	return _date.getTime();
}


/*	Function:	check start and end dates.
*	   Input:
*				msecStart_in - start time in msec;	[NUMBER]
*				msecEnd_in   - end time in msec.	[NUMBER]
*	  Output:
*				true if start date == end date, otherwise - false.	[BOOLEAN]
*       Note:
*/
function ChartLinearIsOneDate(msecStart_in, msecEnd_in)
{
	if(typeof msecStart_in == "number" && typeof msecEnd_in == "number" && typeof ChartLinearGetTimeStamp == "function")
	{
		var _dateStart	= new Date(msecStart_in);
		var _dateEnd	= new Date(msecEnd_in);
		var _tsStart	= ChartLinearGetTimeStamp(_dateStart, 0, 0);
		var _tsEnd		= ChartLinearGetTimeStamp(_dateEnd, 0, 0);
		
		//var a = ChartLinearGetDateStrFromMsec(_tsStart);
		//var b = ChartLinearGetDateStrFromMsec(_tsEnd);
		//alert(a + " :: " + b);
		
		return ((_tsStart == _tsEnd) ? true : false);
	}
	
	return false;
}


/*	Function:	show chart tooltip.
*	   Input:
*				x_in			- X-coord.;	[NUMBER]
*				y_in			- Y-coord.;	[NUMBER]
*				color_in		- color;		[STRING || NULL]
*				content_in	- tooltip content.	[STRING]
*	  Output:
*				none.
*       Note:
*/
function ChartLinearTooltipShow(x_in, y_in, color_in, content_in)
{
	if(typeof x_in == "number" && typeof y_in == "number" && typeof content_in == "string")
	{
		$('<div id="chart_demo_tooltip">' + content_in + '</div>').css({
			position: 'absolute',
			display: 'none',
			top: y_in + 5,
			left: x_in + 20,
			border: '2px solid ' + ((typeof color_in == "string") ? color_in : ""),
			padding: '2px',
			size: '10',   
			'background-color': '#ffffff',
			opacity: 0.80,
			'z-index': 1000
		 }).appendTo("body").fadeIn(200);
	}
}


/*	Function:	event-handler "TooltipHover".
*	   Input:
*				event_in	- Event-object;	[OBJECT]
*				pos_in		- position;	[ARRAY]
*				item_in		- item.	[OBJECT]
*	  Output:
*				none.
*       Note:
*/
function ChartLinearTooltipHovered(event_in, pos_in, item_in)
{
	if(typeof G_CHART_LINEAR_TOOLTIP_DATA_ID != "undefined" && typeof G_CHART_LINEAR_TOOLTIP_SERIES_ID != "undefined" && typeof ChartLinearTooltipShow == "function")
	{
		if(item_in)
		{
			if((G_CHART_LINEAR_TOOLTIP_SERIES_ID != item_in.seriesIndex) || (G_CHART_LINEAR_TOOLTIP_DATA_ID != item_in.dataIndex))
			{
				G_CHART_LINEAR_TOOLTIP_SERIES_ID	= item_in.seriesIndex;
				G_CHART_LINEAR_TOOLTIP_DATA_ID		= item_in.dataIndex;
				
				$("#chart_demo_tooltip").remove();
				
				var dateStr = ((typeof ChartLinearGetTimeStrFromMsec == "function") ? ChartLinearGetTimeStrFromMsec(item_in.datapoint[0]) : "");
				
				ChartLinearTooltipShow(item_in.pageX, item_in.pageY, item_in.series.color, dateStr + "<br/>" + "<strong>" + item_in.datapoint[1] + "</strong> (" + item_in.series.label + ")");
			}
		}
		else
		{
			$("#chart_demo_tooltip").remove();
			
			G_CHART_LINEAR_TOOLTIP_SERIES_ID	= null;
			G_CHART_LINEAR_TOOLTIP_DATA_ID		= null;
		}
	}
}


/*	Function:	formatter for X-axis tick.
*	   Input:
*				v_in	- axis value;	[STRING]
*				axis_in	- axis.	[OBJECT || NUMBER]
*	  Output:
*				X-axis tick value.	[STRING]
*       Note:
*/
function ChartLinearXAxisTickFormatter(v_in, axis_in)
{
	var res = "";
	
	if(typeof ChartLinearGetTimeStrFromMsec == "function" && (typeof v_in == "string" || typeof v_in == "number"))
	{
		var v = ((typeof v_in == "number") ? v_in : v_in-0);
		
		res = ChartLinearGetTimeStrFromMsec(v);
	}
	
    return res;
}


/*	Function:	formatter for Y-axis tick.
*	   Input:
*				v_in	- axis value;	[STRING]
*				axis_in	- axis.	[OBJECT || NUMBER]
*	  Output:
*				Y-axis tick value.	[STRING]
*       Note:
*/
function ChartLinearYAxisTickFormatter(v_in, axis_in)
{
	var res = "";
	
	if(typeof v_in == "string" || typeof v_in == "number")
	{
		res = ((typeof v_in == "number") ? "" + v_in : v_in);
	}
	
    return res;
}


//** CLASSES

/*	Class:	linear chart.
*	Input:
*			DivID_in - ID of DIV-node container.	[STRING]
*/
function ChartLinear(DivID_in)
{
	//Public properties
	
	//* chart data	[ARRAY]
	this.Data		= [];
	
	//* chart options	[OBJECT]
	this.Options	= null;
	
	//* auto scale grid [BOOLEAN]
	this.AutoScaleGrid = false;
	
	//* clearance of scale grid [NUMBER]
	//** +/- from Min/Max
	this.ScaleGridClearance = 10;
	
	
	//Private properties
	
	//* chart	[OBJECT]
	var Chart		= null;
	
	//* chart DIV-container	[OBJECT]
	var ChartDIV	= null;
	
	
	//Methods
	
	//Method:	get string of time values from msec.
	//Input:
	//			msec_in - time in msec.	[NUMBER]
	//Output:
	//			string of time values or NULL.	[STRING || NULL]
	//
	this.getTimeStrFromMsec = function(msec_in)
		{
			return ((typeof ChartDemoGetTimeStrFromMsec == "function") ? ChartDemoGetTimeStrFromMsec(msec_in) : null);
		};
	
	//Method:	get time stamp from date, hours and minutes.
	//Input:
	//			Date_in		- Date-object (null for current date);	[OBJECT]
	//			Hours_in	- hours;	[NUMBER]
	//			Minutes_in	- minutes.	[NUMBER]	
	//Output:
	//			time stamp or 0.	[NUMBER]
	//
	this.getTimeStamp = function(Date_in, Hours_in, Minutes_in)
		{
			return ((typeof ChartDemoGetTimeStamp == "function") ? ChartDemoGetTimeStamp(Date_in, Hours_in, Minutes_in) : null);
		};
	
	//Method:	get data by ID.
	//Input:
	//			DataID_in - ID of data array (0 ...; -1 for last ID).	[NUMBER]
	//Output:
	//			data array or NULL.	[ARRAY || NULL]
	//
	this.getDataByID = function(DataID_in)
		{
			if(typeof DataID_in == "number")
			{
				if(DataID_in >= 0 || DataID_in == -1)
				{
					var DataID = ((DataID_in == -1) ? (this.Data.length-1) : DataID_in);
					if(DataID < 0) DataID = 0;
					
					if(DataID < this.Data.length)
					{
						if(typeof this.Data[DataID]["data"] != "undefined")
						{
							return this.Data[DataID]["data"];
						}
					}
				}
			}
			
			return null;
		};
	
	//Method:	get data item by ID.
	//Input:
	//			DataID_in - ID of data array (0 ...; -1 for last ID);	[NUMBER]
	//			ItemID_in - ID of data item (0 ...; -1 for last ID).	[NUMBER]
	//Output:
	//			data item [x, y] or NULL.	[ARRAY || NULL]
	//
	this.getDataItemByID = function(DataID_in, ItemID_in)
		{
			var DataByID = this.getDataByID(DataID_in);
			
			if(DataByID && typeof ItemID_in == "number")
			{
				if(ItemID_in >= 0 || ItemID_in == -1)
				{
					var ItemID = ((ItemID_in == -1) ? (DataByID.length-1) : ItemID_in);
					if(ItemID < 0) ItemID = 0;
					
					if(ItemID < DataByID.length)
					{
						return DataByID[ItemID];
					}
				}
			}
			
			return null;
		};
	
	//Method:	get scale (minimum and maximum) of data.
	//Input:
	//			None.
	//Output:
	//			{ MinX: MinValueX, MaxX: MaxValueX, MinY: MinValueY, MaxY: MaxValueY }	[OBJECT]
	//
	this.getDataScale = function()
		{
			var Res = { MinX:0, MaxX:0, MinY:0, MaxY:0 };
			
			if(typeof this.Data == "object")
			{
				if(this.Data)
				{
					var Key = "";
					var Inited = false;
					var i = 0, j = 0, k = 0;
					
					//charts
					for(i=0; i<this.Data.length; i++)
					{
						if(typeof this.Data[i]["data"] == "object")
						{
							if(this.Data[i]["data"])
							{
								//chart values
								for(j=0; j<this.Data[i]["data"].length; j++)
								{
									if(typeof this.Data[i]["data"][j] == "object")
									{
										if(this.Data[i]["data"][j])
										{
											//[0] is X (Stamp), [1] is Y (value)
											if(this.Data[i]["data"][j].length >= 2)
											{
												for(k=0; k<2; k++)
												{
													if(typeof this.Data[i]["data"][j][k] == "number" && typeof this.Data[i]["data"][j][k] == "number")
													{
														Key = ((!k) ? "X" : "Y");
														
														if(Inited)
														{
															if(this.Data[i]["data"][j][k] < Res["Min"+Key]) Res["Min"+Key] = this.Data[i]["data"][j][k];
															if(this.Data[i]["data"][j][k] > Res["Max"+Key]) Res["Max"+Key] = this.Data[i]["data"][j][k];
														}
														else
														{
															Res["Min"+Key] = this.Data[i]["data"][j][k];
														}
													}
												}
												Inited = true;
											}
										}
									}
								}
							}
						}
					}
				}
			}
			
			return (Res);
		};
		
	//Method:	clear data.
	//Input:
	//			none.
	//Output:
	//
	this.clearData = function()
		{
			this.Data = [];
		};
	
	//Method:	set horizontal label.
	//Input:
	//			ValueY_in - label value (Y-coord).	[NUMBER || NULL]
	//Output:
	//
	this.setHorizontalLabel = function(ValueY_in)
		{
			if(Chart && ChartDIV)
			{
				var LabelNode = $(".chl_hlabel");
				if(LabelNode) LabelNoderemove();
				
				if(typeof ValueY_in == "number")
				{
					var PointOffset = Chart.pointOffset({ x: null, y: ValueY_in });
					ChartDIV.append("<div class='chl_hlabel' style='position: absolute; left:" + 70 + "px; top:" + (PointOffset.top - 14) + "px; color: #ffffff; font-size: smaller'>" + ValueY_in + "</div>");
				}
			}
		};
	
	//Method:	get chart options.
	//Input:
	//			none.
	//Output:
	//			list of chart options or NULL.	[OBJECT || NULL]
	//
	this.getOptions = function()
		{
			return ((Chart) ? Chart.getOptions() : null);
		};
	
	//Method:	get chart axes.
	//Input:
	//			none.
	//Output:
	//			list of chart axes or NULL.	[OBJECT || NULL]
	//
	this.getAxes = function()
		{
			return ((Chart) ? Chart.getAxes() : null);
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
				if(this.AutoScaleGrid)
				{
					var Res = this.getDataScale();
					var Options = this.getAxes();
					var Clearance = ((typeof this.ScaleGridClearance == "number") ? this.ScaleGridClearance : 0);
					Options["yaxis"]["options"]["min"] = Res["MinY"] - Clearance;
					Options["yaxis"]["options"]["max"] = Res["MaxY"] + Clearance;
					//console.log(Res);
				}
				
				Chart.setData(this.Data);
				Chart.setupGrid();
				Chart.draw();
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
				if(this.Data && this.Options)
				{
					Chart = $.plot("#" + DivID_in, this.Data, this.Options);
				}
			}
		};
	
	
	//Constructor
		
	if(typeof DivID_in == "string")
	{
		ChartDIV = $("#" + DivID_in);
		
		if(ChartDIV)
		{
			ChartDIV.UseTooltip();
			//this.init();
		}
	}
	
	
	//Inheritance
}


//** METHODS IN THE PROTOTYPE

if(typeof ChartLinearTooltipHovered == "function")
{
	$.fn.UseTooltip = function() {
		
		$(this).bind("plothover", ChartLinearTooltipHovered);
	};
}


//** CLASS INHERITANCE

