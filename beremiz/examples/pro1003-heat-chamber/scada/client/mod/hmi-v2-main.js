/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  Module: HMI (v.2).
*   Client functionality.
*
*   Copyright (C) 2019  ATgroup09 (atgroup09@gmail.com)
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

/* Changes
*
*    2019-06-27
*    + isAnswerNetDevAddr()
*    + G_DEVICE_ADDR
*    + G_FIELD__DEVICE_ADDR
*/


//** GLOBAL VARIABLES

//* WebSocket Server
var G_WS_SERVER_URI	    	= "ws://localhost:8100";
var G_WS_SERVER_ID	    	= "WsServer";
var G_WS_SERVER_STAMP		= 0;

//* WebSocket
var G_WS 	    			= null;

//* Time of Watchdog
var G_WATCHDOG_TM			= 60; //seconds > 1 min
var G_WATCHDOG_TIMER		= 0;
var G_WATCHDOG_DATA_STAMP	= 0;
var G_WATCHDOG_DATA_LOGGED  = false;
var G_WATCHDOG_CONN_LOGGED  = false;

//* PopupBasic dialog
var G_POPUP_BASIC			= null;

//* UI Resources
var G_RES 					= {en:{}, ru:{}};

//* UI Language
var G_LANG 					= "ru";

//* forms
var G_FORM_SET				= null;

//* HMI
var G_HMI					= null;

var G_DEBUG 				= false;

//* Data fields
var G_FIELD__ID				= "ID";
var G_FIELD__STAMP			= "Stamp";
var G_FIELD__NETWORKS		= "Networks";
var G_FIELD__DEVICES		= "Devices";
var G_FIELD__DEVICE_ADDR	= "BaseAddr";

//* Log
var G_LOG					= null;
var G_LOG_LIM_ROWS			= 100;

//* Filter of data
//** by Device base address (if > 0 - used, otherwise - all devices)
var G_DEVICE_ADDR			= 0;


//** FUNCTIONS

/*
@brief  Function: Get state of connection with WsServer.
@param  None.
@return state ID: [NUMBER]
		= 0 - connecting
		= 1 - open
		= 2 - closing
		= 3 - closed
		= 4 - unknown
*/
function getWsServerState()
{
	if(G_WS != null)
	{
		if(G_WS.readyState >= 0 || G_WS.readyState < 4) return (G_WS.readyState);
	}
	
	return (4);
}


/*
@brief  Function: Check connection with WsServer.
@param  None.
@return True if the connection has established, otherwise - False.
*/
function hasWsServerOpened()
{
	var State = getWsServerState();
	return ((State == 1) ? true : false);
}


/*
@brief  Function: Refresh description about WsServer.
@param  None.
@return None.
*/
function refreshWsServerDesc()
{
	var State = getWsServerState();
	var Node  = null;
	
	Node = $("#WsServerID");
	if(Node) Node.text(G_WS_SERVER_ID);
	
	Node = $("#WsServerUri");
	if(Node) 
	{
		Node.text(G_WS_SERVER_URI);
		Node.attr("title", G_WS_SERVER_URI);
	}
	
	Node = $("#WsServerState");
	if(Node) Node.text(G_RES[G_LANG]["ConnStates"][State]);
	
	var Arr = [$("#FormSetConnect"), $("#ConnectState")];
	
	for(var i=0; i<Arr.length; i++)
	{
		if(Arr[i])
		{
			Arr[i].removeClass("ui-icon-disconnected");
			Arr[i].removeClass("ui-icon-connected");
			
			Arr[i].addClass(((State == 1) ? "ui-icon-connected" : "ui-icon-disconnected"));
			Arr[i].text(((State == 1) ? G_RES[G_LANG]["Disconnect"] : G_RES[G_LANG]["Connect"]));
			Arr[i].attr("title", ((State == 1) ? G_RES[G_LANG]["Disconnect"] : G_RES[G_LANG]["Connect"]));
		}
	}
}


/*
@brief  Function: Refresh HMI.
@param  DataIn - data for HMI.	[OBJECT]
@return None.
*/
function refreshHMI(DataIn)
{
	if(DataIn && G_HMI)
	{
		G_HMI.refresh(DataIn);
	}
}


