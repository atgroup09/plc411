/* JAVASCRIPT DOCUMENT
*  UTF-8
*/

/* Module: HMI (v.3).
*  Class.
*
*  Copyright (C) 2016-2022  ATgroup09 (atgroup09@gmail.com)
*
*  The JavaScript code in this page is free software: you can
*  redistribute it and/or modify it under the terms of the GNU
*  General Public License (GNU GPL) as published by the Free Software
*  Foundation, either version 3 of the License, or (at your option)
*  any later version.  The code is distributed WITHOUT ANY WARRANTY;
*  without even the implied warranty of MERCHANTABILITY or FITNESS
*  FOR A PARTICULAR PURPOSE.  See the GNU GPL for more details.
*
*  As additional permission under GNU GPL version 3 section 7, you
*  may distribute non-source (e.g., minimized or compacted) forms of
*  that code without the copy of the GNU GPL normally required by
*  section 4, provided you include this license notice and a URL
*  through which recipients can access the Corresponding Source.
*/

/* CHANGES
*
*  2022-08-01
*   + New API.
*/


/* REQUIRED LIB/MOD
*
*	+ lib/js/types/types.js
*	+ lib/js/bit.js
*	+ lib/js/jquery.min.js
*	+ lib/js/date.format.js
*
*/


//** GLOBAL VARIABLES

//* blink timer period	[INTEGER]
var G_HMI__TIMER_BLINK_PERIOD = 1000*1;	//1 sec

//* blink timer ID	[INTEGER]
var G_HMI__TIMER_BLINK_ID = -1;

//* blink toggle state	[BOOLEAN]
var G_HMI__BLINK_STATE = false;

//* Nodes of type "BitLampBlink" (associative array)	[OBJECT]
//*
//*  { Key: { Node: OBJECT, Value: true|false },
//*    ...
//*  }
var G_HMI__BITLAMPBLINK_NODES	= null;


//** FUNCTIONS

/*	Function: timer handler-function.
*	   Input:
*             none.
*	  Output:
*             none.
*       Note:
*/

/*
@brief  Function: Handler for TimerBlink.timeout.
@param  None.
@return None.
*/
function HMI_TimerBlinkHandler()
{
	for(var key in G_HMI__BITLAMPBLINK_NODES)
	{
		if(typeof G_HMI__BITLAMPBLINK_NODES[key] == "object")
		{
			if(G_HMI__BITLAMPBLINK_NODES[key])
			{
				if(typeof G_HMI__BITLAMPBLINK_NODES[key]["Node"] == "object" && (typeof G_HMI__BITLAMPBLINK_NODES[key]["Value"] == "boolean" || typeof G_HMI__BITLAMPBLINK_NODES[key]["Value"] == "number"))
				{
					if(G_HMI__BITLAMPBLINK_NODES[key]["Node"])
					{
						if(G_HMI__BITLAMPBLINK_NODES[key]["Value"])
						{
							//toggle visible status (blink mode) if Value is true
							G_HMI__BITLAMPBLINK_NODES[key]["Node"].toggle(G_HMI__BLINK_STATE);
						}
						else
						{
							//hide if Value is false
							if(G_HMI__BITLAMPBLINK_NODES[key]["Node"].is(":visible")) G_HMI__BITLAMPBLINK_NODES[key]["Node"].hide();
						}
					}
				}
			}
		}
	}

	G_HMI__BLINK_STATE = (!G_HMI__BLINK_STATE);
}


//** CLASSES

/*	Class: HMI.
*	Input:
*          none.
*/

