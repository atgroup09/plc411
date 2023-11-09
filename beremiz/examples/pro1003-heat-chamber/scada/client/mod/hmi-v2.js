/* JAVASCRIPT DOCUMENT
*  UTF-8
*/

/* Module: HMI (v.2).
*  Class.
*
*  Copyright (C) 2016-2023  ATgroup09 (atgroup09@gmail.com)
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
*  2022-06-15
*   + Option "Setpoint"
*
*  2020-05-21
*   ~ Option "Type" is not required
*
*  2020-05-04
*   ~ Offset    > HMI-preprocessing
*   ~ Round     > HMI-preprocessing
*   + Floor     > HMI-preprocessing
*   + Inc       > HMI-preprocessing
*   + Dec       > HMI-preprocessing
*   + SetLocReg > HMI-postprocessing
*   + AddLocReg > HMI-postprocessing
*   + LocReg   (local object)
*
*  2019-06-28
*   + IncAfter
*   + DecAfter
*
*  2019-06-24
*   + Type::"IsoTime"
*/


/* REQUIRED LIB/MOD
*
*	+ lib/js/types/types.js
*	+ lib/js/bit.js
*	+ lib/js/jquery.min.js
*	+ lib/js/date.format.js
*
*/

/* Main model:
*
*      DATA > HMI-processor > WEB-CONTENT
*
*
*  DATA is a list (associative array) of values [OBJECT]
*
*      DATA = { key:value, ... }
*          where, key - key to value [STRING]
*               value - value [STRING || NUMBER || BOOLEAN || NULL]
*
*      ex.: DATA = { WsDI:0, Pres:0, Tres:0, Pret:0, Tret:0, Pext:0, Tloc:0, Name:"Plc", Stamp:1546721099 }
*
*
*  HMI-processor is object of class HMI, that is configured to work with DATA and WEB-CONTENT [OBJECT]
*
*      HMI.Options is list (associative array) of options [OBJECT]
*
*      HMI.Options[Key] = {  key:options, ... }
*          where, key - key to value of option [STRING]
*             options - list (associative array) of options [OBJECT]
*
*      ex.: HMI.Options = { PowerState: { DataKey:"WsDI", Type:"BitLamp", Bit:9 },
*                           PowerAlarm: { DataKey:"WsDI", Type:"BitLampBlink", Bit:9, Inverted:true },
*                             MainTemp: { DataKey:"Temp", Type:"Number", Offset:10, Round:1 },
*						     State: { DataKey:"State", Type:"ArrayIDx", Arr:G_RES[G_LANG]["States"], NodeID:"State" },
*                                Func: { DataKey:"WsDI", Type:"Func", AndMask:1, RiseEdge:true, Func:onBitFuncLog, NodeID:"MainCase" }
*						}

*  Supported options by groups:
*
*      (!) is required options!
*
*      DefaultValue - value by default [STRING || NUMBER || BOOLEAN || NULL]
*                     = typeof "number|boolean|null" for Type "BitLamp", "BitLampBlink"
*                     = typeof "string|number|null" for Type "Text", "String"
*                     = typeof "string|number" for Type "Number"
*                     = typeof "string|number" for Type "ArrayIDx" (between 0 and Arr.length if Arr is common array, string as key if Arr is associative array)
*
*  -- link to DATA
*
*      (!) DataKey - key to list of DATA or NULL. [STRING || NULL]
*
*              Arr - link to resource [STRING || NUMBER || BOOLEAN || OBJECT || ARRAY || NULL ]
*                    * for execution type "ArrayIDx"
*                    * DATA-value is used as key (Arr[DATA-value])
*                    * ex.: Arr:G_RES[G_LANG]["States"]
*
*  -- link to WEB-CONTENT
*
*           NodeID - ID of Node (value of attr. "id") or NULL [STRING || NULL]
*				   * if NULL, then used HMI.Options[Key] as ID or Node
*                    * the ID is required to update web content (see option Type).
*
*         NodeAttr - name of Node-attribute to set DATA-value (not for "BitLamp", "BitLampBlink")	[STRING]
*				   = main attributes (class, id, src ...)
*				   = "top" (offset node position, px)
*				   = "left" (offset node position, px)
*
*  -- link to functions
*
*             Func - link to function [FUNCTION]
*                    = function(Node_in, Value_in, OptKey_in, DataKey_in, Data_in)
*                    * where Node_in - target node, Value_in - value from Data_in by DataKey_in, OptKey_in - key to HMI-options, Key_in - key to Data_in, Data_in - data;
*                    * return true|false.
*
*           BitFunc - link to function [FUNCTION]
*                    = function(Node_in, Value_in, OptKey_in, DataKey_in, Data_in)
*                    * where Node_in - target node, Value_in - value from Data_in by DataKey_in, OptKey_in - key to HMI-options, Key_in - key to Data_in, Data_in - data;
*                    * return true|false.
*                    * for execution type "BitFunc"
*
*
*  -- link to local registers
*
*           LocReg - key to Local register [STRING]
*                    = if set, then will be created local register LocReg[LocReg] on init. HMI
*                    * value of a local register may be modified from any DATA-items (use attributes: SetLocReg, AddLocReg in DATA-item options)
*                    * to refresh HMI linked with Local registers, use method: refreshLocReg()
*
*
*  -- HMI-preprocessing
*
*          Round - rounding a floating point number [NUMBER]
*                   = the number of digits after decimal point (>= 0)
*                   ** Value = round(DATA-value, Round)
*
*         Offset - offset of floating point [NUMBER]
*                   = decimal point offset to right (>= 0)
*                   ** Value = DATA-value/PreOffset
*
*          Floor - True to rounding a floating point number to down [BOOLEAN]
*                   ** Value = floor(DATA-value)
*
*             Inc - increment value (0 by default) [NUMBER]
*                   * for numeric values
*				    * Value+Inc
*
*            Dec - decrement value (0 by default) [NUMBER]
*                   * for numeric values
*				    * Value-Dec
*
*        Inverted - True to invert a bit in DATA-value [BOOLEAN]
*                   * for numeric values
*
*             Bit - extract bit from DATA-value and use it as value. [NUMBER]
*                   = 0 ... 15
*                   * for numeric values
*
*			Not - True to invert all bits of DATA-value [BOOLEAN]
*                   * for numeric values
*
*         AndMask - AND bit-mask [NUMBER]
*                   * for numeric values
*
*          OrMask - OR bit-mask [NUMBER]
*                   * for numeric values
*
*         XorMask - XOR bit-mask [NUMBER]
*                   * for numeric values
*
*  -- HMI-postprocessing
*
*        NotAfter - True to invert all bits of DATA-value [BOOLEAN]
*                   * for numeric values
*
*        IncAfter - increment value (0 by default) [NUMBER]
*                   * for numeric values
*				    = Value+= IncAfter
*
*        DecAfter - decrement value (0 by default) [NUMBER]
*                   * for numeric values
*				    = Value-= DecAfter
*
*        Setpoint - Compare Value and Setpoint [NUMBER]
*                   * for numeric values
*				    = Value = ( Value == Setpoint ? 1 : 0 )
*
*         BoolNum - True to convert value from any type to boolean state number (0 or 1). [BOOLEAN]
*
*        SetLocReg - set result value to Local register [STRING]
*                   = key to Local register
*                   * for any types of value!
*                   ** LocReg[SetLocReg] = Value
*
*        AddLocReg - add result value to Local register [STRING]
*                   = key to Local register
*                   * for numeric values
*                   ** LocReg[AddLocReg]+= Value
*
*        RiseEdge - True to compare of new value and a previous [BOOLEAN]
*                   = if values are match, then end
*                   = if values are not match, then start executing
*
*
*  -- HMI-executing
*
*        (!) Type - type of final execution [STRING]
*                    = "BitLamp" - show/hide Node by boolean state of DATA-value
*                                  1) Node.show() || Node.hide()
*                                     * required options: NodeID
*                                  2) execute function that is linked with option Func (or BitFunc), DATA-value used as input argument of the function
*                                     * required options: Func or BitFunc
*                    = "BitLampBlink" - blink/hide Node by boolean state of DATA-value
*                                  1) Node.show() || Node.hide()
*                                     * required options: NodeID
*                                  2) execute function that is linked with option Func (or BitFunc), DATA-value used as input argument of the function
*                                     * required options: Func or BitFunc
*                    = "Text" or "String" - convert DATA-value to string and set it into Node
*                                  1) convert value to string
*                                  2) Node.text(Value) or Node.attr(AttrName, Value)
*                                     * required options: NodeID (and NodeAttr)
*                                  3) execute function that is linked with option Func (or BitFunc), DATA-value used as input argument of the function
*                                     * required options: Func or BitFunc
*                    = "Number" - convert DATA-value to number and set it into Node
*                                  1) convert value to number
*                                  2) processing the number
*                                     a) offset of floating point
*                                       * required options: Offset
*                                     b) rounding of floating point
*                                       * required options: Round
*                                  3) Node.text(Value) or Node.attr(AttrName, Value)
*                                     * required options: NodeID (and NodeAttr)
*                                  4) execute function that is linked with option Func (or BitFunc), DATA-value used as input argument of the function
*                                     * required options: Func or BitFunc
*                    = "ArrayIDx" - get value from resource and set it into Node
*                                  1) get value from resource that is linked with option Arr by DATA-value as key (Arr[DATA-value])
*                                     * required options: Arr
*                                  2) Node.text(Value) or Node.attr(AttrName, Value)
*                                     * required options: NodeID (and NodeAttr)
*                                  3) execute function that is linked with option Func (or BitFunc), DATA-value used as input argument of the function
*                                     * required options: Func or BitFunc
*                    = "Func" - execute function for any DATA-value
*                                  1) execute function that is linked with option Func, DATA-value used as input argument of the function
*                                     * required options: Func or BitFunc
*                    = "BitFunc" - execute function by True boolean state of DATA-value
*                                  1) execute function that is linked with option BitFunc, DATA-value used as input argument of the function
*                                     * required options: BitFunc
*                                     * only for True boolean state of DATA-value
*                   = "IsoTime" - convert DATA-value (seconds) to string of time in ISO-format ("HH:MM:ss")
*                                  1) convert value to number
*                                  2) convert the number into string of time
*                                  * maximum DATA-value is 1327104000
*
*          Reset - True to reset value after HMI-executing [BOOLEAN]
*                  * if option contain attribute "LocReg", then LocReg[LocReg] will be reset too
*                  ** Value = null
*                  ** LocReg[LocReg] = null
*
*
*  -- HMI-result (read-only)
*     * set automatically!
*
*           Stamp - time of last execution (Unix TimeStamp) [NUMBER]
*           Value - value of last execution [ANY]
*
*
*
*  HTML-Node for Type "BitLamp", "BitLampBlink":
*
*      <img id="MyBitLamp" src="images/red.png" src0="images/red.png" src1="images/green.png" />
*
*        * attr. "src0" is path to image, what will be show for value: 0 || false || NULL
*        * attr. "src1" is path to image, what will be show for value: > 0 || true || NOT NULL
*
*
*  Start HMI-processing:
*
*      HMI.refresh(DATA);
*      HMI.refreshLocReg();
*
*/

