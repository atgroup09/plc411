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


/*   Library: functions.
*
*    Copyright (C) 2012  ATgroup09 (atgroup09@gmail.com)
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
*		*** check required functions ***
*		functions_check_required($func_names_in = null, $src_file_in = null, $src_target_in = null)
*
*
*	Classes: none.
*
*
*	Initialization of global variables: none.
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function:	check required functions.
*	Input:
*				$func_names_in	- array of required functions names;	[ARRAY]
*				$src_file_in	- source file name or NULL;	[STRING || NULL]
*				$src_target_in	- source target (function, class ...) name or NULL.	[STRING || NULL]
*
*	Output:
*				return boolean true if all required functions are exists, otherwise false.	[BOOLEAN]
*
*	Note:
*
*/
function functions_check_required($func_names_in = null, $src_file_in = null, $src_target_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check input argument $func_names_in
	if(!is_array($func_names_in))
	{
		return false;
	}
	
	//Check required functions
	for($i=0; $i<count($func_names_in); $i++)
	{
		if(!is_string($func_names_in[$i]))
		{
			continue;
		}
		
		if(empty($func_names_in[$i]))
		{
			continue;
		}
		
		if(!function_exists($func_names_in[$i]))
		{
			if($FL_DEBUG)
			{
				//* output info	[STRING]
				$msg = ("#error#Error! Function '").($func_names_in[$i]).("()' not exists!");
				
				//* source file name	[STRING]
				$src_file = ((is_string($src_file_in)) ? $src_file_in : '');
				
				//* source target (function, class ...) name	[STRING]
				$src_target = ((is_string($src_target_in)) ? $src_target_in : '');
				
				
				if(!empty($src_file) || !empty($src_target))
				{
					$msg.= '[';
					
					if(!empty($src_file))
					{
						$msg.= $src_file;
					}
					
					if(!empty($src_target))
					{
						$msg.= " -> {$src_target}";
					}
					
					$msg.= ']';
				}
				
				echo($msg);
			}
			return false;
		}
	}
	
	return true;
}


//** CLASSES


//** INITIALIZATION OF GLOBAL VARIABLES


?>
