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


/*   Library: DOM.
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
*				~ check_value_by_mask().
*
*			+ types/string.php:
*				~ string_processing().
*
*			+ types/types.php:
*				~ types_data_formatting().
*/


/*	Global variables: none.
*
*
*	Functions:
*
*		*** check an node attribute ***
*		check_attribute_of_element($obj_in = null, $attr_name_in = null, $re_attr_value_in = null)
*
*		*** set an attribute value of a node ***
*		set_attribute_of_element($obj_in = null, $attr_name_in = null, $attr_value_in = null)
*
*		*** get an attribute value of a node ***
*		get_attribute_of_element($obj_in = null, $attr_name_in = null)
*
*		*** get a root-node from a string ***
*		phpDOM_get_root_node_from_string($str_in = null, $type_in = "xml")
*
*		*** get a root-node from a file ***
*		phpDOM_get_root_node_from_file($file_in = null, $type_in = "xml")
*
*		*** check a node ***
*		phpDOM_check_node($node_in = null, $re_node_name_in = null, $attr_name_in = null, $re_attr_value_in = null)
*
*		*** search nodes by parameters ***
*		phpDOM_parsing($root_node_in = null, $re_node_name_in = null, $attr_name_in = null, $re_attr_value_in = null)
*
*		*** clear a node ***
*		phpDOM_clear_node($node_in = null, $re_node_name_in = null, $attr_name_in = null, $re_attr_value_in = null)
*
*		*** rename a node ***
*		phpDOM_rename_node($node_in = null, $new_node_name_in = null)
*
*		*** remove a node ***
*		phpDOM_remove_node($node_in = null)
*
*		*** attach a node ***
*		phpDOM_attach_node($root_node_in = null, $attached_node_in = null, $attached_position_in = "end")
*
*		*** forming a node ***
*		phpDOM_forming_node($node_in = null, $array_of_targets_in = null)
*
*		*** get values of nodes by parameters ***
*		phpDOM_get_values_of_nodes_by_params($root_node_in = null, $array_of_params_in = null)
*
*		*** write a document to a file ***
*		phpDOM_write_document_to_file($obj_in = null, $file_in = null, $type_in = "xml")
*
*
*	Classes: none.
*
*
*	Initialization of global variables: none.
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function:	check a node attribute.
*	Input:
*				$obj_in           - a node (an object of the class "domElement");	[OBJECT]
*				$attr_name_in     - an attribute name;	[STRING]
*				$re_attr_value_in - an attribute value (regexp) or null	[STRING || NULL].
*	Output:
*				result:	[BOOLEAN]
*					- true	- a node has the attribute $attr_name_in and/or its value is $re_attr_value_in,
*					- false - an object not has the attribute $attr_name_in and/or its value is not $re_attr_value_in.
*/
function check_attribute_of_element($obj_in = null, $attr_name_in = null, $re_attr_value_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> check_attribute_of_element()]");
		}
		return false;
	}
	
	//Check functions
	if(!function_exists("search_sub_string"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'search_sub_string()' not exists! [dom/dom.php -> check_attribute_of_element()]");
		}
		return false;
	}
	
	//Check input arguments
	if(!is_object($obj_in))
	{
		return false;
	}
	
	if(!is_a($obj_in, "domElement"))
	{
		return false;
	}
	
	if(empty($attr_name_in))
	{
		return false;
	}
	
	if(!is_string($attr_name_in))
	{
		return false;
	}
	
	//Check attribute name
	if(!$obj_in->hasAttribute($attr_name_in))
	{
		return false;
	}
	
	//Check attribute value
	if(isset($re_attr_value_in))
	{
		if(is_string($re_attr_value_in))
		{
			if(!search_sub_string($re_attr_value_in, $obj_in->getAttribute($attr_name_in), $regs, null, null))
			{
				return false;
			}
		}
	}
	
	return true;
}


/*	Function:	set an attribute value of a node.
*	Input:
*				$obj_in        - a node (an object of the class "domElement");	[OBJECT]
*				$attr_name_in  - a attribute name;	[STRING]
*				$attr_value_in - a attribute value or null.	[STRING || NULL]
*	Output:
*				result:	[BOOLEAN]
*					- true	- a value of an attribute is changed,
*					- false - a value of an attribute is not changed.
*	Note:
*
*				If the $attr_value_in is null, then the attribute $attr_name_in of the $obj_in will be removed!
*/
function set_attribute_of_element($obj_in = null, $attr_name_in = null, $attr_value_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> set_attribute_of_element()]");
		}
		return false;
	}
	
	//Check input arguments
	if(!is_object($obj_in))
	{
		return false;
	}
	
	if(!is_a($obj_in, "domElement"))
	{
		return false;
	}
	
	if(empty($attr_name_in))
	{
		return false;
	}
	
	if(!is_string($attr_name_in))
	{
		return false;
	}
	
	switch(gettype($attr_value_in))
	{
		case "null":
		case "Null":
		case "NULL":
			
			if(!$obj_in->hasAttribute($attr_name_in))
			{
				return false;
			}
			
			//remove value of attribute
			$obj_in->removeAttribute($attr_name_in);
			
			break;
			
		case "string":
		case "String":
		case "STRING":
			
			//set attribute value
			$obj_in->setAttribute($attr_name_in, $attr_value_in);
			
			break;
			
		default:
			return false;
	}
	
	return true;
}


