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


/*   Module: module extends.
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
*			+ PHP:
*				~ mysql_free_result().
*
*			+ types/types.php:
*				~ types_checking_existence().
*
*			+ mysql.php:
*				~ class dbMySQL.
*
*			+ mysql-table.php:
*				~ abstract class MySQLDBTable.
*
*			+ mysql.php:
*				~ class dbMySQL.
*
*			+ res/values.php:
*				~ class ResValues.
*/

/*	Global variables: none
*
*	Functions: none.
*
*	Classes:
*
*		+ abstract class ModExt:
*
*			input arguments: none.
*/


//** GLOBAL VARIABLES



//** FUNCTIONS



//** CLASSES

class ModExt {
	
	//Options
	
	//* response types
	const RESPONSE_TYPE__ERROR	= 0;
	const RESPONSE_TYPE__OK		= 1;
	
	//* ID of request	[STRING]
	public $requestID;
	
	//* resources	[OBJECT || NULL]
	//** object of class "ResValues"
	public $R;
	
	//* DBHelper (object of class "dbMySQL")	[OBJECT || NULL]
	public $dbHelper;
	
	//* result of check of required functions/classes	[BOOLEAN]
	protected $checkExistenceResult;
	
	
	//Methods
	
	//*	method: check the option $R.
	//*	input:
	//*			none.
	//*	output:
	//*			true if the option $R is object of class "ResValues", otherwise - false.	[BOOLEAN]
	//*	note:
	//*
	public function checkR() {
		
		if(class_exists("ResValues"))
		{
			if(is_object($this->R))
			{
				if(is_a($this->R, "ResValues")) return true;
			}
		}
		
		return false;
	}
	
	//*	method: check the option $dbHelper.
	//*	input:
	//*			none.
	//*	output:
	//*			true if the option $R is object of class "dbMySQL", otherwise - false.	[BOOLEAN]
	//*	note:
	//*
	public function checkDBHelper() {
		
		if(class_exists("dbMySQL"))
		{
			if(is_object($this->dbHelper))
			{
				if(is_a($this->dbHelper, "dbMySQL")) return true;
			}
		}
		
		return false;
	}
	
	//* method:	send response.
	//* input:
	//*			$type_in		- type of the response:	[INTEGER]
	//*								= RESPONSE_TYPE__ERROR (by default),
	//*								= RESPONSE_TYPE__OK;
	//*			$response_in	- content of the response.	[STRING]
	//* output:
	//*			none.
	//* note:
	//*
	public function sendResponse($type_in = 0, $response_in = null) {
		
		if(!empty($response_in))
		{
			if(is_string($response_in))
			{
				$response_type = ((is_int($type_in)) ? $type_in : self::RESPONSE_TYPE__ERROR);
				
				if($response_type == self::RESPONSE_TYPE__OK)
				{
					$rqID = ((is_string($this->requestID)) ? $this->requestID : "");
					echo("#idq={$rqID}#{$response_in}");
				}
				else
				{
					echo("#error#{$response_in}");
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
			if($FL_DEBUG) $this->sendResponse(self::RESPONSE_TYPE__ERROR, "Error! Function 'types_checking_existence()' is not exists! [mod-ext.php -> class ModExt]");
			return false;
		}
		
		return types_checking_existence($required_in, "[mod-ext.php -> class ModExt]");
	}
	
	
	//Constructor and Destructor
	
	//*	input:
	//*			none.
	//*	note:
	//*
	function __construct() {
		
		$this->requestID			= null;
		$this->R					= null;
		$this->dbHelper				= null;
		$this->checkExistenceResult	= false;
	}
	
	function __destruct() {
		
		if(is_object($this->dbHelper)) $this->dbHelper->disconnect();
		
		unset($this->requestID);
		unset($this->R);
		unset($this->dbHelper);
		unset($this->checkExistenceResult);
	}
}


?>
