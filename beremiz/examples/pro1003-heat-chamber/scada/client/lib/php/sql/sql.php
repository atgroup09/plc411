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


/*   Library: SQL.
*
*    Copyright (C) 2010-2012  ATgroup09 (atgroup09@gmail.com)
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
*			+ regexp/regexp.php:
*				~ search_sub_string(),
*				~ replace_sub_string().
*
*			+ types/types.php:
*				~ types_data_formatting().
*
*			+ types/string.php:
*				~ string_processing().
*/


/*	Global variables: none.
*
*
*	Functions:
*
*		*** normalize a value by the type ***
*		sql_normalize_value($value_in = null, $type_in = "string")
*
*		*** get a normalized associative array of table field parameters ***
*		sql_normalize_field_params_array($field_in = null)
*
*		*** get a normalized comparision operator ***
*		sql_normalize_compare($compare_in = '=')
*
*		*** get a normalized comparision operator as an alternate of the operator "BETWEEN" ***
*		sql_normalize_between_alt($between_alt_in = '=')
*
*		*** get a normalized associative array of table field parameters for the operator "where" ***
*		sql_normalize_where_params_array($where_in = null)
*
*		*** get a field name ***
*		sql_get_field_name($field_name_in = null, $table_alias_in = null)
*
*		*** get a field value ***
*		sql_get_field_value($field_in = null, $values_in = null)
*
*		*** get a string of the compare "BETWEEN" from values ***
*		sql_compare_between($field_in = null, $between_alt_in = '=', $values_in = null)
*
*		*** get a string for a comparision operator from values ***
*		sql_compare($where_in = null, $values_in = null)
*
*		*** get a string for the operator "WHERE" from values ***
*		sql_where($where_in = null, $values_in = null)
*
*		*** get a query for the operation "SELECT" ***
*		sql_select($tables_in = null, $fields_in = null, $where_in = null, $values_in = null)
*
*		*** get a query for the operation "INSERT" ***
*		sql_insert($table_name_in = null, $fields_in = null, $values_in = null)
*
*		*** get a query for the operation "UPDATE" ***
*		sql_update($table_name_in = null, $fields_in = null, $where_in = null, $values_in = null)
*
*		*** get a query for the operation "DELETE" ***
*		sql_delete($table_name_in = null, $where_in = null, $values_in = null, $using_in = null)
*
*		*** get a string the operator "LIMIT" from values ***
*		sql_limit($starting_row_in = null, $limit_rows_in = null)
*
*
*	The structure of the associative array of table field parameters:
*
*		* default:
*
*		- ["for_select"]		- if true, then the field used in operation "SELECT" (true by default);	[BOOLEAN]
*		- ["for_insert"]		- if true, then the field used in operation "INSERT" (true by default);	[BOOLEAN]
*		- ["for_update"]		- if true, then the field used in operation "UPDATE" (true by default);	[BOOLEAN]
*
*		* for SELECT:
*
*		- ["field"]				- (*) a field name of a database table;	[STRING]
*		- ["alt_field"]			- alternate field name of a database table;	[STRING || NULL]
*		- ["field_alias"]		- a field alias;	[STRING || NULL]
*		- ["table_alias"]		- a table alias.	[STRING || NULL]
*
*
*		* for INSERT, UPDATE, DELETE:
*
*		- ["key"]				- (*) a key/index name of the array $array_of_values;	[STRING]
*		- ["field"]				- (*) a field name of a database table;	[STRING]
*		- ["alt_field"]			- alternate field name of a database table	[STRING || NULL]
*								  * this option is required if option "field" is NULL or not used!
*		- ["table_alias"]		- a table alias;	[STRING || NULL]
*		- ["type"]				- a data type:	[STRING]
*									-- "int",
*									-- "integer",
*									-- "float",
*									-- "str",
*									-- "string" (by default),
*									-- "unformatted",
*									-- "date" (supported formats: YYYY-MM-DD, YYYY-MM-D, YYYY-M-D - with or witjout a frame of single quotes),
*									-- "time" (supported formats: HH:MM:SS, HH:MM, H:M:S- with or witjout a frame of single quotes),
*									-- "datetime" (supported formats: YYYY-MM-DD HH:MM:SS ...);
*		- ["default"]			- a value by default (if a value of $array_of_values["key"] is not exists)	[STRING || NUMBER || NULL]
*									* if a value by default is not used and a value of the array $array_of_values["key"] is not exists, then will be used NULL!
*
*		- ["use_forced_value"]	- true if use option "forced_value", otherwise - false (by default);	[BOOLEAN]
*		- ["forced_value"]		- use this value instead of $array_of_values["{key}"] (NULL by default) (FORCED!);	[STRING || NUMBER || NULL]
*
*		- ["required"]			- true if value of the field is required (if NULL, then error!), otherwise - false (by default)	[BOOLEAN]
*									* ignored for "forced value"!
*
*		- ["empty_is_null"]		- true if use empty value as NULL (by default), otherwise - false	[BOOLEAN]
*									* empty value is "" (string type)!
*
*			(*) - is required parameters!
*
*
*	The structure of the associative array of table field parameters for the operator "where":
*
*		- ["key"]				- (*) a key/index name of the array $array_of_values (regexp string);	[STRING];
*		- ["field"]				- (*) a field name of a database table;		[STRING]
*		- ["alt_field"]			- alternate field name of a database table	[STRING || NULL]
*								  * this option is required if option "field" is NULL or not used!
*		- ["table_alias"]		- a table alias;	[STRING || NULL]
*		- ["type"]				- a data type:	[STRING]
*									-- "int",
*									-- "integer",
*									-- "float",
*									-- "str",
*									-- "string" (by default),
*									-- "unformatted";
*		- ["compare"]			- a comparison operator:	[STRING]
*									-- '=' (by default),
*									-- "!=",
*									-- '<',
*									-- '>',
*									-- "<=",
*									-- ">=",
*									-- "between" or "BETWEEN"
*										* the array $array_of_values must have keys: "{$key}_min" and/or "{$key}_max")!
*									-- "is null" or "IS NULL",
*									-- "is not null" or "IS NOT NULL",
*									-- "regexp";
*		- ["between_alt"]		- an alternate comparision operator ('=' by default)	[STRING || NULL]
*									* used, when if ["compare"] = "between" and if $array_of_values have only one key of "{$re_key}_min", "{$re_key}_max";
*		- ["not"]				- true (for "NOT field") or false (by default);	[BOOLEAN || NULL]
*
*		- ["use_forced_value"]	- true if use option "forced_value", otherwise - false (by default);	[BOOLEAN]
*		- ["forced_value"]		- use this value instead of $array_of_values["{key}"] (NULL by default) (FORCED!);	[STRING || NUMBER || NULL]
*
*		- ["empty_is_null"]		- true if use empty value as NULL (by default), otherwise - false	[BOOLEAN]
*									* empty value is "" (string type)!
*
*			(*) - is required parameters!
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function: normalize a value by the type.
*	Input:	
*			$value_in		- a value;	[STRING || INTEGER || FLOAT || NULL]
*			$type_in		- the type:	[STRING]
*								-- "int", "integer",
*								-- "float",
*								-- "string" (by default);
*								-- "unformatted",
*								-- "date",
*								-- "time",
*								-- "datetime";
*			$emptyIsNULL_in	- true if use empty value as NULL (by default), otherwise - false.	[BOOLEAN]
*	Output:
*			a normalized value.	[STRING || NULL]
*	Note:
*			normalization of a value by the type "float":
*				- '100,99' -> 100.99,
*				- 100.99   -> 100.99.
*
*			normalization of a value by the type "string":
*				- shielding special characters,
*				- wrapping in single quotes.
*/
function sql_normalize_value($value_in = null, $type_in = "string", $emptyIsNULL_in = true)
{
	global $FL_DEBUG;
	
	if(!function_exists("types_data_formatting"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'types_data_formatting()' not exists! [sql.php -> sql_normalize_value()]");
		return null;
	}
	
	if(!function_exists("string_processing"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'string_processing()' not exists! [sql.php -> sql_normalize_value()]");
		return null;
	}
	
	//* type of value	[STRING]
	$vtype = gettype($value_in);
	
	$emptyIsNULL = ((is_bool($emptyIsNULL_in)) ? $emptyIsNULL_in : true);
	
	switch($vtype)
	{
		case "null":
		case "Null":
		case "NULL":
		case "object":
		case "Object":
		case "OBJECT":
		case "array":
		case "Array":
		case "ARRAY":
		case "resource":
		case "Resource":
		case "RESOURCE":
		case "unknown type":
			
			return (($emptyIsNULL) ? "NULL" : null);
	}
	
	//* a data type	[STRING]
	$type  = "string";
	
	//* value	[STRING || NUMBER || NULL]
	$value = null;
	
	//* a buffer	[STRING || NUMBER || NULL]
	$buff  = null;
	
	$valueIsEmpty = false;
	
	if(is_string($value_in))
	{
		if($value_in == "") $valueIsEmpty = true;
	}
	
	if(is_string($type_in) && !$valueIsEmpty)
	{
		switch($type_in)
		{
			case "int":
			case "integer":
			case "float":
				
				$type  = $type_in;
				$value = ((is_string($value_in)) ? string_processing($value_in, "EQ_NO_BSQ|EQ_NO_BDQ") : $value_in);
				
				break;
				
			case "str":
			case "string":
				
				$type  = $type_in;
				$value = $value_in;
				
				break;
				
			case "date":
			case "time":
			case "datetime":
				
				$type = $type_in;
				$value = ((is_string($value_in)) ? string_processing($value_in, "EQ_NO_BSQ|EQ_NO_BDQ") : null);
				
				break;
				
			case "unformatted":
				
				if(is_string($value_in))
				{
					return $value_in;
				}
				
				break;
		}
	}
	
	//Formatting the value
	$buff = types_data_formatting($value, $type, null);
	
	if($type == "string" || $type == "date" || $type == "time" || $type == "datetime")
	{
		$buff = ((!empty($buff)) ? string_processing($buff, "EQ_NO_BSQ|EQ_SHIELD_CHARS|EQ_ADD_BSQ") : null);
	}
	
	$vtype = gettype($buff);
	
	switch($vtype)
	{
		case "null":
		case "Null":
		case "NULL":
			
			return (($emptyIsNULL) ? "NULL" : null);
	}
	
	return (($type == "string" || $type == "date" || $type == "time" || $type == "datetime") ? $buff : (string)$buff);
}


/*	Function: get a normalized associative array of table field parameters.
*	Input:	
*			$field_in - an associative array of table field parameters.	[ARRAY]
*	Output:
*			a normalized associative array of table field parameters or NULL.	[ARRAY || NULL]
*	Note:
*			If the array $field_in has no elements with keys: "key", "field" (or "alt_field"), then returns NULL!
*/
function sql_normalize_field_params_array($field_in = null)
{
	if(!is_array($field_in)) return null;
	
	//* a normalized associative array of table field parameters	[ARRAY]
	$field = array("key" => null, "field" => null, "alt_field" => null, "type" => "string", "table_alias" => null, "default" => null, "use_forced_value" => false, "forced_value" => null, "required" => false, "empty_is_null" => true);
	
	if(!empty($field_in["key"]))
	{
		if(is_string($field_in["key"])) $field["key"] = $field_in["key"];
	}
	
	if(!empty($field_in["field"]))
	{
		if(is_string($field_in["field"])) $field["field"] = $field_in["field"];
	}
	
	if(!empty($field_in["alt_field"]))
	{
		if(is_string($field_in["alt_field"])) $field["alt_field"] = $field_in["alt_field"];
	}
	
	if(!(!empty($field["key"]) && (!empty($field["field"]) || !empty($field["alt_field"]))))
	{
		return null;
	}
	
	if(isset($field_in["type"]))
	{
		if(is_string($field_in["type"]))
		{
			switch($field_in["type"])
			{
				case "int":
				case "integer":
				case "float":
				case "unformatted":
				case "date":
				case "time":
				case "datetime":
					
					$field["type"] = $field_in["type"];
					
					break;
			}
		}
	}
	
	if(isset($field_in["table_alias"]))
	{
		if(is_string($field_in["table_alias"]))
		{
			if(!empty($field_in["table_alias"])) $field["table_alias"] = $field_in["table_alias"];
		}
	}
	
	if(isset($field_in["default"]))
	{
		if(is_string($field_in["default"]) || is_numeric($field_in["default"])) $field["default"] = $field_in["default"];
	}
	
	if(isset($field_in["use_forced_value"]))
	{
		if(is_bool($field_in["use_forced_value"])) $field["use_forced_value"] = $field_in["use_forced_value"];
	}
	
	if(isset($field_in["forced_value"]))
	{
		if(is_string($field_in["forced_value"]) || is_numeric($field_in["forced_value"])) $field["forced_value"] = $field_in["forced_value"];
	}
	
	if(isset($field_in["required"]))
	{
		if(is_bool($field_in["required"])) $field["required"] = $field_in["required"];
	}
	
	if(isset($field_in["empty_is_null"]))
	{
		if(is_bool($field_in["empty_is_null"])) $field["empty_is_null"] = $field_in["empty_is_null"];
	}
	
	return $field;
}


/*	Function: get a normalized comparision operator.
*	Input:	
*			$compare_in - a comparison operator.	[STRING]
*	Output:
*			a normalized comparision operator.	[STRING]
*	Note:
*/
function sql_normalize_compare($compare_in = '=')
{
	if(!empty($compare_in))
	{
		if(is_string($compare_in))
		{
			switch($compare_in)
			{
				case '=':
				case "!=":
				case '>':
				case '<':
				case ">=":
				case "<=":
				case "between":
				case "BETWEEN":
				case "is null":
				case "IS NULL":
				case "is not null":
				case "IS NOT NULL":
					
					return $compare_in;
					
				case "regexp":
				case "REGEXP":
					
					return "REGEXP";
			}
		}
	}
	
	return '=';
}


/*	Function: get a normalized comparision operator as an alternate of the operator "BETWEEN".
*	Input:	
*			$between_alt_in - an alternate comparison operator for the operator "BETWEEN".	[STRING]
*	Output:
*			a normalized comparision operator.	[STRING]
*	Note:
*/
function sql_normalize_between_alt($between_alt_in = '=')
{
	if(!empty($between_alt_in))
	{
		if(is_string($between_alt_in))
		{
			switch($between_alt_in)
			{
				case '=':
				case "!=":
				case '>':
				case '<':
				case ">=":
				case "<=":
				case "is null":
				case "IS NULL":
				case "is not null":
				case "IS NOT NULL":
					
					return $between_alt_in;
				
				case "regexp":
				case "REGEXP":
					
					return "REGEXP";
			}
		}
	}
	
	return '=';
}


/*	Function: get a normalized associative array of table field parameters for the operator "where".
*	Input:	
*			$where_in - an associative array of table field parameters for the operator "where".	[ARRAY]
*	Output:
*			a normalized associative array of table field parameters for the operator "where" or NULL.	[ARRAY || NULL]
*	Note:
*			If the array $where_in has no elements with keys: "key", "field" (or "alt_field"), then returns NULL!
*/
function sql_normalize_where_params_array($where_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("sql_normalize_compare"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_normalize_compare()' not exists! [sql.php -> sql_normalize_where_params_array()]");
		return null;
	}
	
	if(!function_exists("sql_normalize_between_alt"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_normalize_between_alt()' not exists! [sql.php -> sql_normalize_where_params_array()]");
		return null;
	}
	
	if(!is_array($where_in)) return null;
	
	//* a normalized associative array of table field parameters	[ARRAY]
	$where = array("key" => null, "field" => null, "alt_field" => null, "type" => "string", "table_alias" => null, "compare" => '=', "between_alt" => '=', "not" => false, "use_forced_value" => false, "forced_value" => null, "required" => false, "empty_is_null" => true);
	
	if(!empty($where_in["key"]))
	{
		if(is_string($where_in["key"])) $where["key"] = $where_in["key"];
	}
	
	if(!empty($where_in["field"]))
	{
		if(is_string($where_in["field"])) $where["field"] = $where_in["field"];
	}
	
	if(!empty($where_in["alt_field"]))
	{
		if(is_string($where_in["alt_field"])) $where["alt_field"] = $where_in["alt_field"];
	}
	
	if(!(!empty($where["key"]) && (!empty($where["field"]) || !empty($where["alt_field"])))) return null;
	
	if(isset($where_in["type"]))
	{
		if(is_string($where_in["type"]))
		{
			switch($where_in["type"])
			{
				case "int":
				case "integer":
				case "float":
				case "unformatted":
				case "date":
				case "time":
				case "datetime":
					
					$where["type"] = $where_in["type"];
					
					break;
			}
		}
	}
	
	if(isset($where_in["table_alias"]))
	{
		if(is_string($where_in["table_alias"])) $where["table_alias"] = $where_in["table_alias"];
	}
	
	if(isset($where_in["compare"]))
	{
		$where["compare"] = sql_normalize_compare($where_in["compare"]);
	}
	
	if(isset($where_in["between_alt"]))
	{
		$where["between_alt"] = sql_normalize_between_alt($where_in["between_alt"]);
	}
	
	if(isset($where_in["not"]))
	{
		if(is_bool($where_in["not"])) $where["not"] = $where_in["not"];
	}
	
	if(isset($where_in["use_forced_value"]))
	{
		if(is_bool($where_in["use_forced_value"])) $where["use_forced_value"] = $where_in["use_forced_value"];
	}
	
	if(isset($where_in["forced_value"]))
	{
		if(is_string($where_in["forced_value"]) || is_numeric($where_in["forced_value"])) $where["forced_value"] = $where_in["forced_value"];
	}
	
	if(isset($where_in["empty_is_null"]))
	{
		if(is_bool($where_in["empty_is_null"])) $where["empty_is_null"] = $where_in["empty_is_null"];
	}
	
	return $where;
}


/*	Function: get a field name.
*	Input:	
*			$field_name_in	- a field name;		[STRING]
*			$table_alias_in	- a table alias or NULL.	[STRING || NULL]
*	Output:
*			a field name or NULL.	[STRING || NULL]
*	Note:
*
*			Example 1:
*
*				$result = sql_get_field_name("date", null);
*				//result: "`date`"
*
*			Example 1:
*
*				$result = sql_compare_is_null("date", "my");
*				//result: "`my`.`date`"
*
*			Example 3:
*
*				$result = sql_compare_is_null(null, null);
*				//result: null
*/
function sql_get_field_name($field_name_in = null, $table_alias_in = null)
{
	if(empty($field_name_in)) return null;
	
	if(!is_string($field_name_in)) return null;
	
	if(!empty($table_alias_in))
	{
		if(is_string($table_alias_in)) return "`{$table_alias_in}`.`{$field_name_in}`";
	}
	
	return "`{$field_name_in}`";
}


/*	Function: get a field value.
*	Input:	
*			$field_in	- an associative array of table field parameters;	[ARRAY]
*			$values_in	- an array of field values.	[ARRAY]
*	Output:
*			a field value.	[STRING || NULL]
*	Note:
*			Returns: $values_in[$field_in["forced_value"]] (FORCED!) or $values_in[$field_in["key"]] or $values_in[$field_in["default"]] or NULL.
*
*			The input array $values_in can be $_REQUEST!
*/
function sql_get_field_value($field_in = null, $values_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("sql_normalize_value"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_normalize_value()' not exists! [sql.php -> sql_get_field_value()]");
		return null;
	}
	
	if(!function_exists("sql_normalize_field_params_array"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_normalize_field_params_array()' not exists! [sql.php -> sql_get_field_value()]");
		return null;
	}
	
	//* a normalized associative array of table field parameters	[ARRAY || NULL]
	$field = sql_normalize_field_params_array($field_in);
	
	if(!$field) return null;
	
	//* a key name	[STRING || NULL]
	$key = $field["key"];
	
	//* a field value	[STRING || NUMBER || NULL]
	$value = $field["default"];
	
	if($field["use_forced_value"])
	{
		$value = $field["forced_value"];
	}
	else
	{
		if(is_array($values_in))
		{
			if(isset($values_in[$key]))
			{
				if(is_string($values_in[$key]) || is_numeric($values_in[$key]))
				{
					$value = $values_in[$key];
				}
			}
		}
		
		//* the value type	[STRING]
		$vtype = gettype($value);
		
		if($field["required"] && ($vtype == "null" || $vtype == "Null" || $vtype == "NULL"))
		{
			return null;
		}
	}
	
	return sql_normalize_value($value, $field["type"], $field["empty_is_null"]);
}


/*	Function: get a string of the compare "BETWEEN" from values.
*	Input:	
*			$field_in		- an associative array of table field parameters;	[ARRAY]
*			$between_alt_in	- an alternate comparision operator:	[STRING || NULL]
*								-- '=' (by default),
*								-- "!=",
*								-- '<',
*								-- '>',
*								-- "<=",
*								-- ">=",
*								-- "is null" or "IS NULL",
*								-- "is not null" or "IS NOT NULL";
*			$values_in		- an associative array of field values.	[ARRAY]
*	Output:
*			a string of the compare "BETWEEN" or NULL.	[STRING || NULL]
*	Note:
*			The array $values_in must have keys: "{$field_in["key"]}_min" and/or "{$field_in["key"]}_max")!
*
*			The input array $values_in can be $_REQUEST!
*
*
*			Example 1:
*
*				$field_in		= array("key" => "date", "type" => "string", "field" => "date", "table_alias" => "my");
*				$between_alt_in	= '=';
*				$values_in		= array("date" => "2011-10-10");
*
*
*				$result = sql_compare_between($key_in, $type_in, $values_in);
*				//result: null
*
*
*			Example 2:
*
*				$field_in		= array("key" => "date", "type" => "string", "field" => "date", "table_alias" => "my");
*				$between_alt_in	= '=';
*				$values_in		= array("date" => "2011-10-10", "date_max" => "2011-10-12");
*
*				$result = sql_compare_between($key_in, $type_in, $values_in);
*				//result: "my.date = '2011-10-12'"
*
*
*			Example 3:
*
*				$field_in		= array("key" => "number", "type" => "int", "field" => "id");
*				$between_alt_in	= '=';
*				$values_in		= array("number1" => 1, "number_min" => 10.10, "number_max" => 20);
*
*
*				$result = sql_compare_between($key_in, $type_in, $values_in);
*				//result: "(id BETWEEN 10 AND 20)"
*/
function sql_compare_between($field_in = null, $between_alt_in = '=', $values_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("replace_sub_string"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'search_sub_string()' not exists! [sql.php -> sql_compare_between()]");
		return null;
	}
	
	if(!function_exists("sql_normalize_field_params_array"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_normalize_field_params_array()' not exists! [sql.php -> sql_compare_between()]");
		return null;
	}
	
	if(!function_exists("sql_normalize_between_alt"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_normalize_between_alt()' not exists! [sql.php -> sql_compare_between()]");
		return null;
	}
	
	if(!function_exists("sql_get_field_name"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_get_field_name()' not exists! [sql.php -> sql_compare_between()]");
		return null;
	}
	
	if(!function_exists("sql_get_field_value"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_get_field_value()' not exists! [sql.php -> sql_compare_between()]");
		return null;
	}
	
	//* a normalized associative array of table field parameters	[ARRAY || NULL]
	$field = sql_normalize_field_params_array($field_in);
	
	if(!$field) return null;
	if(!is_array($values_in)) return null;
	
	//* a key name	[STRING]
	$key = replace_sub_string("_min$|_max$", '', $field["key"], -1);
	
	//* the array of key names	[ARRAY]
	$array_keys = array("{$key}_min", "{$key}_max");
	
	//* values	[ARRAY]
	$array_values = array();
	
	//* a buffer	[STRING || NULL]
	$buff = null;
	
	for($i=0; $i<count($array_keys); $i++)
	{
		if(!isset($values_in[$array_keys[$i]])) continue;
		
		$field["key"] = $array_keys[$i];
		$buff = sql_get_field_value($field, $values_in);
		
		if(is_string($buff))
		{
			if(!empty($buff))
			{
				if($i == 0)
				{
					$array_values["min"] = $buff;
				}
				else
				{
					$array_values["max"] = $buff;
				}
			}
		}
	}
	
	if(isset($array_values["min"]) || isset($array_values["max"]))
	{
		//* a field name	[STRING]
		$field_name = ((!empty($field["field"])) ? sql_get_field_name($field["field"], $field["table_alias"]) : $field["alt_field"]);
		
		if(isset($array_values["min"]) && isset($array_values["max"]))
		{
			return "({$field_name} BETWEEN ".($array_values["min"])." AND ".($array_values["max"]).")";
		}
		else
		{
			//* alternate BETWEEN	[STRING]
			$between_alt = sql_normalize_between_alt($between_alt_in);
			
			return ((isset($array_values["min"])) ? "{$field_name} {$between_alt} ".($array_values["min"]) : "{$field_name} {$between_alt} ".($array_values["max"]));
		}
	}
	
	return null;
}


/*	Function: get a string for a comparision operator from values.
*	Input:	
*			$where_in	- an associative array of table field parameters for the operator "where";	[ARRAY]
*			$values_in	- an associative array of field values.	[ARRAY]
*	Output:
*			a string for a comparision operator from values ([NOT] [table alias.] a field name + a comparision operator + a field value) or NULL.	[STRING || NULL]
*	Note:
*			The input array $values_in can be $_REQUEST!
*
*			Example 1:
*
*				$where_in	= array("key"         => "^date[0-9]*",
*									"field"       => "date",
*									"table_alias" => "my",
*									"type"        => "string",
*									"compare"     => "between",
*									"between_alt" => '=',
*									"not"         => false
*									);
*
*				$values_in	= array("date_min" => "2012-09-02", "date_max" => "2012-10-02");
*
*
*				$result = sql_compare($where_in, $values_in);
*				//result: "(my.date BETWEEN '2012-09-02' AND '2012-10-02')"
*
*
*			Example 2:
*
*				$where_in	= array("key"         => "^date[0-9]*",
*									"field"       => "date",
*									"table_alias" => "my",
*									"type"        => "string",
*									"compare"     => "between",
*									"between_alt" => '=',
*									"not"         => false
*									);
*
*				$values_in	= array("date_min" => "2012-09-02", "date_max" => "2012-10-02", "date2_min" => "2012-08-02", "date2_max" => "2012-09-02", "date3_max" => "2012-07-02");
*
*
*				$result = sql_compare($where_in, $values_in);
*				//result: "((my.date BETWEEN '2012-09-02' AND '2012-10-02') OR (my.date BETWEEN '2012-08-02' AND '2012-09-02') OR my.date = '2012-07-02')"
*
*
*			Example 3:
*
*				$where_in	= array("key"         => "^id[0-9]*$",
*									"field"       => "lot_id",
*									"type"        => "int",
*									"compare"     => '='
*									);
*
*				$values_in	= array("id" => 10, "id1" => 1, "id2" => 2, "idN" => 100);
*
*
*				$result = sql_compare($where_in, $values_in);
*				//result: "(lot_id = 10 OR lot_id = 1 OR lot_id = 2)"
*
*
*			Example 4:
*
*				$where_in	= array("key"         		=> "^id$",
*									"field"       		=> "lot_id",
*									"compare"     		=> '=',
*									"use_forced_value"	=> true,
*									"forced_value"		=> 200
*									);
*
*				$values_in	= array("id" => 10, "id1" => 1, "id2" => 2, "idN" => 100);
*
*
*				$result = sql_compare($where_in, $values_in);
*				//result: "lot_id = 200"
*/
function sql_compare($where_in = null, $values_in = null)
{
	$returned_result = null;
	
	global $FL_DEBUG;
	
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'search_sub_string()' not exists! [sql.php -> sql_compare()]");
		return $returned_result;
	}
	
	if(!function_exists("replace_sub_string"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'replace_sub_string()' not exists! [sql.php -> sql_compare()]");
		return $returned_result;
	}
	
	if(!function_exists("sql_normalize_value"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_normalize_value()' not exists! [sql.php -> sql_compare()]");
		return $returned_result;
	}
	
	if(!function_exists("sql_normalize_where_params_array"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_normalize_where_params_array()' not exists! [sql.php -> sql_compare()]");
		return $returned_result;
	}
	
	if(!function_exists("sql_get_field_name"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_get_field_name()' not exists! [sql.php -> sql_compare()]");
		return $returned_result;
	}
	
	if(!function_exists("sql_compare_between"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_compare_between()' not exists! [sql.php -> sql_compare()]");
		return $returned_result;
	}
	
	//* a normalized an associative array of table field parameters for the operator "where"	[ARRAY || NULL]
	$where = sql_normalize_where_params_array($where_in);
	
	if(!$where) return $returned_result;
	
	//* a buffer	[STRING || NULL]
	$buff = $where["key"];
	
	//* the array of values	[ARRAY]
	$values = (($where["use_forced_value"]) ? array("{$buff}" => $where["forced_value"]) : $values_in);
	
	if(!is_array($values)) return $returned_result;
	
	//* the array of field parameters	[ARRAY]
	$field = array("key" => null, "field" => $where["field"], "alt_field" => $where["alt_field"], "type" => $where["type"], "table_alias" => $where["table_alias"], "use_forced_value" => $where["use_forced_value"], "forced_value" => $where["forced_value"], "empty_is_null" => $where["empty_is_null"]);
	
	//* a last key	[STRING]
	$last_key = '';
	
	//* a normalized value	[STRING || NULL]
	$nv = null;
	
	//* a number of additional parts (comparision operators)	[INTEGER]
	$p = 0;
	
	foreach($values as $k=>$v)
	{
		//init variables by default
		$buff = null;
		$field["key"] = $k;
		
		if($where["compare"] == "is null" || $where["compare"] == "IS NULL" || $where["compare"] == "is not null" || $where["compare"] == "IS NOT NULL")
		{
			//** if the comparision operator is "IS NULL" or "IS NOT NULL" 
			
			if(empty($last_key))
			{
				$buff = ((!empty($field["field"])) ? sql_get_field_name($field["field"], $field["table_alias"]) : $field["alt_field"]);
				
				if($buff)
				{
					if($where["compare"] == "is null" || $where["compare"] == "IS NULL")
					{
						$buff.= " IS NULL";
					}
					else
					{
						$buff.= " IS NOT NULL";
					}
					
					$last_key = $k;
				}
			}
		}
		else
		{
			//check the key of the values array by the mask
			if(!search_sub_string($where["key"], $k, $array_matches, null, null))
			{
				continue;
			}
			
			if($where["compare"] == "between" || $where["compare"] == "Between" || $where["compare"] == "BETWEEN")
			{
				//** if the comparision operator is "BETWEEN"
				
				//check a key of the last key name
				if(!search_sub_string("^{$last_key}_min$|^{$last_key}_max$", $k, $array_matches, null, null))
				{
					//get the compare "BETWEEN"
					$buff = sql_compare_between($field, '=', $values);
					
					if($buff)
					{
						$last_key = replace_sub_string("_min$|_max$", '', $k, -1);
					}
				}
			}
			else
			{
				//** if other comparision operator
				
				//check the value
				if(!is_object($v))
				{
					if(!is_array($v))
					{
						//get the field name
						$buff = ((!empty($field["field"])) ? sql_get_field_name($field["field"], $field["table_alias"]) : $field["alt_field"]);
						
						if($buff)
						{
							if($where["not"])
							{
								$buff = "NOT {$buff}";
							}
							
							//normalize the value
							$nv = sql_normalize_value($v, $field["type"], $field["empty_is_null"]);
							
							//check the value
							if(!(is_string($nv) || is_numeric($nv))) continue;
							
							if($nv == "NULL" || $nv == "null")
							{
								//** used the compare "is null"
								$buff.= " IS NULL ";
							}
							else
							{
								$buff.= (' ').($where["compare"]).(' ');
								$buff.= $nv;
							}
						}
					}
				}
			}
		}
		
		//check the buffer value
		if(!empty($buff))
		{
			//check the returned result
			if(empty($returned_result))
			{
				$returned_result = '';
			}
			else
			{
				$returned_result.= " OR ";
			}
			
			$returned_result.= $buff;
			$p++;
		}
	}
	
	return ($p > 1 ? "($returned_result)" : $returned_result);
}


/*	Function: get a string for the operator "WHERE" from values.
*	Input:	
*			$where_in	- a "where"-string (without the operator "WHERE")	[STRING || ARRAY || NULL]
*							or an array of associative arrays of table field parameters for the operator "where";
*			$values_in	- an associative array of field values (if $where_in is array).	[ARRAY || NULL]
*	Output:
*			a string for the operator "WHERE" or NULL.	[STRING || NULL]
*	Note:
*			The structure of the array $where_in:
*
*				[0] - an associative array of table field parameters for the operator "where";
*				...
*				[N]
*
*
*			The input array $values_in can be $_REQUEST!
*
*
*			Example 1:
*
*				$where_in	= array("user_id" =>
*											array("key"         => "^id[0-9]+$",
*										  		  "field"       => "user_id",
*												  "type"        => "int",
*												  "compare"     => '='
*												  ),
*									"session_time" =>
*											array("key"         => "^stime$",
*												  "field"       => "session_time",
*												  "type"        => "int",
*												  "compare"     => "<="
*												  )
*									);
*
*				$values_in	= array("id" => 10, "id1" => 1, "id3" => 3, "id9" => 9, "stime" => "45");
*
*
*				$result	= sql_where($where_in, $values_in);
*				//result: "(user_id = 1 OR user_id = 3 OR user_id = 9) AND session_time <= 45"
*
*
*			Example 2:
*
*				$where_in	= array(array("key"         => "^date[0-9]*$",
*										  "field"       => "date",
*										  "type"        => "string",
*										  "table_alias" => "users",
*										  "compare"     => "between",
*										  "between_alt" => '='
*										  ),
*									array("key"         => "^login$",
*										  "field"       => "login",
*										  "type"        => "string",
*										  "table_alias" => "users",
*										  "compare"     => "is not null"
*										  ),
*									array("key"         => "^state$",
*										  "field"       => "state",
*										  "type"        => "int",
*										  "table_alias" => "users",
*										  "compare"     => "!="
*										  ),
*									array("key"			=> "^added_by",
*										  "field"		=> "added_by",
*										  "type"		=> "unformatted",
*										  "table_alias" => "users",
*										  "compare"     => '=',
*										  "use_forced_value" => true,
*										  "forced_value"	 => "users.updated_by"
*										 )
*									);
*
*				$values_in	= array("state" => 1, "date" => '2012-10-03', "date_min" => '2012-09-01', "date_max" => '2012-10-01');
*
*
*				$result	= sql_where($where_in, $values_in);
*				//result: "(users.date BETWEEN '2012-09-01' AND '2012-10-01') AND users.login IS NOT NULL AND users.state != 1 AND users.added_by = users.updated_by"
*/
function sql_where($where_in = null, $values_in = null)
{
	$returned_result = null;
	
	global $FL_DEBUG;
	
	if(!function_exists("sql_compare"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_compare()' not exists! [sql.php -> sql_where()]");
		return $returned_result;
	}
	
	if(is_array($where_in))
	{
		//** if the $where_in is an array of associative arrays of table field parameters for the operator "where"
		
		//* a buffer	[STRING || NULL]
		$buff = null;
		
		//Forming the string for the operator "WHERE"
		foreach($where_in as $arr_id=>$arr_val)
		{
			//get a string for a comparision operator
			$buff = sql_compare($arr_val, $values_in);
			
			//check the buffer value
			if(!empty($buff))
			{
				//check the returned result
				if(empty($returned_result))
				{
					$returned_result = '';
				}
				else
				{
					$returned_result.= " AND ";
				}
				
				$returned_result.= $buff;
			}
		}
	}
	else
	{
		if(is_string($where_in))
		{
			if(!empty($where_in))
			{
				//** if the $where_in is a "where"-string
				
				$returned_result = $where_in;
			}
		}
	}
	
	return $returned_result;
}


/*	Function: get a query for the operation "SELECT".
*	Input:
*			$tables_in	- a table name/names or an array of tables names;	[STRING || ARRAY]
*			$fields_in	- an array of associative arrays of table field parameters;	[ARRAY]
*			$where_in	- a "where"-string (without the operator "WHERE")	[STRING || ARRAY || NULL]
*							or an array of associative arrays of table field parameters for the operator "where"
*							or NULL (used all fields);
*			$values_in	- an array of field values (if $where_in is array).	[ARRAY || NULL]
*	Output:
*			a query for the operation "SELECT" or NULL.	[STRING || NULL]
*	Note:
*			The structure of the array $tables_in:
*
*				[0]["table"] = "table name",
*				[0]["table_alias"] = "table alias" or NULL
*				...
*				[N]
*
*			The structure of the array $fields_in:
*
*				[0] - an associative array of table field parameters for the operation "SELECT";
*				...
*				[N]
*
*
*			The structure of the array $where_in:
*
*				[0] - an associative array of table field parameters for the operator "where";
*				...
*				[N]
*
*
*			The input array $values_in can be $_REQUEST!
*
*
*			Example 1:
*
*				$tables_in	= array("datasources" => array("table" => "list_datasources"));
*
*				$fields_in	= array("id"       => array("field" => "id", "type" => "integer"),
*								    "added_on" => array("alt_field" => "IFNULL(`added_on`, CURRENT_TIMESTAMP)", "field_alias" => "added_on"),
*								    "added_by" => array("field" => "added_by"),
*								    array("alt_field" => "IFNULL(`updated_on`, UNIX_TIMESTAMP(CURRENT_TIMESTAMP))", "field_alias" => "updated_on"),
*								    array("field" => "updated_by"),
*								    array("alt_field" => "IFNULL(`state`, 0)", "field_alias" => "state"),
*								    array("field" => "name"),
*								    array("field" => "note")
*								   );
*
*				$where_in	= array(array("key" => "^name$", "field" => "name", "type" => "string", "compare" => '='));
*
*				$values_in	= array("name" => "ds1");
*
*
*				$result	= sql_select($tables_in, $fields_in, $where_in, $values_in);
*				//result: ""SELECT `id`, IFNULL(`added_on`, CURRENT_TIMESTAMP) AS `added_on`, `added_by`, IFNULL(`updated_on`, UNIX_TIMESTAMP(CURRENT_TIMESTAMP)) AS `updated_on`, `updated_by`, IFNULL(`state`, 0) AS `state`, `name`, `note` FROM `list_datasources` WHERE `name` = 'ds1'"
*/
function sql_select($tables_in = null, $fields_in = null, $where_in = null, $values_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'search_sub_string()' not exists! [sql.php -> sql_select()]");
		return null;
	}
	
	if(!function_exists("sql_get_field_name"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_get_field_name()' not exists! [sql.php -> sql_select()]");
		return null;
	}
	
	if(!function_exists("sql_where"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_where()' not exists! [sql.php -> sql_select()]");
		return null;
	}
	
	$tables = '';
	
	if(is_array($tables_in))
	{
		foreach($tables_in as $arr_id=>$arr_val)
		{
			if(!is_array($arr_val))		 continue;
			if(empty($arr_val["table"])) continue;
			
			//forming the list of tables
			if(!empty($tables)) $tables.= ", ";
			
			$tables.= ('`').($arr_val["table"]).('`');
			
			//check the parameter "table_alias"
			if(!empty($arr_val["table_alias"]))
			{
				if(is_string($arr_val["table_alias"]))
				{
					//add the table alias
					$tables.= (" AS `").($arr_val["table_alias"]).('`');
				}
			}
		}
	}
	elseif(is_string($tables_in))
	{
		$tables = $tables_in;
	}
	
	//Check the list of tables
	if(empty($tables)) return null;
	
	//* list of fields	[STRING]
	$fields = '';
	
	//Forming the list of fields
	if(is_array($fields_in))
	{
		$field = null;
		
		foreach($fields_in as $arr_id=>$arr_val)
		{
			if(!is_array($arr_val)) continue;
			
			//check the parameter "for_select"
			if(isset($arr_val["for_select"]))
			{
				if(is_bool($arr_val["for_select"]))
				{
					if(!$arr_val["for_select"])
					{
						continue;
					}
				}
			}
			
			$field = null;
			
			//check the parameter "field"
			if(!empty($arr_val["field"]))
			{
				$field = ((!empty($arr_val["table_alias"])) ? sql_get_field_name($arr_val["field"], $arr_val["table_alias"]) : sql_get_field_name($arr_val["field"], null));
			}
			
			if(empty($field))
			{
				//check the parameter "alt_field"
				if(!empty($arr_val["alt_field"]))
				{
					if(is_string($arr_val["alt_field"]))
					{
						$field = $arr_val["alt_field"];
					}
				}
			}
			
			//check the field name
			if(empty($field)) continue;
			
			//forming the list of fields
			if(!empty($fields)) $fields.= ", ";
			
			$fields.= $field;
			
			//check the parameter "field_alias"
			if(!empty($arr_val["field_alias"]))
			{
				if(is_string($arr_val["field_alias"]))
				{
					//add the field alias
					$fields.= (" AS `").($arr_val["field_alias"]).('`');
				}
			}
		}
	}
	
	//* a string for the operator "WHERE"	[STRING]
	$where = sql_where($where_in, $values_in);
	
	//Check the "where"-string
	if(!empty($where))
	{
		if(is_string($where))
		{
			//search the word "WHERE"
			if(!search_sub_string("WHERE", $where, $array_matches, null, null))
			{
				$tables.= " WHERE";
			}
			
			$tables.= " {$where}";
		}
	}
	
	return ((!empty($fields)) ? ("SELECT ").($fields).(" FROM ").($tables) : ("SELECT * FROM ").($tables));
}


/*	Function: get a query for the operation "INSERT".
*	Input:	
*			$table_name_in	- a name of a database table;	[STRING]
*			$fields_in		- an array of associative arrays of table field parameters;	[ARRAY]
*			$values_in		- an array of field values.	[ARRAY]
*	Output:
*			a query for the operation "INSERT" or NULL.	[STRING || NULL]
*	Note:
*			The structure of the array $fields_in:
*
*				[0] - an associative array of table field parameters;
*				...
*				[N]
*
*
*			The input array $values_in can be $_REQUEST!
*
*
*			Example 1:
*
*				$table_name_in	= "my_data";
*
*				$fields_in		= array("user_id"  => array("key" => "id1", "field" => "user_id", "type" => "int"),
*										              array("key" => "time_stamp", "field" => "time_stamp", "type" => "int", "default" => time()),
*										"login"    => array("key" => "login", "field" => "login", "type" => "string"),
*										"password" => array("key" => "password", "field" => "password", "type" => "string")
*									   );
*
*				$values_in		= array("id1" => 1, "id2" => 2, "login" => "user");
*
*
*				$result = sql_get_insert_from_array($table_name_in, $fields_in, $values_in);
*				//result: "INSERT INTO (user_id, time_stamp, login, password) VALUES (1, 1348849243, 'user', NULL)"
*/
function sql_insert($table_name_in = null, $fields_in = null, $values_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("sql_get_field_name"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_get_field_name()' not exists! [sql.php -> sql_insert()]");
		return null;
	}
	
	if(!function_exists("sql_get_field_value"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_get_field_value()' not exists! [sql.php -> sql_insert()]");
		return null;
	}
	
	if(empty($table_name_in)) return null;
	if(!is_string($table_name_in)) return null;
	if(!is_array($fields_in)) return null;
	
	//* a field name	[STRING || NULL]
	$field = null;
	
	//* a field value	[STRING || NULL]
	$value = null;
	
	//* list of field names	[STRING]
	$fields = '';
	
	//* list of field values	[STRING]
	$values = '';
	
	//Forming parts of the SQL
	foreach($fields_in as $arr_id=>$arr_val)
	{
		if(!is_array($arr_val)) continue;
		
		//check the parameter "for_insert"
		if(isset($arr_val["for_insert"]))
		{
			if(is_bool($arr_val["for_insert"]))
			{
				if(!$arr_val["for_insert"]) continue;
			}
		}
		
		//get a field value
		$value = sql_get_field_value($arr_val, $values_in);
		
		//check the value
		if(!is_string($value))
		{
			if(!empty($arr_val["required"]))
			{
				if(is_bool($arr_val["required"]))
				{
					if($arr_val["required"]) return null;
				}
			}
			continue;
		}
		
		//get a field name
		$field = null;
		
		if(!empty($arr_val["field"]))
		{
			$field = sql_get_field_name($arr_val["field"], null);
		}
		
		if(empty($field))
		{
			//check the parameter "alt_field"
			if(!empty($arr_val["alt_field"]))
			{
				if(is_string($arr_val["alt_field"]))
				{
					$field = $arr_val["alt_field"];
				}
			}
		}
		
		//check the field name
		if(!is_string($field)) continue;
		
		//forming the list of field names
		$fields.= (($fields == '') ? $field : ", {$field}");
		
		//forming the list of field values
		$values.= (($values == '') ? $value : ", {$value}");
	}
	
	return ((!empty($fields) && !empty($values)) ? ("INSERT INTO `").($table_name_in).("` (").($fields).(") VALUES (").($values).(')') : null);
}


/*	Function: get a query for the operation "UPDATE".
*	Input:
*			$table_name_in	- a name of a database table;	[STRING]
*			$fields_in		- an array of associative arrays of table field parameters;	[ARRAY]
*			$where_in		- a "where"-string (without the operator "WHERE")	[STRING || ARRAY || NULL]
*								or an array of associative arrays of table field parameters for the operator "where"
*								or NULL;
*			$values_in		- an array of field values.	[ARRAY]
*	Output:
*			a query for the operation "UPDATE" or NULL.	[STRING || NULL]
*	Note:
*			The structure of the array $fields_in:
*
*				[0] - an associative array of table field parameters;
*				...
*				[N]
*
*
*			The structure of the array $where_in:
*
*				[0] - an associative array of table field parameters for the operator "where";
*				...
*				[N]
*
*
*			The input array $values_in can be $_REQUEST!
*
*
*			Example 1:
*
*				$table_name_in	= "sessions";
*
*				$fields_in		= array(array("key" => "sstate", "field" => "session_state", "type" => "string", "default" => "closed")
*									   );
*
*				$where_in		= array(array("key"     => "^stime$",
*											  "field"   => "session_time",
*											  "type"    => "unformatted",
*											  "compare" => '<='
*											  ),
*										array("key"     => "^curr_sstate$",
*											  "field"   => "session_state",
*											  "type"    => "string",
*											  "compare" => '='
*											  )
*										);
*
*				$values_in		= array("curr_sstate" => "opened", "stime" => "session_time_limit");
*
*
*				$result	= sql_where($where_in, $values_in);
*				//result: "UPDATE sessions SET session_state = 'closed' WHERE session_time <= session_time_limit AND session_state = 'opened'"
*/
function sql_update($table_name_in = null, $fields_in = null, $where_in = null, $values_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'search_sub_string()' not exists! [sql.php -> sql_update()]");
		return null;
	}
	
	if(!function_exists("sql_get_field_name"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_get_field_name()' not exists! [sql.php -> sql_update()]");
		return null;
	}
	
	if(!function_exists("sql_get_field_value"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_get_field_value()' not exists! [sql.php -> sql_update()]");
		return null;
	}
	
	if(!function_exists("sql_where"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_where()' not exists! [sql.php -> sql_update()]");
		return null;
	}
	
	if(empty($table_name_in)) return null;
	if(!is_string($table_name_in)) return null;
	if(!is_array($fields_in)) return null;
	
	//* a field name	[STRING || NULL]
	$field = null;
	
	//* a field value	[STRING || NULL]
	$value = null;
	
	//* list of field names and field values	[STRING]
	$fields_values = '';
	
	//Forming parts of the SQL
	foreach($fields_in as $arr_id=>$arr_val)
	{
		if(!is_array($arr_val)) continue;
		
		//check the parameter "for_update"
		if(isset($arr_val["for_update"]))
		{
			if(is_bool($arr_val["for_update"]))
			{
				if(!$arr_val["for_update"]) continue;
			}
		}
		
		//get a field value
		$value = sql_get_field_value($arr_val, $values_in);
		
		//check the value
		if(!is_string($value))
		{
			if(!empty($arr_val["required"]))
			{
				if(is_bool($arr_val["required"]))
				{
					if($arr_val["required"]) return null;
				}
			}
			continue;
		}
		
		//get a field name
		$field = null;
		
		if(!empty($arr_val["field"]))
		{
			$field = sql_get_field_name($arr_val["field"], null);
		}
		
		if(empty($field))
		{
			//check the parameter "alt_field"
			if(!empty($arr_val["alt_field"]))
			{
				if(is_string($arr_val["alt_field"]))
				{
					$field = $arr_val["alt_field"];
				}
			}
		}
		
		//check the field name
		if(!is_string($field)) continue;
		
		//forming the list of field names and field values
		$fields_values.= (($fields_values == '') ? "{$field} = {$value}" : ", {$field} = {$value}");
	}
	
	//* a string for the operator "WHERE"	[STRING]
	$where = sql_where($where_in, $values_in);
	
	if(!empty($fields_values) && !empty($where))
	{
		if(is_string($where))
		{
			//search the word "WHERE"
			if(!search_sub_string("WHERE", $where, $array_matches, null, null))
			{
				$fields_values.= " WHERE";
			}
			
			$fields_values.= " {$where}";
		}
	}
	
	return ((!empty($fields_values)) ? ("UPDATE `").($table_name_in).("` SET ").($fields_values) : null);
}


/*	Function: get a query for the operation "DELETE".
*	Input:	
*			$table_name_in	- a name of a database table;	[STRING]
*			$where_in		- a "where"-string (without the operator "WHERE")	[STRING || ARRAY || NULL]
*								or an array of associative arrays of table field parameters for the operator "where"
*								or NULL;
*			$values_in		- an associative array of field values;	[ARRAY]
*			$using_in		- array of using tables (for operator 'USING') or NULL.		[ARRAY]
*	Output:
*			a query for the operation "DELETE" or NULL.	[STRING || NULL]
*	Note:
*			The structure of the array $where_in:
*
*				[0] - an associative array of table field parameters for the operator "where";
*				...
*				[N]
*
*
*			The input array $values_in can be $_REQUEST!
*
*			The structure of array $using_in:
*
*				array("table1", "table2", ..., "tableN");
*				array("table1" => "my_table1", ...);
*/
function sql_delete($table_name_in = null, $where_in = null, $values_in = null, $using_in = null)
{
	$returned_result = null;
	
	global $FL_DEBUG;
	
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'search_sub_string()' not exists! [sql.php -> sql_delete()]");
		return $returned_result;
	}
	
	if(!function_exists("sql_where"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'sql_where()' not exists! [sql.php -> sql_delete()]");
		return $returned_result;
	}
	
	if(empty($table_name_in)) return $returned_result;
	if(!is_string($table_name_in)) return $returned_result;
	
	//* a string for the operator "WHERE"	[STRING]
	$where = sql_where($where_in, $values_in);
	
	//Forming the retured result
	$returned_result = ("DELETE FROM `").($table_name_in).('`');
	
	if(is_array($using_in))
	{
		//* part for operator "USING"	[STRING || NULL]
		$using_part = null;
		
		foreach($using_in as $arr_id=>$arr_val)
		{
			if(is_string($arr_val))
			{
				if(!empty($arr_val))
				{
					if(empty($using_part))
					{
						$using_part = '';
					}
					else
					{
						$using_part.= ", ";
					}
					
					$using_part.= "`{$arr_val}`";
				}
			}
		}
		
		if(!empty($using_part))
		{
			$returned_result.= " USING {$using_part}";
		}
	}
	
	//Check the "where"-string
	if(!empty($where))
	{
		if(is_string($where))
		{
			//search the word "WHERE"
			if(!search_sub_string("WHERE", $where, $array_matches, null, null))
			{
				$returned_result.= " WHERE";
			}
			
			$returned_result.= " {$where}";
		}
	}
	
	return $returned_result;
}


/*	Function:	get a string the operator "LIMIT" from values.
*	Input:
*				$starting_row_in	- the starting number of string (row) or null,	[INTEGER || NULL]
*				$limit_rows_in		- the maximum number of returned rows;			[INTEGER]
*				$add_operator_in	- true (by default) for add operator "LIMIT" to result, otherwise - false.	[BOOLEAN]
*	Output:
*				a string the operator "LIMIT" or NULL.	[STRING || NULL]
*	Note:
*
*				Example 1:
*
*					$starting_row_in = 1;
*					$limit_rows_in   = 10;
*
*					$result = sql_get_limit_value($starting_row_in, $limit_rows_in);
*					//** $result == "1,10" (get strings/rows from 1 to 10)
*
*				Example 2:
*
*					$starting_row_in = 0;	//or null
*					$limit_rows_in   = 10;
*
*					$result = sql_get_limit_value($starting_row_in, $limit_rows_in);
*					//** $result == "10" (get 10 strings/rows)
*
*				Example 3:
*
*					$starting_row_in = null;
*					$limit_rows_in   = 0;
*
*					$result = sql_get_limit_value($starting_row_in, $limit_rows_in);
*					//** $result == '0' (get 0 strings/rows)
*
*				Example 4:
*
*					$starting_row_in = 1;
*					$limit_rows_in   = null;
*
*					$result = sql_get_limit_value($starting_row_in, $limit_rows_in);
*					//** $result == null
*/
function sql_limit($starting_row_in = null, $limit_rows_in = null, $add_operator_in = true)
{
	if(!is_int($limit_rows_in))	return null;
	if($limit_rows_in < 0)		return null;
	
	$add_operator = ((is_bool($add_operator_in)) ? $add_operator_in : true);
	
	if(!is_int($starting_row_in))
	{
		return (($add_operator) ? "LIMIT {$limit_rows_in}" : "{$limit_rows_in}");
	}
	
	if($starting_row_in < 0)
	{
		return (($add_operator) ? "LIMIT {$limit_rows_in}" : "{$limit_rows_in}");
	}
	
	return (($add_operator) ? "LIMIT {$starting_row_in},{$limit_rows_in}" : "{$starting_row_in},{$limit_rows_in}");
}


?>
