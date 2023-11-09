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


/*   Library: sysconfig.
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
*			+ types/types.php:
*				~ type_of_datetime().
*
*			+ types/functions.php:
*				~ functions_check_required().
*
*			+ dom/dom.php:
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
*			+ datasources/datasource.php:
*				~ class datasource.
*/


/*	Global variables: none.
*
*
*	Functions:
*
*		*** check sysconfig parameters ***
*		sysconfig_params__check($params_in = null)
*
*		*** normalization of sysconfig parameters ***
*		sysconfig_params__normalize(&$params_in)
*
*		*** get new sysconfig parameters ***
*		sysconfig_params__new($name_in = null)
*
*		*** get a list of sysconfig names from a root node ***
*		sysconfig_root_node__get_names($root_node_in = null)
*
*		*** search a sysconfig node in a node ***
*		sysconfig_root_node__search($root_node_in = null, $name_in = null)
*
*		*** search a node "datasources" in a sysconfig node ***
*		sysconfig_node__search_datasources($node_in = null)
*
*		*** get datasource from a node "datasources" ***
*		sysconfig_datasources_node__get_datasource($node_in = null, $ds_name_in = null, $ds_type_in = null)
*
*		*** get list of datasources from a node "datasources" ***
*		sysconfig_datasources_node__get_datasources($node_in = null)
*
*		*** search a node "directories" in a sysconfig node ***
*		sysconfig_node__search_directories($node_in = null)
*
*		*** get list of directories from node "directories" ***
*		sysconfig_directories_node__get_directories($node_in = null)
*
*		*** get a datasource from a sysconfig node ***
*		sysconfig_node__get_datasource($node_in = null, $ds_name_in = null, $ds_type_in = null)
*
*		*** get list of directories from a sysconfig node ***
*		sysconfig_node__get_directories($node_in = null)
*
*		*** get a sysconfig parameters from a sysconfig node ***
*		sysconfig_node__get_params($node_in = null)
*
*		*** get a sysconfig parameters from a root node ***
*		sysconfig_root_node__get_params($root_node_in = null, $name_in = null)
*
*		*** clear a node "datasources" ***
*		sysconfig_datasources_node__clear(&$node_in = null)
*
*		*** clear a node "datasources" ***
*		sysconfig_node__clear_datasources(&$node_in = null)
*
*		*** set the datasource as primary for sysconfig node ***
*		sysconfig_node__set_datasource_as_primary(&$node_in = null, $ds_name_in = null, $ds_type_in = null)
*
*		*** add (or upgrade) a datasource into a sysconfig node ***
*		sysconfig_node__add_datasource(&$node_in = null, $ds_in = null, $primary_in = false)
*
*		*** remove a datasource from a sysconfig node ***
*		sysconfig_node__remove_datasource(&$node_in = null, $ds_in = null)
*
*		*** clear a node "directories" ***
*		sysconfig_directories_node__clear(&$node_in = null)
*
*		*** clear a node "directories" ***
*		sysconfig_node__clear_directories(&$node_in = null)
*
*		*** add (or upgrade) directories into a sysconfig node ***
*		sysconfig_node__add_directories(&$node_in = null, $dirs_in = null)
*
*		*** create sysconfig node ***
*		sysconfig_params__create_node($params_in = null)
*
*		*** add (or upgrade) a sysconfig into a root node ***
*		sysconfig_root_node__add(&$root_node_in = null, $params_in = null)
*
*		*** remove a sysconfig from a root node ***
*		sysconfig_root_node__remove(&$root_node_in = null, $name_in = null)
*
*		*** get a list of sysconfig names from a XML-file ***
*		sysconfig_file__get_names($file_in = null)
*
*		*** get a sysconfig parameters from a XML-file ***
*		sysconfig_file__get_params($file_in = null, $name_in = null)
*
*		*** add (or upgrade) a sysconfig into a XML-file ***
*		sysconfig_file__add($file_in = null, $params_in = null, $root_node_name_in = null)
*
*		*** remove a sysconfig from a XML-file ***
*		sysconfig_file__remove($file_in = null, $name_in = null)
*
*
*	Classes:
*
*		- sysconfig.
*
*
*	Array of sysconfig parameters:
*
*		- ["name"]				- (!) name of sysconfig (the value of attribute "name"; "undefined" by default);	[STRING]
*		- ["added_on"]			- date and time of publication;		[DATETIME AS STRING]
*		- ["updated_on"]		- date and time of modification;	[DATETIME AS STRING]
*		- ["state"]				- state:							[INTEGER]
*									-- 0 - unused,
*									-- 1 - used (by default),
*									-- 2 - removed;
*		- ["note"]				- note (null by default);			[STRING || NULL]
*		- ["datasource_name"]	- name of datasource by default;	[STRING || NULL]
*		- ["datasource_type"]	- type of datasource by default;	[STRING || NULL]
*		- ["datasources"]		- list of datasources:				[ARRAY]
*									[0] = object of class "datasource", [OBJECT]
*									...
*		- ["directories"]		- list of directories:				[ARRAY]
*									[name] = value,
*									...
*									* where name is a directory name (STRING), value is a path to directory (STRING).
*
*		(!) - required parameters.
*
*
*	Node:
*
*		<sysconfig name="sysconfig1">
*			<added_on>2012-09-19 20:27:55</added_on>
*			<updated_on>2012-09-19 20:27:55</updated_on>
*			<state>1</state>
*			<note>the system configuration of number 1</note>
*			<datasources type="db" name="mysql-test">
*				<datasource type="xml" name="xml-connector">
*					<added_on>2012-09-19 20:27:55</added_on>
*					<updated_on>2012-09-19 20:27:55</updated_on>
*					<state>1</state>
*					<note>test</note>
*					<files>
*						<file id="test" type="xml">test.xml</file>
*						...
*					</files>
*				</datasource>
*				<datasource type="db" name="mysql-test">
*					<added_on>2012-09-19 20:30:35</added_on>
*					<updated_on>2012-09-19 20:30:35</updated_on>
*					<state>1</state>
*					<db_type>mysql</db_type>
*					<hostname>localhost</hostname>
*					<port>3306</port>
*					<database>test</database>
*					<table></table>
*					<user>test_user</user>
*					<password>Abc</password>
*					<characters_coding>utf8</characters_coding>
*					<note>test</note>
*					<tables>
*						<table id="list_contacts">list_contacts</table>
*						...
*					</tables>
*				</datasource>
*				...
*			</datasources>
*			<directories>
*				<directory name="config">path-to/config</directory>
*				<directory name="images">images</directory>
*				<directory name="lib">lib</directory>
*				<directory name="mod">mod</directory>
*				<directory name="patterns">patterns</directory>
*				<directory name="css">css</directory>
*				<directory name="tmp">tmp</directory>
*			</directories>
*		</sysconfig>
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function:	check sysconfig parameters.
*	Input:
*				$params_in - sysconfig parameters.	[ARRAY]
*	Output:
*				true if OK, otherwise - false.	[BOOLEAN]
*	Note:
*				required parameters: name.
*/
function sysconfig_params__check($params_in = null)
{
	global $FL_DEBUG;
	
	if(!is_array($params_in))
	{
		if($FL_DEBUG) echo("Error! Undefined the input argument 'sc_params_in'! [sysconfig.php -> sysconfig_params__check()]");
		return false;
	}
	
	if(empty($params_in["name"]))
	{
		if($FL_DEBUG) echo("Error! Undefined the datasource parameter 'name'! [sysconfig.php -> sysconfig_params__check()]");
		return false;
	}
	
	if(!is_string($params_in["name"]))
	{
		if($FL_DEBUG) echo("Error! Undefined the datasource parameter 'name' (not a string)! [sysconfig.php -> sysconfig_params__check()]");
		return false;
	}
	
	return true;
}


