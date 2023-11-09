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


/*   Library: datasource parameters.
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
*				~ get_attribute_of_element(),
*				~ phpDOM_check_node(),
*				~ phpDOM_parsing(),
*				~ phpDOM_attach_node(),
*				~ phpDOM_remove_node(),
*				~ phpDOM_forming_node(),
*				~ phpDOM_get_values_of_nodes_by_params(),
*				~ phpDOM_get_root_node_from_string(),
*				~ phpDOM_get_root_node_from_file(),
*				~ phpDOM_write_document_to_file().
*
*			+ sql/sql.php:
*				~ sql_where(),
*				~ sql_insert(),
*				~ sql_update(),
*				~ sql_delete().
*
*			+ datasources/ds.php:
*				~ ds_search_nodes_by_key_args(),
*				~ ds_get_key_args_from_node(),
*				~ ds_get_db_object(),
*				~ ds_get_key_args_from_db(),
*				~ ds_get_repository_file_name_by_target_id(),
*				~ ds_get_repository_table_name_by_target_id(),
*				~ ds_check_datasource_params().
*/


/*	Global variables: none.
*
*
*	Functions:
*
*		*** check parameters of datasource ***
*		datasource_check_params($ds_params_in = null)
*
*		*** normalize parameters of datasource ***
*		datasource_normalize_params(&$ds_params_in)
*
*		*** get new array with default parameters of datasource ***
*		datasource_new_params($ds_name_in = "undefined", $ds_type_in = "xml")
*
*		*** get list of datasources names from root-node ***
*		datasource_get_names_from_node($root_node_in = null)
*
*		*** search node of datasource in root-node ***
*		datasource_search_node($root_node_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
*
*		*** search node "tables" ***
*		datasource_search_tables_node(&$ds_node_in = null)
*
*		*** search node "files" ***
*		datasource_search_files_node(&$ds_node_in = null)
*
*		*** get array of tables from datasource node ***
*		datasource_get_tables_from_node($ds_node_in = null)
*
*		*** get array of files from datasource node ***
*		datasource_get_files_from_node($ds_node_in = null)
*
*		*** get datasource from root-node ***
*		datasource_get_from_node($root_node_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
*
*		*** add (or update) tables into datasource node ***
*		datasource_add_tables_into_node(&$ds_node_in = null, $tables_params_in = null)
*
*		*** add (or update) files into datasource node ***
*		datasource_add_files_into_node(&$ds_node_in = null, $files_params_in = null)
*
*		*** add (or update) a datasource into root-node ***
*		datasource_add_into_node(&$root_node_in, &$ds_params_in = null)
*
*		*** remove datasource from root-node ***
*		datasource_remove_from_node(&$root_node_in, $ds_name_in = "undefined", $ds_type_in = "xml")
*
*		*** get list of datasources names from XML-file ***
*		datasource_get_names_from_file($file_in = null)
*
*		*** get datasource from XML-file ***
*		datasource_get_from_file($file_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
*
*		*** add (or update) datasource into XML-file ***
*		datasource_add_into_file($file_in = null, $root_node_name_in = null, &$ds_params_in = null)
*
*		*** remove datasource from XML-file ***
*		datasource_remove_from_file($file_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
*
*		*** get list of datasources names from database ***
*		datasource_get_names_from_db($connect_params_in = null)
*
*		*** get datasource from database ***
*		datasource_get_from_db($connect_params_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
*
*		*** get string from content of node "tables" ***
*		datasource_tables_node_to_string($tables_params_in = null)
*
*		*** get string from content of node "files" ***
*		datasource_files_node_to_string($files_params_in = null)
*
*		*** add (or update) datasource into database ***
*		datasource_add_into_db($connect_params_in = null, &$ds_params_in = null)
*
*		*** remove datasource from database ***
*		datasource_remove_from_db($connect_params_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
*
*
*	Classes:
*
*		- datasource.
*
*
*	Array of parameters:
*
*	* default:
*
*		- ["added_on"]			- date and time of publication;					[DATETIME]
*		- ["updated_on"]		- date and time of modification;				[DATETIME]
*		- ["state"]				- state:										[INTEGER]
*									-- 0 - unused (by default),
*									-- 1 - used,
*									-- 2 - removed;
*		- ["name"]				- (!) datasource name;							[STRING]
*		- ["type"]				- (!) datasource type:							[STRING]
*									-- "xml" (by default),
*									-- "db";
*		- ["note"]				- note/description (null by default);			[STRING || NULL]
*
*	** for type "xml":
*
*		- ["file"]				- file name (null or files[0] by default)		[STRING || NULL]
*		- ["files"]				- (!) list of files:							[ARRAY]
*									-- ["identifier of file"]["type"] = "type of the file",
*									-- ["identifier of file"]["path"] = "path to the file",
*										...;
*
*	** for type "db":
*
*		- ["db_type"]			- (!) database type ("mysql" by default);		[STRING]
*		- ["hostname"]			- (!) host name ("localhost" by default);		[STRING]
*		- ["port"]				- port number (3306 by default);				[INTEGER]
*		- ["database"]			- database name (null by default);				[STRING || NULL]
*		- ["table"]				- table name (null or tables[0] by default);	[STRING || NULL]
*		- ["tables"]			- list of tables:								[ARRAY]
*									-- ["identifier of table"] = "table name",
*										...;
*		- ["user"]				- (!) user name;								[STRING]
*		- ["password"]			- user password (null by default);				[STRING || NULL]
*		- ["characters_coding"]	- characters coding ("utf8" by default).		[STRING || NULL]
*
*	* for database:
*
*		- ["id"]				- group identifier (NULL  by default);			[INTEGER || NULL]
*		- ["added_by"]			- user ID who added data (NULL  by default);	[INTEGER || NULL]
*		- ["updated_by"]		- user ID who updated data (NULL  by default).	[INTEGER || NULL]
*
*		(!) - required parameters!
*
*
*	Node:
*
*	* for type "xml":
*
*		<datasource name="xml-connector" type="xml" state="1">
*			<added_on>2012-09-19 20:27:55</added_on>
*			<updated_on>2012-09-19 20:27:55</updated_on>
*			<file>file name</file>
*			<files>
*				<file id="test" type="xml">test.xml</file>
*				...
*			</files>
*			<note>note</note>
*		</datasource>
*
*	* for type "db":
*
*		<datasource name="mysql-test" type="db" state="1">
*			<added_on>2012-09-19 20:30:35</added_on>
*			<updated_on>2012-09-19 20:30:35</updated_on>
*			<db_type>mysql</db_type>
*			<hostname>localhost</hostname>
*			<port>3306</port>
*			<database>test</database>
*			<table>table name</table>
*			<user>test_user</user>
*			<password>Abc</password>
*			<characters_coding>utf8</characters_coding>
*			<tables>
*				<table id="list_contacts">list_contacts</tables>
*				...
*			</tables>
*			<note>note</note>
*		</datasource>
*
*
*	Database table:
*
*		--
*		-- Table structure `list_datasources`
*		--
*
*		DROP TABLE IF EXISTS `list_datasources`;
*
*		CREATE TABLE `list_datasources` (
*			  `datasource_id`        bigint(20) unsigned NOT NULL AUTO_INCREMENT,                                -- identifier
*			  `added_on`  	         datetime NOT NULL DEFAULT '0000-00-00 00:00:00',                            -- date and time of publication
*			  `added_by`  	         bigint(20) unsigned DEFAULT NULL,                                           -- author of publication (identifier of user)
*			  `updated_on`           timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,   -- date and time of modification (timestamp)
*			  `updated_by`  	     bigint(20) unsigned DEFAULT NULL,                                           -- author of publication (identifier of user)
*			  `state`                tinyint(1) unsigned DEFAULT '0',                                            -- state (0 - hidden/unused, 1 - showed/used, 2 - for remove)
*			  `type`                 tinytext,                                                                   -- datasource type (xml, db)
*			  `name`                 tinytext,                                                                   -- datasource name
*			  `file`                 tinytext,                                                                   -- XML-type: file name
*			  `files`                text,                                                                       -- XML-type: xml-structure of list of files (<files><file id="test" type="xml">test.xml</file>...</files>)
*			  `db_type`              tinytext,                                                                   -- DB-type: type (mysql, ...)
*			  `hostname`             tinytext,                                                                   -- DB-type: hostname
*			  `port`                 tinytext,                                                                   -- DB-type: port number
*			  `database`             tinytext,                                                                   -- DB-type: database name
*			  `table`                tinytext,                                                                   -- DB-type: table name
*			  `tables`               text,                                                                       -- DB-type: xml-structure of list of tables (<tables><table id="list_contacts">list_contacts</table>...</tables>)
*			  `user`                 tinytext,                                                                   -- DB-type: user name
*			  `password`             tinytext,                                                                   -- DB-type: password
*			  `characters_coding`    tinytext,                                                                   -- characters coding
*			  `note`                 tinytext,                                                                   -- note
*			  PRIMARY KEY (`datasource_id`),
*			  KEY          `added_on_k` (`added_on`),
*			  KEY          `added_by_k` (`added_by`),
*			  KEY          `updated_on_k` (`updated_on`),
*			  KEY          `updated_by_k` (`updated_by`),
*			  KEY          `state_k` (`state`),
*			  KEY          `type_k` (`type`(4)),
*			  KEY          `name_uk` (`name`(8)),
*			  KEY          `db_type_k` (`db_type`(4)),
*			  KEY          `hostname_k` (`hostname`(8)),
*			  KEY          `database_k` (`database`(8)),
*			  KEY          `table_k` (`table`(8)),
*			  KEY          `user_k` (`user`(8))
*			) ENGINE=InnoDB DEFAULT CHARSET=utf8;
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function: check parameters of a datasource.
*
*	Input:	
*			$ds_params_in - parameters of a datasource.	[ARRAY]
*
*	Output:
*			return boolean true if required parameters are correct, otherwise false.	[BOOLEAN]
*
*	Note:
*
*			next parameters are required: name, type, file (*), files (*), hostname (**), user (**)!
*				*  - for the type "xml",
*				** - for the type "db".
*
*/
function datasource_check_params($ds_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the input argument $ds_params_in
	if(!is_array($ds_params_in))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the input argument 'ds_params_in'! [datasource.php -> datasource_check_params()]");
		}
		return false;
	}
	
	//Check required parameters
	if(empty($ds_params_in["name"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the datasource parameter 'name'! [datasource.php -> datasource_check_params()]");
		}
		return false;
	}
	
	if(!is_string($ds_params_in["name"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the datasource parameter 'name' (not a string)! [datasource.php -> datasource_check_params()]");
		}
		return false;
	}
	
	if(empty($ds_params_in["type"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the datasource parameter 'type'! [datasource.php -> datasource_check_params()]");
		}
		return false;
	}
	
	if(!is_string($ds_params_in["type"]))
	{
		if($FL_DEBUG)
		{
			echo("Error! Undefined the datasource parameter 'type' (not a string)! [datasource.php -> datasource_check_params()]");
		}
		return false;
	}
	
	//Check the parameter "type"
	switch($ds_params_in["type"])
	{
		case "xml":
		case "Xml":
		case "XML":
			
			if(!empty($ds_params_in["file"]))
			{
				if(is_string($ds_params_in["file"]))
				{
					return true;
				}
			}
			
			if(isset($ds_params_in["files"]))
			{
				if(is_array($ds_params_in["files"]))
				{
					return true;
				}
			}
			
			if($FL_DEBUG)
			{
				echo("Error! Undefined the datasource parameter 'file' or 'files'! [datasource.php -> datasource_check_params()]");
			}
			
			break;
		
		case "db":
		case "Db":
		case "DB":
			
			if(!empty($ds_params_in["hostname"]) && !empty($ds_params_in["user"]))
			{
				if(is_string($ds_params_in["hostname"]) && is_string($ds_params_in["user"]))
				{
					return true;
				}
			}
			
			if($FL_DEBUG)
			{
				echo("Error! Undefined the datasource parameter 'hostname' and/or 'user'! [datasource.php -> datasource_check_params()]");
			}
			
			break;
		
		default:
			
			if($FL_DEBUG)
			{
				echo(("Error! Incorrect type '").($ds_params_in["type"]).("' of the datasource! [datasource.php -> datasource_check_params()]"));
			}
			
			break;
	}
	
	return false;
}


/*	Function: normalize parameters of datasource.
*
*	Input:	
*			$ds_params_in - link to parameters of datasource.	[ARRAY]
*
*	Output:
*			return boolean true if datasource parameters normalized, otherwise false.	[BOOLEAN]
*
*	Note:
*			
*/
function datasource_normalize_params(&$ds_params_in)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function types_normalize_array_value()
	if(!function_exists("types_normalize_array_value"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'types_normalize_array_value()' not exists! [datasource.php -> datasource_normalize_params()]");
		}
		return false;
	}
	
	//Check input argument $ds_params_in
	if(!is_array($ds_params_in))
	{
		return false;
	}
	
	//Check option "type"
	if(empty($ds_params_in["type"]))
	{
		$ds_params_in["type"] = "xml";
	}
	
	if(!is_string($ds_params_in["type"]))
	{
		$ds_params_in["type"] = "xml";
	}
	
	//* array of group parameters	[ARRAY]
	$main_params = array(array("key" => "id",                "type" => "int",    "default" => null),
	                     array("key" => "added_on",          "type" => "string", "default" => date("Y-m-d H:i:s")),
	                     array("key" => "added_by",          "type" => "int",    "default" => null),
						 array("key" => "updated_on",        "type" => "string", "default" => date("Y-m-d H:i:s")),
						 array("key" => "updated_by",        "type" => "int",    "default" => null),
						 array("key" => "state",             "type" => "int",    "default" => 0),
						 array("key" => "name",  	         "type" => "string", "default" => "undefined"),
						 array("key" => "type",  	         "type" => "string", "default" => "xml"),
						 array("key" => "note",              "type" => "string", "default" => null)
					    );
	
	switch($ds_params_in["type"])
	{
		case "db":
		case "Db":
		case "DB":
			
			array_push($main_params, array("key" => "db_type",           "type" => "string", "default" => "mysql"));
			array_push($main_params, array("key" => "hostname",          "type" => "string", "default" => "localhost"));
			array_push($main_params, array("key" => "port",              "type" => "int",    "default" => 3306));
			array_push($main_params, array("key" => "database",          "type" => "string", "default" => null));
			array_push($main_params, array("key" => "table",             "type" => "string", "default" => null));
			array_push($main_params, array("key" => "tables",            "type" => "array",  "default" => array()));
			array_push($main_params, array("key" => "user",              "type" => "string", "default" => null));
			array_push($main_params, array("key" => "password",          "type" => "string", "default" => null));
			array_push($main_params, array("key" => "characters_coding", "type" => "string", "default" => "utf8"));
			
			break;
		
		default:
			
			array_push($main_params,array("key" => "file",              "type" => "string", "default" => null));
			array_push($main_params,array("key" => "files",             "type" => "array",  "default" => array()));
			
			break;
	}
	
	//Normalizing main parameters
	for($i=0; $i<count($main_params); $i++)
	{
		types_normalize_array_value($main_params[$i], $ds_params_in);
	}
	
	return true;
}


/*	Function: get new array with default parameters of datasource.
*
*	Input:	
*			$ds_name_in	- datasource name ("undefined" by default),	[STRING || NULL]
*			$ds_type_in	- datasource type:	[STRING || NULL]
*							-- "xml" (by default),
*							-- "db".
*
*	Output:
*			new array with default parameters of datasource.	[ARRAY]
*
*	Note:
*
*/
function datasource_new_params($ds_name_in = "undefined", $ds_type_in = "xml")
{
	//* the returned result	[ARRAY]
	$returned_result = array("name" => "undefined", "type" => "xml");
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function datasource_normalize_params()
	if(!function_exists("datasource_normalize_params"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'datasource_normalize_params()' not exists! [datasource.php -> datasource_new_params()]");
		}
		return $returned_result;
	}
	
	//Check the input argument $ds_name_in
	if(!empty($ds_name_in))
	{
		if(is_string($ds_name_in))
		{
			$returned_result["name"] = $ds_name_in;
		}
	}
	
	//Check the input argument $ds_type_in
	if(!empty($ds_type_in))
	{
		if(is_string($ds_type_in))
		{
			$returned_result["type"] = $ds_type_in;
		}
	}
	
	//Normalize parameters of a datasource
	datasource_normalize_params($returned_result);
	
	return $returned_result;
}


/*	Function: get list of datasources names from root-node.
*
*	Input:	
*			$root_node_in - root-node object.	[OBJECT]
*
*	Output:
*			list of datasource names.	[ARRAY]
*
*	Note:
*
*			structure of list of datasources names:
*
*				list[0]["name"] = "datasource name",
*				list[0]["type"] = "datasource type",
*				...
*				list[N]["name"] = "datasource name",
*				list[N]["type"] = "datasource type".
*
*/
function datasource_get_names_from_node($root_node_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function ds_get_key_args_from_node()
	if(!function_exists("ds_get_key_args_from_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_get_key_args_from_node()' not exists! [datasource.php -> datasource_get_names_from_node()]");
		}
		return array();
	}
	
	//* node name of datasource	[STRING]
	$nodename		= "datasource";
	
	//* description of datasource parameters	[ARRAY]
	$desc_params	= array("name" =>
								array("key"             => "name",
									  "field"           => "name",
									  "attrname"        => "name",
									  "type"            => "string",
									  "default"         => "undefined",
									  "required"		=> true,
									  "if_key_arg"		=> true,
									  "key_arg_value"	=> null
									  ),
							"type" =>
								array("key"             => "type",
									  "field"           => "type",
									  "attrname"        => "type",
									  "type"            => "string",
									  "default"         => "xml",
									  "required"		=> true,
									  "if_key_arg"		=> true,
									  "key_arg_value"	=> null
									  )
							);
	
	
	return ds_get_key_args_from_node($root_node_in, $nodename, $desc_params);
}


