<?php

/*	PHP DOCUMENT
*
*
*	TEXT CODING - UTF-8
*
*	BEST VIEWED WITH A:
*		- tabulation  - 4,
*		- font family - monospace 10.
*/


/*   Library: MySQL table/view.
*
*    Copyright (C) 2014  ATgroup09 (atgroup09@gmail.com)
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
*			+ mysql.php:
*				~ class dbMySQL.
*
*			+ sql.php:
*				~ sql_select(),
*				~ sql_insert(),
*				~ sql_update(),
*				~ sql_delete().
*/

/*	Global variables: none
*
*	Functions: none.
*
*	Classes:
*
*		+ abstract class MySQLDBTable:
*
*			input arguments:
*				dbHelper_in	- a DBHelper;	[dbMySQL]
*				dbTable_in	- a table name;	[STRING]
*				dbView_in   - a view name.	[STRING]
*/


//** GLOBAL VARIABLES



//** FUNCTIONS



//** CLASSES

abstract class MySQLDBTable {
	
	//Options
	
	//** table types
	const TABLE				= 0;
	const VIEW				= 1;
	
	//** action ID
	const ACTION_SELECT		= 0;
	const ACTION_INSERT		= 1;
	const ACTION_UPDATE		= 2;
	const ACTION_DELETE		= 3;
	
	//** statuses
	const STATUS_OFF		= 0;
	const STATUS_ON			= 1;
	public static $STATUSES	= array("off", "on"); 
	
	//* error number	[INTEGER]
	public $errorNo;
	
	//* error string	[STRING]
	public $errorStr;
	
	//* DB helper	[dbMySQL]
	protected $dbHelper;
	
	//* DB table (TABLE)	[STRING]
	//** used for:
	//**  - SELECT/CHECK (if dbView == null),
	//**  - INSERT,
	//**  - UPDATE,
	//**  - DELETE.
	protected $dbTable;
	
	//* DB view (VIEW)	[STRING]
	protected $dbView;
	
	//* locking the table/view since the specified time (by UNIX_TIMESTAMP)	[INTEGER]
	//** if the current time >= the specified time, then the table/view will be locked
	//** if the value <= 0, then the table/view is always available (by default)
	protected $dbLockByTimeStamp;
	
	
	//Methods
	
	//* method:	clear errors.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function clearErrors() {
		
