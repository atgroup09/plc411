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
*    Copyright (C) 2010 - 2013  ATgroup09 (atgroup09@gmail.com)
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
*			-- $FL_DEBUG - on/off debug messages.
*
*
*		- libraries: none.
*/


/*	Global variables: none.
*
*
*	Functions:
*
*		*** search substring ***
*		search_sub_string($re_pattern_in, $src_string_in, &$array_matches_in, $flags_in, $offset_in)
*
*		*** replacement the substring for the pattern ***
*		replace_sub_string($re_pattern_in, $replacement_in, $src_string_in, $limit_in)
*
*		*** split the string ***
*		split_sub_string($re_pattern_in, $src_string_in, $limit_in, $flags_in)
*
*		*** check the value by the mask ***
*		check_value_by_mask($mask_in, $value_in)
*
*
*	Classes: none.
*
*
*	Initialization of global variables: none.
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function:	search the substring.
*	Input:
*				$re_pattern_in  	- pattern (regexp),	[STRING]
*				$src_string_in		- source string,	[STRING]
*				$array_matches_in	- array of all matches in multi-dimensional array ordered according to flags or null,	[ARRAY || NULL]
*				$flags_in			- flags or null,	[INTEGER || NULL]
*				$offset_in			- offset (in bytes) or null.	[INTEGER || NULL]
*				
*	Output:
*				number of matches.	[INTEGER]
*	Note:
*
*					- PREG_PATTERN_ORDER	- orders results so that $array_matches_in[0] is
*												an array of full pattern matches, $array_matches_in[1]
*												is an array of strings matched by the first parenthesized
*												subpattern, and so on;
*					- PREG_SET_ORDER		- orders results so that $array_matches_in[0] is an array of
*												first set of matches, $array_matches_in[1] is an array
*												of second set of matches, and so on;
*					- PREG_OFFSET_CAPTURE	- if this flag is passed, for every occurring match the appendant
*												string offset will also be returned; note that this changes
*												the value of matches into an array where every element is
*												an array consisting of the matched string at offset 0 and
*												its string offset into source at offset 1.
*
*					Offset can be used to specify the alternate place from which to start the search (in bytes).
*/
function search_sub_string($re_pattern_in = null, $src_string_in = null, &$array_matches_in, $flags_in = null, $offset_in = null)
{
	//* flags	[INTEGER]
	$flags	= 0;
	
	//* offset	[INTEGER]
	$offset	= 0;
	
	
	//Check input arguments
	if(is_integer($flags_in))
	{
		if($flags_in > 0)
		{
			$flags = $flags_in;
		}
	}
	
	if(is_integer($offset_in))
	{
		if($offset_in > 0)
		{
			$offset = $offset_in;
		}
	}
	
	if(is_string($re_pattern_in) && is_string($src_string_in))
	{
		return preg_match_all("/{$re_pattern_in}/", $src_string_in, $array_matches_in, $flags, $offset);
	}
	
	return 0;
}


/*	Function:	replacement the substring for the pattern.
*	Input:
*				$re_pattern_in  - pattern (regexp),				[STRING]
*				$replacement_in	- new value of substring,		[STRING]
*				$src_string_in	- source string,				[STRING]
*				$limit_in		- maximum possible replacements	[INTEGER || NULL]
*									for each pattern in each
*									subject string (-1 by default - no limit).
*	Output:
*				new string.	[STRING]
*/
function replace_sub_string($re_pattern_in = null, $replacement_in = null, $src_string_in = null, $limit_in = null)
{
	//* limit	[INTEGER]
	$limit = -1;
	
	
	//Check input arguments
	if(is_integer($limit_in))
	{
		if(!empty($limit_in))
		{
			$limit = $limit_in;
		}
	}
	
	if(is_string($re_pattern_in) && is_string($replacement_in) && is_string($src_string_in))
	{
		return preg_replace("/{$re_pattern_in}/", $replacement_in, $src_string_in, $limit);
	}
	
	return $src_string_in;
}


