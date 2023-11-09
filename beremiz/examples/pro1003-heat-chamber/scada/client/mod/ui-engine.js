/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  Module: Client side - UI-engine.
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

/* Required:
	+ G_DEBUG
	+ G_LANG
	+ G_POPUP_BASIC
	+ response-result.js
	+ form-v2.js
	+ datatable.js
	+ types/types.js
	+ ui-res.js
*/


//** GLOBAL VARIABLES

/* Engine Targets

	 { "TargetID": {              Alias: StringOrNull,
	                           DataForm: Object,
	                          DataTable: Object, 
		                       KeyField: String,
		                   SelClearSets: ObjectOrNull,
                            SelFillSets: ObjectOrNull,
		                  InitResultset: ObjectOrNull,
		                            idq: StringOrNull,
		                      completed: Boolean,
		                FuncRefreshView: Func,
		               FuncShowDataForm: Func
		              },
		...
	   }

	 where (target options),
		    TargetID - ID of engine target (required) [OBJECT]
		               * must be contain in JSON-requert (as "target_id") from client
		               * must be contain in JSON-response (as "target_id") from server
		    KeyField - name of key-field of DataForm (required) [STRING]
		               * must be contain in DataForm and DataTable
		    DataForm - pointer to DataForm; [OBJECT]
		   DataTable - pointer to DataTable; [OBJECT || NULL]
	    SelClearSets - asociative array of select-list names to be cleared before DataForm is displayed; [OBJECT || NULL]
         SelFillSets - asociative array of select-list settings to be filled from server-side before showing DataForm; [OBJECT || NULL]
	   InitResultset - resultset that will be set first or NULL to init. [OBJECT || NULL]
		         idq - ID of query [STRING || NULL]
		               * must be contain in JSON-requert (as "idq") from client
		               * must be contain in JSON-response (as "idq") from server
		   completed - sign of DataForm completed (true - completed) [BOOLEAN]
		               * set automatically after full fillset DataForm elements
		       Alias - named alias of DataForm or NULL [STRING || NULL]
	 FuncRefreshView - pointer to function for refresh view or NULL [FUNCTION || NULL]
	 				   * input args.: None
    FuncShowDataForm - pointer to function that will be call after DataForm displayed or NULL [FUNCTION || NULL]
					   * input args.: pointer to DataForm object

    Ex.: InitResultset = { approved:(new Date()).format("isoDate"), ...}
  	Ex.: SelClearSets  = { location_id:true, position_id:true }
    Ex.: SelFillSets   = { FormNotCompleted: { location_id:true, position_id:true },
	                          FormCompleted: { position_id:true },
	                            location_id: { position_id:true }
	                      }
	                      * FormNotCompleted - list of select-list names to be filled if DataForm if nor completed (completed == false) (ex. first showing DataForm)
	                      * FormCompleted - list of select-list names to be filled if DataForm if nor completed (completed == true) (ex. second and other showing DataForm)
	                      * location_id - list of select-list names to be filled (refresh) from server-side after changing option of select-list with name `location_id` (handler onDataFormItemChanged)

	* use functions:
		isEngineTarget(IDIn)
		delEngineTarget(IDIn)
		addEngineTarget(IDIn, OptsIn)
*/
var G_ENGINE_TARGETS   = { };


//** FUNCTIONS

/*
@brief  Check engine target.
@param  IDIn - ID of engine target. [STRING]
@return true if target exists and correct, otherwise - false. [BOOLEAN]
*/
function isEngineTarget(IDIn)
{
	if(typeof check_object == "function" && typeof IDIn == "string")
	{
		if(IDIn.length)
		{
			if(typeof G_ENGINE_TARGETS[IDIn] == "object")
			{
				if(G_ENGINE_TARGETS[IDIn])
				{
					var Attrs = new Array({ name: "DataForm", data_type: "object", null_value: false },
								          { name: "SelClearSets", data_type: "object", null_value: true },
								          { name: "InitResultset", data_type: "object", null_value: true },
								          { name: "idq", data_type: "string", null_value: true },
								          { name: "KeyField", data_type: "string", null_value: false }
								         );
					
					return (check_object(G_ENGINE_TARGETS[IDIn], Attrs));
				}
			}
		}
	}
	
	return (false);
}


