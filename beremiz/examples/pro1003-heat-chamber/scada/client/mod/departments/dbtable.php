<?php

/*	PHP SCRIPT DOCUMENT
*	UTF-8
*/

/*   Module: Server side DB-helper - Departments.
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

/*	dependencies:
*
*		- global variables:
*
*			+ $FL_DEBUG - on/off debug messages.
*
*		- libraries:
*
*			+ PHP:
*				mysql_fetch_assoc()
*				mysql_free_result()
*
*			+ types/types.php:
*				type_of_datetime()
*				types_data_formatting()
*
*			+ types/string.php:
*				string_processing()
*
*			+ db/mysql-table.php:
*				abstract class MySQLDBTable
*
*			+ dbtable.php:
*				class DbTableItem
*				class DbTable
*/


//** GLOBAL VARIABLES



//** FUNCTIONS



//** CLASSES

class DbTableDepartmentsItem extends DbTableItem {
	
	//Options
	
	//* fields
	const FIELD__ID			 = "department_id";
	const FIELD__TIMESTAMP	 = "time_stamp";
	const FIELD__APPROVED    = "approved";
	const FIELD__STATUS		 = "state";
	const FIELD__DEPARTMENT  = "department";
	const FIELD__NOTE        = "note";
	
	//* statuses
	const STATUS__NOT_USED	 = 0;
	const STATUS__USED		 = 1;

	
	/*
	@brief  Constructor.
	@param  FieldsIn - list of fields.	[ARRAY]
	@return None.
	*/
	function __construct($FieldsIn = null) {
		
		parent::__construct($FieldsIn);
	}
	
	/*
	@brief  Destructor.
	@param  None.
	@return None.
	*/
	function __destruct() {
		
	}
	
	/*
	@brief  Normalize Status.
	@param  $StatusIn - status. [ANY TYPE]
	@return Normalized status (0 by default). [INTEGER]
	*/
	public static function _normalizeStatus($StatusIn) {
		
		if(is_int($StatusIn))
		{
			if($StatusIn == self::STATUS__USED) return (self::STATUS__USED);
		}
		
		if(is_string($StatusIn))
		{
			if($StatusIn == (("").(self::STATUS__USED))) return (self::STATUS__USED);
		}
		
		return (self::STATUS__NOT_USED);
	}
	
	/*
	@brief  Refresh TimeStamp.
	@param  None.
	@return None.
	*/
	public function refreshTimeStamp() {
		
		return (date("Y-m-d H:i:s"));
	}
	
	/*
	@brief  Clear values.
	@param  None.
	@return None.
	*/
	public function clear() {
		
		$this->clearValuesRaw();
		$this->refreshTimeStamp();
	}
	
	/*
	@brief  Normalize limites.
	@param  None.
	@return None.
	*/
	public function normalizeLimits() {
		
		if(empty($this->Fields[self::FIELD__TIMESTAMP]["value"])) $this->refreshTimeStamp();
		if(!is_string($this->Fields[self::FIELD__TIMESTAMP]["value"])) $this->refreshTimeStamp();
		
		$this->Fields[self::FIELD__STATUS]["value"] = self::_normalizeStatus($this->Fields[self::FIELD__STATUS]["value"]);
	}
	
	/*
	@brief  Normalize values.
	@param  None.
	@return None.
	*/
	public function normalize() {
		
		$this->normalizeValuesRaw();
		$this->normalizeLimits();
	}
	
	/*
	@brief  Normalize NULL-values.
	@param  None.
	@return None.
	@details For string values.
	*/
	public function normalizeNULL($ReNullIn = null) {
		
		$this->normalize();
		
		$ReNull = ((is_string($ReNullIn)) ? $ReNullIn : "---");
		
		if(is_null($this->Fields[self::FIELD__APPROVED]["value"])) $this->Fields[self::FIELD__APPROVED]["value"] = $ReNull;
		if(is_null($this->Fields[self::FIELD__DEPARTMENT]["value"])) $this->Fields[self::FIELD__DEPARTMENT]["value"] = $ReNull;
	}
}


class DbTableDepartments extends DbTable {
	
	//Options
	
