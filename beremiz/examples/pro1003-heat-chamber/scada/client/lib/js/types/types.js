//JAVASCRIPT DOCUMENT


/*   Библиотека: функции для работы с типами данных
*
*    Copyright (C) 2010-2013  ATgroup09 (atgroup09@gmail.com)
*
*    The JavaScript code in this page is free software: you can
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


/*	Глобальные переменные:	Нет.
*
*
*	Описание функций:
*
*		*** проверка - является ли выражение числом ***
*		is_number(var_in)
*
*		*** проверка - является ли выражение целым числом ***
*		is_integer(var_in)
*
*		*** проверка - является ли выражение числом с плавающей точкой ***
*		is_float(var_in)
*
*		*** проверка - является ли выражение пустым ***
*		is_empty(var_in)
*
*		*** проверка типов заданных параметров ***
*		check_components(array_typeof_parameters_in, array_typeof_in)
*
*		*** проверка - является ли объект массивом ***
*		is_array(obj_in)
*
*		*** проверка - является ли объект формой (<form></form>) ***
*		is_form(obj_in)
*
*		*** проверка - является ли объект узлом "дерева" документа ***
*		is_node(obj_in)
* 
* 		*** check structure of object (extended version of check_components()) ***
* 		check_object(obj_in, array_params_in)
* 
* 		*** checking of existing objects (variables, functions) ***
*		check_existing_objects(array_params_in) 
*
*
*	Описание классов: Нет.
*
*
*	Описание методов: Нет.
*
*
*	Наследование: Нет.
*
*
*	Инициализация глобальных переменных: Нет.
*/


/*	Зависимости:
*
*		- regexp.js:
*			-- search_sub_string().
*/


//ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ


//ОПИСАНИЕ ФУНКЦИЙ

/*	Функция:	Проверка - является ли значение выражение пустым (т.е. == NULL, '', 0, 0.0).
*	Вход:
*				var_in - любое выражение.				[ANY TYPE]
*	Выход:
*				true  - если значение выражения пустое,	[BOOLEAN]
*				false - если выражение не пустое.		[BOOLEAN]
*/
function is_empty(var_in)
{
	//Проверка входных параметров
	if(typeof var_in != "undefined")
	{
		//если входной параметр является типом "string", то
		//проверяется длина строки
		if(typeof var_in == "string")
		{
			if(var_in.length)
			{
				return false;
			}
		}
		else
		{
			//* т.к. typeof null == "object" (var_in)
			if(var_in)
			{
				return false;
			}
		}
	}
	
	return true;
}


/*	Функция:	Проверка - является ли выражение числом.
*	Вход:
*				var_in - любое выражение.					[ANY TYPE]
*	Выход:
*				true  - если выражение является числом,		[BOOLEAN]
*				false - если выражение не является числом.	[BOOLEAN]
*/
function is_number(var_in)
{
	//Проверка входных параметров
	if(typeof var_in != "undefined")
	{
		if(typeof var_in != "object")
		{
			//проверка - является ли входной параметр нечисловым выражением
			if(!isNaN(var_in))
			{
				return true;
			}
		}
	}
	
	return false;
}


