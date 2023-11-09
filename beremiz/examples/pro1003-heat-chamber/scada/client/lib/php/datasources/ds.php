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


/*   Library: data source.
*
*    Copyright (C) 2012-2013  ATgroup09 (atgroup09@gmail.com)
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
*				~ types_normalize_array_value().
*
*			+ types/functions.php:
*				~ functions_check_required().
*
*			+ dom/dom.php:
*				~ check_attribute_of_element(),
*				~ get_attribute_of_element(),
*				~ phpDOM_parsing(),
*				~ phpDOM_attach_node(),
*				~ phpDOM_remove_node(),
*				~ phpDOM_forming_node(),
*				~ phpDOM_get_values_of_nodes_by_params(),
*				~ phpDOM_get_root_node_from_string(),
*				~ phpDOM_get_root_node_from_file(),
*				~ phpDOM_write_document_to_file().
*
*			+ request/request.php:
*				~ get_request_value_on_key().
*
*			+ sql/sql.php:
*				~ sql_get_field_name(),
*				~ sql_where(),
*				~ sql_select(),
*				~ sql_insert(),
*				~ sql_update(),
*				~ sql_delete().
*
*			+ db/mysql.php:
*				~ class dbMySQL,
*				~ dbMySQL_check_connect_params().
*/


/*	Global variables: none.
*
*
*	Functions:
*
*		*** checking required parameters ***
*		ds_check_params($desc_params_in = null, $ds_params_in = null)
*
*		*** checking parameters by key arguments ***
*		ds_check_params_by_key_args($desc_params_in = null, $ds_params_in = null)
*
*		*** normalization of datasource parameters ***
*		ds_normalize_params($desc_params_in = null, &$ds_params_in = null)
*
*		*** synchronization of values from "desc_params" with values from "ds_params" ***
*		ds_sync_desc_params(&$desc_params_in = null, $ds_params_in = null)
*
*		*** get array of new datasource parameters ***
*		ds_new_params($desc_params_in = null)
*
*		*** get list of values of key arguments from $_REQUEST ***
*		ds_get_key_args_from_request($desc_params_in = null)
*
*		*** get datasource parameters from $_REQUEST ***
*		ds_get_from_request($desc_params_in = null)
*
*		*** get datasource parameters (normalized) from datasource-node ***
*		ds_get_raw_params_from_ds_node($ds_node_in = null, $desc_params_in = null)
*
*		*** get list of values of key arguments from datasource-node ***
*		ds_get_key_args_from_ds_node($ds_node_in = null, $desc_params_in = null)
*
*		*** search datasource nodes in root-node ***
*		ds_search_nodes($root_node_in = null, $ds_node_name_in = null)
*
*		*** search datasource nodes in root-node by key arguments ***
*		ds_search_nodes_by_key_args($root_node_in = null, $ds_node_name_in = null, $desc_params_in = null)
*
*		*** get values of key arguments of datasource from root-node ***
*		ds_get_key_args_from_node($root_node_in = null, $ds_node_name_in = null, $desc_params_in = null)
*
*		*** get datasource parameters from a root-node ***
*		ds_get_from_node($root_node_in = null, $ds_node_name_in = null, $desc_params_in = null)
*
*		*** add (or update) datasource into root-node ***
*		ds_add_into_node(&$root_node_in = null, $ds_node_name_in = null, $desc_params_in = null, &$ds_params_in = null)
*
*		*** remove datasource from root-node ***
*		ds_remove_from_node(&$root_node_in, $ds_node_name_in = null, $desc_params_in = null)
*
*		*** get values of key arguments of datasource from XML-file ***
*		ds_get_key_args_from_file($file_in = null, $ds_node_name_in = null, $desc_params_in = null)
*
*		*** get datasource parameters from XML-file ***
*		ds_get_from_file($file_in = null, $ds_node_name_in = null, $desc_params_in = null)
*
*		*** add (or update) datasource into XML-file ***
*		ds_add_into_file($file_in = null, $root_node_name_in = null, $ds_node_name_in = null, $desc_params_in = null, &$ds_params_in = null)
*
*		*** remove datasource from XML-file ***
*		ds_remove_from_file($file_in = null, $ds_node_name_in = null, $desc_params_in = null)
*
*		*** get object of database class ***
*		ds_get_db_object($connect_params_in = null)
*
*		*** get values of key arguments of datasource from database ***
*		ds_get_key_args_from_db($connect_params_in = null, $desc_params_in = null)
*
*		*** get array of parameters (list of fields names and list of values) for the operator "WHERE" ***
*		ds_get_params_for_where_db($desc_params_in = null)
*
*		*** get datasource parameters from a database ***
*		ds_get_from_db($connect_params_in = null, $desc_params_in = null)
*
*		*** add (or update) datasource into a database ***
*		ds_add_into_db($connect_params_in = null, $desc_params_in = null, &$ds_params_in = null)
*
*		*** remove datasource from a database ***
*		ds_remove_from_db($connect_params_in = null, $desc_params_in = null)
*
*		*** get file name of repository from the datasource parameters by ID of the target repository ***
*		ds_get_repository_file_name_by_target_id($datasource_params_in = null, $target_id_in = null)
*
*		*** get table name of repository from the datasource parameters by ID of the target repository ***
*		ds_get_repository_table_name_by_target_id($datasource_params_in = null, $target_id_in = null)
*
*		*** check datasource parameters ***
*		ds_check_datasource_params($datasource_params_in = null, $target_id_in = null)
*
*		*** extending of datasource parameters ***
*		ds_extend_params($ext_in = null, $desc_ext_params_in = null, &$ds_params_in = null)
*
*
*	Classes:
*
*		- abstract class ds.
*
*
*	The recommended array of datasource parameters:
*
*		* default:
*
*		- ["name"]				- (!) datasource name;							[STRING]
*		- ["added_on"]			- date and time of publication;					[DATETIME]
*		- ["updated_on"]		- date and time of modification;				[DATETIME]
*		- ["state"]				- state:										[INTEGER]
*									-- 0 - unused (by default),
*									-- 1 - used,
*									-- 2 - removed;
*		- ...
*
*		* for database:
*
*		- ["id"]				- ds identifier (NULL  by default);			[INTEGER || NULL]
*		- ["added_by"]			- user ID who added data (NULL  by default);	[INTEGER || NULL]
*		- ["updated_by"]		- user ID who updated data (NULL  by default).	[INTEGER || NULL]
*		- ...
*
*		(!) - required parameters!
*
*
*	The recommended XML-structure of datasource parameters:
*
*		<datasource-node name="ds" state="1">
*			<added_on>2012-09-19 20:27:55</added_on>
*			<updated_on>2012-09-19 20:27:55</updated_on>
*			...
*		</datasource-node>
*
*
*	The recommended structure of database tables:
*
*		--
*		-- Table structure `list_datasources`
*		--
*
*		CREATE TABLE `list_datasources` ( 
*		  `id`                  bigint(20) unsigned NOT NULL AUTO_INCREMENT,                                -- identifier
*		  `added_on`  	        datetime NOT NULL DEFAULT '0000-00-00 00:00:00',                            -- date and time of publication
*		  `added_by`  	        bigint(20) unsigned DEFAULT NULL,                                           -- author of publication (identifier of user)
*		  `updated_on`  	    timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,   -- date and time of modification (timestamp)
*		  `updated_by`  	    bigint(20) unsigned DEFAULT NULL,                                           -- author of publication (identifier of user)
*		  `state`               tinyint(1) unsigned DEFAULT '0',                                            -- state (0 - hidden/unused, 1 - showed/used, 2 - for remove)
*		  `name`                tinytext,                                                                   -- name of datasource
*		  ...
*		  PRIMARY KEY (`ds_id`),
*		  KEY          `added_on_k` (`added_on`),
*		  KEY          `added_by_k` (`added_by`),
*		  KEY          `updated_on_k` (`updated_on`),
*		  KEY          `updated_by_k` (`updated_by`),
*		  KEY          `state_k` (`state`),
*		  UNIQUE KEY   `name_uk` (`name`(10))
*		) ENGINE=InnoDB DEFAULT CHARSET=utf8;
*
*
*	Description of datasource parameters (associative array):	[ARRAY]
*
*	* default:
*
*		["key"]				- parameter name (key of array datasource parameters);	[STRING]
*
*		["type"]			- type of data:		[STRING]
*								-- "str", "string",
*								-- "int", "integer",
*								-- "float", "double",
*								-- "array",
*								-- "bool", "boolean",
*								-- "date",
*								-- "time",
*								-- "datetime";
*
*		["default"]			- value by default;	[STRING || NUMBER || ARRAY || BOOLEAN ||NULL]
*
*		["required"]		- boolean true if parameter is required, otherwise false;	[BOOLEAN]
*
*		["if_key_arg"]		- boolean true if parameter is key argument, otherwise false	[BOOLEAN]
*								* used with "key_value" in operations: search/select/insert/update/delete (for databases - in the operator "WHERE");
*
*		["key_arg_value"]	- value of key argument;	[STRING || NUMBER || BOOLEAN || NULL]
*
*	*extended:
*
*		["ext_key"]			- name of extended parameter	[STRING]
*								* if not exists or empty or not string, then used option "key"!
*
*	* for parameter from nodes, files (XML):
*		(see the library dom/dom.php - the function phpDOM_get_values_of_nodes_by_params())
*
*		["nodename"]		- node name (if the node contains value of datasource parameter);	[STRING || NULL]
*		["attrname"]		- attribute name (if the attribute of datasource-node contains value of datasource parameter);	[STRING || NULL]
*
*	* for parameter from databases:
*		(see the library sql/sql.php -> fields parameters for the operation "SELECT", "INSERT", "UPDATE", "DELETE")
*
*		["field"]			- field name of a database table;	[STRING || NULL]
*		["alt_field"]		- alternate field name of a database table;	[STRING || NULL]
*		["field_alias"]		- field alias;	[STRING || NULL]
*		["table_alias"]		- table alias;	[STRING || NULL]
*		["for_select"]		- if true, then the field used in operation "SELECT" (true by default);	[BOOLEAN]
*		["for_insert"]		- if true, then the field used in operation "INSERT" (true by default);	[BOOLEAN]
*		["for_update"]		- if true, then the field used in operation "UPDATE" (true by default).	[BOOLEAN]
*
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function: checking required parameters.
*
*	Input:
*			$desc_params_in	- description of datasource parameters;	[ARRAY]
*			$ds_params_in	- datasource parameters.	[ARRAY]
*
*	Output:
*			return boolean true if required parameters are correct, otherwise false.	[BOOLEAN]
*
*	Note:
*
*/
function ds_check_params($desc_params_in = null, $ds_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Checking input argument $ds_params_in
	if(!is_array($ds_params_in))
	{
		return false;
	}
	
	if(is_array($desc_params_in))
	{
		//* parameter name	[STRING || NULL]
		$key  = null;
		
		//* type	[STRING]
		$type = '';
		
		//* buffer	[STRING || NULL]
		$buff = null;
		
		
		foreach($desc_params_in as $arr_id=>$arr_val)
		{
			if(!is_array($arr_val))
			{
				continue;
			}
			
			if(empty($arr_val["required"]))
			{
				continue;
			}
			
			if(!$arr_val["required"])
			{
				continue;
			}
			
			$key  = null;
			$type = '';
			$buff = null;
			
			if(!empty($arr_val["key"]))
			{
				if(is_string($arr_val["key"]))
				{
					$key = $arr_val["key"];
				}
			}
			
			if(empty($key))
			{
				continue;
			}
			
			//checking the required parameter
			if(!isset($ds_params_in[$key]))
			{
				return false;
			}
			
			if(!empty($arr_val["type"]))
			{
				if(is_string($arr_val["type"]))
				{
					switch($arr_val["type"])
					{
						case "bool":
							$type = "boolean";
							break;
							
						case "int":
							$type = "integer";
							break;
							
						case "float":
							$type = "double";
							break;
							
						case "str":
							$type = "string";
							break;
							
						case "date":
							
							if(!function_exists("type_of_date"))
							{
								if($FL_DEBUG)
								{
									echo("Error! Function 'type_of_date()' not exists! [ds.php -> ds_check_params()]");
								}
								return false;
							}
							
							$type = "date";
							$buff = type_of_date($ds_params_in[$key]);
							break;
							
						case "time":
							
							if(!function_exists("type_of_time"))
							{
								if($FL_DEBUG)
								{
									echo("Error! Function 'type_of_time()' not exists! [ds.php -> ds_check_params()]");
								}
								return false;
							}
							
							$type = "time";
							$buff = type_of_time($ds_params_in[$key]);
							break;
							
						case "datetime":
							
							if(!function_exists("type_of_datetime"))
							{
								if($FL_DEBUG)
								{
									echo("Error! Function 'type_of_datetime()' not exists! [ds.php -> ds_check_params()]");
								}
								return false;
							}
							
							$type = "datetime";
							$buff = type_of_datetime($ds_params_in[$key]);
							break;
							
						default:
							$type = $arr_val["type"];
							break;
					}
				}
			}
			
			if($type == "date" || $type == "time" || $type == "datetime")
			{
				if(!empty($buff))
				{
					return true;
				}
			}
			
			if((gettype($ds_params_in[$key])) != $type)
			{
				return false;
			}
		}
	}
	
	return true;
}