/*
@brief  Function: Close connection with WebSocket Server.
@param  None.
@return None.
*/
function closeWsServer()
{
	if(G_WS) G_WS.close();
}


/*
@brief  Function: Handler of event Window.unload.
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onWindowBeforeUnload(event)
{
	closeWsServer();
	return (null);
}


/*
@brief  Function: Handler of event WebSocket.onopen.
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onWebSocketOpened(event)
{
	G_WATCHDOG_DATA_LOGGED = false;
	G_WATCHDOG_CONN_LOGGED = false;
	
	G_LOG.add(null, G_RES[G_LANG]["WebSocket"], G_RES[G_LANG]["Connected"], null);
	printDebug(G_DEBUG, "CONNECTED");
	
	refreshWsServerDesc();
}


/*
@brief  Function: Handler of event WebSocket.onclose.
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onWebSocketClosed(event)
{
	if(!G_WATCHDOG_CONN_LOGGED)
	{
		G_LOG.add(null, G_RES[G_LANG]["WebSocket"], G_RES[G_LANG]["Disconnected"], null);
		printDebug(G_DEBUG, "DISCONNECTED");
	}
	
	refreshWsServerDesc();
}


/*
@brief  Function: Check array of networks in a server answer (JSON).
@param  JsonIn - server answer (JSON).	[OBJECT]
@return True if a server answer contains array of networks, otherwise - False.	[BOOLEAN]
@details JsonIn[G_FIELD__ID] == G_WS_SERVER_ID, JsonIn[G_FIELD__STAMP], isArray(JsonIn[G_FIELD__NETWORKS])
*/
function isAnswerNet(JsonIn)
{
	if(typeof JsonIn == "object" && typeof is_array == "function")
	{
		if(JsonIn)
		{
			if(typeof JsonIn[G_FIELD__ID] == "string" && typeof JsonIn[G_FIELD__STAMP] == "number" && typeof JsonIn[G_FIELD__NETWORKS] == "object")
			{
				if(JsonIn[G_FIELD__ID] == G_WS_SERVER_ID)
				{
					return (is_array(JsonIn[G_FIELD__NETWORKS]));
				}
			}
		}
	}
	
	return (false);
}


/*
@brief  Function: Check array of network devices.
@param  JsonNetIn - network.	[OBJECT]
@return True if a network contains array of devices, otherwise - False.	[BOOLEAN]
@details isArray(JsonNetIn[G_FIELD__DEVICES])
*/
function isAnswerNetDev(JsonNetIn)
{
	if(typeof JsonNetIn == "object" && typeof is_array == "function")
	{
		if(JsonNetIn)
		{
			if(typeof JsonNetIn[G_FIELD__DEVICES] == "object")
			{
				return (is_array(JsonNetIn[G_FIELD__DEVICES]));
			}
		}
	}
	
	return (false);
}


/*
@brief  Function: Check device by base address.
@param  JsonDevIn - device;	[OBJECT]
@param  AddrIn - device base address. [NUMBER]
@return True if the device contains target base address, otherwise - False.	[BOOLEAN]
@details if JsonDevIn[G_FIELD__DEVICE_ADDR] == AddrIn
*/
function isAnswerNetDevAddr(JsonDevIn, AddrIn)
{
	if(typeof JsonDevIn == "object")
	{
		if(JsonDevIn)
		{
			if(typeof JsonDevIn[G_FIELD__DEVICE_ADDR] == "number")
			{
				return (JsonDevIn[G_FIELD__DEVICE_ADDR] == AddrIn);
			}
		}
	}
	
	return (false);
}