/*	Function: search datasource node in root-node.
*
*	Input:
*			$root_node_in	- root-node object;	[OBJECT]
*			$ds_name_in		- datasource name ("undefined" by default);	[STRING || NULL]
*			$ds_type_in		- datasource type:	[STRING || NULL]
*								-- "xml" (by default),
*								-- "db".
*
*	Output:
*			datasource node or null.	[OBJECT || NULL]
*
*	Note:
*
*/
function datasource_search_node($root_node_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function ds_search_nodes_by_key_args()
	if(!function_exists("ds_search_nodes_by_key_args"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_search_nodes_by_key_args()' not exists! [datasource.php -> datasource_search_node()]");
		}
		return null;
	}
	
	//* node name of datasource	[STRING]
	$nodename		= "datasource";
	
	//* description of datasource parameters	[ARRAY]
	$desc_params	= array("name" =>
								array("key"             => "name",
									  "field"           => "name",
									  "attrname"        => "name",
									  "type"            => "string",
									  "default"         => "undefined",
									  "required"		=> true,
									  "if_key_arg"		=> true,
									  "key_arg_value"	=> null
									  ),
							"type" =>
								array("key"             => "type",
									  "field"           => "type",
									  "attrname"        => "type",
									  "type"            => "string",
									  "default"         => "xml",
									  "required"		=> true,
									  "if_key_arg"		=> true,
									  "key_arg_value"	=> null
									  )
							);
	
	
	//Check the input argument $ds_name_in
	if(!empty($ds_name_in))
	{
		if(is_string($ds_name_in))
		{
			$desc_params["name"]["key_arg_value"] = $ds_name_in;
		}
	}
	
	//Check the input argument $ds_type_in
	if(!empty($ds_type_in))
	{
		if(is_string($ds_type_in))
		{
			$desc_params["type"]["key_arg_value"] = $ds_type_in;
		}
	}
	
	//* list of nodes	[ARRAY]
	$list_ds_nodes = ds_search_nodes_by_key_args($root_node_in, $nodename, $desc_params);
	
	
	//Check the list
	if(!is_array($list_ds_nodes))
	{
		return null;
	}
	
	if(!count($list_ds_nodes))
	{
		return null;
	}
	
	return $list_ds_nodes[0];
}


/*	Function: search node "tables".
*
*	Input:
*			$ds_node_in - link to datasource node.	[OBJECT]
*
*	Output:
*			node "tables" or NULL.	[OBJECT || NULL]
*
*	Note:
*
*			the function returns only the first matching node!
*
*			<tables>...</tables>
*
*			If the $ds_node_in is a link to a node object of a sysconfig without child-node "tables",
*				then will be created new node "tables" and attached into the $ds_node_in!
*
*/
function datasource_search_tables_node(&$ds_node_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_search_tables_node()]");
		}
		return null;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_parsing",
						 "phpDOM_attach_node",
						 "phpDOM_get_root_node_from_string"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_search_tables_node()"))
	{
		return null;
	}
	
	//* array of nodes "tables"	[ARRAY]
	$tables_nodes = phpDOM_parsing($ds_node_in, "^tables$", null, null);
	
	
	//Check the array
	if(is_array($tables_nodes))
	{
		if(count($tables_nodes))
		{
			return $tables_nodes[0];
		}
	}
	
	//* new node "tables"	[OBJECT || NULL]
	$tables_node = phpDOM_get_root_node_from_string("<tables></tables>", "XML");
	
	
	//Attach the node into $ds_node_in
	return phpDOM_attach_node($ds_node_in, $tables_node, "end");
}