/*
@brief  Remove engine target.
@param  IDIn - ID of engine target. [STRING]
@return true if target removed, otherwise - false. [BOOLEAN]
*/
function delEngineTarget(IDIn)
{
	if(typeof typeof IDIn == "string")
	{
		if(IDIn.length)
		{
			if(typeof G_ENGINE_TARGETS[IDIn] == "objects") G_ENGINE_TARGETS[IDIn] = null;
			return (true);
		}
	}
	
	return (false);
}


/*
@brief  Add engine target.
@param  IDIn    - ID of engine target. [STRING]
@param  OptsIn  - target options. [OBJECT]
@return true if target added, otherwise - false. [BOOLEAN]
@details If target with ID exists already, then it will be replaced!
*/
function addEngineTarget(IDIn, OptsIn)
{
	delEngineTarget(IDIn);
	
	if(typeof typeof IDIn == "string" && typeof OptsIn == "object")
	{
		if(IDIn.length && OptsIn)
		{
			G_ENGINE_TARGETS[IDIn] = { DataForm:null, KeyField:null, SelClearSets:null, SelFillSets:null, InitResultset:null, idq:null, completed:false, Alias:null, DataTable:null, FuncRefreshView:null, FuncShowDataForm:null };
			
			if(typeof OptsIn["DataForm"] == "object")
			{
				if(OptsIn["DataForm"]) G_ENGINE_TARGETS[IDIn]["DataForm"] = OptsIn["DataForm"];
			}
			
			if(typeof OptsIn["KeyField"] == "string")
			{
				if(OptsIn["KeyField"].length) G_ENGINE_TARGETS[IDIn]["KeyField"] = OptsIn["KeyField"];
			}
			
			if(typeof OptsIn["SelClearSets"] == "object")
			{
				if(OptsIn["SelClearSets"]) G_ENGINE_TARGETS[IDIn]["SelClearSets"] = OptsIn["SelClearSets"];
			}
			
			if(typeof OptsIn["SelFillSets"] == "object")
			{
				if(OptsIn["SelFillSets"]) G_ENGINE_TARGETS[IDIn]["SelFillSets"] = OptsIn["SelFillSets"];
			}
			
			if(typeof OptsIn["InitResultset"] == "object")
			{
				if(OptsIn["InitResultset"]) G_ENGINE_TARGETS[IDIn]["InitResultset"] = OptsIn["InitResultset"];
			}
			
			if(typeof OptsIn["idq"] == "string")
			{
				if(OptsIn["idq"].length) G_ENGINE_TARGETS[IDIn]["idq"] = OptsIn["idq"];
			}
			
			if(typeof OptsIn["completed"] == "boolean")
			{
				G_ENGINE_TARGETS[IDIn]["completed"] = OptsIn["completed"];
			}
			
			if(typeof OptsIn["Alias"] == "string")
			{
				if(OptsIn["Alias"].length) G_ENGINE_TARGETS[IDIn]["Alias"] = OptsIn["Alias"];
			}
			
			if(typeof OptsIn["DataTable"] == "object")
			{
				if(OptsIn["DataTable"]) G_ENGINE_TARGETS[IDIn]["DataTable"] = OptsIn["DataTable"];
			}
			
			if(typeof OptsIn["FuncRefreshView"] == "function")
			{
				G_ENGINE_TARGETS[IDIn]["FuncRefreshView"] = OptsIn["FuncRefreshView"];
			}
			
			if(typeof OptsIn["FuncShowDataForm"] == "function")
			{
				G_ENGINE_TARGETS[IDIn]["FuncShowDataForm"] = OptsIn["FuncShowDataForm"];
			}
			
			return (true);
		}
	}
	
	return (false);
}