/*	Function:	normalization of sysconfig parameters.
*	Input:	
*				$params_in - link to sysconfig parameters.	[ARRAY]
*	Output:
*				true if OK, otherwise - false.	[BOOLEAN]
*	Note:
*/
function sysconfig_params__normalize(&$params_in)
{
	global $FL_DEBUG;
	
	if(!function_exists("type_of_datetime"))
	{
		if($FL_DEBUG) echo("Error! Function 'type_of_datetime()' not exists! [sysconfig.php -> sysconfig_params__normalize()]");
		return false;
	}
	
	if(!function_exists("sysconfig_params__check"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_params__check()' not exists! [sysconfig.php -> sysconfig_params__normalize()]");
		return false;
	}
	
	if(!empty($params_in))
	{
		if(sysconfig_params__check($params_in))
		{
			if(!isset($params_in["name"])) $params_in["name"] = null;
			if(empty($params_in["name"])) $params_in["name"] = "unknown";
			if(!is_string($params_in["name"])) $params_in["name"] = "unknown";
			
			if(!isset($params_in["added_on"])) $params_in["added_on"] = null;
			if(!type_of_datetime($params_in["added_on"])) $params_in["added_on"] = date("Y-m-d H:i:s");
			
			if(!isset($params_in["updated_on"])) $params_in["updated_on"] = null;
			if(!type_of_datetime($params_in["updated_on"])) $params_in["updated_on"] = date("Y-m-d H:i:s");
			
			if(!isset($params_in["state"]))  $params_in["state"] = 0;
			if(!is_int($params_in["state"])) $params_in["state"] = 0;
			if(!($params_in["state"] == 0 || $params_in["state"] == 1 || $params_in["state"] == 2)) $params_in["state"] = 0;
			
			if(!isset($params_in["note"])) $params_in["note"] = null;
			
			if(!isset($params_in["datasource_name"]))     $params_in["datasource_name"] = null;
			if(!is_string($params_in["datasource_name"])) $params_in["datasource_name"] = null;
			
			if(!isset($params_in["datasource_type"]))     $params_in["datasource_type"] = null;
			if(!is_string($params_in["datasource_type"])) $params_in["datasource_type"] = null;
			
			if(!isset($params_in["datasources"]))    $params_in["datasources"] = null;
			if(!is_array($params_in["datasources"])) $params_in["datasources"] = array();
			
			if(!isset($params_in["directories"]))    $params_in["directories"] = null;
			if(!is_array($params_in["directories"])) $params_in["directories"] = array();
			
			return true;
		}
	}
	
	return false;
}


/*	Function:	get new sysconfig parameters.
*	Input:	
*				$name_in - sysconfig name.	[STRING || NULL]
*	Output:
*				sysconfig parameters.	[ARRAY]
*	Note:
*/
function sysconfig_params__new($name_in = null)
{
	global $FL_DEBUG;
	
	$result = array();
	
	if(!function_exists("sysconfig_params__normalize"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig__normalize()' not exists! [sysconfig.php -> sysconfig_params__new()]");
		return $result;
	}
	
	$result["name"] = (is_string($name_in) ? $name_in : null);
	
	sysconfig_params__normalize($result);
	
	return $result;
}


/*	Function:	get a list of sysconfig names from a root node.
*	Input:	
*				$root_node_in - node object.	[OBJECT]
*	Output:
*				list of sysconfig names.		[ARRAY]
*	Note:
*				the list structure:
*
*					list[0] = "name of sysconfig",
*					...
*					list[N] = "name of sysconfig".
*/
function sysconfig_root_node__get_names($root_node_in = null)
{
	global $FL_DEBUG;
	
	$result = array();
	
	if(!function_exists("get_attribute_of_element"))
	{
		if($FL_DEBUG) echo("Error! Function 'get_attribute_of_element()' not exists! [sysconfig.php -> sysconfig_root_node__get_names()]");
		return $result;
	}
	
	if(!function_exists("phpDOM_parsing"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_parsing()' not exists! [sysconfig.php -> sysconfig_root_node__get_names()]");
		return $result;
	}
	
	$foundNodes = phpDOM_parsing($root_node_in, "^sysconfig$", "name", null);
	
	if(is_array($foundNodes))
	{
		$name = null;
		
		for($i=0; $i<count($foundNodes); $i++)
		{
			$name = get_attribute_of_element($foundNodes[$i], "name");
			if($name) array_push($result, $name);
		}
	}
	
	return $result;
}


/*	Function:	search a sysconfig node in a node.
*	Input:
*				$root_node_in	- node object;		[OBJECT]
*				$name_in		- sysconfig name.	[STRING]
*	Output:
*				sysconfig node or null.	[OBJECT || NULL]
*	Note:
*				the function returns only the first matching node (by name)!
*
*				<sysconfig name="...">...</sysconfig>
*				...
*/
function sysconfig_root_node__search($root_node_in = null, $name_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("phpDOM_parsing"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_parsing()' not exists! [sysconfig.php -> sysconfig_root_node__search()]");
		return null;
	}
	
	if(!empty($name_in))
	{
		if(is_string($name_in))
		{
			$foundNodes = phpDOM_parsing($root_node_in, "^sysconfig$", "name", "^{$name_in}$");
			
			if(is_array($foundNodes))
			{
				return ((count($foundNodes)) ? $foundNodes[0] : null);
			}
		}
	}
	
	return null;
}


/*	Function:	search a node "datasources" in a sysconfig node.
*	Input:
*				$node_in - a sysconfig node.	[OBJECT]
*	Output:
*				node "datasources" or null.	[OBJECT || NULL]
*	Note:
*				the function returns only the first matching node!
*
*				<datasources type="..." name="...">...</datasources>
*/
function sysconfig_node__search_datasources($node_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("phpDOM_parsing"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_parsing()' not exists! [sysconfig.php -> sysconfig_node__search_datasources()]");
		return null;
	}
	
	$foundNodes	= phpDOM_parsing($node_in, "^datasources$", null, null);
	
	if(is_array($foundNodes))
	{
		return ((count($foundNodes)) ? $foundNodes[0] : null);
	}
	
	return null;
}


/*	Function:	get datasource from a node "datasources".
*	Input:
*				$node_in	- node "datasources";	[OBJECT]
*				$ds_name_in	- datasource name;	[STRING]
*				$ds_type_in	- datasource type.	[STRING]
*	Output:
*				object of class "datasource" or null.	[OBJECT || NULL]
*	Note:
*/
function sysconfig_datasources_node__get_datasource($node_in = null, $ds_name_in = null, $ds_type_in = null)
{
	global $FL_DEBUG;
	
	if(!class_exists("datasource"))
	{
		if($FL_DEBUG) echo("Error! Class 'datasource' not exists! [sysconfig.php -> sysconfig_datasources_node__get_datasource()]");
		return null;
	}
	
	$ds = new datasource();
	$ds->get_from_node($node_in, $ds_name_in, $ds_type_in);
	
	return (($ds->check_params()) ? $ds : null);
}


/*	Function:	get list of datasources from a node "datasources".
*	Input:
*				$node_in - node "datasources".	[OBJECT]
*	Output:
*				list of objects of class "datasource".	[ARRAY]
*	Note:
*				the structure of array:
*
*					[0] = object of class "datasource", [OBJECT]
*					...
*/
function sysconfig_datasources_node__get_datasources($node_in = null)
{
	global $FL_DEBUG;
	
	$result = array();
	
	if(!class_exists("datasource"))
	{
		if($FL_DEBUG) echo("Error! Class 'datasource' not exists! [sysconfig.php -> sysconfig_datasources_node__get_datasources()]");
		return $result;
	}
	
	if(!function_exists("sysconfig_datasources_node__get_datasource"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_datasources_node__get_datasource()' not exists! [sysconfig.php -> sysconfig_datasources_node__get_datasources()]");
		return $result;
	}
	
	$ds			= new datasource();
	$listNames	= $ds->get_names_from_node($node_in);
	
	if(is_array($listNames))
	{
		$dsRes		= null;
		$listItem	= null;
		
		for($i=0; $i<count($listNames); $i++)
		{
			$listItem = $listNames[$i];
			
			if(is_array($listItem))
			{
				if(!empty($listItem["name"]) && !empty($listItem["type"]))
				{
					$dsRes = sysconfig_datasources_node__get_datasource($node_in, $listItem["name"], $listItem["type"]);
					if($dsRes) array_push($result, $dsRes);
				}
			}
		}
	}
	
	return $result;
}


/*	Function:	search a node "directories" in a sysconfig node.
*	Input:
*				$node_in - a sysconfig node.	[OBJECT]
*	Output:
*				node "directories" or null.	[OBJECT || NULL]
*	Note:
*				the function returns only the first matching node!
*
*				<directories>...</directories>
*/
function sysconfig_node__search_directories($node_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("phpDOM_parsing"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_parsing()' not exists! [sysconfig.php -> sysconfig_node__search_directories()]");
		return null;
	}
	
	$foundNodes = phpDOM_parsing($node_in, "^directories$", null, null);
	
	if(is_array($foundNodes))
	{
		return ((count($foundNodes)) ? $foundNodes[0] : null);
	}
	
	return null;
}


/*	Function:	get list of directories from node "directories".
*	Input:
*				$node_in - node "directories".	[OBJECT]
*	Output:
*				list of directories.	[ARRAY]
*	Note:
*				The structure of the array:
*
*					- [name] = value;
*					- ...
*
*					* where name is a directory name (STRING), value is a path to directory (STRING).
*/
function sysconfig_directories_node__get_directories($node_in = null)
{
	global $FL_DEBUG;
	
	$result = array();
	
	if(!function_exists("get_attribute_of_element"))
	{
		if($FL_DEBUG) echo("Error! Function 'get_attribute_of_element()' not exists! [sysconfig.php -> sysconfig_directories_node__get_directories()]");
		return $result;
	}
	
	if(!function_exists("phpDOM_parsing"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_parsing()' not exists! [sysconfig.php -> sysconfig_directories_node__get_directories()]");
		return $result;
	}
	
	$foundNodes = phpDOM_parsing($node_in, "^directory$", "name", null);
	
	if(is_array($foundNodes))
	{
		$attrName = null;
		
		for($i=0; $i<count($foundNodes); $i++)
		{
			if(is_object($foundNodes[$i]))
			{
				if(!empty($foundNodes[$i]->nodeValue))
				{
					$attrName = get_attribute_of_element($foundNodes[$i], "name");
					if(!empty($attrName)) $result[$attrName] = $foundNodes[$i]->nodeValue;
				}
			}
		}
	}
	
	return $result;
}


/*	Function:	get a datasource from a sysconfig node.
*	Input:
*				$node_in	- sysconfig node;	[OBJECT]
*				$ds_name_in	- datasource name;	[STRING || NULL]
*				$ds_type_in	- datasource type.	[STRING || NULL]
*	Output:
*				object of class "datasource" or null.	[OBJECT || NULL]
*	Note:
*				If $ds_name_in == null and/or $ds_type_in == null, then used name and type of selected datasource
*					(<datasources name="ds-repos-xml" type="xml">).
*/
function sysconfig_node__get_datasource($node_in = null, $ds_name_in = null, $ds_type_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG) echo("Error! Function 'functions_check_required()' not exists! [sysconfig.php -> sysconfig_node__get_datasource()]");
		return null;
	}
	
	$r_functions = array("get_attribute_of_element",
						 "sysconfig_node__search_datasources",
						 "sysconfig_datasources_node__get_datasource"
						 );
	
	if(!functions_check_required($r_functions, "sysconfig.php", "sysconfig_node__get_datasource()"))
	{
		return null;
	}
	
	$datasourcesNode = sysconfig_node__search_datasources($node_in);
	
	if(is_object($datasourcesNode))
	{
		$ds_name = ((is_string($ds_name_in)) ? $ds_name_in : null);
		$ds_type = ((is_string($ds_type_in)) ? $ds_type_in : null);
		
		if(empty($ds_name)) $ds_name = get_attribute_of_element($datasourcesNode, "name");
		if(empty($ds_type)) $ds_type = get_attribute_of_element($datasourcesNode, "type");
		
		if(!empty($ds_name) && !empty($ds_type))
		{
			return sysconfig_datasources_node__get_datasource($datasourcesNode, $ds_name, $ds_type);
		}
	}
	
	return null;
}


/*	Function:	get list of directories from a sysconfig node.
*	Input:
*				$node_in - sysconfig node.	[OBJECT]
*	Output:
*				list of directories.	[ARRAY]
*	Note:
*				The structure of the array:
*
*					- [name] = value;
*					- ...
*
*					* where name is a directory name (STRING), value is a path to directory (STRING).
*/
function sysconfig_node__get_directories($node_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("sysconfig_node__search_directories"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_node__search_directories()' not exists! [sysconfig.php -> sysconfig_node__get_directories()]");
		return array();
	}
	
	if(!function_exists("sysconfig_directories_node__get_directories"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_directories_node__get_directories()' not exists! [sysconfig.php -> sysconfig_node__get_directories()]");
		return array();
	}
	
	$directoriesNode = sysconfig_node__search_directories($node_in);
	
	return sysconfig_directories_node__get_directories($directoriesNode);
}


/*	Function:	get a sysconfig parameters from a sysconfig node.
*	Input:
*				$node_in - a sysconfig node.		[OBJECT]
*	Output:
*				sysconfig parameters or NULL.	[ARRAY || NULL]
*	Note:
*/
function sysconfig_node__get_params($node_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG) echo("Error! Function 'functions_check_required()' not exists! [sysconfig.php -> sysconfig_node__get_params()]");
		return null;
	}
	
	$r_functions = array("get_attribute_of_element",
						 "phpDOM_get_values_of_nodes_by_params",
						 "sysconfig_params__normalize",
						 "sysconfig_node__search_datasources",
						 "sysconfig_datasources_node__get_datasources",
						 "sysconfig_node__get_directories"
						 );
	
	if(!functions_check_required($r_functions, "sysconfig.php", "sysconfig_node__get_params()"))
	{
		return null;
	}
	
	if(is_object($node_in))
	{
		$name = get_attribute_of_element($node_in, "name");
		
		if(!empty($name))
		{
			$targetChildren = array(array("nodename" => "added_on", "type" => "string", "required" => false, "default_value" => date("Y-m-d H:i:s")),
									array("nodename" => "updated_on", "type" => "string", "required" => false, "default_value" => date("Y-m-d H:i:s")),
									array("nodename" => "state", "type" => "integer", "required" => false, "default_value" => 1),
									array("nodename" => "note", "type" => "string", "required" => false, "default_value" => null)
									);
			
			$params = phpDOM_get_values_of_nodes_by_params($node_in, $targetChildren);
			
			if(is_array($params))
			{
				$datasourcesNode = sysconfig_node__search_datasources($node_in);
				
				$params["name"]				= $name;
				$params["datasource_name"]	= get_attribute_of_element($datasourcesNode, "name");
				$params["datasource_type"]	= get_attribute_of_element($datasourcesNode, "type");
				$params["datasources"]		= sysconfig_datasources_node__get_datasources($datasourcesNode);
				$params["directories"]		= sysconfig_node__get_directories($node_in);
				
				sysconfig_params__normalize($params);
				
				return $params;
			}
		}
	}
	
	return null;
}


/*	Function:	get a sysconfig parameters from a root node.
*	Input:
*				$root_node_in	- node object;		[OBJECT]
*				$name_in		- sysconfig name.	[STRING]
*	Output:
*				sysconfig parameters or NULL.	[ARRAY || NULL]
*	Note:
*/
function sysconfig_root_node__get_params($root_node_in = null, $name_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("sysconfig_root_node__search"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_root_node__search()' not exists! [sysconfig.php -> sysconfig_root_node__get_params()]");
		return null;
	}
	
	if(!function_exists("sysconfig_node__get_params"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_node__get_params()' not exists! [sysconfig.php -> sysconfig_root_node__get_params()]");
		return null;
	}
	
	$scNode = sysconfig_root_node__search($root_node_in, $name_in);
	
	return sysconfig_node__get_params($scNode);
}


/*	Function:	clear a node "datasources".
*	Input:
*				$node_in - link to a node "datasources".	[OBJECT]
*	Output:
*				number of modified nodes.	[NUMBER]
*	Note:
*/
function sysconfig_datasources_node__clear(&$node_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("phpDOM_forming_node"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_forming_node()' not exists! [sysconfig.php -> sysconfig_datasources_node__clear()]");
		return 0;
	}
	
	$formingPattern = array("datasources" => array("remove_childs" => array("node_name" => null, "attr_name" => null, "attr_value" => null)));
	
	return phpDOM_forming_node($node_in, $formingPattern);
}


/*	Function:	clear a node "datasources".
*	Input:
*				$node_in - link to a sysconfig node.	[OBJECT]
*	Output:
*				number of modified nodes.	[NUMBER]
*	Note:
*/
function sysconfig_node__clear_datasources(&$node_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("sysconfig_node__search_datasources"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_node__search_datasources()' not exists! [sysconfig.php -> sysconfig_node__clear_datasources()]");
		return 0;
	}
	
	if(!function_exists("sysconfig_datasources_node__clear"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_datasources_node__clear()' not exists! [sysconfig.php -> sysconfig_node__clear_datasources()]");
		return 0;
	}
	
	$datasourcesNode = sysconfig_node__search_datasources($node_in);
	
	return ((is_object($datasourcesNode)) ? sysconfig_datasources_node__clear($datasourcesNode) : 0);
}


/*	Function:	set the datasource as primary for sysconfig node.
*	Input:
*				$node_in	- link to a sysconfig node;	[OBJECT]
*				$ds_name_in	- datasource name;	[STRING || NULL]
*				$ds_type_in	- datasource type.	[STRING || NULL]
*	Output:
*				object of class "datasource" (selected as primary) or null.	[OBJECT || NULL]
*	Note:
*/
function sysconfig_node__set_datasource_as_primary(&$node_in = null, $ds_name_in = null, $ds_type_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG) echo("Error! Function 'functions_check_required()' not exists! [sysconfig.php -> sysconfig_node__set_datasource_as_primary()]");
		return null;
	}
	
	$r_functions = array("set_attribute_of_element",
						 "sysconfig_node__search_datasources",
						 "sysconfig_datasources_node__get_datasource"
						 );
	
	if(!functions_check_required($r_functions, "sysconfig.php", "sysconfig_node__set_datasource_as_primary()"))
	{
		return null;
	}
	
	$datasourcesNode = sysconfig_node__search_datasources($node_in);
	
	if(is_object($datasourcesNode))
	{
		$ds = sysconfig_datasources_node__get_datasource($datasourcesNode, $ds_name_in, $ds_type_in);
		
		if(is_object($ds))
		{
			set_attribute_of_element($datasourcesNode, "name", $ds_name_in);
			set_attribute_of_element($datasourcesNode, "type", $ds_type_in);
			
			return $ds;
		}
	}
	
	return null;
}


/*	Function:	add (or upgrade) a datasource into a sysconfig node.
*	Input:
*				$node_in	- link to a sysconfig node;			[OBJECT]
*				$ds_in	 	- object of the class "datasource";	[OBJECT]
*				$primary_in	- true if the datasource is primary, otherwise - false (by default).	[BOOLEAN]
*	Output:
*				the copy of added/upgraded the datasource node or null.	[OBJECT || NULL]
*	Note:
*				The datasource will be set as primary for this system configuration if the $primary_in is true!
*/
function sysconfig_node__add_datasource(&$node_in = null, $ds_in = null, $primary_in = false)
{
	global $FL_DEBUG;
	
	if(!class_exists("datasource"))
	{
		if($FL_DEBUG) echo("Error! Class 'datasource' not exists! [sysconfig.php -> sysconfig_node__add_datasource()]");
		return null;
	}
	
	if(!function_exists("sysconfig_node__search_datasources"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_node__search_datasources()' not exists! [sysconfig.php -> sysconfig_node__add_datasource()]");
		return null;
	}
	
	if(!function_exists("sysconfig_node__set_datasource_as_primary"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_node__set_datasource_as_primary()' not exists! [sysconfig.php -> sysconfig_node__add_datasource()]");
		return null;
	}
	
	if(is_object($ds_in))
	{
		if(is_a($ds_in, "datasource"))
		{
			if($ds_in->check_params())
			{
				$datasourcesNode = sysconfig_node__search_datasources($node_in);
				
				if(is_object($datasourcesNode))
				{
					//add datasource node into list of datasources of the sysconfig
					$dsNode = $ds_in->add_into_node($datasourcesNode);
					
					if(is_object($dsNode))
					{
						if(is_bool($primary_in))
						{
							if($primary_in) sysconfig_node__set_datasource_as_primary($node_in, $ds_in->params["name"], $ds_in->params["type"]);
						}
						
						return $dsNode;
					}
				}
			}
		}
	}
	
	return null;
}

/*	Function:	remove a datasource from a sysconfig node.
*	Input:
*				$node_in	- link to a sysconfig node;			[OBJECT]
*				$ds_in	 	- object of the class "datasource".	[OBJECT]
*	Output:
*				the copy of removed datasource node or null.	[OBJECT || NULL]
*	Note:
*/
function sysconfig_node__remove_datasource(&$node_in = null, $ds_in = null)
{
	global $FL_DEBUG;
	
	if(!class_exists("datasource"))
	{
		if($FL_DEBUG) echo("Error! Class 'datasource' not exists! [sysconfig.php -> sysconfig_node__remove_datasource()]");
		return null;
	}
	
	if(!function_exists("sysconfig_node__search_datasources"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_node__search_datasources()' not exists! [sysconfig.php -> sysconfig_node__remove_datasource()]");
		return null;
	}
	
	if(is_object($ds_in))
	{
		if(is_a($ds_in, "datasource"))
		{
			if($ds_in->check_params())
			{
				$datasourcesNode = sysconfig_node__search_datasources($node_in);
				
				return $dsNode;
			}
		}
	}
	
	return null;
}


/*	Function:	clear a node "directories".
*	Input:
*				$node_in - link to a node "directories".	[OBJECT]
*	Output:
*				number of modified nodes.	[NUMBER]
*	Note:
*/
function sysconfig_directories_node__clear(&$node_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("phpDOM_forming_node"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_forming_node()' not exists! [sysconfig.php -> sysconfig_directories_node__clear()]");
		return 0;
	}
	
	$formingPattern = array("directories" => array("remove_childs" => array("node_name" => null, "attr_name" => null, "attr_value" => null)));
	
	return phpDOM_forming_node($node_in, $formingPattern);
}


/*	Function:	clear a node "directories".
*	Input:
*				$node_in - link to a sysconfig node.	[OBJECT]
*	Output:
*				number of modified nodes.	[NUMBER]
*	Note:
*/
function sysconfig_node__clear_directories(&$node_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("sysconfig_node__search_directories"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_node__search_directories()' not exists! [sysconfig.php -> sysconfig_node__clear_directories()]");
		return 0;
	}
	
	if(!function_exists("sysconfig_directories_node__clear"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_directories_node__clear()' not exists! [sysconfig.php -> sysconfig_node__clear_directories()]");
		return 0;
	}
	
	$dirsNode = sysconfig_node__search_directories($node_in);
	
	return ((is_object($dirsNode)) ? sysconfig_directories_node__clear($dirsNode) : 0);
}


/*	Function:	add (or upgrade) directories into a sysconfig node.
*	Input:
*				$node_in	- link to a sysconfig node;	[OBJECT]
*				$dirs_in	- list of directories.	[ARRAY]
*	Output:
*				the copy of added/upgraded node "directories" or null.	[OBJECT || NULL]
*	Note:
*				the last directories will be replaced to new!
*
*				The structure of list of directories:
*
*					- [name] = value;
*					- ...
*
*					* where name is a directory name (STRING), value is a path to directory (STRING).
*/
function sysconfig_node__add_directories(&$node_in = null, $dirs_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG) echo("Error! Function 'functions_check_required()' not exists! [sysconfig.php -> sysconfig_node__add_directories()]");
		return null;
	}
	
	$r_functions = array("phpDOM_get_root_node_from_string",
						 "phpDOM_forming_node",
						 "sysconfig_node__search_directories"
						 );
	
	if(!functions_check_required($r_functions, "sysconfig.php", "sysconfig_node__add_directories()"))
	{
		return null;
	}
	
	if(is_array($dirs_in))
	{
		$dirsNode = sysconfig_node__search_directories($node_in);
		
		if(is_object($dirsNode))
		{
			$formingPattern = array("directories" => array("attach_node" => null, "attach_position" => "replace_all"));
			
			foreach($dirs_in as $k=>$v)
			{
				if(!empty($k) && !empty($v))
				{
					if(is_string($k) && is_string($v))
					{
						//create node "directory" with value from input list
						$formingPattern["directories"]["attach_node"] = phpDOM_get_root_node_from_string("<directory name=\"{$k}\">{$v}</directory>", "XML");
						
						//add the node into node "directories"
						if(phpDOM_forming_node($dirsNode, $formingPattern))
						{
							//position "replace_all" is only for the first node, next nodes added into end of node "directories"
							$formingPattern["directories"]["attach_position"] = null;
						}
					}
				}
			}
			
			return $dirsNode;
		}
	}
	
	return null;
}


/*	Function:	create sysconfig node.
*	Input:
*				$params_in - sysconfig parameters.	[ARRAY]
*	Output:
*				sysconfig node or null.	[OBJECT || NULL]
*	Note:
*/
function sysconfig_params__create_node($params_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG) echo("Error! Function 'functions_check_required()' not exists! [sysconfig.php -> sysconfig_params__create_node()]");
		return null;
	}
	
	$r_functions = array("phpDOM_attach_node",
						 "phpDOM_forming_node",
						 "phpDOM_get_root_node_from_string",
						 "sysconfig_params__normalize",
						 "sysconfig_node__set_datasource_as_primary",
						 "sysconfig_node__add_datasource",
						 "sysconfig_node__add_directories"
						 );
	
	if(!functions_check_required($r_functions, "sysconfig.php", "sysconfig_params__create_node()"))
	{
		return null;
	}
	
	if(is_array($params_in))
	{
		$params = $params_in;
		
		if(sysconfig_params__normalize($params))
		{
			//create new node "sysconfig"
			$scNode = phpDOM_get_root_node_from_string("<sysconfig name=\"".$params["name"]."\"></sysconfig>", "XML");
			
			if($scNode)
			{
				//create new node "datasources"
				$datasourcesNode = phpDOM_get_root_node_from_string("<datasources></datasources>", "XML");
				$datasourcesNode = phpDOM_attach_node($scNode, $datasourcesNode, "end");
				
				//create new node "directories"
				$dirsNode = phpDOM_get_root_node_from_string("<directories></directories>", "XML");
				$dirsNode = phpDOM_attach_node($scNode, $dirsNode, "end");
				
				//add (or upgrade) the datasources
				for($i=0; $i<count($params["datasources"]); $i++)
				{
					sysconfig_node__add_datasource($scNode, $params["datasources"][$i], false);
				}
				
				//set primary datasource
				if(is_string($params["datasource_name"]) && is_string($params["datasource_type"]))
				{
					sysconfig_node__set_datasource_as_primary($scNode, $params["datasource_name"], $params["datasource_type"]);
				}
				
				//add (or upgrade) a list of directories
				sysconfig_node__add_directories($scNode, $params["directories"]);
				
				$formingPattern = array("root"        => array("remove_childs" => array("node_name" => "^added_on$|^updated_on$|^state$|^note$", "attr_name" => null, "attr_value" => null), "attributes" => array("name" => $params["name"])),
									 	"node"        => array("attach_node" => phpDOM_get_root_node_from_string(("<note>").($params["note"]).("</note>"), "XML"), "attach_position" => "start"),
									 	"state"       => array("attach_node" => phpDOM_get_root_node_from_string(("<state>").($params["state"]).("</state>"), "XML"), "attach_position" => "start"),
										"updated_on"  => array("attach_node" => phpDOM_get_root_node_from_string(("<updated_on>").($params["updated_on"]).("</updated_on>"), "XML"), "attach_position" => "start"),
										"added_on"    => array("attach_node" => phpDOM_get_root_node_from_string(("<added_on>").($params["added_on"]).("</added_on>"), "XML"), "attach_position" => "start")
									 	);
				
				return ((phpDOM_forming_node($scNode, $formingPattern)) ? $scNode : null);
			}
		}
	}
	
	return null;
}


/*	Function:	add (or upgrade) a sysconfig into a root node.
*	Input:
*				$root_node_in	- link to a root node;	[OBJECT]
*				$params_in		- sysconfig parameters.	[ARRAY]
*	Output:
*				the copy of added/apgraded sysconfig node or null.	[OBJECT || NULL]
*	Note:
*/
function sysconfig_root_node__add(&$root_node_in = null, $params_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG) echo("Error! Function 'functions_check_required()' not exists! [sysconfig.php -> sysconfig_root_node__add()]");
		return null;
	}
	
	$r_functions = array("phpDOM_attach_node",
						 "phpDOM_forming_node",
						 "phpDOM_get_root_node_from_string",
						 "sysconfig_params__normalize",
						 "sysconfig_root_node__search",
						 "sysconfig_node__search_datasources",
						 "sysconfig_node__search_directories",
						 "sysconfig_node__set_datasource_as_primary",
						 "sysconfig_node__add_datasource",
						 "sysconfig_node__add_directories"
						 );
	
	if(!functions_check_required($r_functions, "sysconfig.php", "sysconfig_root_node__add()"))
	{
		return null;
	}
	
	if(is_object($root_node_in) && is_array($params_in))
	{
		$params = $params_in;
		
		if(sysconfig_params__normalize($params))
		{
			$scNode = sysconfig_root_node__search($root_node_in, $params["name"]);
			
			if(!$scNode)
			{
				//create new node "sysconfig"
				$scNode = phpDOM_get_root_node_from_string("<sysconfig name=\"".$params["name"]."\"></sysconfig>", "XML");
				
				//attach the new node into the root-node
				$scNode = phpDOM_attach_node($root_node_in, $scNode, "end");
			}
			
			$datasourcesNode = sysconfig_node__search_datasources($scNode);
			
			if(!$datasourcesNode)
			{
				//create new node "datasources"
				$datasourcesNode = phpDOM_get_root_node_from_string("<datasources></datasources>", "XML");
				
				//attach the new node into the sysconfig-node
				$datasourcesNode = phpDOM_attach_node($scNode, $datasourcesNode, "end");
			}
			
			$dirsNode = sysconfig_node__search_directories($scNode);
			
			if(!$dirsNode)
			{
				//create new node "directories"
				$dirsNode = phpDOM_get_root_node_from_string("<directories></directories>", "XML");
				
				//attach the new node into the sysconfig-node
				$dirsNode = phpDOM_attach_node($scNode, $dirsNode, "end");
			}
			
			//add (or upgrade) the datasources
			for($i=0; $i<count($params["datasources"]); $i++)
			{
				sysconfig_node__add_datasource($scNode, $params["datasources"][$i], false);
			}
			
			//set primary datasource
			if(is_string($params["datasource_name"]) && is_string($params["datasource_type"]))
			{
				sysconfig_node__set_datasource_as_primary($scNode, $params["datasource_name"], $params["datasource_type"]);
			}
			
			//add (or upgrade) a list of directories
			sysconfig_node__add_directories($scNode, $params["directories"]);
			
			$formingPattern = array("root"        => array("remove_childs" => array("node_name" => "^added_on$|^updated_on$|^state$|^note$", "attr_name" => null, "attr_value" => null), "attributes" => array("name" => $params["name"])),
								 	"node"        => array("attach_node" => phpDOM_get_root_node_from_string(("<note>").($params["note"]).("</note>"), "XML"), "attach_position" => "start"),
								 	"state"       => array("attach_node" => phpDOM_get_root_node_from_string(("<state>").($params["state"]).("</state>"), "XML"), "attach_position" => "start"),
									"updated_on"  => array("attach_node" => phpDOM_get_root_node_from_string(("<updated_on>").($params["updated_on"]).("</updated_on>"), "XML"), "attach_position" => "start"),
									"added_on"    => array("attach_node" => phpDOM_get_root_node_from_string(("<added_on>").($params["added_on"]).("</added_on>"), "XML"), "attach_position" => "start")
								 	);
			
			return ((phpDOM_forming_node($scNode, $formingPattern)) ? $scNode : null);
		}
	}
	
	return null;
}


