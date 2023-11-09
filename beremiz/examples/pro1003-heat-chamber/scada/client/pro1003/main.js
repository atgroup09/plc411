/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  pro1003
*   webSCADA client / UI controller
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

/** Dependencies:
 *    + mod/hmi-v3.js.js
 *    + mod/ui-hmi-v3.js
 *    + mod/ui-hmi-v3.css
 */

//Chart context
var G_CHART            = null;
var G_CHART_DATA       = null;
var G_CHART_DATA_ASSOC = null;

//Chart current values
var G_CHART_SP         = 0.0;
var G_CHART_SP_D       = 0.0;
var G_CHART_SP_LO      = 0.0;
var G_CHART_SP_HI      = 0.0;

//WebHMI-server configuration
var G_WS_SERVER_URI 	= "ws://127.0.0.1:8100";
var G_WS_SERVER_ID  	= "pro1003";
var G_WS_SERVER_NET_ID 	= 1;
var G_WS_SERVER_DEV_ID 	= 1;


/*
@brief  Function: Handler for event Plot.hover
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onPlotHover(event, pos, item)
{
	if(item)
	{
		var x = item.datapoint[0].toFixed(2);
		var y = item.datapoint[1].toFixed(2);
		
		$("#PlotTooltip").html("x:" + x + " y:" + y)
						 .css({top: item.pageY+5, left: item.pageX+5})
						 .fadeIn(200);
	}
	else
	{
		$("#PlotTooltip").stop().hide();
	}
}

/*
@brief  Function: Handler for event Plot.hoverclean
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onPlotHoverClean(event, pos, item)
{
	$("#PlotTooltip").hide();
}


/*
@brief  Handler for event FormViewScheme.onClicked
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onFormViewSchemeClicked(event)
{
	var Res = G_FORM_SET.getResultset();

	if(Res)
	{
		var Status = ((typeof Res["scheme_use"] == "number") ? true : false);
		var Node   = $("#RootCase");
		Node.toggle(Status);
	}
}


/*
@brief  Handler for event FormViewChart.onClicked
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onFormViewChartClicked(event)
{
	var Res = G_FORM_SET.getResultset();

	if(Res)
	{
		var Status = ((typeof Res["chart_use"] == "number") ? true : false);
		var Node   = $("#ChartCase");
		Node.toggle(Status);
	}
}


/*
@brief  Handler for event FormSetApply.onClicked
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onFormSetApplyClicked(event)
{
	if(hasWsServerOpened())
	{
		var Res = G_FORM_SET.getResultset();
		
		if(Res)
		{
			var Msg = {SrvID:G_WS_SERVER_ID, NetID:G_WS_SERVER_NET_ID, DevID:G_WS_SERVER_DEV_ID, Data:Res, Stamp:(new Date()).get_current_time_stamp()};
			//convert message object into JSON-string and send it to WsServer
			sendToWsServer(JSON.stringify(Msg));
		}
	}
}


/*
@brief  Add Value into ChartData.
@param  DataKeyIn - key to Data-list [STRING]
@param  ValueIn - value [NUMBER]
@return None
*/
function addChartDataValue(DataKeyIn, ValueIn)
{
	if(typeof G_CHART_DATA_ASSOC[DataKeyIn] == "object")
	{
		var ChartID = G_CHART_DATA_ASSOC[DataKeyIn]["ChartID"];
		
		if(G_CHART_DATA["charts"][ChartID].data.length == 30)
		{
			G_CHART_DATA["charts"][ChartID].data.shift();
		}
		
		G_CHART_DATA["charts"][ChartID].data.push([G_WS_SERVER_STAMP*1000, ValueIn]);
	}
}

/*
@brief  Set Data into LineChart.
@param  DataIn - array of data [OBJECT]
@return None
*/
function setLinearChart(DataIn)
{
	G_CHART["Data"] = [];
	G_CHART["Data"] = G_CHART_DATA["charts"];
	G_CHART.reDraw();
	G_CHART.refreshXAxisLabel();
}

