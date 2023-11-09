<?php

//TEXT CODING - UTF-8

//PHP SCRIPT DOCUMENT

/*   db-table.
*
*    Copyright (C) 2017  ATgroup09 (atgroup09@gmail.com)
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
*				~ mysql_fetch_assoc();
*				~ mysql_free_result().
*
*			+ types/types.php:
*				~ type_of_datetime();
*				~ types_data_formatting().
*
*			+ types/string.php:
*				~ string_processing().
*
*			+ db/mysql-table.php:
*				~ abstract class MySQLDBTable.
*/


//** GLOBAL VARIABLES



//** FUNCTIONS



//** CLASSES

class DbTableItem {
	
	//Options
	
	//* support of functionality	[BOOLEAN]
	protected $HaveFunc;
	
	//** fields
	public $Fields;
	
	//Constructor and Destructor
	
	//*	input:
	//*			FieldsIn - list of fields.	[ARRAY]
	//*	note:
	//*
	function __construct($FieldsIn = null) {
		
		global $FL_DEBUG;
		
		$_Rqt = array(array("name" => "mysql_fetch_assoc", "type" => "function"),
					  array("name" => "types_normalize_array", "type" => "function"),
					  array("name" => "MySQLDBTable", "type" => "class")
					 );
		
		$this->HaveFunc = false;
		$this->Fields   = ((is_array($FieldsIn)) ? $FieldsIn : null);
		
		if(function_exists("types_checking_existence"))
		{
			$this->HaveFunc = types_checking_existence($_Rqt, "[".(basename(__FILE__)).(" -> ").(__METHOD__).(" ").(__LINE__)."]");
		}
		else
		{
			if($FL_DEBUG) echo("#error#Error! Function 'types_checking_existence()' is not exists! [".(basename(__FILE__)).(" -> ").(__METHOD__).(" ").(__LINE__)."]");
		}
	}
	
	function __destruct() {
		
	}
	
	
	//Methods
	
	//*	method:	get list of field parameters.
	//*	input:
	//*			$ActionTypeIn	- action type:	[INTEGER]
	//*								= MySQLDBTable::ACTION_SELECT,
	//*								= MySQLDBTable::ACTION_INSERT,
	//*								= MySQLDBTable::ACTION_UPDATE;
	//*
	//*			$TableTypeIn - table type for action MySQLDBTable::ACTION_SELECT:	[INTEGER]
	//*								= MySQLDBTable::TABLE (by default),
	//*								= MySQLDBTable::VIEW.
	//*	output:
	//*			list of field parameters or NULL.	[ARRAY || NULL]
	//*	note:
	//*			+ supported additional options:
	//*				"only" = "insert"
	//*				"only" = "update"
	public function getFieldParams($ActionTypeIn = -1, $TableTypeIn = 0, $FieldsIn = null) {
		
		global $FL_DEBUG;
		
		$Res = null;
		
		if($this->HaveFunc && is_array($this->Fields))
		{
			$_Act       = ((is_int($ActionTypeIn)) ? $ActionTypeIn : -1);
			$_TableType = ((is_int($TableTypeIn)) ? $TableTypeIn : -1);
			
			$_Access    = (($_Act == MySQLDBTable::ACTION_INSERT || $_Act == MySQLDBTable::ACTION_UPDATE) ? "w" : "any");
			$_ObjType   = (($_TableType == MySQLDBTable::VIEW) ? "any" : "table");
			$_Only      = null;
			
			foreach($this->Fields as $k => $v)
			{
				if(!empty($k))
				{
					if(isset($this->Fields[$k]["access"]) && isset($this->Fields[$k]["obj_type"]))
					{
						if(($_Access == "any" || ($_Access == $this->Fields[$k]["access"])) &&  ($_ObjType == "any" || ($_ObjType == $this->Fields[$k]["obj_type"])))
						{
							$_Only = "any";
							if(isset($this->Fields[$k]["only"]))
							{
								if(is_string($this->Fields[$k]["only"])) $_Only = $this->Fields[$k]["only"];
							}
							
							if(!(($_Act == MySQLDBTable::ACTION_INSERT && $_Only == "update") || ($_Act == MySQLDBTable::ACTION_UPDATE && $_Only == "insert")))
							{
								$Res[$k] = $this->Fields[$k];
							}
						}
					}
				}
			}
		}
		
		return ($Res);
	}
	
