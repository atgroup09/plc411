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


/*   Library: request.
*
*    Copyright (C) 2011-2012  ATgroup09 (atgroup09@gmail.com)
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


/*	Global variables: undefined.
*
*
*	Functions:
*
*		*** check key in $_REQUEST ***
*		check_key_in_request($key_in)
*		
*		*** get value from global array $_REQUEST by key ***
*		get_request_value_on_key($key_in)
*
*		*** get array of values from global array $_REQUEST by parameters ***
*		get_array_of_request_values_on_key($re_key_in)
*
*		*** get array of accepted languages of client ***
*		get_array_of_accepted_languages()
*
*		*** get name of accepted language of client with high quotient ***
*		get_name_of_language_with_high_quotient()
*
*
*	Classes: undefined.
*/


/*	Dependencies:
*
*		- global variables:
*
*			+ FL_DEBUG - show/hide debug info.
*
*
*		- libraries:
*
*			+ regexp/regexp.php:
*				~ search_sub_string().
*/


//DIRECTIONS


//GLOBAL VARIABLES


//FUNCTIONS

/*	Function:	check key in $_REQUEST.
*	Input:
*				$key_in - key.	[STRING]
*	Output:
*				result:	[BOOLEAN]
*					- true	- key exists,
*					- false - key not exists.
*/
function check_key_in_request($key_in)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'search_sub_string()' not exists! [request/request.php -> check_key_in_request()]");
		}
		return false;
	}
	
	//Check input arguments
	if(empty($key_in))
	{
		if($FL_DEBUG)
		{
			echo("Error! Input argument 'key_in' is undefined! [request/request.php -> check_key_in_request()]");
		}
		return false;
	}
	
	if(!is_string($key_in))
	{
		if($FL_DEBUG)
		{
			echo("Error! Input argument 'key_in' is undefined (not string)! [request/request.php -> check_key_in_request()]");
		}
		return false;
	}
	
	//Check global array $_REQUEST
	if(!empty($_REQUEST))
	{
		foreach($_REQUEST as $k=>$v)
		{
			//search the key
			if(search_sub_string("^{$key_in}$", $k, $regs, null, null))
			{
				return true;
			}
		}
	}
	
	return false;
}


/*	Function:	get value from global array $_REQUEST by key.
*	Input:
*				$key_in - key.	[STRING]
*	Output:
*				value by key or null.	[STRING || NULL]
*/
function get_request_value_on_key($key_in)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'search_sub_string()' not exists! [request/request.php -> get_request_value_on_key()]");
		}
		return null;
	}
	
	//Check input arguments
	if(empty($key_in))
	{
		if($FL_DEBUG)
		{
			echo("Error! Input argument 'key_in' is undefined! [request/request.php -> get_request_value_on_key()]");
		}
		return null;
	}
	
	if(!is_string($key_in))
	{
		if($FL_DEBUG)
		{
			echo("Error! Input argument 'key_in' is undefined (not string)! [request/request.php -> get_request_value_on_key()]");
		}
		return null;
	}
	
	//Check global array $_REQUEST
	if(!empty($_REQUEST))
	{
		foreach($_REQUEST as $k=>$v)
		{
			//search the key
			if(search_sub_string("^{$key_in}$", $k, $regs, null, null))
			{
				return $v;
			}
		}
	}
	
	return null;
}


/*	Function:	get array of values from global array $_REQUEST by parameters.
*	Input:
*				$re_key_in - key (regexp).	[STRING]
*	Output:
*				array of values.	[ARRAY]
*	Note:
*
*				Example 1:
*
*					//** $_REQUEST = array("field" => "100", "field0" => '0', "field2" => '2', "field3id" => '3', "id_field" => "id");
*					$result = get_array_of_request_values_on_key("^field$");
*
*					//** $result == array("field" => "100");
*
*				Example 2:
*
*					//** $_REQUEST = array("field" => "100", "field0" => '0', "field2" => '2', "field3id" => '3', "id_field" => "id");
*					$result = get_array_of_request_values_on_key("^field[0-9]+$");
*
*					//** $result == array("field" => "100", "field0" => '0', "field2" => '2');
*/
function get_array_of_request_values_on_key($re_key_in)
{
	//* result	[ARRAY]
	$return_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'search_sub_string()' not exists! [request/request.php -> get_array_of_request_values_on_key()]");
		}
		return $return_result;
	}
	
	//Check input arguments
	if(empty($re_key_in))
	{
		if($FL_DEBUG)
		{
			echo("Error! Input argument 're_key_in' is undefined! [request/request.php -> get_array_of_request_values_on_key()]");
		}
		return $return_result;
	}
	
	if(!is_string($re_key_in))
	{
		if($FL_DEBUG)
		{
			echo("Error! Input argument 're_key_in' is undefined (not a string)! [request/request.php -> get_array_of_request_values_on_key()]");
		}
		return $return_result;
	}
	
	//Check global array $_REQUEST
	if(!empty($_REQUEST))
	{
		foreach($_REQUEST as $k=>$v)
		{
			//search the key
			if(search_sub_string($re_key_in, $k, $regs, null, null))
			{
				$return_result[$k] = $v;
			}
		}
	}
	
	return $return_result;
}


