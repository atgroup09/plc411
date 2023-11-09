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


/*   Library: strings.
*
*    Copyright (C) 2012-2014  ATgroup09 (atgroup09@gmail.com)
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
*				~ iconv(),
*				~ mb_convert_encoding().
*
*			+ regexp/regexp.php:
*				~ search_sub_string(),
*				~ replace_sub_string().
*/


/*	Global variables: none.
*
*
*	Functions:
*
*		*** check the framing of the single-quoted strings ***
*		string_check_bsq($str_in, $options_in)
*
*		*** check the framing of the double-quoted strings ***
*		string_check_bdq($str_in, $options_in)
*
*		*** add the framing from single or double quotes ***
*		string_add_bq($str_in, $options_in)
*
*		*** shielding special characters ***
*		string_shielding_chars($str_in, $options_in)
*
*		*** processing string ***
*		string_processing($str_in, $options_in)
*
*		*** encoding string **
*		string_encoding($str_in = null, $from_encoding_in = null, $to_encoding_in = null)
*
*
*	Classes: none.
*
*
*	Initialization of global variables: none.
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function:	check the framing of the single-quoted strings.
*	Input:
*				$str_in		- string,	[STRING]
*				$options_in	- options:	[STRING || NULL]
*								-- "EQ_SHIELD_BQ"	- framing the quotes shielded,
*								-- "!EQ_SHIELD_BQ"	- framing the quotes not shielded (hight priority!),
*								-- null				- any.
*	Output:
*				result:	[BOOLEAN]
*					- true	- framing exists,
*					- false	- framing not exists.
*	Note:
*
*			Example 1:
*
*				$res = string_check_bsq("'", "EQ_SHIELD_BQ");
*
*				//** result: false
*				//**	- one single quote!
*
*
*			Example 2:
*
*				$res = string_check_bsq("'Text'", "EQ_SHIELD_BQ");
*
*				//** result: false
*				//**	- framing the quotes not shielded!
*
*
*			Example 3:
*
*				$res = string_check_bsq("'Text'", "!EQ_SHIELD_BQ");
*
*				//** result: true
*				//**	- framing exists!
*				//**	- framing the quotes not shielded!
*
*
*			Example 4:
*
*				$res = string_check_bsq("\\'Text\\'", "EQ_SHIELD_BQ");
*
*				//** result: true
*				//**	- framing exists!
*				//**	- framing the quotes shielded!
*
*
*			Example 5:
*
*				$res = string_check_bsq("\\'Text\\'", null);
*
*				//** result: true
*				//**	- framing exists!
*/
function string_check_bsq($str_in = null, $options_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'search_sub_string()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return false;
	}
	
	//Check input arguments
	if(is_string($str_in))
	{
		//** if string is only one single quote, then returs false!
		if(!search_sub_string("^\'$|^\\\'$", $str_in, $arr, null, 0))
		{
			//* state [BOOLEAN]
			$o_shield		= false;
			$o_no_shield	= false;
			
			
			//** if framing the quotes shielded
			if(search_sub_string("^\\\'", $str_in, $arr, null, 0) && search_sub_string("\\\'$", $str_in, $arr, null, 0))
			{
				$o_shield = true;
			}
			
			//** if framing the quotes shielded
			if(search_sub_string("^\'", $str_in, $arr, null, 0) && search_sub_string("\'$", $str_in, $arr, null, 0))
			{
				$o_no_shield = true;
			}
			
			//check options
			if(!empty($options_in))
			{
				if(is_string($options_in))
				{
					if(search_sub_string("EQ_SHIELD_BQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_SHIELD_BQ", $options_in, $arr, null, 0))
					{
						return $o_shield;
					}
					else
					{
						return $o_no_shield;
					}
				}
			}
		}
	}
	
	return (($o_shield == true) ? $o_shield : $o_no_shield);
}