/*
@brief  Function: Handler for event execFunc - out data into chart.
@param  OptionsIn  - array of options [OBJECT]
@param  DataIn - array of data [OBJECT]
@param  DataKeyIn - key to Data [STRING]
@param  ValueIn - modified value [ANY]
@param  BeforeValueIn - modified value defore fromArray [ANY]
@return true.	[BOOLEAN]
*/
function onFuncWsChart(OptionsIn, DataIn, DataKeyIn, ValueIn, BeforeValueIn)
{
	if(DataKeyIn == "SP")
	{
		G_CHART_SP    = ValueIn;
		G_CHART_SP_LO = (G_CHART_SP-G_CHART_SP_D);
		G_CHART_SP_HI = (G_CHART_SP+G_CHART_SP_D);
	}
	else if(DataKeyIn == "D")
	{
		G_CHART_SP_D  = ValueIn;
		G_CHART_SP_LO = (G_CHART_SP-G_CHART_SP_D);
		G_CHART_SP_HI = (G_CHART_SP+G_CHART_SP_D);
	}
	else if(DataKeyIn == "TT001")
	{
		addChartDataValue("SP", G_CHART_SP);
		addChartDataValue("SP_Lo", G_CHART_SP_LO);
		addChartDataValue("SP_Hi", G_CHART_SP_HI);
		addChartDataValue(DataKeyIn, ValueIn);
		setLinearChart();
	}
}