/*	Function: search node "files".
*
*	Input:
*			$ds_node_in - link to datasource node.	[OBJECT]
*
*	Output:
*			node "files" of NULL.	[OBJECT || NULL]
*
*	Note:
*
*			the function returns only the first matching node!
*
*			<files>...</files>
*
*			If the $ds_node_in is a link to a node object of a sysconfig without child-node "files",
*				then will be created new node "files" and attached into the $ds_node_in!
*
*/
function datasource_search_files_node(&$ds_node_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_search_files_node()]");
		}
		return null;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_parsing",
						 "phpDOM_attach_node",
						 "phpDOM_get_root_node_from_string"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_search_files_node()"))
	{
		return null;
	}
	
	//* array of nodes "files"	[ARRAY]
	$files_nodes = phpDOM_parsing($ds_node_in, "^files$", null, null);
	
	
	//Check the array
	if(is_array($files_nodes))
	{
		if(count($files_nodes))
		{
			return $files_nodes[0];
		}
	}
	
	//* new node "files"	[OBJECT || NULL]
	$files_node = phpDOM_get_root_node_from_string("<files></files>", "XML");
	
	
	//Attach the node into $ds_node_in
	return phpDOM_attach_node($ds_node_in, $files_node, "end");
}


/*	Function: get array of tables from a node.
*
*	Input:
*			$ds_node_in - datasource node or node "tables".	[OBJECT]
*
*	Output:
*			array of tables.	[ARRAY]
*
*	Note:
*
*			structure of array of tables:
*
*				["identifier of table"] = "table name",
*				...
*
*/
function datasource_get_tables_from_node($ds_node_in = null)
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
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_get_tables_from_node()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("get_attribute_of_element",
						 "phpDOM_check_node",
						 "phpDOM_parsing",
						 "datasource_search_tables_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_get_tables_from_node()"))
	{
		return $returned_result;
	}
	
	//* node "tables"	[OBJECT || NULL]
	$tables_node = null;
	
	
	//Check input argument $ds_node_in
	if(phpDOM_check_node($ds_node_in, "^tables$", null, null))
	{
		$tables_node = $ds_node_in;
	}
	else
	{
		//search the node in $ds_node_in
		$tables_node = datasource_search_tables_node($ds_node_in);
	}
	
	//Check the node
	if(!$tables_node)
	{
		return $returned_result;
	}
	
	//* array of nodes "table"	[ARRAY]
	$table_nodes = phpDOM_parsing($tables_node, "^table$", "id", null);
	
	
	//Check the array
	if(is_array($table_nodes))
	{
		//* identifier of table	[STRING || NULL]
		$table_id = null;
		
		
		for($i=0; $i<count($table_nodes); $i++)
		{
			//check value of the node
			if(empty($table_nodes[$i]->nodeValue))
			{
				continue;
			}
			
			//get identifier of table
			$table_id = get_attribute_of_element($table_nodes[$i], "id");
			
			if($table_id)
			{
				$returned_result[$table_id] = $table_nodes[$i]->nodeValue;
			}
		}
	}
	
	return $returned_result;
}


/*	Function: get array of files from a node.
*
*	Input:
*			$ds_node_in - datasource node or node "files".	[OBJECT]
*
*	Output:
*			array of files.	[ARRAY]
*
*	Note:
*
*			structure of the array:
*
*				["identifier of file"]["type"] = "type of file",
*				["identifier of file"]["path"] = "path to file",
*				...
*
*/
function datasource_get_files_from_node($ds_node_in = null)
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
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_get_files_from_node()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("get_attribute_of_element",
						 "phpDOM_check_node",
						 "phpDOM_parsing",
						 "datasource_search_tables_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_get_files_from_node()"))
	{
		return $returned_result;
	}
	
	//* node of files	[OBJECT || NULL]
	$files_node = null;
	
	
	//Check input argument $ds_node_in
	if(phpDOM_check_node($ds_node_in, "^files$", null, null))
	{
		$files_node = $ds_node_in;
	}
	else
	{
		//search the node in $ds_node_in
		$files_node = datasource_search_files_node($ds_node_in);
	}
	
	//Check the node
	if(!$files_node)
	{
		return $returned_result;
	}
	
	//* array of nodes "file"	[ARRAY]
	$file_nodes = phpDOM_parsing($files_node, "^file$", "id", null);
	
	
	//Check the array
	if(is_array($file_nodes))
	{
		//* identifier of file	[STRING || NULL]
		$file_id	= null;
		
		//* type of file		[STRING || NULL]
		$file_type	= null;
		
		
		for($i=0; $i<count($file_nodes); $i++)
		{
			//check value of the node
			if(empty($file_nodes[$i]->nodeValue))
			{
				continue;
			}
			
			//get identifier of the file
			$file_id = get_attribute_of_element($file_nodes[$i], "id");
			
			//get type of the file
			$file_type = get_attribute_of_element($file_nodes[$i], "type");
			
			if($file_id && $file_type)
			{
				$returned_result[$file_id]["type"] = $file_type;
				$returned_result[$file_id]["path"] = $file_nodes[$i]->nodeValue;
			}
		}
	}
	
	return $returned_result;
}


/*	Function: get datasource from root-node.
*
*	Input:
*			$root_node_in	- root-node object;	[OBJECT]
*			$ds_name_in		- datasource name ("undefined" by default);	[STRING || NULL]
*			$ds_type_in		- datasource type:	[STRING || NULL]
*								-- "xml" (by default),
*								-- "db".
*
*	Output:
*			array of datasource parameters.	[ARRAY]
*
*	Note:
*
*/
function datasource_get_from_node($root_node_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
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
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_get_from_node()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_get_values_of_nodes_by_params",
						 "datasource_normalize_params",
						 "datasource_search_node",
						 "datasource_get_tables_from_node",
						 "datasource_get_files_from_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_get_from_node()"))
	{
		return $returned_result;
	}
	
	//* datasource name	[STRING]
	$ds_name	= "undefined";
	
	//* datasource type	[STRING]
	$ds_type	= "xml";
	
	
	//Check the input argument $ds_name_in
	if(!empty($ds_name_in))
	{
		if(is_string($ds_name_in))
		{
			$ds_name = $ds_name_in;
		}
	}
	
	//Check the input argument $ds_type_in
	if(!empty($ds_type_in))
	{
		if(is_string($ds_type_in))
		{
			$ds_type = $ds_type_in;
		}
	}
	
	//* datasource node	[OBJECT || NULL]
	$ds_node = datasource_search_node($root_node_in, $ds_name, $ds_type);
	
	
	//Check the node
	if(!$ds_node)
	{
		return $returned_result;
	}
	
	//* array of parameters extracted data	[ARRAY]
	$params_targets	= array(array("nodename" => "added_on", "type" => "string", "required" => false, "default_value" => date("Y-m-d H:i:s")),
							array("nodename" => "updated_on", "type" => "string", "required" => false, "default_value" => date("Y-m-d H:i:s")),
					 		array("nodename" => "state", "type" => "integer", "required" => false, "default_value" => 1),
					 		array("nodename" => "note", "type" => "string", "required" => false, "default_value" => null)
						   );
	
	//** additional parameters
	
	//* parameter name (tables of files)	[STRING || NULL]
	$ap_name		= null;
	
	//* parameter value	[ARRAY || NULL]
	$ap_value		= null;
	
	
	//Check datasource type
	switch($ds_type)
	{
		case "db":
		case "Db":
		case "DB":
			
			$ap_name  = "tables";
			$ap_value = datasource_get_tables_from_node($ds_node);
			
			array_push($params_targets, array("nodename" => "db_type", "type" => "string", "required" => false, "default_value" => "mysql"));
			array_push($params_targets, array("nodename" => "hostname", "type" => "string", "required" => false, "default_value" => "localhost"));
			array_push($params_targets, array("nodename" => "port", "type" => "integer", "required" => false, "default_value" => 3306));
			array_push($params_targets, array("nodename" => "database", "type" => "string", "required" => false, "default_value" => null));
			array_push($params_targets, array("nodename" => "table", "type" => "string", "required" => false, "default_value" => null));
			array_push($params_targets, array("nodename" => "user", "type" => "string", "required" => true));
			array_push($params_targets, array("nodename" => "password", "type" => "string", "required" => false, "default_value" => null));
			array_push($params_targets, array("nodename" => "characters_coding", "type" => "string", "required" => false, "default_value" => "utf8"));
			
			break;
			
		case "xml":
		case "Xml":
		case "XML":
			
			$ap_name  = "files";
			$ap_value = datasource_get_files_from_node($ds_node);
			
			array_push($params_targets, array("nodename" => "file", "type" => "string", "required" => false, "default_value" => null));
			
			break;
	}
	
	//* buffer	[ARRAY || NULL]
	$buff = phpDOM_get_values_of_nodes_by_params($ds_node, $params_targets);
	
	
	//Check the buffer
	if(is_array($buff))
	{
		if(count($buff))
		{
			//init the returned result
			$returned_result           = $buff;
			$returned_result["name"]   = $ds_name;
			$returned_result["type"]   = $ds_type;
			$returned_result[$ap_name] = $ap_value;
			
			//normalization of datasource parameters
			datasource_normalize_params($returned_result);
		}
	}
	
	return $returned_result;
}


/*	Function: add (or update) tables into datasource node.
*
*	Input:
*			$ds_node_in 		- link to datasource node;	[OBJECT]
*			$tables_params_in	- list of tables.	[ARRAY]
*
*	Output:
*			copy of node "tables" or NULL.	[OBJECT || NULL]
*
*	Note:
*
*/
function datasource_add_tables_into_node(&$ds_node_in = null, $tables_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_add_tables_into_node()]");
		}
		return null;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_forming_node",
						 "phpDOM_get_root_node_from_string",
						 "datasource_search_tables_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_add_tables_into_node()"))
	{
		return null;
	}
	
	//Check the input argument $tables_params_in
	if(!is_array($tables_params_in))
	{
		return null;
	}
	
	//* node "tables"	[OBJECT || NULL]
	$tables_node = datasource_search_tables_node($ds_node_in);
	
	
	//Check the node
	if(!$tables_node)
	{
		return null;
	}
	
	//* pattern for forming 	[ARRAY || NULL]
	$pattern_for_forming = array("tables" => array("attach_node" => null, "attach_position" => "replace_all"));
	
	
	foreach($tables_params_in as $k=>$v)
	{
		//check the value
		if(!empty($v))
		{
			if(is_string($v))
			{
				$pattern_for_forming["tables"]["attach_node"] = phpDOM_get_root_node_from_string("<table id=\"{$k}\">{$v}</table>", "XML");
				
				if(phpDOM_forming_node($tables_node, $pattern_for_forming))
				{
					//** position "replace_all" only for the first node "table"
					$pattern_for_forming["tables"]["attach_position"] = null;
				}
			}
		}
	}
	
	return $tables_node;
}