/*	Function:	get an attribute value of a node.
*	Input:
*				$obj_in        - a node (an object of the class "domElement");	[OBJECT]
*				$attr_name_in  - an attribute name.	[STRING]
*	Output:
*				a value of the attribute or null.	[STRING || NULL]
*/
function get_attribute_of_element($obj_in = null, $attr_name_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check functions
	if(!function_exists("check_attribute_of_element"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'check_attribute_of_element()' not exists! [dom/dom.php -> get_attribute_of_element()]");
		}
		return null;
	}
	
	//Check attribute
	if(!check_attribute_of_element($obj_in, $attr_name_in, null))
	{
		return null;
	}
	
	return $obj_in->getAttribute($attr_name_in);
}


/*	Function:	get a root-node from a string.
*	Input:
*				$str_in		- XML-, HTML-string,	[STRING]
*				$type_in	- type of document:		[STRING]
*								-- "xml" (by default),
*								-- "html".
*	Output:
*				the root-node or null.	[OBJECT || NULL]
*
*	Note:
*
*				set the character encoding (example):
*
*					- phpDOM_get_root_node_from_string(("<?xml encoding=\"utf-8\"?>").($str_in), "HTML");
*/
function phpDOM_get_root_node_from_string($str_in = null, $type_in = "xml")
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("DOMDocument"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'DOMDocument' not exists! [dom/dom.php -> phpDOM_get_root_node_from_string()]");
		}
		return null;
	}
	
	//Check input arguments
	if(empty($str_in))
	{
		return null;
	}
	
	if(!is_string($str_in))
	{
		return null;
	}
	
	//* new DOM Document	[OBJECT || NULL]
	$doc = new DOMDocument();
	
	
	//Check object
	if(!$doc)
	{
		return null;
	}
	
	//* type of document	[STRING]
	$doc_type = "XML";
	
	
	if(is_string($type_in))
	{
		$doc_type = $type_in;
	}
	
	//** without white spaces
	$doc->preserveWhiteSpace = false;
	
	//Check type of document
	switch($doc_type)
	{
		case "HTML":
		case "Html":
		case "html":
			
			if($doc->loadHTML($str_in))
			{
				return $doc->documentElement;
			}
			
			break;
			
		default:
			
			if($doc->loadXML($str_in))
			{
				return $doc->documentElement;
			}
	}
	
	return null;
}


/*	Function:	get a root-node from a file.
*	Input:
*				$file_in	- a path to a file;	[STRING]
*				$type_in	- a document type:	[STRING]
*								-- "xml" (by default),
*								-- "html".
*	Output:
*				the root-node or null.	[OBJECT || NULL]
*/
function phpDOM_get_root_node_from_file($file_in = null, $type_in = "xml")
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("DOMDocument"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'DOMDocument' not exists! [dom/dom.php -> phpDOM_get_root_node_from_string()]");
		}
		return null;
	}
	
	//Check input arguments
	if(empty($file_in))
	{
		return null;
	}
	
	if(!is_string($file_in))
	{
		return null;
	}
	
	//* new DOM Document	[OBJECT || NULL]
	$doc = new DOMDocument();
	
	
	//Check object
	if(!$doc)
	{
		return null;
	}
	
	//* type of document	[STRING]
	$doc_type = "XML";
	
	
	if(is_string($type_in))
	{
		$doc_type = $type_in;
	}
	
	//** without white spaces
	$doc->preserveWhiteSpace = false;
	
	//Check type of document
	switch($doc_type)
	{
		case "HTML":
		case "Html":
		case "html":
			
			if($doc->loadHTMLFile($file_in))
			{
				return $doc->documentElement;
			}
			
			break;
			
		default:
			
			if($doc->load($file_in))
			{
				return $doc->documentElement;
			}
	}
	
	return null;
}