/*
@brief  Inititialize UI.
@param  None.
@return None.
*/
function Main_InitUI()
{
	if(typeof initUI == "function")
	{
        /* INIT WS-HMI
         */
		
		//Settings of tags (link data with WebHMI-content)
		//* _txt - Text
		//* _bil - BitLamp
		//* _plo - Plot/Chart
		var WsOpts = { ID_txt: { DataKey:"SET_ID", setNode:"ID_txt", NodeAlg:"Text", byRiseEdge:true, execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["SET_ID"], LogColor:null },
					   SP_txt: { DataKey:"SP", setNode:"SP_txt", NodeAlg:"Text", byRiseEdge:true, execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["SP"], LogColor:null },
					   SP_plo: { DataKey:"SP", byRiseEdge:true, execFunc:onFuncWsChart },
					    D_txt: { DataKey:"D", setNode:"D_txt", NodeAlg:"Text", byRiseEdge:true, execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["D"], LogColor:null },
						D_plo: { DataKey:"D", byRiseEdge:true, execFunc:onFuncWsChart },
					  DHI_txt: { DataKey:"DHI", setNode:"DHI_txt", NodeAlg:"Text", byRiseEdge:true, execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["DHI"], LogColor:null },
					  THI_txt: { DataKey:"THI", setNode:"THI_txt", NodeAlg:"Text", byRiseEdge:true, execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["THI"], LogColor:null },
					  DLO_txt: { DataKey:"DLO", setNode:"DLO_txt", NodeAlg:"Text", byRiseEdge:true, execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["DLO"], LogColor:null },
					  TLO_txt: { DataKey:"TLO", setNode:"TLO_txt", NodeAlg:"Text", byRiseEdge:true, execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["TLO"], LogColor:null },
					   TB_txt: { DataKey:"TB", setNode:"TB_txt", NodeAlg:"Text", byRiseEdge:true, execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["TB"], LogColor:null },
				    TT001_txt: { DataKey:"TT001", setNode:"TT001_txt", NodeAlg:"Text", div:10, execFunc:onFuncWsChart },
					HS001_txt: { DataKey:"STATES", setNode:"HS001_txt", NodeAlg:"Text", byRiseEdge:true, getBit:0, fromArray:G_RES[G_LANG]["HS001_List"], execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["HS001"], LogColor:null },
					HS001_bil: { DataKey:"STATES", setNode:"HS001_bil", NodeAlg:"BitLamp", byRiseEdge:true, getBit:0 },
					HS002_txt: { DataKey:"STATES", setNode:"HS002_txt", NodeAlg:"Text", byRiseEdge:true, getBit:1, fromArray:G_RES[G_LANG]["HS002_List"], execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["HS002"], LogColor:null },
					HS002_bil: { DataKey:"STATES", setNode:"HS002_bil", NodeAlg:"BitLamp", byRiseEdge:true, getBit:1 },
					 H001_bil: { DataKey:"STATES", setNode:"H001_bil", NodeAlg:"BitLamp", byRiseEdge:true, getBit:2 },
					 H001_log: { DataKey:"STATES", byRiseEdge:true, getBit:2, fromArray:G_RES[G_LANG]["OffOn_List"], execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["H001"], LogColor:null },
					 C001_bil: { DataKey:"STATES", setNode:"C001_bil", NodeAlg:"BitLamp", byRiseEdge:true, getBit:3 },
					 C001_log: { DataKey:"STATES", byRiseEdge:true, getBit:3, fromArray:G_RES[G_LANG]["OffOn_List"], execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["C001"], LogColor:null },
					  LED_bil: { DataKey:"STATES", setNode:"LED_bil", NodeAlg:"BitLamp", byRiseEdge:true, getBit:4 },
					ALARM_bil: { DataKey:"STATES", setNode:"ALARM_bil", NodeAlg:"BitLampBlink", byRiseEdge:true, getBit:5 },
					  PLC_txt: { DataKey:"PLC", setNode:"PLC_txt", NodeAlg:"Text" },
				   PLC_TT_txt: { DataKey:"PLC_TT", setNode:"PLC_TT_txt", NodeAlg:"Text", div:10 },
				    STATE_txt: { DataKey:"STATE", setNode:"STATE_txt", NodeAlg:"Text", byRiseEdge:true, fromArray:G_RES[G_LANG]["STATE_List"] },
					STATE_log: { DataKey:"STATE", byRiseEdge:true, fromArray:G_RES[G_LANG]["STATE_ListShort"], execFunc:onFuncWsLog, LogTarget:G_RES[G_LANG]["STATE"], LogColor:G_RES[G_LANG]["STATE_ListColor"] }
				   };
		
		//Init. WebHMI-client
		initUI(G_WS_SERVER_URI, G_WS_SERVER_ID, WsOpts);


        /* INIT UI
         */
		
		G_FORM_SET["ItemOptions"]["SET_ID"]	    = { ItemType: "number", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["SP"]  	    = { ItemType: "number", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["D"]  	    = { ItemType: "number", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["DHI"]  	    = { ItemType: "number", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["THI"]  	    = { ItemType: "number", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["DLO"]  	    = { ItemType: "number", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["TLO"]  	    = { ItemType: "number", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["TB"]  	    = { ItemType: "number", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["START"]      = { ItemType: "select", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["scheme_use"]	= { ItemType: "checkbox", DataType: "number", Allow: true };
		G_FORM_SET["ItemOptions"]["chart_use"]	= { ItemType: "checkbox", DataType: "number", Allow: true };
		
		$("#FormViewScheme").bind("click", onFormViewSchemeClicked);
		$("#FormViewChart").bind("click", onFormViewChartClicked);
		$("#FormSetApply").bind("click", onFormSetApplyClicked);


        /* INIT PLOT
         */
        
		G_CHART = new MainChartLinear("Chart");
		G_CHART.AutoScaleGrid = false;
		G_CHART.ValueMin      = 0;
		G_CHART.ValueMax      = 60;
		G_CHART.init();
		
		G_CHART_DATA_ASSOC = { SP_Lo:{ChartID:0, Check:"Chart_SP_Lo"}, SP_Hi:{ChartID:1, Check:"Chart_SP_Hi"}, TT001:{ChartID:2, Check:"Chart_TT001"}, SP:{ChartID:3, Check:"Chart_SP"} };
		G_CHART_DATA = { charts: [  
									{    id: "SP_Lo",
									  label: "SP-D",
									  lines: { show:true, fill:false, lineWidth:0 },
									  color: "#008000",
									 points: { show: false, symbol: "circle" },
									   data: [  ] //[ [X.msec, Y.number], ... ]
									},
									{    id: "SP_Hi",
									  label: "SP+D",
									  lines: { show:true, fill:0.25, lineWidth:0 },
									  color: "#008000",
									  fillBetween: "SP_Lo",
									 points: { show: false, symbol: "circle" },
									   data: [  ] //[ [X.msec, Y.number], ... ]
									},
									{    id: "TT001",
									  label: "TT001",
									  lines: { show:true, fill:false, lineWidth:3.0 },
									  color: "#000000",
									 points: { show: false, symbol: "circle" },
									   data: [  ] //[ [X.msec, Y.number], ... ]
									},
									{    id: "SP",
									  label: "SP",
									  lines: { show:true, fill:false, lineWidth:0.8 },
									  color: "#FFFF00",
									 points: { show: false, symbol: "circle" },
									   data: [  ] //[ [X.msec, Y.number], ... ]
									}									
								 ]
						};
	}
}