/*	Function: add (or update) files into datasource node.
*
*	Input:
*			$ds_node_in 		- link to datasource node;	[OBJECT]
*			$files_params_in	- list of files.	[ARRAY]
*
*	Output:
*			copy of node "files" or NULL.	[OBJECT || NULL]
*
*	Note:
*
*/
function datasource_add_files_into_node(&$ds_node_in = null, $files_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_add_files_into_node()]");
		}
		return null;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_forming_node",
						 "phpDOM_get_root_node_from_string",
						 "datasource_search_files_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_add_files_into_node()"))
	{
		return null;
	}
	
	//Check the input argument $files_params_in
	if(!is_array($files_params_in))
	{
		return null;
	}
	
	//* node "files"	[OBJECT || NULL]
	$files_node = datasource_search_files_node($ds_node_in);
	
	
	//Check the node
	if(!$files_node)
	{
		return null;
	}
	
	//* pattern for forming 	[ARRAY || NULL]
	$pattern_for_forming = array("files" => array("attach_node" => null, "attach_position" => "replace_all"));
	
	
	foreach($files_params_in as $k=>$v)
	{
		//check the value
		if(is_array($v))
		{
			//check parameter: "type", "path"
			if(!empty($v["type"]) && !empty($v["path"]))
			{
				if(is_string($v["type"]) && is_string($v["path"]))
				{
					$pattern_for_forming["files"]["attach_node"] = phpDOM_get_root_node_from_string(("<file id=\"{$k}\" type=\"").($v["type"]).("\">").($v["path"]).("</file>"), "XML");
					
					if(phpDOM_forming_node($files_node, $pattern_for_forming))
					{
						//** position "replace_all" only for the first node "file"
						$pattern_for_forming["files"]["attach_position"] = null;
					}
				}
			}
		}
	}
	
	return $files_node;
}


/*	Function: add (or update) datasource into root-node.
*
*	Input:
*			$root_node_in	- link to root-node;	[OBJECT]
*			$ds_params_in	- linl to parameters of datasource.	[ARRAY]
*
*	Output:
*			copy of datasource node or NULL.	[OBJECT || NULL]

*	Note:
*
*/
function datasource_add_into_node(&$root_node_in, &$ds_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_add_into_node()]");
		}
		return null;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_attach_node",
						 "phpDOM_forming_node",
						 "phpDOM_get_root_node_from_string",
						 "datasource_check_params",
						 "datasource_normalize_params",
						 "datasource_search_node",
						 "datasource_add_tables_into_node",
						 "datasource_add_files_into_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_add_into_node()"))
	{
		return null;
	}
	
	//Check the input argument $root_node_in
	if(empty($root_node_in))
	{
		return null;
	}
	
	//Normalization of datasource parameters
	datasource_normalize_params($ds_params_in);
	
	//Checking of datasource parameters
	if(!datasource_check_params($ds_params_in))
	{
		return null;
	}
	
	//Update the value of parameter "updated_on"
	$ds_params_in["updated_on"]	= date("Y-m-d H:i:s");
	
	//* pattern for forming 	[ARRAY]
	$pattern_for_forming		= array("root"        => array("remove_childs" => array("node_name" => "^added_on$|^updated_on$|^state$|^note$|^db_type$|^hostname$|^port$|^database$|^table$|^user$|^password$|^characters_coding$", "attr_name" => null, "attr_value" => null), "attributes" => array("type" => $ds_params_in["type"], "name" => $ds_params_in["name"])),
										"note"        => array("attach_node" => phpDOM_get_root_node_from_string(("<note>").($ds_params_in["note"]).("</node>"), "XML"), "attach_position" => "start"),
										"state"       => array("attach_node" => phpDOM_get_root_node_from_string(("<state>").($ds_params_in["state"]).("</state>"), "XML"), "attach_position" => "start"),
										"updated_on"  => array("attach_node" => phpDOM_get_root_node_from_string(("<updated_on>").($ds_params_in["updated_on"]).("</updated_on>"), "XML"), "attach_position" => "start"),
										"added_on"    => array("attach_node" => phpDOM_get_root_node_from_string(("<added_on>").($ds_params_in["added_on"]).("</added_on>"), "XML"), "attach_position" => "start")
										);
	
	//* datasource node	[OBJECT || NULL]
	$ds_node					= datasource_search_node($root_node_in, $ds_params_in["name"], $ds_params_in["type"]);
	
	
	//Check the node
	if(!$ds_node)
	{
		//create new datasource node
		$ds_node = phpDOM_get_root_node_from_string("<datasource></datasource>", "XML");
		
		//attach new datasource node into root-node
		$ds_node = phpDOM_attach_node($root_node_in, $ds_node, "end");
	}
	
	//Check the datasource type
	switch($ds_params_in["type"])
	{
		case "db":
		case "Db":
		case "DB":
			
			$pattern_for_forming["db_type"]				= array("attach_node" => phpDOM_get_root_node_from_string(("<db_type>").($ds_params_in["db_type"]).("</db_type>"), "XML"));
			$pattern_for_forming["hostname"]			= array("attach_node" => phpDOM_get_root_node_from_string(("<hostname>").($ds_params_in["hostname"]).("</hostname>"), "XML"));
			$pattern_for_forming["port"]				= array("attach_node" => phpDOM_get_root_node_from_string(("<port>").($ds_params_in["port"]).("</port>"), "XML"));
			$pattern_for_forming["database"]			= array("attach_node" => phpDOM_get_root_node_from_string(("<database>").($ds_params_in["database"]).("</database>"), "XML"));
			$pattern_for_forming["table"]				= array("attach_node" => phpDOM_get_root_node_from_string(("<table>").($ds_params_in["table"]).("</table>"), "XML"));
			$pattern_for_forming["user"]				= array("attach_node" => phpDOM_get_root_node_from_string(("<user>").($ds_params_in["user"]).("</user>"), "XML"));
			$pattern_for_forming["password"]			= array("attach_node" => phpDOM_get_root_node_from_string(("<password>").($ds_params_in["password"]).("</password>"), "XML"));
			$pattern_for_forming["characters_coding"]	= array("attach_node" => phpDOM_get_root_node_from_string(("<characters_coding>").($ds_params_in["characters_coding"]).("</characters_coding>"), "XML"));
			
			//forming the node
			if(!phpDOM_forming_node($ds_node, $pattern_for_forming))
			{
				return null;
			}
			
			//add (or update) list of tables
			datasource_add_tables_into_node($ds_node, $ds_params_in["tables"]);
			
			break;
		
		default:
			
			$pattern_for_forming["file"]				= array("attach_node" => phpDOM_get_root_node_from_string(("<file>").($ds_params_in["file"]).("</file>"), "XML"));
			
			//forming the node
			if(!phpDOM_forming_node($ds_node, $pattern_for_forming))
			{
				return null;
			}
			
			//add (or update) list of files
			datasource_add_files_into_node($ds_node, $ds_params_in["files"]);
			
			break;
	}
	
	return $ds_node;
}


/*	Function: remove datasource from root-node.
*
*	Input:
*			$root_node_in	- link to root-node;	[OBJECT]
*			$ds_name_in		- datasource name ("undefined" by default);	[STRING || NULL]
*			$ds_type_in		- datasource type:	[STRING || NULL]
*								-- "xml" (by default),
*								-- "db".
*
*	Output:
*			copy of old datasource node or NULL.	[OBJECT || NULL]
*
*	Note:
*
*/
function datasource_remove_from_node(&$root_node_in, $ds_name_in = "undefined", $ds_type_in = "xml")
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function phpDOM_remove_node()
	if(!function_exists("phpDOM_remove_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_remove_node()' not exists! [datasource.php -> datasource_remove_from_node()]");
		}
		return null;
	}
	
	//Check the function datasource_search_node()
	if(!function_exists("datasource_search_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'datasource_search_node()' not exists! [datasource.php -> datasource_remove_from_node()]");
		}
		return null;
	}
	
	//Check the input argument $root_node_in
	if(empty($root_node_in))
	{
		return null;
	}
	
	//* datasource node	[OBJECT || NULL]
	$ds_node = datasource_search_node($root_node_in, $ds_name_in, $ds_type_in);
	
	
	return phpDOM_remove_node($ds_node);
}


/*	Function: get list of datasources names from XML-file.
*
*	Input:	
*			$file_in - file name.	[STRING]
*
*	Output:
*			list of datasources names.	[ARRAY]
*
*	Note:
*
*			Input file must be of type "xml"!
*
*
*			structure of list of datasources names:
*
*				list[0]["name"] = "datasource name",
*				list[0]["type"] = "datasource type",
*				...
*				list[N]["name"] = "datasource name",
*				list[N]["type"] = "datasource type".
*
*/
function datasource_get_names_from_file($file_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function phpDOM_get_root_node_from_file()
	if(!function_exists("phpDOM_get_root_node_from_file"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_get_root_node_from_file()' not exists! [datasource.php -> datasource_get_names_from_file()]");
		}
		return array();
	}
	
	//Check the function datasource_get_names_from_node()
	if(!function_exists("datasource_get_names_from_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'datasource_get_names_from_node()' not exists! [datasource.php -> datasource_get_names_from_node()]");
		}
		return array();
	}
	
	//* root-node from XML-file	[OBJECT || NULL]
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	
	return datasource_get_names_from_node($root_node);
}


/*	Function: get datasource from XML-file.
*
*	Input:
*			$file_in	- file name;	[STRING]
*			$ds_name_in	- datasource name ("undefined" by default);	[STRING || NULL]
*			$ds_type_in	- datasource type:	[STRING || NULL]
*							-- "xml" (by default),
*							-- "db".
*
*	Output:
*			array of datasource parameters.	[ARRAY]
*
*	Note:
*
*/
function datasource_get_from_file($file_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function phpDOM_get_root_node_from_file()
	if(!function_exists("phpDOM_get_root_node_from_file"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_get_root_node_from_file()' not exists! [datasource.php -> datasource_get_from_file()]");
		}
		return array();
	}
	
	//Check the function datasource_get_from_node()
	if(!function_exists("datasource_get_from_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'datasource_get_from_node()' not exists! [datasource.php -> datasource_get_from_file()]");
		}
		return array();
	}
	
	//* root-node from XML-file	[OBJECT || NULL]
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	
	return datasource_get_from_node($root_node, $ds_name_in, $ds_type_in);
}