/*	Function: checking parameters by key arguments.
*
*	Input:
*			$desc_params_in	- description of datasource parameters;	[ARRAY]
*			$ds_params_in	- datasource parameters.	[ARRAY]
*
*	Output:
*			return boolean true if parameters are correct, otherwise false.	[BOOLEAN]
*
*	Note:
*
*			return false if:
*
*				- $ds_params_in is not array,
*				- ds_check_params($desc_params_in, $ds_params_in) == false,
*				- $desc_params_in[$key]["if_key_arg"] == true && $desc_params_in[$key]["key_arg_value"] != $ds_params_in[$key].
*
*/
function ds_check_params_by_key_args($desc_params_in = null, $ds_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function ds_check_params()
	if(!function_exists("ds_check_params"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_check_params()' not exists! [ds.php -> ds_check_params_by_key_args()]");
		}
		return false;
	}
	
	//Checking of datasource parameters
	if(!ds_check_params($desc_params_in, $ds_params_in))
	{
		return false;
	}
	
	if(is_array($desc_params_in))
	{
		//* parameter name	[STRING || NULL]
		$key				= null;
		
		//* type of data	[STRING || NULL]
		$type_key_arg_value	= null;
		$type_ds_param		= null;
		
		
		foreach($desc_params_in as $arr_id=>&$arr_val)
		{
			if(!is_array($arr_val))
			{
				continue;
			}
			
			if(!empty($arr_val["key"]) && !empty($arr_val["if_key_arg"]))
			{
				if(is_string($arr_val["key"]))
				{
					$key = $arr_val["key"];
					
					if(!empty($ds_params_in[$key]))
					{
						if(empty($arr_val["key_arg_value"]))
						{
							return false;
						}
						
						//get type of data
						$type_key_arg_value	= gettype($arr_val["key_arg_value"]);
						$type_ds_param		= gettype($ds_params_in[$key]);
						
						//checking of data types
						if($type_key_arg_value != $type_ds_param)
						{
							return false;
						}
						
						//checking of values
						if($arr_val["key_arg_value"] != $ds_params_in[$key])
						{
							return false;
						}
					}
					else
					{
						if(!empty($arr_val["key_arg_value"]))
						{
							return false;
						}
					}
				}
			}
		}
	}
	
	return true;
}


/*	Function: normalization of datasource parameters.
*
*	Input:
*			$desc_params_in	- description of datasource parameters;	[ARRAY]
*			$ds_params_in 	- link to datasource parameters.	[ARRAY]
*
*	Output:
*			return boolean true if datasource parameters normalized, otherwise false.	[BOOLEAN]
*
*	Note:
*
*/
function ds_normalize_params($desc_params_in = null, &$ds_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function types_normalize_array_value()
	if(!function_exists("types_normalize_array_value"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'types_normalize_array_value()' not exists! [ds.php -> ds_normalize_params()]");
		}
		return false;
	}
	
	//Check the input argument $desc_params_in
	if(!is_array($desc_params_in))
	{
		return false;
	}
	
	//Normalize parameters of the datasource
	foreach($desc_params_in as $arr_id=>$arr_val)
	{
		types_normalize_array_value($arr_val, $ds_params_in);
	}
	
	return true;
}


/*	Function: synchronization of values from "desc_params" with values from "ds_params".
*
*	Input:
*			$desc_params_in	- link to description of datasource parameters;	[ARRAY]
*			$ds_params_in 	- datasource parameters.	[ARRAY]
*
*	Output:
*			return boolean true if parameters synchronized, otherwise false.	[BOOLEAN]
*
*	Note:
*
*			$desc_params_in[$key]["key_arg_value"] = $ds_params_in[$key] or $desc_params_in[$key]["default"];
*
*/
function ds_sync_desc_params(&$desc_params_in = null, $ds_params_in = null)
{
	//Check input argument $desc_params_in
	if(!is_array($desc_params_in))
	{
		return false;
	}
	
	//Check the input argument $ds_params_in
	if(!is_array($ds_params_in))
	{
		return false;
	}
	
	//* parameter name	[STRING || NULL]
	$key = null;
	
	
	//Sync values
	foreach($desc_params_in as $arr_id=>&$arr_val)
	{
		if(!is_array($arr_val))
		{
			continue;
		}
		
		if(!empty($arr_val["key"]) && !empty($arr_val["if_key_arg"]))
		{
			if(is_string($arr_val["key"]))
			{
				$key = $arr_val["key"];
				
				//init option "key_arg_value" by default (NULL)
				$arr_val["key_arg_value"] = null;
				
				//check option "default"
				if(isset($arr_val["default"]))
				{
					if(is_string($arr_val["default"]) || is_numeric($arr_val["default"]) || is_bool($arr_val["default"]))
					{
						$arr_val["key_arg_value"] = $arr_val["default"];
					}
				}
				
				//check value of parameter
				if(isset($ds_params_in[$key]))
				{
					if(is_string($ds_params_in[$key]) || is_numeric($ds_params_in[$key]) || is_bool($ds_params_in[$key]))
					{
						$arr_val["key_arg_value"] = $ds_params_in[$key];
					}
				}
			}
		}
	}
	
	return true;
}


/*	Function: get array of new datasource parameters.
*
*	Input:	
*			$desc_params_in	- description of datasource parameters.	[ARRAY]
*
*	Output:
*			array of new datasource parameters.	[ARRAY]
*
*	Note:
*
*/
function ds_new_params($desc_params_in = null)
{
	//* returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function ds_normalize_params()
	if(!function_exists("ds_normalize_params"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_normalize_params()' not exists! [ds.php -> ds_new_params()]");
		}
		return $returned_result;
	}
	
	//Normalization of datasource parameters
	ds_normalize_params($desc_params_in, $returned_result);
	
	return $returned_result;
}


/*	Function: get list of values of key arguments from $_REQUEST.
*
*	Input:	
*			$desc_params_in	- description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of values of datasource key arguments.	[ARRAY]
*
*	Note:
*
*			for datasource parameters with option "if_key_arg" == true!
*
*
*			structure of returned list:
*
*				[$key 1] = "value of key argument",
*				...
*				[$key N] = "value of key argument".
*
*/
function ds_get_key_args_from_request($desc_params_in = null)
{
	//* the returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_get_key_args_from_request()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("get_request_value_on_key",
						 "ds_normalize_params"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_get_key_args_from_request()"))
	{
		return $returned_result;
	}
	
	//Check the input argument $desc_params_in
	if(!is_array($desc_params_in))
	{
		return $returned_result;
	}
	
	foreach($desc_params_in as $arr_id=>$arr_val)
	{
		if(!is_array($arr_val))
		{
			continue;
		}
		
		if(!empty($arr_val["key"]) && !empty($arr_val["if_key_arg"]))
		{
			if(is_string($arr_val["key"]))
			{
				//get value of key argument from super global array $_REQUEST
				$returned_result[$arr_val["key"]] = get_request_value_on_key($arr_val["key"]);
			}
		}
	}
	
	if(count($returned_result))
	{
		//normalization of datasource parameters
		ds_normalize_params($desc_params_in, $returned_result);
	}
	
	return $returned_result;
}


/*	Function: get datasource parameters from $_REQUEST.
*
*	Input:
*			$desc_params_in - description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of datasources (array of arrays of datasource parameters).	[ARRAY]
*
*	Note:
*
*			mismatched datasource parameters:
*
*				- if datasource parameters are not correct,
*				- if $desc_params_in[$key]["if_key_arg"] == true && $desc_params_in[$key]["key_arg_value"] != $ds_params[$key].
*
*/
function ds_get_from_request($desc_params_in = null)
{
	//* the returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_get_from_request()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("get_request_value_on_key",
						 "ds_check_params",
						 "ds_normalize_params"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_get_from_request()"))
	{
		return $returned_result;
	}
	
	//Check the input argument $desc_params_in
	if(!is_array($desc_params_in))
	{
		return $returned_result;
	}
	
	//* datasource parameters	[ARRAY]
	$ds_params = array();
	
	
	foreach($desc_params_in as $arr_id=>$arr_val)
	{
		if(!is_array($arr_val))
		{
			continue;
		}
		
		if(!empty($arr_val["key"]))
		{
			if(is_string($arr_val["key"]))
			{
				//get value of ds-parameter from super global array $_REQUEST
				$ds_params[$arr_val["key"]] = get_request_value_on_key($arr_val["key"]);
			}
		}
	}
	
	if(count($ds_params))
	{
		//normalization of datasource parameters
		ds_normalize_params($desc_params_in, $ds_params);
		
		//checking of database parameters by key arguments
		if(ds_check_params($desc_params_in, $ds_params))
		{
			//** if datasource parameter are correct!
			array_push($returned_result, $ds_params);
		}
	}
	
	return $returned_result;
}