/*
@brief  Get SelFillSets of engine target.
@param  IDIn  - ID of target; [STRING]
@param  KeyIn - key to list SelFillSets of target. [STRING]
@return SelFillSets or NULL. [OBJECT || NULL]
*/
function getSelFillSets(IDIn, KeyIn)
{
	if(typeof KeyIn == "string")
	{
		if(KeyIn.length)
		{
			if(isEngineTarget(IDIn))
			{
				if(typeof G_ENGINE_TARGETS[IDIn]["SelFillSets"] == "object")
				{
					if(G_ENGINE_TARGETS[IDIn]["SelFillSets"])
					{
						if(typeof G_ENGINE_TARGETS[IDIn]["SelFillSets"][KeyIn] == "object")
						{
							return (G_ENGINE_TARGETS[IDIn]["SelFillSets"][KeyIn]);
						}
					}
				}
			}
		}
	}
	
	return (null);
}


/*
@brief  Check completeness status of DataForm.
@param  IDIn  - ID of target; [STRING]
@return completeness status. [BOOLEAN]
*/
function isDataFormCompleted(IDIn)
{
	if(isEngineTarget(IDIn))
	{
		if(typeof G_ENGINE_TARGETS[IDIn]["completed"] == "boolean")
		{
			return (G_ENGINE_TARGETS[IDIn]["completed"]);
		}
	}
	
	return (false);
}


/*
@brief  Set status of DataForm as completed.
@param  IDIn - ID of target. [STRING]
@param  CompleteIn - true or false. [BOOLEAN]
@return completeness status. [BOOLEAN]
*/
function setDataFormCompleteStatus(IDIn, CompleteIn)
{
	if(isEngineTarget(IDIn))
	{
		if(typeof G_ENGINE_TARGETS[IDIn]["completed"] == "boolean")
		{
			G_ENGINE_TARGETS[IDIn]["completed"] = ((typeof CompleteIn == "boolean") ? CompleteIn : false);
			return (G_ENGINE_TARGETS[IDIn]["completed"]);
		}
	}
	
	return (false);
}