/*
@brief  Function: Handler of event WebSocket.onmessage.
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onWebSocketMsgReceived(event)
{
	var JsonParse = JSON.parse(event.data);
	
	printDebug(G_DEBUG, "MESSAGE: " + event.data);
	//printDebug(G_DEBUG, JsonParse);
	
	if(isAnswerNet(JsonParse))
	{
		G_WS_SERVER_STAMP      = JsonParse[G_FIELD__STAMP];
		G_WATCHDOG_DATA_LOGGED = false;
		
		var i = 0, j = 0;
		
		for(i=0; i<JsonParse[G_FIELD__NETWORKS].length; i++)
		{
			if(isAnswerNetDev(JsonParse[G_FIELD__NETWORKS][i]))
			{
				printDebug(G_DEBUG, JsonParse[G_FIELD__NETWORKS][i]);
				
				for(j=0; j<JsonParse[G_FIELD__NETWORKS][i][G_FIELD__DEVICES].length; j++)
				{
					//** filtration of devices
					
					// by base address
					if(G_DEVICE_ADDR > 0)
					{
						if(!isAnswerNetDevAddr(JsonParse[G_FIELD__NETWORKS][i][G_FIELD__DEVICES][j], G_DEVICE_ADDR)) continue;
					}
					
					printDebug(G_DEBUG, JsonParse[G_FIELD__NETWORKS][i][G_FIELD__DEVICES][j]);
					refreshHMI(JsonParse[G_FIELD__NETWORKS][i][G_FIELD__DEVICES][j]);
				}
			}
		}
	}
}


/*
@brief  Function: Handler of event WebSocket.onerror.
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onWebSocketErrReceived(event)
{
	if(!G_WATCHDOG_CONN_LOGGED)
	{
		var Str = G_RES[G_LANG]["SrvConnErr"].replace(/\{0\}/g, G_WS_SERVER_URI);
	
		printDebug(G_DEBUG, Str);
		G_LOG.add(null, G_RES[G_LANG]["WebSocket"], Str, "yellow");
		if(!G_LOG.isCaseVisible()) G_POPUP_BASIC.showBasic(Str);
	}
}


/*
@brief  Function: Open connection with WebSocket Server.
@param  None.
@return None.
*/
function openWsServer()
{
	try
	{
		if(typeof MozWebSocket == "function") WebSocket = MozWebSocket;
		if(G_WS && G_WS.readyState == 1) G_WS.close();
		
		if(!G_WS) window.onbeforeunload = onWindowBeforeUnload;
		
		if(typeof WebSocket != "undefined")
		{
			G_WS = new WebSocket(G_WS_SERVER_URI);
			G_WS.onopen    = onWebSocketOpened;
			G_WS.onclose   = onWebSocketClosed;
			G_WS.onmessage = onWebSocketMsgReceived;
			G_WS.onerror   = onWebSocketErrReceived;
		}
		else
		{
			printDebug(G_DEBUG, "Error! Websocket is not supported in your browser!");
			G_LOG.add(null, G_RES[G_LANG]["WebSocket"], G_RES[G_LANG]["WsNotSupportErr"], null);
			if(!G_LOG.isCaseVisible()) G_POPUP_BASIC.showBasic(G_RES[G_LANG]["WsNotSupportErr"]);
		}
	}
	catch (exception)
	{
		printDebug(G_DEBUG, "Exception! " + exception);
		G_LOG.add(null, G_RES[G_LANG]["WebSocket"], "Exception! " + exception, null);
		if(!G_LOG.isCaseVisible()) G_POPUP_BASIC.showBasic("Exception! " + exception);
	}
}


/*
@brief  Function: Handler for event FormSetConnect.click.
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onFormSetConnectClicked(event)
{
	var State = getWsServerState();
	
	G_WATCHDOG_DATA_LOGGED = false;
	G_WATCHDOG_CONN_LOGGED = false;
	
	if(State == 0 || State == 1)
	{
		closeWsServer();
	}
	else
	{
		openWsServer();
	}
}


/*
@brief  Function: Handler for event FormSetLog.click.
@param  event - Event-object.	[OBJECT]
@return None.
*/
function onFormSetLogClicked(event)
{
	var Res = G_FORM_SET.getResultset();
	
	if(Res)
	{
		var LogUse = ((typeof Res["log_use"] == "number") ? true : false);
		G_LOG.toggleCase(LogUse);
	}
}