/*	Function:	check a node.
*	Input:
*				$node_in			- a node (an object of the class "domElement");	[OBJECT]
*				$re_node_name_in	- a node name or null;	[STRING || NULL]
*				$attr_name_in		- an attribute name or null;	[STRING || NULL]
*				$re_attr_value_in	- an attribute value (regexp) or null.	[STRING || NULL]
*	Output:
*				result:	[BOOLEAN]
*					- true  - a node matches the specified parameters,
*					- false - a node not matches the specified parameters.
*	Note:
*				Check by attributes for nodes with nodeType == 1 (no text node, no comment...)!
*
*				For re_attr_value_in required value of attr_name_in!
*
*				re_node_name_in can be set as mask (see the function check_value_by_mask())!
*/
function phpDOM_check_node($node_in = null, $re_node_name_in = null, $attr_name_in = null, $re_attr_value_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domNode"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domNode' not exists! [dom/dom.php -> phpDOM_check_node()]");
		}
		return false;
	}
	
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> phpDOM_check_node()]");
		}
		return false;
	}
	
	//Check functions
	if(!function_exists("check_value_by_mask"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'check_value_by_mask()' not exists! [dom/dom.php -> phpDOM_check_node()]");
		}
		return false;
	}
	
	if(!function_exists("check_attribute_of_element"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'check_attribute_of_element()' not exists! [dom/dom.php -> phpDOM_check_node()]");
		}
		return false;
	}
	
	if(!function_exists("get_attribute_of_element"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'get_attribute_of_element()' not exists! [dom/dom.php -> phpDOM_check_node()]");
		}
		return false;
	}
	
	//Check input arguments
	if(!is_object($node_in))
	{
		return false;
	}
	
	if(!is_a($node_in, "domNode"))
	{
		return false;
	}
	
	//Check an object by node name
	if(!empty($re_node_name_in))
	{
		if(!check_value_by_mask($re_node_name_in, $node_in->nodeName))
		{
			return false;
		}
	}
	
	//Other checking for nodeType == 1!
	if(is_a($node_in, "domElement"))
	{
		//check an object by an attribute name
		if(!empty($attr_name_in))
		{
			if(!get_attribute_of_element($node_in, $attr_name_in))
			{
				return false;
			}
			
			//check an object by an attribute value
			if(!empty($re_attr_value_in))
			{
				if(!check_attribute_of_element($node_in, $attr_name_in, $re_attr_value_in))
				{
					return false;
				}
			}
		}
	}
	
	return true;
}


/*	Function:	search nodes by parameters.
*	Input:
*				$root_node_in		- a roott-node (an object of the class "domElement");	[OBJECT]
*				$re_node_name_in	- a name of a target node (regexp string) or null;	[STRING || NULL]
*				$attr_name_in		- an attribute name of a target node or null;	[STRING || NULL]
*				$re_attr_value_in	- an attribute value of a target node or null.	[STRING || NULL]
*	Output:
*				an array of nodes or empty array.	[ARRAY]
*/
function phpDOM_parsing($root_node_in = null, $re_node_name_in = null, $attr_name_in = null, $re_attr_value_in = null)
{
	//* result	[ARRAY]
	$return_result = array();
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> phpDOM_parsing()]");
		}
		return $return_result;
	}
	
	//Check functions
	if(!function_exists("check_attribute_of_element"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'check_attribute_of_element()' not exists! [dom/dom.php -> phpDOM_parsing()]");
		}
		return $return_result;
	}
	
	if(!function_exists("set_attribute_of_element"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'set_attribute_of_element()' not exists! [dom/dom.php -> phpDOM_parsing()]");
		}
		return $return_result;
	}
	
	if(!function_exists("phpDOM_check_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_check_node\()' not exists! [dom/dom.php -> phpDOM_parsing()]");
		}
		return $return_result;
	}
	
	//Check input arguments
	if(!is_object($root_node_in))
	{
		return $return_result;
	}
	
	if(!is_a($root_node_in, "domElement"))
	{
		return $return_result;
	}
	
	//* buffer	[OBJECT || NULL]
	$buf_node	= $root_node_in->firstChild;
	
	//* use or not use 'nextSibling'	[BOOLEAN]
	//** true  - use 'nextSibling' (by default),
	//** false - not use 'nextSibling'.
	$fl_ns		= true;
	
	//* a node matches or not matches the specified parameters	[BOOLEAN]
	//* (matches by default)
	$fl_fit		= true;
	
	//marking the start node
	set_attribute_of_element($root_node_in, "phpdom", "tmp");
	
	while($buf_node)
	{
		if($buf_node)
		{
			$fl_ns	= true;
			$fl_fit	= true;
			
			//check by attributes and values
			if(is_string($re_node_name_in) || is_string($attr_name_in))
			{
				//check node
				$fl_fit = phpDOM_check_node($buf_node, $re_node_name_in, $attr_name_in, $re_attr_value_in);
			}
			
			//** if the buf_node matches the specified parameters then add it to the result array
			if($fl_fit)
			{
				array_push($return_result, $buf_node);
			}
			
			//check child nodes of the buf_node
			if($buf_node->childNodes)
			{
				if($buf_node->childNodes->length)
				{
					//get first child node
					$buf_node = $buf_node->firstChild;
					
					//off 'nextSibling'
					$fl_ns = false;
				}
			}
			
			//** sibling
			while($fl_ns)
			{
				//check a next node of the current level (next sibling node)
				//** if there is no next sibling node then return to the parent node of the current level (parsing of the current level of completed!)
				if($buf_node->nextSibling)
				{
					//get next sibling node
					$buf_node = $buf_node->nextSibling;
					
					//off 'nextSibling'
					$fl_ns = false;
				}
				else
				{
					//get the parent node of the current level
					$buf_node = $buf_node->parentNode;
					
					//on 'nextSibling'
					$fl_ns = true;
					
					//** if the parent node contains the attribute 'jsdom' then exit from function (end parsing!)
					if(check_attribute_of_element($buf_node, "phpdom", "tmp"))
					{
						//off 'nextSibling'
						$fl_ns = false;
						
						//break parsing
						$buf_node = null;
					}
				}
			}
		}
	}
	
	//Remove the attribute 'jsdom'
	set_attribute_of_element($root_node_in, "phpdom", null);
	
	return $return_result;
}