/*	Function:	split the string.
*	Input:
*				$re_pattern_in  - pattern (regexp),				[STRING]
*				$src_string_in	- source string,				[STRING]
*				$limit_in		- maximum possible replacements	[INTEGER || NULL]
*									for each pattern in each
*									subject string (-1 by default - no limit);
*				$flags_in		- flags or null.	[INTEGER || NULL]
*	Output:
*				array containing substrings of subject split along boundaries matched by pattern or empty array.	[ARRAY]
*	Note:
*
*					- PREG_SPLIT_NO_EMPTY		- only non-empty pieces,
*					- PREG_SPLIT_DELIM_CAPTURE	- parenthesized expression in the delimiter pattern
*													will be captured and returned as well,
*					- PREG_SPLIT_OFFSET_CAPTURE	- if this flag is set, for every occurring match
*													the appendant string offset will also be returned;
*													note that this changes the return value in an array
*													where every element is an array consisting of
*													the matched string at offset 0 and its string offset
*													into source at offset 1.
*
*				Example:
*
*					$array = split_sub_string($re_pattern_in, $src_string_in, $limit_in, PREG_SPLIT_NO_EMPTY | PREG_SPLIT_DELIM_CAPTURE);
*/
function split_sub_string($re_pattern_in = null, $src_string_in = null, $limit_in = null, $flags_in = null)
{
	//* limit	[INTEGER]
	$limit	= -1;
	
	//* flags	[INTEGER]
	$flags	= 0;
	
	
	//Check input arguments
	if(is_integer($limit_in))
	{
		if(!empty($limit_in))
		{
			$limit = $limit_in;
		}
	}
	
	if(is_integer($flags_in))
	{
		if($flags_in > 0)
		{
			$flags = $flags_in;
		}
	}
	
	if(is_string($re_pattern_in) && is_string($src_string_in))
	{
		return preg_split("/{$re_pattern_in}/", $src_string_in, $limit, $flags);
	}
	
	return array();
}


/*	Function:	check the value by the mask.
*	Input:
*				$mask_in	- mask,		[STRING]
*				$value_in	- value.	[STRING]
*	Output:
*				result:	[BOOLEAN]
*					- true  - mask match the value,
*					- false - mask does not match the value.
*	Note:
*
*				In the mask can contain all possible values (regexp string) and "all" (the value of "all" allows all values).
*
*				The values in mask may be used the prefix '!' (not used for value of "all").
*
*				If used value of "all":
*					- return true:
*						-- if the mask does not match the value,
*						-- if the mask match the value;
*					- return false:
*						-- if the mask match the value, but value in mask contain the prefix '!'.
*
*
*				Example 1:
*
*						mask_in = "info";
*					   value_in = "info";
*
*						//** result - true ("info" == "info").
*
*
*				Example 2:
*
*						mask_in = "!info";
*					   value_in = "info";
*
*						//** result - false (mask contain the prefix '!').
*
*
*				Example 3:
*
*						mask_in = "all|info";
*					   value_in = "error";
*
*						//** result - true (used "all").
*
*
*				Example 4:
*
*						mask_in = "all|!info";
*					   value_in = "info";
*
*						//** result - false (used "all", but "info" with the prefix '!').
*
*
*				Example 5:
*
*						mask_in = "error|info";
*					   value_in = "warning";
*
*						//** result - false (mask does not match the value).
*
*
*				Example 6:
*
*						mask_in = "!error|!info|all";
*					   value_in = "warning";
*
*						//** result - true (used "all" and value not "error" and not "info").
*
*
*				Example 7:
*
*						mask_in = "^entry[0-9]*$|all|!entry1";
*					   value_in = "entry2";
*
*						//** result - true (used "all" and value not "!entry1" and suitable by mask "^entry[0-9]*$").
*/
function check_value_by_mask($mask_in = null, $value_in = null)
{
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'search_sub_string()' not exists! [regexp/regexp.php -> check_value_by_mask()]");
		}
		return false;
	}
	
	//Check input arguments
	if(empty($mask_in))
	{
		return false;
	}
	
	if(empty($value_in))
	{
		return false;
	}
	
	//** if the mask does not match the value and the mask not contain of "all", then exit with false
	if(!search_sub_string($mask_in, $value_in, $regs, null, null) && !search_sub_string($mask_in, "all", $regs, null, null))
	{
		return false;
	}
	
	//** if the mask match the value, but value in mask contain the prefix '!', then exit with false
	if(search_sub_string("!{$value_in}", $mask_in, $regs, null, null))
	{
		return false;
	}
	
	return true;
}


//CLASSES


?>