/*
@brief  Function: Handler for event WatchdogTimer.elapsed
@param  None.
@return None.
*/
function onWatchdogTimerElapsed()
{
	var State     = getWsServerState();
	var Connected = (State == 0 || State == 1);
	
	//** Check data
	
	if(G_WATCHDOG_DATA_STAMP == G_WS_SERVER_STAMP)
	{
		if(!G_WATCHDOG_DATA_LOGGED)
		{
			G_WATCHDOG_DATA_LOGGED = true;
			
			var Str = G_RES[G_LANG]["NoDataErr"].replace(/\{0\}/g, G_WS_SERVER_URI);
			printDebug(G_DEBUG, Str);
			G_LOG.add(null, G_RES[G_LANG]["WatchDog"], Str, "yellow");
			if(!G_LOG.isCaseVisible() && Connected) G_POPUP_BASIC.showBasic(Str);
		}
	}
	
	G_WATCHDOG_DATA_STAMP = G_WS_SERVER_STAMP;
	
	
	//** Check connection
	
	if(!Connected)
	{
		if(!G_WATCHDOG_CONN_LOGGED)
		{
			G_WATCHDOG_CONN_LOGGED = true;
			
			printDebug(G_DEBUG, "WatchdogConnect: Reconnect");
			G_LOG.add(null, G_RES[G_LANG]["WatchDog"], G_RES[G_LANG]["AutoReconnect"], null);
		}
		
		openWsServer();
	}
}


/*
@brief  Function: Write to Log
@param  NodeIn - target node;	[OBJECT]
@param  ValueIn - value; [NUMBER]
@param  DataKeyIn - key to DataIn; [STRING]
@param  ColorIn - Log-color. [STRING]
@return None.
*/
function writeToLog(NodeIn, ValueIn, DataKeyIn, ColorIn)
{
	if(typeof NodeIn == "object" && typeof ValueIn == "number" && typeof DataKeyIn == "string")
	{
		if(NodeIn && DataKeyIn.length)
		{
			var LogStamp = null;
				
			if(G_WS_SERVER_STAMP > 0)
			{
				var Stamp = new Date();
				Stamp.set_time_stamp(G_WS_SERVER_STAMP);
				LogStamp = Stamp.format("isoDateTimeNorm");
			}
			
			var LogTarget    = null;
			var LogResTarget = NodeIn.attr("log-res-target");
			
			if(typeof LogResTarget == "string")
			{
				LogTarget = ((typeof G_RES[G_LANG][LogResTarget] == "string") ? G_RES[G_LANG][LogResTarget] : null);
			}
			
			
			var LogMessage = null;
			
			//message by DataKey
			//console.log(DataKeyIn + " " + ValueIn);
			if(typeof G_RES[G_LANG][DataKeyIn] != "undefined")
			{
				if(typeof G_RES[G_LANG][DataKeyIn][ValueIn] == "string") LogMessage = G_RES[G_LANG][DataKeyIn][ValueIn];
			}
			
			//message by attr. "log-res-msg"
			var LogResMsg = NodeIn.attr("log-res-msg");
			//console.log(LogResMsg + " " + ValueIn);
			if(typeof LogResMsg == "string")
			{
				LogMessage = null;
				if(typeof G_RES[G_LANG][LogResMsg][ValueIn] == "string") LogMessage = G_RES[G_LANG][LogResMsg][ValueIn];
			}
			
			
			var LogColor = ((typeof ColorIn == "string") ? ColorIn : null);
			
			if(typeof LogMessage == "string")
			{
				if(LogMessage.length) G_LOG.add(LogStamp, LogTarget, LogMessage, LogColor);
			}
		}
	}
}


/*
@brief  Function: Handler for event BitFuncWs.log
@param  NodeIn - target node;	[OBJECT]
@param  ValueIn - value; [NUMBER]
@param  KeyIn - key to HMI-options; [STRING]
@param  DataKeyIn - key to DataIn; [STRING]
@param  DataIn - data. [OBJECT]
@return true.	[BOOLEAN]
*/
function onBitFuncWsLog(NodeIn, ValueIn, KeyIn, DataKeyIn, DataIn)
{
	if(typeof NodeIn == "object" && typeof ValueIn == "number" && typeof DataKeyIn == "string")
	{
		writeToLog(NodeIn, ValueIn, DataKeyIn, null);
	}
	
	return (true);
}