/*	Function: get raw datasource parameters (normalized) from datasource-node.
*
*	Input:	
*			$ds_node_in		- datasource node;	[OBJECT]
*			$desc_params_in	- description of datasource parameters.	[ARRAY]
*
*	Output:
*			array of raw datasource parameters.	[ARRAY]
*
*	Note:
*
*/
function ds_get_raw_params_from_ds_node($ds_node_in = null, $desc_params_in = null)
{
	//* the returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_get_raw_params_from_ds_node()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("get_attribute_of_element",
						 "phpDOM_get_values_of_nodes_by_params",
						 "ds_normalize_params"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_get_raw_params_from_ds_node()"))
	{
		return $returned_result;
	}
	
	//Check the input argument $desc_params_in
	if(!is_array($desc_params_in))
	{
		return $returned_result;
	}
	
	//* buffer	[ARRAY || NULL]
	$buff = null;
	
	
	foreach($desc_params_in as $arr_id=>$arr_val)
	{
		if(!is_array($arr_val))
		{
			continue;
		}
		
		if(!empty($arr_val["key"]))
		{
			if(is_string($arr_val["key"]))
			{
				//init value of key argument by default (NULL)
				$returned_result[$arr_val["key"]] = null;
				
				if(!empty($arr_val["nodename"]))
				{
					if(is_string($arr_val["nodename"]))
					{
						//get the value from the node
						$buff = phpDOM_get_values_of_nodes_by_params($ds_node_in, array($arr_val));
						
						if(is_array($buff))
						{
							if(isset($buff[$arr_val["nodename"]]))
							{
								$returned_result[$arr_val["key"]] = $buff[$arr_val["nodename"]];
							}
						}
					}
				}
				else
				{
					if(!empty($arr_val["attrname"]))
					{
						if(is_string($arr_val["attrname"]))
						{
							//get the value from attribute of datasource-node
							$returned_result[$arr_val["key"]] = get_attribute_of_element($ds_node_in, $arr_val["attrname"]);
						}
					}
				}
			}
		}
	}
	
	if(count($returned_result))
	{
		//normalization of datasource parameters
		ds_normalize_params($desc_params_in, $returned_result);
	}
	
	return $returned_result;
}


/*	Function: get list of values of key arguments from datasource-node.
*
*	Input:	
*			$ds_node_in		- datasource node;	[OBJECT]
*			$desc_params_in	- description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of values of datasource key arguments.	[ARRAY]
*
*	Note:
*
*			for datasource parameters with option "if_key_arg" == true!
*
*
*			structure of returned list:
*
*				[$key 1] = "value of key argument",
*				...
*				[$key N] = "value of key argument".
*
*/
function ds_get_key_args_from_ds_node($ds_node_in = null, $desc_params_in = null)
{
	//* the returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function ds_get_raw_params_from_ds_node()
	if(!function_exists("ds_get_raw_params_from_ds_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_get_params_from_ds_node()' not exists! [ds.php -> ds_get_key_args_from_ds_node()]");
		}
		return $returned_result;
	}
	
	//* raw datasource parameters (normalized) from datasource-node	[ARRAY]
	$raw_ds_params = ds_get_raw_params_from_ds_node($ds_node_in, $desc_params_in);
	
	
	if(!count($raw_ds_params))
	{
		return $returned_result;
	}
	
	foreach($desc_params_in as $arr_id=>$arr_val)
	{
		if(!is_array($arr_val))
		{
			continue;
		}
		
		if(!empty($arr_val["key"]) && !empty($arr_val["if_key_arg"]))
		{
			if(is_string($arr_val["key"]))
			{
				//init value of key argument by default (NULL)
				$returned_result[$arr_val["key"]] = null;
				
				if(isset($raw_ds_params[$arr_val["key"]]))
				{
					$returned_result[$arr_val["key"]] = $raw_ds_params[$arr_val["key"]];
				}
			}
		}
	}
	
	return $returned_result;
}


/*	Function: search datasource nodes in root-node.
*
*	Input:
*			$root_node_in		- root-node object;	[OBJECT]
*			$ds_node_name_in	- name of datasource node.	[STRING]
*
*	Output:
*			list of datasource nodes.	[ARRAY]
*
*	Note:
*
*/
function ds_search_nodes($root_node_in = null, $ds_node_name_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function phpDOM_parsing()
	if(!function_exists("phpDOM_parsing"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_parsing()' not exists! [ds.php -> ds_search_nodes()]");
		}
		return $returned_result;
	}
	
	//Check the input argument $ds_node_name_in
	if(empty($ds_node_name_in))
	{
		return $returned_result;
	}
	
	if(!is_string($ds_node_name_in))
	{
		return $returned_result;
	}
	
	return phpDOM_parsing($root_node_in, "^{$ds_node_name_in}$", null, null);
}


/*	Function: search datasource nodes in root-node by key arguments.
*
*	Input:
*			$root_node_in		- root-node object;	[OBJECT]
*			$ds_node_name_in	- name of datasource node;	[STRING]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of datasource nodes.	[ARRAY]
*
*	Note:
*
*/
function ds_search_nodes_by_key_args($root_node_in = null, $ds_node_name_in = null, $desc_params_in = null)
{
	//*returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_search_nodes_by_key_args()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("ds_check_params_by_key_args",
						 "ds_get_raw_params_from_ds_node",
						 "ds_search_nodes"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_search_nodes_by_key_args()"))
	{
		return $returned_result;
	}
	
	//* array of datasource nodes	[ARRAY]
	$ds_nodes = ds_search_nodes($root_node_in, $ds_node_name_in);
	
	
	//Check the array
	if(!is_array($ds_nodes))
	{
		return $returned_result;
	}
	
	//* datasource parameters	[ARRAY || NULL]
	$ds_params = null;
	
	
	for($i=0; $i<count($ds_nodes); $i++)
	{
		//get raw datasource parameters (normalized) from datasource-node
		$ds_params = ds_get_raw_params_from_ds_node($ds_nodes[$i], $desc_params_in);
		
		//checking of database parameters by key arguments
		if(ds_check_params_by_key_args($desc_params_in, $ds_params))
		{
			//** if datasource parameter are correct!
			array_push($returned_result, $ds_nodes[$i]);
		}
	}
	
	return $returned_result;
}


/*	Function: get values of datasource key arguments from root-node.
*
*	Input:	
*			$root_node_in 		- root node object;	[OBJECT]
*			$ds_node_name_in	- name of datasource node;	[STRING]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of values of key arguments.	[ARRAY]
*
*	Note:
*
*			for datasource parameters with option "if_key_arg" == true!
*
*
*			structure of returned list:
*
*				[0][$key] = "value of key argument",
*				...
*				[N][$key] = "value of key argument".
*
*/
function ds_get_key_args_from_node($root_node_in = null, $ds_node_name_in = null, $desc_params_in = null)
{
	//* the returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_get_key_args_from_node()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("ds_search_nodes",
						 "ds_get_key_args_from_ds_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_get_key_args_from_node()"))
	{
		return $returned_result;
	}
	
	//* array of datasource nodes	[ARRAY]
	$ds_nodes = ds_search_nodes($root_node_in, $ds_node_name_in);
	
	
	//Check the array
	if(!is_array($ds_nodes))
	{
		return $returned_result;
	}
	
	//* list of values of key arguments	[ARRAY || NULL]
	$list_key_args	= null;
	
	
	for($i=0; $i<count($ds_nodes); $i++)
	{
		//get list of values of key arguments from datasource-node
		$list_key_args = ds_get_key_args_from_ds_node($ds_nodes[$i], $desc_params_in);
		
		//checking list of values
		if(count($list_key_args))
		{
			array_push($returned_result, $list_key_args);
		}
	}
	
	return $returned_result;
}


