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


/*   Library: resources/values.
*
*    Copyright (C) 2014  ATgroup09 (atgroup09@gmail.com)
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
*				~ file_exists().
*
*			+ regexp/regexp.php:
*				~ replace_sub_string().
*
*			+ types/types.php:
*				~ types_checking_existence().
*
*			+ request/request.php:
*				~ get_name_of_language_with_high_quotient().
*
*			+ dom/dom.php:
*				~ get_attribute_of_element();
*				~ phpDOM_get_root_node_from_file();
*				~ phpDOM_parsing().
*/

/*	Global variables: none
*
*	Functions: none.
*
*	Classes:
*/


//** GLOBAL VARIABLES



//** FUNCTIONS



//** CLASSES

class ResValues {
	
	//Options
	
	//* path to resource file	[STRING]
	public $filePath;
	
	//* resource file type ("xml" by default)	[STRING]
	public $fileType;
	
	//* array of values	[ARRAY]
	//*
	//*		["name"] = "value";
	//*		...
	//*
	private $values;
	
	
	//Methods
	
	//*	method: check required functions, classes.
	//*	input:
	//*			$required_in - list of required functions/classes.	[ARRAY]
	//*	output:
	//*			true if OK, otherwise - error.	[BOOLEAN]
	//*	note:
	//*
	public static function _checkExistence($required_in = null) {
		
		global $FL_DEBUG;
		
		if(!function_exists("types_checking_existence"))
		{
			if($FL_DEBUG) echo("Error! Function 'dbMySQL_check_connect_params()' not exists! [values.php -> class ResValues]");
			return false;
		}
		
		return types_checking_existence($required_in, "[values.php -> class ResValues]");
	}
	
	//*	method: check file.
	//*	input:
	//*			$filePath_in - path to resource file.	[STRING]
	//*	output:
	//*			true if the file exists, otherwise - false.	[BOOLEAN]
	//*	note:
	//*
	public static function _checkFile($filePath_in = null) {
		
		$rqt = array(array("name" => "file_exists", "type" => "function")
					);
		
		if(self::_checkExistence($rqt))
		{
			if(is_string($filePath_in))
			{
				if(!empty($filePath_in))
				{
					return file_exists($filePath_in);
				}
			}
		}
		
		return false;
	}
	
	//*	method: get accepted client language name with high quotient.
	//*	input:
	//*			$withoutSubLangName_in - use (true) or not use (false by default) language name without sub-name.	[BOOLEAN]
	//*	output:
	//*			accepted client language name or NULL.	[STRING || NULL]
	//*	note:
	//*			"en-EN" with sub-name, "en" without sub-name
	//*
	public static function _getHQLang($withoutSubLangName_in = false) {
		
		$lang = null;
		
		$rqt = array(array("name" => "get_name_of_language_with_high_quotient", "type" => "function")
					);
		
		if(self::_checkExistence($rqt))
		{
			$withoutSubLangName	= ((is_bool($withoutSubLangName_in)) ? $withoutSubLangName_in : false);
			$lang				= get_name_of_language_with_high_quotient();
			
			if($withoutSubLangName && !empty($lang))
			{
				$buff = explode('-', $lang);
				if(is_array($buff))
				{
					if(count($buff) > 0) $lang = $buff[0];
				}
			}
		}
		
		return $lang;
	}
	
	//*	method: get path to file of resource values.
	//*	input:
	//*			$resValuesDir_in			- path to directory of resource values;	[STRING || NULL]
	//*			$resValuesFileName_in		- name of resource values file;			[STRING]
	//*			$resValuesByAcceptLang_in	- use (true) or not use (false by default) language from header "HTTP_ACCEPT_LANGUAGE";	[BOOLEAN]
	//*			$withoutSubLangName_in		- use (true) or not use (false by default) language name without sub-name.				[BOOLEAN]
	//*	output:
	//*			path to file of resource values or NULL.	[STRING || NULL]
	//*	note:
	//*
	public static function _getFilePath($resValuesDir_in = null, $resValuesFileName_in = null, $resValuesByAcceptLang_in = false, $withoutSubLangName_in = false) {
		
		$filePath = null;
		
		$rqt = array(array("name" => "replace_sub_string", "type" => "function")
					);
		
		if(self::_checkExistence($rqt))
		{
			if(is_string($resValuesFileName_in))
			{
				if(!empty($resValuesFileName_in))
				{
					$filePath		= $resValuesFileName_in;
					$resValuesDir	= replace_sub_string("\/*$", '', $resValuesDir_in, -1);
					
					if(is_string($resValuesDir))
					{
						if(!empty($resValuesDir))
						{
							$resValuesByAcceptLang = ((is_bool($resValuesByAcceptLang_in)) ? $resValuesByAcceptLang_in : false);
							
							if($resValuesByAcceptLang)
							{
								$lang = self::_getHQLang($withoutSubLangName_in);
								if(!empty($lang)) $resValuesDir.= "-".($lang);
							}
							
							$filePath = "{$resValuesDir}/{$resValuesFileName_in}";
						}
					}
				}
			}
		}
		
		return $filePath;
	}
	
