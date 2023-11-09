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


/*   Library: data types.
*
*    Copyright (C) 2011 - 2014  ATgroup09 (atgroup09@gmail.com)
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
*				~ search_sub_string();
*				~ replace_sub_string().
*
*			+ string.php:
*				~ string_processing().
*/

/*	Global variables: none
*
*	Functions:
*
*		*** checking of a date ***
*		type_of_date($date_in = null)
*
*		*** checking of a time ***
*		type_of_time($time_in = null)
*
*		*** checking of a datetime ***
*		type_of_datetime($datetime_in = null)
*
*		*** data formatting ***
*		types_data_formatting($value_in = null, $type_in = null, $value_by_default_in = null)
*
*		*** normalize array value ***
*		types_normalize_array_value($params_in = null, &$array_in = null)
*
*		*** normalize array values ***
*		types_normalize_array($params_in = null, &$array_in = null)
*
*		*** check required functions/classes ***
*		types_checking_existence($names_in = null, $err_suffix_in = null)
*
*
*	Classes: none.
*/


//** GLOBAL VARIABLES



//** FUNCTIONS

/*	Function:	checking of a date.
*	Input:
*				$date_in - a date.	[STRING]
*	Output:
*				$date_in or NULL.	[STRING || NULL]
*	Note:
*				correct format: YYYY-MM-DD
*/
function type_of_date($date_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'search_sub_string()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return null;
	}
	
	if(!function_exists("string_processing"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'string_processing()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return null;
	}
	
	$buff = string_processing($date_in, "EQ_NO_BSQ");
	
	return ((search_sub_string("^[0-9]{4}-[0-9]{1,2}-[0-9]{1,2}$", $buff, $arr, null, 0)) ? $buff : null);
}


/*	Function:	checking of a time.
*	Input:
*				$time_in - a time;	[STRING]
*	Output:
*				$time_in or NULL.	[STRING || NULL]
*	Note:
*				correct format: HH:MM:SS (returns) or HH:MM
*/
function type_of_time($time_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'search_sub_string()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return null;
	}
	
	if(!function_exists("string_processing"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'string_processing()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return null;
	}
	
	$buff = string_processing($time_in, "EQ_NO_BSQ");
	
	if(!search_sub_string("^[0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}$|^[0-9]{1,2}:[0-9]{1,2}$", $buff, $arr, null, 0))
	{
		return null;
	}
	
	if(search_sub_string("^[0-9]{1,2}:[0-9]{1,2}$", $buff, $arr, null, 0))
	{
		$buff.= ":00";
	}
	
	$time_parts = explode(':', $buff, 3);
	
	if(count($time_parts))
	{
		$h = (int)$time_parts[0];
		$m = (int)$time_parts[1];
		$s = (int)$time_parts[2];
		
		if($h >= 0 && $m >= 0 && $s >= 0)
		{
			if($h < 24 && $m < 60 && $s < 60) return $buff;
		}
	}
	
	return null;
}


