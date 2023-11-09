<?php

/*	PHP SCRIPT DOCUMENT
*	UTF-8
*/

/*   Module: Server side responder (includes) - Departments.
*
*    Copyright (C) 2019  ATgroup09 (atgroup09@gmail.com)
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


/*	Global variables:
*
*		*** main responder ***
*		$MAIN_RESPONDER
*
*
*	Functions: none.
*
*	Classes: undefined.
*/


/*	Dependencies:
*
*		- global variables: none.
*
*
*		- libraries:
*
*			+ types/types.php:
*				types_checking_existence().
*
*
*		- modules:
*
*			+ mod_workstation/responder.php:
*				abstract class responder.
*
*			+ global.php:
*				$G_SYSCONFIG_FILE;
*				$G_SYSCONFIG_NAME;
*				$G_DATASOURCE_TYPE;
*				$G_DATASOURCE_NAME.
*/


//INCLUDE LIBRARIES

include "../../lib/php/regexp/regexp.php";
include "../../lib/php/request/request.php";
include "../../lib/php/types/functions.php";
include "../../lib/php/types/string.php";
include "../../lib/php/types/types.php";
include "../../lib/php/dom/dom.php";
include "../../lib/php/sql/sql.php";
include "../../lib/php/db/mysql.php";
include "../../lib/php/db/mysql-table.php";
include "../../lib/php/datasources/ds.php";
include "../../lib/php/datasources/datasource.php";
include "../../lib/php/datasources/sysconfig.php";
include "../../lib/php/res/values.php";

//INCLUDE MODULES

include "../../global.php";
include "../responder.php";
include "../dbtable.php";
include "dbtable.php";
include "resp-class.php";


//GLOBAL VARIABLES

$MAIN_RESPONDER = null;


//FUNCTIONS


//CLASSES


//MAIN

if(function_exists("types_checking_existence"))
{
	$_rqt = array(array("name" => "responder", "type" => "class"),
				  array("name" => "Resp", "type" => "class")
				  );
	
	if(types_checking_existence($_rqt, "[index.php]"))
	{
		if(isset($G_SYSCONFIG_FILE) && isset($G_SYSCONFIG_NAME) && isset($G_DATASOURCE_TYPE) && isset($G_DATASOURCE_NAME) && isset($G_RES_VALUES_DIR))
		{
			if(is_string($G_SYSCONFIG_FILE))
			{
				$_resValuesDir	= ((is_string($G_RES_VALUES_DIR)) ? "../../".($G_RES_VALUES_DIR) : null);
				$MAIN_RESPONDER	= new Resp("../../".($G_SYSCONFIG_FILE), $G_SYSCONFIG_NAME, $G_DATASOURCE_TYPE, $G_DATASOURCE_NAME, $_resValuesDir);
			}
		}
		
		if(!is_object($MAIN_RESPONDER))
		{
			$MAIN_RESPONDER = new Resp();
		}
		
		$MAIN_RESPONDER->start();
	}
}
else
{
	if($FL_DEBUG) echo("#error#Error! Function 'types_checking_existence()' is undefined! [index.php]");
}

?>
