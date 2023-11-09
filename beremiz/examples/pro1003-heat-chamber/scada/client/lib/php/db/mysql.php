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


/*   Library: MySQL.
*
*    Copyright (C) 2010-2014  ATgroup09 (atgroup09@gmail.com)
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
*		- libraries: none.
*/


/*	Global variables: none.
*
*
*	Functions:
*
*		*** check parameters of a connection ***
*		dbMySQL_check_connect_params($connect_params_in = null)
*
*		*** get the new array with default parameters of a connection ***
*		dbMySQL_new_connect_params($hostname_in = "localhost", $user_in = "user")
*
*		*** connecting to a database ***
*		dbMySQL_connect($connect_params_in = null)
*
*		*** send a query ***
*		dbMySQL_send_query($connect_in = null, $query_in = null, $characters_coding_in = "utf8")
*
*		*** test a connection ***
*		dbMySQL_ping($connect_in = null, $table_name_in = null)
*
*	Classes:
*
*		class dbMySQL.
*
*
*	The structure of parameter of a connection:
*
*		- ["db_type"]			- a type name ("mysql" by default);			[STRING]
*		- ["hostname"]			- a host name ("localhost" by default);		[STRING]
*		- ["port"]				- a port number (3306 by default);			[INTEGER]
*		- ["database"]			- a database name (null by default);		[STRING || NULL]
*		- ["table"]				- a table name (null by default);			[STRING || NULL]
*		- ["user"]				- a user name;								[STRING]
*		- ["password"]			- a user password (null by default);		[STRING || NULL]
*		- ["characters_coding"]	- characters coding ("utf8" by default).	[STRING || NULL]
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function: check parameters of a connection.
*
*	Input:	
*			$connect_params_in	- parameters of the connection.	[ARRAY]
*
*	Output:
*			result:	[BOOLEAN]
*				- true	- parameters are suitable,
*				- flase	- parameters not are suitable.
*
*	Note:
*			next parameters is required: hostname, user!
*/
function dbMySQL_check_connect_params($connect_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the input argument $connect_params_in
	if(!is_array($connect_params_in))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the input argument 'connect_params_in'! [mysql.php -> dbMySQL_check_connect_params()]");
		}
		return false;
	}
	
	//Check required parameters
	if(!isset($connect_params_in["hostname"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the connection parameter 'hostname'! [mysql.php -> dbMySQL_check_connect_params()]");
		}
		return false;
	}
	
	if(!is_string($connect_params_in["hostname"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the connection parameter 'hostname' (not a string)! [mysql.php -> dbMySQL_check_connect_params()]");
		}
		return false;
	}
	
	if(!isset($connect_params_in["user"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the connection parameter 'user'! [mysql.php -> dbMySQL_check_connect_params()]");
		}
		return false;
	}
	
	if(!is_string($connect_params_in["user"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the connection parameter 'user' (not a string)! [mysql.php -> dbMySQL_check_connect_params()]");
		}
		return false;
	}
	
	return true;
}


/*	Function: get the new array with default parameters of a connection.
*
*	Input:	
*			$hostname_in	- a host name ("localhost" by default),	[STRING || NULL]
*			$user_in		- a user name ("user" by default).	[STRING || NULL]
*
*	Output:
*			the new array with default parameters of a connection.	[ARRAY]
*
*	Note:
*
*/
function dbMySQL_new_connect_params($hostname_in = "localhost", $user_in = "user")
{
	//* the returned result	[ARRAY]
	$returned_result = array("db_type" => "mysql",
							 "hostname" => "localhost",
							 "port" => 3306,
							 "database" => null,
							 "table" => null,
							 "user" => "user",
							 "password" => null,
							 "characters_coding" => "utf8");
	
	
	//Check input arguments
	if(!empty($hostname_in))
	{
		if(is_string($hostname_in))
		{
			$returned_result["hostname"] = $hostname_in;
		}
	}
	
	if(!empty($user_in))
	{
		if(is_string($user_in))
		{
			$returned_result["user"] = $user_in;
		}
	}
	
	return $returned_result;
}


/*	Function: connecting to a database.
*
*	Input:	
*			$connect_params_in	- parameters of the connection;	[ARRAY]
*
*	Output:
*			a connection resource or NULL.	[RESOURCE || NULL]
*
*	Note:
*
*/
function dbMySQL_connect($connect_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function mysql_connect()
	if(!function_exists("mysql_connect"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'mysql_connect()' not exists! [mysql.php -> dbMySQL_connect()]");
		}
		return null;
	}
	
	//Check the function mysql_select_db)
	if(!function_exists("mysql_select_db"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'mysql_select_db()' not exists! [mysql.php -> dbMySQL_connect()]");
		}
		return null;
	}
	
	//Check the function mysql_error()
	if(!function_exists("mysql_error"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'mysql_error()' not exists! [mysql.php -> dbMySQL_connect()]");
		}
		return null;
	}
	
	//Check the function dbMySQL_check_connect_params()
	if(!function_exists("dbMySQL_check_connect_params"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'dbMySQL_check_connect_params()' not exists! [mysql.php -> dbMySQL_connect()]");
		}
		return null;
	}
	
	//Check the input argument $connect_params_in
	if(!dbMySQL_check_connect_params($connect_params_in))
	{
		return null;
	}
	
	//* a port	[INTEGER]
	$port = 3306;
	
	//* a user password	[STRING]
	$password = '';
	
	//* a connection resource	[RESOURCE || NULL]
	$connect = null;
	
	
	//Check the connection parameter "port"
	if(isset($connect_params_in["port"]))
	{
		if(is_int($connect_params_in["port"]))
		{
			if($connect_params_in["port"] > 0)
			{
				$port = $connect_params_in["port"];
			}
		}
	}
	
	//Check the connection parameter "password"
	if(isset($connect_params_in["password"]))
	{
		if(is_string($connect_params_in["password"]))
		{
			if(!empty($connect_params_in["password"]))
			{
				$password = $connect_params_in["password"];
			}
		}
	}
	
	//Open the connection
	$connect = mysql_connect(($connect_params_in["hostname"]).(':').($port), $connect_params_in["user"], $password);
	
	//Check the connection
	if(!$connect)
	{
		return null;
	}
	
	//Check the connection parameter "database"
	if(isset($connect_params_in["database"]))
	{
		if(is_string($connect_params_in["database"]))
		{
			if(!empty($connect_params_in["database"]))
			{
				mysql_select_db($connect_params_in["database"], $connect);
			}
		}
	}
	
	return $connect;
}


/*	Function: send a query.
*
*	Input:	
*			$connect_in 			- a connection resource.	[RESOURCE]
*			$query_in				- a query,	[STRING]
*			$characters_coding_in	- characters coding ("utf8" by default).	[STRING || NULL]
*
*	Output:
*			for queries SELECT, SHOW, DESCRIBE, EXPLAIN and other statements returning resultset:	[RESOURCE || BOOLEAN]
*				- a resource on success,
*				- false on error;
*
*			for other type of SQL statements, INSERT, UPDATE, DELETE, DROP, etc:	[BOOLEAN]
*				- true on success,
*				- false on error. 
*
*	Note:
*			The returned result resource should be passed to mysql_fetch_array(), and other functions
*				for dealing with result tables, to access the returned data.
*
*			Use mysql_num_rows() to find out how many rows were returned for a SELECT statement or
*				mysql_affected_rows() to find out how many rows were affected by a DELETE, INSERT, REPLACE,
*				or UPDATE statement.
*/
function dbMySQL_send_query($connect_in = null, $query_in = null, $characters_coding_in = "utf8")
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function mysql_query()
	if(!function_exists("mysql_query"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'mysql_query()' not exists! [mysql.php -> dbMySQL_send_query()]");
		}
		return false;
	}
	
	//Check the input argument $connect_in
	if(!is_resource($connect_in))
	{
		return false;
	}
	
	//Check the input argument $query_in
	if(empty($query_in))
	{
		return false;
	}
	
	if(!is_string($query_in))
	{
		return false;
	}
	
	//* characters coding	[STRING]
	$characters_coding = "utf8";
	
	
	//Check the input argument $characters_coding_in
	if(!empty($characters_coding_in))
	{
		if(is_string($characters_coding_in))
		{
			$characters_coding = $characters_coding_in;
		}
	}
	
	//Send the request for set a coding of characters
	mysql_query("SET character_set_client=\"{$characters_coding}\"", $connect_in);
	mysql_query("SET character_set_results=\"{$characters_coding}\"", $connect_in);
	mysql_query("SET collation_connection=\"{$characters_coding}_general_ci\"", $connect_in);
	mysql_query("SET NAMES {$characters_coding}", $connect_in);
	
	//Send the query
	return mysql_query($query_in, $connect_in);
}


/*	Function: test a connection.
*
*	Input:	
*			$connect_in    - a connection resource;	[RESOURCE]
*			$table_name_in - a table name or NULL.	[STRING || NULL]
*
*	Output:
*			result:	[BOOLEAN]
*					- true	- connected successfully,
*					- false	- error.
*
*	Note:
*
*/
function dbMySQL_ping($connect_in = null, $table_name_in = null)
{
	//* returned result	[BOOLEAN]
	$returned_result = false;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function dbMySQL_send_query()
	if(!function_exists("dbMySQL_send_query"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'dbMySQL_send_query()' not exists! [mysql.php -> dbMySQL_ping()]");
		}
		return $returned_result;
	}
	
	//* a resultset	[RESOURCE || BOOLEAN || NULL]
	$resultset = null;
	
	//* query	[STRING]
	$query = "SELECT 1";
	
	
	//Check the input argument $table_name_in
	if(!empty($table_name_in))
	{
		if(is_string($table_name_in))
		{
			$query = "SELECT COUNT(*) FROM {$table_name_in}";
		}
	}
	
	//Send the request for check the connection
	$resultset = dbMySQL_send_query($connect_in, $query, "utf8");
	
	//Check resultset
	if($resultset)
	{
		if(is_resource($resultset))
		{
			//read data from the resultset
			if(($row = mysql_fetch_assoc($resultset)))
			{
				if(count($row))
				{
					$returned_result = true;
				}
			}
			
			//freeing a memory
			mysql_free_result($resultset);
		}
	}
	
	return $returned_result;
}


//** CLASSES

/*	Class: db mysql.
*
*	Input: none.
*/
class dbMySQL
{
	//** Options
	
	//** public
	
	//* parameters of the connection	[ARRAY]
	public $params;
	
	//** private
	
	//* a connection resource	[RESOURCE || NULL]
	private $connect;
	
	//* locking the table/view since the specified time (by UNIX_TIMESTAMP)	[INTEGER]
	//** if the current time >= the specified time, then the table/view will be locked
	//** if the value <= 0, then the table/view is always available (by default)
	//
	//** use time()
	private $dbLockByTimeStamp;
	
	
	//** Methods
	
	//* method:	normalization of values.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function normalize() {
		
		if(!is_array($this->params))
		{
			$this->params = array("hostname"			=> "localhost",
								  "port"				=> 3306,
								  "database"			=> null,
								  "table"				=> null,
								  "user"				=> "user",
								  "password"			=> null,
								  "characters_coding"	=> "utf8");
		}
		
		if(empty($this->params["hostname"]))		$this->params["hostname"] = "localhost";
		if(!is_string($this->params["hostname"]))	$this->params["hostname"] = "localhost";
		
		if(empty($this->params["port"]))			$this->params["port"] = 3306;
		if(!is_int($this->params["port"]))			$this->params["port"] = 3306;
		if($this->params["port"] < 1)				$this->params["port"] = 1;
		if($this->params["port"] > 65535)			$this->params["port"] = 65535;
		
		if(!isset($this->params["database"]))		$this->params["database"] = null;
		if(!isset($this->params["table"]))			$this->params["table"] = null;
		if(!isset($this->params["user"]))			$this->params["user"] = null;
		if(!isset($this->params["password"]))		$this->params["password"] = null;
		
		if(empty($this->params["characters_coding"]))		$this->params["characters_coding"] = "utf8";
		if(!is_string($this->params["characters_coding"]))	$this->params["characters_coding"] = "utf8";
	}
	
	//* method:	get locking time stamp.
	//* input:
	//*			none.
	//* output:
	//*			value of option $dbLockByTimeStamp.
	//* note:
	//*
	public function getLockByTimeStamp() {
		
		return $this->dbLockByTimeStamp;
	}
	
	//*	method: check connection parameters.
	//*	input:
	//*			$params_in - connection parameters.	[ARRAY]
	//*	output:
	//*			result:	[BOOLEAN]
	//*				- true	- parameters are suitable,
	//*				- flase	- parameters not are suitable.
	//*	note:
	//*
	public static function _check_params($params_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("dbMySQL_check_connect_params"))
		{
			if($FL_DEBUG) echo("Error! Function 'dbMySQL_check_connect_params()' not exists! [mysql.php -> class dbMySQL]");
			return false;
		}
		
		return dbMySQL_check_connect_params($params_in);
	}
	
	
	//*	method: check connection parameters.
	//*	input:
	//*			none.
	//*	output:
	//*			result:	[BOOLEAN]
	//*				- true	- parameters are suitable,
	//*				- flase	- parameters not are suitable.
	//*	note:
	//*
	public function check_params() {
		
		return self::_checkParams($this->params);
	}
	
	//*	method: get an error number from the last MySQL function.
	//*	input:
	//*			$connect_in - a connection resource.	[RESOURCE]
	//*	output:
	//*			the error number from the last MySQL function, or 0 (zero) if no error occurred.	[INTEGER]
	//*	note:
	//*
	public static function _errno($connect_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("mysql_errno"))
		{
			if($FL_DEBUG) echo("Error! Function 'mysql_errno()' not exists! [mysql.php -> class dbMySQL]");
			return 0;
		}
		
		return ((is_resource($connect_in)) ? mysql_errno($connect_in) : 0);
	}
	
	//*	method: get an error number from the last MySQL function.
	//*	input:
	//*			none.
	//*	output:
	//*			the error number from the last MySQL function, or 0 (zero) if no error occurred.	[INTEGER]
	//*	note:
	//*
	public function errno() {
		
		return self::_errno($this->connect);
	}
	
	//*	method: get an error text from the last MySQL function.
	//*	input:
	//*			$connect_in - a connection resource.	[RESOURCE]
	//*	output:
	//*			the error text from the last MySQL function, or '' (empty string) if no error occurred.	[STRING]
	//*	note:
	//*
	public static function _error($connect_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("mysql_error"))
		{
			if($FL_DEBUG) echo("Error! Function 'mysql_error()' not exists! [mysql.php -> class dbMySQL]");
			return '';
		}
		
		return ((is_resource($connect_in)) ? mysql_error($connect_in) : '');
	}
	
	//*	method: get an error text from the last MySQL function.
	//*	input:
	//*			none.
	//*	output:
	//*			the error text from the last MySQL function, or '' (empty string) if no error occurred.	[STRING]
	//*	note:
	//*
	public function error() {
		
		return self::_error($this->connect);
	}
	
	//*	method: close the connection.
	//*	input:
	//*			$connect_in - a connection resource.	[RESOURCE]
	//*	output:
	//*			none.
	//*	note:
	//*
	public static function _disconnect($connect_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("mysql_close"))
		{
			if($FL_DEBUG) echo("Error! Function 'mysql_close()' not exists! [mysql.php -> class dbMySQL]");
			return;
		}
		
		if(is_resource($connect_in)) mysql_close($connect_in);
	}
	
	//*	method: close the connection.
	//*	input:
	//*			none.
	//*	output:
	//*			none.
	//*	note:
	//*
	public function disconnect() {
		
		self::_disconnect($this->connect);
		
		$this->connect = null;
	}
	
	//*	method: connect to DB.
	//*	input:
	//*			$params_in	- connection parameters.	[ARRAY]
	//*	output:
	//*			connection resource.	[RESOURCE || NULL]
	//*	note:
	//*
	public static function _connect($params_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("dbMySQL_connect"))
		{
			if($FL_DEBUG) echo("Error! Function 'dbMySQL_connect()' not exists! [mysql.php -> class dbMySQL]");
			return false;
		}
		
		return ((is_array($params_in)) ? dbMySQL_connect($params_in) : null);
	}
	
	//*	method: connect to DB.
	//*	input:
	//*			none.
	//*	output:
	//*			connection resource.	[RESOURCE || NULL]
	//*	note:
	//*
	public function connect() {
		
		$this->disconnect();
		$this->normalize();
		
		$this->connect = self::_connect($this->params);
		
		return $this->connect;
	}
	
	//*	method: send query.
	//*	input:
	//*			$connect_in				- a connection resource;	[RESOURCE]
	//*			$query_in				- a query;	[STRING]
	//*			$characters_coding_in	- a characters coding ("utf8" by default) or NULL.	[STRING || NULL]
	//*	output:
	//*			for queries SELECT, SHOW, DESCRIBE, EXPLAIN and other statements returning resultset:	[RESOURCE || BOOLEAN]
	//*				- a resource on success,
	//*				- false on error;
	//*
	//*			for other type of SQL statements, INSERT, UPDATE, DELETE, DROP, etc:	[BOOLEAN]
	//*				- true on success,
	//*				- false on error. 
	//*	note:
	//*			The returned result resource should be passed to mysql_fetch_array(), and other functions
	//*				for dealing with result tables, to access the returned data.
	//*
	//*			Use mysql_num_rows() to find out how many rows were returned for a SELECT statement or
	//*				mysql_affected_rows() to find out how many rows were affected by a DELETE, INSERT, REPLACE,
	//*				or UPDATE statement.
	//*
	public static function _send_query($connect_in = null, $query_in = null, $characters_coding_in = "utf8") {
		
		global $FL_DEBUG;
		
		if(!function_exists("dbMySQL_send_query"))
		{
			if($FL_DEBUG) echo("Error! Function 'dbMySQL_send_query()' not exists! [mysql.php -> class dbMySQL]");
			return false;
		}
		
		if(is_resource($connect_in) && !empty($query_in))
		{
			if(is_string($query_in))
			{
				$characters_coding = "utf8";
				
				if(!empty($characters_coding_in))
				{
					if(is_string($characters_coding_in))
					{
						$characters_coding = $characters_coding_in;
					}
				}
				
				return dbMySQL_send_query($connect_in, $query_in, $characters_coding);
			}
		}
		
		return false;
	}
	
	//*	method: send query.
	//*	input:
	//*			$query_in - a query.	[STRING]
	//*	output:
	//*			for queries SELECT, SHOW, DESCRIBE, EXPLAIN and other statements returning resultset:	[RESOURCE || BOOLEAN]
	//*				- a resource on success,
	//*				- false on error;
	//*
	//*			for other type of SQL statements, INSERT, UPDATE, DELETE, DROP, etc:	[BOOLEAN]
	//*				- true on success,
	//*				- false on error. 
	//*	note:
	//*			The database connection must be established (use method connect())!
	//*
	//*			The returned result resource should be passed to mysql_fetch_array(), and other functions
	//*				for dealing with result tables, to access the returned data.
	//*
	//*			Use mysql_num_rows() to find out how many rows were returned for a SELECT statement or
	//*				mysql_affected_rows() to find out how many rows were affected by a DELETE, INSERT, REPLACE,
	//*				or UPDATE statement.
	//*
	public function send_query($query_in = null) {
		
		$this->normalize();
		
		return self::_send_query($this->connect, $query_in, $this->params["characters_coding"]);
	}
	
	//*	method: test the connection.
	//*	input:
	//*			$connect_in	- a connection resource;	[RESOURCE]
	//*			$table_in	- a table name.	[STRING || NULL]
	//*	output:
	//*			result:	[BOOLEAN]
	//*				- true	- connected successfully,
	//*				- false	- error.
	//*	note:	
	//*
	public static function _ping($connect_in = null, $table_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("dbMySQL_ping"))
		{
			if($FL_DEBUG) echo("Error! Function 'dbMySQL_ping()' not exists! [mysql.php -> class dbMySQL]");
			return false;
		}
		
		return ((is_resource($connect_in)) ? dbMySQL_ping($connect_in, $table_in) : false);
	}
	
	//*	method: the connection test.
	//*	input:
	//*			none.
	//*	output:
	//*			result:	[BOOLEAN]
	//*				- true	- connected successfully,
	//*				- false	- error.
	//*	note:
	//*			The database connection must be established (use method connect())!
	//*
	public function ping()
	{
		$this->normalize();
		
		return self::_ping($this->connect, $this->params["table"]);
	}
	
	
	//** Constructor and Destructor
	
	//*	input:
	//*			none.
	//*	note:
	//*
	function __construct()
	{
		//init options by default
		$this->params = array("hostname"			=> "localhost",
							  "port"				=> 3306,
							  "database"			=> null,
							  "table"				=> null,
							  "user"				=> "user",
							  "password"			=> null,
							  "characters_coding"	=> "utf8");
		
		$this->connect			 	= null;
		$this->dbLockByTimeStamp	= -1;
	}
	
	function __destruct()
	{
		$this->disconnect();
	}
}


?>