/*	Function:	clear a node.
*	Input:
*				$node_in			- a node (an object of the class "domElement");	[OBJECT]
*				$re_node_name_in	- a name of removed child-nodes (regexp string for search) or NULL;	[STRING || NULL]
*				$attr_name_in		- a attribute name of removed child-nodes (for search) or NULL;	[STRING || NULL]
*				$re_attr_value_in	- a attribute value of removed child-nodes (regexp string for search) or NULL.	[STRING || NULL]
*	Output:
*				number of removed child nodes.	[INTEGER]
*	Note:
*				If $re_node_name_in == NULL, the removed all child-nodes of the $node_in!
*
*				If used $re_node_name_in, $attr_name_in (not required), $re_attr_value_in (required for $attr_name_in),
*					then will removed child nodes with the specified options!
*/
function phpDOM_clear_node($node_in = null, $re_node_name_in = null, $attr_name_in = null, $re_attr_value_in = null)
{
	//* number of removed child nodes	[INTEGER]
	$return_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> phpDOM_clear_node()]");
		}
		return $return_result;
	}
	
	//Check functions
	if(!function_exists("check_attribute_of_element"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'check_attribute_of_element()' not exists! [dom/dom.php -> phpDOM_clear_node()]");
		}
		return $return_result;
	}
	
	//Check input arguments
	if(!is_object($node_in))
	{
		return $return_result;
	}
	
	if(!is_a($node_in, "domElement"))
	{
		return $return_result;
	}
	
	//* a node matches or not matches the specified parameters	[BOOLEAN]
	//* (matches by default)
	$fl_fit = true;
	
	//* buffer	[OBJECT || NULL]
	$buf_node = $node_in->firstChild;
	
	
	while($buf_node)
	{
		//init
		$fl_fit	= true;
		
		//check a node by attributes and values
		if(is_string($re_node_name_in) || is_string($attr_name_in))
		{
			$fl_fit = phpDOM_check_node($buf_node, $re_node_name_in, $attr_name_in, $re_attr_value_in);
		}
		
		if($fl_fit)
		{
			//remove child nodes
			if($node_in->removeChild($buf_node))
			{
				$return_result++;
			}
			
			//get a first child node
			$buf_node = $node_in->firstChild;
		}
		else
		{
			//get a next child node
			$buf_node = $buf_node->nextSibling;
		}
	}
	
	return $return_result;
}


/*	Function:	rename a node.
*	Input:
*				$node_in			- a node (an object of the class "domElement");		[OBJECT]
*				$new_node_name_in	- a new node name.	[STRING]
*	Output:
*				a copy of old node or null.	[OBJECT || NULL]
*	Note:
*				Only for nodes with type 1 (not for root-nodes - where parent node is document!) (ELEMENT_NODE)!
*/
function phpDOM_rename_node($node_in = null, $new_node_name_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> phpDOM_rename_node()]");
		}
		return null;
	}
	
	//Check functions
	if(!function_exists("string_processing"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'string_processing()' not exists! [dom/dom.php -> phpDOM_rename_node()]");
		}
		return null;
	}
	
	if(!function_exists("set_attribute_of_element"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'set_attribute_of_element()' not exists! [dom/dom.php -> phpDOM_rename_node()]");
		}
		return null;
	}
	
	//Check input arguments
	if(!is_object($node_in))
	{
		return null;
	}
	
	if(!is_a($node_in, "domElement"))
	{
		return null;
	}
	
	if(empty($new_node_name_in))
	{
		return null;
	}
	
	if(!is_string($new_node_name_in))
	{
		return null;
	}
	
	//* new node name	[STRING]
	$new_node_name = string_processing($new_node_name_in, "EQ_SP_TO_USC");
	
	//* parent node	[OBJECT || NULL]
	$parent_node = $node_in->parentNode;
	
	
	//Check parent node
	if(!is_a($parent_node, "domElement"))
	{
		return null;
	}
	
	//* owner document	[OBJECT || NULL]
	$doc = $node_in->ownerDocument;
	
	
	//Check document
	if(!$doc)
	{
		return null;
	}
	
	//* new node	[OBJECT]
	$new_node = $doc->createElement($new_node_name);
	
	
	if(!$new_node)
	{
		return null;
	}
	
	//* attributes list	[OBJECT || NULL]
	$attributes = $node_in->attributes;
	
	//* child nodes list	[OBJECT || NULL]
	$child_nodes = $node_in->childNodes;
	
	
	if(!$attributes || !$child_nodes)
	{
		return null;
	}
	
	//* clone	[OBJECT || NULL]
	$cloned_node = null;
	
	//* buffer	[OBJECT || NULL]
	$buff = null;
	
	
	//Copying attributes
	for($i=0; $i<$attributes->length; $i++)
	{
		$buff = $attributes->item($i);
		
		if($buff)
		{
			set_attribute_of_element($new_node, $buff->nodeName, $buff->nodeValue);
		}
	}
	
	//Cloning child nodes of node_in
	for($i=0; $i<$child_nodes->length; $i++)
	{
		$buff = $child_nodes->item($i);
		
		if($buff)
		{
			$cloned_node = $buff->cloneNode(true);
			
			if($cloned_node)
			{
				$new_node->appendChild($cloned_node);
			}
		}
	}
	
	//Replace node_in to new_node
	return $parent_node->replaceChild($new_node, $node_in);
}