	//*	method:	get associative array of values (without normalization).
	//*	input:
	//*			none.
	//*	output:
	//*			associative array of values.	[ARRAY]
	//*	note:
	public function getValuesRaw() {
		
		$Res = array();
		
		if(is_array($this->Fields))
		{
			foreach($this->Fields as $k => $v)
			{
				if(!empty($k))
				{
					if(isset($v["value"]))
					{
						$Res[$k] = $v["value"];
					}
				}
			}
		}
		
		return ($Res);
	}
	
	//*	method: get value of field.
	//*	input:
	//*			$FieldIn - field name.	[STRING]
	//*	output:
	//*			value of the field or NULL.	[ANY TYPE || NULL]
	//*	note:
	//*
	public function getValue($FieldIn = null) {
		
		if(is_string($FieldIn) && is_array($this->Fields))
		{
			if(isset($this->Fields[$FieldIn]))
			{
				if(isset($this->Fields[$FieldIn]["value"]))
				{
					return ($this->Fields[$FieldIn]["value"]);
				}
			}
		}
		
		return (null);
	}
	
	//*	method:	set values from associative array (without normalization).
	//*	input:
	//*			$ValuesIn - associative array of values.	[ARRAY].
	//*	output:
	//*			none.
	//*	note:
	public function setValuesRaw($ValuesIn) {
		
		if(is_array($ValuesIn))
		{
			foreach($ValuesIn as $k => $v)
			{
				if(!empty($k))
				{
					if(isset($this->Fields[$k]))
					{
						$this->Fields[$k]["value"] = $v;
					}
				}
			}
		}
	}
	
	//*	method: set value of field.
	//*	input:
	//*			$FieldIn - field name;	[STRING]
	//*			$ValueIn - field value.	[ANY TYPE]
	//*	output:
	//*			none.
	//*	note:
	//*
	public function setValue($FieldIn = null, $ValueIn = null) {
		
		if(is_string($FieldIn))
		{
			if(!empty($FieldIn))
			{
				$_Values = array($FieldIn => $ValueIn);
				$this->setValues($_Values);
			}
		}
	}
	
	//*	method:	clear the values (raw).
	//*	input:
	//*			none.
	//*	output:
	//*			none.
	//*	note:
	public function clearValuesRaw() {
		
		if($this->HaveFunc)
		{
			$_Fields = $this->getFieldParams(MySQLDBTable::ACTION_SELECT, MySQLDBTable::VIEW);
			$_BuffArr = array();
			
			types_normalize_array($_Fields, $_BuffArr);
			$this->setValuesRaw($_BuffArr);
		}
	}
	
	//*	method:	normalize the values (raw).
	//*	input:
	//*			none.
	//*	output:
	//*			none.
	//*	note:
	public function normalizeValuesRaw() {
		
		if($this->HaveFunc)
		{
			$_Fields  = $this->getFieldParams(MySQLDBTable::ACTION_SELECT, MySQLDBTable::VIEW);
			$_BuffArr = $this->getValuesRaw();
			
			types_normalize_array($_Fields, $_BuffArr);
			$this->setValuesRaw($_BuffArr);
		}
	}
	
	//*	method: get values.
	//*	input:
	//*			$TableTypeIn - table type for action MySQLDBTable::ACTION_SELECT:	[INTEGER]
	//*								= MySQLDBTable::TABLE (by default),
	//*								= MySQLDBTable::VIEW.
	//*	output:
	//*			associative array of values.	[ARRAY]
	//*	note:
	//*
	public function getValues($TableTypeIn = -1) {
		
		$Res = array();
		
		$this->normalizeValuesRaw();
		
		if($this->HaveFunc)
		{
			$_TableType = ((is_int($TableTypeIn)) ? $TableTypeIn : MySQLDBTable::TABLE);
			$_Fields    = $this->getFieldParams(MySQLDBTable::ACTION_SELECT, $_TableType);
			
			$_BuffArr   = $this->getValuesRaw();
			
			//copy this buffer into output array
			foreach($_Fields as $k => $v)
			{
				if(!empty($k))
				{
					if(isset($_BuffArr[$k]))
					{
						$Res[$k] = $_BuffArr[$k];
					}
				}
			}
		}
		
		return ($Res);
	}
	