/*	Function:	checking of a datetime.
*	Input:
*				$datetime_in - a datetime.	[STRING]
*	Output:
*				$datetime_in or NULL.	[STRING || NULL]
*	Note:
*				correct format: YYYY-MM-DD HH:MM:SS (returns) or YYYY-MM-DD HH:MM
*/
function type_of_datetime($datetime_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("type_of_date"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'type_of_date()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return null;
	}
	
	if(!function_exists("type_of_time"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'type_of_time()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return null;
	}
	
	if(!function_exists("string_processing"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'string_processing()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return null;
	}
	
	$buff = string_processing($datetime_in, "EQ_NO_BSQ");
	
	if(!empty($buff))
	{
		$datetime_parts = explode(' ', $buff, 2);
		
		if(count($datetime_parts) >= 2)
		{
			$date_part = type_of_date($datetime_parts[0]);
			$time_part = type_of_time($datetime_parts[1]);
			
			if(!empty($date_part) && !empty($time_part)) return "{$date_part} {$time_part}";
		}
	}
	
	return null;
}


/*	Function:	data formatting.
*	Input:
*				$value_in				- value;		[ANY TYPE]
*				$type_in				- data type;	[STRING]
*				$value_by_default_in	- value by default or NULL.	[ANY TYPE || NULL]
*	Output:
*				formatted data.	[ANY TYPES]
*	Note:
*				supported data types:
*
*					- "string"				- converting from: string, integer, float;
*
*					- "integer" | "int"		- converting from: string, integer, float;
*
*					- "float" | "double"	- converting from: string, integer, float;
*												* character ',' in the string value will be replaced to '.' automaticaly;
*
*					- "boolean | bool"		- converting from: string, integer, float);
*
*					- "array"			 	- convertin from any types;
*												* if the input value is array, then will be returned the balue as-is;
*											  	* if the input value is NULL, then will be returned empty array;
*
*					- "date"				- supported formats: YYYY-MM-DD, YYYY-MM-D, YYYY-M-D - with or without a frame of single quotes;
*
*					- "time"				- supported formats: HH:MM:SS, HH:MM, H:M:S - with or without a frame of single quotes;
*
*					- "datetime"			- supported formats: YYYY-MM-DD HH:MM:SS.
*
*
*				Examples:

*					types_data_formatting("100", "int");
*					//100
*
*					types_data_formatting("10.1", "int");
*					//10
*
*					types_data_formatting("a10.1", "int");
*					//NULL
*
*					types_data_formatting("a10.1", "int", 0);
*					//0
*
*					types_data_formatting(true, "int");
*					//1
*
*					types_data_formatting(array(1, 2, 3), "array");
*					//array(1, 2, 3)
*
*					types_data_formatting(1, "array");
*					//array(1)
*/
function types_data_formatting($value_in = null, $type_in = null, $value_by_default_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("type_of_date"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'type_of_date()' not exists! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return $value_by_default_in;
	}
	
	if(!function_exists("type_of_time"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'type_of_time()' not exists! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return $value_by_default_in;
	}
	
	if(!function_exists("type_of_datetime"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'type_of_datetime()' not exists! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return $value_by_default_in;
	}
	
	if(!is_string($type_in)) return $value_by_default_in;
	
	$value = $value_in;
	
	if($type_in == "int" || $type_in == "integer" || $type_in == "float" || $type_in == "double")
	{
		if(is_string($value) && function_exists("replace_sub_string"))
		{
			$value = replace_sub_string(',', '.', $value, -1);
		}
	}
	
	switch($type_in)
	{
		case "int":
		case "integer":
			
			if(is_numeric($value) || is_bool($value) || is_string($value))
			{
				return ((is_int($value)) ? $value : (int)$value);
			}
			
			break;
		
		case "float":
		case "double":
			
			if(is_numeric($value) || is_bool($value) || is_string($value))
			{
				return ((is_float($value)) ? $value : (float)$value);
			}
			
			break;
		
		case "str":
		case "string":
			
			if(is_int($value) || is_float($value))
			{
				return "{$value}";
			}
			elseif(is_bool($value))
			{
				return (($value) ? "true" : "false");
			}
			elseif(is_string($value))
			{
				return $value;
			}
			
			break;
		
		case "boolean":
		case "bool":
			
			if(is_int($value) || is_float($value))
			{
				return (bool)$value;
			}
			elseif(is_string($value))
			{
				return (($value == "true" || $value == "True" || $value == "TRUE") ? true : false);
			}
			elseif(is_bool($value))
			{
				return $value;
			}
			
			break;
		
		case "array":
			
			if(is_array($value))
			{
				return $value;
			}
			else
			{
				$arr = array();
				if(!empty($value)) array_push($arr, $value);
				
				return $arr;
			}
			
			break;
			
		case "date":
			
			$res = type_of_date($value);
			if(!empty($res)) return $res;
			
			break;
			
		case "time":
			
			$res = type_of_time($value);
			if(!empty($res)) return $res;
			
			break;
			
		case "datetime":
			
			$res = type_of_datetime($value);
			if(!empty($res)) return $res;
			
			break;
	}
	
	return $value_by_default_in;
}


/*	Function: normalize array value.
*
*	Input:
*			$params_in	- value parameters;	[ARRAY]
*			$array_in	- link to an associative array.	[ARRAY]
*
*	Output:
*			result:	[BOOLEAN]
*				- true	- the array normalized,
*				- false	- the array not normalized!
*
*	Note:
*			structure of the associative array of parameters:
*
*				- ["key"]			- (*) a key/index name of the array $array_in;	[STRING]
*				- ["type"]			- a data type:	[STRING]
*										-- "int", "integer",
*										-- "float", "double",
*										-- "str", "string",
*										-- "bool", "boolean",
*										-- "array";
*										-- "date"(supported formats: YYYY-MM-DD, YYYY-MM-D, YYYY-M-D - with or witjout a frame of single quotes),
*										-- "time" (supported formats: HH:MM:SS, HH:MM, H:M:S- with or witjout a frame of single quotes),
*										-- "datetime" (supported formats: YYYY-MM-DD HH:MM:SS ...);
*				- ["default"]		- a value by default (if a value of $array_in["key"] is not exists)	[ANY TYPES]
*										* if a value by default is not used and a value of the array $array_in["key"] is not exists, then will be used NULL!
*
*				(*) - is required parameters!
*
*
*			Example 1:
*
*				$user = array("login" => "user1");
*
*				$params = array(array("key" => "login",      "type" => "string", "default" => "user1"),
*								array("key" => "password",   "type" => "string", "default" => null),
*								array("key" => "department", "type" => "string", "default" => null),
*								array("key" => "position",   "type" => "string", "default" => null)
*							   );
*
*				types_normalize_array_value($params[0], $user);
*				types_normalize_array_value($params[1], $user);
*				types_normalize_array_value($params[2], $user);
*				types_normalize_array_value($params[3], $user);
*
*				//print_r($user):
*				//Array ( [login] => user1 [password] => [department] => [position] => )
*/
function types_normalize_array_value($params_in = null, &$array_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("types_data_formatting"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'types_data_formatting()' not exists! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return false;
	}
	
	if(!is_array($params_in))			return false;
	if(!is_array($array_in))			return false;
	if(!isset($params_in["key"]))		return false;
	if(!is_string($params_in["key"]))	return false;
	
	if(isset($params_in["type"]))
	{
		if(is_string($params_in["type"]))
		{
			switch($params_in["type"])
			{
				case "int":
				case "integer":
				case "float":
				case "double":
				case "array":
				case "bool":
				case "boolean":
				case "str":
				case "string":
				case "date":
				case "time":
				case "datetime":
					
					$key = $params_in["key"];
					$value = null;
					
					if(isset($array_in[$key]))
					{
						$value = $array_in[$key];
					}
					else
					{
						if(isset($params_in["default"]))
						{
							$value = $params_in["default"];
						}
					}
					
					$value			= types_data_formatting($value, $params_in["type"], null);
					$array_in[$key]	= $value;
					
					return true;
			}
		}
	}
	
	return false;
}


/*	Function: normalize array values.
*
*	Input:
*			$params_in	- array of value parameters;	[ARRAY]
*			$array_in	- link to an associative array.	[ARRAY]
*
*	Output:
*			result:	[BOOLEAN]
*				- true	- the array normalized,
*				- false	- the array not normalized!
*
*	Note:
*			structure of the associative array of parameters see in the description of function types_normalize_array_value()!
*
*			Example 1:
*
*				$user = array("login" => "user1", "password" => 123);
*
*				$params = array(array("key" => "login",      "type" => "string", "default" => "user1"),
*								array("key" => "password",   "type" => "string", "default" => null),
*								array("key" => "department", "type" => "string", "default" => null),
*								array("key" => "position",   "type" => "string", "default" => null)
*							   );
*
*				types_normalize_array($params, $user);
*
*				//print_r($user):
*				//Array ( [login] => user1 [password] => [department] => [position] => )
*/
function types_normalize_array($params_in = null, &$array_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("types_normalize_array_value"))
	{
		if($FL_DEBUG) echo("#error#Error! Function 'types_normalize_array_value()' not exists! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		return false;
	}
	
	$cTrue = 0;
	
	if(is_array($params_in) && is_array($array_in))
	{
		foreach($params_in as $arr_id=>$arr_val)
		{
			if(types_normalize_array_value($arr_val, $array_in)) $cTrue++;
		}
	}
	
	return (($cTrue > 0) ? true : false);
}


/*	Function:	check required functions/classes.
*	Input:
*				$names_in		- array of required functions, classes;	[ARRAY]
*				$err_suffix_in	- suffix for error message (source file name) or NULL.	[STRING || NULL]
*	Output:
*				return boolean true if all required classes are exists, otherwise false.	[BOOLEAN]
*	Note:
*				the structure of array $names_in:
*
*					[0]["name"] = "{name of function/class}",	[STRING]
*					[0]["type"] = "{function/class}";			[STRING]
*					...
*/
function types_checking_existence($names_in = null, $err_suffix_in = null)
{
	global $FL_DEBUG;
	
	if(is_array($names_in)) 
	{
		$result		= false;
		$err_msg	= null;
		
		for($i=0; $i<count($names_in); $i++)
		{
			if(!is_array($names_in[$i])) continue;
			if(!(!empty($names_in[$i]["name"]) && !empty($names_in[$i]["type"]))) continue;
			if(!(is_string($names_in[$i]["name"]) && is_string($names_in[$i]["type"]))) continue;
			if(!($names_in[$i]["type"] == "function" || $names_in[$i]["type"] == "class")) continue;
			
			$result = (($names_in[$i]["type"] == "function") ? function_exists($names_in[$i]["name"]) : class_exists($names_in[$i]["name"]));
			
			if(!$result)
			{
				if($FL_DEBUG)
				{
					$err_msg = "#error#Error! ";
					$err_msg.= (($names_in[$i]["type"] == "function") ? "Function" : "Class");
					$err_msg.= " '".$names_in[$i]["name"]."' is not exists!";
					
					if(!empty($err_suffix_in))
					{
						if(is_string($err_suffix_in)) $err_msg.= " ".$err_suffix_in;
					}
					
					echo($err_msg);
				}
				
				return false;
			}
		}
	}
	
	return true;
}


?>
