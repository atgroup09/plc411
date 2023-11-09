<?php

/*	PHP SCRIPT DOCUMENT
*	UTF-8
*/

/*   Module: Server side responder - Departments.
*
*    Copyright (C) 2019  ATgroup09 (atgroup09@gmail.com)
*
*    The PHP code in this page is free software: you can
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
*		- global variables:
*
*			+ $FL_DEBUG - on/off debug messages.
*
*
*		- libraries:
*
*			+ request/request.php:
*				 get_request_value_on_key().
*
*			+ sql/sql.php:
*				sql_limit().
*
*			+ db/mysql.php:
*				class dbMySQL.
*
*			+ db/mysql-table.php:
*				abstract class MySQLDBTable.
*
*			+ res/values.php:
*				class ResValues.
*
*
*		- modules:
*
*			+ mod_workstation/responder.php:
*				abstract class responder.
*/

/*	Global variables: none
*
*	Functions: none.
*/


/* PROTOCOL

	Request "get_data_table"

	-- request
	
		...
		draw (*)
		start (*)
		length (*)
		[columns][i][data] (*)
		[columns][i][searchable] (*)
		[columns][i][orderable] (*)
		[order][i][column] (*)
		[order][i][dir] (*)

	-- response (*)
	
		{            draw: draw,
		     recordsTotal: ...,
		  recordsFiltered: ...,
					 data: [ { Field1Name: Field1Value, ... },
							 ...
							]
		 }

		* DataTable protocol (see responder.php -> getJsDataTableColumnByID)


	Request "get_data_form"
	
	-- request
	
		id
		fillset["departments"]=... (*)

		* if the argument is set (any value), then will be get fillset-data

	-- response

		{   result: {  status: true|false,	* (true - OK, false - error)
					   message: ...
				     },
			  data: { Field1Name: Field1Value, ... },
		   fillset: { Field1Name: {   attrs: { AttrName: AttrValue, ... },
				                    options: [ { value: ..., text: ..., disabled: true||false, selected: true||false },
								               ...
								              ] ,
						              clear: true||false, * allow to clear select-list before fill it
						             append: true||false  * allow to append new options into select-list
						           },
					  ...
				     }
		 }


	Request "get_data_form_fillset"

	-- request
	
		fillset["departments"]=... (*)

		* if the argument is set (any value), then will be get fillset-data

	-- response

		{   result: {  status: true|false,	* (true - OK, false - error)
					   message: ...
				     },
		   fillset: { Field1Name: {   attrs: { AttrName: AttrValue, ... },
				                    options: [ { value: ..., text: ..., disabled: true||false, selected: true||false },
								               ...
								              ] ,
						              clear: true||false, * allow to clear select-list before fill it
						             append: true||false  * allow to append new options into select-list
						           },
					  ...
				     }
		 }


	Request "insert_data"

	-- request
	
		...

	-- response

		{ result: {  status: true|false,	* (true - OK, false - error)
					message: ...
				   }
		 }


	Request "update_data"

	-- request
	
		id
		...

	-- response

		{ result: {  status: true|false,	* (true - OK, false - error)
					message: ...
				   }
		 }


	Request "delete_data"

	-- request
	
		id (for one row)
		id[0-9]+ (for much rows)

	-- response

		{ result: {  status: true|false,	* (true - OK, false - error)
					message: ...
				   }
		 }
*/


//** GLOBAL VARIABLES


//** FUNCTIONS


//** CLASSES

class Resp extends responder {
	
	//Options
	
	//** files of resource values
	
	const R_STRINGS_FILE_NAME__STATUSES	  = "strings-statuses.xml";
	const R_STRINGS_FILE_TYPE__STATUSES	  = "xml";
	
	
	//Methods
	
	//** init. data form type.
	public function initDataFormType() {
		
	}
	
