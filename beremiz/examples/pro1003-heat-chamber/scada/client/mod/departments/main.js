/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  Module: Client side - Departments.
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
*    + ui-res.js
*    + ui-engine.js
*/


//** GLOBAL VARIABLES

//URI
var G_DEPARTS_RESP_URI	  = "../mod/departments/resp.php";

//Nodes
var G_DEPARTS_BOX_NODE    = null;
var G_DEPARTS_TABLE_NODE  = null;
var G_DEPARTS_TOOLS_NODE  = null;
var G_DEPARTS_FORM_NODE   = null;

//Engine target ID
var G_DEPARTS_TARGET_ID	  = "Departments";

//Key fields
var G_DEPARTS_KEY_FIELD   = "department_id";

//Local resoutces
var G_DEPARTS_RES         = { ru: { Alias:"Подразделение" }
                             };  


//** FUNCTIONS

/*
@brief  Init. DataTable.
@param  None.
@return None.
*/
function initDepartsDataTable()
{
	clearDataTable(G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataTable"]);

	if(!G_DEPARTS_TABLE_NODE) G_DEPARTS_TABLE_NODE = $("#TableDeparts");
	
	var Opts = {   language: { url: G_LANG_DATA_TABLE },
				 lengthMenu: [ [15, 25, 50, 100, -1], [15, 25, 50, 100, G_RES[G_LANG]["All"]] ],
					  order: [ [ 1, "desc" ], [ 0, "desc" ] ],
			     pageLength: 15,
				  searching: false,
				 processing: true,
				 serverSide: true,
					   ajax: {    url: G_DEPARTS_RESP_URI,
							   method: "POST",
								 data: { idq: "get_data_table", target_id: G_DEPARTS_TARGET_ID }
								},
					columns: [ { data: G_DEPARTS_KEY_FIELD },
							   { data: "approved" },
							   { data: "department" },
							   { data: "note" }
							  ],
				 columnDefs: [ { targets: [2, 3], orderable: false }
							  ],
				 createdRow: onDataTableRowUnused
				};
	
	G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataTable"] = G_DEPARTS_TABLE_NODE.DataTable(Opts);
	
	G_DEPARTS_TABLE_NODE.on("xhr.dt", onDataTableXhr);
	G_DEPARTS_TABLE_NODE.find("tbody").on("click", "tr", onDataTableRowSelected);
}


/*
@brief  Refresh view.
@param  None.
@return None.
*/
function refreshDepartsView()
{
	G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataForm"].hide();
	initDepartsDataTable();
}


/*
@brief  Init. DataForm.
@param  None.
@return None.
*/
function initDepartsDataForm()
{
	if(typeof jsForm == "function")
	{
		var KeyField = G_DEPARTS_KEY_FIELD;
		
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataForm"]        = new jsForm("FormDepart");
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["KeyField"]        = KeyField;
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["Alias"]           = G_DEPARTS_RES[G_LANG]["Alias"];
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["InitResultset"]   = { approved:(new Date()).format("isoDate") };
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["completed"]       = false;
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["FuncRefreshView"] = refreshDepartsView;
		
		var ItemOpts = { };
		ItemOpts[KeyField]     = { ItemType: "text", DataType: "number", Allow: true };
		ItemOpts["state"]      = { ItemType: "select", DataType: "number", Allow: true };
		ItemOpts["approved"]   = { ItemType: "text", DataType: "string", Allow: true };
		ItemOpts["department"] = { ItemType: "text", DataType: "string", Allow: true };
		ItemOpts["note"]       = { ItemType: "text", DataType: "string", Allow: true };
		
		var AjaxOpts = { };
		AjaxOpts["url"]        = G_DEPARTS_RESP_URI;
		AjaxOpts["method"]     = "POST";
		AjaxOpts["dataType"]   = "json";
		AjaxOpts["mimeType"]   = "application/json";
		AjaxOpts["error"]      = ajaxDataFormError;
		AjaxOpts["success"]    = ajaxDataFormSuccess;
		AjaxOpts["data"]       = null;
		
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataForm"]["ItemOptions"] = ItemOpts;
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataForm"]["AjaxOptions"] = AjaxOpts;
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataForm"].AutoCreate     = true;
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataForm"].AutoScrollTo   = true;
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataForm"].initTitle("FormDepartTitle");
		G_ENGINE_TARGETS[G_DEPARTS_TARGET_ID]["DataForm"].setDatePicker("approved", {dateFormat: "yy-mm-dd", language: G_LANG, changeYear: true, showButtonPanel: true});
		
		$("#FormDepartSave").bind("click", onDataFormSaveClicked);
		$("#FormDepartCancel").bind("click", onDataFormCancelClicked);
	}
}


/*
@brief  Init. content.
@param  None.
@return None.
*/
function initDeparts()
{
	G_DEPARTS_BOX_NODE   = $("#BoxDeparts");
	G_DEPARTS_TOOLS_NODE = $("#ToolsDeparts");
	G_DEPARTS_FORM_NODE  = $("#FormDepart");
	
	addEngineTarget(G_DEPARTS_TARGET_ID, {});
	
	initDepartsDataForm();
	
	$("#AddDepart").bind("click", onAddDataClicked);
	$("#EditDepart").bind("click", onEditDataClicked);
	$("#RefreshDeparts").bind("click", onRefreshDataViewClicked);
}