	//*	method: set values.
	//*	input:
	//*			$ValuesIn - associative array of values.	[ARRAY]
	//*	output:
	//*			none.
	//*	note:
	//*
	public function setValues($ValuesIn = null) {
		
		//$this->clearValuesRaw();
		
		if($this->HaveFunc && is_array($ValuesIn))
		{
			$_FieldsAll = $this->getFieldParams(MySQLDBTable::ACTION_SELECT, MySQLDBTable::VIEW);
			
			$_Fields = array();
			$_Values = array();
			
			//* key names	[ARRAY || NULL]
			//** [0] is key name
			//** [1] is field alias
			//** [2] is field name
			$_Keys = array(null, null, null);
			
			if(is_array($_FieldsAll))
			{
				//copy input array into the buffer
				foreach($_FieldsAll as $k => $v)
				{
					if(!empty($k) && is_array($v))
					{
						$_Keys[0] = $k;
						$_Keys[1] = (isset($v["field_alias"]) ? $v["field_alias"] : null);
						$_Keys[2] = (isset($v["field"]) ? $v["field"] : null);
						
						for($i=0; $i<count($_Keys); $i++)
						{
							if(!empty($_Keys[$i]))
							{
								if(isset($ValuesIn[$_Keys[$i]]))
								{
									$_Fields[$k] = $v;
									$_Values[$k] = $ValuesIn[$_Keys[$i]];
									break;
								}
							}
						}
					}
				}
				
				types_normalize_array($_Fields, $_Values);
				$this->setValuesRaw($_Values);
			}
		}
	}
	
	//*	method: set values from a resultset.
	//*	input:
	//*			$ResultsetIn - a resultset.	[RESOURCE]
	//*	output:
	//*			none.
	//*	note:
	//*
	public function setValuesFromResultset($ResultsetIn = 0) {
		
		if($this->HaveFunc && is_resource($ResultsetIn))
		{
			$_BuffArr = mysql_fetch_assoc($ResultsetIn);
			if(!is_array($_BuffArr)) $_BuffArr = array();
			
			$this->setValues($_BuffArr);
		}
		else
		{
			$this->clearValuesRaw();
		}
	}
}


class DbTable extends MySQLDBTable {
	
	//Options
	
	//* support of functionality	[BOOLEAN]
	protected $HaveFunc;
	
	//** fields
	public $Fields;
	
	//** key fields
	public $KeyFields;
	
	
	//Constructor and Destructor
	
	//*	input:
	//*			$DbHelperIn - a DBHelper;	[dbMySQL]
	//*			$DbTableIn  - a table name (self::TABLE_NAME by default);	[STRING || NULL]
	//*			$DbViewIn   - a view name (self::VIEW_NAME by default).	[STRING || NULL]
	//*	note:
	//*
	function __construct($DbHelperIn = null, $DbTableIn = null, $DbViewIn = null) {
		
		global $FL_DEBUG;
		
		$_Rqt = array(array("name" => "mysql_free_result", "type" => "function"),
					  array("name" => "DbTableItem", "type" => "class")
					  );
		
		$this->HaveFunc = false;
		
		if(function_exists("types_checking_existence"))
		{
			$this->HaveFunc = types_checking_existence($_Rqt, "[".(basename(__FILE__)).(" -> ").(__METHOD__).(" ").(__LINE__)."]");
		}
		else
		{
			if($FL_DEBUG) echo("#error#Error! Function 'types_checking_existence()' is not exists! [".(basename(__FILE__)).(" -> ").(__METHOD__).(" ").(__LINE__)."]");
		}
		
		parent::__construct($DbHelperIn, $DbTableIn, $DbViewIn);
	}
	
	function __destruct() {
		
		parent::__destruct();
	}
	
	
	//Methods
	
	//*	method: get new item.
	//*	input:
	//*			$ValuesIn - list of values, resultset or NULL.	[ARRAY || RESOURCE || NULL]
	//*	output:
	//*			object of class "DbTableItem".	[OBJECT]
	//*	note:
	//*
	public function newItem($ValuesIn = null) {
		
		$Res = null;
		
		if($this->HaveFunc)
		{
			$Res = new DbTableItem($this->Fields);
			
			if(is_array($ValuesIn))
			{
				$Res->setValues($ValuesIn);
			}
			elseif(is_resource($ValuesIn))
			{
				$Res->setValuesFromResultset($ValuesIn);
			}
		}
		
		return ($Res);
	}
	