/*  Stages of HMI-processing:
*
*		Value = null
*
*		Value = DATA[DataKey]
*
*		if Value is number
*		{
*			if(Bit:number)
*			{
*				if(Inverted) Value = invertBit(Value, Bit)
*				Value = getBit(Value, Bit)
*			}
*
*			if(Not:true) Value = ~Value;
*
*			if(AndMask:number) Value = Value & AndMask;
*
*			if(OrMask:number) Value = Value | AndMask;
*
*			if(XorMask:number) Value = Value ^ XorMask;
*
*			if(NotAfter:true) Value = ~Value;
*		}
*
*		if(BoolNum:true) Value = ((toBool(Value)) ? 1 : 0)
*
*		if(RiseEdge:true)
*		{
*			if(ValuePrev == Value) exit
*		}
*
*		if(Type:"BitLamp" or "BitLampBlink")
*		{
*			refreshBitLamp(NODE, Value, DefaultValue)
*		}
*		else if(Type:"Text" or "String")
*		{
*			refreshText(NODE, NodeAttr, Value, DefaultValue)
*		}
*		else if(Type:"Number")
*		{
*			refreshNumber(NODE, NodeAttr, Value, Offset, Round, DefaultValue)
*		}
*		else if(Type:"ArrayIDx")
*		{
*			refreshArrayIDx(NODE, NodeAttr, Value, Arr, DefaultValue)
*		}
*
*		if(BitFunc:function)
*		{
*			if(toBool(Value)) BitFunc(NODE, Value, key, DataKey, DATA)
*		}
*		else if(Func:function)
*		{
*			if(Type:"BitFunc")
*			{
*				if(!toBool(Value)) Func(NODE, Value, key, DataKey, DATA)
*			}
*			else
*			{
*				Func(NODE, Value, key, DataKey, DATA)
*			}
*		}
*
*		Stamp = CURRENT_TIMESTAMP
*		PrevValue = Value
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
				if(typeof G_HMI__BITLAMPBLINK_NODES[key]["Node"] == "object" && typeof G_HMI__BITLAMPBLINK_NODES[key]["Value"] == "boolean")
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

	//* object options (associative array)	[OBJECT]
	this.Options = { };

	//* value by default (global)	[STRING || NUMBER || NULL]
	this.DefaultValue = "---";

	//* True to use previous value if no data, False to use DefaultValue [BOOLEAN]
	this.UsePrevValue = true;


	//Private properties

	//* nodes (associative array)	[OBJECT]
	var Nodes = { };

	//* local registers (associative array)	[OBJECT]
	var LocReg = { };

	//* status of checking the functions		[BOOLEAN]
	var HaveFunc = false;


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
	@brief  Public Method: Get list of default values.
	@param  Keys_in - array of keys or NULL.	[ARRAY || NULL]
	@return list of default values.	[OBJECT]
	@detailed
		      If Keys_in is NULL, then will use all Options.
	*/
	this.getDefaultValues = function(Keys_in)
		{
			var Values = { };
			var Keys   = null;
			var Key    = null;

			if(typeof Keys_in != "undefined")
			{
				if(is_array(Keys_in)) Keys = Keys_in;
			}

			if(!Keys) Keys = this.getKeys();

			for(var i=0; i<Keys.length; i++)
			{
				Key = Keys[i];

				if(this.isOptionByKey(Key))
				{
					if(typeof this.Options[Key]["DefaultValue"] != "undefined") Values[Key] = this.Options[Key]["DefaultValue"];
				}
			}

			return (Values);
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
	@brief  Public Method: Convert value to bool-type.
	@param  Value_in - value. [NUMBER || STRING || OBJECT || BOOLEAN || NULL]
	@return True || False.	[BOOLEAN]
	@detailed
			  If Value_in is:
   		      0 || empty string || false || NULL  - false,
		    > 0 || string       || true  || !NULL - true
	*/
	this.toBool = function(Value_in)
		{
			if(typeof Value_in == "object" || typeof Value_in == "boolean" || typeof Value_in == "number")
			{
				if(Value_in) return (true);
			}
			else if(typeof Value_in == "string")
			{
				if(Value_in.length > 0) return (true);
			}

			return (false);
		};

	/*
	@brief  Public Method: Set node attribute.
	@param  Node_in - node; [OBJECT]
	@param  NodeAttr_in - name of attribute or NULL; [STRING]
	@param  Value_in - value. [NUMBER || STRING || NULL]
	@return None.
	*/
	this.setNodeAttr = function(Node_in, NodeAttr_in, Value_in)
		{
			if(typeof Node_in == "object" && typeof NodeAttr_in == "string")
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
					else
					{
						Node_in.attr(NodeAttr_in, Buff);
					}
				}
			}
		};

	/*
	@brief  Public Method: Refresh target item of Type "Text", "String".
	@param  Node_in  - node; [OBJECT]
	@param  NodeAttr_in - name of attribute or NULL; [STRING || NULL]
	@param  Value_in - value; [NUMBER || STRING || NULL]
	@param  DefValue_in - value by default. [NUMBER || STRING]
	@return True if refresh done, otherwise - False.	[BOOLEAN]
	*/
	this.refreshText = function(Node_in, NodeAttr_in, Value_in, DefValue_in)
		{
			if(HaveFunc && typeof Node_in == "object")
			{
				if(Node_in)
				{
					var Buff = ((typeof DefValue_in == "number" || typeof DefValue_in == "string") ? ("" + DefValue_in) : this.DefaultValue);

					if(typeof Value_in == "number" || typeof Value_in == "string")
					{
						Buff = ("" + Value_in);
					}

					if(typeof NodeAttr_in == "string")
					{
						this.setNodeAttr(Node_in, NodeAttr_in, Buff);
					}
					else
					{
						Node_in.text(Buff);
					}

					return (true);
				}
			}

			return (false);
		};

	/*
	@brief  Public Method: Refresh target item of Type "BitLamp".
	@param  Node_in  - node; [OBJECT]
	@param  Value_in - value; [NUMBER || STRING || BOOLEAN || NULL]
	@param  BlinkMode_in - true if Type is "BitLampBlink", otherwise - false; [BOOLEAN]
	@param  DefValue_in - value by default. [NUMBER || STRING]
	@return BitLamp state.	[BOOLEAN]
	*/
	this.refreshBitLamp = function(Node_in, Value_in, BlinkMode_in, DefValue_in)
		{
			var fl = false;

			if(HaveFunc && typeof Node_in == "object")
			{
				if(Node_in)
				{
					var Value     = ((typeof DefValue_in == "number" || typeof DefValue_in == "string" || typeof DefValue_in == "boolean") ? DefValue_in : false);
					var BlinkMode = ((typeof BlinkMode_in == "boolean") ? BlinkMode_in : false);
					var Src0      = Node_in.attr("src0");	//attr for FALSE state
					var Src1      = Node_in.attr("src1");	//attr for TRUE state
					var fl        = this.toBool(Value_in);

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
	@brief  Private Method: Set decimal pointer offset to left for numeric value.
	@param  Value_in  - value. [NUMBER || STRING]
	@param  Offset_in - decimal point offset to right (>=0). [NUMBER]
	@return New value. [NUMBER]
	*/
	var setOffset = function(Value_in, Offset_in)
		{
			var Value = normFloatPoint(Value_in);

			if(typeof Offset_in == "number")
			{
				if(Offset_in > 0) Value = (Value/Offset_in);
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
	@brief  Public Method: Add value to Local register.
	@param  LocRegKey_in - register key. [STRING]
	@param  Value_in - value. [NUMBER || STRING]
	@return None.
	*/
	this.addLocReg = function(LocRegKey_in, Value_in)
		{
			if(typeof LocRegKey_in == "string" && typeof Value_in == "number")
			{
				if(LocRegKey_in.length)
				{
					if(typeof LocReg[LocRegKey_in] != "undefined")
					{
						LocReg[LocRegKey_in]+= Value_in;
					}
				}
			}
		};

	/*
	@brief  Public Method: Refresh target item of Type "Number".
	@param  Node_in  - node; [OBJECT]
	@param  NodeAttr_in - name of attribute or NULL; [STRING || NULL]
	@param  Value_in - value; [NUMBER || STRING || NULL]
	@param  DefValue_in - value by default. [NUMBER || STRING]
	@return True if refresh done, otherwise - False.	[BOOLEAN]
	*/
	this.refreshNumber = function(Node_in, NodeAttr_in, Value_in, DefValue_in)
		{
			if(HaveFunc && typeof Node_in == "object")
			{
				if(Node_in)
				{
					var Buff = this.DefaultValue;

					if(typeof Value_in == "number" || typeof Value_in == "string")
					{
						Buff = "" + normFloatPoint(Value_in);
					}
					else if(typeof DefValue_in == "number" || typeof DefValue_in == "string")
					{
						Buff = ("" + DefValue_in);
					}

					if(typeof NodeAttr_in == "string")
					{
						this.setNodeAttr(Node_in, NodeAttr_in, Buff);
					}
					else
					{
						Node_in.text(Buff);
					}

					return (true);
				}
			}

			return (false);
		};

	/*
	@brief  Public Method: Refresh target item of Type "ArrayIDx".
	@param  Node_in  - node; [OBJECT]
	@param  NodeAttr_in - name of attribute or NULL; [STRING || NULL]
	@param  Key_in - key to Arr; [NUMBER || STRING]
	@param  Arr_in - array; [ARRAY]
	@param  DefValue_in - value by default.	[NUMBER || STRING || NULL]
	@return True if refresh done, otherwise - False.	[BOOLEAN]
	*/
	this.refreshArrayIDx = function(Node_in, NodeAttr_in, Key_in, Arr_in, DefValue_in)
		{
			if(HaveFunc && typeof Node_in == "object")
			{
				if(Node_in)
				{
					var Buff       = null;
					var BufThisDef = false;

					if(typeof DefValue_in == "string" || typeof DefValue_in == "number")
					{
						Buff = ("" + DefValue_in);
					}
					else
					{
						Buff = this.DefaultValue;
						BufThisDef = true;
					}

					if(typeof Arr_in != "undefined" && (typeof Key_in == "string" || typeof Key_in == "number"))
					{
						if(typeof Arr_in[Key_in] == "string" || typeof Arr_in[Key_in] == "number")
						{
							Buff = Arr_in[Key_in];
						}
					}

					if(typeof NodeAttr_in == "string")
					{
						if((NodeAttr_in == "class" && !BufThisDef) || NodeAttr_in != "class") this.setNodeAttr(Node_in, NodeAttr_in, Buff);
					}
					else
					{
						Node_in.text(Buff);
					}

					return (true);
				}
			}

			return (false);
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
				var Result   = false;
				var RawValue = null;
				var Value    = null;
				var DataKey  = null;
				var DefValue = null;
				var Attr     = null;
				var Inverted = false;

				for(var Key in Nodes)
				{
					if(typeof this.Options[Key] == "object")
					{
						if(this.isOption(this.Options[Key]))
						{
							DefValue = ((typeof this.Options[Key]["DefaultValue"] != "undefined") ? this.Options[Key]["DefaultValue"] : null);
							RawValue = ((this.UsePrevValue && typeof this.Options[Key]["RawValue"] != "undefined") ? this.Options[Key]["RawValue"] : DefValue);
							DataKey  = this.Options[Key]["DataKey"];
							Attr     = ((typeof this.Options[Key]["NodeAttr"] == "string") ? this.Options[Key]["NodeAttr"] : null);
							Inverted = ((typeof this.Options[Key]["Inverted"] == "boolean") ? this.Options[Key]["Inverted"] : false);

							if(typeof Data_in == "object")
							{
								if(Data_in)
								{
									if(typeof Data_in[DataKey] != "undefined") RawValue = Data_in[DataKey];
								}
							}

							Value = RawValue;

							if(typeof Value == "number" || typeof Value == "string")
							{
								if(typeof this.Options[Key]["Offset"] == "number")
								{
									if(this.Options[Key]["Offset"] > 0) Value = setOffset(Value, this.Options[Key]["Offset"]);
								}

								if(typeof this.Options[Key]["Round"] == "number")
								{
									Value = setRound(Value, this.Options[Key]["Round"]);
								}

								if(typeof this.Options[Key]["Floor"] == "boolean")
								{
									if(this.Options[Key]["Floor"]) Value = setFloor(Value);
								}
							}

							if(typeof Value == "number")
							{
								if(typeof this.Options[Key]["Inc"] == "number")
								{
									if(this.Options[Key]["Inc"] != 0) Value+= this.Options[Key]["Inc"];
								}

								if(typeof this.Options[Key]["Dec"] == "number")
								{
									if(this.Options[Key]["Dec"] != 0) Value-= this.Options[Key]["Dec"];
								}

								if(typeof this.Options[Key]["Bit"] == "number")
								{
									Value = ((Inverted && typeof invertBit == "function") ? invertBit(Value, this.Options[Key]["Bit"]) : Value);
									Value = ((typeof getBit == "function") ? getBit(Value, this.Options[Key]["Bit"]) : 0);
								}

								if(typeof this.Options[Key]["Not"] == "boolean")
								{
									if(this.Options[Key]["Not"]) Value = ~Value;
								}

								if(typeof this.Options[Key]["AndMask"] == "number")
								{
									Value = (Value & this.Options[Key]["AndMask"]);
								}

								if(typeof this.Options[Key]["OrMask"] == "number")
								{
									Value = (Value | this.Options[Key]["OrMask"]);
								}

								if(typeof this.Options[Key]["XorMask"] == "number")
								{
									Value = (Value ^ this.Options[Key]["XorMask"]);
								}

								if(typeof this.Options[Key]["NotAfter"] == "boolean")
								{
									if(this.Options[Key]["NotAfter"]) Value = ~Value;
								}

								if(typeof this.Options[Key]["IncAfter"] == "number")
								{
									Value+= this.Options[Key]["IncAfter"];
								}

								if(typeof this.Options[Key]["DecAfter"] == "number")
								{
									Value-= this.Options[Key]["DecAfter"];
								}
							}

							if(typeof this.Options[Key]["BoolNum"] == "boolean")
							{
								if(this.Options[Key]["BoolNum"]) Value = ((this.toBool(Value)) ? 1 : 0);
							}
							
							if(typeof this.Options[Key]["Setpoint"] != "undefined")
							{
								Value = ((Value == this.Options[Key]["Setpoint"]) ? 1 : 0);
							}
							
							if(typeof this.Options[Key]["SetLocReg"] == "string")
							{
								this.setLocReg(this.Options[Key]["SetLocReg"], Value);
							}

							if(typeof this.Options[Key]["AddLocReg"] == "string")
							{
								this.addLocReg(this.Options[Key]["AddLocReg"], Value);
							}

							if(typeof this.Options[Key]["RiseEdge"] == "boolean")
							{
								if(this.Options[Key]["RiseEdge"])
								{
									if(this.isEqPrev(Key, Value)) continue;
								}
							}

							if(typeof this.Options[Key]["Type"] == "string")
							{
								switch(this.Options[Key]["Type"])
								{
									case "BitLamp":
									case "BitLampBlink":

										Result = ((this.Options[Key]["Type"] == "BitLampBlink") ? this.refreshBitLamp(Nodes[Key], Value, true, DefValue) : this.refreshBitLamp(Nodes[Key], Value, false, DefValue));
										if(typeof G_HMI__BITLAMPBLINK_NODES[Key] != "undefined") G_HMI__BITLAMPBLINK_NODES[Key]["Value"] = Result;
										break;

									case "Text":
									case "String":

										Result = this.refreshText(Nodes[Key], Attr, Value, DefValue);
										break;

									case "Number":

										Result = this.refreshNumber(Nodes[Key], Attr, Value, DefValue);
										break;

									case "ArrayIDx":

										if(typeof this.Options[Key]["Arr"] != "undefined")
										{
											Result = this.refreshArrayIDx(Nodes[Key], Attr, Value, this.Options[Key]["Arr"], DefValue);
										}
										break;

									case "IsoTime":

										Value = (new Date()).SecToIsoTime(Value-0);
										Result = this.refreshText(Nodes[Key], Attr, Value, DefValue);
								}
							}

							if(typeof this.Options[Key]["BitFunc"] == "function")
							{
								if(this.toBool(Value)) Result = this.Options[Key]["BitFunc"](Nodes[Key], Value, Key, DataKey, Data_in);
							}
							else if(typeof this.Options[Key]["Func"] == "function")
							{
								if(this.Options[Key]["Type"] == "BitFunc")
								{
									if(this.toBool(Value)) Result = this.Options[Key]["Func"](Nodes[Key], Value, Key, DataKey, Data_in);
								}
								else
								{
									Result = this.Options[Key]["Func"](Nodes[Key], Value, Key, DataKey, Data_in);
								}
							}

							if(typeof this.Options[Key]["Reset"] == "boolean")
							{
								if(this.Options[Key]["Reset"])
								{
									Value = null;
									if(typeof this.Options[Key]["LocReg"] == "string") this.setLocReg(this.Options[Key]["LocReg"], Value);
								}
							}

							this.fixValue(Key, Value, RawValue);
						}
					}
				}
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
								Nodes[key] = $(("#" + ((typeof this.Options[key]["NodeID"] == "string") ? this.Options[key]["NodeID"] : key)));
								if(this.Options[key]["Type"] == "BitLampBlink")
								{
									G_HMI__BITLAMPBLINK_NODES[key] = { Node: Nodes[key], Value: false };
								}

								if(typeof this.Options[key]["LocReg"] == "string")
								{
									if(this.Options[key]["LocReg"].length) LocReg[this.Options[key]["LocReg"]] = null;
								}
							}
						}
					}
				}
			}
		};

	//Constructor

	HaveFunc = (typeof is_empty == "function" && typeof check_object == "function" && typeof replace_sub_string == "function" && typeof is_array == "function");
	G_HMI__TIMER_BLINK_ID = setInterval(HMI_TimerBlinkHandler, G_HMI__TIMER_BLINK_PERIOD);
}


//** METHODS IN THE PROTOTYPE


//** CLASS INHERITANCE