/*	Function:	remove a node.
*	Input:
*				$node_in - a node (an object of the class "domElement").	[OBJECT]
*	Output:
*				the copy of old node or null.	[OBJECT || NULL]
*	Note:
*				Only for nodes with type 1 (not for root-nodes - where parent node is document!) (ELEMENT_NODE)!
*/
function phpDOM_remove_node($node_in = null)
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> phpDOM_remove_node()]");
		}
		return null;
	}
	
	//Check input arguments
	if(!is_object($node_in))
	{
		return null;
	}
	
	if(!is_a($node_in, "domElement"))
	{
		return null;
	}
	
	//* parent node	[OBJECT || NULL]
	$parent_node = $node_in->parentNode;
	
	
	//Check parent node
	if(!is_a($parent_node, "domElement"))
	{
		return null;
	}
	
	//* last namespaceURI	[STRING]
	//$nsuri = $parent_node->namespaceURI;
	
	//* the removed node	[OBJECT]
	$removed_node = $parent_node->removeChild($node_in);
	
	
	//Update namespaceURI
	//$parent_node->namespaceURI = $nsuri;
	
	return $removed_node;
}


/*	Function:	attach a node.
*	Input:
*				$root_node_in			- a root-node (an object of the class "domElement");	[OBJECT]
*				$attached_node_in		- a attached node (an object of the class "domElement");	[OBJECT]
*				$attached_position_in	- a attached position:	[STRING || NULL]
*											-- "start"			- into start of root_node_in,
*											-- "end"			- into end of root_node_in (by default),
*											-- "replace_all"	- replace all child nodes of root_node_in.
*	Output:
*				a attached node or null.	[OBJECT || NULL]
*	Note:
*				If the $root_node_name_in == NULL and/or the $attached_node_in == NULL, then returns NULL!
*/
function phpDOM_attach_node($root_node_in = null, $attached_node_in = null, $attached_position_in = "end")
{
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> phpDOM_attach_node()]");
		}
		return null;
	}
	
	//Check functions
	if(!function_exists("phpDOM_clear_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_clear_node()' not exists! [dom/dom.php -> phpDOM_attach_node()]");
		}
		return null;
	}
	
	//Check input arguments
	if(!is_object($root_node_in))
	{
		return null;
	}
	
	if(!is_a($root_node_in, "domElement"))
	{
		return null;
	}
	
	if(!is_object($attached_node_in))
	{
		return null;
	}
	
	if(!is_a($attached_node_in, "domElement"))
	{
		return null;
	}
	
	//* owner document	[OBJECT || NULL]
	$doc = $root_node_in->ownerDocument;
	
	
	//Check document
	if(!$doc)
	{
		return null;
	}
	
	//* a attached position	[STRING]
	$attached_position = "end";
	
	
	//Check the input argument $attached_position_in
	if(is_string($attached_position_in))
	{
		$attached_position = $attached_position_in;
	}
	
	//* a imported node	[OBJECT]
	//** import with all child-nodes!
	$imported_node = $doc->importNode($attached_node_in, true);
	
	
	//Check the node
	if(!$imported_node)
	{
		return null;
	}
	
	//Check the attached position
	switch($attached_position)
	{
		case "start":
			
			return $root_node_in->insertBefore($imported_node, $root_node_in->firstChild);
		
		case "replace_all":
			
			//remove all child-nodes
			phpDOM_clear_node($root_node_in);
	}
	
	return $root_node_in->appendChild($imported_node);
}