/*	Function:	get array of accepted languages of client.
*	Input:
*				none.
*	Output:
*				array of languages.	[ARRAY]
*	Note:
*
*				Structure of output array:
*
*					$result["LANG-NAME"] = LANG-QUOTIENT,
*					...
*
*
*				Example 1:
*
*					//** $_SERVER['HTTP_ACCEPT_LANGUAGE'] = "ru-ru,ru;q=0.8,en-us;q=0.5,en;q=0.3"
*					$result = get_array_of_accepted_languages();
*
*					//** $result["ru-ru"]	== 0.8,
*					//** $result["ru"]		== 0.8,
*					//** $result["en-us"]	== 0.5,
*					//** $result["en"]		== 0.3
*/
function get_array_of_accepted_languages()
{
	//* result	[ARRAY]
	$return_result = array();
	
	
	//Check global array $_SERVER
	if(!empty($_SERVER))
	{
		//check element 'HTTP_ACCEPT_LANGUAGE'
		if(!empty($_SERVER["HTTP_ACCEPT_LANGUAGE"]))
		{
			//* array of language parts	[ARRAY]
			//
			//**	array("LANG-NAME", "LANG-NAME;LANG-QUOTIENT", ...)
			$array_of_lang_parts	= explode(',', $_SERVER["HTTP_ACCEPT_LANGUAGE"]);
			
			//* array of quotient parts	[ARRAY || NULL]
			//
			//**	array("LANG-NAME", "LANG-QUOTIENT")
			$array_of_q_parts		= null;
			
			//* name of language		[STRING || NULL]
			$lang					= null;
			
			//* buffer					[ARRAY]
			$buff					= array();
			
			
			for($i=0; $i<count($array_of_lang_parts); $i++)
			{
				$array_of_q_parts = explode(";q=", $array_of_lang_parts[$i]);
				
				if(count($array_of_q_parts))
				{
					$lang = $array_of_q_parts[0];
					
					//init output array by default (empty value)
					$return_result[$lang] = 0.0;
					
					if(count($array_of_q_parts) > 1)
					{
						$return_result[$lang] = (float)$array_of_q_parts[1];
						
						//init previous empty elements
						while(count($buff))
						{
							$lang = array_pop($buff);
							$return_result[$lang] = (float)$array_of_q_parts[1];
						}
					}
					else
					{
						array_push($buff, $lang);
					}
				}
			}
		}
	}
	
	return $return_result;
}


/*	Function:	get name of accepted language of client with high quotient.
*	Input:
*				none.
*	Output:
*				name of language or null.	[STRING || NULL]
*/
function get_name_of_language_with_high_quotient()
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("get_array_of_accepted_languages"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'get_array_of_accepted_languages()' not exists! [request/request.php -> get_array_of_accepted_languages()]");
		}
		return null;
	}
	
	//* array of languages	[ARRAY]
	$array_of_langs = get_array_of_accepted_languages();
	
	
	//Check array
	if(is_array($array_of_langs))
	{
		//* buffer	[STRING || NULL]
		$buff = null;
		
		
		foreach($array_of_langs as $k=>$v)
		{
			//check value
			if(is_float($v))
			{
				if(!is_string($buff))
				{
					$buff = $k;
				}
				else
				{
					if($array_of_langs[$buff] < $v)
					{
						$buff = $k;
					}
				}
			}
		}
	}
	
	return $buff;
}


//CLASSES


//CONSTRUCTOR


?>