/*	Function:	remove a sysconfig from a root node.
*	Input:
*				$root_node_in	- link to a root node;	[OBJECT]
*				$name_in		- a sysconfig name.		[STRING]
*	Output:
*				the copy of old sysconfig node or null.	[OBJECT || NULL]
*	Note:
*/
function sysconfig_root_node__remove(&$root_node_in = null, $name_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("phpDOM_remove_node"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_remove_node()' not exists! [sysconfig.php -> sysconfig_root_node__remove()]");
		return null;
	}
	
	if(!function_exists("sysconfig_root_node__search"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_root_node__search()' not exists! [sysconfig.php -> sysconfig_root_node__remove()]");
		return null;
	}
	
	if(is_object($root_node_in) && is_string($name_in))
	{
		$scNode = sysconfig_root_node__search($root_node_in, $name_in);
		
		if($scNode)
		{
			return phpDOM_remove_node($scNode);
		}
	}
	
	return null;
}


/*	Function:	get a list of sysconfig names from a XML-file.
*	Input:	
*				$file_in - a file name.	[STRING]
*	Output:
*				list of sysconfig names.		[ARRAY]
*	Note:
*				the list structure:
*
*					list[0] = "name of sysconfig",
*					...
*					list[N] = "name of sysconfig".
*/
function sysconfig_file__get_names($file_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("phpDOM_get_root_node_from_file"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_get_root_node_from_file()' not exists! [sysconfig.php -> sysconfig_file__get_names()]");
		return array();
	}
	
	if(!function_exists("sysconfig_root_node__get_names"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_root_node__get_names()' not exists! [sysconfig.php -> sysconfig_file__get_names()]");
		return array();
	}
	
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	return sysconfig_root_node__get_names($root_node);
}


/*	Function:	get a sysconfig parameters from a XML-file.
*	Input:
*				$file_in	- a file name;		[STRING]
*				$name_in	- sysconfig name.	[STRING]
*	Output:
*				sysconfig parameters or NULL.	[ARRAY || NULL]
*	Note:
*/
function sysconfig_file__get_params($file_in = null, $name_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("phpDOM_get_root_node_from_file"))
	{
		if($FL_DEBUG) echo("Error! Function 'phpDOM_get_root_node_from_file()' not exists! [sysconfig.php -> sysconfig_file__get_names()]");
		return null;
	}
	
	if(!function_exists("sysconfig_root_node__get_params"))
	{
		if($FL_DEBUG) echo("Error! Function 'sysconfig_root_node__get_params()' not exists! [sysconfig.php -> sysconfig_file__get_params()]");
		return null;
	}
	
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	return sysconfig_root_node__get_params($root_node, $name_in);
}


/*	Function:	add (or upgrade) a sysconfig into a XML-file.
*	Input:
*				$file_in			- a file name;	[STRING]
*				$params_in			- sysconfig parameters;	[ARRAY]
*				$root_node_name_in	- a root-node name or NULL.	[STRING || NULL]
*	Output:
*				the copy of added/apgraded sysconfig node or null.	[OBJECT || NULL]
*	Note:
*				if $root_node_name_in == NULL, then will be used the root-node of a XML-file!
*/
function sysconfig_file__add($file_in = null, $params_in = null, $root_node_name_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG) echo("Error! Function 'functions_check_required()' not exists! [sysconfig.php -> sysconfig_file__add()]");
		return null;
	}
	
	$r_functions = array("phpDOM_parsing",
						 "phpDOM_get_root_node_from_string",
						 "phpDOM_get_root_node_from_file",
						 "phpDOM_write_document_to_file",
						 "sysconfig_root_node__add"
						 );
	
	if(!functions_check_required($r_functions, "sysconfig.php", "sysconfig_file__add()"))
	{
		return null;
	}
	
	$root_node = phpDOM_get_root_node_from_file($file_in, "xml");
	
	if(!$root_node)
	{
		//create new root-node
		$root_node = phpDOM_get_root_node_from_string("<body></body>", "xml");
	}
	
	$used_root_node = $root_node;
	
	if(!empty($root_node_name_in))
	{
		if(is_string($root_node_name_in))
		{
			$foundNodes = phpDOM_parsing($root_node, "^{$root_node_name_in}$", null, null);
			
			if(is_array($foundNodes))
			{
				if(count($foundNodes))
				{
					$used_root_node = $foundNodes[0];
				}
			}
		}
	}
	
	$scNode = sysconfig_root_node__add($used_root_node, $params_in);
	
	if($scNode)
	{
		//rewrite the XML-file
		if(phpDOM_write_document_to_file($root_node, $file_in, "xml"))
		{
			return $scNode;
		}
	}
	
	return null;
}


