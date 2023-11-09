<?php

/*	PHP SCRIPT DOCUMENT
*	UTF-8
*/

/*   Module: Server side responder.
*
*    Copyright (C) 2014-2019  ATgroup09 (atgroup09@gmail.com)
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
*			+ types/types.php:
*				~ types_checking_existence().
*
*			+ request/request.php:
*				~ get_request_value_on_key().
*
*			+ mysql.php:
*				~ class dbMySQL.
*
*			+ datasources/sysconfig.php:
*				~ class sysconfig.
*
*			+ res/values.php:
*				~ class ResValues.
*/

/* 2019-07-19
	+ get and send TargetID ($_REQUEST["target_id"])
	+ send requestID ($_REQUEST["idq"])
*/



//** GLOBAL VARIABLES


//** FUNCTIONS


//** CLASSES

abstract class responder {
	
	//Options
	
	//** response data format
	const RESPONSE_FORMAT__URL		= 0;	//#idq=IDW#a1=A1&a2=A2...
	const RESPONSE_FORMAT__JSON		= 1;	//JSON structure
	
	//** response types
	const RESPONSE_TYPE__ERROR		= 0;
	const RESPONSE_TYPE__OK			= 1;
	
	//** data form types
	const DATA_FORM_TYPE__NEW		= 0;
	const DATA_FORM_TYPE__EDIT		= 1;
	
	//** data table types
	const DATA_TABLE_TYPE__BLANK	= 0;
	const DATA_TABLE_TYPE__EDIT		= 1;
	
	//** resource values files
	const R_STRINGS_FILE_NAME__MAIN	= "strings.xml";
	const R_STRINGS_FILE_TYPE__MAIN	= "xml";
	
	//** data row colors
	public static $DATA_ROW__COLORS	= array("#E7E7E7", null);
	
	//* language	[STRING || NULL]
	public $language;
	
	//* sysconfig file	[STRING || NULL]
	public $sysConfigFile;
	
	//* sysconfig name	[STRING || NULL]
	public $sysConfigName;
	
	//* datasource type	[STRING || NULL]
	public $dataSourceType;
	
	//* datasource name	[STRING || NULL]
	public $dataSourceName;
	
	//* path to directory of resource values	[STRING || NULL]
	public $resValuesDir;
	
	//* sysconfig	[OBJECT]
	//** object of class "sysconfig"
	protected $sysConfig;
	
	//* datasource	[OBJECT || NULL]
	//** object of class "datasource"
	protected $dataSource;
	
	//* DBHelper	[OBJECT || NULL]
	//** object of class "dbMySQL"
	protected $dbHelper;
	
	//* ID of workstation	[STRING]
	protected $workStationID;
	
	//* ID of request	[STRING]
	protected $requestID;
	
	//* ID of engine target	[STRING]
	protected $targetID;
	
	//* ID of selector	[STRING]
	protected $selectorID;
	
	//* data form type	[INTEGER]
	protected $dataFormType;
	
	//* data table type	[INTEGER]
	protected $dataTableType;
	
	//* limit of rows	[INTEGER]
	protected $limitRows;
	
	//* offset of rows	[INTEGER]
	protected $limitOffset;
	
	//* display all rows	[BOOLEAN]
	protected $displayAll;
	
	//* order by	[STRING || NULL]
	//** "field-name ASC|DESC"
	protected $orderBy;
	
	//* resources	[OBJECT || NULL]
	//** object of class "ResValues"
	protected $R;
	
	//* result of check of required functions/classes	[BOOLEAN]
	protected $checkExistenceResult;
	
	//* data row color ID	[INTEGER]
	protected $dataRowColorID;
	
	//* response format	[INTEGER]
	protected $responseFormat;
	
	
	//Methods
	