/*
@brief  Class: HMI.
@param  None.
*/
function HMI()
{
	//Public properties

	//* object options (associative array) [OBJECT]
	this.Options = { };
	
	//* first refresh-iteration is done [BOOLEAN]
	this.RefreshFirstIter = false;
	

	//Private properties

	//* nodes (associative array)	[OBJECT]
	var Nodes = { };

	//* local registers (associative array)	[OBJECT]
	var LocReg  = { };

	//* status of checking the functions		[BOOLEAN]
	var HaveFunc = false;
	
	//* status of break-flow watchdog [BOOLEAN]
	var BreakFlow = false;


	//Methods

	/*
	@brief  Public Method: Check option of target item.
	@param  Option_in - option item. [OBJECT]
	@return True if option item is correct, otherwise - False.	[BOOLEAN]
	*/
	this.isOption = function(Option_in)
		{
			if(HaveFunc && typeof Option_in == "object")
			{
				var ItemAttrs = new Array( { name: "DataKey", data_type: "string", null_value: false }
										 );

				return check_object(Option_in, ItemAttrs);
			}

			return (false);
		};

	/*
	@brief  Public Method: Check option of target item by key.
	@param  Key_in - key of option. [STRING]
	@return True if option item is correct, otherwise - False.	[BOOLEAN]
	*/
	this.isOptionByKey = function(Key_in)
		{
			if(typeof Key_in == "string")
			{
				if(typeof this.Options[Key_in] == "object")
				{
					return (this.isOption(this.Options[Key_in]));
				}
			}

			return (false);
		};

	/*
	@brief  Public Method: Get list of keys to Options.
	@param  None.
	@return list of keys.	[ARRAY]
	*/
	this.getKeys = function()
		{
			var Keys = [ ];

			for(var Key in this.Options)
			{
				Keys.push(Key);
			}

			return (Keys);
		};

	/*
	@brief  Public Method: Get list of keys to Options for items with Old-values.
	@param  Stamp_in - master Unix TimeStamp or NULL. [NUMBER || NULL]
	@return list of keys.	[ARRAY]
	@detailed
		      If Stamp_in is not number, then will use Current TimeStamp.
		      If option stamp < Stamp_in, then is Old-value.
	*/
	this.getKeysForOld = function(Stamp_in)
		{
			var Stamp = ((typeof Stamp_in == "number") ? Stamp_in : (new Date()).get_current_time_stamp());
			var Keys  = [ ];

			for(var Key in this.Options)
			{
				if(typeof this.Options[Key]["Stamp"] == "number")
				{
					if(this.Options[Key]["Stamp"] < Stamp) Keys.push(Key);
				}
			}

			return (Keys);
		};

	/*
	@brief  Public Method: Set "Stamp".
	@param  Key_in - key of option;	[STRING]
	@param  Stamp_in - value or NULL. [NUMBER || NULL]
	@return Set value or -1 if an Option not found. [NUMBER]
	@detailed
		      If Stamp_in is not number, then will use Current TimeStamp.
	*/
	this.setStamp = function(Key_in, Stamp_in)
		{
			var Result = -1;

			if(typeof Key_in == "string" && this.Options)
			{
				if(typeof this.Options[Key_in] == "object")
				{
					if(this.Options[Key_in])
					{
						Result = ((typeof Stamp_in == "number") ? Stamp_in : (new Date()).get_current_time_stamp());
						this.Options[Key_in]["Stamp"] = Result;
					}
				}
			}

			return (Result);
		};

	/*
	@brief  Public Method: Fix value.
	@param  Key_in - key of option;	[STRING]
	@param  Value_in - value or NULL. [NUMBER || STRING || BOOLEAN || OBJECT || NULL]
	@param  RawValue_in - raw-value or NULL. [NUMBER || STRING || BOOLEAN || OBJECT || NULL]
	@return None.
	@detailed
		      this.Options[Key_in]["Value"] = Value_in
		      this.Options[Key_in]["Stamp"] = CurrentTimeStamp
	*/
	this.fixValue = function(Key_in, Value_in, RawValue_in)
		{
			if(typeof Key_in == "string" && this.Options)
			{
				if(typeof this.Options[Key_in] == "object")
				{
					if(this.Options[Key_in])
					{
						this.Options[Key_in]["RawValue"] = ((typeof RawValue_in != "undefined") ? RawValue_in : null);
						this.Options[Key_in]["Value"]    = ((typeof Value_in != "undefined") ? Value_in : null);
						this.Options[Key_in]["Stamp"]    = (new Date()).get_current_time_stamp();
					}
				}
			}
		};

	/*
	@brief  Public Method: Compare value with a previous.
	@param  Key_in   - key of option;	[STRING]
	@param  Value_in - value. [NUMBER || STRING || BOOLEAN || OBJECT || NULL]
	@return True if values are equivalent, otherwise - False.
	*/
	this.isEqPrev = function(Key_in, Value_in)
		{
			if(typeof Key_in == "string" && this.Options)
			{
				if(typeof this.Options[Key_in] == "object")
				{
					if(this.Options[Key_in])
					{
						if(typeof Value_in == typeof this.Options[Key_in]["Value"])
						{
							if(Value_in == this.Options[Key_in]["Value"]) return (true);
						}
					}
				}
			}
			
			return (false);
		};

	/*
	@brief  Public Method: Convert value to number of bool-notation.
	@param  Value_in - value. [NUMBER || STRING || OBJECT || BOOLEAN || NULL]
	@return 0 || 1.	[NUMBER]
	*/
	this.toBoolNum = function(Value_in)
		{
			if(typeof Value_in == "object" || typeof Value_in == "boolean" || typeof Value_in == "number")
			{
				if(Value_in) return (1);
			}
			else if(typeof Value_in == "string")
			{
				if(Value_in.length > 0) return (1);
			}
			
			return (0);
		};

	/*
	@brief  Public Method: Test Value by setpoint.
	@param  SetpointAlgIn - sertpoint algoritm [STRING]
	@arg    = "equ" - value is equal to setpoint
	@arg    = "neq" - value is not equal to setpoint
	@arg    = "lss" - value is less than setpoint
	@arg    = "leq" - value is less than or equal to setpoint
	@arg    = "gtr" - value is greater than setpoint
	@arg    = "geq" - value is greater than or equal to setpoint
	@param  SetpointIn - sertpoint [ANY]
	@param  ValueIn - source value [ANY]
	@return 0 || 1.	[NUMBER]
	@note "equ" and "neq" - for Value and Setpoint of any types
          "lss", "leq", "gtr", "geq" - for Value and Setpoint of number types
	*/
	this.bySetpoint = function(SetpointAlgIn, SetpointIn, ValueIn)
		{
			var Res = 0;
			
			if(typeof SetpointAlgIn == "string" && typeof SetpointIn != "undefined" && typeof SetpointIn == typeof ValueIn)
			{
				switch(SetpointAlgIn)
				{
					case "equ":
						if(ValueIn == SetpointIn) Res = 1;
						break;
					
					case "neq":
						if(ValueIn != SetpointIn) Res = 1;
						break;
					
					case "lss":
						if(typeof SetpointIn == "number")
						{
							if(ValueIn < SetpointIn) Res = 1;
						}
						break;
						
					case "leq":
						if(typeof SetpointIn == "number")
						{
							if(ValueIn <= SetpointIn) Res = 1;
						}
						break;
						
					case "gtr":
						if(typeof SetpointIn == "number")
						{
							if(ValueIn > SetpointIn) Res = 1;
						}
						break;
						
					case "geq":
						if(typeof SetpointIn == "number")
						{
							if(ValueIn >= SetpointIn) Res = 1;
						}
						break;
				}
			}
			
			if(!Res) BreakFlow = true;
			
			return (Res);
		};
		
	/*
	@brief  Public Method: Extract a value from an array.
	@param  ArrIn - array; [ARRAY]
	@param  KeyIn - key to Arr. [NUMBER || STRING]
	@param  DefaultIn - value by default. [NUMBER || STRING || NULL]
	@return Exctracted value or KeyIn. [ANY]
	*/
	this.fromArray = function(ArrIn, KeyIn, DefaultIn)
		{
			if(typeof ArrIn != "undefined" && (typeof KeyIn == "string" || typeof KeyIn == "number"))
			{
				if(typeof ArrIn[KeyIn] != "undefined")
				{
					return (ArrIn[KeyIn]);
				}
			}
			
			BreakFlow = true;
			
			return ((typeof DefaultIn == "number" || typeof DefaultIn == "string") ? DefaultIn : KeyIn);
		};

	/*
	@brief  Private Method: Normilize float point for numeric value.
	@param  Value_in - value. [NUMBER || STRING]
	@return Normilized numeric value. [NUMBER]
	*/
	var normFloatPoint = function(Value_in)
		{
			var Value = 0.0;
			
			if(typeof Value_in == "string")
			{
				var Buff = replace_sub_string("[,]", Value_in, ".");
				Value = (Buff-0);
			}
			else if(typeof Value_in == "number")
			{
				Value = Value_in;
			}
			
			return (Value);
		}

	/*
	@brief  Private Method: Set rounding to up for numeric value.
	@param  Value_in - value. [NUMBER || STRING]
	@param  Round_in - the number of digits after decimal point (>=0). [NUMBER]
	@return New value. [NUMBER]
	*/
	var setRound = function(Value_in, Round_in)
		{
			var Value = normFloatPoint(Value_in);
			var Round = ((typeof Round_in == "number") ? Math.round(Round_in) : 0);
			return (Value.toFixed(Round)-0);
		}

	/*
	@brief  Private Method: Set rounding to down for numeric value.
	@param  Value_in - value. [NUMBER || STRING]
	@return New value. [NUMBER]
	*/
	var setFloor = function(Value_in)
		{
			var Value = normFloatPoint(Value_in);
			return (Math.floor(Value));
		}

	/*
	@brief  Public Method: Set value to Local register.
	@param  LocRegKey_in - register key. [STRING]
	@param  Value_in - value. [NUMBER || STRING]
	@return None.
	*/
	this.setLocReg = function(LocRegKey_in, Value_in)
		{
			if(typeof LocRegKey_in == "string")
			{
				if(LocRegKey_in.length)
				{
					if(typeof LocReg[LocRegKey_in] != "undefined")
					{
						LocReg[LocRegKey_in] = Value_in;
					}
				}
			}
		};
	
	/*
	@brief  Public Method: Set (increment) Local register-counter.
	@param  LocCntrKey_in - register-counter key. [STRING]
	@param  Alg_in - algorithm. [STRING]
	@param  Value_in - value. [NUMBER || STRING]
	@param  MinIn - minimum limit (null is disable this limit) [NUMBER || NULL]
	@param  MaxIn - maximum limit (null is disable this limit) [NUMBER || NULL]
	@return None.
	*/
	this.setLocCntr = function(LocCntrKey_in, Alg_in, Value_in, MinIn, MaxIn)
		{
			if(typeof LocCntrKey_in == "string" && typeof Alg_in == "string")
			{
				if(LocCntrKey_in.length)
				{
					if(typeof LocReg[LocCntrKey_in] != "undefined")
					{
						if(this.toBoolNum(Value_in))
						{
							if(!(Alg_in == "Inc" || Alg_in == "IncDec")) return;
							
							if(typeof MaxIn == "number")
							{
								if(LocReg[LocCntrKey_in] >= MaxIn) return;
							}
							
							LocReg[LocCntrKey_in]++;
						}
						else
						{
							if(!(Alg_in == "Dec" || Alg_in == "IncDec")) return;
							
							if(typeof MinIn == "number")
							{
								if(LocReg[LocCntrKey_in] <= MinIn) return;
							}
							
							LocReg[LocCntrKey_in]--;
						}
					}
				}
			}
		};
		
	/*
	@brief  Public Method: Reset (set zero) Local register-counter.
	@param  LocCntrKey_in - register-counter key. [STRING]
	@return None.
	*/
	this.rstLocCntr = function(LocCntrKey_in)
		{
			if(typeof LocCntrKey_in == "string")
			{
				if(LocCntrKey_in.length)
				{
					if(typeof LocReg[LocCntrKey_in] != "undefined")
					{
						LocReg[LocCntrKey_in] = 0;
					}
				}
			}
		};
		
	/*
	@brief  Public Method: Set node attribute.
	@param  Node_in - node; [OBJECT]
	@param  NodeAttr_in - name of attribute or NULL; [STRING]
	@param  Value_in - value. [NUMBER || STRING || NULL]
	@param  KeyIn - Key to Opts [STRING]
	@return None.
	*/
	this.setNodeAttr = function(Node_in, NodeAttr_in, Value_in, KeyIn)
		{
			if(typeof Node_in == "object" && typeof NodeAttr_in == "string" && typeof KeyIn == "string")
			{
				if(NodeAttr_in.length)
				{
					var Buff = ((typeof Value_in == "string" || typeof Value_in == "number") ? Value_in : 0);
					
					if(NodeAttr_in == "top")
					{
						Node_in.css("top", ("" + (Buff-0) + "px"));
					}
					else if(NodeAttr_in == "left")
					{
						Node_in.css("left", ("" + (Buff-0) + "px"));
					}
					else if(NodeAttr_in == "class")
					{
						if(this.toBoolNum(Buff))
						{
							Node_in.attr(KeyIn, Buff);
							Node_in.addClass(Buff);
						}
						else
						{
							if(typeof Node_in.attr(KeyIn) != "undefined")
							{
								Node_in.removeClass(Node_in.attr(KeyIn));
								Node_in.removeAttr(KeyIn);
							}
						}
					}
					else
					{
						if(this.toBoolNum(Buff))
						{
							Node_in.attr(NodeAttr_in, Buff);
						}
						else
						{
							if(typeof Node_in.attr(NodeAttr_in) != "undefined")
							{
								Node_in.removeAttr(NodeAttr_in);
							}
						}
					}
				}
			}
		};

	/*
	@brief  Public Method: Set BitLamp.
	@param  Node_in  - node; [OBJECT]
	@param  Value_in - value; [NUMBER || STRING || BOOLEAN || NULL]
	@param  BlinkMode_in - true if Type is "BitLampBlink", otherwise - false; [BOOLEAN]
	@return BitLamp state.	[BOOLEAN]
	*/
	this.setBitLamp = function(Node_in, Value_in, BlinkMode_in)
		{
			var fl = 0;
			
			if(typeof Node_in == "object")
			{
				if(Node_in)
				{
					var BlinkMode = ((typeof BlinkMode_in == "boolean") ? BlinkMode_in : false);
					var Src0      = Node_in.attr("src0");	//attr for FALSE state
					var Src1      = Node_in.attr("src1");	//attr for TRUE state
					
					fl = this.toBoolNum(Value_in);
					
					if(fl)
					{
						if(typeof Src1 == "string")
						{
							Node_in.attr("src", Src1);
						}
						else if(Node_in.is(":hidden") && !BlinkMode)
						{
							Node_in.show();
						}
					}
					else
					{
						if(typeof Src0 == "string")
						{
							Node_in.attr("src", Src0);
						}
						else if(Node_in.is(":visible") && !BlinkMode)
						{
							Node_in.hide();
						}
					}
				}
			}
			
			return (fl);
		};
	
	/*
	@brief  Public Method: Set Node.
	@param  NodeIn     - Node [OBJECT]
	@param  NodeAlgIn  - Algorithm to set node value [STRING]
	@param  NodeAttrIn - Name of node attribute (for NodeAlgIn == "Attr") [STRING]
	@param  ValueIn    - New node value [NUMBER || STRING]
	@param  KeyIn      - Key to Opts [STRING]
	@return None.
	*/
	this.setNode = function(NodeIn, NodeAlgIn, NodeAttrIn, ValueIn, KeyIn)
		{
			if(typeof NodeIn == "object" && typeof NodeAlgIn == "string" && (typeof ValueIn == "string" || typeof ValueIn == "number"))
			{
				if(NodeIn)
				{
					switch(NodeAlgIn)
					{
						case "Text":
							if(typeof ValueIn == "number")
								 NodeIn.text(""+ValueIn);
							else NodeIn.text(ValueIn);
							break;
							
						case "Attr":
							this.setNodeAttr(NodeIn, NodeAttrIn, ValueIn, KeyIn);
							break;
						
						case "BitLamp":
							this.setBitLamp(NodeIn, ValueIn, false);
							break;
						
						case "BitLampBlink":
							if(typeof KeyIn == "string")
							{
								if(typeof G_HMI__BITLAMPBLINK_NODES[KeyIn] != "undefined") G_HMI__BITLAMPBLINK_NODES[KeyIn]["Value"] = this.setBitLamp(NodeIn, ValueIn, true);
							}
							break;
					}
				}
			}
		};
		
	/*
	@brief  Public Method: Refresh HMI.
	@param  Data_in  - input data (resultset). [OBJECT]
	@return None.
	*/
	this.refresh = function(Data_in)
		{
			if(HaveFunc && Nodes)
			{
				var Result       = false;
				var RawValue     = null;
				var Value        = null;
				var DataKey      = null;
				var DefaultValue = null;
				var BeforeValue  = null;
				var LocCntrMin   = null;
				var LocCntrMax   = null;
				
				for(var Key in Nodes)
				{
					if(typeof this.Options[Key] == "object")
					{
						if(this.isOption(this.Options[Key]))
						{
							DataKey = this.Options[Key]["DataKey"];
							
							//VALUE INIT
							
							if(typeof Data_in != "object") continue;
							if(!Data_in) continue;
							if(typeof Data_in[DataKey] == "undefined") continue;
							
							RawValue     = Data_in[DataKey];
							Value        = RawValue;
							
							DefaultValue = null;
							BreakFlow    = false;
							LocCntrMin   = null;
							LocCntrMax   = null;
							
							if(typeof this.Options[Key]["Default"] == "number" || typeof this.Options[Key]["Default"] == "string")
							{
								DefaultValue = this.Options[Key]["Default"];
							}
							
							if(typeof this.Options[Key]["LocCntrMin"] == "number")
							{
								LocCntrMin = this.Options[Key]["LocCntrMin"];
							}
							
							if(typeof this.Options[Key]["LocCntrMax"] == "number")
							{
								LocCntrMax = this.Options[Key]["LocCntrMax"];
							}
							
							//VALUE MODIFICATORS
							
							if(typeof this.Options[Key]["toBoolNum"] == "number" || typeof this.Options[Key]["toBoolNum"] == "boolean")
							{
								if(this.Options[Key]["toBoolNum"]) Value = this.toBoolNum(Value);
							}
							
							if(typeof this.Options[Key]["div"] == "number" && typeof Value == "number")
							{
								if(this.Options[Key]["div"]) Value = Value/this.Options[Key]["div"];
							}
							
							if(typeof this.Options[Key]["mul"] == "number" && typeof Value == "number")
							{
								Value = Value*this.Options[Key]["mul"];
							}
							
							if(typeof this.Options[Key]["add"] == "number" && typeof Value == "number")
							{
								Value = Value+this.Options[Key]["add"];
							}
							
							if(typeof this.Options[Key]["sub"] == "number" && typeof Value == "number")
							{
								Value = Value+this.Options[Key]["sub"];
							}
							
							if(typeof this.Options[Key]["round"] == "number" && typeof Value == "number")
							{
								Value = setRound(Value, this.Options[Key]["round"]);
							}
							
							if((typeof this.Options[Key]["floor"] == "number" || typeof this.Options[Key]["floor"] == "boolean") && typeof Value == "number")
							{
								if(this.Options[Key]["floor"]) Value = setFloor(Value);
							}
							
							if((typeof this.Options[Key]["inc"] == "number" || typeof this.Options[Key]["inc"] == "boolean") && typeof Value == "number")
							{
								if(this.Options[Key]["inc"]) Value++;
							}
							
							if((typeof this.Options[Key]["dec"] == "number" || typeof this.Options[Key]["dec"] == "boolean") && typeof Value == "number")
							{
								if(this.Options[Key]["dec"]) Value--;
							}
							
							if(typeof this.Options[Key]["getBit"] == "number" && typeof Value == "number" && typeof getBit == "function")
							{
								Value = getBit(Value, this.Options[Key]["getBit"]);
							}
							
							if((typeof this.Options[Key]["not"] == "number" || typeof this.Options[Key]["not"] == "boolean") && typeof Value == "number")
							{
								Value = ~Value;
							}
							
							if(typeof this.Options[Key]["andMask"] == "number" && typeof Value == "number")
							{
								if(this.Options[Key]["andMask"]) Value = (Value & this.Options[Key]["andMask"]);
							}
							
							if(typeof this.Options[Key]["orMask"] == "number" && typeof Value == "number")
							{
								if(this.Options[Key]["orMask"]) Value = (Value | this.Options[Key]["orMask"]);
							}
							
							if(typeof this.Options[Key]["xorMask"] == "number" && typeof Value == "number")
							{
								if(this.Options[Key]["xorMask"]) Value = (Value ^ this.Options[Key]["xorMask"]);
							}
							
							if((typeof this.Options[Key]["toIsoTime"] == "number" || typeof this.Options[Key]["toIsoTime"] == "boolean") && typeof Value == "number")
							{
								if(this.Options[Key]["toIsoTime"]) Value = (new Date()).SecToIsoTime(Value-0);
							}
							
							if(typeof this.Options[Key]["bySetpoint"] != "undefined" && typeof this.Options[Key]["SetpointAlg"] == "string")
							{
								BeforeValue = Value;
								Value = this.bySetpoint(this.Options[Key]["SetpointAlg"], this.Options[Key]["bySetpoint"], Value);
								
								if(typeof this.Options[Key]["SetpointNoMod"] == "number" || typeof this.Options[Key]["SetpointNoMod"] == "boolean")
								{
									if(this.Options[Key]["SetpointNoMod"])
									{
										if(!Value) continue;
										Value = BeforeValue;
									}
								}
							}
							
							BeforeValue = Value;
							
							if(typeof this.Options[Key]["byRiseEdge"] == "number" || typeof this.Options[Key]["byRiseEdge"] == "boolean")
							{
								if(this.Options[Key]["byRiseEdge"])
								{
									if(this.isEqPrev(Key, Value)) continue;
								}
							}
							this.fixValue(Key, Value, RawValue);
							
							if(typeof this.Options[Key]["fromArray"] != "undefined")
							{
								Value = this.fromArray(this.Options[Key]["fromArray"], Value, DefaultValue);
							}
							
							//DATA FLOW CONTROL
							
							if(typeof this.Options[Key]["Break"] == "number" || typeof this.Options[Key]["Break"] == "boolean")
							{
								if(this.Options[Key]["Break"] && BreakFlow) continue;
							}
							
							if(typeof this.Options[Key]["setLocReg"] == "string")
							{
								this.setLocReg(this.Options[Key]["setLocReg"], Value);
							}
							
							if(typeof this.Options[Key]["setLocCntr"] == "string" && typeof this.Options[Key]["LocCntrAlg"] == "string")
							{
								this.setLocCntr(this.Options[Key]["setLocCntr"], this.Options[Key]["LocCntrAlg"], Value, LocCntrMin, LocCntrMax);
							}
							
							if(typeof this.Options[Key]["setNode"] == "string" && typeof this.Options[Key]["NodeAlg"] == "string")
							{
								if(typeof this.Options[Key]["NodeAttr"] == "string")
									 this.setNode(Nodes[Key], this.Options[Key]["NodeAlg"], this.Options[Key]["NodeAttr"], Value, Key);
								else this.setNode(Nodes[Key], this.Options[Key]["NodeAlg"], null, Value, Key);
							}
							
							if(typeof this.Options[Key]["execFunc"] == "function")
							{
								this.Options[Key]["execFunc"](this.Options[Key], Data_in, DataKey, Value, BeforeValue);
							}
							
							if(typeof this.Options[Key]["rstLocCntr"] == "string")
							{
								this.rstLocCntr(this.Options[Key]["rstLocCntr"]);
							}
							
							if(typeof this.Options[Key]["rstLocReg"] == "string")
							{
								this.setLocReg(this.Options[Key]["rstLocReg"], null);
							}
						}
					}
				}
				
				if(!this.RefreshFirstIter) this.RefreshFirstIter = true;
			}
		};

	/*
	@brief  Public Method: Refresh HMI for LocReg.
	@param  None.
	@return None.
	*/
	this.refreshLocReg = function()
		{
			this.refresh(LocReg);
		};

	/*
	@brief  Public Method: Copy options from source list to new container.
	@param  SrcIn - source. [OBJECT]
	@return New list with copy of source options.	[OBJECT]
	*/
	this.copyOptionsFrom = function(SrcIn)
		{
			var Res = {	};

			if(typeof SrcIn == "object")
			{
				if(SrcIn)
				{
					for(var key in SrcIn)
					{
						Res[key] = SrcIn[key];
					}
				}
			}

			return (Res);
		};

	/*
	@brief  Public Method: Set Options from source list.
	@param  NodeIdIn - Node ID (prefix+ID);	[STRING]
	@param  IdIn - ID without prefix or NULL; [STRING || NUMBER || NULL]
	@param  OptionsIn - source list of options (array of objects); [ARRAY]
	@return The number of copied options. [NUMBER]
	@detailed
		      OptionsIn = [ { NodeID:#, ... }, ... ] will copy to Options as is

			if available "NodeAttr" (as string) argument in the source list, then
				Key (to Options) = NodeIdIn + OptionsIn[i]["NodeAttr"]
			otherwise
				Key (to Options) = NodeIdIn

			If not available "NodeID" argument in the source list, then:
				Options[Key]["NodeID"] = NodeIdIn

			if not available "DataKey" argument in the source list:
				if available "PreDataKey" in the source list and set IdIn as "string" or "number":
					Options[Key]["DataKey"] = OptionsIn[i]["PreDataKey"]+IdIn
				otherwise
					Options[Key]["DataKey"] = NodeIdIn - otherwise
	*/
	this.setOptionsFrom = function(NodeIdIn, IdIn, OptionsIn)
		{
			var Res = 0;

			if(HaveFunc && typeof NodeIdIn == "string" && typeof OptionsIn == "object")
			{
				if(is_array(OptionsIn))
				{
					var Key         = null;
					var HasNodeID   = false;
					var HasDataKey  = false;
					var HasNodeAttr = false;

					if(!this.Options) this.Options = { };

					for(var i=0; i<OptionsIn.length; i++)
					{
						if(typeof OptionsIn[i] == "object")
						{
							if(OptionsIn[i])
							{
								HasNodeID = false;
								if(typeof OptionsIn[i]["NodeID"] == "string")
								{
									if(OptionsIn[i]["NodeID"].length) HasNodeID = true;
								}

								HasDataKey = false;
								if(typeof OptionsIn[i]["DataKey"] == "string")
								{
									if(OptionsIn[i]["DataKey"].length) HasDataKey = true;
								}

								HasNodeAttr = false;
								if(typeof OptionsIn[i]["NodeAttr"] == "string")
								{
									if(OptionsIn[i]["NodeAttr"].length) HasNodeAttr = true;
								}

								Key = ((HasNodeAttr == true) ? (NodeIdIn+OptionsIn[i]["NodeAttr"]): NodeIdIn);
								this.Options[Key] = this.copyOptionsFrom(OptionsIn[i]);

								if(!HasNodeID)
								{
									this.Options[Key]["NodeID"] = NodeIdIn;
								}

								if(!HasDataKey)
								{
									this.Options[Key]["DataKey"] = ((typeof OptionsIn[i]["PreDataKey"] == "string" && (typeof IdIn == "number" || typeof IdIn == "string")) ? (OptionsIn[i]["PreDataKey"]+IdIn) : NodeIdIn);
								}

								Res++;
							}
						}
					}
				}
			}

			return (Res);
		};

	/*
	@brief  Public Method: Set values by default.
	@param  Keys_in  - list of keys to Options. [ARRAY || NULL]
	@return None.
	@detailed
		      If Keys_in is NULL, then will use all Options.
	*/
	this.setDefault = function(Keys_in)
		{
			var Data = ((typeof Keys_in != "undefined") ? this.getDefaultValues(Keys_in) : null);
			this.refresh(Data);
		};

	/*
	@brief  Public Method: Set values by default for items with Old-values.
	@param  Stamp_in - master Unix TimeStamp or NULL. [NUMBER || NULL]
	@return None.
	@detailed
		      If Stamp_in is not number, then will use Current TimeStamp.
		      If option stamp < Stamp_in, then is Old-value.
	*/
	this.setDefaultForOld = function(Stamp_in)
		{
			var Keys = this.getKeysForOld(Stamp_in);
			var Data = this.getDefaultValues(Keys);
			this.refresh(Data);
		};

	/*
	@brief  Public Method: Init.
	@param  None.
	@return None.
	*/
	this.init = function()
		{
			Nodes = {};
			G_HMI__BITLAMPBLINK_NODES = {};

			if(HaveFunc && typeof this.Options == "object")
			{
				if(this.Options)
				{
					for(var key in this.Options)
					{
						if(typeof this.Options[key] == "object")
						{
							if(this.isOption(this.Options[key]))
							{
								Nodes[key] = $(("#" + ((typeof this.Options[key]["setNode"] == "string") ? this.Options[key]["setNode"] : key)));
								if(this.Options[key]["NodeAlg"] == "BitLampBlink")
								{
									G_HMI__BITLAMPBLINK_NODES[key] = { Node: Nodes[key], Value: false };
								}
								
								if(typeof this.Options[key]["setLocReg"] == "string")
								{
									if(this.Options[key]["setLocReg"].length) LocReg[this.Options[key]["setLocReg"]] = null;
								}
								
								if(typeof this.Options[key]["setLocCntr"] == "string")
								{
									if(this.Options[key]["setLocCntr"].length) LocReg[this.Options[key]["setLocCntr"]] = 0;
								}
							}
						}
					}
				}
			}
		};

	//Constructor

	HaveFunc  = (typeof is_empty == "function" && typeof check_object == "function" && typeof replace_sub_string == "function" && typeof is_array == "function");
	G_HMI__TIMER_BLINK_ID = setInterval(HMI_TimerBlinkHandler, G_HMI__TIMER_BLINK_PERIOD);
}


//** METHODS IN THE PROTOTYPE


//** CLASS INHERITANCE