	//* called when a class creating.
	protected function onCreate() {
		
		$rqt = array(array("name" => "get_request_value_on_key", "type" => "function"),
					 array("name" => "sql_limit", "type" => "function"),
					 array("name" => "ResValues", "type" => "class"),
					 array("name" => "dbMySQL", "type" => "class"),
					 array("name" => "MySQLDBTable", "type" => "class"),
					 array("name" => "DbTableDepartmentsItem", "type" => "class"),
					 array("name" => "DbTableDepartments", "type" => "class")
					);
		
		$this->responseFormat = self::RESPONSE_FORMAT__JSON;
		
		$this->checkExistenceResult = $this->checkingExistence($rqt);
		
		$this->initSysConfig();
		$this->initDataSource();
		$this->initMySQLDBHelper();
		
		$this->initR();
		
		$this->initWorkStationID();
		$this->initRequestID();
		$this->initTargetID();
		$this->initSelectorID();
		
		$this->initDataFormType();
		$this->initDataTableType();
		
		$this->initLimitRows();
		$this->initOrderBy();
		
		if(!is_object($this->sysConfig))
		{
			$this->checkExistenceResult = false;
			$this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Error init. the system configuration!");
		}
		
		if(!is_object($this->dataSource))
		{
			$this->checkExistenceResult = false;
			$this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Error init. the data source!");
		}
		
		if(!is_object($this->dbHelper))
		{
			$this->checkExistenceResult = false;
			$this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Error init. the object 'dbHelper'!");
		}
		
		if(!is_object($this->R))
		{
			$this->checkExistenceResult = false;
			$this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Error init. the object 'R'!");
		}
		
		if($this->checkExistenceResult)
		{
			//** read resource values
			
			$this->R->fileType = self::R_STRINGS_FILE_TYPE__MAIN;
			$this->R->filePath = ResValues::_getFilePath($this->resValuesDir, self::R_STRINGS_FILE_NAME__MAIN, true, true);
			if(!ResValues::_checkFile($this->R->filePath)) $this->R->filePath = ResValues::_getFilePath($this->resValuesDir, self::R_STRINGS_FILE_NAME__MAIN, false, false);
			$this->R->readValuesFromFile();
			
			$this->R->fileType = self::R_STRINGS_FILE_TYPE__STATUSES;
			$this->R->filePath = ResValues::_getFilePath($this->resValuesDir, self::R_STRINGS_FILE_NAME__STATUSES, true, true);
			if(!ResValues::_checkFile($this->R->filePath)) $this->R->filePath = ResValues::_getFilePath($this->resValuesDir, self::R_STRINGS_FILE_NAME__STATUSES, false, false);
			$this->R->readValuesFromFile();
			
			
			//** read additional input arguments
		}
	}
	
	//* called when a class destroying.
	protected function onDestroy() {
		
	}
	
	/*
	@brief  Get the number of data items.
	@param  None.
	@return The number of items (0 by default). [INTEGER]
	@details
	        WHERE-fields: id, status
	*/
	private function countData() {
		
		$Res = 0;
		
		if($this->checkExistenceResult && is_object($this->dbHelper))
		{
			$Table		 = new DbTableDepartments($this->dbHelper);
			$WhereFields = array(array("key" => "^".(DbTableDepartmentsItem::FIELD__ID)."$", "field" => DbTableDepartmentsItem::FIELD__ID, "type" => "int", "compare" => '='),
								 array("key" => "^".(DbTableDepartmentsItem::FIELD__STATUS)."$", "field" => DbTableDepartmentsItem::FIELD__STATUS, "type" => "int", "compare" => '='),
								 array("key" => "^".(DbTableDepartmentsItem::FIELD__APPROVED), "field" => DbTableDepartmentsItem::FIELD__APPROVED, "type" => "date", "compare" => "between", "between_alt" => '=')
								 );
			
			$Res = $Table->count($WhereFields, $_REQUEST, DbTableDepartmentsItem::FIELD__ID);
			$Table->sendError("#error#");
		}
		
		return ($Res);
	}
	
	/*
	@brief  Get data items.
	@param  None.
	@return Array of items (class "DbTableItem") or NULL. [ARRAY || NULL]
	@details
	        WHERE-fields: id, status
	*/
	private function getData() {
		
		if($this->checkExistenceResult && is_object($this->dbHelper))
		{
			$Table		 = new DbTableDepartments($this->dbHelper);
			$WhereFields = array(array("key" => "^".(DbTableDepartmentsItem::FIELD__ID)."$", "field" => DbTableDepartmentsItem::FIELD__ID, "type" => "int", "compare" => '='),
								 array("key" => "^".(DbTableDepartmentsItem::FIELD__STATUS)."$", "field" => DbTableDepartmentsItem::FIELD__STATUS, "type" => "int", "compare" => '='),
								 array("key" => "^".(DbTableDepartmentsItem::FIELD__APPROVED), "field" => DbTableDepartmentsItem::FIELD__APPROVED, "type" => "date", "compare" => "between", "between_alt" => '=')
								 );
			
			$SqlOrderBy = $this->getJsDataTableOrderBy();
			$SqlLimit   = ((isset($_REQUEST["start"]) && isset($_REQUEST["length"])) ? sql_limit((int)$_REQUEST["start"], (int)$_REQUEST["length"], false) : null);
			
			return ($Table->getItems($WhereFields, $_REQUEST, null, null, $SqlOrderBy, $SqlLimit));
		}
		
		return (null);
	}
	