/*	Function:	remove a sysconfig from a XML-file.
*	Input:
*				$file_in	- a file name;	[STRING]
*				$name_in	- a sysconfig name.	[STRING]
*	Output:
*				the copy of old sysconfig node or null.	[OBJECT || NULL]
*	Note:
*/
function sysconfig_file__remove($file_in = null, $name_in = null)
{
	global $FL_DEBUG;
	
	if(!function_exists("functions_check_required"))
	{
		if($FL_DEBUG) echo("Error! Function 'functions_check_required()' not exists! [sysconfig.php -> sysconfig_file__remove()]");
		return null;
	}
	
	$r_functions = array("phpDOM_get_root_node_from_file",
						 "phpDOM_write_document_to_file",
						 "sysconfig_root_node__remove"
						 );
	
	if(!functions_check_required($r_functions, "sysconfig.php", "sysconfig_file__remove()"))
	{
		return null;
	}
	
	$root_node	= phpDOM_get_root_node_from_file($file_in, "xml");
	$scNode		= sysconfig_root_node__remove($root_node, $name_in);
	
	if($scNode)
	{
		//rewrite a file
		if(phpDOM_write_document_to_file($root_node, $file_in, "xml"))
		{
			return $scNode;
		}
	}
	
	return null;
}


//** CLASSES