/*	Функция:	Проверка - является ли выражение целым числом.
*	Вход:
*				var_in - любое выражение.	[ANY TYPE]
*	Выход:
*				true  - если выражение является целым числом,		[BOOLEAN]
*				false - если выражение не является целым числом.	[BOOLEAN]
*/
function is_integer(var_in)
{
	//Проверка входных параметров
	if(typeof var_in != "undefined")
	{
		if(typeof var_in != "object")
		{
			//Проверка существования функции search_sub_string()
			if(typeof search_sub_string == "function")
			{
				//проверка - является ли входной параметр нечисловым выражением
				if(!isNaN(var_in))
				{
					//определяем - является ли входной параметр целым числом
					//* не должно быть разделителя дробной части	[STRING]
					var buff = var_in + '';
					
					
					if(!search_sub_string("[.]", buff))
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}


/*	Функция:	Проверка - является ли выражение числом с плавающей точкой.
*	Вход:
*				var_in - любое выражение.	[ANY TYPE]
*	Выход:
*				true  - если выражение является числом с	[BOOLEAN]
*						плавающей точкой,
*				false - если выражение не является числом	[BOOLEAN]
*						с плавающей точкой.
*/
function is_float(var_in)
{
	//Проверка входных параметров
	if(typeof var_in != "undefined")
	{
		if(typeof var_in != "object")
		{
			//Проверка существования функции search_sub_string() 
			if(typeof search_sub_string == "function")
			{
				//проверка - является ли входной параметр нечисловым выражением
				if(!isNaN(var_in))
				{
					//определяем - является ли входной параметр целым числом
					//* не должно быть разделителя дробной части
					var buff = var_in + '';	//[STRING]
					
					
					if(search_sub_string("[.]", buff))
					{
						return true;
					}
				}
			}
		}
	}
	
	return false;
}


/*	Функция:	Проверка типов заданных параметров.
*	Вход:
*				array_typeof_parameters_in	- указатель на массив типов компонентов			[OBJECT]
*												объекта, полученных через оператор typeof,
*				array_re_typeof_in		- указатель на массив типов, которым должны		[OBJECT]
*												соответствовать компоненты объекта
*												(значения массива - строка регулярного
*												выражения, например, "string|number"). 
*	Выход:
*				true  - если все значения входных массивов идентичны;	[BOOLEAN]
*				false - если хотя бы одно из значений входных массивов	[BOOLEAN]
*						отличное от другого.
*
*	Описание:
*				например, проверка компонентов объекта Form:
*
*					//инициализация объекта формы
*					var form = document.getElementById("form1");
*
*					//формирование массива типом компонентов объекта через оператор typeof
*					array_typeof_parameters_in = new Array(typeof form.obj_in.length, typeof form.name, typeof form.elements);
*
*					//формирование массива типов, которым должны соответствовать компоненты объекта
*					array_typeof_in = new Array("number", "string", "object");
*
*					//проверка соответствия типов
*					if(check_components(array_typeof_parameters_in, array_typeof_in)) alert("This is form!");
*					else alert("This is not form!");
*/
function check_components(array_typeof_parameters_in, array_re_typeof_in)
{
	//Проверка входных параметров
	if(typeof array_typeof_parameters_in == "object" && typeof array_re_typeof_in == "object")
	{
		//проверка существования у входных объектов свойств length
		if(typeof array_typeof_parameters_in.length == "number" && typeof array_re_typeof_in.length == "number")
		{
			//проверка размерностей входных массивов (должны быть одинаковы)
			if(array_typeof_parameters_in.length == array_re_typeof_in.length)
			{
				//проверка существования функции search_sub_string()
				if(typeof search_sub_string == "function")
				{
					//объявление переменных
					
					//признак несоответствия элементов	[BOOLEAN]
					//* false - значения идентичны,
					//* true - значения не идентичны (несовпадение). 
					var f_break = false;
					
					
					//перебор входных массивов
					for(var i=0; i<array_typeof_parameters_in.length; i++)
					{
						//сравнение значений массивов
						if(!search_sub_string(array_re_typeof_in[i], array_typeof_parameters_in[i]))
						{
							//если значения массивов не идентичны, то формируем признак и завершаем цикл
							f_break = true;
							break;
						}
					}
					
					//проверка признака несоответствия
					if(!f_break)
					{
						return true;
					}
				}
			}
		} 
	}
	
	return false;
}


/*	Функция:	Проверка - является ли объект массивом.
*	Вход:
*				obj_in - указатель на объект.	[OBJECT]
*	Выход:
*				true  - если объект является массивом;		[BOOLEAN]
*				false - если объект не является массивом.	[BOOLEAN]
*/
function is_array(obj_in)
{
	//Проверка входных параметров
	if(typeof obj_in == "object")
	{
		//* т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования функции check_components()
			if(typeof check_components == "function")
			{
				//объявление переменных
				
				//формирование массива типом компонентов объекта через оператор typeof	[OBJECT]
				var array_typeof_parameters = new Array(typeof obj_in.length, typeof obj_in.concat, typeof obj_in.join, typeof obj_in.pop, typeof obj_in.push, typeof obj_in.reverse, typeof obj_in.shift, typeof obj_in.slice, typeof obj_in.sort);
				
				//формирование массива типов, которым должны соответствовать компоненты объекта	[OBJECT]
				var array_typeof = new Array("number", "function", "function", "function", "function", "function", "function", "function", "function");
				
				
				//проверка соответствия типов
				return check_components(array_typeof_parameters, array_typeof);
			}
		}
	}
	
	return false;
}


/*	ФУНКЦИЯ:	Проверка - является ли объект узлом "дерева" документа.
*	ВХОД:
*				obj_in - указатель на узел "дерева" документа.	[OBJECT]
*	ВЫХОД:
*				true	- если obj_in является узлом дерева документа.		[BOOLEAN]
				false	- если obj_in не является узлом дерева документа.	[BOOLEAN]
*	Описание:
*				Если не задан один из входных параметров, то возвращается false.
*
*				Проверка осуществляется по следующим правилам:
*					- у объекта node_in должно быть свойство nodeName типа STRING.
*/
function is_node(obj_in)
{
	//Проверяем входные парараметры
	if(typeof obj_in == "object")
	{
		//* т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования функции check_components()
			if(typeof check_components == "function")
			{
				//объявление переменных
				
				//формирование массива типом компонентов объекта через оператор typeof	[OBJECT]
				var array_typeof_parameters  = new Array(typeof obj_in.nodeName);
				
				//формирование массива типов, которым должны соответствовать компоненты объекта	[OBJECT]
				var array_typeof = new Array("string");
				
				
				//проверка соответствия типов
				return check_components(array_typeof_parameters, array_typeof);
			}
		}
	}
	
	return false;
}


/*	Function:	check an object of document.
*	Input:
*				obj_in - object.	[OBJECT]
*	Output:
*				result:				[BOOLEAN]
*					- true  - input object is Document,
*					- false - input object is not Document.
*/
function is_document(obj_in)
{
	//Check functions
	if(typeof check_components != "function")
	{
		return false;
	}
	
	//Check input arguments
	if(typeof obj_in != "object")
	{
		return false;
	}
	
	//** since type of NULL is object
	if(!obj_in)
	{
		return false;
	}
	
	//* array of types of components of the object	[ARRAY]
	var array_typeof_parameters = new Array(typeof obj_in.firstChild, typeof obj_in.childNodes, typeof obj_in.createElement, typeof obj_in.createTextNode, typeof obj_in.getElementsByTagName);
	
	//* array of the required types	[ARRAY]
	var array_typeof			= new Array("object", "object", "function|object|unknown", "function|object|unknown", "function|object|unknown");
	
	
	return check_components(array_typeof_parameters, array_typeof);
}


/*	Функция:	Получение массива из значений.
*	Вход:
*				params_in - значение или массив значений.	[ANY TYPES]
*	Выход:
*				Массив из значений.							[ARRAY]
*	Описание:
*				Если params_in - массив, то он же и возвращается.
*				Если params_in - переменная (не массив), то добавляется в выходной массив.
*
*				Если входной параметр не задан (null), то возвращается пустой массив.
*/
function get_type_array(params_in)
{
	//Объявление переменных
	
	//* массив строк дополнительных параметров	[ARRAY]
	var return_array = new Array();
	
	
	//Проверка функции is_array()
	if(typeof is_array != "function")
	{
		return return_array;
	}
	
	//Проверка функции is_empty()
	if(typeof is_empty != "function")
	{
		return return_array;
	}
	
	//Проверка входного параметра
	if(is_array(params_in))
	{
		//инициализация выходного параметра
		return_array = params_in;
	}
	else
	{
		//проверка на пустое значение
		if(!is_empty(params_in))
		{
			//формирование выходного параметра
			return_array.push(params_in);
		}
	}
	
	return return_array;
}


/*	Function:	check structure of object (extended version of check_components()).
*	Input:
*				obj_in			- object,	[OBJECT]
*				array_params_in	- array with a description of the components.	[ARRAY]
*	Output:
*				result:	[BOOLEAN]
*					- true  - object contains components,
*					- false - object not contains components.
*	Note:
*
*				false is returned:
*					- if obj_in is undefined (null or not object),
*					- if array_params_in is undefined (null or not array),
*					- ifarray_params_in is the array, but it is empty.
*
*				structure of element of array_params_in (description of the components of an object):
*
*					- ["name"]		- name of component (required!!!);	[STRING]
*
*					- ["data_type"]	- data type value of the component (regexp string)	[STRING]
*						* supported types: "string", "boolean",	"object", "number", "function", "node", "document", "array", "integer", "float";
*
*					- ["value"]		- value of the component (regexp string)	[STRING]
*						* for data types: "string", "boolean", "number", "integer", "float"!
*
*					- ["null_value"]	- NULL value:	[BOOLEAN]
*											-- true		- allow (default),
*											-- false	- not allow.
*
*
*				Example 1:
*
*					obj_in			= {state: "start", lang: "Ru", arr: new Array(1, 2, 3), num: 10, other: null, func: on_button_click};
*
*					array_params_in	= new Array({name: "state",	data_type: "string", value: "^start$|^started$|^end$", null_value: false},
*												{name: "lang", data_type: "string", value: "Ru", null_value: false},
*												{name: "arr", data_type: "array", null_value: true},
*												{name: "num", data_type: "number",	value: "^10$|^0.1$", null_value: false},
*												{name: "other"},
*												{name: "func", data_type: "function", null_value: false}
*											   );
*/
function check_object(obj_in, array_params_in)
{
	//Check functions
	if(typeof search_sub_string != "function")
	{
		return false;
	}
	
	if(typeof is_array != "function")
	{
		return false;
	}
	
	//Check input arguments
	if(typeof obj_in != "object")
	{
		return false;
	}
	
	//** since type of NULL is object
	if(!obj_in)
	{
		return false;
	}
	
	if(typeof array_params_in != "object")
	{
		return false;
	}
	
	if(!is_array(array_params_in))
	{
		return false;
	}
	
	//* name of component	[STRING || NULL]
	var name = null;
	
	//* allowed NULL		[BOOLEAN]
	var null_value = true;
	
	//* true if value of option is NULL	[BOOLEAN]
	var opt_is_null	= false;
	
	//* result of checking data type	[BOOLEAN]
	var checkResDataType = false;
	
	//* counter	[NUMBER]
	var c = 0;
	
	
	for(var i=0; i<array_params_in.length; i++)
	{
		//check element of array
		if(typeof array_params_in[i] != "object") continue;
		if(!array_params_in[i]) continue;
		
		//check option "name"
		if(typeof array_params_in[i]["name"] != "string") continue;
		
		name		= array_params_in[i]["name"];
		null_value	= true;
		opt_is_null = false;
		checkResDataType = false;
		
		//check component of the object
		if(typeof obj_in[name] == "undefined") return false;
		
		//check option "null_value"
		if(typeof array_params_in[i]["null_value"] == "boolean")
		{
			null_value = array_params_in[i]["null_value"];
		}
		
		//check value for NULL
		if(!search_sub_string("^string$|^boolean$|^number$|^function$", (typeof obj_in[name])))
		{
			if(!obj_in[name])
			{
				opt_is_null = true;
				if(!null_value) return false;
			}
		}
		
		//check option "data_type"
		if(typeof array_params_in[i]["data_type"] == "string" && !opt_is_null)
		{
			if(search_sub_string(array_params_in[i]["data_type"], "node"))
			{
				if(typeof is_node != "function") return false;
				if(is_node(obj_in[name])) checkResDataType = true;
			}
			
			if(search_sub_string(array_params_in[i]["data_type"], "document"))
			{
				if(typeof is_document != "function") return false;
				if(is_document(obj_in[name])) checkResDataType = true;
			}
			
			if(search_sub_string(array_params_in[i]["data_type"], "array"))
			{
				if(is_array(obj_in[name])) checkResDataType = true;
			}
			
			if(search_sub_string(array_params_in[i]["data_type"], "integer|int"))
			{
				if(typeof is_integer != "function") return false;
				if(is_integer(obj_in[name])) checkResDataType = true;
			}
			
			if(search_sub_string(array_params_in[i]["data_type"], "float|real|double"))
			{
				if(typeof is_float != "function") return false;
				if(is_float(obj_in[name])) checkResDataType = true;
			}
			
			if(search_sub_string(array_params_in[i]["data_type"], "string|boolean|object|number|function"))
			{
				if(search_sub_string(array_params_in[i]["data_type"], (typeof obj_in[name]))) checkResDataType = true;
			}
			
			if(!checkResDataType) return false;
			
			/*switch(array_params_in[i]["data_type"])
			{
				case "node":
					
					if(typeof is_node != "function")
					{
						return false;
					}
					
					if(!is_node(obj_in[name]))
					{
						return false;
					}
					break;
					
				case "document":
					
					if(typeof is_document != "function")
					{
						return false;
					}
					
					if(!is_document(obj_in[name]))
					{
						return false;
					}
					break;
					
				case "array":
					
					if(!is_array(obj_in[name]))
					{
						return false;
					}
					break;
					
				case "integer":
				case "int":
					
					if(typeof is_integer != "function")
					{
						return false;
					}
					
					if(!is_integer(obj_in[name]))
					{
						return false;
					}
					break;
					
				case "float":
				case "real":
				case "double":
					
					if(typeof is_float != "function")
					{
						return false;
					}
					
					if(!is_float(obj_in[name]))
					{
						return false;
					}
					break;
					
				case "string":
				case "boolean":
				case "object":
				case "number":
				case "function":
					
					if(!search_sub_string(array_params_in[i]["data_type"], (typeof obj_in[name])))
					{
						return false;
					}
					break;
					
				default:
					
					return false;
			}*/
		}
		
		//check option "value"
		if(typeof array_params_in[i]["value"] == "string" && !opt_is_null)
		{
			if(search_sub_string("string|boolean|number", (typeof obj_in[name])))
			{
				if(!search_sub_string(array_params_in[i]["value"], obj_in[name].toString()))
				{
					return false;
				}
			}
		}
		
		c++;
	}
	
	return ((!c) ? false : true);
}


/*	Function:	checking of existing objects (variables, functions).
*	Input:
*				array_params_in - array of parameters.	[ARRAY]
*	Output:
*				true if a target meet the requirements, otherwise - false.
*	Note:
*
* 				structure of array_targets_in:
* 
* 					new Array({
* 								name:		   "some_target",		// [STRING]
* 								data_type:	   "some-data-type",	// [STRING]
* 								value:    	   some-value,			// [ANY TYPE]
* 								null_value:    true | false			// [BOOLEAN]
* 								target_class:  "value" | "function" | "object" (by default)	// [STRING]
* 							  },
* 							 ...
* 							);
* 
* 
* 					* required options: "name"!
* 
* 					* "name" - name of target as string (name of variable, function).
*					* "data_type" - regexp-string; supported types: "string", "boolean", "object", "number", "function", "node", "document", "array", "integer", "float".
* 					* "value" - regexp-string; only for data types: "string", "boolean", "number", "integer", "float"!
* 					* "null_value" - true if allowed NULL-value (by default), otherwise - false.
*
*
*				Example 1:
*
*					array_params_in	= new Array({name: "global_val1", target_class: "value"},
*												{name: "global_val2", data_type: "string", target_class: "value"},
*												{name: "array1", data_type: "array", target_class: "value"},
* 												{name: "array2", data_type: "array", null_value: false, target_class: "value"},
* 												{name: "function1", data_type: "function", target_class: "function"},
* 												{name: "num", data_type: "number", value: "^10$|^0.1$", null_value: false, target_class: "value"}
*											   );
* 
* 				If returns false and exists global variable FL_DEBUG_STR, then
* 					FL_DEBUG_STR == "Value 'some name' is undefined or contains an incorrect value!" (for target class "value");
* 					FL_DEBUG_STR == "Function 'some name' is undefined!" (for target class "function")!
* 					FL_DEBUG_STR == "Object 'some name' is undefined or contains an incorrect structure!" (by default)!
*/
function check_existing_objects(array_params_in)
{
	//Check functions
	if(typeof search_sub_string != "function")
	{
		return false;
	}
	
	if(typeof check_object != "function")
	{
		return false;
	}
	
	if(typeof is_array != "function")
	{
		return false;
	}
	
	//Check input arguments
	if(typeof array_params_in != "object")
	{
		return false;
	}
	
	if(!is_array(array_params_in))
	{
		return false;
	}
	
	//* arra of parameters	[ARRAY]
	var array_params = new Array(null);
	
	//* name of component	[STRING || NULL]
	var name = null;
	
	//* target class	[STRING]
	var target_class = "object";
	
	//* object	[OBJECT || NULL]
	var obj = null;
	
	//* test of eval	[STRING]
	var test_eval = null;
	
	//* counter	[NUMBER]
	var c = 0;
	
	
	for(var i=0; i<array_params_in.length; i++)
	{
		if(typeof array_params_in[i] != "object")
		{
			continue;
		}
		
		if(!array_params_in[i])
		{
			continue;
		}
		
		if(typeof array_params_in[i]["name"] != "string")
		{
			continue;
		}
		
		name			= array_params_in[i]["name"];
		target_class	= ((typeof array_params_in[i]["target_class"] == "string") ? array_params_in[i]["target_class"] : "object");
		test_eval		= eval("typeof " + name);
		array_params[0]	= array_params_in[i];
		obj				= new Object();
		
		if(!search_sub_string("undefined|Undefined|UNDEFINED", test_eval))
		{
			obj[name] = eval(name);
		}
		
		if(!check_object(obj, array_params))
		{
			if(typeof FL_DEBUG_STR != "undefined")
			{
				switch(target_class)
				{
					case "variable":
						
						FL_DEBUG_STR = "Value '" + name + "' is undefined or contains an incorrect value!";
						break;
						
					case "function":
						
						FL_DEBUG_STR = "Function '" + name + "()' is undefined!";
						break;
						
					default:
						
						FL_DEBUG_STR = "Object '" + name + "' is undefined or contains an incorrect structure!";
				}
			}
			return false;
		}
		
		c++;
	}
	
	return ((!c) ? false : true);
}


//ОПИСАНИЕ КЛАССОВ


//ОПИСАНИЕ МЕТОДОВ В ПРОТОТИПЕ


//НАСЛЕДОВАНИЕ


//КОНСТРУКТИВНЫЕ ДЕЙСТВИЯ