	//*	method: check an item.
	//*	input:
	//*			$KeyValuesIn - values of key fields ( array("key" => "value", ...) ).	[ASSOCIATIVE ARRAY]
	//*	output:
	//*			true if the item is exists, otherwise - false.
	//*	note:
	//*
	public function checkItem($KeyValuesIn = null) {
		
		$Res = false;
		
		if($this->HaveFunc && is_array($KeyValuesIn))
		{
			$Res = $this->check($this->KeyFields, $KeyValuesIn);
			$this->sendError("#error#");
		}
		
		return ($Res);
	}
	
	//*	method: get item.
	//*	input:
	//*			$WhereIn	- a "WHERE"-string (without operator "WHERE")	[STRING || ARRAY || NULL]
	//*							or list of WHERE-fields
	//*							or NULL;
	//*			$ValuesIn	- list of values for WHERE-fields or $_REQUEST (if $where_in is list of WHERE-fields) or NULL.	[ARRAY || NULL]
	//*	output:
	//*			object of class "DbTableItem" or NULL.	[OBJECT || NULL]
	//*	note:
	//*
	public function getItemRaw($WhereIn = null, $ValuesIn = null) {
		
		$Res = null;
		
		if($this->HaveFunc)
		{
			if($this->openDB())
			{
				$_Resultset = $this->select(null, $WhereIn, $ValuesIn, null, null, null, "1");
				
				if($_Resultset)
				{
					$Res = new DbTableItem($this->Fields);
					$Res->setValuesFromResultset($_Resultset);
					
					mysql_free_result($_Resultset);
				}
				
				$this->closeDB();
			}
			
			$this->sendError("#error#");
		}
		
		return ($Res);
	}
	
	//*	method: get item.
	//*	input:
	//*			$KeyValuesIn - values of key fields ( array("key" => "value", ...) ).	[ASSOCIATIVE ARRAY]
	//*	output:
	//*			object of class "DbTableItem" or NULL.	[OBJECT || NULL]
	//*	note:
	//*
	public function getItem($KeyValuesIn = null) {
		
		return (($this->HaveFunc && is_array($KeyValuesIn)) ? $this->getItemRaw($this->KeyFields, $KeyValuesIn) : null);
	}
	
	//*	method: get list of items.
	//*	input:
	//*			$FieldsIn	- a list of returned fields or NULL (all fields);	[ARRAY || NULL]
	//*			$WhereIn	- a "WHERE"-string (without operator "WHERE")	[STRING || ARRAY || NULL]
	//*							or list of WHERE-fields
	//*							or NULL;
	//*			$ValuesIn	- list of values for WHERE-fields or $_REQUEST (if $where_in is list of WHERE-fields) or NULL;	[ARRAY || NULL]
	//*			$GroupByIn	- a filter declaring how to group rows, formatted as an SQL GROUP BY clause (excluding the GROUP BY itself); passing null will cause the rows to not be grouped; [STRING || NULL]
	//*			$HavingIn	- a filter declare which row groups to include in the cursor, if row grouping is being used, formatted as an SQL HAVING clause (excluding the HAVING itself); passing null will cause all row groups to be included, and is required when row grouping is not being used;	[STRING || NULL]
	//*			$OrderByIn	- how to order the rows, formatted as an SQL ORDER BY clause (excluding the ORDER BY itself) or NULL;	[STRING || NULL]
	//*			$LimitIn	- limits the number of rows returned by the query, formatted as LIMIT clause.	[STRING || NULL]
	//*	output:
	//*			list of objecst of class "DbTableItem" or NULL.	[ARRAY || NULL]
	//*	note:
	//*
	public function getItemsRaw($FieldsIn = null, $WhereIn = null, $ValuesIn = null, $GroupByIn = null, $HavingIn = null, $OrderByIn = null, $LimitIn = null) {
		
		$Res = null;
		
		if($this->HaveFunc)
		{
			if($this->openDB())
			{
				$_Resultset = $this->select($FieldsIn, $WhereIn, $ValuesIn, $GroupByIn, $HavingIn, $OrderByIn, $LimitIn);
				
				if($_Resultset)
				{
					$_Item	= null;
					$Res	= array();
					
					while(($_Row = mysql_fetch_assoc($_Resultset)))
					{
						$_Item = new DbTableItem($this->Fields);
						$_Item->setValues($_Row);
						
						array_push($Res, $_Item);
					}
					
					mysql_free_result($_Resultset);
				}
				
				$this->closeDB();
			}
			
			$this->sendError("#error#");
		}
		
		return ($Res);
	}
	