/*
@brief  Event-handler for Ajax of DataTable (check error).
@param  event - Event-object; [OBJECT]
@param  SettingsIn - settings object; [OBJECT]
@param  JsonIn - data from server; [OBJECT || NULL]
@param  XhrIn - jQuery XHR. [OBJECT]
@return None.
*/
function onDataTableXhr(event, SettingsIn, JsonIn, XhrIn)
{
	if(typeof G_POPUP_BASIC == "object")
	{
		if(G_POPUP_BASIC)
		{
			var Rx = new RegExp(/^#error#/gi);
			if(Rx.test(XhrIn.responseText)) G_POPUP_BASIC.showBasic(XhrIn.responseText.replace(/^#[a-zA-Z]*#/gi, ''));
		}
	}
	
	return (true);
}


/*
@brief  Event-handler for created unused DataTable row.
@param  tr - TR-node; [OBJECT]
@param  rowData - Row data; [ARRAY]
@param  row - DataTables' internal index for the row. [NUMBER]
@return None.
*/
function onDataTableRowUnused(tr, rowData, row)
{
	var Unused = false;

	if(typeof rowData["status_code"] == "number")
	{
		Unused = (rowData["status_code"] == 0);
	}
	else if(typeof rowData["state_code"] == "number")
	{
		Unused = (rowData["state_code"] == 0);
	}
	
	if(Unused) $(tr).addClass("unused");
}


/*
@brief  Event-handler for click on Row.
@param  event - Event-object. [OBJECT]
@return None.
@details Make Row selected.
*/
function onDataTableRowSelected(event)
{
	$(this).toggleClass("selected");
	
	return (false);
}


/*
@brief  Clear Data Table.
@param  DataTableIn - DataTable. [OBJECT]
@return None.
@details Remove al event handler onClick for Rows
         DataTable.destroy()
*/
function clearDataTable(DataTableIn)
{
	if(typeof DataTableIn == "object")
	{
		if(DataTableIn)
		{
			$(DataTableIn.table().node()).find("tbody").off("click", "tr");
			DataTableIn.destroy();
		}
	}
}


/*
@brief  Clear select-list of DataForm.
@param  DataFormIn - DataForm; [OBJECT]
@param  ItemNameIn - name of form item. [STRING]
@return None.
*/
function clearDataFormSelect(DataFormIn, ItemNameIn)
{
	if(typeof DataFormIn == "object" && typeof ItemNameIn == "string")
	{
		if(DataFormIn && ItemNameIn.length)
		{
			var FillSet = { };
			FillSet[ItemNameIn] = DataFormIn.getListEmptyOneFillset();
			DataFormIn.fill(FillSet);
		}
	}
}


/*
@brief  Clear select-lists of DataForm.
@param  DataFormIn - DataForm; [OBJECT]
@param  SelClearSetsIn - asociative array of select-list names to be cleared. [OBJECT]
@return None.
*/
function clearDataFormSelects(DataFormIn, SelClearSetsIn)
{
	if(typeof DataFormIn == "object" && typeof SelClearSetsIn == "object")
	{
		if(DataFormIn && SelClearSetsIn)
		{
			for(var Key in SelClearSetsIn)
			{
				clearDataFormSelect(DataFormIn, Key);
			}
		}
	}
}


/*
@brief  Set DataForm.
@param  DataFormIn      - DataForm; [OBJECT]
@param  SelClearSetsIn  - asociative array of select-list names to be cleared; [OBJECT || NULL]
@param  InitResultsetIn - resultset or NULL to init.; [ARRAY || NULL]
@param  ResultsetIn     - resultset or NULL; [ARRAY || NULL]
@param  FillsetIn       - fillset or NULL. [ARRAY || NULL]
@return None.
@details Ex.: SelClearSetsIn  = { "location_id", "position_id" }
         Ex.: InitResultsetIn = { approved: (new Date()).format("isoDate") }
*/
function setDataForm(DataFormIn, SelClearSetsIn, InitResultsetIn, ResultsetIn, FillsetIn)
{
	if(typeof DataFormIn == "object")
	{
		if(DataFormIn)
		{
			clearDataFormSelects(DataFormIn, SelClearSetsIn);
			
			DataFormIn.reset();
			
			if(typeof InitResultsetIn == "object")
			{
				if(InitResultsetIn) DataFormIn.setResultset(InitResultsetIn);
			}
			
			if(typeof FillsetIn == "object")
			{
				if(FillsetIn)
				{
					if(typeof G_DEBUG == "boolean")
					{
						if(G_DEBUG)
						{
							console.log("DataForm::fill");
							console.log(JSON.stringify(FillsetIn));
						}
					}
					DataFormIn.fill(FillsetIn);
				}
			}
			
			if(typeof ResultsetIn == "object")
			{
				if(ResultsetIn)
				{
					if(typeof G_DEBUG == "boolean")
					{
						if(G_DEBUG)
						{
							console.log("DataForm.setResultset");
							console.log(JSON.stringify(ResultsetIn));
						}
					}
					DataFormIn.setResultset(ResultsetIn);
				}
			}
		}
	}
}


/*
@brief  Show DataForm.
@param  DataFormIn      - DataForm; [OBJECT]
@param  SelClearSetsIn       - array of names of select-lists to clear; [ARRAY]
@param  InitResultsetIn - resultset or NULL to init.; [ARRAY || NULL]
@param  ResultsetIn     - resultset or NULL; [ARRAY || NULL]
@param  FillsetIn       - fillset or NULL. [ARRAY || NULL]
@return None.
*/
function showDataForm(DataFormIn, SelClearSetsIn, InitResultsetIn, ResultsetIn, FillsetIn)
{
	if(typeof DataFormIn == "object")
	{
		if(DataFormIn)
		{
			setDataForm(DataFormIn, SelClearSetsIn, InitResultsetIn, ResultsetIn, FillsetIn);
			DataFormIn.show();
		}
	}
}


/*
@brief  Show DataForm by ID to ExtSettings.
@param  IDIn         - ID of target; [STRING]
@param  ResultsetIn  - resultset or NULL; [ARRAY || NULL]
@param  FillsetIn    - fillset or NULL. [ARRAY || NULL]
@return None.
*/
function showDataFormByID(IDIn, ResultsetIn, FillsetIn)
{
	if(isEngineTarget(IDIn))
	{
		showDataForm(G_ENGINE_TARGETS[IDIn]["DataForm"], G_ENGINE_TARGETS[IDIn]["SelClearSets"], G_ENGINE_TARGETS[IDIn]["InitResultset"], ResultsetIn, FillsetIn);
		if(typeof G_ENGINE_TARGETS[IDIn]["FuncShowDataForm"] == "function") G_ENGINE_TARGETS[IDIn]["FuncShowDataForm"](G_ENGINE_TARGETS[IDIn]["DataForm"]);
	}
}


/*
@brief  Error-handler of Ajax for DataForm.
@param  XMLHttpRequestIn - XMLHttpRequest-object; [OBJECT]
@param  TextStatusIn - status code; [STRING]
@param  ErrorThrownIn - error thrown. [STRING]
@return None.
*/
function ajaxDataFormError(XMLHttpRequestIn, TextStatusIn, ErrorThrownIn)
{
	if(typeof G_DEBUG == "boolean")
	{
		if(G_DEBUG)
		{
			console.log("DataForm::ajaxError");
			console.log((XMLHttpRequestIn.responseText).replace(/^#[a-zA-Z]*#/gi, ''));
		}
	}
	
	if(typeof G_POPUP_BASIC == "object")
	{
		if(G_POPUP_BASIC)
		{
			var Res = new jsResponseResult(XMLHttpRequestIn.responseText);
			if(Res.HaveMessage) G_POPUP_BASIC.showBasic(Res.Message);
		}
	}
}


/*
@brief  Success-handler of Ajax for DataForm.
@param  DataIn - data; [OBJECT || ARRAY]
@param  TextStatusIn - status code; [STRING]
@param  XMLHttpRequestIn - XMLHttpRequest-object. [OBJECT]
@return None.
*/
function ajaxDataFormSuccess(DataIn, TextStatusIn, XMLHttpRequestIn)
{
	if(typeof G_DEBUG == "boolean")
	{
		if(G_DEBUG)
		{
			console.log("DataForm::ajaxSuccess");
			console.log((XMLHttpRequestIn.responseText).replace(/^#[a-zA-Z]*#/gi, ''));
		}
	}
	
	var Res = new jsResponseResult(DataIn);
	
	if(Res.HaveMessage)
	{
		if(typeof G_POPUP_BASIC == "object")
		{
			if(G_POPUP_BASIC) G_POPUP_BASIC.showBasic(Res.Message);
		}
	}
	
	if(isEngineTarget(Res.TargetID))
	{
		if(G_ENGINE_TARGETS[Res.TargetID]["DataForm"]["AjaxOptions"]["data"]["idq"] == Res.idq)
		{
			switch(Res.idq)
			{
				case "insert_data":
				case "update_data":
					
					if(typeof G_ENGINE_TARGETS[Res.TargetID]["FuncRefreshView"] == "function") G_ENGINE_TARGETS[Res.TargetID]["FuncRefreshView"]();
					break;
					
				case "get_data_form":
				case "get_data_form_fillset":
					
					if(Res.Status)
					{
						showDataFormByID(Res.TargetID, Res.Data, Res.Fillset);
						G_ENGINE_TARGETS[Res.TargetID]["completed"] = true;
					}
					break;
					
				case "get_data_form_fillset_item":
					
					if(Res.Status) G_ENGINE_TARGETS[Res.TargetID]["DataForm"].fill(Res.Fillset);
					break;
			}
		}
	}
}


/*
@brief  Event-handler for button "Save" of DataForm.
@param  event - Event-object. [OBJECT]
@return None.
@details Node of event.target must be contain attribute "target-id" with ID of engine target!
         G_ENGINE_TARGETS[ID]["DataForm"]["idq"] must be set!
*/
function onDataFormSaveClicked(event)
{
	var TargetID = $(event.target).attr("target-id");
	
	if(isEngineTarget(TargetID))
	{
		var Res = G_ENGINE_TARGETS[TargetID]["DataForm"].getResultset();
		
		if(Res && G_ENGINE_TARGETS[TargetID]["idq"].length)
		{
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]              = Res;
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["target_id"] = TargetID;
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["idq"]       = G_ENGINE_TARGETS[TargetID]["idq"];
			G_ENGINE_TARGETS[TargetID]["DataForm"].ajax();
		}
	}
	
	return (true);
}


/*
@brief  Event-handler for button "Cancel" of DataForm.
@param  event - Event-object. [OBJECT]
@return None.
@details Node of event.target must be contain attribute "target-id" with ID of engine target!
*/
function onDataFormCancelClicked(event)
{
	var TargetID = $(event.target).attr("target-id");
	
	if(isEngineTarget(TargetID))
	{
		if(typeof G_ENGINE_TARGETS[TargetID]["FuncRefreshView"] == "function") G_ENGINE_TARGETS[TargetID]["FuncRefreshView"]();
	}
	
	return (true);
}


/*
@brief  Handler of event `Change` for an Item of DataForm.
@param  event - Event-object. [OBJECT]
@return None.
@details Node of event.target must be contain attribute "target-id" with ID of engine target!
*/
function onDataFormItemChanged(event)
{
	var TargetID = $(event.target).attr("target-id");
	
	if(isEngineTarget(TargetID))
	{
		var Res = G_ENGINE_TARGETS[TargetID]["DataForm"].getResultset();
		
		if(Res)
		{
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"] = Res;
			
			var Name = $(event.target).attr("name");
			var SelFillSets = getSelFillSets(TargetID, Name);
			if(SelFillSets)
			{
				clearDataFormSelects(G_ENGINE_TARGETS[TargetID]["DataForm"], SelFillSets);
				G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["fillset"] = SelFillSets;
			}
			
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["target_id"] = TargetID;
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["idq"]       = "get_data_form_fillset_item";
			G_ENGINE_TARGETS[TargetID]["DataForm"].ajax();
		}
	}
	
	return (true);
}


/*
@brief  Event-handler for button "AddData" of NavTools.
@param  event - Event-object. [OBJECT]
@return None.
@details Node of event.target must be contain attribute "target-id" with ID of engine target.
*/
function onAddDataClicked(event)
{
	var TargetID = $(event.target).attr("target-id");
	
	if(isEngineTarget(TargetID))
	{
		var Alias = "";
		
		if(typeof G_ENGINE_TARGETS[TargetID]["Alias"] == "string")
		{
			if(G_ENGINE_TARGETS[TargetID]["Alias"].length) Alias = (G_ENGINE_TARGETS[TargetID]["Alias"] + " :: ");
		}
		
		G_ENGINE_TARGETS[TargetID]["DataForm"].title((Alias + G_RES[G_LANG]["New"]));
		
		G_ENGINE_TARGETS[TargetID]["idq"] = "insert_data";
		
		var SelFillSets = ((isDataFormCompleted(TargetID)) ? getSelFillSets(TargetID, "FormCompleted") : getSelFillSets(TargetID, "FormNotCompleted"));
		
		if(SelFillSets)
		{
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"] = { };
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["target_id"] = TargetID;
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["idq"]       = "get_data_form_fillset";
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["fillset"]   = SelFillSets;
			G_ENGINE_TARGETS[TargetID]["DataForm"].ajax();
		}
		else
		{
			showDataFormByID(TargetID, null, null);
		}
	}
	
	return (true);
}


/*
@brief  Event-handler for button "EditData" of NavTools.
@param  event - Event-object. [OBJECT]
@return None.
@details Node of event.target must be contain attribute "target-id" with ID of engine target.
*/
function onEditDataClicked(event)
{
	var TargetID = $(event.target).attr("target-id");
	
	if(isEngineTarget(TargetID))
	{
		var Alias = "";
		
		if(typeof G_ENGINE_TARGETS[TargetID]["Alias"] == "string")
		{
			if(G_ENGINE_TARGETS[TargetID]["Alias"].length) Alias = (G_ENGINE_TARGETS[TargetID]["Alias"] + " :: ");
		}
		
		G_ENGINE_TARGETS[TargetID]["DataForm"].title((Alias + G_RES[G_LANG]["Edit"]));
		
		G_ENGINE_TARGETS[TargetID]["idq"] = "update_data";
		
		var Data = [];
		
		if(typeof G_ENGINE_TARGETS[TargetID]["DataTable"] == "object")
		{
			if(G_ENGINE_TARGETS[TargetID]["DataTable"]) Data = G_ENGINE_TARGETS[TargetID]["DataTable"].rows(".selected").data();
		}
		
		if(typeof G_DEBUG == "boolean")
		{
			if(G_DEBUG) console.log("EditData::Data.length=" + Data.length);
		}
		
		if(Data.length == 1)
		{
			if(typeof G_DEBUG == "boolean")
			{
				if(G_DEBUG) console.log(Data[0]);
			}
			
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"] = { };
			
			var KeyField    = G_ENGINE_TARGETS[TargetID]["KeyField"];
			var SelFillSets = ((isDataFormCompleted(TargetID)) ? getSelFillSets(TargetID, "FormCompleted") : getSelFillSets(TargetID, "FormNotCompleted"));
			
			if(SelFillSets)
			{
				G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["fillset"] = SelFillSets;
			}
			
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["target_id"] = TargetID;
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"]["idq"]       = "get_data_form";
			G_ENGINE_TARGETS[TargetID]["DataForm"]["AjaxOptions"]["data"][KeyField]    = Data[0][KeyField];
			G_ENGINE_TARGETS[TargetID]["DataForm"].ajax();
		}
		else
		{
			if(typeof G_POPUP_BASIC == "object")
			{
				if(G_POPUP_BASIC) G_POPUP_BASIC.showBasic(G_RES[G_LANG]["SelRowToEdit"]);
			}
		}
	}
	
	return (true);
}


/*
@brief  Reinit data form by target ID.
@param  IDIn - ID of target. [STRING]
@return None.
*/
function reinitDataFormByID(IDIn)
{
	if(isEngineTarget(IDIn))
	{
		G_ENGINE_TARGETS[IDIn]["DataForm"].reset();
		
		G_ENGINE_TARGETS[IDIn]["DataForm"]["AjaxOptions"]["data"] = { };
		
		var SelFillSets = ((isDataFormCompleted(IDIn)) ? getSelFillSets(IDIn, "FormCompleted") : getSelFillSets(IDIn, "FormNotCompleted"));
		if(SelFillSets)
		{
			G_ENGINE_TARGETS[IDIn]["DataForm"]["AjaxOptions"]["data"]["fillset"] = SelFillSets;
		}
		
		G_ENGINE_TARGETS[IDIn]["DataForm"]["AjaxOptions"]["data"]["target_id"] = IDIn;
		G_ENGINE_TARGETS[IDIn]["DataForm"]["AjaxOptions"]["data"]["idq"]       = "get_data_form_fillset_item";
		G_ENGINE_TARGETS[IDIn]["DataForm"].ajax();
	}
}


/*
@brief  Event-handler for button "RefreshDataView" of NavTools.
@param  event - Event-object. [OBJECT]
@return None.
@details Node of event.target must be contain attribute "target-id" with ID of engine target!
*/
function onRefreshDataViewClicked(event)
{
	var TargetID = $(event.target).attr("target-id");
	
	if(isEngineTarget(TargetID))
	{
		G_ENGINE_TARGETS[TargetID]["completed"] = false;
	}
	
	onDataFormCancelClicked(event);
	
	return (true);
}