/*	Function: add (or update) datasource into XML-file.
*
*	Input:
*			$file_in			- file name;	[STRING]
*			$root_node_name_in	- root-node name or NULL;	[STRING || NULL]
*			$ds_params_in		- link to datasource parameters.	[ARRAY]
*
*	Output:
*			copy of datasource node or NULL.	[OBJECT || NULL]
*
*	Note:
*
*			if $root_node_name_in == NULL, then will be used the root-node from XML-file!
*
*/
function datasource_add_into_file($file_in = null, $root_node_name_in = null, &$ds_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_add_into_file()]");
		}
		return null;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_parsing",
						 "phpDOM_get_root_node_from_string",
						 "phpDOM_get_root_node_from_file",
						 "phpDOM_write_document_to_file",
						 "datasource_add_into_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_add_into_file()"))
	{
		return null;
	}
	
	//* root-node from XML-file	[OBJECT || NULL]
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	
	//Check the root-node
	if(!$root_node)
	{
		//create new root-node
		$root_node = phpDOM_get_root_node_from_string("<body></body>", "xml");
	}
	
	//* used root-node	[OBJECT || NULL]
	$used_root_node = $root_node;
	
	
	//Check the input argument $root_node_name_in
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
	
	//* the copy of the datasource node	[OBJECT || NULL]
	$added_datasource = datasource_add_into_node($used_root_node, $ds_params_in);
	
	
	//Check the datasource node
	if($added_datasource)
	{
		//rewrite a file
		if(phpDOM_write_document_to_file($root_node, $file_in, "xml"))
		{
			return $added_datasource;
		}
	}
	
	return null;
}


/*	Function: remove datasource from XML-file.
*
*	Input:
*			$file_in	- file name;	[STRING]
*			$ds_name_in	- datasource name ("undefined" by default);	[STRING || NULL]
*			$ds_type_in	- datasource type:	[STRING || NULL]
*							-- "xml" (by default),
*							-- "db".
*
*	Output:
*			copy of old datasource node or NULL.	[OBJECT || NULL]
*
*	Note:
*
*/
function datasource_remove_from_file($file_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_remove_from_file()]");
		}
		return null;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_get_root_node_from_file",
						 "phpDOM_write_document_to_file",
						 "datasource_remove_from_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_remove_from_file()"))
	{
		return null;
	}
	
	//* root-node from XML-file	[OBJECT || NULL]
	$root_node			= phpDOM_get_root_node_from_file($file_in, "xml");
	
	//* copy of datasource node	[OBJECT || NULL]
	$removed_datasource	= datasource_remove_from_node($root_node, $ds_name_in, $ds_type_in);
	
	
	//Check the datasource node
	if($removed_datasource)
	{
		//rewrite a file
		if(phpDOM_write_document_to_file($root_node, $file_in, "xml"))
		{
			return $removed_datasource;
		}
	}
	
	return null;
}


/*	Function: get list of datasources names from database.
*
*	Input:	
*			$connect_params_in - connection parameters (see library "db").	[ARRAY]
*
*	Output:
*			list of datasources names.	[ARRAY]
*
*	Note:
*
*			Next parameters of the connection is required: db_type, hostname, user, database, table!
*
*
*			structure of list of datasources names:
*
*				list[0]["name"] = "datasource name",
*				list[0]["type"] = "datasource type",
*				...
*				list[N]["name"] = "datasource name",
*				list[N]["type"] = "datasource type".
*
*/
function datasource_get_names_from_db($connect_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function ds_get_key_args_from_db()
	if(!function_exists("ds_get_key_args_from_db"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'ds_get_key_args_from_db()' not exists! [datasource.php -> datasource_get_names_from_db()]");
		}
		return array();
	}
	
	//* description of datasource parameters	[ARRAY]
	$desc_params	= array("name" =>
								array("key"             => "name",
									  "field"           => "name",
									  "attrname"        => "name",
									  "type"            => "string",
									  "default"         => "undefined",
									  "required"		=> true,
									  "if_key_arg"		=> true,
									  "key_arg_value"	=> null
									  ),
							"type" =>
								array("key"             => "type",
									  "field"           => "type",
									  "attrname"        => "type",
									  "type"            => "string",
									  "default"         => "xml",
									  "required"		=> true,
									  "if_key_arg"		=> true,
									  "key_arg_value"	=> null
									  )
							);
	
	
	return ds_get_key_args_from_db($connect_params_in, $desc_params);
}


/*	Function: get datasource from database.
*
*	Input:
*			$connect_params_in	- connection parameters (see library "db");	[ARRAY]
*			$ds_name_in			- datasource name ("undefined" by default),	[STRING || NULL]
*			$ds_type_in			- datasource type:	[STRING || NULL]
*									-- "xml" (by default),
*									-- "db".
*
*	Output:
*			array of datasource parameters.	[ARRAY]
*
*	Note:
*
*			Next parameters of the connection is required: db_type, hostname, user, database, table!
*
*
*			Additional parameters of a datasource from a database:
*
*				- "added_by", "updated_by" - a identifier of a user.
*
*/
function datasource_get_from_db($connect_params_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
{
	//* a returned result	[ARRAY]
	$returned_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_get_from_db()]");
		}
		return $returned_result;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("phpDOM_get_root_node_from_string",
						 "sql_where",
						 "ds_get_db_object",
						 "datasource_normalize_params",
						 "datasource_get_tables_from_node",
						 "datasource_get_files_from_node"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_get_from_db()"))
	{
		return $returned_result;
	}
	
	//Check the input argument $ds_name_in
	if(empty($ds_name_in))
	{
		return $returned_result;
	}
	
	if(!is_string($ds_name_in))
	{
		return $returned_result;
	}
	
	//Check the input argument $ds_type_in
	if(empty($ds_type_in))
	{
		return $returned_result;
	}
	
	if(!is_string($ds_type_in))
	{
		return $returned_result;
	}
	
	//* new object of the database class	[OBJECT || NULL]
	$db_object = ds_get_db_object($connect_params_in);
	
	
	//Check the object
	if($db_object)
	{
		//* field parameters for the operator "WHERE"	[ARRAY]
		$fields_for_where	= array(array("key" => "^name$", "field"=> "name", "type" => "string", "compare" => '='),
									array("key" => "^type$", "field"=> "type", "type" => "string", "compare" => '=')
									);
		
		//* string for operator "WHERE"	[STRING || NULL]
		$where				= sql_where($fields_for_where, array("name" => $ds_name_in, "type" => $ds_type_in));
		
		
		//check the where-string
		if(empty($where))
		{
			return $returned_result;
		}
		
		//* SQL-query	[STRING || NULL]
		$query				= "SELECT `datasource_id` AS `id`, IFNULL(`added_on`, CURRENT_TIMESTAMP) AS `added_on`, `added_by`, IFNULL(`updated_on`, UNIX_TIMESTAMP(CURRENT_TIMESTAMP)) AS `updated_on`, `updated_by`, IFNULL(`state`, 0) AS `state`, `note`, `type`, `name`";
		
		//* a resultset	[RESOURCE || BOOLEAN || NULL]
		$resultset			= null;
		
		
		//check the datasource type
		switch($ds_type_in)
		{
			case "db":
			case "Db":
			case "DB":
				
				$query.= ", IFNULL(`db_type`, 'mysql') AS `db_type`, IFNULL(`hostname`, 'localhost') AS `hostname`, IFNULL(`port`, 3306) AS `port`, `database`, `table`, `user`, `password`, IFNULL(`characters_coding`, 'utf8') AS `characters_coding`, `tables`";
				
				break;
			
			default:
				
				$query.= ", `file`, `files`";
				
				break;
		}
		
		$query.= (" FROM ").($connect_params_in["table"]).(" WHERE {$where} LIMIT 1");
		
		//send the request
		$resultset = $db_object->send_query($query);
		
		//check resultset
		if($resultset)
		{
			if(is_resource($resultset))
			{
				//read data from the resultset
				if(($row = mysql_fetch_assoc($resultset)))
				{
					foreach($row as $k=>$v)
					{
						//check field name
						switch($k)
						{
							case "files":
							case "tables":
								
								//* node "files"/"tables"	[OBJECT || NULL]
								$node = phpDOM_get_root_node_from_string($v, "xml");
								
								
								if($k == "files")
								{
									//get array of files parameters from the node
									$returned_result[$k] = datasource_get_files_from_node($node);
								}
								else
								{
									//get array of tables parameters from the node
									$returned_result[$k] = datasource_get_tables_from_node($node);
								}
								
								break;
								
							default:
								
								$returned_result[$k] = $v;
								
								break;
						}
					}
				}
				
				if(count($returned_result))
				{
					//normalization of datasource parameters
					datasource_normalize_params($returned_result);
				}
				
				//freeing the memory allocated for the result set
				mysql_free_result($resultset);
			}
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


/*	Function: get string from content of node "tables".
*
*	Input:
*			$tables_params_in - array of tables parameters.	[ARRAY]
*
*	Output:
*			string from content of node "tables" or NULL.	[STRING || NULL]
*
*	Note:
*
*/
function datasource_tables_node_to_string($tables_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domNode"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domNode' not exists! [datasource.php -> datasource_tables_node_to_string()]");
		}
		return null;
	}
	
	//Check the function phpDOM_get_root_node_from_string()
	if(!function_exists("phpDOM_get_root_node_from_string"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_get_root_node_from_string()' not exists! [datasource.php -> datasource_tables_node_to_string()]");
		}
		return null;
	}
	
	//Check the function datasource_add_tables_into_node()
	if(!function_exists("datasource_add_tables_into_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'datasource_add_tables_into_node()' not exists! [datasource.php -> datasource_tables_node_to_string()]");
		}
		return null;
	}
	
	//* node "body"	[OBJECT || NULL]
	$body_node		= phpDOM_get_root_node_from_string("<body></body>", "xml");
	
	//* node "tables"	[OBJECT || NULL]
	$tables_node	= datasource_add_tables_into_node($body_node, $tables_params_in);
	
	
	//Check the node
	if($tables_node)
	{
		if(is_a($tables_node, "domNode"))
		{
			//* owner document	[OBJECT || NULL]
			$doc = $tables_node->ownerDocument;
			
			
			//set output format
			$doc->formatOutput = true;
			
			//get string from the XML-structure
			return $doc->saveXML($tables_node);
		}
	}
	
	return null;
}