class sysconfig
{
	//Options
	
	//** state types
	const UNUSED	= 0;
	const USED		= 1;
	const REMOVED	= 2;
	
	
	//** public
	
	//* sysconfig name					[STRING || NULL]
	public $name;
	
	//* date and time of publication	[TIMESTAMP AS INTEGER]
	public $added_on;
	
	//* date and time of modification	[TIMESTAMP AS INTEGER]
	public $updated_on;
	
	//* state (UNUSED by default)		[INTEGER]
	public $state;
	
	//* note							[STRING || NULL]
	public $note;
	
	//* name of datasource by default	[STRING || NULL]
	public $datasource_name;
	
	//* type of datasource by default	[STRING || NULL]
	public $datasource_type;
	
	//* list of datasources				[ARRAY]
	public $datasources;
	
	//* list of directories				[ARRAY]
	public $directories;
	
	
	//** private
	
	
	//Methods
	
	//*	method:	search a sysconfig node in a root node.
	//*	input:
	//*			$root_node_in	- root node;		[OBJECT]
	//*			$name_in		- sysconfig name.	[STRING]
	//*	output:
	//*			sysconfig node or null.	[OBJECT || NULL]
	//*	note:
	//*			the function returns only the first matching node (by name)!
	//*
	//*			<sysconfig name="...">...</sysconfig>
	//*			...
	//*
	public static function _searchInRootNode($root_node_in = null, $name_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_root_node__search"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_root_node__search()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_root_node__search($root_node_in, $name_in);
	}
	