	//* method:	read values from the resource file.
	//* input:
	//*			$filePath_in 	- path to resource file;	[STRING]
	//*			$fileType_in	- resource file type ("xml" by default).	[STRING || NULL]
	//* output:
	//*			array of values.	[ARRAY]
	//* note:
	//*			["name"] = "value";
	//*			...
	//*
	public static function _readValuesFromFile($filePath_in = null, $fileType_in = null) {
		
		$_values = array();
		
		$rqt = array(array("name" => "get_attribute_of_element", "type" => "function"),
					 array("name" => "phpDOM_get_root_node_from_file", "type" => "function"),
					 array("name" => "phpDOM_parsing", "type" => "function")
					);
		
		if(self::_checkExistence($rqt))
		{
			$fileType = "xml";
			
			if(is_string($fileType_in))
			{
				if(!empty($fileType_in)) $fileType = $fileType_in;
			}
			
			if(self::_checkFile($filePath_in))
			{
				$rootNode	= phpDOM_get_root_node_from_file($filePath_in, $fileType);
				$nodes		= phpDOM_parsing($rootNode, null, "name", null);
				
				if(is_array($nodes))
				{
					$attrName = null;
					
					for($i=0; $i<count($nodes); $i++)
					{
						if(!is_object($nodes[$i]))          continue;
						if(!is_a($nodes[$i], "domElement")) continue;
						
						$attrName = get_attribute_of_element($nodes[$i], "name");
						
						if(!empty($attrName))
						{
							$_values[$attrName] = ((!empty($nodes[$i]->nodeValue)) ? $nodes[$i]->nodeValue : null);
						}
					}
				}
			}
		}
		
		return $_values;
	}
	
	//* method:	get count of values.
	//* input:
	//*			none.
	//* output:
	//*			count of values.	[INTEGER]
	//* note:
	//*
	public function countValues() {
		
		return count($this->values);
	}
	
	//* method:	clear values.
	//* input:
	//*			none.
	//* output:
	//*			none.
	//* note:
	//*
	public function clearValues() {
		
		$this->values = array();
	}
	
	//* method:	read values from the resource file.
	//* input:
	//*			none.
	//* output:
	//*			array of values.	[ARRAY]
	//* note:
	//*			["name"] = "value";
	//*			...
	//*
	public function readValuesFromFile() {
		
		$_values = self::_readValuesFromFile($this->filePath, $this->fileType);
		
		foreach($_values as $k=>$v)
		{
			$this->values[$k] = $v;
		}
		
		return $this->values;
	}
	
	//* method:	get resource value by name.
	//* input:
	//*			$name_in 			- resource name;	[STRING]
	//*			$defaultValue_in	- value by default (used if the resource value is NULL);	[STRING || NULL]
	//*			$replacedTargets_in	- array of replaceable substrings or NULL;	[ARRAY || NULL]
	//*			$replacedValues_in	- array of real values to replace or NULL.	[ARRAY || NULL]
	//* output:
	//*			value or NULL.	[STRING || NULL]
	//* note:
	//*			Example 1:
	//*
	//*				// <string name="err">Error! {0} is not {1}!</string>
	//*				$value = getValue("err", "error", array("\{0\}", "\{1\}"), array("Abc", "Cde"));
	//*
	//*				// Error! Abc is Cde {1}!
	//*
	public function getValue($name_in = null, $defaultValue_in = null, $replacedTargets_in = null, $replacedValues_in = null) {
		
		$value = null;
		
		if(is_string($name_in))
		{
			if(!empty($name_in)) $value = $name_in;
		}
		
		if(is_string($defaultValue_in))
		{
			if(!empty($defaultValue_in)) $value = $defaultValue_in;
		}
		
		if(is_array($this->values) && is_string($name_in))
		{
			if(!empty($name_in))
			{
				if(!empty($this->values[$name_in]))
				{
					$value = $this->values[$name_in];
				}
			}
		}
		
		if(is_array($replacedTargets_in) && is_array($replacedValues_in))
		{
			$rqt = array(array("name" => "replace_sub_string", "type" => "function")
						);
			
			if(self::_checkExistence($rqt))
			{
				for($i=0; $i<count($replacedTargets_in); $i++)
				{
					if($i < count($replacedValues_in))
					{
						$value = replace_sub_string($replacedTargets_in[$i], $replacedValues_in[$i], $value, -1);
					}
					else
					{
						break;
					}
				}
			}
		}
		
		return $value;
	}
	
	
	//Constructor and Destructor
	
	//*	input:
	//*			$filePath_in 	- path to resource file;	[STRING]
	//*			$fileType_in	- resource file type ("xml" by default).	[STRING || NULL]
	//*	note:
	//*
	function __construct($filePath_in = null, $fileType_in = null)
	{
		$this->filePath = null;
		$this->fileType = "xml";
		$this->values	= array();
		
		if(is_string($filePath_in))
		{
			if(!empty($filePath_in)) $this->filePath = $filePath_in;
		}
		
		if(is_string($fileType_in))
		{
			if(!empty($fileType_in)) $this->fileType = $fileType_in;
		}
	}
	
	function __destruct()
	{
		unset($this->filePath);
		unset($this->fileType);
		unset($this->values);
	}
}


?>