/*	Function: get string from content of node "files".
*
*	Input:
*			$files_params_in - array of files parameters.	[ARRAY]
*
*	Output:
*			string from content of node "files" or NULL.	[STRING || NULL]
*
*	Note:
*
*/
function datasource_files_node_to_string($files_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domNode"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domNode' not exists! [datasource.php -> datasource_files_node_to_string()]");
		}
		return null;
	}
	
	//Check the function phpDOM_get_root_node_from_string()
	if(!function_exists("phpDOM_get_root_node_from_string"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_get_root_node_from_string()' not exists! [datasource.php -> datasource_files_node_to_string()]");
		}
		return null;
	}
	
	//Check the function datasource_add_files_into_node()
	if(!function_exists("datasource_add_files_into_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'datasource_add_files_into_node()' not exists! [datasource.php -> datasource_files_node_to_string()]");
		}
		return null;
	}
	
	//* node "body"	[OBJECT || NULL]
	$body_node	= phpDOM_get_root_node_from_string("<body></body>", "xml");
	
	//* node "files"	[OBJECT || NULL]
	$files_node	= datasource_add_files_into_node($body_node, $files_params_in);
	
	
	//Check the node
	if($files_node)
	{
		if(is_a($files_node, "domNode"))
		{
			//* owner document	[OBJECT || NULL]
			$doc = $files_node->ownerDocument;
			
			
			//set output format
			$doc->formatOutput = true;
			
			//get string from the XML-structure
			return $doc->saveXML($files_node);
		}
	}
	
	return null;
}


/*	Function: add (or update) datasource into database.
*
*	Input:
*			$connect_params_in	- connection parameters (see the library "db");	[ARRAY]
*			$ds_params_in		- link to datasource parameters.	[ARRAY]
*
*	Output:
*			copy of array of datasource parameters or null.	[ARRAY || NULL]
*
*	Note:
*
*			Next parameters of the connection is required: db_type, hostname, user, database, table!
*
*/
function datasource_add_into_db($connect_params_in = null, &$ds_params_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_add_into_db()]");
		}
		return null;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("sql_insert",
						 "sql_update",
						 "ds_get_db_object",
						 "datasource_check_params",
						 "datasource_normalize_params",
						 "datasource_get_from_db",
						 "datasource_tables_node_to_string",
						 "datasource_files_node_to_string"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_add_into_db()"))
	{
		return null;
	}
	
	//Normalization of datasource parameters
	datasource_normalize_params($ds_params_in);
	
	//Checking of datasource parameters
	if(!datasource_check_params($ds_params_in))
	{
		return null;
	}
	
	//* new object of the database class	[OBJECT || NULL]
	$db_object = ds_get_db_object($connect_params_in);
	
	
	//Check the object
	if(!$db_object)
	{
		return null;
	}
	
	//* parameters of fields	[ARRAY]
	$fields			= array(array("key" => "updated_by", "field" => "updated_by", "type" => "int", "default" => null),
							array("key" => "state", "field" => "state", "type" => "int", "default" => 0),
							array("key" => "type", "field" => "type", "type" => "string", "default" => null),
							array("key" => "name", "field" => "name", "type" => "string", "default" => null),
							array("key" => "file", "field" => "file", "type" => "string", "default" => null),
							array("key" => "db_type", "field" => "db_type", "type" => "string", "default" => null),
							array("key" => "hostname", "field" => "hostname", "type" => "string", "default" => null),
							array("key" => "port", "field" => "port", "type" => "string", "default" => null),
							array("key" => "database", "field" => "database", "type" => "string", "default" => null),
							array("key" => "table", "field" => "table", "type" => "string", "default" => null),
							array("key" => "user", "field" => "user", "type" => "string", "default" => null),
							array("key" => "password", "field" => "password", "type" => "string", "default" => null),
							array("key" => "characters_coding", "field" => "characters_coding", "type" => "string", "default" => null),
							array("key" => "note", "field" => "note", "type" => "string", "default" => null)
						);
	
	//* last datasource parameters	[ARRAY]
	$last_ds_params	= datasource_get_from_db($connect_params_in, $ds_params_in["name"], $ds_params_in["type"]);
	
	//* a query	string	[STRING || NULL]
	$query			= null;
	
	
	//Check the datasource type
	switch($ds_params_in["type"])
	{
		case "db":
		case "Db":
		case "DB":
			
			//* string of the content of a node "tables"	[STRING || NULL]
			$tables_str = datasource_tables_node_to_string($ds_params_in["tables"]);
			
			
			array_push($fields, array("key" => "_tables", "field" => "tables", "type" => "string", "default" => $tables_str));
			
			break;
			
		default:
			
			//* string of the content of a node "files"	[STRING || NULL]
			$files_str = datasource_files_node_to_string($ds_params_in["files"]);
			
			
			array_push($fields, array("key" => "_files", "field" => "files", "type" => "string", "default" => $files_str));
			
			break;
	}
	
	//Check the array of last datasource parameters
	if(is_array($last_ds_params))
	{
		if(empty($last_ds_params["name"]))
		{
			$last_ds_params = null;
		}
		
		if(empty($last_ds_params["type"]))
		{
			$last_ds_params = null;
		}
	}
	
	if(is_array($last_ds_params))
	{
		//** update
		
		//* field parameters for the operator "WHERE"	[ARRAY]
		$where = array(array("key" => "^name$", "field" => "name", "type" => "string", "compare" => '='),
					   array("key" => "^type$", "field" => "type", "type" => "string", "compare" => '=')
					  );
		
		
		//get a query for the operation "UPDATE"
		$query = sql_update($connect_params_in["table"], $fields, $where, $ds_params_in);
	}
	else
	{
		//** insert
		
		//add additional fields
		array_push($fields, array("key" => "added_on", "field" => "added_on", "type" => "string", "default" => date("Y-m-d H:i:s")));
		array_push($fields, array("key" => "added_by", "field" => "added_by", "type" => "int", "default" => null));
		
		//get a query for the operation "INSERT"
		$query = sql_insert($connect_params_in["table"], $fields, $ds_params_in);
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
		
		return null;
	}
	
	return $ds_params_in;
}


/*	Function: remove datasource from database.
*
*	Input:
*			$connect_params_in	- connection parameters (see library "db");	[ARRAY]
*			$ds_name_in			- datasource name ("undefined" by default),	[STRING || NULL]
*			$ds_type_in			- datasource type:	[STRING || NULL]
*									-- "xml" (by default),
*									-- "db".
*
*	Output:
*			copy of array of datasource parameters or NULL.	[ARRAY || NULL]
*
*	Note:
*
*			the connection's parameter "table" is required!
*
*/
function datasource_remove_from_db($connect_params_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check the function functions_check_required()
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'functions_check_required()' not exists! [datasource.php -> datasource_remove_from_db()]");
		}
		return null;
	}
	
	//* the array of required functions 	[ARRAY]
	$r_functions = array("sql_delete",
						 "ds_get_db_object"
						 );
	
	
	//Check required functions
	if(!functions_check_required($r_functions, "datasource.php", "datasource_remove_from_db()"))
	{
		return null;
	}
	
	//* last datasource parameters	[ARRAY]
	$last_ds_params = datasource_get_from_db($connect_params_in, $ds_name_in, $ds_type_in);
	
	
	//Check the array of last datasource parameters
	if(is_array($last_ds_params))
	{
		if(empty($last_ds_params["name"]))
		{
			$last_ds_params = null;
		}
		
		if(empty($last_ds_params["type"]))
		{
			$last_ds_params = null;
		}
	}
	
	if(!is_array($last_ds_params))
	{
		return null;
	}
	
	//* new object of the database class	[OBJECT || NULL]
	$db_object = ds_get_db_object($connect_params_in);
	
	
	//Check the object
	if(!$db_object)
	{
		return null;
	}
	
	//* field parameters for the operator "where"	[ARRAY]
	$where = array(array("key" => "^name$", "field" => "name", "type" => "string", "compare" => '='),
				   array("key" => "^type$", "field" => "type", "type" => "string", "compare" => '=')
				  );
	
	//* a query for the operation "DELETE"	[STRING || NULL]
	$query = sql_delete($connect_params_in["table"], $where, $last_ds_params);
	
	
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
		
		return null;
	}
	
	return $last_ds_params;
}


//** CLASSES

/*	Class: data source.
*
*	Input:
*			$ds_name_in	- datasource name ("undefined" by default),	[STRING || NULL]
*			$ds_type_in	- datasource type:	[STRING || NULL]
*							-- "xml" (by default),
*							-- "db".
*/
class datasource
{
	//** Options
	
	//** public
	
	//* an array of datasource parameters	[ARRAY]
	public $params;
	
	
	//** private
	
	
	//** Methods
	