	/*
	@brief  Get data form.
	@param  None.
	@return None.
	@details Get and pack data for jqForm, send packet to client.
	*/
	public function getDataForm() {
		
		$Pack = array("result" => array("status" => false, "message" => null), "data" => null, "fillset" => null);
		
		if($this->checkExistenceResult)
		{
			$Data = $this->getData();
			
			if(is_array($Data))
			{
				if(count($Data))
				{
					$Table	   = new DbTableDepartments($this->dbHelper);
					$TableItem = $Table->extendItem($Data[0]);
					
					$Pack["data"] = array();
					$Pack["data"][DbTableDepartmentsItem::FIELD__ID]	     = $TableItem->Fields[DbTableDepartmentsItem::FIELD__ID]["value"];
					$Pack["data"][DbTableDepartmentsItem::FIELD__STATUS]     = $TableItem->Fields[DbTableDepartmentsItem::FIELD__STATUS]["value"];
					$Pack["data"][DbTableDepartmentsItem::FIELD__APPROVED]   = $TableItem->Fields[DbTableDepartmentsItem::FIELD__APPROVED]["value"];
					$Pack["data"][DbTableDepartmentsItem::FIELD__DEPARTMENT] = $TableItem->Fields[DbTableDepartmentsItem::FIELD__DEPARTMENT]["value"];
					$Pack["data"][DbTableDepartmentsItem::FIELD__NOTE]       = $TableItem->Fields[DbTableDepartmentsItem::FIELD__NOTE]["value"];
					
					$Pack["result"]["status"] = true;
				}
			}
		}
		
		if(!$Pack["result"]["status"]) $Pack["result"]["message"] = $this->R->getValue("no_data", "No Data");
		
		$this->sendResponse(self::RESPONSE_TYPE__OK, $Pack);
	}
	
	/*
	@brief  Get data table.
	@param  None.
	@return None.
	@details Get and pack data for jqDataTable, send packet to client.
	*/
	public function getDataTable() {
		
		$Pack = array("draw" => $_REQUEST["draw"], "recordsTotal" => 0, "recordsFiltered" => 0, "data" => array());
		
		if($this->checkExistenceResult)
		{
			$Pack["recordsTotal"] = $this->countData();
			$Data = $this->getData();
			
			if(is_array($Data) && $Pack["recordsTotal"] > 0)
			{
				$Table		= new DbTableDepartments($this->dbHelper);
				$TableItem  = null;
				$PackItem	= null;
				
				for($i=0; $i<count($Data); $i++)
				{
					$TableItem = $Table->extendItem($Data[$i]);
					$TableItem->normalizeNULL();
					
					$PackItem = array();
					$PackItem[DbTableDepartmentsItem::FIELD__ID]		     = $TableItem->Fields[DbTableDepartmentsItem::FIELD__ID]["value"];
					$PackItem[DbTableDepartmentsItem::FIELD__STATUS."_code"] = $TableItem->Fields[DbTableDepartmentsItem::FIELD__STATUS]["value"];
					$PackItem[DbTableDepartmentsItem::FIELD__STATUS] 		 = $this->R->getValue(("status_").($TableItem->Fields[DbTableDepartmentsItem::FIELD__STATUS]["value"]), $TableItem->Fields[DbTableDepartmentsItem::FIELD__STATUS]["value"]);
					$PackItem[DbTableDepartmentsItem::FIELD__APPROVED]       = $TableItem->Fields[DbTableDepartmentsItem::FIELD__APPROVED]["value"];
					$PackItem[DbTableDepartmentsItem::FIELD__DEPARTMENT]     = $TableItem->Fields[DbTableDepartmentsItem::FIELD__DEPARTMENT]["value"];
					$PackItem[DbTableDepartmentsItem::FIELD__NOTE]           = $TableItem->Fields[DbTableDepartmentsItem::FIELD__NOTE]["value"];
					
					array_push($Pack["data"], $PackItem);
				}
				
				if(!$i) $Pack["recordsTotal"] = 0;
				$Pack["recordsFiltered"] = $Pack["recordsTotal"];
			}
		}
		
		$this->sendResponse(self::RESPONSE_TYPE__OK, $Pack);
	}
	