/*	Function:	forming a node.
*	Input:
*				$node_in			 - a root-node (an object of the class "domElement");	[OBJECT]
*				$array_of_targets_in - an array of parameters.	[ARRAY]
*	Output:
*				number of modified nodes.	[NUMBER]
*	Note:
*
*				Structure of the $array_of_targets_in:
*
*					["node_name"]		- name of a target node (regexp string for search; required!);			[STRING]
*					["attr_name"]		- attribute name of target node (for search) or NULL;					[STRING || NULL]
*					["attr_value"]		- attribute value of target node (regexp string for search) or NULL;	[STRING || NULL]
*					["new_node_name"]	- name of target node or NULL;											[STRING || NULL]
*					["new_node_value"]	- value of target node or NULL;											[STRING || NULL]
*					["attach_node"]		- attached a node (domNode) or NULL;									[STRING || NULL]
*					["attach_position"]	- position the insertion or NULL:										[STRING || NULL]
*												-- "start"			- into start of root_node_in,
*												-- "end"			- into end of root_node_in (by default),
*												-- "replace_all"	- replace all child nodes of root_node_in;
*					["remove_node"]		- remove a target node:													[BOOLEAN || NULL]
*												-- false (by default),
*												-- true;
*					["remove_childs"]	- remove child-nodes of a target node:									[ARRAY || NULL]
*												-- search settings:
*													array("node_name"  => "..." or null,	//NULL for remove all child-nodes!
*														  "attr_name"  => "..." or null,
*														  "attr_value" => "..." or null
*														 );
*					["attributes"]		- array of target node attributes (for add/update value):				[ARRAY || NULL]
*												-- array("attr_name1" => "value"...).
*
*				If ["node_name"] is NULL or undefined then used name of the node_in!
*
*
*					Example of array structure 1:
*
*						$array_of_targets	= array(array("node_name"		=>	"^div$",	//0 - div (logo)
*														  "attr_name"		=>	"class",
*														  "attr_value"		=>	"^main-page-logo$",
*														  "attach_node"		=>	null,
*														  "attach_position"	=>	"replace_all",
*														  "default_class"	=>	"main-page-logo",
*														  "attributes"		=>	array("class" => "main-page-logo display-hidden")
*														 ),
*													...
*													);
*
*					Example of array structure 2:
*
*						$array_of_targets	= array("target1" => array("node_name"			=>	"^div$",	//0 - div (logo)
*																	   "attr_name"			=>	"class",
*																	   "attr_value"			=>	"^main-page-logo$",
*																	   "attach_node"		=>	null,
*																	   "attach_position"	=>	"replace_all",
*																	   "default_class"		=>	"main-page-logo",
*																	   "attributes"			=>	array("class" => "main-page-logo display-hidden")
*																	  ),
*													 ...
*													);
*/
function phpDOM_forming_node($node_in = null, $array_of_targets_in = null)
{
	//* result	[NUMBER]
	$return_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> phpDOM_forming_node()]");
		}
		return $return_result;
	}
	
	//Check functions
	if(!function_exists("set_attribute_of_element"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'set_attribute_of_element()' not exists! [dom/dom.php -> phpDOM_forming_node()]");
		}
		return $return_result;
	}
	
	if(!function_exists("phpDOM_parsing"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_parsing()' not exists! [dom/dom.php -> phpDOM_forming_node()]");
		}
		return $return_result;
	}
	
	if(!function_exists("phpDOM_clear_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_clear_node()' not exists! [dom/dom.php -> phpDOM_forming_node()]");
		}
		return $return_result;
	}
	
	if(!function_exists("phpDOM_rename_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_rename_node()' not exists! [dom/dom.php -> phpDOM_forming_node()]");
		}
		return $return_result;
	}
	
	if(!function_exists("phpDOM_remove_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_remove_node()' not exists! [dom/dom.php -> phpDOM_forming_node()]");
		}
		return $return_result;
	}
	
	if(!function_exists("phpDOM_attach_node"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_attach_node()' not exists! [dom/dom.php -> phpDOM_forming_node()]");
		}
		return $return_result;
	}
	
	//Check input arguments
	if(!is_object($node_in))
	{
		return $return_result;
	}
	
	if(!is_a($node_in, "domElement"))
	{
		return $return_result;
	}
	
	if(!is_array($array_of_targets_in))
	{
		return $return_result;
	}
	
	//* array of target nodes	  					[ARRAY || NULL]
	$array_of_nodes		= null;
	
	//* name of target node (for search)			[STRING || NULL]
	$node_name			= null;
	
	//* attribute name of target node (for search)	[STRING || NULL]
	$attr_name			= null;
	
	//* attribute value of target node (for search)	[STRING || NULL]
	$attr_value			= null;
	
	//* result										[BOOLEAN]
	$fl_res				= false;
	
	
	foreach($array_of_targets_in as $k=>$v)
	{
		if(!is_array($v))
		{
			continue;
		}
		
		//init
		$node_name	= null;
		$attr_name	= null;
		$attr_value	= null;
		
		//check property "node_name"
		if(!empty($v["node_name"]))
		{
			if(is_string($v["node_name"]))
			{
				//** use the found nodes
				
				$node_name = $v["node_name"];
				
				//check property "attr_name"
				if(!empty($v["attr_name"]))
				{
					if(is_string($v["attr_name"]))
					{
						$attr_name = $v["attr_name"];
					}
				}
				
				//check property "attr_value"
				if(!empty($v["attr_value"]))
				{
					if(is_string($v["attr_value"]))
					{
						$attr_value = $v["attr_value"];
					}
				}
				
				//get array of target nodes
				$array_of_nodes = phpDOM_parsing($node_in, $node_name, $attr_name, $attr_value);
			}
		}
		
		//check node_name
		if(empty($node_name))
		{
			//** use the root_node_in
			
			$array_of_nodes = array($node_in);
		}
		
		if(is_array($array_of_nodes))
		{
			for($j=0; $j<count($array_of_nodes); $j++)
			{
				if(!is_object($array_of_nodes[$j]))
				{
					continue;
				}
				
				if(!is_a($array_of_nodes[$j], "domElement"))
				{
					continue;
				}
				
				$fl_res = false;
				
				
				//** remove a target node
				
				if(!empty($v["remove_node"]))
				{
					if(is_bool($v["remove_node"]))
					{
						if($v["remove_node"])
						{
							if(phpDOM_remove_node($array_of_nodes[$j]))
							{
								$return_result++;
								continue;
							}
						}
					}
				}
				
				
				//** remove child-nodes of a target node
				
				if(!empty($v["remove_childs"]))
				{
					if(is_array($v["remove_childs"]))
					{
						//* search settings	[STRING || NULL]
						$child_node_name	= null;
						$child_attr_name	= null;
						$child_attr_value	= null;
						
						
						if(!empty($v["remove_childs"]["node_name"]))
						{
							$child_node_name = $v["remove_childs"]["node_name"];
						}
						
						if(!empty($v["remove_childs"]["attr_name"]))
						{
							$child_attr_name = $v["remove_childs"]["attr_name"];
						}
						
						if(!empty($v["remove_childs"]["attr_value"]))
						{
							$child_attr_value = $v["remove_childs"]["attr_value"];
						}
						
						if(phpDOM_clear_node($array_of_nodes[$j], $child_node_name, $child_attr_name, $child_attr_value))
						{
							$fl_res = true;
						}
					}
				}
				
				
				//** rename a target node
				
				if(!empty($v["new_node_name"]))
				{
					if(is_string($v["new_node_name"]))
					{
						if(phpDOM_rename_node($array_of_nodes[$j], $v["new_node_name"]))
						{
							$fl_res = true;
						}
					}
				}
				
				
				//** new node value
				
				if(!empty($v["new_node_value"]))
				{
					if(is_string($v["new_node_value"]))
					{
						//set new node value
						$array_of_nodes[$j]->nodeValue = $v["new_node_value"];
						$fl_res = true;
					}
				}
				
				
				//** attach a node
				
				if(!empty($v["attach_node"]))
				{
					if(is_object($v["attach_node"]))
					{
						//* a attached position	[STRING]
						$attach_position = "end";
						
						
						if(!empty($v["attach_position"]))
						{
							if(is_string($v["attach_position"]))
							{
								$attach_position = $v["attach_position"];
							}
						}
						
						if(phpDOM_attach_node($array_of_nodes[$j], $v["attach_node"], $attach_position))
						{
							$fl_res = true;
						}
					}
				}
				
				
				//** set value of attributes
				
				if(!empty($v["attributes"]))
				{
					if(is_array($v["attributes"]))
					{
						foreach($v["attributes"] as $k=>$v)
						{
							if(set_attribute_of_element($array_of_nodes[$j], $k, $v))
							{
								$fl_res = true;
							}
						}
					}
				}
				
				//check sign of result
				if($fl_res)
				{
					$return_result++;
				}
			}
		}
	}
	
	return $return_result;
}