	//*	method: check parameters of the datasource.
	//
	//*	input: none.
	//
	//*	output:
	//			result:	[BOOLEAN]
	//				- true	- parameters are suitable,
	//				- flase	- parameters not are suitable.
	//
	//*	note:
	//
	function check_params()
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_check_params()
		if(!function_exists("datasource_check_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_check_params()' not exists! [datasource.php -> class datasource]");
			}
			return false;
		}
		
		return datasource_check_params($this->params);
	}
	
	//*	method: normalize parameters of the datasource.
	//
	//*	input: none.
	//
	//*	output:
	//			result:	[BOOLEAN]
	//				- true	- parameters are suitable,
	//				- flase	- parameters not are suitable.
	//
	//*	note:
	//
	function normalize()
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_normalize_params()
		if(!function_exists("datasource_normalize_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_normalize_params()' not exists! [datasource.php -> class datasource]");
			}
			return false;
		}
		
		return datasource_normalize_params($this->params);
	}
	
	//*	method: get a list of datasources names from a node.
	//
	//*	input:
	//			$root_node_in - a node object.	[OBJECT]
	//
	//*	output:
	//			the list of datasources names.	[ARRAY]
	//
	//*	note:
	//			The structure of the list:
	//
	//				list[0]["name"] = "datasource name",
	//				list[0]["type"] = "datasource type",
	//				...
	//				list[N]["name"] = "datasource name",
	//				list[N]["type"] = "datasource type".
	//
	function get_names_from_node($root_node_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_get_names_from_node()
		if(!function_exists("datasource_get_names_from_node"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_names_from_node()' not exists! [datasource.php -> class datasource]");
			}
			return array();
		}
		
		return datasource_get_names_from_node($root_node_in);
	}
	
	//*	method: get a datasource from a node.
	//
	//*	input:
	//			$root_node_in	- a node object;	[OBJECT]
	//			$ds_name_in		- a datasource name ("undefined" by default);	[STRING || NULL]
	//			$ds_type_in		- a datasource type:	[STRING || NULL]
	//								-- "xml" (by default),
	//								-- "db".
	//
	//*	output:
	//			the array of parameters of a datasource.	[ARRAY]
	//
	//*	note:
	//
	function get_from_node($root_node_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
	{
		//init global variables
		global $FL_DEBUG;
		
		$this->params = array();
		
		//check the function datasource_get_from_node()
		if(!function_exists("datasource_get_from_node"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_from_node()' not exists! [datasource.php -> class datasource]");
			}
			return $this->params;
		}
		
		//get datasource parameters from the node
		$this->params = datasource_get_from_node($root_node_in, $ds_name_in, $ds_type_in);
		
		return $this->params;
	}
	
	//*	method: add (or update) the datasource into a node.
	//
	//*	input:
	//			$root_node_in - link to a node object.	[OBJECT]
	//
	//*	output:
	//			the copy of the datasource node or null.	[OBJECT || NULL]
	//
	//*	note:
	//
	function add_into_node(&$root_node_in)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_add_into_node()
		if(!function_exists("datasource_add_into_node"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_add_into_node()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		return datasource_add_into_node($root_node_in, $this->params);
	}
	
	//*	method: remove the datasource from a node.
	//
	//*	input:
	//			$root_node_in - link to a node object.	[OBJECT]
	//
	//*	output:
	//			the copy of old datasource node or null.	[OBJECT || NULL]
	//
	//*	note:
	//			$root_node_in is a root-node object (its child-nodes is parameters of the datasources)!
	//
	//			used parameters from the public option "params"!
	//
	function remove_from_node(&$root_node_in)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_remove_from_node()
		if(!function_exists("datasource_remove_from_node"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_remove_from_node()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//check the public option $this->params
		if(!is_array($this->params))
		{
			return null;
		}
		
		if(!isset($this->params["name"]))
		{
			return null;
		}
		
		if(!isset($this->params["type"]))
		{
			return null;
		}
		
		return datasource_remove_from_node($root_node_in, $this->params["name"], $this->params["type"]);
	}
	
	//*	method: get the list of datasources names from a XML-file.
	//
	//*	input:
	//			$file_in - a file name.	[STRING]
	//
	//*	output:
	//			the list of datasource names.	[ARRAY]
	//
	//*	note:
	//			The type of input file must be "xml"!
	//
	//			The structure of the list:
	//
	//				list[0]["name"] = "datasource name",
	//				list[0]["type"] = "datasource type",
	//				...
	//				list[N]["name"] = "datasource name",
	//				list[N]["type"] = "datasource type".
	//
	function get_names_from_file($file_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_get_names_from_file()
		if(!function_exists("datasource_get_names_from_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_names_from_file()' not exists! [datasource.php -> class datasource]");
			}
			return array();
		}
		
		return datasource_get_names_from_file($file_in);
	}
	
	//*	method: get a datasource from a XML-file.
	//
	//*	input:
	//			$file_in	- a file name;	[STRING]
	//			$ds_name_in	- a datasource name ("undefined" by default);	[STRING || NULL]
	//			$ds_type_in	- a datasource type:	[STRING || NULL]
	//							-- "xml" (by default),
	//							-- "db".
	//
	//*	output:
	//			the array of parameters of a datasource.	[ARRAY]
	//
	//*	note:
	//			the resulting value saved in the public options "params"!
	//
	function get_from_file($file_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
	{
		//init global variables
		global $FL_DEBUG;
		
		$this->params = array();
		
		//check the function datasource_get_from_file()
		if(!function_exists("datasource_get_from_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_from_file()' not exists! [datasource.php -> class datasource]");
			}
			return $this->params;
		}
		
		//get datasource parameters from a file
		$this->params = datasource_get_from_file($file_in, $ds_name_in, $ds_type_in);
		
		return $this->params;
	}
	
	//*	method: add (or update) the datasource into a XML-file.
	//
	//*	input:
	//			$file_in			- a file name;	[STRING]
	//			$root_node_name_in	- a root-node name or NULL.	[STRING || NULL]
	//
	//*	output:
	//			the copy of the datasource node or null.	[OBJECT || NULL]
	//
	//*	note:
	//			if $root_node_name_in == NULL, then will be used the root-node of a XML-file!
	//
	function add_into_file($file_in = null, $root_node_name_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_add_into_file()
		if(!function_exists("datasource_add_into_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_add_into_file()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		return datasource_add_into_file($file_in, $root_node_name_in, $this->params);
	}
	
	//*	method: remove the datasource from a XML-file.
	//
	//*	input:
	//			$file_in - a file name.	[STRING]
	//
	//*	output:
	//			the copy of old datasource node or null.	[OBJECT || NULL]
	//
	//*	note:
	//
	function remove_from_file($file_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_remove_from_file()
		if(!function_exists("datasource_remove_from_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_remove_from_file()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//check the public option $this->params
		if(!is_array($this->params))
		{
			return null;
		}
		
		if(!isset($this->params["name"]))
		{
			return null;
		}
		
		if(!isset($this->params["type"]))
		{
			return null;
		}
		
		return datasource_remove_from_file($file_in, $this->params["name"], $this->params["type"]);
	}
	
	//*	method: get a object of a database class.
	//
	//*	input:
	//			$connect_params_in - parameters of a connection (see the library "db") or null.	[ARRAY || NULL]
	//
	//*	output:
	//			a object of a class by the database type (dbMySQL ...) or NULL.	[OBJECT || NULL]
	//
	//*	note:
	//			Next parameters of the connection is required: db_type, hostname, user, database, table!
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	function get_db_object($connect_params_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function ds_get_db_object()
		if(!function_exists("ds_get_db_object"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_db_object()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		return ((is_array($connect_params_in)) ? ds_get_db_object($connect_params_in) : ds_get_db_object($this->params));
	}
	
	//*	method: get the list of datasources names from a database.
	//
	//*	input:
	//			$connect_params_in - parameters of a connection (see the library "db").	[ARRAY]
	//
	//*	output:
	//			the list of datasource names.	[ARRAY]
	//
	//*	note:
	//			Next parameters of the connection is required: db_type, hostname, user, database, table!
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	//			The structure of the list:
	//
	//				list[0]["name"] = "datasource name",
	//				list[0]["type"] = "datasource type",
	//				...
	//				list[N]["name"] = "datasource name",
	//				list[N]["type"] = "datasource type".
	//
	function get_names_from_db($connect_params_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_get_names_from_db()
		if(!function_exists("datasource_get_names_from_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_names_from_db()' not exists! [datasource.php -> class datasource]");
			}
			return array();
		}
		
		return ((is_array($connect_params_in)) ? datasource_get_names_from_db($connect_params_in) : datasource_get_names_from_db($this->params));
	}
	
	//*	method: get a datasource from a database.
	//
	//*	input:
	//			$connect_params_in	- parameters of a connection (see the library "db");	[ARRAY]
	//			$ds_name_in			- a datasource name ("undefined" by default),	[STRING || NULL]
	//			$ds_type_in			- a datasource type:	[STRING || NULL]
	//									-- "xml" (by default),
	//									-- "db".
	//
	//*	output:
	//			the array with parameters of a datasource.	[ARRAY]
	//
	//*	note:
	//			Next parameters of the connection is required: db_type, hostname, user, database, table!
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	//			Additional parameters of a datasource from a database:
	//				- "added_by", "updated_by", "id" - a identifier of a user.
	//
	function get_from_db($connect_params_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
	{
		//init global variables
		global $FL_DEBUG;
		
		$this->params = array();
		
		//check the function datasource_get_from_db()
		if(!function_exists("datasource_get_from_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_from_db()' not exists! [datasource.php -> class datasource]");
			}
			return $this->params;
		}
		
		//get datasource parameters from a database
		if(is_array($connect_params_in))
		{
			$this->params = datasource_get_from_db($connect_params_in, $ds_name_in, $ds_type_in);
		}
		else
		{
			$this->params = datasource_get_from_db($this->params, $ds_name_in, $ds_type_in);
		}
		
		return $this->params;
	}
	
	//*	method: add (or update) the datasource into a database.
	//
	//*	input:
	//			$connect_params_in	- parameters of a connection (see the library "db").	[ARRAY]
	//
	//*	output:
	//			the copy of the array of parameters of a datasource or null.	[ARRAY || NULL]
	//
	//*	note:
	//			Next parameters of the connection is required: db_type, hostname, user, database, table!
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	function add_into_db($connect_params_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_add_into_db()
		if(!function_exists("datasource_add_into_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_add_into_db()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		return ((is_array($connect_params_in)) ? datasource_add_into_db($connect_params_in, $this->params) : datasource_add_into_db($this->params, $this->params));
	}
	
	//*	method: remove the datasource from a database.
	//
	//*	input:
	//			$connect_params_in	- parameters of a connection (see the library "db").	[ARRAY]
	//
	//*	output:
	//			the copy of the array of parameters of a datasource or null.	[ARRAY || NULL]
	//
	//*	note:
	//			The connection's parameter "table" is required!
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	function remove_from_db($connect_params_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function datasource_remove_from_db()
		if(!function_exists("datasource_remove_from_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_remove_from_db()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//check the public option $this->params
		if(!is_array($this->params))
		{
			return null;
		}
		
		if(!isset($this->params["name"]))
		{
			return null;
		}
		
		if(!isset($this->params["type"]))
		{
			return null;
		}
		
		return ((is_array($connect_params_in)) ? datasource_remove_from_db($connect_params_in, $this->params["name"], $this->params["type"]) : datasource_remove_from_db($this->params, $this->params["name"], $this->params["type"]));
	}
	
	//*	method: get file name from list of files by ID.
	//
	//*	input:
	//			$file_id_in - identifier to list of files of null.	[STRING || NULL]
	//
	//*	output:
	//			file name or null.	[STRING || NULL]
	//
	//*	note:
	//
	//			datasource parameters:
	//				-- required: "file" or "files" with $file_id_in.
	//
	public function get_file_name_by_id($file_id_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function ds_get_repository_file_name_by_target_id()
		if(!function_exists("ds_get_repository_file_name_by_target_id"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_repository_file_name_by_target_id()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//get file name from list of files by ID
		return ds_get_repository_file_name_by_target_id($this->params, $file_id_in);
	}
	
	//*	method: get table name from list of tables by ID.
	//
	//*	input:
	//			$table_id_in - identifier to list of tables of null.	[STRING || NULL]
	//
	//*	output:
	//			table name or null.	[STRING || NULL]
	//
	//*	note:
	//
	//			datasource parameters:
	//				-- required: "table" or "tables" with $table_id_in.
	//
	public function get_table_name_by_id($table_id_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function ds_get_repository_table_name_by_target_id()
		if(!function_exists("ds_get_repository_table_name_by_target_id"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_get_repository_table_name_by_target_id()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//get table name from list of tables by ID
		return ds_get_repository_table_name_by_target_id($this->params, $table_id_in);
	}
	
	//*	method: get the list of datasources names from a datasource.
	//
	//*	input:
	//			$connect_params_in	- parameters of a connection (see the library "db" and "datasource.php");	[ARRAY]
	//			$target_id_in		- identifier to list of files (for datasource type "xml")	[STRING || NULL]
	//									or list of tables (for datasource type "db") or null.
	//
	//*	output:
	//			the list of datasource names.	[ARRAY]
	//
	//*	note:
	//
	//			parameters of the connection:
	//				-- required:
	//					~ for type "xml": "file" or "files" with $target_id_in,
	//					~ for type "db":  "db_type", "hostname", "user", "database", "table" or "tables" with $target_id_in.
	//
	//			The structure of the list:
	//
	//				list[0]["name"] = "datasource name",
	//				list[0]["type"] = "datasource type",
	//				...
	//				list[N]["name"] = "datasource name",
	//				list[N]["type"] = "datasource type".
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	function get_names_from_ds($connect_params_in = null, $target_id_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function ds_check_datasource_params()
		if(!function_exists("ds_check_datasource_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_check_datasource_params()' not exists! [datasource.php -> class datasource]");
			}
			return array();
		}
		
		//check the function datasource_get_names_from_file()
		if(!function_exists("datasource_get_names_from_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_names_from_file()' not exists! [datasource.php -> class datasource]");
			}
			return array();
		}
		
		//check the function datasource_get_names_from_db()
		if(!function_exists("datasource_get_names_from_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_names_from_db()' not exists! [datasource.php -> class datasource]");
			}
			return array();
		}
		
		//* connection parameters	[ARRAY]
		$connect_params = ((is_array($connect_params_in)) ? ds_check_datasource_params($connect_params_in, $target_id_in) : ds_check_datasource_params($this->params, $target_id_in));
		
		
		//check the connection parameters
		if($connect_params)
		{
			switch($connect_params["type"])
			{
				case "db":
				case "Db":
				case "DB":
					
					return datasource_get_names_from_db($connect_params);
					
				case "xml":
				case "Xml":
				case "XML":
					
					return datasource_get_names_from_file($connect_params["file"]);
			}
		}
		
		return array();
	}
	
	//*	method: get a datasource from a datasource.
	//
	//*	input:
	//			$connect_params_in	- parameters of a connection (see the library "db" and "datasource.php");	[ARRAY]
	//			$target_id_in		- identifier to list of files (for datasource type "xml")	[STRING || NULL]
	//									or list of tables (for datasource type "db") or null;
	//			$ds_name_in			- a datasource name ("undefined" by default);	[STRING || NULL]
	//			$ds_type_in			- a datasource type:	[STRING || NULL]
	//									-- "xml" (by default),
	//									-- "db".
	//
	//*	output:
	//			the array of parameters of a datasource.	[ARRAY]
	//
	//*	note:
	//
	//			parameters of the connection:
	//				-- required:
	//					~ for type "xml": "file" or "files" with $target_id_in,
	//					~ for type "db":  "db_type", "hostname", "user", "database", "table" or "tables" with $target_id_in.
	//
	//			The resulting value saved in the public options "params"!
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	function get_from_ds($connect_params_in = null, $target_id_in = null, $ds_name_in = "undefined", $ds_type_in = "xml")
	{
		//init global variables
		global $FL_DEBUG;
		
		$this->params = array();
		
		//check the function ds_check_datasource_params()
		if(!function_exists("ds_check_datasource_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_check_datasource_params()' not exists! [datasource.php -> class datasource]");
			}
			return $this->params;
		}
		
		//check the function datasource_get_from_file()
		if(!function_exists("datasource_get_from_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_from_file()' not exists! [datasource.php -> class datasource]");
			}
			return $this->params;
		}
		
		//check the function datasource_get_from_db()
		if(!function_exists("datasource_get_from_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_get_from_db()' not exists! [datasource.php -> class datasource]");
			}
			return $this->params;
		}
		
		//* connection parameters	[ARRAY]
		$connect_params = ((is_array($connect_params_in)) ? ds_check_datasource_params($connect_params_in, $target_id_in) : ds_check_datasource_params($this->params, $target_id_in));
		
		
		//check the connection parameters
		if($connect_params)
		{
			switch($connect_params["type"])
			{
				case "db":
				case "Db":
				case "DB":
					
					$this->params = datasource_get_from_db($connect_params, $ds_name_in, $ds_type_in);
					
					break;
					
				case "xml":
				case "Xml":
				case "XML":
					
					$this->params = datasource_get_from_file($connect_params["file"], $ds_name_in, $ds_type_in);
					
					break;
			}
		}
		
		return $this->params;
	}
	
	//*	method: add (or update) the datasource into a datasource.
	//
	//*	input:
	//			$connect_params_in	- parameters of a connection (see the library "db" and "datasource.php");	[ARRAY]
	//			$target_id_in		- identifier to list of files (for datasource type "xml")	[STRING || NULL]
	//									or list of tables (for datasource type "db") or null;
	//			$root_node_name_in	- a root-node name (for connection type "xml") or NULL.	[STRING || NULL]
	//
	//*	output:
	//			the copy of datasource node (for connection type "xml")	[OBJECT || ARRAY || NULL]
	//				or the array of parameters of a datasource (for connection type "db")
	//				or null.
	//
	//*	note:
	//
	//			if $connect_params_in["type"] == "xml" and $root_node_name_in == NULL, then will be used the root-node of a XML-file!
	//
	//			parameters of the connection:
	//				-- required:
	//					~ for type "xml": "file" or "files" with $target_id_in,
	//					~ for type "db":  "db_type", "hostname", "user", "database", "table" or "tables" with $target_id_in.
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	function add_into_ds($connect_params_in = null, $target_id_in = null, $root_node_name_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function ds_check_datasource_params()
		if(!function_exists("ds_check_datasource_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_check_datasource_params()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//check the function datasource_add_into_file()
		if(!function_exists("datasource_add_into_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_add_into_file()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//check the function datasource_add_into_db()
		if(!function_exists("datasource_add_into_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_add_into_db()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//* connection parameters	[ARRAY]
		$connect_params = ((is_array($connect_params_in)) ? ds_check_datasource_params($connect_params_in, $target_id_in) : ds_check_datasource_params($this->params, $target_id_in));
		
		
		//check the connection parameters
		if($connect_params)
		{
			switch($connect_params["type"])
			{
				case "db":
				case "Db":
				case "DB":
					
					return datasource_add_into_db($connect_params, $this->params);
					
				case "xml":
				case "Xml":
				case "XML":
					
					return datasource_add_into_file($connect_params["file"], $root_node_name_in, $this->params);
			}
		}
		
		return null;
	}
	
	//*	method: remove the datasource from a datasource.
	//
	//*	input:
	//			$connect_params_in	- parameters of a connection (see the library "db" and "datasource.php");	[ARRAY]
	//			$target_id_in		- identifier to list of files (for datasource type "xml")	[STRING || NULL]
	//									or list of tables (for datasource type "db") or null.
	//
	//*	output:
	//			the copy of the removed datasource node (for connection type "xml")	[OBJECT || ARRAY || NULL]
	//				or the array of parameters of the removed datasource (for connection type "db")
	//				or null.
	//
	//*	note:
	//
	//			parameters of the connection:
	//				-- required:
	//					~ for type "xml": "file" or "files" with $target_id_in,
	//					~ for type "db":  "db_type", "hostname", "user", "database", "table" or "tables" with $target_id_in.
	//
	//			If the input argument $connect_params_in is NULL, then used $this->params!
	//
	function remove_from_ds($connect_params_in = null, $target_id_in = null)
	{
		//init global variables
		global $FL_DEBUG;
		
		//check the function ds_check_datasource_params()
		if(!function_exists("ds_check_datasource_params"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'ds_check_datasource_params()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//check the function datasource_remove_from_file()
		if(!function_exists("datasource_remove_from_file"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_remove_from_file()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//check the function datasource_remove_from_db()
		if(!function_exists("datasource_remove_from_db"))
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_remove_from_db()' not exists! [datasource.php -> class datasource]");
			}
			return null;
		}
		
		//check the public option $this->params
		if(!is_array($this->params))
		{
			return null;
		}
		
		if(!isset($this->params["name"]))
		{
			return null;
		}
		
		if(!isset($this->params["type"]))
		{
			return null;
		}
		
		//* connection parameters	[ARRAY]
		$connect_params = ((is_array($connect_params_in)) ? ds_check_datasource_params($connect_params_in, $target_id_in) : ds_check_datasource_params($this->params, $target_id_in));
		
		
		//check the connection parameters
		if($connect_params)
		{
			switch($connect_params["type"])
			{
				case "db":
				case "Db":
				case "DB":
					
					return datasource_remove_from_db($connect_params, $this->params["name"], $this->params["type"]);
					
				case "xml":
				case "Xml":
				case "XML":
					
					return datasource_remove_from_file($connect_params["file"], $this->params["name"], $this->params["type"]);
			}
		}
		
		return null;
	}
	
	
	//** Constructor and Destructor
	
	//*	constructor
	//
	//*	input:
	//			$ds_name_in	- a datasource name ("undefined" by default),	[STRING || NULL]
	//			$ds_type_in	- a datasource type:	[STRING || NULL]
	//							-- "xml" (by default),
	//							-- "db".
	//
	//*	note:	
	//
	function __construct($ds_name_in = "undefined", $ds_type_in = "xml")
	{
		//init global variables
		global $FL_DEBUG;
		
		//init options by default
		$this->params = array("name" => "undefined", "type" => "xml");
		
		//check the function datasource_new_params()
		if(function_exists("datasource_new_params"))
		{
			//create a new datasource
			$this->params = datasource_new_params($ds_name_in, $ds_type_in);
		}
		else
		{
			if($FL_DEBUG)
			{
				echo("Error! Function 'datasource_new_params()' is undefined! [datasource.php -> class datasource]");
			}
		}
	}
	
	//*	destructor
	//
	//*	note:	
	//
	function __destruct()
	{
		unset($this->params);
	}
}


?>