	const TABLE_NAME = "norm_departments";
	const VIEW_NAME	 = null;
	
	
	/*
	@brief  Constructor.
	@param  $DbHelperIn - a DBHelper;	[dbMySQL]
	@param  $DbTableIn  - a table name (self::TABLE_NAME by default);	[STRING || NULL]
	@param  $DbViewIn   - a view name (self::VIEW_NAME by default).	[STRING || NULL]
	@return None.
	*/
	function __construct($DbHelperIn = null, $DbTableIn = null, $DbViewIn = null) {
		
		$_DbTable = ((is_string($DbTableIn)) ? $DbTableIn : self::TABLE_NAME);
		$_DbView  = ((is_string($DbViewIn)) ? $DbViewIn : self::VIEW_NAME);
		
		parent::__construct($DbHelperIn, $_DbTable, $_DbView);
		
		//FIELDS
		$this->Fields = array("department_id" => array("key" => "department_id", "field" => "department_id", "type" => "int", "default" => 0, "value" => 0, "access" => "r", "obj_type" => "table"),
							  "time_stamp"    => array("key" => "time_stamp", "field" => "time_stamp", "type" => "datetime", "default" => null, "value" => null, "access" => "r", "obj_type" => "table"),
							  "approved"      => array("key" => "approved", "field" => "approved", "type" => "date", "default" => null, "value" => null, "access" => "w", "obj_type" => "table"),
							  "state"	      => array("key" => "state", "field" => "state", "type" => "int", "default" => 0, "value" => 0, "access" => "w", "obj_type" => "table"),
							  "department"	  => array("key" => "department", "field" => "department", "type" => "string", "default" => null, "value" => null, "access" => "w", "obj_type" => "table"),
							  "note"	      => array("key" => "note", "field" => "note", "type" => "string", "default" => null, "value" => null, "access" => "w", "obj_type" => "table")
							  );
		
		//KEY FIELDS
		$this->KeyFields = array(array("key" => "^department_id[0-9]*$", "field" => "department_id", "type" => "int", "compare" => '=')
								 );
	}
	
	/*
	@brief  Destructor.
	@param  None.
	@return None.
	*/
	function __destruct() {
		
		parent::__destruct();
	}
	
	/*
	@brief  Copy data from an object of class DbTableItem into new DbTableDepartmentsItem.
	@param  $DbTableItemIn - an object of class "DbTableItem".	[OBJECT]
	@return New object of class DbTableDepartmentsItem. [OBJECT]
	*/
	public function extendItem($DbTableItemIn = null) {
		
		$Res = new DbTableDepartmentsItem($this->Fields);
		
		if(is_object($DbTableItemIn))
		{
			if(is_a($DbTableItemIn, "DBTableItem"))
			{
				$Values = $DbTableItemIn->getValues(MySQLDBTable::VIEW);
				$Res->setValues($Values);
			}
		}
		
		return ($Res);
	}
	
	/*
	@brief  Get list of data.
	@param  None.
	@return Array of items (class "DbTableItem") or NULL. [ARRAY || NULL]
	@details
		       WHERE: `status` = 1
		    ORDER BY: `department` ASC
	*/
	public function getData() {
		
		$WhereFields = array(array("key" => "^".(DbTableDepartmentsItem::FIELD__STATUS)."$", "field" => DbTableDepartmentsItem::FIELD__STATUS, "type" => "int", "compare" => '=')
							 );
		
		$WhereValues = array();
		$WhereValues[DbTableDepartmentsItem::FIELD__STATUS] = DbTableDepartmentsItem::STATUS__USED;
		
		$SqlOrderBy  = "`".(DbTableDepartmentsItem::FIELD__DEPARTMENT)."` ASC";
		
		return ($this->getItems($WhereFields, $WhereValues, null, null, $SqlOrderBy, null));
	}
	
	/*
	@brief  Get fillset for select-list of DataForm.
	@param  $IDIn - ID of selected option or -1. [INTEGER]
	@return Fillset. [ARRAY]
	@details attr. `value` = DbTableDepartmentsItem::FIELD__ID;
			 attr. `text`  = DbTableDepartmentsItem::FIELD__DEPARTMENT;
	*/
	public function getFillset($IDIn = -1) {
		
		$Res = array("options" => array(), "clear" => true, "append" => true);
		
		//first option is empty
		array_push($Res["options"], array("value" => "", "text" => "---"));
		
		$Data = $this->getData();
		
		if(is_array($Data))
		{
			$TableItem  = null;
			$Option     = null;
			$ID			= ((is_int($IDIn)) ? $IDIn : -1);
			
			for($i=0; $i<count($Data); $i++)
			{
				$TableItem = $this->extendItem($Data[$i]);
				$TableItem->normalizeNULL();
				
				$Option = array();
				$Option["value"] = $TableItem->Fields[DbTableDepartmentsItem::FIELD__ID]["value"];
				$Option["text"]  = $TableItem->Fields[DbTableDepartmentsItem::FIELD__DEPARTMENT]["value"];
				if($Option["value"] == $ID) $Option["selected"] = true;
				
				array_push($Res["options"], $Option);
			}
		}
		
		return ($Res);
	}
}


?>
