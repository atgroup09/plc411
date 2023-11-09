/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  Module: Interactive Form.
*
*   Copyright (C) 2016-2019  ATgroup09 (atgroup09@gmail.com)
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


/* Required:
*    + types/types.js:
*    ~ search_sub_string(),
*    ~ replace_sub_string(),
*    ~ is_empty(),
*    ~ is_array(),
*    ~ check_object().
*/


//** GLOBAL VARIABLES


//** FUNCTIONS


//** CLASSES

/*	Class:	form.
*	Input:
*			IDIn - form ID.
*/
function jsForm(IDIn)
{
	//**	Structures of data:
	//
	//	ItemOptions = { name: {     ItemType: "select|button|checkbox|file|hidden|image|password|radio|reset|submit|text|textarea|number|range|date|tel|search",
	//			    		          DataType: "string|number",
	//						        Allow: true|false,   -- on/off get/setResultset action (true by default)
	//						      NoEmpty: true|false,   -- if the option is TRUE and value is empty, then item is not add to resultset (true by default),
	//							  Encode: "sha1",       -- for string types (required jquery.sha1.js),
	//						    Required: true|false    -- name of field with invalid value will be add to array this.ErrRequiredValues
	//		   		         },
	//			         ...
	//			       }
	//
	//	  ResultSet = { name: string||number||array(string||number, ...),
	//				    ...
	//				   }
	//
	//					* array() is using for ItemType "select" with mode "multiselect"
	//
	//	    FillSet = { name: {   attrs: { attr-name: attr-value, ... },
	//						    options: [ { value: string||number, text: string, disabled: true||false, selected: true||false },
	//								       ...
	//								      ] ,
	//						      clear: true||false, -- allow to clear select-list before fill it
	//						     append: true||false  -- allow to append new options into select-list
	//						   },
	//					...
	//				   }
	//
	//					* ["name"]["attr"] for Input-elements
	//					* ["name"]["attr"], ["name"]["options"], ["name"]["clear"], ["name"]["append"] for Select-elements
	
	//Private properties
	var ItemType__Select			= "select";
	var ItemType__InputButton		= "button";
	var ItemType__InputCheckbox		= "checkbox";
	var ItemType__InputFile			= "file";
	var ItemType__InputHidden		= "hidden";
	var ItemType__InputImage		= "image";
	var ItemType__InputPassword		= "password";
	var ItemType__InputRadio		= "radio";
	var ItemType__InputReset		= "reset";
	var ItemType__InputSubmit		= "submit";
	var ItemType__InputText			= "text";
	var ItemType__InputNumber		= "number";
	var ItemType__InputRange		= "range";
	var ItemType__InputDate			= "date";
	var ItemType__InputTel			= "tel";
	var ItemType__InputSearch		= "search";
	var ItemType__Textarea			= "textarea";
	
	var DataType__String			= "string";
	var DataType__Number			= "number";
	
	var FillSet__Hours				= "hours";
	var FillSet__Minutes			= "minutes";
	
	var Code__Sha1					= "sha1";
	
	
	//Public properties
	
	//* Form Item Types	[STRING]
	this.ITEM_TYPE__SELECT			= ItemType__Select;
	this.ITEM_TYPE__INPUT_BUTTON	= ItemType__InputButton;
	this.ITEM_TYPE__INPUT_CHECKBOX	= ItemType__InputCheckbox;
	this.ITEM_TYPE__INPUT_FILE		= ItemType__InputFile;
	this.ITEM_TYPE__INPUT_HIDDEN	= ItemType__InputHidden;
	this.ITEM_TYPE__INPUT_IMAGE		= ItemType__InputImage;
	this.ITEM_TYPE__INPUT_PASSWORD	= ItemType__InputPassword;
	this.ITEM_TYPE__INPUT_RADIO		= ItemType__InputRadio;
	this.ITEM_TYPE__INPUT_RESET		= ItemType__InputReset;
	this.ITEM_TYPE__INPUT_SUBMIT	= ItemType__InputSubmit;
	this.ITEM_TYPE__INPUT_TEXT		= ItemType__InputText;
	this.ITEM_TYPE__INPUT_NUMBER	= ItemType__InputNumber;
	this.ITEM_TYPE__INPUT_RANGE		= ItemType__InputRange;
	this.ITEM_TYPE__INPUT_DATE		= ItemType__InputDate;
	this.ITEM_TYPE__INPUT_TEL		= ItemType__InputTel;
	this.ITEM_TYPE__INPUT_SEARCH	= ItemType__InputSearch;
	this.ITEM_TYPE__TEXTAREA		= ItemType__Textarea;
	
	//* Data Types	[STRING]
	this.DATA_TYPE__STRING			= DataType__String;
	this.DATA_TYPE__NUMBER			= DataType__Number;
	
	//* FillSet types	[STRING]
	this.FILL_SET__HOURS			= FillSet__Hours;
	this.FILL_SET__MINUTES			= FillSet__Minutes;
	
	//* 	ItemOptions	[OBJECT]
	//** see structure of data ItemOption
	this.ItemOptions = null;
	
	//* AJAX Options	[OBJECT]
	this.AjaxOptions = null;
	
	//* Auto reset form before set resultset/fillset	[BOOLEAN]
	this.AutoReset = false;
	
	//* Auto create form after set resultset/fillset	[BOOLEAN]
	this.AutoCreate = false;
	
	//* Auto clear select-lists of the form before set fillset	[BOOLEAN]
	this.AutoClear = false;
	
	//* Auto append new options into select-lists from fillset	[BOOLEAN]
	this.AutoAppend = false;
	
	//* Auto scroll to the form after it showed [BOOLEAN]
	this.AutoScrollTo = false;
	
	//* Code types	[STRING]
	this.CodeSha1 = Code__Sha1;
	
	//* Empty values "as is"	[BOOLEAN]
	this.EmptyAsIs = false;
	
	//* invalid required values	[ARRAY]
	//** [0][name] ...
	this.ErrRequiredValues = [ ];
	
	
	//Private properties
	
	//* Form ID		[STRING]
	var ID = null;
	
	//* Form node	[OBJECT || NULL]
	var FormNode = null;
	
	//* Title node	[OBJECT || NULL]
	var TitleNode = null;
	
	//* Data type by default	[STRING]
	var DataTypeDef = "string";
	
	//* Functionality	[BOOLEAN]
	var CheckFunc = false;
	
	
	//Methods
	
	//Private Method: Check value of ItemOption["ItemType"].
	//Input:
	//			ItemTypeIn - item type.	[STRING]
	//Output:
	//			true if item type is correct, otherwise - false. [BOOLEAN]
	//
	var isItemType = function(ItemTypeIn)
	{
		if(CheckFunc && typeof ItemTypeIn == "string")
		{
			return (search_sub_string("select|button|checkbox|file|hidden|image|password|radio|reset|submit|text|textarea|number|range|date|tel|search", ItemTypeIn));
		}
		
		return (false);
	};
	
	//Private Method: Check value of ItemOption["DataType"].
	//Input:
	//			DataTypeIn - data type.	[STRING]
	//Output:
	//			true if data type is correct, otherwise - false. [BOOLEAN]
	//
	var isDataType = function(DataTypeIn)
	{
		if(CheckFunc && typeof DataTypeIn == "string")
		{
			return (search_sub_string("string|number", TypeIn));
		}
		
		return (false);
	};
	
	//Private Method: Check input type.
	//Input:
	//			InputTypeIn - item type.	[STRING]
	//Output:
	//			true if item type is Input, otherwise - false. [BOOLEAN]
	//
	var isInputType = function(InputTypeIn)
	{
		if(CheckFunc && typeof InputTypeIn == "string")
		{
			return (search_sub_string("button|checkbox|file|hidden|image|password|radio|reset|submit|text|number|range|date|tel|search", InputTypeIn));
		}
		
		return (false);
	};
	
	//Private Method: Check item option.
	//Input:
	//			ItemOptionIn - option item.	[OBJECT]
	//Output:
	//			true if option item is correct, otherwise - false.	[BOOLEAN]
	//
	var isItemOption = function(ItemOptionIn)
	{
		if(CheckFunc && typeof ItemOptionIn == "object")
		{
			var Attrs = new Array( { name: "ItemType", data_type: "string", null_value: false, value: "select|button|checkbox|file|hidden|image|password|radio|reset|submit|text|textarea|number|range|date|tel|search" },
								   { name: "DataType", data_type: "string|number", null_value: true }
								 );
			
			return (check_object(ItemOptionIn, Attrs));
		}
		
		return (false);
	};
	
	//Public Method: Check item option.
	//Input:
	//			ItemOptionIn - option item.	[OBJECT]
	//Output:
	//			true if option item is correct, otherwise - false.	[BOOLEAN]
	//
	this.isItemOption = function(ItemOptionIn)
	{
		if(CheckFunc && typeof ItemOptionIn == "object")
		{
			var Attrs = new Array( { name: "ItemType", data_type: "string", null_value: false, value: "select|button|checkbox|file|hidden|image|password|radio|reset|submit|text|textarea|number|range|date|tel|search" },
								   { name: "DataType", data_type: "string|number", null_value: true }
								 );
			
			return (check_object(ItemOptionIn, Attrs));
		}
		
		return (false);
	};
	
	//Public Method: Get item option.
	//Input:
	//			NameIn - item option name.	[STRING]
	//Output:
	//			Option or NULL.	[STRING || NULL]
	//
	this.getItemOption = function(NameIn)
	{
		if(CheckFunc && typeof NameIn == "string" && typeof this.ItemOptions == "object")
		{
			if(!is_empty(NameIn))
			{
				if(typeof this.ItemOptions[NameIn] == "object")
				{
					if(this.isItemOption(this.ItemOptions[NameIn]))
					{
						return (this.ItemOptions[NameIn]);
					}
				}
			}
		}
		
		return (null);
	};
	
	//Public Method: Get allowed item option.
	//Input:
	//			NameIn - item option name.	[STRING]
	//Output:
	//			Aloowed option or NULL.	[STRING || NULL]
	//
	this.getAllowedItemOption = function(NameIn)
	{
		var Opts = this.getItemOption(NameIn);
		
		if(Opts)
		{
			if(typeof Opts["Allow"] == "boolean")
			{
				if(Opts["Allow"]) return (Opts);
			}
		}
		
		return (null);
	};
	
	//Private Method: Get filter for find-string from value(s).
	//Input:
	//			ValueIn - item vaue.	[STRING || NUMBER || ARRAY || NULL]
	//Output:
	//			filter-string or NULL	[STRING || NULL]
	//
	var getFindFilterStr = function(ValueIn)
	{
		var Res = ((typeof ValueIn == "string" || typeof ValueIn == "number") ? ("^" + ValueIn + "$") : null);
		
		if(CheckFunc && typeof ValueIn == "object")
		{
			if(ValueIn)
			{
				if(is_array(ValueIn))
				{
					for(var i=0; i<ValueIn.length; i++)
					{
						if(!i) Res = ValueIn[i];
						else   Res+= "|" + ValueIn[i];
					}
				}
			}
		}
		
		return (Res);
	}
	
	//Private Method: Get RegExp-object from value(s).
	//Input:
	//			NameIn - item name;	[STRING]
	//			ItemOptionIn - item;	[OBJECT]
	//			ValueIn - item vaue.	[STRING || NUMBER || ARRAY || NULL]
	//Output:
	//			{ find: string|null, filter: string|null, findSrc: string|null }	[OBJECT]
	//
	// Note:
	//			findSrc == find, but it value is not contains "option" for select-items 
	//
	var getFindStr = function(NameIn, ItemOptionIn, ValueIn)
	{
		var Res = { find: null, findSrc: null, filter: null };
		
		Res["filter"] = getFindFilterStr(ValueIn);
		
		if(CheckFunc && typeof NameIn == "string" && typeof ItemOptionIn == "object")
		{
			if(isItemOption(ItemOptionIn))
			{
				switch(ItemOptionIn["ItemType"])
				{
					case ItemType__Select:
						
						Res["find"]    = "select[name='{0}'] option".replace(/\{0\}/g, NameIn);
						Res["findSrc"] = "select[name='{0}']".replace(/\{0\}/g, NameIn);
						if(!Res["filter"]) Res["find"]+= ":selected";
						break;
						
					case ItemType__Textarea:
						
						Res["find"] = "textarea[name='{0}']".replace(/\{0\}/g, NameIn);
						Res["findSrc"] = Res["find"];
						break;
						
					case ItemType__InputButton:
					case ItemType__InputHidden:
					case ItemType__InputPassword:
					case ItemType__InputReset:
					case ItemType__InputSubmit:
					case ItemType__InputText:
					case ItemType__InputNumber:
					case ItemType__InputRange:
					case ItemType__InputDate:
					case ItemType__InputTel:
					case ItemType__InputSearch:
						
						Res["find"] = "input[name='{0}'][type='{1}']".replace(/\{0\}/g, NameIn);
						Res["find"] = Res["find"].replace(/\{1\}/g, ItemOptionIn["ItemType"]);
						Res["findSrc"] = Res["find"];
						break;
						
					case ItemType__InputCheckbox:
					case ItemType__InputRadio:
						
						Res["find"] = "input[name='{0}'][type='{1}']".replace(/\{0\}/g, NameIn);
						Res["find"] = Res["find"].replace(/\{1\}/g, ItemOptionIn["ItemType"]);
						Res["findSrc"] = Res["find"];
						if(!Res["filter"]) Res["find"]+= ":checked";
						break;
				}
			}
		}
		
		return (Res);
	}
	
	//Public Method: Get form item by name.
	//Input:
	//			NameIn - item name;	[STRING]
	//			ValueIn - item vaue.	[STRING || NUMBER || ARRAY || NULL]
	//Output:
	//			form item or NULL.	[OBJECT || NULL]
	//
	this.getItems = function(NameIn, ValueIn)
	{
		if(CheckFunc && FormNode && typeof NameIn == "string")
		{
			var Opts = this.getItemOption(NameIn);
			
			if(Opts)
			{
				var FindStr = getFindStr(NameIn, Opts, ValueIn);
				/*
				console.log("getItems:");
				console.log(Opts);
				console.log(FindStr);
				*/
				return ((!FindStr["filter"]) ? FormNode.find(FindStr["find"]) : FormNode.find(FindStr["find"]).filter(function(i){ return (new RegExp(FindStr["filter"])).test(this.value) }));
			}
		}
		
		return (null);
	};
	
	//Public Method: Get form item (not chield) by name.
	//Input:
	//			NameIn - item name;	[STRING]
	//			ValueIn - item vaue.	[STRING || NUMBER || ARRAY || NULL]
	//Output:
	//			form item or NULL.	[OBJECT || NULL]
	//
	this.getSrcItems = function(NameIn, ValueIn)
	{
		if(CheckFunc && FormNode && typeof NameIn == "string")
		{
			var Opts = this.getItemOption(NameIn);
			
			if(Opts)
			{
				var FindStr = getFindStr(NameIn, Opts, ValueIn);
				/*
				console.log("getSrcItems:");
				console.log(Opts);
				console.log(FindStr);
				*/
				return ((!FindStr["filter"]) ? FormNode.find(FindStr["findSrc"]) : FormNode.find(FindStr["findSrc"]).filter(function(i){ return (new RegExp(FindStr["filter"])).test(this.value) }));
			}
		}
		
		return (null);
	};
	
	//Private Method: Normalize float.
	//Input:
	//			ValueIn - value.	[STRING || NUMBER]
	//Output:
	//			Normalized float. [NUMBER || NULL]
	//
	var normalizeFloatValue = function(ValueIn)
	{
		if(CheckFunc && (typeof ValueIn == "string" || typeof ValueIn == "number"))
		{
			var Value = ((typeof ValueIn == "number") ? ("" + ValueIn) : ValueIn);
			Value = replace_sub_string("[,]", ValueIn, ".");
			return (Value-0);
		}
		
		return (null);
	};
	
	//Private Method: Normalize value.
	//Input:
	//			ValueIn - value;	[STRING || NUMBER]
	//			DataTypeIn - data type ("string" by default).	[STRING || NULL]
	//Output:
	//			Normalized value. [STRING || NUMBER || NULL]
	//
	var normalizeValue = function(ValueIn, DataTypeIn)
	{
		var Res = null;
		
		if(CheckFunc && (typeof ValueIn == "string" || typeof ValueIn == "number"))
		{
			switch(DataTypeIn)
			{
				case DataType__String:
					
					Res = ((typeof ValueIn == "number") ? ("" + ValueIn) : ValueIn);
					break;
					
				case DataType__Number:
					
					Res = normalizeFloatValue(ValueIn);
					break;
			}
		}
		
		return (Res);
	};
	
	//Private Method: Encode value.
	//Input:
	//			ValueIn    - value;		[STRING || NULL]
	//			CodeTypeIn - code type:	[STRING]
	//						= "sha1"
	//Output:
	//			encoded value.
	//
	var encodeValue = function(ValueIn, CodeTypeIn)
	{
		if(CheckFunc && typeof ValueIn == "string" && typeof CodeTypeIn == "string")
		{
			switch(CodeTypeIn)
			{
				case Code__Sha1:
					return ($.sha1(ValueIn));
			}
		}
		
		return (ValueIn);
	};
	
	//Public Method: Get resultset.
	//Input:
	//			none.
	//Output:
	//			resultset or NULL.	[OBJECT || NULL]
	//Note:
	// 			See structure of data ResultSet.
	//
	this.getResultset = function()
	{
		var Res = null;
		this.ErrRequiredValues = [ ];
		
		if(CheckFunc && FormNode && typeof this.ItemOptions == "object")
		{
			if(this.ItemOptions)
			{
				var Items       = null;
				var NoEmpty     = true;
				var ItIsEmpty   = false;
				var Required    = false;
				var ValueRaw    = null;
				var Value       = null;
				var i           = 0;
				
				for(var Name in this.ItemOptions)
				{
					Items = this.getItems(Name, null);
					
					if(Items)
					{
						if(typeof this.ItemOptions[Name]["Allow"] == "boolean")
						{
							if(!this.ItemOptions[Name]["Allow"]) continue;
						}
						
						NoEmpty  = ((typeof this.ItemOptions[Name]["NoEmpty"] == "boolean") ? this.ItemOptions[Name]["NoEmpty"] : true);
						Required = ((typeof this.ItemOptions[Name]["Required"] == "boolean") ? this.ItemOptions[Name]["Required"] : false);
						
						if(!Res) Res = { };
						//Res[Name] = ((Items.length > 1) ? [ ] : null);
						
						for(i=0; i<Items.length; i++)
						{
							ValueRaw  = Items.eq(i).val();
							ItIsEmpty = is_empty(ValueRaw);
							
							if(Required && ItIsEmpty) this.ErrRequiredValues.push(Name);
							if(NoEmpty && ItIsEmpty) continue;
							
							Value = ((this.EmptyAsIs && ItIsEmpty) ? ValueRaw : normalizeValue(ValueRaw, this.ItemOptions[Name]["DataType"]));
							
							//check required
							if(Required && Value === null) this.ErrRequiredValues.push(Name);
							
							if(typeof this.ItemOptions[Name]["Encode"] == "string")
							{
								Value = encodeValue(ValueRaw, this.ItemOptions[Name]["Encode"]);
							}
							
							if(Items.length > 1)
							{
								if(i == 0) Res[Name] = [ ];
								Res[Name].push(Value);
							}
							else
							{
								Res[Name] = Value;
							}
						}
					}
				}
			}
		}
		
		return (Res);
	};
	
	//Public Method: Get resultset into other associative array.
	//Input:
	//			none.
	//Output:
	//			new resultset or NULL.	[OBJECT || NULL]
	//Note:
	//
	this.getResultsetTo = function(ResultsetIn)
	{
		var Res = this.getResultset();
		
		if(typeof ResultsetIn == "object")
		{
			if(ResultsetIn)
			{
				if(!Res) Res = { };
				
				for(var Key in ResultsetIn)
				{
					Res[Key] = ResultsetIn[Key];
				}
			}
		}
		
		return (Res);
	};
	
	//Public Method: Init. SelectMenu method.
	//Input:
	//			ItemIn   - select item;	[OBJECT]
	//			MethodIn - method:		[STRING]
	//						= "refresh",
	//						= "close",
	//						= "open",
	//						= "enable",
	//						= "disable".
	//Output:
	//			none.
	//Note:
	//
	this.initSelectMenuItem = function(ItemIn, MethodIn)
	{
		if(CheckFunc && typeof ItemIn == "object" && typeof MethodIn == "string")
		{
			if(ItemIn)
			{
				if(typeof ItemIn.selectmenu == "function" && (MethodIn == "refresh" || MethodIn == "close" || MethodIn == "open" || MethodIn == "enable" || MethodIn == "disable"))
				{
					((MethodIn == "refresh") ? ItemIn.selectmenu(MethodIn, true) : ItemIn.selectmenu(MethodIn));
				}
			}
		}
	};
	
	//Public Method: Init. SelectMenu method.
	//Input:
	//			ItemIn   - select item;	[OBJECT]
	//			MethodIn - method:		[STRING]
	//						= "refresh",
	//						= "close",
	//						= "open",
	//						= "enable",
	//						= "disable".
	//Output:
	//			none.
	//Note:
	//
	this.initSelectMenu = function(NameIn, MethodIn)
	{
		if(CheckFunc && typeof NameIn == "string")
		{
			var Item = this.getSrcItems(NameIn, null);
			this.initSelectMenuItem(Item, MethodIn);
		}
	};
	
	//Public Method: Clear Select Item.
	//Input:
	//			ItemIn  - select item.		[OBJECT]
	//Output:
	//			none.
	//Note:
	//			remove all options from the Select item.
	//
	this.clearSelectItem = function(ItemIn)
	{
		if(CheckFunc && typeof ItemIn == "object")
		{
			if(ItemIn)
			{
				var Options = ItemIn.find("option");
				if(Options) Options.remove();
			}
		}
	};
	
	//Public Method: Clear Select Item.
	//Input:
	//			NameIn - item name.	[STRING]
	//Output:
	//			none.
	//Note:
	//
	this.clearSelect = function(NameIn)
	{
		if(CheckFunc && typeof NameIn == "string")
		{
			var Item = this.getSrcItems(NameIn, null);
			this.clearSelectItem(Item);
		}
	};

	//Public Method: call trigger.
	//Input:
	//			ItemIn - item;			[OBJECT || NULL]
	//			MethodIn - trigger-method.	[STRING]
	//Output:
	//			none.
	//Note:
	//			If ItemIn is NULL, then trigger will be execute for this form-node.
	//
	this.triggerItem = function(ItemIn, MethodIn)
	{
		if(CheckFunc && FormNode && typeof MethodIn == "string")
		{
			var Item = FormNode;
			
			if(typeof ItemIn == "object")
			{
				if(ItemIn) Item = ItemIn;
			}
			
			Item.trigger(MethodIn);
		}
	};
	
	//Public Method: call trigger.
	//Input:
	//			NameIn - item name;		[STRING || NULL]
	//			MethodIn - trigger-method.	[STRING]
	//Output:
	//			none.
	//Note:
	//			If NameIn is NULL, then trigger will be execute for this form-node.
	//
	this.trigger = function(NameIn, MethodIn)
	{
		if(CheckFunc)
		{
			var Item = null;
			
			if(typeof NameIn == "string")
			{
				if(!is_empty(NameIn)) Item = this.getSrcItems(NameIn, null);
			}
			
			this.triggerItem(Item, MethodIn);
		}
	};
	
	//Public Method: Reset.
	//Input:
	//			none.
	//Output:
	//			none.
	//Note:
	//
	this.reset = function()
	{
		if(FormNode) FormNode.find("input[type=hidden").val("");
		this.trigger(null, "reset");
		this.trigger(null, "create");
	};
	
	//Public Method: Create.
	//Input:
	//			none.
	//Output:
	//			none.
	//Note:
	//
	this.create = function()
	{
		this.trigger(null, "create");
	};
	
	//Public Method: Set resultset.
	//Input:
	//			ResultsetIn - resultset.	[OBJECT]
	//Output:
	//			none.
	//Note:
	// 			See structure of data ResultSet.
	//
	this.setResultset = function(ResultsetIn)
	{
		if(CheckFunc && FormNode)
		{
			if(this.AutoReset) this.reset();
			
			if(typeof ResultsetIn == "object")
			{
				if(ResultsetIn)
				{
					var Opts  = null;
					var Items = null;
					
					for(var Name in ResultsetIn)
					{
						Opts = this.getAllowedItemOption(Name);
						
						if(Opts)
						{
							Items = ((Opts["ItemType"] == this.ITEM_TYPE__SELECT || Opts["ItemType"] == this.ITEM_TYPE__INPUT_CHECKBOX || Opts["ItemType"] == this.ITEM_TYPE__INPUT_RADIO) ? this.getItems(Name, ResultsetIn[Name]) : this.getItems(Name, null));
							
							switch(Opts["ItemType"])
							{
								case this.ITEM_TYPE__SELECT:
									
									Items.prop("selected", true);
									break;
									
								case this.ITEM_TYPE__INPUT_CHECKBOX:
								case this.ITEM_TYPE__INPUT_RADIO:
									
									Items.prop("checked", true);
									break;
									
								default:
									
									if(typeof ResultsetIn[Name] == "string" || typeof ResultsetIn[Name] == "number")
									{
										Items.val(ResultsetIn[Name]);
									}
							}
						}
					}
					
					if(this.AutoCreate) this.create();
				}
			}
		}
	};
	
	//Private Method: Check existence of option in the select-list.
	//Input:
	//			ItemIn  - select-list; [OBJECT]
	//			ValueIn - value.		 [STRING || NUMBER || NULL]
	//Output:
	//			option-item or NULL.	[OBJECT || NULL]
	//Note:
	//
	var hasSelectOption = function(ItemIn, ValueIn)
	{
		if(typeof ItemIn == "object")
		{
			if(ItemIn)
			{
				var OptItem = (((typeof ValueIn == "string" || typeof ValueIn == "number")) ? ItemIn.find("option[value='{0}']".replace(/\{0\}/g, ValueIn)) : ItemIn.find("option[value='']"));
				
				if(OptItem)
				{
					if(OptItem.length) return (OptItem);
				}
			}
		}
		
		return (null);
	};
	
	//Private Method: set Item attributes/properties/values/text.
	//Input:
	//			ItemIn  - item; 				[OBJECT]
	//			AttrsIn - list of attributes.	[ARRAY || NULL]
	//Output:
	//			none.
	//Note:
	// 			See structure of data FillSet["name"]["attr"].
	//
	var setItemAttr = function(ItemIn, AttrsIn)
	{
		if(CheckFunc && typeof ItemIn == "object" && typeof AttrsIn == "object")
		{
			if(ItemIn && AttrsIn)
			{
				for(var Name in AttrsIn)
				{
					switch(Name)
					{
						case "checked":
						case "selected":
						case "multiple":
							
							if(typeof AttrsIn[Name] == "string" || typeof AttrsIn[Name] == "boolean") ItemIn.prop(Name, AttrsIn[Name]);
							break;
							
						case "value":
							
							if(typeof AttrsIn[Name] == "string" || typeof AttrsIn[Name] == "number")  ItemIn.val(AttrsIn[Name]);
							break;
							
						case "text":
							
							if(typeof AttrsIn[Name] == "string" || typeof AttrsIn[Name] == "number")  ItemIn.text(AttrsIn[Name]);
							break;
							
						default:
							
							if(typeof AttrsIn[Name] == "string" || typeof AttrsIn[Name] == "number" || typeof AttrsIn[Name] == "boolean")  ItemIn.attr(Name, AttrsIn[Name]);
					}
				}
			}
		}
	};
	
	//Private Method: fill select-list.
	//Input:
	//			ItemIn    - item; 			[OBJECT]
	//			OptionsIn - list of options;	[ARRAY || NULL]
	//			AllowAppendIn - allow append new options into select-list.	[BOOLEAN]
	//Output:
	//			none.
	//Note:
	// 			See structure of data FillSet["name"]["options"].
	//
	var fillSelect = function(ItemIn, OptionsIn, AllowAppendIn)
	{
		if(CheckFunc && typeof ItemIn == "object")
		{
			if(ItemIn && typeof OptionsIn == "object")
			{
				if(is_array(OptionsIn))
				{
					var OptSet  = { };
					var OptItem = null;
					
					for(var i=0; i<OptionsIn.length; i++)
					{
						if(OptionsIn[i])
						{
							OptSet = { };
							if(typeof OptionsIn[i]["value"] == "string" || typeof OptionsIn[i]["value"] == "number") OptSet["value"] = OptionsIn[i]["value"];
							if(typeof OptionsIn[i]["text"] == "string" || typeof OptionsIn[i]["text"] == "number") OptSet["text"] = OptionsIn[i]["text"];
							OptSet["disabled"] = ((typeof OptionsIn[i]["disabled"] == "boolean") ? OptionsIn[i]["disabled"] : false);
							OptSet["selected"] = ((typeof OptionsIn[i]["selected"] == "boolean") ? OptionsIn[i]["selected"] : false);
							
							OptItem = hasSelectOption(ItemIn, OptSet["value"]);
							
							if(!OptItem && AllowAppendIn)
							{
								//create new option
								OptItem = $('<option value=""> </option>');
								OptItem.appendTo(ItemIn);
							}
							
							setItemAttr(OptItem, OptSet);
						}
					}
				}
			}
		}
	};
	
	//Public Method: fill elements.
	//Input:
	//			FillSetIn - list of settings.	[OBJECT]
	//Output:
	//			none.
	//Note:
	// 			See structure of data FillSet.
	//
	this.fill = function(FillSetIn)
	{
		if(CheckFunc && FormNode)
		{
			if(this.AutoReset) this.reset();
			
			if(typeof FillSetIn == "object")
			{
				if(FillSetIn)
				{
					var Opts   = null;
					var Items  = null;
					var Clear  = false;
					var Append = false;
					
					for(var Name in FillSetIn)
					{
						Opts = this.getAllowedItemOption(Name);
						
						if(Opts)
						{
							Items = this.getSrcItems(Name, null);
							
							if(Items)
							{
								if(typeof FillSetIn[Name]["attrs"] == "object")
								{
									setItemAttr(Items, FillSetIn[Name]["attrs"]);
								}
								
								if(Opts["ItemType"] == this.ITEM_TYPE__SELECT && typeof FillSetIn[Name]["options"] == "object")
								{
									Clear  = ((typeof FillSetIn[Name]["clear"] == "boolean") ? FillSetIn[Name]["clear"] : false);
									Append = ((typeof FillSetIn[Name]["append"] == "boolean") ? FillSetIn[Name]["append"] : false);
									
									if(this.AutoClear || Clear) this.clearSelectItem(Items);
									fillSelect(Items, FillSetIn[Name]["options"], (this.AutoAppend || Append));
								}
								
								if(Opts["ItemType"] == this.ITEM_TYPE__SELECT)
								{
									((Items.is(":enabled")) ? this.initSelectMenuItem(Items, "enable") : this.initSelectMenuItem(Items, "disable"));
									this.initSelectMenuItem(Items, "refresh");
								}
							}
						}
					}
					
					if(this.AutoCreate) this.create();
				}
			}
		}
	};
	
	//Public Method: Set callback function to form item.
	//Input:
	//			ItemIn - item;	[OBJECT]
	//			EventTypeIn - event type;	[STRING]
	//			FunctionIn - callback function.	[FUNCTION]
	//Output:
	//			None.
	//
	this.bindItem = function(ItemIn, EventTypeIn, FunctionIn)
	{
		if(CheckFunc && typeof ItemIn == "object" && typeof FunctionIn == "function" && typeof EventTypeIn == "string")
		{
			if(ItemIn && !is_empty(EventTypeIn)) ItemIn.bind(EventTypeIn, FunctionIn);
		}
	};
	
	//Public Method: Set callback function to form item by Item name.
	//Input:
	//			NameIn - option name;	[STRING]
	//			EventTypeIn - event type;	[STRING]
	//			FunctionIn - callback function.	[FUNCTION]
	//Output:
	//			None.
	//
	this.bind = function(NameIn, EventTypeIn, FunctionIn)
	{
		if(CheckFunc && typeof NameIn == "string")
		{
			var Item = this.getSrcItems(NameIn, null);
			this.bindItem(Item, EventTypeIn, FunctionIn);
		}
	};
	
	//Public Method: Remove callback function from form item.
	//Input:
	//			ItemIn - item;	[OBJECT]
	//			EventTypeIn - event type;	[STRING]
	//			FunctionIn - callback function.	[FUNCTION]
	//Output:
	//			None.
	//
	this.unbindItem = function(ItemIn, EventTypeIn, FunctionIn)
	{
		if(CheckFunc && typeof ItemIn == "object" && typeof FunctionIn == "function" && typeof EventTypeIn == "string")
		{
			if(ItemIn && !is_empty(EventTypeIn)) ItemIn.unbind(EventTypeIn, FunctionIn);
		}
	};
	
	//Public Method: Remove callback function from form item by it name.
	//Input:
	//			ItemIn - item;	[OBJECT]
	//			EventTypeIn - event type;	[STRING]
	//			FunctionIn - callback function.	[FUNCTION]
	//Output:
	//			None.
	//
	this.unbind = function(NameIn, EventTypeIn, FunctionIn)
	{
		if(CheckFunc && typeof NameIn == "string")
		{
			var Item = this.getSrcItems(NameIn, null);
			this.unbindItem(Item, EventTypeIn, FunctionIn);
		}
	};
	
	//Public Method: Set DatePicker to Item.
	//Input:
	//			ItemIn 	  - item;		[OBJECT]
	//			SettingsIn - settings.		[OBJECT]
	//Output:
	//			none.
	//Note:
	//			settings ex.: {dateFormat: "yy-mm-dd", language: "en"} (by default)
	//
	this.setDatePickerItem = function(ItemIn, SettingsIn)
	{
		if(CheckFunc && typeof ItemIn == "object")
		{
			if(ItemIn)
			{
				var Sett = ((typeof SettingsIn == "object") ? SettingsIn : null);
				
				if(Sett)
				{
					if(typeof Sett["language"] == "string")
					{
						$.datepicker.setDefaults($.extend($.datepicker.regional[Sett["language"]]));
					}
				}
				
				ItemIn.datepicker(Sett);
			}
		}
	};
	
	//Public Method: Set DatePicker.
	//Input:
	//			NameIn 	  - option name;	[STRING]
	//			SettingsIn - settings.		[OBJECT]
	//Output:
	//			none.
	//Note:
	//			settings ex.: {dateFormat: "yy-mm-dd", language: "en"} (by default)
	//
	this.setDatePicker = function(NameIn, SettingsIn)
	{
		if(CheckFunc && typeof NameIn == "string")
		{
			var Item = this.getSrcItems(NameIn, null);
			this.setDatePickerItem(Item, SettingsIn);
		}
	};
	
	//Public Method: Encode form resultset to encoded URI-format.
	//Input:
	//			ResultsetIn - form resultset.	[OBJECT]
	//Output:
	//			Encoded URI-string or NULL.	[STRING || NULL]
	//Note:
	//
	this.toURI = function(ResultsetIn)
	{
		if(CheckFunc && typeof ResultsetIn == "object")
		{
			if(ResultsetIn)
			{
				return ($.param(ResultsetIn));
			}
		}
		
		return (null);
	};
	
	//Public Method: Encode form resultset to decoded URI-format.
	//Input:
	//			ResultsetIn - form resultset.	[OBJECT]
	//Output:
	//			Decoded URI-string or NULL.	[STRING || NULL]
	//Note:
	//
	this.toDecodedURI = function(ResultsetIn)
	{
		if(CheckFunc && typeof ResultsetIn == "object")
		{
			var URI = this.toURI(ResultsetIn);
			
			return (decodeURIComponent(URI));
		}
		
		return (null);
	};
	
	//Public Method: Send request via AJAX.
	//Input:
	//			none.
	//Output:
	//			none.
	//
	this.ajax = function()
	{
		if(CheckFunc && typeof this.AjaxOptions == "object")
		{
			if(this.AjaxOptions)
			{
				$.ajax(this.AjaxOptions);
			}
		}
	};
	
	//Public Method: Show.
	//Input:
	//			none.
	//Output:
	//			none.
	//
	this.show = function()
	{
		if(FormNode)
		{
			FormNode.show();
			if(this.AutoScrollTo) this.scrollTo();
		}
	};
	
	//Public Method: Hide.
	//Input:
	//			none.
	//Output:
	//			none.
	//
	this.hide = function()
	{
		if(FormNode) FormNode.hide();
	};
	
	//Public Method: Toggle visible.
	//Input:
	//			none.
	//Output:
	//			none.
	//
	this.toggle = function()
	{
		if(FormNode) FormNode.toggle();
	};
	
	//Public Method: Get fillset for select-list with one empty option.
	//Input:
	//			none.
	//Output:
	//			Fillset.	[OBJECT]
	//
	this.getListEmptyOneFillset = function()
	{
		var Res = { options: [ { value: "", text: "---" }
							  ],
					  clear: true,
					 append: true
				   };
		
		return (Res);
	};
	
	//Public Method: Get fillset for select-list of time part.
	//Input:
	//			TimePartIDIn - ID of time-part:	[STRING]
	//							= "hours"   (00 ... 23)
	//							= "minutes" (00 ... 59)
	//Output:
	//			Fillset.	[OBJECT]
	//
	this.getListTimePartFillset = function(TimePartIDIn)
	{
		var Res = { options: [ ],
					  clear: true,
					 append: true
				   };
		
		if(typeof TimePartIDIn == "string")
		{
			if(TimePartIDIn == this.FILL_SET__HOURS || TimePartIDIn == this.FILL_SET__MINUTES)
			{
				var OptNum = ((TimePartIDIn == this.FILL_SET__HOURS) ? 24 : 60);
				var OptObj = null;
				
				for(var i=0; i<OptNum; i++)
				{
					OptObj = { value: "", text: "" };
					OptObj["value"] = ("" + i);
					OptObj["text"]  = ((i < 10) ? ("0" + i) : ("" + i));
					Res["options"].push(OptObj);
				}
			}
		}
		
		return (Res);
	};
	
	//Public Method: Init.
	//Input:
	//			IDIn - form ID.	[STRING]
	//Output:
	//			none.
	//
	this.init = function(IDIn)
	{
		ID = null;
		FormNode = null;
		
		if(CheckFunc && typeof IDIn == "string")
		{
			ID = IDIn;
			FormNode = $("#" + IDIn);
			if(FormNode.length == 0) FormNode = null;
		}
	};
	
	//Public Method: Init.
	//Input:
	//			NodeIn - form node (jQuery Node).	[OBJECT]
	//Output:
	//			none.
	//
	this.initNode = function(NodeIn)
	{
		ID = null;
		FormNode = null;
		
		if(CheckFunc && typeof NodeIn == "object")
		{
			if(NodeIn)
			{
				FormNode = NodeIn;
				ID = NodeIn.attr("id");
			}
		}
	};
	
	//Public Method: Init. Form Title.
	//Input:
	//			IDIn - ID of Node with title of the Form.	[STRING]
	//Output:
	//			none.
	//
	this.initTitle = function(IDIn)
	{
		TitleNode = null;
		
		if(typeof IDIn == "string")
		{
			if(IDIn.length) TitleNode = $("#" + IDIn);
		}
	};
	
	//Public Method: Set / Get value of Form title.
	//Input:
	//			TextIn - text of form title or NULL or NONE. [STRING || NULL || NONE]
	//Output:
	//			Value of Form title.
	//
	this.title = function(TextIn)
	{
		if(TitleNode && typeof TextIn != "undefined")
		{
			var Text = ((typeof TextIn == "string") ? TextIn : "");
			TitleNode.text(Text);
			
			return (TitleNode.text());
		}
		
		return (null);
	};
	
	/*
	@brief  Scroll to form.
	@param  None.
	@return None.
	*/
	this.scrollTo = function()
	{
		if(FormNode) $("html, body").animate({ scrollTop: FormNode.offset().top-40 }, 500);
	};
	
	
	//Constructor
	
	if(typeof search_sub_string == "function" && typeof replace_sub_string == "function" && typeof is_empty == "function" && typeof is_array == "function" && typeof check_object == "function")
	{
		CheckFunc = true;
		this.init(IDIn);
	}
}