	/*
	@brief  Check valid data of item.
	@param  $ItemIn - item object. [OBJECT]
	@return true is valid, false - invalid. [BOOLEAN]
	*/
	private function checkItem($ItemIn = null) {
		
		return (true);
	}
	
	/*
	@brief  Insert data from $_REQUEST into DB.
	@param  None.
	@return None.
	*/
	public function insertData() {
		
		$Pack = array("result" => array("status" => false, "message" => null));
		
		if($this->checkExistenceResult && is_object($this->dbHelper))
		{
			$Table = new DbTableDepartments($this->dbHelper);
			$Item  = $Table->newItem(null);
			$Item->setValues($_REQUEST);
			
			if($this->checkItem($Item))
			{
				$Pack["result"]["status"] = $Table->saveItem($Item);
			}
		}
		
		if(!$Pack["result"]["status"]) $Pack["result"]["message"] = $this->R->getValue("error_record", "error save data");
		
		$this->sendResponse(self::RESPONSE_TYPE__OK, $Pack);
	}
	
	/*
	@brief  Update data from $_REQUEST in DB.
	@param  None.
	@return None.
	*/
	public function updateData() {
		
		$Pack = array("result" => array("status" => false, "message" => null));
		
		if($this->checkExistenceResult && is_object($this->dbHelper))
		{
			$Table = new DbTableDepartments($this->dbHelper);
			$Item  = $Table->newItem(null);
			$Item->setValues($_REQUEST);
			
			if($Item->Fields[DbTableDepartmentsItem::FIELD__ID] > 0 && $this->checkItem($Item))
			{
				$Pack["result"]["status"] = $Table->saveItem($Item);
			}
		}
		
		if(!$Pack["result"]["status"]) $Pack["result"]["message"] = $this->R->getValue("error_update", "error update data");
		
		$this->sendResponse(self::RESPONSE_TYPE__OK, $Pack);
	}
	
	/*
	@brief  Remove data from DB by ID from $_REQUEST.
	@param  None.
	@return None.
	*/
	public function deleteData() {
		
		$Pack = array("result" => array("status" => false, "message" => null));
		
		if($this->checkExistenceResult && is_object($this->dbHelper))
		{
			$Table = new DbTableDepartments($this->dbHelper);
			
			$Pack["result"]["status"] = $Table->delItems($_REQUEST);
			
			if(!$Pack["result"]["status"]) $Pack["result"]["message"] = $this->R->getValue("error_remove", "error remove data");
			
			$this->sendResponse(self::RESPONSE_TYPE__OK, $Pack);
		}
	}
	
	//* start the responder.
	public function start() {
		
		if($this->checkExistenceResult)
		{
			switch($this->requestID)
			{
				case "get_data_table":
					
					$this->getDataTable();
					break;
				
				case "get_data_form":
					
					$this->getDataForm();
					break;
				
				case "insert_data":
					
					$this->insertData();
					break;
					
				case "update_data":
					
					$this->updateData();
					break;
					
				/* physical removing the data is not recommended
				 * use field `state` to set state of inactivity data
				case "delete_data":
					
					$this->deleteData();
					break;
				*/
			}
		}
	}
	
	/*
	@brief  Constructor.
	@param  $sysConfigFile_in - sysconfig file;	[STRING || NULL]
	@param  $sysConfigName_in - sysconfig name;	[STRING || NULL]
	@param  $dataSourceType_in - datasource type;	[STRING || NULL]
	@param  $dataSourceName_in - datasource name;	[STRING || NULL]
	@param  $resValuesDir_in - path to directory of resource values.	[STRING || NULL]
	@return None.
	*/
	function __construct($sysConfigFile_in = null, $sysConfigName_in = null, $dataSourceType_in = null, $dataSourceName_in = null, $resValuesDir_in = null) {
		
		parent::__construct($sysConfigFile_in, $sysConfigName_in, $dataSourceType_in, $dataSourceName_in, $resValuesDir_in);
	}
	
	/*
	@brief  Destructor.
	@param  None.
	@return None.
	*/
	function __destruct() {
		
		parent::__destruct();
	}
}

?>