/*	Function:	check the framing of the double-quoted strings.
*	Input:
*				$str_in		- string,	[STRING]
*				$options_in	- options:	[STRING || NULL]
*								-- "EQ_SHIELD_BQ"	- framing the quotes shielded,
*								-- "!EQ_SHIELD_BQ"	- framing the quotes not shielded (hight priority!),
*								-- null				- any.
*	Output:
*				result:	[BOOLEAN]
*					- true	- framing exists,
*					- false	- framing not exists.
*/
function string_check_bdq($str_in = null, $options_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'search_sub_string()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return false;
	}
	
	//Check input arguments
	if(is_string($str_in))
	{
		//** if string is only one single quote, then returs false!
		if(!search_sub_string("^\"$|^\\\"$", $str_in, $arr, null, 0))
		{
			//* state	[BOOLEAN]
			$o_shield		= false;
			$o_no_shield	= false;
			
			
			//** if framing the quotes shielded
			if(search_sub_string("^\\\"", $str_in, $arr, null, 0) && search_sub_string("\\\"$", $str_in, $arr, null, 0))
			{
				$o_shield = true;
			}
			
			//** if framing the quotes shielded
			if(search_sub_string("^\"", $str_in, $arr, null, 0) && search_sub_string("\"$", $str_in, $arr, null, 0))
			{
				$o_no_shield = true;
			}
			
			//check options
			if(!empty($options_in))
			{
				if(is_string($options_in))
				{
					if(search_sub_string("EQ_SHIELD_BQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_SHIELD_BQ", $options_in, $arr, null, 0))
					{
						return $o_shield;
					}
					else
					{
						return $o_no_shield;
					}
				}
			}
		}
	}
	
	return (($o_shield == true) ? $o_shield : $o_no_shield);
}