/*	Function: get datasource parameters from root-node.
*
*	Input:
*			$root_node_in		- root-node object;	[OBJECT]
*			$ds_node_name_in	- name of datasource node;	[STRING]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of datasources (array of arrays of datasource parameters).	[ARRAY]
*
*	Note:
*
*			mismatched datasource parameters:
*
*				- if datasource parameters are not correct,
*				- if $desc_params_in[$key]["if_key_arg"] == true && $desc_params_in[$key]["key_arg_value"] != $ds_params[$key].
*
*/
function ds_get_from_node($root_node_in = null, $ds_node_name_in = null, $desc_params_in = null)
{
	//*returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_get_from_node()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]$list_key_args
	$r_functions = array("ds_check_params",
						 "ds_get_raw_params_from_ds_node",
						 "ds_search_nodes_by_key_args"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_get_from_node()"))
	{
		return $returned_result;
	}
	
	//* array of datasource nodes by key arguments	[ARRAY]
	$ds_nodes = ds_search_nodes_by_key_args($root_node_in, $ds_node_name_in, $desc_params_in);
	
	
	//Check the array
	if(!is_array($ds_nodes))
	{
		return $returned_result;
	}
	
	//* datasource parameters	[ARRAY || NULL]
	$ds_params = null;
	
	
	for($i=0; $i<count($ds_nodes); $i++)
	{
		//get raw datasource parameters (normalized) from datasource-node
		$ds_params = ds_get_raw_params_from_ds_node($ds_nodes[$i], $desc_params_in);
		
		//checking of database parameters by key arguments
		if(ds_check_params($desc_params_in, $ds_params))
		{
			//** if datasource parameter are correct!
			array_push($returned_result, $ds_params);
		}
	}
	
	return $returned_result;
}


/*	Function: add (or update) datasource into root-node.
*
*	Input:
*			$root_node_in		- link to root-node object;	[OBJECT]
*			$ds_node_name_in	- name of datasource node;	[STRING]
*			$desc_params_in		- description of datasource parameters;	[ARRAY]
*			$ds_params_in 		- link to datasource parameters.	[ARRAY]
*
*	Output:
*			number of added/updated datasource nodes.	[INTEGER]
*
*	Note:
*
*/
function ds_add_into_node(&$root_node_in = null, $ds_node_name_in = null, $desc_params_in = null, &$ds_params_in = null)
{
	//* returned result	[INTEGER]
	$returned_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_add_into_node()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("types_data_formatting",
						 "phpDOM_attach_node",
						 "phpDOM_forming_node",
						 "phpDOM_get_root_node_from_string",
						 "ds_check_params",
						 "ds_normalize_params",
						 "ds_sync_desc_params",
						 "ds_search_nodes_by_key_args"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_add_into_node()"))
	{
		return $returned_result;
	}
	
	//Check the input argument $root_node_in
	if(empty($root_node_in))
	{
		return $returned_result;
	}
	
	//Check the input argument $ds_node_name_in
	if(empty($ds_node_name_in))
	{
		return $returned_result;
	}
	
	if(!is_string($ds_node_name_in))
	{
		return $returned_result;
	}
	
	//Normalize datasource parameters
	ds_normalize_params($desc_params_in, $ds_params_in);
	
	//Check datasource parameters
	if(!ds_check_params($desc_params_in, $ds_params_in))
	{
		return $returned_result;
	}
	
	//Sync desc_params_in and ds_params_in
	if(!ds_sync_desc_params($desc_params_in, $ds_params_in))
	{
		return $returned_result;
	}
	
	//* pattern of nodes 	[ARRAY]
	$pattern_nodes	= array("root" => array("remove_childs" => array("node_name" => null, "attr_name" => null, "attr_value" => null), "attributes" => array()));
	
	//* buffer	[STRING || NULL]
	$buff			= null;
	
	//* key	[STRING || NULL]
	$key			= null;
	
	
	//Update the value of the parameter "updated_on"
	$ds_params_in["updated_on"] = date("Y-m-d H:i:s");
	
	//Forming the $pattern_nodes
	if(is_array($desc_params_in))
	{
		foreach($desc_params_in as $arr_id=>$arr_val)
		{
			if(!is_array($arr_val))
			{
				continue;
			}
			
			if(empty($arr_val["key"]))
			{
				continue;
			}
			
			if(!is_string($arr_val["key"]))
			{
				continue;
			}
			
			$buff = null;
			
			if(isset($ds_params_in[$arr_val["key"]]))
			{
				$buff = types_data_formatting($ds_params_in[$arr_val["key"]], "string", true);
			}
			
			if(!is_string($buff))
			{
				$buff = '';
			}
			
			if(!empty($arr_val["nodename"]))
			{
				if(is_string($arr_val["nodename"]))
				{
					//** if datasource parameter is datasource-node
					
					//forming of list of parameters for removing
					if(empty($pattern_nodes["root"]["remove_childs"]["node_name"]))
					{
						$pattern_nodes["root"]["remove_childs"]["node_name"] = '';
					}
					else
					{
						$pattern_nodes["root"]["remove_childs"]["node_name"].= '|';
					}
					
					$pattern_nodes["root"]["remove_childs"]["node_name"].= ('^').($arr_val["nodename"]).('$');
					
					//forming of node for datasource parameter
					if(is_string($buff))
					{
						//create new nodes
						$pattern_nodes[$arr_val["nodename"]] = array("attach_node" => phpDOM_get_root_node_from_string(('<').($arr_val["nodename"]).('>').($buff).("</").($arr_val["nodename"]).('>'), "XML"));
					}
				}
			}
			else
			{
				if(!empty($arr_val["attrname"]))
				{
					if(is_string($arr_val["attrname"]))
					{
						//** if datasource parameter is attribute of datasource-node
						
						$pattern_nodes["root"]["attributes"][$arr_val["attrname"]] = '';
						
						if(is_string($buff))
						{
							$pattern_nodes["root"]["attributes"][$arr_val["attrname"]] = $buff;
						}
					}
				}
			}
		}
	}
	
	//* array of datasource nodes by key arguments	[ARRAY]
	$ds_nodes = ds_search_nodes_by_key_args($root_node_in, $ds_node_name_in, $desc_params_in);
	
	
	//Check the list
	if(!count($ds_nodes))
	{
		//* new datasource node	[OBJECT]
		$ds_node = phpDOM_get_root_node_from_string("<{$ds_node_name_in}></{$ds_node_name_in}>", "XML");
		
		
		//attach the node into root-node
		$ds_node = phpDOM_attach_node($root_node_in, $ds_node, "end");
		
		//add the node into array of nodes
		array_push($ds_nodes, $ds_node);
	}
	
	for($i=0; $i<count($ds_nodes); $i++)
	{
		//forming the node
		if(phpDOM_forming_node($ds_nodes[$i], $pattern_nodes))
		{
			$returned_result++;
		}
	}
	
	return $returned_result;
}


/*	Function: remove datasource from root-node.
*
*	Input:
*			$root_node_in		- link to root-node object;	[OBJECT]
*			$ds_node_name_in	- name of datasource node;	[STRING]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			number of removed datasource nodes.	[INTEGER]
*
*	Note:
*
*/
function ds_remove_from_node(&$root_node_in, $ds_node_name_in = null, $desc_params_in = null)
{
	//* returned result	[INTEGER]
	$returned_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function phpDOM_remove_node()
	if(!function_exists("phpDOM_remove_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_remove_node()' not exists! [ds.php -> ds_remove_from_node()]");
		}
		return $returned_result;
	}
	
	//Check the function ds_search_nodes_by_key_args()
	if(!function_exists("ds_search_nodes_by_key_args"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_search_nodes_by_key_args()' not exists! [ds.php -> ds_remove_from_node()]");
		}
		return $returned_result;
	}
	
	//Check the input argument $root_node_in
	if(empty($root_node_in))
	{
		return $returned_result;
	}
	
	//* array of datasource nodes by key arguments	[ARRAY]
	$ds_nodes = ds_search_nodes_by_key_args($root_node_in, $ds_node_name_in, $desc_params_in);
	
	
	for($i=0; $i<count($ds_nodes); $i++)
	{
		//remove the node
		if(phpDOM_remove_node($ds_nodes[$i]))
		{
			$returned_result++;
		}
	}
	
	return $returned_result;
}


/*	Function: get values of key arguments of datasource from XML-file.
*
*	Input:	
*			$file_in 			- file name;	[STRING]
*			$ds_node_name_in	- name of datasource node;	[STRING]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of values of key arguments.	[ARRAY]
*
*	Note:
*
*			for datasource parameters with option "if_key_arg" == true!
*
*
*			structure of returned list:
*
*				[0][$key] = "value of key argument",
*				...
*				[N][$key] = "value of key argument".
*
*/
function ds_get_key_args_from_file($file_in = null, $ds_node_name_in = null, $desc_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function phpDOM_get_root_node_from_file()
	if(!function_exists("phpDOM_get_root_node_from_file"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_get_root_node_from_file()' not exists! [ds.php -> ds_get_key_args_from_file()]");
		}
		return array();
	}
	
	//Check the function ds_get_key_args_from_node()
	if(!function_exists("ds_get_key_args_from_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_get_key_args_from_node()' not exists! [ds.php -> ds_get_key_args_from_file()]");
		}
		return array();
	}
	
	//* root-node from a XML-file	[OBJECT || NULL]
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	
	//Get values of key arguments of datasource from root-node
	return ds_get_key_args_from_node($root_node, $ds_node_name_in, $desc_params_in);
}


/*	Function: get datasource parameters from XML-file.
*
*	Input:
*			$file_in			- file name;	[STRING]
*			$ds_node_name_in	- name of datasource node;	[STRING]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of datasources (array of arrays of datasource parameters).	[ARRAY]
*
*	Note:
*			mismatched datasource parameters:
*
*				- if datasource parameters are not correct,
*				- if $desc_params_in[$key]["if_key_arg"] == true && $desc_params_in[$key]["key_arg_value"] != $ds_params[$key].
*
*/
function ds_get_from_file($file_in = null, $ds_node_name_in = null, $desc_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function phpDOM_get_root_node_from_file()
	if(!function_exists("phpDOM_get_root_node_from_file"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_get_root_node_from_file()' not exists! [ds.php -> ds_get_from_file()]");
		}
		return array();
	}
	
	//Check the function ds_get_from_node()
	if(!function_exists("ds_get_from_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_get_from_node()' not exists! [ds.php -> ds_get_from_file()]");
		}
		return array();
	}
	
	//* root-node from a XML-file	[OBJECT || NULL]
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	
	//get array of datasource parameters from root-node
	return ds_get_from_node($root_node, $ds_node_name_in, $desc_params_in);
}


/*	Function: add (or update) datasource into XML-file.
*
*	Input:
*			$file_in			- file name;	[STRING]
*			$root_node_name_in	- root-node name or NULL;	[STRING || NULL]
*			$ds_node_name_in	- name of datasource node;	[STRING]
*			$desc_params_in		- description of datasource parameters;	[ARRAY]
*			$ds_params_in 		- link to datasource parameters.	[ARRAY]
*
*	Output:
*			number of added/updated datasources.	[INTEGER]
*
*	Note:
*
*			if $root_node_name_in == NULL, then will be used root-node from XML-file!
*
*/
function ds_add_into_file($file_in = null, $root_node_name_in = null, $ds_node_name_in = null, $desc_params_in = null, &$ds_params_in = null)
{
	//* returned result	[INTEGER]
	$returned_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_add_into_file()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_parsing",
						 "phpDOM_get_root_node_from_string",
						 "phpDOM_get_root_node_from_file",
						 "phpDOM_write_document_to_file",
						 "ds_add_into_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_add_into_file()"))
	{
		return $returned_result;
	}
	
	//* root-node from XML-file	[OBJECT || NULL]
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	
	//Check the root-node
	if(!$root_node)
	{
		//create new root-node
		$root_node = phpDOM_get_root_node_from_string("<body></body>", "xml");
	}
	
	//* a used root-node	[OBJECT || NULL]
	$used_root_node = $root_node;
	
	
	//Check the input argument $type_in
	if(!empty($root_node_name_in))
	{
		if(is_string($root_node_name_in))
		{
			//* array of nodes with the name of $root_node_name_in	[ARRAY]
			$founded_nodes = phpDOM_parsing($root_node, "^{$root_node_name_in}$", null, null);
			
			
			//check the array
			if(is_array($founded_nodes))
			{
				if(count($founded_nodes))
				{
					//init
					$used_root_node = $founded_nodes[0];
				}
			}
		}
	}
	
	//Add/update datasources
	$returned_result = ds_add_into_node($used_root_node, $ds_node_name_in, $desc_params_in, $ds_params_in);
	
	if($returned_result)
	{
		//rewrite a file
		if(!phpDOM_write_document_to_file($root_node, $file_in, "xml"))
		{
			$returned_result = 0;
		}
	}
	
	return $returned_result;
}


/*	Function: remove datasource from XML-file.
*
*	Input:
*			$file_in			- file name;	[STRING]
*			$ds_node_name_in	- name of datasource node;	[STRING]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			number of removed datasources.	[INTEGER]
*
*	Note:
*
*/
function ds_remove_from_file($file_in = null, $ds_node_name_in = null, $desc_params_in = null)
{
	//* returned result	[INTEGER]
	$returned_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_remove_from_file()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_get_root_node_from_file",
						 "phpDOM_write_document_to_file",
						 "ds_remove_from_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_remove_from_file()"))
	{
		return $returned_result;
	}
	
	//* root-node from XML-file	[OBJECT || NULL]
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	
	//Remove matching datasources
	$returned_result = ds_remove_from_node($root_node, $ds_node_name_in, $desc_params_in);
	
	if($returned_result)
	{
		//rewriting of XML-file
		if(!phpDOM_write_document_to_file($root_node, $file_in, "xml"))
		{
			$returned_result = 0;
		}
	}
	
	return $returned_result;
}