	//*	method: get list of items.
	//*	input:
	//*			$WhereIn	- a "WHERE"-string (without operator "WHERE")	[STRING || ARRAY || NULL]
	//*							or list of WHERE-fields
	//*							or NULL;
	//*			$ValuesIn	- list of values for WHERE-fields or $_REQUEST (if $where_in is list of WHERE-fields) or NULL;	[ARRAY || NULL]
	//*			$GroupByIn	- a filter declaring how to group rows, formatted as an SQL GROUP BY clause (excluding the GROUP BY itself); passing null will cause the rows to not be grouped; [STRING || NULL]
	//*			$HavingIn	- a filter declare which row groups to include in the cursor, if row grouping is being used, formatted as an SQL HAVING clause (excluding the HAVING itself); passing null will cause all row groups to be included, and is required when row grouping is not being used;	[STRING || NULL]
	//*			$OrderByIn	- how to order the rows, formatted as an SQL ORDER BY clause (excluding the ORDER BY itself) or NULL;	[STRING || NULL]
	//*			$LimitIn	- limits the number of rows returned by the query, formatted as LIMIT clause.	[STRING || NULL]
	//*	output:
	//*			list of objecst of class "DbTableItem" or NULL.	[ARRAY || NULL]
	//*	note:
	//*
	public function getItems($WhereIn = null, $ValuesIn = null, $GroupByIn = null, $HavingIn = null, $OrderByIn = null, $LimitIn = null) {
		
		return ($this->getItemsRaw(null, $WhereIn, $ValuesIn, $GroupByIn, $HavingIn, $OrderByIn, $LimitIn));
	}
	
	//*	method: save (insert/update) an item.
	//*	input:
	//*			$ItemIn - an object of class "DbTableItem".	[OBJECT]
	//*	output:
	//*			true on success or false.	[BOOLEAN]
	//*	note:
	//*
	public function saveItem($ItemIn = null) {
		
		$Res = false;
		
		if($this->HaveFunc && is_object($ItemIn))
		{
			if(is_a($ItemIn, "DbTableItem"))
			{
				$ItemIn->normalizeValuesRaw();
				
				$_Values = $ItemIn->getValues(MySQLDBTable::TABLE);
				
				$_CheckVal = $this->checkItem($_Values);
				
				if(empty($this->errorStr))
				{
					if($this->openDB())
					{
						if(!$_CheckVal)
						{
							$_Fields = $ItemIn->getFieldParams(MySQLDBTable::ACTION_INSERT);
							$Res     = $this->insert($_Fields, $_Values);
						}
						else
						{
							$_Fields = $ItemIn->getFieldParams(MySQLDBTable::ACTION_UPDATE);
							$Res     = $this->update($_Fields, $_Values, $this->KeyFields);
						}
						
						$this->closeDB();
					}
					
					$this->sendError("#error#");
				}
			}
		}
		
		return ($Res);
	}
	
	//*	method: remove items by ID of row.
	//*	input:
	//*			$KeyValuesIn - list of values for WHERE-fields (ID of rows) or $_REQUEST (if $where_in is list of WHERE-fields) or NULL.	[ARRAY || NULL]
	//*	output:
	//*			true on success or false.	[BOOLEAN]
	//*	note:
	//*
	public function delItems($KeyValuesIn = null) {
		
		$Res = false;
		
		if($this->openDB())
		{
			$Res = $this->delete($this->KeyFields, $KeyValuesIn, null);
			$this->closeDB();
		}
		
		$this->sendError("#error#");
		
		return ($Res);
	}
	
	//*	method: remove an item.
	//*	input:
	//*			$ItemIn - an object of class "DbTableItem".	[OBJECT]
	//*	output:
	//*			true on success or false.	[BOOLEAN]
	//*	note:
	//*
	public function delItem($ItemIn = null) {
		
		$Res = false;
		
		if(is_object($ItemIn))
		{
			if(is_a($ItemIn, "DBTableItem"))
			{
				$ItemIn->normalizeValuesRaw();
				
				$_Values = $ItemIn->getValues(MySQLDBTable::TABLE);
				
				$Res = $this->delItems($_Values);
			}
		}
		
		return ($Res);
	}
}


?>