/*	Function:	add the framing of the double- or single-quoted strings.
*	Input:
*				$str_in		- string,	[STRING]
*				$options_in	- options:	[STRING || NULL]
*								-- "EQ_ADD_BSQ"		- add the framing of the single-quoted strings (if they not exists!),
*								-- "EQ_ADD_BDQ"		- add the framing of the double-quoted strings (if they not exists!),
*								-- "EQ_SHIELD_BQ"	- escape framing quotes,
*								-- "!EQ_SHIELD_BQ"	- not escape framing quotes (by default).
*	Output:
*				updated input string or null (if error).	[STRING || NULL]
*	Note:
*
*			Example 1:
*
*				$res = string_add_bq("Text", "EQ_ADD_BSQ");
*				//** or string_add_bq("Text", "EQ_ADD_BSQ|!EQ_SHIELD_BQ");
*
*				//** result: 'Text'
*
*
*			Example 2:
*
*				$res = string_add_bq("Text", "EQ_ADD_BSQ|EQ_SHIELD_BQ");
*
*				//** result: \'Text\'
*
*
*			Example 3:
*
*				$res = string_add_bq("\'Text\'", "EQ_ADD_BSQ|EQ_SHIELD_BQ");
*				//** or string_add_bq("\'Text\'", "EQ_SHIELD_BQ");
*
*				//** result: \'Text\'
*
*
*			Example 4:
*
*				$res = string_add_bq("\\\'Text\\\'", "EQ_ADD_BSQ|EQ_SHIELD_BQ");
*				//** or string_add_bq("\\\'Text\\\'", "EQ_SHIELD_BQ");
*
*				//** result: \'Text\'
*
*
*			Example 5:
*
*				$res = string_add_bq("Text", "EQ_SHIELD_BQ");
*
*				//** result: Text
*/
function string_add_bq($str_in = null, $options_in = null)
{
	//* result	[STRING || NULL]
	$return_result = null;
	
	
	//Init global values
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'search_sub_string()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	if(!function_exists("replace_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'replace_sub_string()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	if(!function_exists("string_check_bsq"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'string_check_bsq()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	if(!function_exists("string_check_bdq"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'string_check_bdq()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	//Check input arguments
	if(is_string($str_in))
	{
		//init result (by default)
		$return_result = $str_in;
		
		//** if string is only one single quote, then returs false!
		if(!search_sub_string("^\'$|^\\\'$|^\"$|^\\\"$", $return_result, $arr, null, 0))
		{
			//* escape or not escape framing quotes	[STRING]
			$shield = "!EQ_SHIELD_BQ";
			
			//* add or not add the framing quotes 	[STRING]
			$add_bsq = "!EQ_ADD_BSQ";
			$add_bdq = "!EQ_ADD_BDQ";
			
			
			//check options
			if(!empty($options_in))
			{
				if(is_string($options_in))
				{
					if(search_sub_string("EQ_SHIELD_BQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_SHIELD_BQ", $options_in, $arr, null, 0))
					{
						$shield		= "EQ_SHIELD_BQ";
					}
					
					if(search_sub_string("EQ_ADD_BSQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_ADD_BSQ", $options_in, $arr, null, 0))
					{
						$add_bsq	= "EQ_ADD_BSQ";
					}
					
					if(search_sub_string("EQ_ADD_BDQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_ADD_BDQ", $options_in, $arr, null, 0))
					{
						$add_bdq	= "EQ_ADD_BDQ";
					}
				}
			}
			
			if($shield == "EQ_SHIELD_BQ")
			{
				//** if escape framing quotes
				
				//check the framing of the single-quoted strings
				if(string_check_bsq($return_result, "!EQ_SHIELD_BQ") && ($add_bsq != "EQ_ADD_BSQ"))
				{
					//escape framing single-quotes
					$return_result = replace_sub_string("^\'", "\\\'", $return_result, -1);
					$return_result = replace_sub_string("\'$", "\\\'", $return_result, -1);
				}
				
				//check the framing of the double-quoted strings
				if(string_check_bdq($return_result, "!EQ_SHIELD_BQ") && ($add_bdq != "EQ_ADD_BDQ"))
				{
					//escape framing double-quotes
					$return_result = replace_sub_string("^\"", "\\\"", $return_result, -1);
					$return_result = replace_sub_string("\'$", "\\\"", $return_result, -1);
				}
				
				if($add_bsq == "EQ_ADD_BSQ")
				{
					//add and escape the framing of the single-quoted strings
					$return_result = "\\'{$return_result}\\'";
				}
				
				if($add_bdq == "EQ_ADD_BDQ")
				{
					//add and escape the framing of the double-quoted strings
					$return_result = "\\\"{$return_result}\\\"";
				}
			}
			else
			{
				//** if not escape framing quotes
				
				//check the framing of the single-quoted strings
				if(string_check_bsq($return_result, "EQ_SHIELD_BQ") && ($add_bsq != "EQ_ADD_BSQ"))
				{
					//unescape framing single-quotes
					$return_result = replace_sub_string("^\\\'", '\'', $return_result, -1);
					$return_result = replace_sub_string("\\\'$", '\'', $return_result, -1);
				}
				
				//check the framing of the double-quoted strings
				if(string_check_bdq($return_result, "EQ_SHIELD_BQ") && ($add_bdq != "EQ_ADD_BDQ"))
				{
					//unescape framing double-quotes
					$return_result = replace_sub_string("^\\\"", '\"', $return_result, -1);
					$return_result = replace_sub_string("\\\"$", '\"', $return_result, -1);
				}
				
				if($add_bsq == "EQ_ADD_BSQ")
				{
					//add the framing of the single-quoted strings
					$return_result = "'{$return_result}'";
				}
				
				if($add_bdq == "EQ_ADD_BDQ")
				{
					//add the framing of the double-quoted strings
					$return_result = "\"{$return_result}\"";
				}
			}
		}
	}
	
	return $return_result;
}


/*	Function:	shielding special chars.
*	Input:
*				$str_in		- string,	[STRING]
*				$options_in	- options:	[STRING]
*								-- "EQ_SHIELD_CHARS"	- shielding special chars (addslashes)
*															* before addslashes makes stripslashes (if not used EQ_SHIELD_NO_O!) for avoid double shielding,
*								-- "!EQ_SHIELD_CHARS"	- no shielding special chars,
*								-- "EQ_SHIELD_NO_O"		- do not make the abolition of shielding special chars (stripslashes),
*								-- "EQ_ADD_BSQ"			- add the framing of the single-quoted strings (if they not exists!),
*								-- "!EQ_ADD_BSQ"		- not add the framing of the single-quoted strings (if they not exists!),
*								-- "EQ_ADD_BDQ"			- add the framing of the double-quoted strings (if they not exists!),
*								-- "!EQ_ADD_BDQ"		- not add the framing of the double-quoted strings (if they not exists!),
*								-- "EQ_SHIELD_BQ"		- escape framing quotes,
*								-- "!EQ_SHIELD_BQ"		- not escape framing quotes.
*	Output:
*				updated string or null (if error).	[STRING || NULL]
*	Note:
*
*				special chars: " ' \ NULL.
*
*
*			Example 1:
*
*				$res = string_shielding_chars("Text \\\\ \' \" ", null);
*
*				//** result: Text \ ' "
*
*
*			Example 2:
*
*				$res = string_shielding_chars("'Text'", "EQ_SHIELD_CHARS");
*
*				//** result: \'Text\'
*
*
*			Example 3:
*
*				$res = string_shielding_chars("Text \\\\ \' \" ", "EQ_SHIELD_CHARS|EQ_ADD_BSQ");
*
*				//** result: \'Text \\ \' \"\'
*
*
*			Example 4:
*
*				$res = string_shielding_chars("Text\\\'", "EQ_SHIELD_NO_O|EQ_ADD_BSQ");
*
*				//** result: 'Text\''
*/
function string_shielding_chars($str_in = null, $options_in = null)
{
	//* result	[STRING || NULL]
	$return_result = null;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'search_sub_string()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	if(!function_exists("string_add_bq"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'string_add_bq()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	//Check input arguments
	if(is_string($str_in))
	{
		//* options	[BOOLEAN]
		$eq_shield_no_o		= false;
		$eq_shield			= false;
		
		
		//init result (by default)
		$return_result = $str_in;
		
		//check options
		if(!empty($options_in))
		{
			if(is_string($options_in))
			{
				//check option 'EQ_SHIELD_NO_O'
				if(search_sub_string("EQ_SHIELD_NO_O", $options_in, $arr, null, 0) && !search_sub_string("!EQ_SHIELD_NO_O", $options_in, $arr, null, 0))
				{
					$eq_shield_no_o = true;
				}
				
				//check option 'EQ_SHIELD_CHARS'
				if(search_sub_string("EQ_SHIELD_CHARS", $options_in, $arr, null, 0) && !search_sub_string("!EQ_SHIELD_CHARS", $options_in, $arr, null, 0))
				{
					$eq_shield = true;
				}
			}
		}
		
		//** if not used EQ_SHIELD_NO_O
		if(!$eq_shield_no_o)
		{
			//stripslashes
			$return_result = stripslashes($return_result);
		}
		
		//** if used EQ_SHIELD_CHARS
		if($eq_shield)
		{
			//addslashes
			$return_result = addslashes($return_result);
		}
		
		//add the framing of the single- or double-quoted strings
		if(is_string($options_in))
		{
			if((search_sub_string("EQ_ADD_BSQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_ADD_BSQ", $options_in, $arr, null, 0)) || (search_sub_string("EQ_ADD_BDQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_ADD_BDQ", $options_in, $arr, null, 0)) || (search_sub_string("EQ_SHIELD_BQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_SHIELD_BQ", $options_in, $arr, null, 0)))
			{
				$return_result = string_add_bq($return_result, $options_in);
			}
		}
	}
	
	return $return_result;
}


/*	Function:	processing a string.
*	Input:
*				$str_in		- string,	[STRING]
*				$options_in	- options:	[STRING]
*								-- "EQ_AT"				- replace '@' to '[AT]',
*								-- "EQ_BACK_AT"			- replace '[AT]' to '@',
*								-- "EQ_AMP"				- replace '&' to '&amp;',
*								-- "EQ_BACK_AMP"		- replace '&amp;' to '&',
*								-- "EQ_LT"				- replace '<' to '&lt;',
*								-- "EQ_BACK_LT	"		- replace '&lt;' to '<',
*								-- "EQ_GT"				- replace '>' to '&gt;',
*								-- "EQ_BACK_GT	"		- replace '&gt;' to '>',
*								-- "EQ_BR"				- replace '\r\n', '\n\r', '\r', '\n' to '<br />',
*								-- "EQ_BACK_BR"			- replace '<br />' to '\r\n',
*								-- "EQ_SP_TO_USC"		- replace ' ' to '_',
*								-- "EQ_USC_TO_SP"		- replace '_' to ' ',
*								-- "EQ_SP_TO_URI"		- replace ' ' to '%20',
*								-- "EQ_URI_TO_SP"		- replace '%20' to ' ',
*								-- "EQ_BSLASH"			- replace '\' to '&#92;',
*								-- "EQ_BACK_BSLASH"		- replace '&#92;' to '\',
*								-- "EQ_NO_RN"			- remove '\r\n', '\n\r', '\r', '\n',
*								-- "EQ_NO_BR"			- remove '<br />',
*								-- "EQ_NO_BSP"			- remove the beginning and end spaces,
*								-- "EQ_NO_BTAB"			- remove the beginning and end tabs,
*								-- "EQ_NO_BSQ"			- remove the beginning and end single quotes,
*								-- "EQ_NO_BDQ"			- remove the beginning and end double quotes,
*								-- "EQ_TRIM"			- strip whitespace (or other characters) from the beginning and end of a string,
*								-- "EQ_SHIELD_CHARS"	- shielding special chars (addslashes)
*															* before addslashes makes stripslashes (if not used EQ_SHIELD_NO_O!) for avoid double shielding,
*								-- "EQ_BACK_SHIELD"		- make the abolition of shielding special chars (stripslashes),
*								-- "EQ_SHIELD_NO_O"		- do not make the abolition of shielding special chars (stripslashes),
*								-- "EQ_ADD_BSQ"			- add the framing of the single-quoted strings,
*								-- "EQ_ADD_BDQ"			- add the framing of the double-quoted strings,
*								-- "EQ_SHIELD_BQ"		- escape framing quotes.
*	Output:
*				updated string or null (if error).	[STRING || NULL]
*	Note:
*
*
*				PHP-settings for using "EQ_SHIELD_BQ", "EQ_SHIELD_CHARS" (in .htaccess file):
*
*					# set magic_quotes_gpc in off
*					php_value magic_quotes_gpc 0
*
*					# set magic_quotes_runtime off
*					php_value magic_quotes_runtime 0
*
*					# set magic_quotes_sybase off
*					php_value magic_quotes_sybase 0
*
*
*				Examples:
*					string_processing(str_in, "EQ_AT");
*					string_processing(str_in, "EQ_AT|EQ_AMP");
*					string_processing(str_in, "EQ_AT|EQ_AMP|EQ_NO_RN");
*
*				Options without the suffix "_BACK" has high priority!
*
*				The prefix '!' used as NOT!
*
*
*				The option "EQ_TRIM" will strip these characters:
*					- " " (ASCII 32 (0x20)), an ordinary space;
*					- "\t" (ASCII 9 (0x09)), a tab;
*					- "\n" (ASCII 10 (0x0A)), a new line (line feed);
*					- "\r" (ASCII 13 (0x0D)), a carriage return;
*					- "\0" (ASCII 0 (0x00)), the NUL-byte;
*					- "\x0B" (ASCII 11 (0x0B)), a vertical tab.
*/
function string_processing($str_in = null, $options_in = null)
{
	//* result	[STRING || NULL]
	$return_result = null;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'search_sub_string()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	if(!function_exists("replace_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'replace_sub_string()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	if(!function_exists("string_check_bsq"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'string_check_bsq()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	if(!function_exists("string_check_bdq"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'string_check_bdq()' is undefined! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $return_result;
	}
	
	//Check input arguments
	if(is_string($str_in))
	{
		//init result (by default)
		$return_result = $str_in;
		
		//check options
		if(is_string($options_in))
		{
			//** if option EQ_AT
			if(search_sub_string("EQ_AT", $options_in, $arr, null, 0) && !search_sub_string("!EQ_AT", $options_in, $arr, null, 0))
			{
				//replace '@' to '[AT]'
				$return_result = replace_sub_string('@', "[AT]", $return_result, -1);
			}
			else
			{
				if(search_sub_string("EQ_BACK_AT", $options_in, $arr, null, 0) && !search_sub_string("!EQ_BACK_AT", $options_in, $arr, null, 0))
				{
					//replace '[AT]' to '@'
					$return_result = replace_sub_string("\[AT\]", '@', $return_result, -1);
				}
			}
			
			//** if option EQ_AMP
			if(search_sub_string("EQ_AMP", $options_in, $arr, null, 0) && !search_sub_string("!EQ_AMP", $options_in, $arr, null, 0))
			{
				//replace '&' to "&amp;"
				$return_result = replace_sub_string('&', "&amp;", $return_result, -1);
			}
			else
			{
				if(search_sub_string("EQ_BACK_AMP", $options_in, $arr, null, 0) && !search_sub_string("!EQ_BACK_AMP", $options_in, $arr, null, 0))
				{
					//replace "&amp;" to '&'
					$return_result = replace_sub_string("&amp;", '&', $return_result, -1);
				}
			}
			
			//** if option EQ_LT
			if(search_sub_string("EQ_LT", $options_in, $arr, null, 0) && !search_sub_string("!EQ_LT", $options_in, $arr, null, 0))
			{
				//replace '<' to "&lt;"
				$return_result = replace_sub_string('<', "&lt;", $return_result, -1);
			}
			else
			{
				if(search_sub_string("EQ_BACK_LT", $options_in, $arr, null, 0) && !search_sub_string("!EQ_BACK_LT", $options_in, $arr, null, 0))
				{
					//replace "&lt;" to '<'
					$return_result = replace_sub_string("&lt;", '<', $return_result, -1);
				}
			}
			
			//** if option EQ_GT
			if(search_sub_string("EQ_GT", $options_in, $arr, null, 0) && !search_sub_string("!EQ_GT", $options_in, $arr, null, 0))
			{
				//replace '>' to "&gt;"
				$return_result = replace_sub_string('>', "&gt;", $return_result, -1);
			}
			else
			{
				if(search_sub_string("EQ_BACK_GT", $options_in, $arr, null, 0) && !search_sub_string("!EQ_BACK_GT", $options_in, $arr, null, 0))
				{
					//replace "&gt;" to '>'
					$return_result = replace_sub_string("&gt;", '>', $return_result, -1);
				}
			}
			
			//** if option EQ_BR
			if(search_sub_string("EQ_BR", $options_in, $arr, null, 0) && !search_sub_string("!EQ_BR", $options_in, $arr, null, 0))
			{
				//replace "\r\n|\n\r|\r|\n" to "<br />"
				$return_result = replace_sub_string("\r\n|\n\r|\r|\n", "<br />", $return_result, -1);
			}
			else
			{
				if(search_sub_string("EQ_BACK_BR", $options_in, $arr, null, 0) && !search_sub_string("!EQ_BACK_BR", $options_in, $arr, null, 0))
				{
					//replace "<br \/>|<br>" to "\r\n"
					$return_result = replace_sub_string("<br \/>|<br>", "\r\n", $return_result, -1);
				}
			}
			
			//** if option EQ_SP_TO_USC
			if(search_sub_string("EQ_SP_TO_USC", $options_in, $arr, null, 0) && !search_sub_string("!EQ_SP_TO_USC", $options_in, $arr, null, 0))
			{
				//replace ' ' to '_'
				$return_result = replace_sub_string("\s{1,1}", '_', $return_result, -1);
			}
			else
			{
				if(search_sub_string("EQ_USC_TO_SP", $options_in, $arr, null, 0) && !search_sub_string("!EQ_USC_TO_SP", $options_in, $arr, null, 0))
				{
					//replace '_' to ' '
					$return_result = replace_sub_string('_{1,1}', ' ', $return_result, -1);
				}
			}
			
			//** if option EQ_SP_TO_URI
			if(search_sub_string("EQ_SP_TO_URI", $options_in, $arr, null, 0) && !search_sub_string("!EQ_SP_TO_URI", $options_in, $arr, null, 0))
			{
				//replace ' ' to '%20'
				$return_result = replace_sub_string("\s{1,1}", "%20", $return_result, -1);
			}
			else
			{
				if(search_sub_string("EQ_URI_TO_SP", $options_in, $arr, null, 0) && !search_sub_string("!EQ_URI_TO_SP", $options_in, $arr, null, 0))
				{
					//replace '_' to ' '
					$return_result = replace_sub_string("%20{1,1}", ' ', $return_result, -1);
				}
			}
			
			//** if option EQ_BSLASH
			if(search_sub_string("EQ_BSLASH", $options_in, $arr, null, 0) && !search_sub_string("!EQ_BSLASH", $options_in, $arr, null, 0))
			{
				//replace '\' to "&#92;"
				$return_result = replace_sub_string("\\\\", "&#92;", $return_result, -1);
			}
			else
			{
				if(search_sub_string("EQ_BACK_BSLASH", $options_in, $arr, null, 0) && !search_sub_string("!EQ_BACK_BSLASH", $options_in, $arr, null, 0))
				{
					//replace "&#92;" to '\'
					$return_result = replace_sub_string("&#92;", "\\", $return_result, -1);
				}
			}
			
			//** if option EQ_NO_RN
			if(search_sub_string("EQ_NO_RN", $options_in, $arr, null, 0) && !search_sub_string("!EQ_NO_RN", $options_in, $arr, null, 0))
			{
				//replace "\r\n|\n\r|\r|\n" to ''
				$return_result = replace_sub_string("\r\n|\n\r|\r|\n", '', $return_result, -1);
			}
			
			//** if option EQ_NO_BR
			if(search_sub_string("EQ_NO_BR", $options_in, $arr, null, 0) && !search_sub_string("!EQ_NO_BR", $options_in, $arr, null, 0))
			{
				//replace "<br \/>|<br>" to ''
				$return_result = replace_sub_string("<br \/>|<br>", '', $return_result, -1);
			}
			
			//** if option EQ_NO_BSP
			if(search_sub_string("EQ_NO_BSP", $options_in, $arr, null, 0) && !search_sub_string("!EQ_NO_BSP", $options_in, $arr, null, 0))
			{
				//replace "^\s*|\s*$" to ''
				$return_result = replace_sub_string("^\s*|\s*$", '', $return_result, -1);
			}
			
			//** if option EQ_NO_BTAB
			if(search_sub_string("EQ_NO_BTAB", $options_in, $arr, null, 0) && !search_sub_string("!EQ_NO_BTAB", $options_in, $arr, null, 0))
			{
				//replace "^\t*|\t*$" to ''
				$return_result = replace_sub_string("^\t*|\t*$", '', $return_result, -1);
			}
			
			//** if option EQ_NO_BSQ
			if(search_sub_string("EQ_NO_BSQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_NO_BSQ", $options_in, $arr, null, 0))
			{
				if(string_check_bsq($return_result, null))
				{
					//replace "^\\\'|\\\'$|^\'|\'$" to ''
					$return_result = replace_sub_string("^\\\'|\\\'$|^\'|\'$", '', $return_result, -1);
				}
			}
			
			//** if option EQ_NO_BDQ
			if(search_sub_string("EQ_NO_BDQ", $options_in, $arr, null, 0) && !search_sub_string("!EQ_NO_BDQ", $options_in, $arr, null, 0))
			{
				if(string_check_bdq($return_result, null))
				{
					//replace "^\\\"|\\\"$|^\"|\"$" to ''
					$return_result = replace_sub_string("^\\\"|\\\"$|^\"|\"$", '', $return_result, -1);
				}
			}
			
			//** if option EQ_TRIM
			if(search_sub_string("EQ_TRIM", $options_in, $arr, null, 0) && !search_sub_string("!EQ_TRIM", $options_in, $arr, null, 0))
			{
				$return_result = trim($return_result);
			}
			
			//** if option EQ_BACK_SHIELD
			if(search_sub_string("EQ_BACK_SHIELD", $options_in, $arr, null, 0) && !search_sub_string("!EQ_BACK_SHIELD", $options_in, $arr, null, 0))
			{
				//stripslashes
				$return_result = stripslashes($return_result);
			}
			else
			{
				//shielding chars
				$return_result = string_shielding_chars($return_result, $options_in);
			}
		}
	}
	
	return $return_result;
}


/*	Function: encode message.
*
*	Input:
*			$str_in				- a string;	[STRING]
*			$from_encoding_in	- the original character encoding;	[STRING]
*			$to_encoding_in		- the tarfer character encoding.	[STRING]
*
*	Output:
*			encoded string or NULL.	[STRING || NULL]
*
*	Note:
*
*			required library "php-mbstring"!
*
*/
function string_encoding($str_in = null, $from_encoding_in = null, $to_encoding_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check input argument $str_in
	if(!is_string($str_in))
	{
		return null;
	}
	
	//Check function iconv()
	if(!function_exists("iconv"))
	{
		if($FL_DEBUG)
		{
			echo("#error#Error! Function 'iconv()' not exists! [".(basename(__FILE__)).(" -> ").(__FUNCTION__).(" ").(__LINE__)."]");
		}
		return $str_in;
	}
	
	//Check input argument $from_encoding_in
	if(!is_string($from_encoding_in))
	{
		return $str_in;
	}
	
	//Check input argument $to_encoding_in
	if(!is_string($to_encoding_in))
	{
		return $str_in;
	}
	
	//* target encoding	[STRING || NULL]
	$to_encoding = trim($to_encoding_in);
	
	
	if(empty($to_encoding))
	{
		return $str_in;
	}
	
	//* original encoding	[STRING || NULL]
	$from_encoding	= trim($from_encoding_in);
	
	
	if(empty($from_encoding))
	{
		return $str_in;
	}
	
	if(strtolower($from_encoding) == strtolower($to_encoding))
	{
		return $str_in;
	}
	
	return ((function_exists("mb_convert_encoding")) ? mb_convert_encoding($str_in, $to_encoding, $from_encoding) : iconv($from_encoding, $to_encoding, $str_in));
}


//** CLASSES


//** INITIALIZATION OF GLOBAL VARIABLES


?>