	//* method:	send response.
	//* input:
	//*			$type_in		- response type:	[INTEGER]
	//*								= RESPONSE_TYPE__ERROR (by default),
	//*								= RESPONSE_TYPE__OK;
	//*			$response_in	- response content.	[STRING || ARRAY]
	//* output:
	//*			none.
	//* note:
	//*			if response format is RESPONSE_FORMAT__JSON and $response_in is string, then used next JSON-structure:
	//*				array("error" => $response_in) - if $type_in is RESPONSE_TYPE__ERROR
	//*				array("data"  => $response_in) - if $type_in is RESPONSE_TYPE__OK
	//*
	public function sendResponse($type_in = 0, $response_in = null) {
		
		if(!empty($response_in))
		{
			$response_format	= ((is_int($this->responseFormat)) ? $this->responseFormat : self::RESPONSE_FORMAT__URL);
			$response_type		= ((is_int($type_in)) ? $type_in : self::RESPONSE_TYPE__ERROR);
			
			if(!function_exists("json_encode") || $response_format == self::RESPONSE_FORMAT__URL)
			{
				if(is_string($response_in))
				{
					if($response_type == self::RESPONSE_TYPE__OK)
					{
						echo("#idq=".$this->requestID."#{$response_in}");
					}
					else
					{
						echo("#error#{$response_in}");
					}
				}
			}
			else
			{
				$jsonStr  = null;
				$jsonPack = null;
				
				if(is_string($response_in))
				{
					$jsonPack = (($response_type == self::RESPONSE_TYPE__OK) ? array("data" => $response_in) : array("error" => $response_in));
				}
				elseif(is_array($response_in))
				{
					$jsonPack = $response_in;
				}
				
				if($jsonPack)
				{
					$jsonPack["idq"]       = $this->requestID;
					$jsonPack["target_id"] = $this->targetID;
					$jsonStr = json_encode($jsonPack, JSON_UNESCAPED_UNICODE);
					echo($jsonStr);
				}
			}
		}
	}
	