		$this->errorNo	= 0;
		$this->errorStr	= '';
	}
	
	//*	method: send error string.
	//*	input:
	//*			$prefix_in - a prefix.	[STRING || NULL]
	//*	output:
	//*			none.
	//*	note:
	//*
	public function sendError($prefix_in = null) {
		
		if(!empty($this->errorStr))
		{
			$prefix = ((is_string($prefix_in)) ? $prefix_in : '');
			
			echo("{$prefix}Error! ".($this->errorStr)." [".($this->errorNo)."]");
		}
	}
	
	//* method:	open the DB.
	//* input:
	//*			none.
	//* output:
	//*			connection resource.	[RESOURCE || NULL]
	//* note:
	//*
	public function openDB() {
		
		$result = null;
		$this->clearErrors();
		
		if(is_object($this->dbHelper))
		{
			$result = $this->dbHelper->connect();
			
			$this->errorNo	= $this->dbHelper->errno();
			$this->errorStr	= $this->dbHelper->error();
		}
		
		return $result;
	}
	
	//* method:	close the DB.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function closeDB() {
		
		if(is_object($this->dbHelper))
		{
			$this->dbHelper->disconnect();
		}
	}
	
	//* method:	get name of DB-table.
	//* input:
	//*			none.
	//* output:
	//*			the name of DB-table.	[STRING || NULL]
	//* note:
	//*
	public function getTableName() {
		
		if(!empty($this->dbTable))
		{
			if(is_string($this->dbTable)) return $this->dbTable;
		}
		
		return null;
	}
	
	//* method:	get name of DB-view.
	//* input:
	//*			none.
	//* output:
	//*			the name of DB-view.	[STRING || NULL]
	//* note:
	//*
	public function getViewName() {
		
		if(!empty($this->dbView))
		{
			if(is_string($this->dbView)) return $this->dbView;
		}
		
		return null;
	}
	
	//* method:	get name of DB-table/view by action ID.
	//* input:
	//*			action_in - the code of an action:
	//*							= 0 - "select",
	//*							= 1 - "insert" (by default),
	//*							= 2 - "update",
	//*							= 3 - "delete".
	//* output:
	//*			the name of DB-table/view.	[STRING || NULL]
	//* note:
	//*
	public function getTableNameByAction($action_in = 0) {
		
		$tableName = $this->getTableName();
		
		if(is_int($action_in))
		{
			if($action_in == self::ACTION_SELECT)
			{
				$viewName = $this->getViewName();
				if(!empty($viewName)) $tableName = $viewName;
			}
		}
		
		return $tableName;
	}
	
	//* method:	get the count of rows.
	//* input:
	//*			$where_in		- "WHERE"-string (without operator "WHERE")	[STRING || ARRAY || NULL]
	//*								or list of WHERE-fields
	//*								or NULL (for all rows);
	//*			$values_in		- list of values for WHERE-fields or $_REQUEST (if $where_in is list of WHERE-fields) or NULL;	[ARRAY || NULL]
	//*			$key_field_in	- name of key field or NULL. [STRING || NULL]
	//* output:
	//*			the count of rows.	[INTEGER]
	//* note:
	//*			if $where_in + $values_in + $key_field_in
	//*				SELECT COUNT(`{$key_field_in}`) FROM `table` WHERE {$where_in=$values_in ...}
	//*
	//*			if $where_in + $values_in
	//*				SELECT COUNT(*) FROM `table` WHERE {$where_in=$values_in ...}
	//*
	//*			if $key_field_in
	//*				SELECT COUNT(`{$key_field_in}`) FROM `table`
	//*
	//*			else
	//*				SELECT COUNT(*) FROM `table`
	//*
	public function count($where_in = null, $values_in = null, $key_field_in = null) {
		
		global $FL_DEBUG;
		
		$countRows = 0;
		$this->clearErrors();
		
		if(!function_exists("sql_select"))
		{
			if($FL_DEBUG) echo("Error! Function 'sql_select()' not exists! [mysql-table.php -> class MySQLDBTable]");
			return $countRows;
		}
		
		if(is_object($this->dbHelper))
		{
			$tableName = $this->getTableNameByAction(self::ACTION_SELECT);
			
			if(!empty($tableName) && $this->openDB())
			{
				$query     = null;
				$key_field = "*";
				
				if(!empty($key_field_in))
				{
					if(is_string($key_field_in)) $key_field = "`{$key_field_in}`";
				}
				
				if(!empty($where_in))
				{
					if(is_string($where_in) || is_array($where_in))
					{
						$query = sql_select("`{$tableName}`", array(array("alt_field" => "COUNT(".($key_field).")")), $where_in, $values_in);
					}
				}
				
				if(empty($query)) $query = "SELECT COUNT(".($key_field).") FROM `{$tableName}`";
				//echo("#error#{$query}");
				
				$resultset = $this->dbHelper->send_query($query);
				
				$this->errorNo	= $this->dbHelper->errno();
				$this->errorStr	= $this->dbHelper->error();
				
				if(is_resource($resultset))
				{
					$row = mysql_fetch_array($resultset);
					
					if($row)
					{
						if(count($row)) $countRows = (int)$row[0];
					}
					
					mysql_free_result($resultset);
				}
				
				$this->closeDB();
			}
		}
		
		return $countRows;
	}
	
	//* method:	check data.
	//* input:
	//*			$where_in	- "WHERE"-string (without operator "WHERE")	[STRING || ARRAY]
	//*							or list of WHERE-fields;
	//*			$values_in	- list of values for WHERE-fields or $_REQUEST (if $where_in is list of WHERE-fields) or NULL.	[ARRAY || NULL]
	//* output:
	//*			true if the item is exists, otherwise - false.	[BOOLEAN]
	//* note:
	//*
	public function check($where_in = null, $values_in = null) {
		
		if(!empty($where_in))
		{
			if(is_string($where_in) || is_array($where_in))
			{
				$countRows = $this->count($where_in, $values_in);
				
				return (($countRows > 0) ? true : false);
			}
		}
		
		return false;
	}
	
	//* method:	get data.
	//* input:
	//*			$fields_in	- a list of returned fields or NULL (all fields);	[ARRAY || NULL]
	//*			$where_in	- a "WHERE"-string (without operator "WHERE")	[STRING || ARRAY || NULL]
	//*							or list of WHERE-fields
	//*							or NULL;
	//*			$values_in	- list of values for WHERE-fields or $_REQUEST (if $where_in is list of WHERE-fields) or NULL;	[ARRAY || NULL]
	//*			groupBy_in	- a filter declaring how to group rows, formatted as an SQL GROUP BY clause (excluding the GROUP BY itself); passing null will cause the rows to not be grouped; [STRING || NULL]
	//*			having_in	- a filter declare which row groups to include in the cursor, if row grouping is being used, formatted as an SQL HAVING clause (excluding the HAVING itself); passing null will cause all row groups to be included, and is required when row grouping is not being used;	[STRING || NULL]
	//*			orderBy_in	- how to order the rows, formatted as an SQL ORDER BY clause (excluding the ORDER BY itself) or NULL;	[STRING || NULL]
	//*			limit_in	- limits the number of rows returned by the query, formatted as LIMIT clause.	[STRING || NULL]
	//* output:
	//*			a resource on success or false (if error).	[RESOURCE || BOOLEAN]
	//* note:
	//*			The database connection must be established (use method openDB())!
	//*
	//*			see sql.php for help.
	//*
	public function select($fields_in = null, $where_in = null, $values_in = null, $groupBy_in = null, $having_in = null, $orderBy_in = null, $limit_in = null) {
		
		global $FL_DEBUG;
		
		$this->clearErrors();
		
		if(!function_exists("sql_select"))
		{
			if($FL_DEBUG) echo("Error! Function 'sql_select()' not exists! [mysql-table.php -> class MySQLDBTable]");
			return false;
		}
		
		if(is_object($this->dbHelper))
		{
			$tableName = $this->getTableNameByAction(self::ACTION_SELECT);
			
			if(!empty($tableName))
			{
				$query = sql_select("`{$tableName}`", $fields_in, $where_in, $values_in);
				
				if(!empty($query))
				{
					if(!empty($groupBy_in))
					{
						if(is_string($groupBy_in)) $query.= " GROUP BY {$groupBy_in}";
					}
					
					if(!empty($having_in))
					{
						if(is_string($having_in)) $query.= " HAVING {$having_in}";
					}
					
					if(!empty($orderBy_in))
					{
						if(is_string($orderBy_in)) $query.= " ORDER BY {$orderBy_in}";
					}
					
					if(!empty($limit_in))
					{
						if(is_string($limit_in)) $query.= " LIMIT {$limit_in}";
					}
					
					//echo("#error#{$query}");
					
					$result = $this->dbHelper->send_query($query);
					
					$this->errorNo	= $this->dbHelper->errno();
					$this->errorStr	= $this->dbHelper->error();
					
					return $result;
				}
			}
		}
		
		return false;
	}
	
	//* method:	insert a row of data.
	//* input:
	//*			$fields_in	- a list of inserted fields;	[ARRAY]
	//*			$values_in	- a list of field values or $_REQUEST.	[ARRAY]
	//* output:
	//*			true on success or false.	[BOOLEAN]
	//* note:
	//*			The database connection must be established (use method openDB())!
	//*
	//*			see sql.php for help.
	//*
	public function insert($fields_in = null, $values_in = null) {
		
		global $FL_DEBUG;
		
		$this->clearErrors();
		
		if(!function_exists("sql_insert"))
		{
			if($FL_DEBUG) echo("Error! Function 'sql_insert()' not exists! [mysql-table.php -> class MySQLDBTable]");
			return false;
		}
		
		//** locking the DB by TimeStamp
		if($this->dbLockByTimeStamp > 0)
		{
			$_time = time();
			if($_time > $this->dbLockByTimeStamp) return false;
		}
		
		if(is_object($this->dbHelper))
		{
			$tableName = $this->getTableNameByAction(self::ACTION_INSERT);
			
			if(!empty($tableName))
			{
				$query = sql_insert($tableName, $fields_in, $values_in);
				
				//echo("#error#{$query}");
				//$result	= false;
				
				$result = $this->dbHelper->send_query($query);
				
				$this->errorNo	= $this->dbHelper->errno();
				$this->errorStr	= $this->dbHelper->error();
				
				return $result;
			}
		}
		
		return false;
	}
	
	//* method:	update data.
	//* input:
	//*			$fields_in	- a list of updated fields;	[ARRAY]
	//*			$values_in	- a list of field values or $_REQUEST;	[ARRAY]
	//*			$where_in	- a "WHERE"-string (without operator "WHERE")	[STRING || ARRAY || NULL]
	//*							or list of WHERE-fields
	//*							or NULL.
	//* output:
	//*			true on success or false.	[BOOLEAN]
	//* note:
	//*			The database connection must be established (use method openDB())!
	//*
	//*			see sql.php for help.
	//*
	//*			$values_in used and as list of values for WHERE-fields (if $where_in is list of WHERE-fields)!
	//*
	public function update($fields_in = null, $values_in = null, $where_in = null) {
		
		global $FL_DEBUG;
		
		$this->clearErrors();
		
		if(!function_exists("sql_update"))
		{
			if($FL_DEBUG) echo("Error! Function 'sql_update()' not exists! [mysql-table.php -> class MySQLDBTable]");
			return false;
		}
		
		//** locking the DB by TimeStamp
		if($this->dbLockByTimeStamp > 0)
		{
			$_time = time();
			if($_time > $this->dbLockByTimeStamp) return false;
		}
		
		if(is_object($this->dbHelper))
		{
			$tableName = $this->getTableNameByAction(self::ACTION_UPDATE);
			
			if(!empty($tableName))
			{
				$query = sql_update($tableName, $fields_in, $where_in, $values_in);
				
				//echo("#error#{$query}");
				//$result	= false;
				
				$result	= $this->dbHelper->send_query($query);
				
				$this->errorNo	= $this->dbHelper->errno();
				$this->errorStr	= $this->dbHelper->error();
				
				return $result;
			}
		}
		
		return false;
	}
	
	//* method:	delete data.
	//* input:
	//*			$where_in	- a "WHERE"-string (without operator "WHERE")	[STRING || ARRAY || NULL]
	//*							or list of WHERE-fields
	//*							or NULL;
	//*			$values_in	- list of values for WHERE-fields or $_REQUEST (if $where_in is list of WHERE-fields) or NULL;	[ARRAY || NULL]
	//*			$using_in	- array of using tables (for operator 'USING') or NULL.	[ARRAY || NULL]
	//* output:
	//*			true on success or false.	[BOOLEAN]
	//* note:
	//*			The database connection must be established (use method openDB())!
	//*
	//*			see sql.php for help.
	//*
	public function delete($where_in = null, $values_in = null, $using_in = null) {
		
		global $FL_DEBUG;
		
		$this->clearErrors();
		
		if(!function_exists("sql_delete"))
		{
			if($FL_DEBUG) echo("Error! Function 'sql_delete()' not exists! [mysql-table.php -> class MySQLDBTable]");
			return false;
		}
		
		//** locking the DB by TimeStamp
		if($this->dbLockByTimeStamp > 0)
		{
			$_time = time();
			if($_time > $this->dbLockByTimeStamp) return false;
		}
		
		if(is_object($this->dbHelper))
		{
			$tableName = $this->getTableNameByAction(self::ACTION_DELETE);
			
			if(!empty($tableName))
			{
				$query	= sql_delete($tableName, $where_in, $values_in, $using_in);
				
				//echo("#error#{$query}");
				
				$result	= $this->dbHelper->send_query($query);
				
				$this->errorNo	= $this->dbHelper->errno();
				$this->errorStr	= $this->dbHelper->error();
				
				return $result;
			}
		}
		
		return false;
	}
	
	//* method:	raw SQL.
	//* input:
	//*			$SQLin - SQL-string.	[STRING]
	//* output:
	//*			resultset.	[RESOURCE || NULL]
	//* note:
	//*
	public function rawSQL($QueryIn = null) {
		
		global $FL_DEBUG;
		
		$this->clearErrors();
		
		$result = null;
		
		if(is_string($QueryIn))
		{
			if(!empty($QueryIn))
			{
				if($this->openDB())
				{
					$result	= $this->dbHelper->send_query($QueryIn);
					$this->closeDB();
				}
				
				$this->errorNo	= $this->dbHelper->errno();
				$this->errorStr	= $this->dbHelper->error();
			}
		}
		
		return ($result);
	}
	
	//* method:	free resultset.
	//* input:
	//*			$ResultIn - resultset.	[RESOURCE]
	//* output:
	//*			none.
	//* note:
	//*
	public function freeResult($ResultIn = null) {
		
		if(is_resource($ResultIn)) mysql_free_result($ResultIn);
	}
	
	
	//Constructor and Destructor
	
	//*	input:
	//*			dbHelper_in	- a DBHelper;	[dbMySQL]
	//*			dbTable_in	- a table name;	[STRING]
	//*			dbView_in   - a view name.	[STRING]
	//*	note:
	//*
	function __construct($dbHelper_in = null, $dbTable_in = null, $dbView_in = null)
	{
		global $FL_DEBUG;
		
		$this->dbHelper				= null;
		$this->dbTable				= ((is_string($dbTable_in)) ? $dbTable_in : null);
		$this->dbView				= ((is_string($dbView_in)) ? $dbView_in : null);
		$this->dbLockByTimeStamp	= -1;
		$this->errorNo				= 0;
		$this->errorStr				= '';
		
		if(class_exists("dbMySQL"))
		{
			if(is_object($dbHelper_in))
			{
				if(is_a($dbHelper_in, "dbMySQL"))
				{
					$this->dbHelper				= $dbHelper_in;
					$this->dbLockByTimeStamp	= $this->dbHelper->getLockByTimeStamp();
				}
			}
		}
		else
		{
			if($FL_DEBUG) echo("Error! Class 'dbMySQL' not exists! [mysql-table.php -> class MySQLDBTable]");
		}
	}
	
	function __destruct()
	{
		$this->closeDB();
		
		unset($this->dbHelper);
		unset($this->dbTable);
		unset($this->dbView);
		unset($this->dbLockByTimeStamp);
		unset($this->errorNo);
		unset($this->errorStr);
	}
}


?>