	//*	method: get list of sysconfig names from a root node.
	//*	input:
	//*			$root_node_in - a root node.	[OBJECT]
	//*	output:
	//*			list of sysconfig names.	[ARRAY]
	//*	note:
	//*			structure of the list:
	//*
	//*				list[0] = "name of sysconfig",
	//*				...
	//*				list[N] = "name of sysconfig".
	//*
	public static function _getNamesFromRootNode($root_node_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_root_node__get_names"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_root_node__get_names()' not exists! [sysconfig.php -> class sysconfig]");
			return array();
		}
		
		return sysconfig_root_node__get_names($root_node_in);
	}
	
	//*	method: get list of sysconfig names from a XML-file.
	//*	input:
	//*			$file_in - a file name.	[STRING]
	//*	output:
	//*			list of sysconfig names.	[ARRAY]
	//*	note:
	//*			structure of the list:
	//*
	//*				list[0] = "name of sysconfig",
	//*				...
	//*				list[N] = "name of sysconfig".
	//*
	public static function _getNamesFromFile($file_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_file__get_names"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_file__get_names()' not exists! [sysconfig.php -> class sysconfig]");
			return array();
		}
		
		return sysconfig_file__get_names($file_in);
	}
	
	//*	method:	get a sysconfig parameters from a sysconfig node.
	//*	input:
	//*			$node_in - a sysconfig node.	[OBJECT]
	//*	output:
	//*			sysconfig parameters or NULL.	[ARRAY || NULL]
	//*	note:
	//*
	public static function _getParamsFromNode($node_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__get_params"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__get_params()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_node__get_params($node_in);
	}
	
	//*	method: get sysconfig parameters from a root node.
	//*	input:
	//*			$root_node_in	- root node;	[OBJECT]
	//*			$name_in		- sysconfig name.	[STRING]
	//*	output:
	//*			sysconfig parameters or NULL.	[ARRAY || NULL]
	//*	note:
	//*
	public static function _getParamsFromRootNode($root_node_in = null, $name_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_root_node__get_params"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_root_node__get_params()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_root_node__get_params($root_node_in, $name_in);
	}
	
	//*	method: get a sysconfig parameters from a XML-file.
	//*	input:
	//*			$file_in	- a file name;		[STRING]
	//*			$name_in	- sysconfig name.	[STRING]
	//*	output:
	//*			sysconfig parameters or NULL.	[ARRAY || NULL]
	//*	note:
	//*
	public static function _getParamsFromFile($file_in = null, $name_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_file__get_params"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_file__get_params()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_file__get_params($file_in, $name_in);
	}
	
	//*	method:	create sysconfig node.
	//*	input:
	//*			$params_in - sysconfig parameters.	[ARRAY]
	//*	output:
	//*			sysconfig node or null.	[OBJECT || NULL]
	//*	note:
	//*
	public static function _createNode($params_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_params__create_node"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_params__create_node()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_params__create_node($params_in);
	}
	
	//*	method: add (or upgrade) a sysconfig into a root node.
	//*	input:
	//*			root_node_in	- link to a root node;	[OBJECT]
	//*			$params_in		- sysconfig parameters.	[ARRAY]
	//*	output:
	//*			the copy of added/apgraded sysconfig node or null.	[OBJECT || NULL]
	//*	note:
	//*
	public static function _addParamsIntoRootNode(&$root_node_in = null, $params_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_root_node__add"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_root_node__add()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_root_node__add($root_node_in, $params_in);
	}
	
	//*	method: add (or upgrade) a sysconfig into a XML-file.
	//*	input:
	//*			$file_in			- a file name;	[STRING]
	//*			$params_in			- sysconfig parameters;	[ARRAY]
	//*			$root_node_name_in	- a root-node name or NULL.	[STRING || NULL]
	//*	output:
	//*			the copy of added/apgraded sysconfig node or null.	[OBJECT || NULL]
	//*	note:
	//*			if $root_node_name_in == NULL, then will be used the root-node of a XML-file!
	//*
	public static function _addParamsIntoFile($file_in = null, $params_in = null, $root_node_name_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_file__add"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_file__add()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_file__add($file_in, $params_in, $root_node_name_in);
	}
	
	//*	method: remove a sysconfig from a root node.
	//*	input:
	//*			root_node_in	- link to a root node;	[OBJECT]
	//*			$name_in		- a sysconfig name.		[STRING]
	//*	output:
	//*			the copy of old sysconfig node or null.	[OBJECT || NULL]
	//*	note:
	//*
	public static function _removeFromRootNode(&$root_node_in = null, $name_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_root_node__add"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_root_node__add()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_root_node__remove($root_node_in, $name_in);
	}
	
	//*	method: remove a sysconfig from a XMK-file.
	//*	input:
	//*			$file_in	- a file name;	[STRING]
	//*			$name_in	- a sysconfig name.	[STRING]
	//*	output:
	//*			the copy of old sysconfig node or null.	[OBJECT || NULL]
	//*	note:
	//*
	public static function _removeFromFile($file_in = null, $name_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_file__add"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_file__add()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_file__remove($file_in, $name_in);
	}
	
	//*	method:	get list of datasources from a sysconfig node.
	//*	input:
	//*			$node_in - sysconfig node.	[OBJECT]
	//*	output:
	//*			list of objects of class "datasource".	[ARRAY]
	//*	note:
	//*			the structure of array:
	//*
	//*				[0] = object of class "datasource", [OBJECT]
	//*				...
	//*
	public static function _getDatasourcesFromNode($node_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__search_datasources"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__search_datasources()' not exists! [sysconfig.php -> class sysconfig]");
			return array();
		}
		
		if(!function_exists("sysconfig_datasources_node__get_datasources"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_datasources_node__get_datasources()' not exists! [sysconfig.php -> class sysconfig]");
			return array();
		}
		
		$datasourcesNode = sysconfig_node__search_datasources($node_in);
		
		return ((is_object($datasourcesNode)) ? sysconfig_datasources_node__get_datasources($datasourcesNode) : array());
	}
	
	//*	method:	get a datasource from a sysconfig node.
	//*	input:
	//*			$node_in	- sysconfig node;	[OBJECT]
	//*			$ds_name_in	- datasource name;	[STRING || NULL]
	//*			$ds_type_in	- datasource type.	[STRING || NULL]
	//*	output:
	//*			object of class "datasource" or null.	[OBJECT || NULL]
	//*	note:
	//*			If $ds_name_in == null and/or $ds_type_in == null, then used name and type of selected datasource
	//*				(<datasources name="ds-repos-xml" type="xml">).
	//*
	public static function _getDatasourceFromNode($node_in = null, $ds_name_in = null, $ds_type_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__get_datasource"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__get_datasource()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_node__get_datasource($node_in, $ds_name_in, $ds_type_in);
	}
	
	//*	method:	clear datasources in a sysconfig node.
	//*	input:
	//*			$node_in - link to a sysconfig node.	[OBJECT]
	//*	output:
	//*			number of modified nodes.	[NUMBER]
	//*	note:
	//*
	public static function _clearDatasourcesNode(&$node_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__clear_datasources"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__clear_datasources()' not exists! [sysconfig.php -> class sysconfig]");
			return 0;
		}
		
		return sysconfig_node__clear_datasources($node_in);
	}
	
	//*	method:	set the datasource as primary for sysconfig node.
	//*	input:
	//*			$node_in	- link to a sysconfig node;	[OBJECT]
	//*			$ds_name_in	- datasource name;	[STRING || NULL]
	//*			$ds_type_in	- datasource type.	[STRING || NULL]
	//*	output:
	//*			object of class "datasource" (selected as primary) or null.	[OBJECT || NULL]
	//*	note:
	//*
	public static function _setDatasourceAsPrimary(&$node_in = null, $ds_name_in = null, $ds_type_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__set_datasource_as_primary"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__set_datasource_as_primary()' not exists! [sysconfig.php -> class sysconfig]");
			return 0;
		}
		
		return sysconfig_node__set_datasource_as_primary($node_in, $ds_name_in, $ds_type_in);
	}
	
	//*	method:	add (or upgrade) a datasource into a sysconfig node.
	//*	input:
	//*			$node_in	- link to a sysconfig node;	[OBJECT]
	//*			$ds_in	 	- object of the class "datasource";	[OBJECT]
	//*			$primary_in	- true if the datasource is primary, otherwise - false (by default).	[BOOLEAN]
	//*	output:
	//*			the copy of added/upgraded the datasource node or null.	[OBJECT || NULL]
	//*	note:
	//*			The datasource will be set as primary for this system configuration if the $primary_in is true!
	//*
	public static function _addDatasourceIntoNode(&$node_in = null, $ds_in = null, $primary_in = false) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__add_datasource"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__add_datasource()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_node__add_datasource($node_in, $ds_in, $primary_in);
	}
	
	//*	method:	remove a datasource from a sysconfig node.
	//*	input:
	//*			$node_in	- link to a sysconfig node;			[OBJECT]
	//*			$ds_in	 	- object of the class "datasource".	[OBJECT]
	//*	output:
	//*			the copy of removed datasource node or null.	[OBJECT || NULL]
	//*	note:
	//*
	public static function _removeDatasourceFromNode(&$node_in = null, $ds_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__remove_datasource"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__remove_datasource()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_node__remove_datasource($node_in, $ds_in);
	}
	
	//*	method:	get list of directories from a sysconfig node.
	//*	input:
	//*			$node_in - sysconfig node.	[OBJECT]
	//*	output:
	//*			list of directories.	[ARRAY]
	//*	note:
	//*				The structure of the array:
	//*
	//*					- [name] = value;
	//*					- ...
	//*
	//*					* where name is a directory name (STRING), value is a path to directory (STRING).
	//*
	public static function _getDirectoriesFromNode($node_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__get_directories"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__get_directories()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_node__get_directories($node_in);
	}
	
	//*	method:	clear directories in a sysconfig node.
	//*	input:
	//*			$node_in - link to a sysconfig node.	[OBJECT]
	//*	output:
	//*			number of modified nodes.	[NUMBER]
	//*	note:
	//*
	public static function _clearDirectoriesNode(&$node_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__clear_directories"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__clear_directories()' not exists! [sysconfig.php -> class sysconfig]");
			return 0;
		}
		
		return sysconfig_node__clear_directories($node_in);
	}
	
	//*	method:	add (or upgrade) directories into a sysconfig node.
	//*	input:
	//*			$node_in	- link to a sysconfig node;	[OBJECT]
	//*			$dirs_in	- list of directories.	[ARRAY]
	//*	output:
	//*			the copy of added/upgraded node "directories" or null.	[OBJECT || NULL]
	//*	note:
	//*			the last directories will be replaced to new!
	//*
	//*			The structure of list of directories:
	//*
	//*				- [name] = value;
	//*				- ...
	//*
	//*				* where name is a directory name (STRING), value is a path to directory (STRING).
	//*
	public static function _addDirectoriesIntoNode(&$node_in = null, $dirs_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("sysconfig_node__add_directories"))
		{
			if($FL_DEBUG) echo("Error! Function 'sysconfig_node__add_directories()' not exists! [sysconfig.php -> class sysconfig]");
			return null;
		}
		
		return sysconfig_node__add_directories($node_in, $dirs_in);
	}
	
	//*	method:	refresh value of option $added_on.
	//*	input:
	//*			none.
	//*	output:
	//*			none.
	//*	note:
	public function refreshAddedOn() {
		
		$this->added_on = date("Y-m-d H:i:s");
	}
	
	//*	method:	refresh value of option $updated_on.
	//*	input:
	//*			none.
	//*	output:
	//*			none.
	//*	note:
	public function refreshUpdatedOn() {
		
		$this->updated_on = date("Y-m-d H:i:s");
	}
	
	//*	method:	normalization of values.
	//*	input:
	//*			none.
	//*	output:
	//*			none.
	//*	note:
	function normalize() {
		
		if(empty($this->name))         $this->name = "unknown";
		if(!is_string($this->name))    $this->name = "unknown";
		
		if(function_exists("type_of_datetime"))
		{
			$this->added_on   = type_of_datetime($this->added_on);
			$this->updated_on = type_of_datetime($this->updated_on);
			
			if(empty($this->added_on))       $this->refreshAddedOn();
			if(!is_string($this->added_on))  $this->refreshAddedOn();
			
			if(empty($this->updated_on))      $this->refreshUpdatedOn();
			if(!is_string($this->updated_on)) $this->refreshUpdatedOn();
		}
		else
		{
			$this->refreshAddedOn();
			$this->refreshUpdatedOn();
		}
		
		if(!is_int($this->state)) $this->state = self::UNUSED;
		$this->state = (($this->state == self::UNUSED || $this->state == self::USED || $this->state == self::REMOVED) ? $this->state : self::UNUSED);
		
		if(!is_string($this->datasource_name)) $this->datasource_name = null;
		if(!is_string($this->datasource_type)) $this->datasource_type = null;
		
		if(!is_array($this->datasources)) $this->datasources = array();
		if(!is_array($this->directories)) $this->directories = array();
	}
	
	//*	method:	clear values.
	//*	input:
	//*			none.
	//*	output:
	//*			none.
	//*	note:
	function clear() {
		
		$this->refreshAddedOn();
		$this->refreshUpdatedOn();
		
		$this->name				= "unknown";
		$this->state			= self::UNUSED;
		$this->datasource_name	= null;
		$this->datasource_type	= null;
		$this->datasources		= array();
		$this->directories		= array();
	}
	
	//*	method: get sysconfig parameters.
	//*	input:
	//*			none.
	//*	output:
	//*			sysconfig parameters.	[ARRAY]
	//*	note:
	//*
	public function getParams() {
		
		$params = array();
		
		$this->normalize();
		
		$params["name"]				= $this->name;
		$params["added_on"]			= $this->added_on;
		$params["updated_on"]		= $this->updated_on;
		$params["state"]			= $this->state;
		$params["note"]				= $this->note;
		$params["datasource_name"]	= $this->datasource_name;
		$params["datasource_type"]	= $this->datasource_type;
		$params["datasources"]		= $this->datasources;
		$params["directories"]		= $this->directories;
		
		return $params;
	}
	
	//*	method: create node.
	//*	input:
	//*			none.
	//*	output:
	//*			sysconfig node.	[OBJECT]
	//*	note:
	//*
	public function createNode() {
		
		$params = $this->getParams();
		
		return self::_createNode($params);
	}
	
	//*	method:	set values from list of parameters.
	//*	input:
	//*			$params_in - sysconfig parameters.	[ARRAY]
	//*	output:
	//*			true if the values extracted, otherwise - false.	[BOOLEAN]
	//*	note:
	//*
	public function setValuesFromParams($params_in = null) {
		
		if(is_array($params_in))
		{
			if(!empty($params_in["name"]))
			{
				if(is_string($params_in["name"]))
				{
					$this->clear();
					
					$this->name				= $params_in["name"];
					$this->added_on			= ((is_string($params_in["added_on"])) ? $params_in["added_on"] : null);
					$this->updated_on		= ((is_string($params_in["updated_on"])) ? $params_in["updated_on"] : null);
					$this->state			= ((is_int($params_in["state"])) ? $params_in["state"] : 0);
					$this->note				= ((is_string($params_in["note"])) ? $params_in["note"] : null);
					$this->datasource_name	= ((is_string($params_in["datasource_name"])) ? $params_in["datasource_name"] : null);
					$this->datasource_type	= ((is_string($params_in["datasource_type"])) ? $params_in["datasource_type"] : null);
					$this->datasources		= ((is_array($params_in["datasources"])) ? $params_in["datasources"] : null);
					$this->directories		= ((is_array($params_in["directories"])) ? $params_in["directories"] : null);
					
					$this->normalize();
					
					return true;
				}
			}
		}
		
		return false;
	}
	
	//*	method:	set values from a sysconfig node.
	//*	input:
	//*			$node_in - a sysconfig node.	[OBJECT]
	//*	output:
	//*			true if the values extracted, otherwise - false.	[BOOLEAN]
	//*	note:
	//*
	public function setValuesFromNode($node_in = null) {
		
		$params = self::_getParamsFromNode($node_in);
		
		return $this->setValuesFromParams($params);
	}
	
	//*	method:	set values from a root node.
	//*	input:
	//*			$root_node_in	- a root node;	[OBJECT]
	//*			$name_in		- sysconfig name or NULL.	[STRING || NULL]
	//*	output:
	//*			true if the values extracted, otherwise - false.	[BOOLEAN]
	//*	note:
	//*			if $name_in is NULL or not string, or empty string, then
	//*				will be used $this->name as name of a sysconfig.
	//*
	public function setValuesFromRootNode($root_node_in = null, $name_in = null) {
		
		$this->normalize();
		
		$name = $this->name;
		
		if(!empty($name_in))
		{
			if(is_string($name_in)) $name = $name_in;
		}
		
		$params = self::_getParamsFromRootNode($root_node_in, $name);
		
		return $this->setValuesFromParams($params);
	}
	
	//*	method:	set values from a XML-file.
	//*	input:
	//*			$file_in	- file name;	[OBJECT]
	//*			$name_in	- sysconfig name or NULL.	[STRING || NULL]
	//*	output:
	//*			true if the values extracted, otherwise - false.	[BOOLEAN]
	//*	note:
	//*
	public function setValuesFromFile($file_in = null, $name_in = null) {
		
		$this->normalize();
		
		$name = $this->name;
		
		if(!empty($name_in))
		{
			if(is_string($name_in)) $name = $name_in;
		}
		
		$params = self::_getParamsFromFile($file_in, $name_in);
		
		return $this->setValuesFromParams($params);
	}
	
	//*	method:	save values into a XML-file.
	//*	input:
	//*			$file_in 			- file name;	[OBJECT]
	//*			$root_node_name_in	- a root-node name or NULL.	[STRING || NULL]
	//*	output:
	//*			true if the values saved, otherwise - false.	[BOOLEAN]
	//*	note:
	//*			if $root_node_name_in == NULL, then will be used the root-node of a XML-file!
	//*
	public function saveValuesIntoFile($file_in = null, $root_node_name_in = null) {
		
		$this->normalize();
		
		$params = $this->getParams();
		
		$scNode = self::_addParamsIntoFile($file_in, $params, $root_node_name_in);
		
		return (($scNode) ? true : false);
	}
	
	//*	method:	get selected datasource.
	//*	input:
	//*			$name_in	- datasource name;	[STRING]
	//*			$type_in	- datasource type.	[STRING]
	//*	output:
	//*			object of class "datasource" or NULL.	[OBJECT]
	//*	note:
	//*
	public function getDatasource($name_in = null, $type_in = null) {
		
		$this->normalize();
		
		if(is_array($this->datasources) && !empty($name_in) && !empty($type_in))
		{
			for($i=0; $i<count($this->datasources); $i++)
			{
				if(is_object($this->datasources[$i]))
				{
					if($this->datasources[$i]->params["name"] == $name_in && $this->datasources[$i]->params["type"] == $type_in)
					{
						return $this->datasources[$i];
					}
				}
			}
		}
		
		return null;
	}
	
	//*	method:	get selected datasource.
	//*	input:
	//*			none.
	//*	output:
	//*			object of class "datasource" or NULL.	[OBJECT]
	//*	note:
	//*
	public function getSelectedDatasource() {
		
		return $this->getDatasource($this->datasource_name, $this->datasource_type);
	}
	
	
	//Constructor and Destructor
	
	//*	input:
	//*			$name_in - sysconfig name or NULL.	[STRING || NULL]
	//*	note:
	//*
	function __construct($name_in = null) {
		
		$this->name				= null;
		$this->added_on			= null;
		$this->updated_on		= null;
		$this->state			= self::UNUSED;
		$this->note				= null;
		$this->datasource_name	= null;
		$this->datasource_type	= null;
		$this->datasources		= null;
		$this->directories		= null;
		
		if(!empty($name_in))
		{
			if(is_string($name_in)) $this->name = $name_in;
		}
		
		$this->normalize();
	}
	
	//*	destructor
	//
	//*	note:	
	//
	function __destruct() {
		
		unset($this->name);
		unset($this->added_on);
		unset($this->updated_on);
		unset($this->state);
		unset($this->note);
		unset($this->datasource_name);
		unset($this->datasource_type);
		unset($this->datasources);
		unset($this->directories);
	}
}


?>