	//*	method: check of required functions, classes.
	//*	input:
	//*			$required_in - list of required functions/classes.	[ARRAY]
	//*	output:
	//*			true if OK, otherwise - error.	[BOOLEAN]
	//*	note:
	//*
	protected function checkingExistence($required_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("types_checking_existence"))
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Function 'types_checking_existence()' is not exists! [responder.php -> class responder]");
			return false;
		}
		
		return types_checking_existence($required_in, "[responder.php -> class responder]");
	}
	
	//* method:	init. sysconfig.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initSysConfig() {
		
		global $FL_DEBUG;
		
		$this->sysConfig = null;
		
		if(class_exists("sysconfig"))
		{
			$this->sysConfig = new sysconfig();
			$this->sysConfig->setValuesFromFile($this->sysConfigFile, $this->sysConfigName);
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Class 'sysconfig' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	init. datasource.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*			if datasource name or/and type is empty or not string, then used selected datasource in the sysconfig!
	//*
	public function initDataSource() {
		
		$this->dataSource = null;
		
		if(is_object($this->sysConfig))
		{
			$dsType = null;
			$dsName = null;
			
			if(!empty($this->dataSourceType))
			{
				if(is_string($this->dataSourceType)) $dsType = $this->dataSourceType;
			}
			
			if(!empty($this->dataSourceName))
			{
				if(is_string($this->dataSourceName)) $dsName = $this->dataSourceName;
			}
			
			$this->dataSource = ((!empty($dsType) && !empty($dsName)) ? $this->sysConfig->getDatasource($dsName, $dsType) : $this->sysConfig->getSelectedDatasource());
		}
	}
	
	//* method:	get MySQL DB-helper.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initMySQLDBHelper() {
		
		global $FL_DEBUG;
		
		$this->dbHelper = null;
		
		if(class_exists("dbMySQL"))
		{
			if(is_object($this->dataSource))
			{
				$this->dbHelper = new dbMySQL();
				$this->dbHelper->params = $this->dataSource->params;
			}
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Class 'dbMySQL' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	init. resource values object.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initR() {
		
		global $FL_DEBUG;
		
		$this->R = null;
		
		if(class_exists("ResValues"))
		{
			$this->R = new ResValues();
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Class 'ResValues' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	init. ID of a workstation.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initWorkStationID() {
		
		global $FL_DEBUG;
		
		$this->workStationID = "unknown";
		
		if(function_exists("get_request_value_on_key"))
		{
			$buff = get_request_value_on_key("arm_id");
			if(!empty($buff)) $this->workStationID = $buff;
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Function 'get_request_value_on_key()' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	init. ID of a request.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initRequestID() {
		
		global $FL_DEBUG;
		
		$this->requestID = "unknown";
		
		if(function_exists("get_request_value_on_key"))
		{
			$buff = get_request_value_on_key("idq");
			if(!empty($buff)) $this->requestID = $buff;
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Function 'get_request_value_on_key()' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	init. ID of engine target.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initTargetID() {
		
		global $FL_DEBUG;
		
		$this->targetID = "unknown";
		
		if(function_exists("get_request_value_on_key"))
		{
			$buff = get_request_value_on_key("target_id");
			if(!empty($buff)) $this->targetID = $buff;
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Function 'get_request_value_on_key()' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	init. ID of a selector form.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initSelectorID() {
		
		global $FL_DEBUG;
		
		$this->selectorID = "unknown";
		
		if(function_exists("get_request_value_on_key"))
		{
			$buff = get_request_value_on_key("selector");
			if(!empty($buff)) $this->selectorID = $buff;
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Function 'get_request_value_on_key()' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	init. data table type.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initDataTableType() {
		
		$this->dataTableType = self::DATA_TABLE_TYPE__BLANK;
		
		if(function_exists("get_request_value_on_key"))
		{
			$buff = get_request_value_on_key("table_type");
			
			if(!empty($buff))
			{
				if($buff == "edit") $this->dataTableType = self::DATA_TABLE_TYPE__EDIT;
			}
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Function 'get_request_value_on_key()' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	init. limit of rows.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initLimitRows() {
		
		$this->limitRows	= -1;
		$this->limitOffset	= 0;
		$this->displayAll	= false;
		
		if(function_exists("get_request_value_on_key"))
		{
			$buff = get_request_value_on_key("display_all");
			if(!empty($buff))
			{
				if(is_string($buff)) $this->displayAll = true;
			}
			
			if(!$this->displayAll)
			{
				$this->limitRows	= (int)get_request_value_on_key("limit_rows");
				$this->limitOffset	= (int)get_request_value_on_key("limit_offset");
			}
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Function 'get_request_value_on_key()' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	init. order by.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function initOrderBy() {
		
		$this->orderBy = null;
		
		if(function_exists("get_request_value_on_key"))
		{
			$buff = get_request_value_on_key("order_value");
			
			if(!empty($buff))
			{
				if(is_string($buff))
				{
					$direction		= "ASC";
					$this->orderBy	= "`{$buff}`";
					$buff			= get_request_value_on_key("order_direction");
					
					if(is_string($buff))
					{
						if($buff == "desc" || $buff == "Desc" || $buff == "DESC") $direction = "DESC";
					}
					
					$this->orderBy.= " ".($direction);
				}
			}
		}
		else
		{
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Function 'get_request_value_on_key()' not exists! [responder.php -> class responder]");
		}
	}
	
	//* method:	switch data row color.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	protected function switchDataRowColor() {
		
		$this->dataRowColorID++;
		
		if($this->dataRowColorID > (count(self::$DATA_ROW__COLORS)-1)) $this->dataRowColorID = 0;
	}
	
	//* method:	get data row color.
	//* input:
	//*			none.
	//* output:
	//*			 data row color or NULL.	[STRING || NULL]
	//* note:
	//*
	protected function getDataRowColor() {
		
		if($this->dataRowColorID > (count(self::$DATA_ROW__COLORS)-1)) $this->dataRowColorID = 0;
		
		return self::$DATA_ROW__COLORS[$this->dataRowColorID];
	}
	
	
	//** JsDataTable protocol
	//*
	//* $_REQUEST["draw"]    - draw counter [NUMBER]
	//* $_REQUEST["start"]   - start point in the current data set [NUMBER]
	//* $_REQUEST["length"]  - number of records that the table can display in the current draw [NUMBER]
	//* $_REQUEST["columns"] - array defining all columns in the table [ARRAY]
	//* $_REQUEST["columns"][i]["data"]       - column name [STRING]
	//* $_REQUEST["columns"][i]["searchable"] - true if this column is searchable [BOOLEAN]
	//* $_REQUEST["columns"][i]["orderable"]  - true if this column is orderable [BOOLEAN]
	//* $_REQUEST["order"] - array defining how many columns are being ordered upon [ARRAY]
	//* $_REQUEST["order"][i][column] - column to which ordering should be applied (index reference to $DT_Columns) [NUMBER]
	//* $_REQUEST["order"][i][dir]    - ordering direction for this column ("asc", "desc")	[STRING]
	
	//*	method: get column options (JS DataTable protocol).
	//*	input:
	//*			$IdxIn - index of column in $_REQUEST["columns"] (0 ...).	[INTEGER]
	//*	output:
	//*			normalized column options or NULL.	[ARRAY || NULL]
	//*	note:
	//*
	protected function getJsDataTableColumnByID($IdxIn = -1) {
		
		$Res = null;
		
		if(isset($_REQUEST["columns"]) && is_int($IdxIn))
		{
			if(is_array($_REQUEST["columns"]) && $IdxIn >= 0)
			{
				if($IdxIn < count($_REQUEST["columns"]))
				{
					if(is_array($_REQUEST["columns"][$IdxIn]))
					{
						if(!empty($_REQUEST["columns"][$IdxIn]["data"]))
						{
							if(is_string($_REQUEST["columns"][$IdxIn]["data"]))
							{
								$Res = array();
								$Res["data"]		= $_REQUEST["columns"][$IdxIn]["data"];
								$Res["searchable"]	= false;
								$Res["orderable"]	= false;
								
								if(!empty($_REQUEST["columns"][$IdxIn]["searchable"]))
								{
									if(is_string($_REQUEST["columns"][$IdxIn]["searchable"]))
									{
										if($_REQUEST["columns"][$IdxIn]["searchable"] == "true") $Res["searchable"] = true;
									}
								}
								
								if(isset($_REQUEST["columns"][$IdxIn]["orderable"]))
								{
									if(is_string($_REQUEST["columns"][$IdxIn]["orderable"]))
									{
										if($_REQUEST["columns"][$IdxIn]["orderable"] == "true") $Res["orderable"] = true;
									}
								}
							}
						}
					}
				}
			}
		}
		
		return ($Res);
	}
	
	//*	method: get "ORDER BY"-string (JS DataTable protocol).
	//*	input:  none.
	//*	output:
	//*			"ORDER BY"-string or NULL.	[STRING || NULL]
	//*	note:
	//*
	protected function getJsDataTableOrderBy() {
		
		$Res = null;
		
		if(isset($_REQUEST["order"]))
		{
			if(is_array($_REQUEST["order"]))
			{
				$ColOpts   = null;
				$FieldName = null;
				$FieldDir  = null;
				
				for($i=0; $i<count($_REQUEST["order"]); $i++)
				{
					if(!isset($_REQUEST["order"][$i]))    continue;
					if(!is_array($_REQUEST["order"][$i])) continue;
					
					if(isset($_REQUEST["order"][$i]["column"]))
					{
						$ColOpts = $this->getJsDataTableColumnByID((int)$_REQUEST["order"][$i]["column"]);
						
						if($ColOpts)
						{
							$FieldName = $ColOpts["data"];
							$FieldDir  = "ASC";
							
							if(!empty($_REQUEST["order"][$i]["dir"]))
							{
								if(is_string($_REQUEST["order"][$i]["dir"]))
								{
									if($_REQUEST["order"][$i]["dir"] == "desc") $FieldDir  = "DESC";
								}
							}
							
							if(empty($Res)) $Res = "`{$FieldName}` {$FieldDir}";
							else $Res.= ", `{$FieldName}` {$FieldDir}";
						}
					}
				}
			}
		}
		
		return ($Res);
	}
	
	/*
	@brief  Get data value from pack["data"] of DataForm.
	@param  $PackIn - link to pack of data; [ARRAY]
	@param  $KeyIn - key to pack["data"]. [STRING]
	@return data value. [STRING || NUMBER || NULL]
	*/
	protected function getDataFormPackValue(&$PackIn = null, $KeyIn = null) {
		
		if(is_array($PackIn) && !empty($KeyIn))
		{
			if(isset($PackIn["data"]) && is_string($KeyIn))
			{
				if(isset($PackIn["data"][$KeyIn])) return ($PackIn["data"][$KeyIn]);
			}
		}
		
		return (null);
	}
	
	/*
	@brief  Get data value from pack["data"] of DataForm as signed integer.
	@param  $PackIn - link to pack of data; [ARRAY]
	@param  $KeyIn - key to pack["data"]. [STRING]
	@return data value or -1. [INTEGER]
	*/
	protected function getDataFormPackInt(&$PackIn = null, $KeyIn = null) {
		
		if(is_array($PackIn) && !empty($KeyIn))
		{
			if(isset($PackIn["data"]) && is_string($KeyIn))
			{
				if(isset($PackIn["data"][$KeyIn])) return ((int)$PackIn["data"][$KeyIn]);
			}
		}
		
		return (-1);
	}
	
	/*
	@brief  Get data value from pack["data"] of DataForm as unsigned integer.
	@param  $PackIn - link to pack of data; [ARRAY]
	@param  $KeyIn - key to pack["data"]. [STRING]
	@return data value or 0. [INTEGER]
	*/
	protected function getDataFormPackUint(&$PackIn = null, $KeyIn = null) {
		
		$Res = $this->getDataFormPackInt($PackIn, $KeyIn);
		return (($Res >= 0) ? $Res : 0);
	}
	
	/*
	@brief  Get value from $_REQUEST as signed integer.
	@param  $KeyIn - key to $_REQUEST, where contains ID. [STRING]
	@return ID or -1. [INTEGER]
	*/
	protected function getRequestInt($KeyIn = null) {
		
		if(!empty($KeyIn))
		{
			if(is_string($KeyIn))
			{
				if(isset($_REQUEST[$KeyIn])) return ((int)$_REQUEST[$KeyIn]);
			}
		}
		
		return (-1);
	}
	
	/*
	@brief  Get value from $_REQUEST as unsigned integer.
	@param  $KeyIn - key to $_REQUEST, where contains ID. [STRING]
	@return ID or 0. [INTEGER]
	*/
	protected function getRequestUint($KeyIn = null) {
		
		$Res = $this->getRequestInt($KeyIn);
		return (($Res >= 0) ? $Res : 0);
	}
	
	//* method:	init. data form type.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	abstract public function initDataFormType();
	
	//* method:	called when a class creating.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	abstract protected function onCreate();
	
	//* method:	called when a class destroying.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	abstract protected function onDestroy();
	
	//* method:	start the responder.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	abstract public function start();
	
	
	//Constructor and Destructor
	
	//*	input:
	//*			$sysConfigFile_in	- sysconfig file;	[STRING || NULL]
	//*			$sysConfigName_in	- sysconfig name;	[STRING || NULL]
	//*			$dataSourceType_in	- datasource type;	[STRING || NULL]
	//*			$dataSourceName_in	- datasource name;	[STRING || NULL]
	//*			$resValuesDir_in	- path to directory of resource values.	[STRING || NULL]
	//*	note:
	//*
	function __construct($sysConfigFile_in = null, $sysConfigName_in = null, $dataSourceType_in = null, $dataSourceName_in = null, $resValuesDir_in = null) {
		
		$this->language					= null;
		
		$this->sysConfigFile			= ((is_string($sysConfigFile_in)) ? $sysConfigFile_in : null);
		$this->sysConfigName			= ((is_string($sysConfigName_in)) ? $sysConfigName_in : null);
		$this->sysConfig				= null;
		
		$this->dataSourceType			= ((is_string($dataSourceType_in)) ? $dataSourceType_in : null);
		$this->dataSourceName			= ((is_string($dataSourceName_in)) ? $dataSourceName_in : null);
		$this->dataSource				= null;
		
		$this->dbHelper					= null;
		
		$this->resValuesDir				= ((is_string($resValuesDir_in)) ? $resValuesDir_in : null);
		$this->R						= null;
		
		$this->workStationID			= "unknown";
		$this->requestID				= "unknown";
		$this->targetID					= "unknown";
		$this->selectorID				= "unknown";
		
		$this->dataFormType				= self::DATA_FORM_TYPE__NEW;
		$this->dataTableType			= self::DATA_TABLE_TYPE__BLANK;
		
		$this->limitRows				= -1;
		$this->limitOffset				= 0;
		$this->displayAll				= false;
		
		$this->orderBy					= null;
		
		$this->checkExistenceResult		= false;
		
		$this->dataRowColorID			= 0;
		
		$this->onCreate();
	}
	
	function __destruct() {
		
		$this->onDestroy();
		
		unset($this->language);
		
		unset($this->sysConfigFile);
		unset($this->sysConfigName);
		unset($this->sysConfig);
		
		unset($this->dataSourceType);
		unset($this->dataSourceName);
		unset($this->dataSource);
		
		unset($this->dbHelper);
		
		unset($this->resValuesDir);
		unset($this->R);
		
		unset($this->workStationID);
		unset($this->requestID);
		unset($this->selectorID);
		
		unset($this->dataFormType);
		unset($this->dataTableType);
		
		unset($this->limitRows);
		unset($this->limitOffset);
		unset($this->displayAll);
		
		unset($this->orderBy);
		
		unset($this->checkExistenceResult);
		
		unset($this->dataRowColorID);
	}
}


?>