/*	Function:	get values of nodes by parameters.
*	Input:
*				$root_node_in		- a node (an object of the class "domElement");	[OBJECT]
*				$array_of_params_in	- an array of parameters.	[ARRAY]
*	Output:
*				an array of values of nodes by parameters or null.	[ARRAY || NULL]
*	Note:
*
*				Structure of the array of parameters:
*
*					$array_of_params_in = array("timestamp" => array("nodename" => "timestamp",   "type" => "integer", "required" => false, "default_value"  => 0),
*												"db_type"   => array("nodename" => "db_type",     "type" => "string",  "required" => true),
*									 			"hostname"  => array("nodename" => "hostname",    "type" => "string",  "required" => false, "default_value"  => "localhost"),
*									 			array("nodename" => "port",        "type" => "integer", "required" => false, "default_value"  => 3306),
*												array("nodename" => "database",    "type" => "string",  "required" => true),
*												array("nodename" => "table",       "type" => "string",  "required" => false, "default"  => null),
*												array("nodename" => "user",        "type" => "string",  "required" => true),
*												array("nodename" => "password",    "type" => "string",  "required" => false, "default"  => null),
*												array("nodename" => "description", "type" => "string",  "required" => false, "default"  => null)
*											   );
*
*						* for the value by default used keys: "default_value" or "default"!
*
*				Structure of result array:
*
*					$result[$nodename] = value by type or default value,
*					 ...
*
*
*				If value of node is empty and option "required" is "true", then  returns NULL!
*/
function phpDOM_get_values_of_nodes_by_params($root_node_in = null, $array_of_params_in = null)
{
	//* result	[ARRAY || NULL]
	$return_result = null;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domElement"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domElement' not exists! [dom/dom.php -> phpDOM_get_values_of_nodes_by_params()]");
		}
		return $return_result;
	}
	
	//Check functions
	if(!function_exists("types_data_formatting"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'types_data_formatting()' is undefined! [dom.php -> phpDOM_get_values_of_nodes_by_params()]");
		}
		return $return_result;
	}	
	
	if(!function_exists("phpDOM_parsing"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Function 'phpDOM_parsing()' is undefined! [dom.php -> phpDOM_get_values_of_nodes_by_params()]");
		}
		return $return_result;
	}
	
	//Check input arguments
	if(!is_object($root_node_in))
	{
		return $return_result;
	}
	
	if(!is_a($root_node_in, "domElement"))
	{
		return $return_result;
	}
	
	if(!is_array($array_of_params_in))
	{
		return $return_result;
	}
	
	//* array of target nodes	[ARRAY || NULL]
	$target_nodes = null;
	
	//* name of node	[STRING || NULL]
	$nodename = null;
	
	//* data type	[STRING || NULL]
	//** "string" by default
	$type = "string";
	
	//* required	[BOOLEAN]
	//** false by default
	$required = false;
	
	
	foreach($array_of_params_in as $arr_id=>$arr_val)
	{
		//check the list of parameters
		if(!is_array($arr_val))
		{
			continue;
		}
		
		if(empty($arr_val["nodename"]))
		{
			continue;
		}
		
		//check the returned array
		if(!is_array($return_result))
		{
			$return_result = array();
		}
		
		//init
		$nodename = $arr_val["nodename"];
		$type = "string";
		$required = false;
		
		//check the parameter "type"
		if(!empty($arr_val["type"]))
		{
			if(is_string($arr_val["type"]))
			{
				$type = $arr_val["type"];
			}
		}
		
		//check the parameter "required"
		if(!empty($arr_val["required"]))
		{
			if(is_bool($arr_val["required"]))
			{
				$required = $arr_val["required"];
			}
		}
		
		//get target nodes
		$target_nodes = phpDOM_parsing($root_node_in, "^{$nodename}$", null, null);
		
		//check the array of target nodes
		if(is_array($target_nodes))
		{
			for($j=0; $j<count($target_nodes); $j++)
			{
				//check the node
				if(is_object($target_nodes[$j]))
				{
					if(is_a($target_nodes[$j], "domElement"))
					{
						//get the node value
						if(!empty($target_nodes[$j]->nodeValue))
						{
							$return_result[$nodename] = types_data_formatting($target_nodes[$j]->nodeValue, $type, true);
							
							//check the data type of the result
							if($required && (gettype($return_result[$nodename])) != $type)
							{
								return null;
							}
							break;
						}
					}
				}
			}
		}
		
		if(!isset($return_result[$nodename]))
		{
			if($required)
			{
				return null;
			}
			
			$return_result[$nodename] = null;
			
			if(isset($arr_val["default_value"]) || isset($arr_val["default"]))
			{
				if(isset($arr_val["default_value"]))
				{
					$return_result[$nodename] = $arr_val["default_value"];
				}
				else
				{
					$return_result[$nodename] = $arr_val["default"];
				}
			}
		}
	}
	
	return $return_result;
}


