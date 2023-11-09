/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  pro1003
*   webSCADA client / Chart controller
*   AT09 (atgroup09@gmail.com), 2023
*
*   The JavaScript code in this page is free software: you can
*   redistribute it and/or modify it under the terms of the GNU
*   General Public License (GNU GPL) as published by the Free Software
*   Foundation, either version 3 of the License, or (at your option)
*   any later version.  The code is distributed WITHOUT ANY WARRANTY;
*   without even the implied warranty of MERCHANTABILITY or FITNESS
*   FOR A PARTICULAR PURPOSE.  See the GNU GPL for more details.
*
*   As additional permission under GNU GPL version 3 section 7, you
*   may distribute non-source (e.g., minimized or compacted) forms of
*   that code without the copy of the GNU GPL normally required by
*   section 4, provided you include this license notice and a URL
*   through which recipients can access the Corresponding Source.
*/


//** GLOBAL VARIABLES


//** CLASSES

/*	Class:	linear chart.
*	Input:
*			DivID_in - ID of container.	[STRING]
*/
function MainChartLinear(DivID_in)
{
	//Public properties
	
	//* flow rate limites	[FLOAT]
	this.ValueMin		= 0.0;
	this.ValueMax		= 60.0;
	
	//* time profile (msec)	[INT]
	var mProfile		= 1000;
	
	
	//Private properties
	
	
	//Methods
	
	//Method:	refresh X-axis (datetime) label.
	//Input:
	//			none.
	//Output:
	//			none.
	//
	this.refreshXAxisLabel = function()
		{
			var Axes = this.getAxes();
			
			if(Axes && typeof ChartLinearGetDateStrFromMsec == "function" && typeof ChartLinearIsOneDate == "function")
			{
				var DateStr			= null;
				var DataItemStart	= this.getDataItemByID(0, 0);
				var DataItemEnd		= this.getDataItemByID(0, -1);
				
				if(DataItemStart && DataItemEnd)
				{
					DateStr = ChartLinearGetDateStrFromMsec(DataItemStart[0]);
					
					if(DateStr && !ChartLinearIsOneDate(DataItemStart[0], DataItemEnd[0]))
					{
						var buff = ChartLinearGetDateStrFromMsec(DataItemEnd[0]);
						if(buff) DateStr += " - " + buff;
					}
					
					Axes["xaxis"]["options"]["axisLabel"] = ((DateStr) ? DateStr : "---");
					this.reDraw();
				}
			}
		};
	
	
	//Constructor
	
	if(typeof MainChartLinear.superclass == "object")
	{
		if(typeof MainChartLinear.superclass.constructor == "function")
		{
			MainChartLinear.superclass.constructor.call(this, DivID_in);
		}
	}
	
	this.Data		= [ ];
	
	this.Options	= {			series: { lines: { show: false, fill: true, lineWidth: 1.2 } },
								  grid: { hoverable: true,
										  clickable: false, 
										  mouseActiveRadius: 30,
										  backgroundColor: { colors: ["#d1d1d1", "#7a7a7a"] }
										},
							axisLabels: { show: true },
								 xaxis: { axisLabel: "---",
										  axisLabelUseCanvas: true,
									      axisLabelFontSizePixels: 12,
									      axisLabelFontFamily: 'Verdana, Arial',
									      axisLabelPadding: 20,
										  show: false,
									      mode: "time",
									      tickSize: [1, "second"],
									      tickFormatter: ((typeof ChartLinearXAxisTickFormatter == "function") ? ChartLinearXAxisTickFormatter : null)
										},
								 yaxis: { axisLabel: "Значение канала",
										  axisLabelUseCanvas: true,
										  axisLabelFontSizePixels: 12,
										  axisLabelFontFamily: 'Verdana, Arial',
										  axisLabelPadding: 6,
									      show: true,
										  min: this.ValueMin,
										  max: this.ValueMax,
										  tickFormatter: ((typeof ChartLinearYAxisTickFormatter == "function") ? ChartLinearYAxisTickFormatter : null)
										},
								legend: { container:$("#LinearChartLegend") }
					  };
}


//** METHODS IN THE PROTOTYPE


//** CLASS INHERITANCE

if(typeof extend_class == "function")
{
	if(typeof ChartLinear == "function")
	{
		extend_class(MainChartLinear, ChartLinear);
	}
}