/*
@brief  Function: Handler for event BitFuncWsRed.log
@param  NodeIn - target node;	[OBJECT]
@param  ValueIn - value; [NUMBER]
@param  KeyIn - key to HMI-options; [STRING]
@param  DataKeyIn - key to DataIn; [STRING]
@param  DataIn - data. [OBJECT]
@return true.	[BOOLEAN]
*/
function onBitFuncWsRedLog(NodeIn, ValueIn, KeyIn, DataKeyIn, DataIn)
{
	if(typeof NodeIn == "object" && typeof ValueIn == "number" && typeof DataKeyIn == "string")
	{
		writeToLog(NodeIn, ValueIn, DataKeyIn, "red");
	}
	
	return (true);
}


/*
@brief  Function: Handler for event BitFuncWsYellow.log
@param  NodeIn - target node;	[OBJECT]
@param  ValueIn - value; [NUMBER]
@param  KeyIn - key to HMI-options; [STRING]
@param  DataKeyIn - key to DataIn; [STRING]
@param  DataIn - data. [OBJECT]
@return true.	[BOOLEAN]
*/
function onBitFuncWsYellowLog(NodeIn, ValueIn, KeyIn, DataKeyIn, DataIn)
{
	if(typeof NodeIn == "object" && typeof ValueIn == "number" && typeof DataKeyIn == "string")
	{
		writeToLog(NodeIn, ValueIn, DataKeyIn, "yellow");
	}
	
	return (true);
}


/*
@brief  Function: Handler for event BitFuncWsGreen.log
@param  NodeIn - target node;	[OBJECT]
@param  ValueIn - value; [NUMBER]
@param  KeyIn - key to HMI-options; [STRING]
@param  DataKeyIn - key to DataIn; [STRING]
@param  DataIn - data. [OBJECT]
@return true.	[BOOLEAN]
*/
function onBitFuncWsGreenLog(NodeIn, ValueIn, KeyIn, DataKeyIn, DataIn)
{
	if(typeof NodeIn == "object" && typeof ValueIn == "number" && typeof DataKeyIn == "string")
	{
		writeToLog(NodeIn, ValueIn, DataKeyIn, "green");
	}
	
	return (true);
}


/*
@brief  Function: Initialize PopupBasic-dialog.
@param  None.
@return None.
*/
function initPopupBasic()
{
	if(typeof jsPopupDialog == "function")
	{
		G_POPUP_BASIC = new jsPopupDialog("PopupBasic");
	}
}


/*
@brief  Function: Initialize FormSet.
@param  None.
@return None.
*/
function initFormSet()
{
	if(typeof jsForm == "function")
	{
		G_FORM_SET = new jsForm("FormSet");
		
		G_FORM_SET["ItemOptions"] = { log_use: { ItemType: "checkbox", DataType: "number", Allow: true }
									 };
		
		$("#FormSetConnect").bind("click", onFormSetConnectClicked);
		$("#FormSetLog").bind("click", onFormSetLogClicked);
		
		G_FORM_SET.AutoCreate = true;
	}
}


/* TEMPLATE
@brief  Function: Inititialize UI.
@param  None.
@return None.
*/
/*
function initUI()
{
	if(typeof HMI == "function")
	{
		G_HMI = new HMI();
		G_HMI["Options"] = { ... };
		G_HMI["DefaultValue"] = G_RES[G_LANG]["None"];
		G_HMI.init();
	}
	
	if(typeof jsLog == "function")
	{
		G_LOG = new jsLog("LogTable");
		G_LOG.LimRows           = G_LOG_LIM_ROWS;
		G_LOG.AllowRotate       = true;
		G_LOG.AllowCurrentStamp = true;
		G_LOG.CaseID            = "LogCase";
	}
	
	initPopupBasic();
	initFormSet();
	
	refreshWsServerDesc();
	
	$("#FormSetConnect").trigger("click");
	
	G_WATCHDOG_TIMER = setInterval(onWatchdogTimerElapsed, G_WATCHDOG_TM*1000);
}
*/