/*	Function:	write a document to a file.
*	Input:
*				$obj_in		- an object of the class "DOMDocument" or "domNode",	[OBJECT]
*				$file_in	- path to file,			[STRING]
*				$type_in	- type of document:		[STRING]
*								-- "XML" (by default),
*								-- "HTML".
*	Output:
*				number of bytes written.	[INTEGER]
*/
function phpDOM_write_document_to_file($obj_in = null, $file_in = null, $type_in = "xml")
{
	//* result	[INTEGER]
	$return_result = 0;
	
	
	//Init global variables
	global $FL_DEBUG;
	
	//Check classes
	if(!class_exists("domNode"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'domNode' not exists! [dom/dom.php -> phpDOM_write_document_to_file()]");
		}
		return $return_result;
	}
	
	if(!class_exists("DOMDocument"))
	{
		if($FL_DEBUG)
		{
			echo("Error! Class 'DOMDocument' not exists! [dom/dom.php -> phpDOM_write_document_to_file()]");
		}
		return $return_result;
	}
	
	//Check input arguments
	if(!is_object($obj_in))
	{
		return $return_result;
	}
	
	if(empty($file_in))
	{
		return $return_result;
	}
	
	if(!is_string($file_in))
	{
		return $return_result;
	}
	
	if(is_a($obj_in, "domNode") || is_a($obj_in, "DOMDocument"))
	{
		//* file descriptor	[INTEGER]
		$fp = fopen($file_in, "w");
		
		
		//check descriptor
		if($fp)
		{
			//* type of document	[STRING]
			$doc_type	= "XML";
			
			//* owner document		[OBJECT || NULL]
			$doc		= null;
			
			
			//check type of document
			if(!empty($type_in))
			{
				if(is_string($type_in))
				{
					$doc_type = $type_in;
				}
			}
			
			//check class of input object
			if(is_a($obj_in, "domNode"))
			{
				//** if $obj_in is the object of the class "domNode"
				$doc = $obj_in->ownerDocument;
			}
			else
			{
				//** //** if $obj_in is the object of the class "DOMDocument"
				$doc = $obj_in;
			}
			
			//set output format
			$doc->formatOutput = true;
			
			//check type of document
			switch($doc_type)
			{
				case "HTML":
				case "Html":
				case "html":
					
					//write HTML-document to file
					if(is_a($obj_in, "domNode"))
					{
						$return_result = fwrite($fp, $doc->saveHTML($obj_in));
					}
					else
					{
						$return_result = fwrite($fp, $doc->saveHTML());
					}
					
					break;
					
				default:
					
					//write XML-document to file
					if(is_a($obj_in, "domNode"))
					{
						$return_result = fwrite($fp, $doc->saveXML($obj_in));
					}
					else
					{
						$return_result = fwrite($fp, $doc->saveXML());
					}
			}
			
			//close the file
			fclose($fp);
		}
	}
	
	return $return_result;
}


//CLASSES


?>