/*	Function: get object of database class.
*
*	Input:	
*			$connect_params_in - connection parameters (see library "db").	[ARRAY]
*
*	Output:
*			object of class by database type (dbMySQL ...) or NULL.	[OBJECT || NULL]
*
*	Note:
*
*			connection parameters:
*
*				-- required: "db_type", "hostname", "user", "database", "table".
*
*/
function ds_get_db_object($connect_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the input argument $connect_params_in
	if(!is_array($connect_params_in))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the input argument 'connect_params_in'! [ds.php -> ds_get_db_object()]");
		}
		return null;
	}
	
	//Check required connection parameters (db_type, database, table)
	
	//** db_type
	if(empty($connect_params_in["db_type"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the connection parameter 'db_type'! [ds.php -> ds_get_db_object()]");
		}
		return null;
	}
	
	if(!is_string($connect_params_in["db_type"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Incorrect value of the connection parameter 'db_type'! [ds.php -> ds_get_db_object()]");
		}
		return null;
	}
	
	//** database
	if(empty($connect_params_in["database"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the connection parameter 'database'! [ds.php -> ds_get_db_object()]");
		}
		return null;
	}
	
	if(!is_string($connect_params_in["database"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Incorrect value of the connection parameter 'database'! [ds.php -> ds_get_db_object()]");
		}
		return null;
	}
	
	//** table	
	if(empty($connect_params_in["table"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the connection parameter 'table'! [ds.php -> ds_get_db_object()]");
		}
		return null;
	}
	
	if(!is_string($connect_params_in["table"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Incorrect value of the connection parameter 'table'! [ds.php -> ds_get_db_object()]");
		}
		return null;
	}
	
	//Check a value of the connection parameter 'db_type'
	switch($connect_params_in["db_type"])
	{
		case "mysql":
		case "MySQL":
		case "MYSQL":
			
			//check the function dbMySQL_check_connect_params()
			if(!function_exists("dbMySQL_check_connect_params"))
			{
				if($FL_DEBUG)
				{
					echo("Error! Function 'dbMySQL_check_connect_params()' not exists! [ds.php -> ds_get_db_object()]");
				}
				return null;
			}
			
			//check the class dbMySQL
			if(!class_exists("dbMySQL"))
			{
				if($FL_DEBUG)
				{
					echo("Error! Class 'dbMySQL' not exists! [ds.php -> ds_get_db_object()]");
				}
				return null;
			}
			
			//check the input argument $connect_params_in
			if(!dbMySQL_check_connect_params($connect_params_in))
			{
				if($FL_DEBUG)
				{
					echo("Error! Incorrect parameters of the connection! [ds.php -> ds_get_db_object()]");
				}
				return null;
			}
			
			//* new object of the class "dbMySQL"	[OBJECT]
			$db_object = new dbMySQL();
			
			
			//init parameters of the connection
			$db_object->params = $connect_params_in;
			
			return $db_object;
			
		default:
			
			if($FL_DEBUG)
			{
				echo(("Error! The database type '").($connect_params_in["db_type"]).("' is unsupported! [ds.php -> ds_get_db_object()]"));
			}
	}
	
	return null;
}


/*	Function: get values of key arguments of datasource from database.
*
*	Input:	
*			$connect_params_in	- parameters of a connection (see the library "db");	[ARRAY]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of values of key arguments.	[ARRAY]
*
*	Note:
*
*			connection parameters:
*
*				-- required: "db_type", "hostname", "user", "database", "table".
*
*
*
*			for datasource parameters with option "if_key_arg" == true!
*
*
*			structure of returned list:
*
*				[0][$key] = "value of key argument",
*				...
*				[N][$key] = "value of key argument".
*
*/
function ds_get_key_args_from_db($connect_params_in = null, $desc_params_in = null)
{
	//* a returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function sql_get_field_name()
	if(!function_exists("sql_get_field_name"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'sql_get_field_name()' not exists! [ds.php -> ds_get_key_args_from_db()]");
		}
		return $returned_result;
	}
	
	//Check the function ds_get_db_object()
	if(!function_exists("ds_get_db_object"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_get_db_object()' not exists! [ds.php -> ds_get_key_args_from_db()]");
		}
		return $returned_result;
	}
	
	//Check the input argument $desc_params_in
	if(!is_array($desc_params_in))
	{
		return $returned_result;
	}
	
	//* list of fields	[STRING || NULL]
	$list_fields		= null;
	
	//* list "field to key"	[ARRAY]
	//
	//**	[$field] = $key
	$list_field_to_key	= array();
	
	
	//Forming of list of fields
	foreach($desc_params_in as $arr_id=>$arr_val)
	{
		if(!is_array($arr_val))
		{
			continue;
		}
		
		if(!empty($arr_val["key"]) && !empty($arr_val["if_key_arg"]) && !empty($arr_val["field"]))
		{
			if(is_string($arr_val["key"]) && is_string($arr_val["field"]))
			{
				if(empty($list_fields))
				{
					$list_fields = '';
				}
				else
				{
					$list_fields.= ", ";
				}
				
				$list_field_to_key[$arr_val["field"]] = $arr_val["key"];
				
				$list_fields.= sql_get_field_name($arr_val["field"], null);
			}
		}
	}
	
	//Checking of list of fields
	if(empty($list_fields))
	{
		return $returned_result;
	}
	
	//* new object of the database class	[OBJECT || NULL]
	$db_object = ds_get_db_object($connect_params_in);
	
	
	//Check the object
	if($db_object)
	{
		//* SQL-query	[STRING]
		$query		= ("SELECT {$list_fields} FROM ").($connect_params_in["table"]);
		
		//* resultset	[RESOURCE || BOOLEAN || NULL]
		$resultset	= $db_object->send_query($query);
		
		
		//checking of resultset
		if(is_resource($resultset))
		{
			//* list of values of key arguments	[ARRAY || NULL]
			$list_key_args = null;
			
			
			//read data from the resultset
			while(($row = mysql_fetch_assoc($resultset)))
			{
				$list_key_args = array();
				
				foreach($list_field_to_key as $k=>$v)
				{
					$list_key_args[$v] = null;
					
					if(isset($row[$k]))
					{
						$list_key_args[$v] = $row[$k];
					}
				}
				
				//checking of list of values
				if(count($list_key_args))
				{
					array_push($returned_result, $list_key_args);
				}
			}
			
			//freeing of memory allocated for resultset
			mysql_free_result($resultset);
		}
		else
		{
			if($FL_DEBUG)
			{
				//check errors
				if($db_object->errno())
				{
					echo($db_object->error());
				}
			}
		}
	}
	
	return $returned_result;
}


/*	Function: get array of parameters (list of fields names and list of values) for operator "WHERE".
*
*	Input:
*			$desc_params_in - description of datasource parameters.	[ARRAY]
*
*	Output:
*			array of parameters for operator "WHERE".	[ARRAY]
*
*	Note:
*
*			structure of returned array:
*
*				["fields"] - array of fields parameters:
*
*					-- array(array("key" => "key-name", "field"=> "field-name", "type" => "string", "compare" => '='), ...);
*
*				["values"] - array of fields values:
*
*					-- array("key-name" => "value", ...);
*
*/
function ds_get_params_for_where_db($desc_params_in = null)
{
	//* returned result	[ARRAY]
	$returned_result = array("fields" => array(), "values" => array());
	
	
	//Checking of input argument $desc_params_in
	if(is_array($desc_params_in))
	{
		//* array of field parameters	[ARRAY || NULL]
		$field_params	= null;
		
		//* key	[STRING || NULL]
		$key			= null;
		
		
		foreach($desc_params_in as $arr_id=>$arr_val)
		{
			if(!is_array($arr_val))
			{
				continue;
			}
			
			if(!empty($arr_val["key"]) && !empty($arr_val["if_key_arg"]) && !empty($arr_val["field"]))
			{
				if(is_string($arr_val["key"]) && is_string($arr_val["field"]))
				{
					$key = $arr_val["key"];
					
					//init field parameters by default
					$field_params = array("key" => $key, "field"=> $arr_val["field"], "type" => "string", "compare" => '=');
					
					//checking of option "type"
					if(!empty($arr_val["type"]))
					{
						if(is_string($arr_val["type"]))
						{
							$field_params["type"] = $arr_val["type"];
						}
					}
					
					//checking of option "table_alias"
					if(!empty($arr_val["table_alias"]))
					{
						if(is_string($arr_val["table_alias"]))
						{
							$field_params["table_alias"] = $arr_val["table_alias"];
						}
					}
					
					//init of where-value by default (NULL)
					$returned_result["values"][$key] = null;
					
					//checking of option "key_arg_value"
					if(isset($arr_val["key_arg_value"]))
					{
						$returned_result["values"][$key] = $arr_val["key_arg_value"];
					}
					
					array_push($returned_result["fields"], $field_params);
				}
			}
		}
	}
	
	return $returned_result;
}


/*	Function: get datasource parameters from database.
*
*	Input:
*			$connect_params_in	- connection parameters (see library "db");	[ARRAY]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			list of datasources (array of arrays of datasource parameters).	[ARRAY]
*
*	Note:
*
*			connection parameters:
*
*				-- required: "db_type", "hostname", "user", "database", "table".
*
*/
function ds_get_from_db($connect_params_in = null, $desc_params_in = null)
{
	//* returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_get_from_db()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("sql_select",
						 "sql_where",
						 "ds_check_params",
						 "ds_normalize_params",
						 "ds_get_db_object",
						 "ds_get_params_for_where_db"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_get_from_db()"))
	{
		return $returned_result;
	}
	
	//* new object of the database class	[OBJECT || NULL]
	$db_object = ds_get_db_object($connect_params_in);
	
	
	//Check the object
	if($db_object)
	{
		//* list of tables	[ARRAY]
		$tables			= array(array("table" => $connect_params_in["table"]));
		
		//* parameters for the operator 'WHERE'	[ARRAY]
		$params_where	= ds_get_params_for_where_db($desc_params_in);
		
		//* SQL-query	[STRING || NULL]
		$query			= sql_select($tables, $desc_params_in, $params_where["fields"], $params_where["values"]);
		
		//* resultset	[RESOURCE || BOOLEAN || NULL]
		$resultset		= $db_object->send_query($query);
		
		
		//check resultset
		if(is_resource($resultset))
		{
			//* datasource parameters	[ARRAY || NULL]
			$ds_params = null;
			
			
			//read data from the resultset
			while(($row = mysql_fetch_assoc($resultset)))
			{
				$ds_params = array();
				
				foreach($row as $k=>$v)
				{
					$ds_params[$k] = $v;
				}
				
				//normalize datasource parameters
				ds_normalize_params($desc_params_in, $ds_params);
				
				//check datasource parameters
				if(ds_check_params($desc_params_in, $ds_params))
				{
					array_push($returned_result, $ds_params);
				}
			}
			
			//freeing the memory allocated for the result set
			mysql_free_result($resultset);
		}
		else
		{
			if($FL_DEBUG)
			{
				//check errors
				if($db_object->errno())
				{
					echo($db_object->error());
				}
			}
		}
	}
	
	return $returned_result;
}


/*	Function: add (or update) datasource into a database.
*
*	Input:
*			$connect_params_in	- connection parameters (see library "db");	[ARRAY]
*			$desc_params_in		- description of datasource parameters;	[ARRAY]
*			$ds_params_in 		- link to parameters of a datasource.	[ARRAY]
*
*	Output:
*			number of added/updated datasources.	[INTEGER]
*
*	Note:
*
*			connection parameters:
*
*				-- required: "db_type", "hostname", "user", "database", "table".
*
*/
function ds_add_into_db($connect_params_in = null, $desc_params_in = null, &$ds_params_in = null)
{
	//* returned result	[INTEGER]
	$returned_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_add_into_db()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("sql_insert",
						 "sql_update",
						 "ds_check_params",
						 "ds_normalize_params",
						 "ds_sync_desc_params",
						 "ds_get_db_object",
						 "ds_get_from_db",
						 "ds_get_params_for_where_db"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_add_into_db()"))
	{
		return $returned_result;
	}
	
	//Normalize datasource parameters
	ds_normalize_params($desc_params_in, $ds_params_in);
	
	//Check datasource parameters
	if(!ds_check_params($desc_params_in, $ds_params_in))
	{
		return $returned_result;
	}
	
	//Sync desc_params_in and ds_params_in
	if(!ds_sync_desc_params($desc_params_in, $ds_params_in))
	{
		return $returned_result;
	}
	
	//* new object of the database class	[OBJECT || NULL]
	$db_object = ds_get_db_object($connect_params_in);
	
	
	//Check the object
	if(!$db_object)
	{
		return $returned_result;
	}
	
	//* list of datasources	[ARRAY]
	$list_ds	= ds_get_from_db($connect_params_in, $desc_params_in);
	
	//* a query	string	[STRING || NULL]
	$query		= null;
	
	
	//Update the value of the parameter "updated_on"
	$ds_params_in["updated_on"] = date("Y-m-d H:i:s");
	
	//Check the list
	if(!count($list_ds))
	{
		//** INSERT
		
		//echo("<br />INSERT; name = ".$ds_params_in["name"]."<br />");
		
		//get a query for the operation "INSERT"
		$query = sql_insert($connect_params_in["table"], $desc_params_in, $ds_params_in);
		
		$returned_result = 1;
	}
	else
	{
		//** UPDATE
		
		//echo("<br />UPDATE; name = ".$ds_params_in["name"]."<br />");
		
		//* parameters for the operator 'WHERE'	[ARRAY]
		$params_where = ds_get_params_for_where_db($desc_params_in);
		
		
		//get a query for the operation "UPDATE"
		$query = sql_update($connect_params_in["table"], $desc_params_in, $params_where["fields"], $ds_params_in);
		
		$returned_result = count($list_ds);
	}
	
	//Send the request
	if(!$db_object->send_query($query))
	{
		if($FL_DEBUG)
		{
			//check errors
			if($db_object->errno())
			{
				echo($db_object->error());
			}
		}
		
		$returned_result = 0;
	}
	
	return $returned_result;
}


/*	Function: remove datasource from a database.
*
*	Input:
*			$connect_params_in	- connection parameters (see the library "db");	[ARRAY]
*			$desc_params_in		- description of datasource parameters.	[ARRAY]
*
*	Output:
*			number of removed datasources.	[INTEGER]
*
*	Note:
*
*			connection parameters:
*
*				-- required: "db_type", "hostname", "user", "database", "table".
*
*/
function ds_remove_from_db($connect_params_in = null, $desc_params_in = null)
{
	//* returned result	[INTEGER]
	$returned_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [ds.php -> ds_remove_from_db()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("sql_delete",
						 "ds_get_db_object",
						 "ds_get_from_db",
						 "ds_get_params_for_where_db"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "ds.php", "ds_remove_from_db()"))
	{
		return $returned_result;
	}
	
	//* new object of the database class	[OBJECT || NULL]
	$db_object = ds_get_db_object($connect_params_in);
	
	
	//Check the object
	if(!$db_object)
	{
		return $returned_result;
	}
	
	//* list of datasources	[ARRAY]
	$list_ds = ds_get_from_db($connect_params_in, $desc_params_in);
	
	
	//Check the list
	if(count($list_ds))
	{
		//* parameters for the operator 'WHERE'	[ARRAY]
		$params_where	= ds_get_params_for_where_db($desc_params_in);
		
		//* a query for the operation "DELETE"	[STRING || NULL]
		$query			= null;
		
		
		for($i=0; $i<count($list_ds); $i++)
		{
			$query = sql_delete($connect_params_in["table"], $params_where["fields"], $params_where["values"]);
		}
		
		
		
		
		$returned_result = count($list_ds);
		
		//send the request
		if(!$db_object->send_query($query))
		{
			if($FL_DEBUG)
			{
				//check errors
				if($db_object->errno())
				{
					echo($db_object->error());
				}
			}
			
			$returned_result = 0;
		}
	}
	
	return $returned_result;
}


/*	Function: get file name of repository from the datasource parameters by ID of the target repository.
*
*	Input:
*			$datasource_params_in	- datasource parameters (see library "db" and "ds_datasource.php");	[ARRAY]
*			$target_id_in			- ID of the target repository of null.	[STRING || NULL]
*
*	Output:
*			file name or null.	[STRING || NULL]
*
*	Note:
*
*			datasource parameters:
*
*				-- required: "file" or "files" with $target_id_in.
*
*/
function ds_get_repository_file_name_by_target_id($datasource_params_in = null, $target_id_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check input arguments
	if(!is_array($datasource_params_in))
	{
		return null;
	}
	
	if(empty($target_id_in))
	{
		return null;
	}
	
	if(!is_string($target_id_in))
	{
		return null;
	}
	
	//check parameter "files"
	if(empty($datasource_params_in["files"]))
	{
		return null;
	}
	
	if(!is_array($datasource_params_in["files"]))
	{
		return null;
	}
	
	//get file name by ID
	if(empty($datasource_params_in["files"][$target_id_in]))
	{
		return null;
	}
	
	if(!is_array($datasource_params_in["files"][$target_id_in]))
	{
		return null;
	}
	
	if(empty($datasource_params_in["files"][$target_id_in]["path"]))
	{
		return null;
	}
	
	if(!is_string($datasource_params_in["files"][$target_id_in]["path"]))
	{
		return null;
	}
	
	return $datasource_params_in["files"][$target_id_in]["path"];
}


/*	Function: get table name of repository from the datasource parameters by ID of the target repository.
*
*	Input:
*			$datasource_params_in	- datasource parameters (see library "db" and "ds_datasource.php");	[ARRAY]
*			$target_id_in			- ID of the target repository of null.	[STRING || NULL]
*
*	Output:
*			table name or null.	[STRING || NULL]
*
*	Note:
*
*			datasource parameters:
*
*				-- required: "table" or "tables" with $target_id_in.
*
*/
function ds_get_repository_table_name_by_target_id($datasource_params_in = null, $target_id_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check input arguments
	if(!is_array($datasource_params_in))
	{
		return null;
	}
	
	if(empty($target_id_in))
	{
		return null;
	}
	
	if(!is_string($target_id_in))
	{
		return null;
	}
	
	//check parameter "tables"
	if(empty($datasource_params_in["tables"]))
	{
		return null;
	}
	
	if(!is_array($datasource_params_in["tables"]))
	{
		return null;
	}
	
	//get table name by ID
	if(empty($datasource_params_in["tables"][$target_id_in]))
	{
		return null;
	}
	
	if(!is_string($datasource_params_in["tables"][$target_id_in]))
	{
		return null;
	}
	
	return $datasource_params_in["tables"][$target_id_in];
}


/*	Function: check datasource parameters.
*
*	Input:
*			$datasource_params_in	- datasource parameters (see library "db" and "ds_datasource.php");	[ARRAY]
*			$target_id_in			- ID of the target repository of null.	[STRING || NULL]
*
*	Output:
*			the normalized datasource parameters or null.	[ARRAY || NULL]
*
*	Note:
*
*			datasource parameters:
*
*				-- required:
*					~ for type "xml": "file" or "files" with $target_id_in,
*					~ for type "db":  "db_type", "hostname", "user", "database", "table" or "tables" with $target_id_in.
*
*/
function ds_check_datasource_params($datasource_params_in = null, $target_id_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function ds_get_repository_file_name_by_target_id()
	if(!function_exists("ds_get_repository_file_name_by_target_id"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_get_repository_file_name_by_target_id()' not exists! [ds.php -> ds_check_datasource_params()]");
		}
		return null;
	}
	
	//Check the function ds_get_repository_table_name_by_target_id()
	if(!function_exists("ds_get_repository_table_name_by_target_id"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_get_repository_table_name_by_target_id()' not exists! [ds.php -> ds_check_datasource_params()]");
		}
		return null;
	}
	
	//Check input arguments
	if(!is_array($datasource_params_in))
	{
		return null;
	}
	
	//Check parameter "type"
	if(empty($datasource_params_in["type"]))
	{
		return null;
	}
	
	if(!is_string($datasource_params_in["type"]))
	{
		return null;
	}
	
	//* connection parameters	[ARRAY]
	$datasource_params = $datasource_params_in;
	
	
	//Check datasource type
	switch($datasource_params["type"])
	{
		case "db":
		case "Db":
		case "DB":
			
			//check parameter "table"
			if(!empty($datasource_params["table"]))
			{
				if(!is_string($datasource_params["table"]))
				{
					$datasource_params["table"] = null;
				}
			}
			
			if(!empty($target_id_in))
			{
				if(is_string($target_id_in))
				{
					$datasource_params["table"] = ds_get_repository_table_name_by_target_id($datasource_params, $target_id_in);
				}
			}
			
			if(!empty($datasource_params["table"]))
			{
				return $datasource_params;
			}
			
			break;
	
		case "xml":
		case "Xml":
		case "XML":
			
			//check parameter "file"
			if(!empty($datasource_params["file"]))
			{
				if(!is_string($datasource_params["file"]))
				{
					$datasource_params["file"] = null;
				}
			}
			
			if(!empty($target_id_in))
			{
				if(is_string($target_id_in))
				{
					$datasource_params["file"] = ds_get_repository_file_name_by_target_id($datasource_params, $target_id_in);
				}
			}
			
			if(!empty($datasource_params["file"]))
			{
				return $datasource_params;
			}
			
			break;
	}
	
	return null;
}


/*	Function: extending of datasource parameters.
*
*	Input:
*			$ext_in				- extended data;	[ARRAY]
*			$desc_ext_params_in	- description of extended parameters;	[ARRAY]
*			$ds_params_in		- link to parameters of a datasource.	[ARRAY]
*
*	Output:
*			number of added/updated parameters.	[INTEGER]
*
*	Note:
*
*/
function ds_extend_params($ext_in = null, $desc_ext_params_in = null, &$ds_params_in = null)
{
	//* returned result	[INTEGER]
	$returned_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function types_normalize_array_value()
	if(!function_exists("types_normalize_array_value"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'types_normalize_array_value()' not exists! [ds.php -> ds_extend_params()]");
		}
		return $returned_result;
	}
	
	//Checking of input argument $ext_in
	if(!is_array($ext_in))
	{
		return $returned_result;
	}
	
	//Checking of input argument $desc_ext_params_in
	if(!is_array($desc_ext_params_in))
	{
		return $returned_result;
	}
	
	//Checking of input argument $ds_params_in
	if(!is_array($ds_params_in))
	{
		return $returned_result;
	}
	
	//* extended data	[ARRAY]
	$ext = $ext_in;
	
	//* name of parameter	[STRING || NULL]
	//
	//**	"ext_key" or "key"
	$key = null;
	
	
	foreach($desc_ext_params_in as $arr_id=>$arr_val)
	{
		if(!is_array($arr_val))
		{
			continue;
		}
		
		if(!empty($arr_val["key"]))
		{
			if(is_string($arr_val["key"]))
			{
				$key = $arr_val["key"];
			}
		}
		
		if(!empty($arr_val["ext_key"]))
		{
			if(is_string($arr_val["ext_key"]))
			{
				$key = $arr_val["ext_key"];
			}
		}
		
		if(!empty($key))
		{
			//checking of extended data by key
			if(isset($ext[$arr_val["key"]]))
			{
				types_normalize_array_value($arr_val, $ext);
				
				$ds_params_in[$key] = $ext[$arr_val["key"]];
				$returned_result++;
			}
		}
	}
	
	return $returned_result;
}


//** CLASSES

/*	Class: data source.
*
*	Input: none.
*/
abstract class ds
{
	//** Options
	
	//** public
	
	//* node name of datasource	[STRING]
	public $nodename;
	
	//* description of datasource parameters	[ARRAY]
	public $desc_params;
	
	//* description of extended parameters	[ARRAY]
	public $desc_ext_params;
	
	//* datasource parameters	[ARRAY]
	public $params;
	
	
	//** private
	
	
	//** Methods
	
	//*	method: checking required parameters.
	//
	//*	input: none.
	//
	//*	output:
	//			return boolean true if required parameters are correct, otherwise false.	[BOOLEAN]
	//
	//*	note:
	//
	public function check_params()
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_check_params()
		if(!function_exists("ds_check_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_check_params()' not exists! [ds.php -> class ds]");
			}
			return false;
		}
		
		return ds_check_params($this->desc_params, $this->params);
	}
	
	//*	method: checking parameters by key arguments.
	//
	//*	input: none.
	//
	//*	output:
	//			return boolean true if required parameters are correct, otherwise false.	[BOOLEAN]
	//
	//*	note:
	//
	//			return false if:
	//
	//				- $ds_params_in is not array,
	//				- ds_check_params($desc_params_in, $ds_params_in) == false,
	//				- $desc_params_in[$key]["if_key_arg"] == true && $desc_params_in[$key]["key_arg_value"] != $ds_params_in[$key].
	//
	public function check_params_by_key_args()
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_check_params_by_key_args()
		if(!function_exists("ds_check_params_by_key_args"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_check_params_by_key_args()' not exists! [ds.php -> class ds]");
			}
			return false;
		}
		
		return ds_check_params_by_key_args($this->desc_params, $this->params);
	}
	
	//*	method: normalization of datasource parameters.
	//
	//*	input: none.
	//
	//*	output:
	//			return boolean true if datasource parameters normalized, otherwise false.	[BOOLEAN]
	//
	//*	note:
	//
	public function normalize()
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_normalize_params()
		if(!function_exists("ds_normalize_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_normalize_params()' not exists! [ds.php -> class ds]");
			}
			return false;
		}
		
		return ds_normalize_params($this->desc_params, $this->params);
	}
	
	//*	method: synchronization of values from "desc_params" with values from "ds_params".
	//
	//*	input: none.
	//
	//*	output:
	//			return boolean true if parameters synchronized, otherwise false.	[BOOLEAN]
	//
	//*	note:
	//
	//			$desc_params[$key]["key_arg_value"] = $ds_params[$key] or $desc_params[$key]["default"].
	//
	public function sync_desc_params()
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_sync_desc_params()
		if(!function_exists("ds_sync_desc_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_sync_desc_params()' not exists! [ds.php -> class ds]");
			}
			return false;
		}
		
		return ds_sync_desc_params($this->desc_params, $this->params);
	}
	
	//*	method: get values of datasource key arguments from $_REQUEST.
	//
	//*	input:
	//			none.
	//
	//*	output:
	//			list of values of key arguments.	[ARRAY]
	//
	//*	note:
	//
	//			for datasource parameters with option "if_key_arg" == true!
	//
	//
	//			structure of returned list:
	//
	//				[0][$key] = "value of key argument",
	//				...
	//				[N][$key] = "value of key argument".
	//
	public function get_key_args_from_request()
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_get_key_args_from_request()
		if(!function_exists("ds_get_key_args_from_request"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_key_args_from_request()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		return ds_get_key_args_from_request($this->desc_params);
	}
	
	//*	method: get datasource parameters from $_REQUEST.
	//
	//*	input:
	//			none.
	//
	//*	output:
	//			list of datasources (array of arrays of datasource parameters).	[ARRAY]
	//
	//*	note:
	//
	//			mismatched datasource parameters:
	//
	//				- if datasource parameters are not correct,
	//				- if $desc_params[$key]["if_key_arg"] == true && $desc_params[$key]["key_arg_value"] != $ds_params[$key].
	//
	public function get_from_request()
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_get_from_request()
		if(!function_exists("ds_get_from_request"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_from_request()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		return ds_get_from_request($this->desc_params);
	}
	
	//*	method: get values of datasource key arguments from root-node.
	//
	//*	input:
	//			$root_node_in - root-node object.	[OBJECT]
	//
	//*	output:
	//			list of values of key arguments.	[ARRAY]
	//
	//*	note:
	//
	//			for datasource parameters with option "if_key_arg" == true!
	//
	//
	//			structure of returned list:
	//
	//				[0][$key] = "value of key argument",
	//				...
	//				[N][$key] = "value of key argument".
	//
	public function get_key_args_from_node($root_node_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_get_key_args_from_node()
		if(!function_exists("ds_get_key_args_from_node"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_key_args_from_node()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		return ds_get_key_args_from_node($root_node_in, $this->nodename, $this->desc_params);
	}
	
	//*	method: get datasource parameters from root-node.
	//
	//*	input:
	//			$root_node_in - root-node object.	[OBJECT]
	//
	//*	output:
	//			list of datasources (array of arrays of datasource parameters).	[ARRAY]
	//
	//*	note:
	//
	//			mismatched datasource parameters:
	//
	//				- if datasource parameters are not correct,
	//				- if $desc_params[$key]["if_key_arg"] == true && $desc_params[$key]["key_arg_value"] != $ds_params[$key].
	//
	public function get_from_node($root_node_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_get_from_node()
		if(!function_exists("ds_get_from_node"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_from_node()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		//get datasource parameters from root-node
		return ds_get_from_node($root_node_in, $this->nodename, $this->desc_params);
	}
	
	//*	method: add (or update) datasource into root-node.
	//
	//*	input:
	//			$root_node_in - link to a node object.	[OBJECT]
	//
	//*	output:
	//			number of added/updated datasource nodes.	[INTEGER]
	//
	//*	note:
	//
	public function add_into_node(&$root_node_in)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_add_into_node()
		if(!function_exists("ds_add_into_node"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_add_into_node()' not exists! [ds.php -> class ds]");
			}
			return 0;
		}
		
		return ds_add_into_node($root_node_in, $this->nodename, $this->desc_params, $this->params);
	}
	
	//*	method: remove datasource from root-node.
	//
	//*	input:
	//			$root_node_in - link to root-node object.	[OBJECT]
	//
	//*	output:
	//			number of removed datasource nodes.	[INTEGER]
	//
	//*	note:
	//
	public function remove_from_node(&$root_node_in)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_remove_from_node()
		if(!function_exists("ds_remove_from_node"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_remove_from_node()' not exists! [ds.php -> class ds]");
			}
			return 0;
		}
		
		return ds_remove_from_node($root_node_in, $this->nodename, $this->desc_params);
	}
	
	//*	method: get values of key arguments of datasource from XML-file.
	//
	//*	input:
	//			$file_in - a file name.	[STRING]
	//
	//*	output:
	//			list of values of key arguments.	[ARRAY]
	//
	//*	note:
	//
	//			for datasource parameters with option "if_key_arg" == true!
	//
	//
	//			structure of returned list:
	//
	//				[0][$key] = "value of key argument",
	//				...
	//				[N][$key] = "value of key argument".
	//
	public function get_key_args_from_file($file_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_get_key_args_from_file()
		if(!function_exists("ds_get_key_args_from_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_key_args_from_file()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		return ds_get_key_args_from_file($file_in, $this->nodename, $this->desc_params);
	}
	
	//*	method: get datasource parameters from XML-file.
	//
	//*	input:
	//			$file_in - file name.	[STRING]
	//
	//*	output:
	//			list of datasources (array of arrays of datasource parameters).	[ARRAY]
	//
	//*	note:
	//
	//			mismatched datasource parameters:
	//
	//				- if datasource parameters are not correct,
	//				- if $desc_params[$key]["if_key_arg"] == true && $desc_params[$key]["key_arg_value"] != $ds_params[$key].
	//
	public function get_from_file($file_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_get_from_file()
		if(!function_exists("ds_get_from_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_from_file()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		return ds_get_from_file($file_in, $this->nodename, $this->desc_params);
	}
	
	//*	method: add (or update) datasource into XML-file.
	//
	//*	input:
	//			$file_in			- file name;	[STRING]
	//			$root_node_name_in	- root-node name or NULL.	[STRING || NULL]
	//
	//*	output:
	//			number of added/updated datasources.	[INTEGER]
	//
	//*	note:
	//
	//			if $root_node_name_in == NULL, then will be used root-node from XML-file!
	//
	public function add_into_file($file_in = null, $root_node_name_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_add_into_file()
		if(!function_exists("ds_add_into_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_add_into_file()' not exists! [ds.php -> class ds]");
			}
			return 0;
		}
		
		return ds_add_into_file($file_in, $root_node_name_in, $this->nodename, $this->desc_params, $this->params);
	}
	
	//*	method: remove datasource from XML-file.
	//
	//*	input:
	//			$file_in - file name.	[STRING]
	//
	//*	output:
	//			number of removed datasources.	[INTEGER]
	//
	//*	note:
	//
	public function remove_from_file($file_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_remove_from_file()
		if(!function_exists("ds_remove_from_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_remove_from_file()' not exists! [ds.php -> class ds]");
			}
			return 0;
		}
		
		return ds_remove_from_file($file_in, $this->nodename, $this->desc_params);
	}
	
	//*	method: get object of database class.
	//
	//*	input:
	//			$connect_params_in - connection parameters (see library "db") or null.	[ARRAY || NULL]
	//
	//*	output:
	//			object of class by database type (dbMySQL ...) or NULL.	[OBJECT || NULL]
	//
	//*	note:
	//
	//			connection parameters:
	//
	//				-- required: "db_type", "hostname", "user", "database", "table".
	//
	//
	//			if the input argument $connect_params_in is NULL, then used $this->params!
	//
	public function get_db_object($connect_params_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_get_db_object()
		if(!function_exists("ds_get_db_object"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_db_object()' not exists! [ds.php -> class ds]");
			}
			return null;
		}
		
		return ((is_array($connect_params_in)) ? ds_get_db_object($connect_params_in) : ds_get_db_object($this->params));
	}
	
	//*	method: get values of key arguments of datasource from database.
	//
	//*	input:
	//			$connect_params_in - connection parameters (see library "db").	[ARRAY]
	//
	//*	output:
	//			list of values of key arguments.	[ARRAY]
	//
	//*	note:
	//
	//			connection parameters:
	//
	//				-- required: "db_type", "hostname", "user", "database", "table".
	//
	//
	//
	//			for datasource parameters with option "if_key_arg" == true!
	//
	//
	//			structure of returned list:
	//
	//				[0][$key] = "value of key argument",
	//				...
	//				[N][$key] = "value of key argument".
	//
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	public function get_key_args_from_db($connect_params_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_get_key_args_from_db()
		if(!function_exists("ds_get_key_args_from_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_key_args_from_db()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		return ((is_array($connect_params_in)) ? ds_get_key_args_from_db($connect_params_in, $this->desc_params) : ds_get_key_args_from_db($this->params, $this->desc_params));
	}
	
	//*	method: get datasource parameters from database.
	//
	//*	input:
	//			$connect_params_in - connection parameters (see library "db").	[ARRAY]
	//
	//*	output:
	//			list of datasources (array of arrays of datasource parameters).	[ARRAY]
	//
	//*	note:
	//
	//			connection parameters:
	//
	//				-- required: "db_type", "hostname", "user", "database", "table".
	//
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	public function get_from_db($connect_params_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_get_from_db()
		if(!function_exists("ds_get_from_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_from_db()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		return ((is_array($connect_params_in)) ? ds_get_from_db($connect_params_in, $this->desc_params) : ds_get_from_db($this->params, $this->desc_params));
	}
	
	//*	method: add (or update) datasource into a database.
	//
	//*	input:
	//			$connect_params_in - connection parameters (see library "db").	[ARRAY]
	//
	//*	output:
	//			number of added/updated datasources.	[INTEGER]
	//
	//*	note:
	//
	//			connection parameters:
	//
	//				-- required: "db_type", "hostname", "user", "database", "table".
	//
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	public function add_into_db($connect_params_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_add_into_db()
		if(!function_exists("ds_add_into_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_add_into_db()' not exists! [ds.php -> class ds]");
			}
			return 0;
		}
		
		return ((is_array($connect_params_in)) ? ds_add_into_db($connect_params_in, $this->desc_params, $this->params) : ds_add_into_db($this->params, $this->desc_params, $this->params));
	}
	
	//*	method: remove datasource from a database.
	//
	//*	input:
	//			$connect_params_in	- connection parameters (see library "db").	[ARRAY]
	//
	//*	output:
	//			number of removed datasources.	[INTEGER]
	//
	//*	note:
	//
	//			connection parameters:
	//
	//				-- required: "db_type", "hostname", "user", "database", "table".
	//
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	public function remove_from_db($connect_params_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//checking of function ds_remove_from_db()
		if(!function_exists("ds_remove_from_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_remove_from_db()' not exists! [ds.php -> class ds]");
			}
			return 0;
		}
		
		return ((is_array($connect_params_in)) ? ds_remove_from_db($connect_params_in, $this->desc_params) : ds_remove_from_db($this->params, $this->desc_params));
	}
	
	//*	method: get values of key arguments of datasource from datasource.
	//
	//*	input:
	//			$datasource_params_in	- datasource parameters (see library "db" and "ds_datasource.php");	[ARRAY]
	//			$target_id_in			- ID of the target repository.	[STRING || NULL]
	//
	//*	output:
	//			list of values of key arguments.	[ARRAY]
	//
	//*	note:
	//
	//			datasource parameters:
	//
	//				-- required:
	//					~ for type "xml": "file" or "files" with $target_id_in,
	//					~ for type "db":  "db_type", "hostname", "user", "database", "table" or "tables" with $target_id_in.
	//
	//
	//
	//			for datasource parameters with option "if_key_arg" == true!
	//
	//
	//			structure of returned list:
	//
	//				[0][$key] = "value of key argument",
	//				...
	//				[N][$key] = "value of key argument".
	//
	//
	//			If the input argument $datasource_params_in is NULL, then used $this->params!
	//
	public function get_key_args_from_ds($datasource_params_in = null, $target_id_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function functions_check_required()
		if(!function_exists("functions_check_required"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'functions_check_required()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		//* the array of required functions 	[ARRAY]
		$r_functions = array("ds_check_datasource_params",
							 "ds_get_key_args_from_file",
							 "ds_get_key_args_from_db"
							);
		
		
		//checking of required functions
		if(!functions_check_required($r_functions, "ds.php", "class ds"))
		{
			return array();
		}
		
		//* datasource parameters	[ARRAY]
		$datasource_params = ((is_array($datasource_params_in)) ? ds_check_datasource_params($datasource_params_in, $target_id_in) : ds_check_datasource_params($this->params, $target_id_in));
		
		
		//checking of datasource parameters
		if($datasource_params)
		{
			switch($connect_params["type"])
			{
				case "db":
				case "Db":
				case "DB":
					
					return ds_get_key_args_from_db($datasource_params, $this->desc_params);
					
				case "xml":
				case "Xml":
				case "XML":
					
					return ds_get_key_args_from_file($datasource_params["file"], $this->nodename, $this->desc_params);
			}
		}
		
		return array();
	}
	
	//*	method: get datasource parameters from datasource.
	//
	//*	input:
	//			$datasource_params_in	- datasource parameters (see library "db" and "ds_datasource.php");	[ARRAY]
	//			$target_id_in			- ID of the target repository.	[STRING || NULL]
	//
	//*	output:
	//			list of datasources (array of arrays of datasource parameters).	[ARRAY]
	//
	//*	note:
	//
	//			datasource parameters:
	//
	//				-- required:
	//					~ for type "xml": "file" or "files" with $target_id_in,
	//					~ for type "db":  "db_type", "hostname", "user", "database", "table" or "tables" with $target_id_in.
	//
	//
	//			If the input argument $datasource_params_in is NULL, then used $this->params!
	//
	public function get_from_ds($datasource_params_in = null, $target_id_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function functions_check_required()
		if(!function_exists("functions_check_required"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'functions_check_required()' not exists! [ds.php -> class ds]");
			}
			return array();
		}
		
		//* the array of required functions 	[ARRAY]
		$r_functions = array("ds_check_datasource_params",
							 "ds_get_from_file",
							 "ds_get_from_db"
							);
		
		
		//checking of required functions
		if(!functions_check_required($r_functions, "ds.php", "class ds"))
		{
			return array();
		}
		
		//* datasource parameters	[ARRAY]
		$datasource_params = ((is_array($datasource_params_in)) ? ds_check_datasource_params($datasource_params_in, $target_id_in) : ds_check_datasource_params($this->params, $target_id_in));
		
		
		//checking of datasource parameters
		if($datasource_params)
		{
			switch($datasource_params["type"])
			{
				case "db":
				case "Db":
				case "DB":
					
					return ds_get_from_db($datasource_params, $this->desc_params);
					
					break;
					
				case "xml":
				case "Xml":
				case "XML":
					
					return ds_get_from_file($datasource_params["file"], $this->nodename, $this->desc_params);
					
					break;
			}
		}
		
		return array();
	}
	
	//*	method: add (or update) datasource into datasource.
	//
	//*	input:
	//			$datasource_params_in	- datasource parameters (see library "db" and "ds_datasource.php");	[ARRAY]
	//			$target_id_in			- ID of the target repository;	[STRING || NULL]
	//			$root_node_name_in		- a root-node name (for connection type "xml") or NULL.	[STRING || NULL]
	//
	//*	output:
	//			number of added/updated datasources.	[INTEGER]
	//
	//*	note:
	//
	//			if $datasource_params_in["type"] == "xml" and $root_node_name_in == NULL, then will be used root-node from XML-file!
	//
	//			datasource parameters:
	//
	//				-- required:
	//					~ for type "xml": "file" or "files" with $target_id_in,
	//					~ for type "db":  "db_type", "hostname", "user", "database", "table" or "tables" with $target_id_in.
	//
	//
	//			If the input argument $datasource_params_in is NULL, then used $this->params!
	//
	public function add_into_ds($datasource_params_in = null, $target_id_in = null, $root_node_name_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function functions_check_required()
		if(!function_exists("functions_check_required"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'functions_check_required()' not exists! [ds.php -> class ds]");
			}
			return 0;
		}
		
		//* the array of required functions 	[ARRAY]
		$r_functions = array("ds_check_datasource_params",
							 "ds_add_into_file",
							 "ds_add_into_db"
							);
		
		
		//checking of required functions
		if(!functions_check_required($r_functions, "ds.php", "class ds"))
		{
			return 0;
		}
		
		//* datasource parameters	[ARRAY]
		$datasource_params = ((is_array($datasource_params_in)) ? ds_check_datasource_params($datasource_params_in, $target_id_in) : ds_check_datasource_params($this->params, $target_id_in));
		
		
		//checking of datasource parameters
		if($datasource_params)
		{
			switch($datasource_params["type"])
			{
				case "db":
				case "Db":
				case "DB":
					
					return ds_add_into_db($datasource_params, $this->desc_params, $this->params);
					
				case "xml":
				case "Xml":
				case "XML":
					
					return ds_add_into_file($datasource_params["file"], $root_node_name_in, $this->nodename, $this->desc_params, $this->params);
			}
		}
		
		return 0;
	}
	
	//*	method: remove datasource from datasource.
	//
	//*	input:
	//			$datasource_params_in	- datasource parameters (see library "db" and "ds_datasource.php");	[ARRAY]
	//			$target_id_in			- ID of the target repository.	[STRING || NULL]
	//
	//*	output:
	//			number of removed datasources.	[INTEGER]
	//
	//*	note:
	//
	//			datasource parameters:
	//
	//				-- required:
	//					~ for type "xml": "file" or "files" with $target_id_in,
	//					~ for type "db":  "db_type", "hostname", "user", "database", "table" or "tables" with $target_id_in.
	//
	//
	//			If the input argument $datasource_params_in is NULL, then used $this->params!
	//
	public function remove_from_ds($datasource_params_in = null, $target_id_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function functions_check_required()
		if(!function_exists("functions_check_required"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'functions_check_required()' not exists! [ds.php -> class ds]");
			}
			return 0;
		}
		
		//* the array of required functions 	[ARRAY]
		$r_functions = array("ds_check_datasource_params",
							 "ds_remove_from_file",
							 "ds_remove_from_db"
							);
		
		
		//checking of required functions
		if(!functions_check_required($r_functions, "ds.php", "class ds"))
		{
			return 0;
		}
		
		//* datasource parameters	[ARRAY]
		$datasource_params = ((is_array($datasource_params_in)) ? ds_check_datasource_params($datasource_params_in, $target_id_in) : ds_check_datasource_params($this->params, $target_id_in));
		
		
		//checking of datasource parameters
		if($datasource_params)
		{
			switch($datasource_params["type"])
			{
				case "db":
				case "Db":
				case "DB":
					
					return ds_remove_from_db($datasource_params, $this->desc_params);
					
				case "xml":
				case "Xml":
				case "XML":
					
					return ds_remove_from_file($datasource_params["file"], $this->nodename, $this->desc_params);
			}
		}
		
		return 0;
	}
	
	//*	method: extending of datasource parameters.
	//
	//*	input:
	//			$ext_in - extended data.	[ARRAY]
	//
	//*	output:
	//			number of added/updated parameters.	[INTEGER]
	//
	//*	note:
	//
	public function extend_params($ext_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function ds_extend_params()
		if(!function_exists("ds_extend_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_extend_params()' not exists! [ds.php -> class ds]");
			}
			return 0;
		}
		
		return ds_extend_params($ext_in, $this->desc_ext_params, $this->params);
	}
	
	
	//** Constructor and Destructor
	
	//*	constructor
	//
	//*	input: none.
	//
	//*	note:	
	//
	function __construct()
	{
		//init options by default
		$this->nodename			= null;
		$this->params			= array();
		$this->desc_params		= array();
		$this->desc_ext_params	= array();
	}
	
	//*	destructor
	//
	//*	note:	
	//
	function __destruct()
	{
		unset($this->nodename);
		unset($this->params);
		unset($this->desc_params);
		unset($this->desc_ext_params);
	}
}


?>
