//JAVASCRIPT DOCUMENT


/*   Библиотека: функции для работы с объектами (Document Object Model)
*
*    Copyright (C) 2010-2011  ATgroup09 (atgroup09@gmail.com)
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


/*	Глобальные переменные: нет.
*
*	Описание функций:
* 
*		*** наследование класса ***
*		extend_class(child_in, parent_in)
*
*		*** вставка узла в объект (последовательно) ***
*		object_attach(obj_in, obj_attach_in, pos_in)
*
*		*** удаление узла из объекта ***
*		object_unattach(obj_in, obj_unattach_in)
* 
*		*** проверка значения атрибута ***
*		check_attribute_of_element(obj_in, attr_name_in, re_attr_value_in)
*
*		*** установка значения атрибута ***
*		set_attribute_of_element(obj_in, attr_name_in, attr_value_in)
*
*		*** получение значения атрибута ***
*		get_attribute_of_element(obj_in, attr_name_in)
*
*		*** получение указателя на элемент по заданным параметрам ***
*		get_element_by_parameters(id_in, re_node_name_in, attr_name_in)
* 
* 		*** get object of class 'Document' from a node ***
* 		jsDOM_get_document_from_node(node_in)
* 
* 		*** get node "body" from a document ***
* 		jsDOM_get_body_from_document(document_in)
* 
* 		*** get node "body" from a node ***
* 		jsDOM_get_body_from_node(node_in)
* 
*		*** get root-node of a document ***
*		jsDOM_get_root_node_of_document(document_in)
* 
*		*** import a node with attributes and associates it with a target document ***
*		jsDOM_import_one_node(target_document_in, node_in)
*
*		*** import a node with attributes and all child nodes (if defined) and associates it with a target document ***
*		jsDOM_import_node(target_document_in, node_in, deep_in)
*
*		*** поиск соответствия заданных параметров с параметрами узла дерева документа ***
*		jsDOM_search_node(node_in, re_node_name_in, attr_name_in, re_attr_value_in)
*
*		*** разбор дерева докмента (парсинг) ***
*		jsDOM_parsing(root_node_in, re_node_name_in, attr_name_in, re_attr_value_in)
*
*		*** получение указателя на объект с заданными параметрами ***
*		jsDOM_get_object(root_node_in, re_node_name_in, attr_name_in, re_attr_value_in)
*
*		*** установка визуального состояния объекта (объектов) ***
*		jsDOM_set_visual_state(root_node_in, re_list_names_in, visual_state_in)
*
*
*	Описание классов: нет.
*
*	Описание методов в прототипе: нет.
*
*	Наследование: Нет.
*
*	Инициализация глобальных переменных: Нет.
*/


/*	Зависимости: Нет.
*		regexp.js:
*			- search_sub_string(). 
*
*		types.js:
*			- is_node().
*
*		screen.js:
*			- object_show(),
*			- object_hide().
*/


//ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ


//ОПИСАНИЕ ФУНКЦИЙ

/*	Функция:	наследование класса.
*	Вход:
*				child_in	- указатель на дочерний класс;		[FUNCTION]
*				parent_in	- указатель на родительский класс.	[FUNCTION]
*	Выход:		нет.
*	Описание:
*				Если не задан один из входных параметров, то
*					наследование класса не производится.
*
*				Класс child_in становится наследником parent_in
*					(наследуются все свойства и методы parent_in, т.е.
*					доступны в child_in). 
*
*				!!!Внимание: в классе child_in при добавлении методов и
*					свойств в объект this необходимо вызвать следующую инструкцию:
*					* вызов конструктора родительского класса в потомке - 
*					child_class.superclass.constructor.call(this, arguments);
*						где arguments - указатель на атрибуты родительского класса или
*											на объект arguments.
*
*				Пример:
*				function parent_class(value_in)
*				{
*					//скрытые атрибуты
*					var value = null;
*
*					//методы
*					this.show = function()
*						{
*							//show "value"
*							alert(value);
*						};
*
*					//конструктивные действия
*					value = value_in;
*				}
*
*				function child_class(value_in)
*				{
*					//скрытые атрибуты
*					var value = null;
*
*					//методы
*					this.get_value = function()
*						{
*							//return "value"
*							return value;
*						};
*
*					//конструктивные действия
*					value = value_in;
*
*					//проверка существования у объекта child_class свойства "superclass"
*					//* свойство "superclass" доступно после наследования 
*					if(typeof child_class.superclass == "object")
*					{
*						//проверка существования у свойства "superclass" свойства "constructor"
*						//* свойство "constructor" доступно после наследования
*					 	if(typeof child_class.superclass.constructor == "function")
*						{
*							//вызов конструктора родительского класса с передачей параметра value
*							child_class.superclass.constructor.call(this, value);
*						}
*					}
*				}
*
*				//extend
*				extend_class(child_class, parent_class);
*
*				//create new object of class "child_class"
*				var test = new child_class("abc");
*
*				alert(test.get_value());	//=> window with context "abc"
*				test.show();				//=> window with context "abc"
*/
function extend_class(child_in, parent_in)
{
	//Объявление переменных
	
	//вспомогательный объект-функция	[FUNCTION]
	var tmp_func = new Function();
	
	
	//инициализация свойства "prototype" объекта tmp_func
	//в значение свойства "prototype" класса parent_in
	tmp_func.prototype = parent_in.prototype;
	
	//инициализация свойства "prototype" дочернего класса
	//указателем на новый объект класса "tmp_func"
	child_in.prototype = new tmp_func();
	
	//обновляем конструктор дочернего класса, т.к.
	//он унаследовал "элементы" родительского класса
	child_in.prototype.constructor = child_in;
	
	//обновляем свойство "superclass" дочернего класса - 
	//для возможности вызова его конструктора
	child_in.superclass = parent_in.prototype;
}


/*	Функция:	вставка узла в объект (последовательно).
*	Вход:
*				obj_in			- указатель на родительский объект,	[OBJECT]
*				obj_attach_in	- указатель на вставляемый объект, 	[OBJECT]
*				pos_in			- позиция вставки:					[STRING || NULL]
*									"start"	- в начало родительского объекта,
*									"end"	- в конец родительского объекта (по-умолчанию).
*	Выход:
*				указатель на прикрепленный элемент или null.	[OBJECT || NULL]
*	Описание:
*				Если не задан входной параметр или возникла ошибка, то возвращается null.
*
*				Оба входных параметра - должны являться узлами "дерева" документа (класс "Node").
*/
function object_attach(obj_in, obj_attach_in, pos_in)
{
	//Объявление переменных
	
	//* указатель на вставленный объект	[OBJECT || NULL]
	var return_attach = null;

	
	//Проверка существования функции search_sub_string()
	if(typeof search_sub_string != "function")
	{
		return return_attach;
	}
	
	//Проверка существования функции is_node()
	if(typeof is_node != "function")
	{
		return return_attach;
	}
	
	//Проверка - является ли входные параметры узлами "дерева" документа
	if(is_node(obj_in) && is_node(obj_attach_in))
	{
		//проверка параметра pos_in и существования у объекта obj_in метода insertBefore()
		//* in Firefox:		typeof obj_in.insertBefore == "function"
		//* in Opera:		typeof obj_in.insertBefore == "function"
		//* in IE 4...7:	typeof obj_in.insertBefore == "object"
		if(typeof pos_in == "string" && search_sub_string("function|object", (typeof obj_in.insertBefore)))
		{
			switch(pos_in)
			{
				case "start":
				case "Start":
				case "START":
					
					//вставка объекта в начало родительского
					return_attach = obj_in.insertBefore(obj_attach_in, obj_in.firstChild);
					
					break;
			}
		}
		
		//проверка указателя
		if(!return_attach)
		{
			//проверка существования у объекта obj_in метода appendChild()
			//* in Firefox:		typeof obj_in.appendChild == "function"
			//* in Opera:		typeof obj_in.appendChild == "function"
			//* in IE 4...7:	typeof obj_in.appendChild == "object"
			if(search_sub_string("function|object", (typeof obj_in.appendChild)))
			{
				//вставка объекта
				return_attach = obj_in.appendChild(obj_attach_in);
			}
		}
	}
	
	return return_attach;
}


/*	Функция:	удаление узла из объекта.
*	Вход:
*				obj_in			- указатель на родительский объект;	[OBJECT]
*				obj_unattach_in	- указатель на удаляемый объект или null. 	[OBJECT || NULL]
*	Выход:
*				указатель на последний удаленный объект или null.	[OBJECT || NULL]
*	Описание:
*				Если не задан входной параметр или возникла ошибка, то возвращается null.
*
*				Если obj_unattach_in == null, то удаляются все дочерние элементы.
*/
function object_unattach(obj_in, obj_unattach_in)
{
	//Объявление переменных
	
	//* указатель на последний удаленный элемент	[OBJECT || NULL]
	var return_obj = null;

	
	//Проверка существования функции search_sub_string()
	if(typeof search_sub_string != "function")
	{
		return return_obj;
	}
	
	//Проверка существования функции is_node()
	if(typeof is_node != "function")
	{
		return return_obj;
	}
	
	//Проверка - является ли объект obj_in узлом "дерева" документа
	if(is_node(obj_in))
	{
		//проверка существования у объекта obj_in метода appendChild()
		//* in Firefox:		typeof obj_in.removeChild == "function"
		//* in Opera:		typeof obj_in.removeChild == "function"
		//* in IE 4...7:	typeof obj_in.removeChild == "object"
		if(search_sub_string("function|object", (typeof obj_in.removeChild)))
		{
			//проверка - является ли объект obj_unattach_in узлом "дерева" документа
			if(is_node(obj_unattach_in))
			{
				//удаление одного дочернего узла
				return_obj = obj_in.removeChild(obj_unattach_in);
			}
			else
			{
				//удаление всех дочерних узлов
				while(obj_in.childNodes.length)
				{
					//получение указателя на дочерний элемент
					if((return_obj = obj_in.childNodes[0]))
					{
						//удаление дочернего элемента
						return_obj = obj_in.removeChild(return_obj);
					}
				}
			}
		}
	}
	
	return return_obj;
}


/*	Функция:	проверка значения атрибута элемента.
*	Вход:
*				obj_in				- указатель на элемент (объект),			[OBJECT]
*				attr_name_in		- название атрибута (например, "class"),	[STRING]
*				re_attr_value_in	- значение атрибута (строка регулярного		[STRING]
*										выражения, например, "button1|Button1").
*	Выход:
*				результат проверки:												[BOOLEAN]
*					- true	- если значение атрибута attr_name_in объекта obj_in
*								равно одному из значений, заданному в регулярном
*								выражении re_attr_value_in,
*					- false	- элемент не содержит заданный атрибут.
*/
function check_attribute_of_element(obj_in, attr_name_in, re_attr_value_in)
{
	//Объявление переменных
	var result = false;	//[BOOLEAN]
	

	//Проверка входных параметров
	if(typeof obj_in == "object" && typeof attr_name_in == "string" && typeof re_attr_value_in == "string")
	{
		//* т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка - является ли obj_in узлом "дерева"
			if(typeof obj_in.nodeName == "string" && typeof obj_in.nodeType == "number")
			{
				if(obj_in.nodeType == 1)
				{
					//проверка наличия функции search_sub_string()
					if(typeof search_sub_string == "function")
					{
						//Если attr_name_in == "class", то
						//использовать свойство - className,
						//иначе - метод getAttribute()
						if(!search_sub_string("class|Class|CLASS", attr_name_in))
						{
							if(search_sub_string(re_attr_value_in, obj_in.getAttribute(attr_name_in)))
							{
								result = true;
							}
						}
						else
						{
							if(search_sub_string(re_attr_value_in, obj_in.className))
							{
								result = true;
							}
						}
					}
				}
			}
		}
	}
	
	return result; 
}


/*	Функция:	установка значения атрибута элемента.
*	Вход:
*				obj_in			- указатель на элемент (объект),			[OBJECT]
*				attr_name_in	- название атрибута (например, "class"),	[STRING]
*									значение к-рого нужно получить (если
*									такого атрибута нет - он будет создан),
*				attr_value_in	- значение атрибута.						[ANY TYPE && NOT OBJECT]
*	Выход:
*				true - значение атрибута установлено, иначе - false.		[BOOLEAN]
*/
function set_attribute_of_element(obj_in, attr_name_in, attr_value_in)
{
	//Объявление переменных
	var result = false;	//[BOOLEAN]
	

	//Проверка входных параметров
	if(typeof obj_in == "object" && typeof attr_name_in == "string" && typeof attr_value_in != "undefined")
	{
		//* т.к. typeof null == "object" (obj_in)
		if(obj_in && attr_name_in.length && typeof attr_value_in != "object")
		{
			//проверка - является ли obj_in узлом "дерева"
			if(typeof obj_in.nodeName == "string" && typeof obj_in.nodeType == "number")
			{
				if(obj_in.nodeType == 1)
				{
					//проверка наличия функции search_sub_string()
					if(typeof search_sub_string == "function")
					{
						//Если attr_name_in == "class", то
						//использовать свойство - className,
						//иначе - метод setAttribute()
						if(!search_sub_string("class|Class|CLASS", attr_name_in))
						{
							obj_in.setAttribute(attr_name_in, attr_value_in);
							result = true;
						}
						else
						{
							obj_in.className = attr_value_in;
							result = true;
						}
					}
				}
			}
		}
	}
	
	return result;  
}


/*	Функция:	получение значения атрибута элемента.
*	Вход:
*				obj_in			- указатель на элемент (объект),			[OBJECT]
*				attr_name_in	- название атрибута (например, "class"),	[STRING]
*									значение к-рого нужно получить.
*	Выход:
*				Значение атрибута attr_name_in элемента (объекта) obj_in	[STRING || NULL]
*					или null - если ошибка.
*/
function get_attribute_of_element(obj_in, attr_name_in)
{
	//Объявление переменных
	var attr_value = null;	//[STRING || NULL]
	

	//Проверка входных параметров
	if(typeof obj_in == "object" && typeof attr_name_in == "string")
	{
		//* т.к. typeof null == "object" (obj_in)
		if(obj_in && attr_name_in.length)
		{
			//проверка - является ли obj_in узлом "дерева"
			if(typeof obj_in.nodeName == "string" && typeof obj_in.nodeType == "number")
			{
				if(obj_in.nodeType == 1)
				{
					attr_value = obj_in.getAttribute(attr_name_in);
					
					//проверка наличия функции search_sub_string()
					if(typeof search_sub_string == "function")
					{
						//Если attr_name_in == "class", то
						//использовать свойство - className,
						//иначе - метод setAttribute()
						if(!search_sub_string("class|Class|CLASS", attr_name_in))
						{
							attr_value = obj_in.getAttribute(attr_name_in);
						}
						else
						{
							attr_value = obj_in.className; 
						}
					}
				}
			}
		}
	}
	
	return attr_value;  
}


/*	Функция:	получение указателя на элемент по заданным параметрам.
*	Вход:
*				id_in			- значение атрибута "id",					[STRING]
*				re_node_name_in	- имя узла (строка регулярного выражения,	[STRING]
*									например, "input|INPUT"),
*				attr_name_in	- название атрибута (например, "class") или	[NULL || STRING]
*									 null (* необязательный параметр).
*	Выход:
*				объект с заданными параметрами или null, если он не найден.	[OBJECT || NULL]
*/
function get_element_by_parameters(id_in, re_node_name_in, attr_name_in)
{
	//Объявление переменных
	var obj = null;	//[OBJECT || NULL]

	
	//Проверка наличия функции search_sub_string()
	if(typeof search_sub_string == "function")
	{
		//Проверка входных (обязательных) параметров
		if(typeof id_in == "string" && typeof re_node_name_in == "string")
		{
			if(document.getElementById(id_in))
			{
				obj = document.getElementById(id_in);
				
				//Если искомый объект не с именем узла, равным одному
				//из re_node_name_in значений, то null.
				if(!search_sub_string(re_node_name_in, obj.nodeName))
				{
					obj = null;
				}
			}
		}
	}
	
	//Проверка входных (необязательных) параметров
	if(obj && typeof attr_name_in == "string")
	{
		//проверка - является ли obj_in узлом "дерева"
		if(typeof obj.nodeName == "string")
		{
			//Если у искомого объекта нет атрибута
			//с именем attr_name_in, то null.
			
			//Если attr_name_in == "class", то
			//использовать свойство - className,
			//иначе - метод getAttribute()
			if(!search_sub_string("class|Class|CLASS", attr_name_in))
			{
				if(!obj.getAttribute(attr_name_in))
				{
					obj = null;
				}
			}
			else
			{
				if(!obj.className)
				{
					obj = null;
				}
			}
		}
	}

	return obj;
}


/*	Function:	get object of class 'Document' from a node.
*	Input:
*				node_in - node.	[OBJECT]
*	Output:
*				an object of class 'Document' or null.	[OBJECT || NULL]
*	Note:
* 
*/
function jsDOM_get_document_from_node(node_in)
{
	//Check functions
	if(typeof is_node != "function")
	{
		return null;
	}
	
	//Check input arguments
	if(typeof node_in != "object")
	{
		return null;
	}
	
	if(!is_node(node_in))
	{
		return null;
	}
	
	if(node_in.contentDocument)
	{
		return node_in.contentDocument;
	}
	else if(node_in.contentWindow)
	{
		return node_in.contentWindow.document;
	}
	else if(node_in.document)
	{
		return node_in.document;
	}
	
	return null;
}


/*	Function:	get node "body" from a document.
*	Input:
*				document_in - object of class 'Document'.	[OBJECT]
*	Output:
*				node-object "body" or null.	[OBJECT || NULL]
*	Note:
* 
*/
function jsDOM_get_body_from_document(document_in)
{
	//Check functions
	if(typeof is_document != "function")
	{
		return null;
	}
	
	//Check input arguments
	if(typeof document_in != "object")
	{
		return null;
	}
	
	if(!is_document(document_in))
	{
		return null;
	}
	
	return (document_in.body ? document_in.body : null);
}


/*	Function:	get node "body" from a node.
*	Input:
*				node_in - node-object.	[OBJECT]
*	Output:
*				node-object "body" or null.	[OBJECT || NULL]
*	Note:
* 
*/
function jsDOM_get_body_from_node(node_in)
{
	//Check functions
	if(typeof jsDOM_get_document_from_node != "function")
	{
		return null;
	}
	
	if(typeof jsDOM_get_body_from_document != "function")
	{
		return null;
	}
	
	//Check input arguments
	if(typeof node_in != "object")
	{
		return null;
	}
	
	//* object of class 'Document'	[OBJECT || NULL]
	var doc = jsDOM_get_document_from_node(node_in);
	
	
	return jsDOM_get_body_from_document(doc);
}


/*	Function:	get root-node of a document.
*	Input:
*				document_in - an object of class 'Document'.	[OBJECT]
*	Output:
*				root-node or null.	[OBJECT || NULL]
*	Note:
*
*				Returns only node with type by 1 (ELEMENT_NODE)!
*/
function jsDOM_get_root_node_of_document(document_in)
{
	//Check functions
	if(typeof is_node != "function")
	{
		return null;
	}
	
	if(typeof is_document != "function")
	{
		return null;
	}
	
	//Check input argument 'document_in'
	if(typeof document_in != "object")
	{
		return null;
	}
	
	if(!is_document(document_in))
	{
		return null;
	}
	
	//Search
	for(var i=0; i<document_in.childNodes.length; i++)
	{
		if(is_node(document_in.childNodes[i]) == 1)
		{
			return document_in.childNodes[i];
		}
	}
	
	return null;
}


/*	Function:	import a one node with attributes and associates it with a target document.
*	Input:
*				target_document_in	- target document or null,	[OBJECT || NULL]
*				node_in				- imported a node.			[OBJECT]
*	Output:
*				copy of a one node to import and associates it with the target document or null.	[OBJECT || NULL]
*	Note:
*
*				If target_document_in is not an object of class 'Document' or NULL then will be used current document.
*
*
*				Example:
*
*					var new_div = document.createElement("DIV");
*					var new_doc = jsDOM_new_document();
*					var inode   = jsDOM_import_one_node(new_doc, new_div);
*					var first   = jsDOM_get_root_node_of_document(new_doc);
*
*					object_attach(first, inode);
*/
function jsDOM_import_one_node(target_document_in, node_in)
{
	//* result	[OBJECT || NULL]
	var return_result = null;
	
	
	//Check functions
	if(typeof is_node != "function")
	{
		return return_result;
	}
	
	if(typeof is_document != "function")
	{
		return return_result;
	}
	
	if(typeof set_attribute_of_element != "function")
	{
		return return_result;
	}
	
	//Check input arguments
	if(typeof node_in != "object")
	{
		return return_result;
	}
	
	if(!is_node(node_in))
	{
		return return_result;
	}
	
	//* target document (current document by default)	[OBJECT]
	var target_document = document;
	
	
	if(typeof target_document_in == "object")
	{
		if(is_document(target_document_in))
		{
			target_document = target_document_in;
		}
	}
	
	//Check node type
	switch(node_in.nodeType)
	{
		//ELEMENT_NODE
		case 1:
			
			//copy node
			return_result = target_document.createElement(node_in.nodeName);
			
			if(!return_result)
			{
				break;
			}
			
			//copy attributes of node
			for(var i=0; i<node_in.attributes.length; i++)
			{
				set_attribute_of_element(return_result, node_in.attributes[i].name, node_in.attributes[i].value);
			}
			
			break;
		
		//TEXT_NODE
		//CDATA_SECTION_NODE
		//COMMENT_NODE
		case 3:
		case 4:
    	case 8:
			
			//copy node
			return_result = target_document.createTextNode(node_in.nodeValue);
			
			break;
	}
	
	return return_result;
}


/*	Function:	import a node with attributes and all child nodes (if defined) and associates it with a target document.
*	Input:
*				target_document_in	- target document or null,	[OBJECT || NULL]
*				node_in				- imported a node,			[OBJECT]
*				deep_in				- import all child nodes:	[BOOLEAN]
*										-- true  - import all child nodes (by default),
*										-- false - import only node_in.
*	Output:
*				copy of a node with attributes and all child nodes (if defined) and associates it with the target document or null.	[OBJECT || NULL]
*	Note:
*
*				If target_document_in is not an object of class 'Document' or NULL then will be used current document.
*/
function jsDOM_import_node(target_document_in, node_in, deep_in)
{
	//* result	[OBJECT || NULL]
	var return_result = null;
	
	
	//Check functions
	if(typeof is_node != "function")
	{
		return return_result;
	}
	
	if(typeof object_attach != "function")
	{
		return return_result;
	}
	
	if(typeof check_attribute_of_element != "function")
	{
		return return_result;
	}
	
	if(typeof set_attribute_of_element != "function")
	{
		return return_result;
	}
	
	if(typeof jsDOM_import_one_node != "function")
	{
		return return_result;
	}
	
	//Check input arguments
	if(typeof node_in != "object")
	{
		return return_result;
	}
	
	if(!is_node(node_in))
	{
		return return_result;
	}
	
	//* import all child nodes	[BOOLEAN]
	var deep			= true;
	
	//* target document [OBJECT || NULL]
	var target_document	= null;
	
	
	if(typeof deep_in == "boolean")
	{
		deep = deep_in;
	}
	
	if(typeof target_document_in == "object")
	{
		target_document = target_document_in;
	}
	
	//* buffer (parent inported node)	[OBJECT || NULL]
	var p_imp_node = jsDOM_import_one_node(target_document, node_in);
	
	
	//Check node
	if(!is_node(p_imp_node))
	{
		return return_result;
	}
	
	//Init result
	return_result = p_imp_node;
	
	//Check variable 'deep'
	if(!deep)
	{
		//** import only one node
		return return_result;
	}
	
	//* buffer (firstChild by default)	[OBJECT]
	var buf_node			= node_in.firstChild;
	
	//* buffer (inported node)	[OBJECT || NULL]
	var imp_node			= null;
	
	//* use or not use 'nextSibling'	[BOOLEAN]
	//** true  - use 'nextSibling' (by default),
	//** false - not use 'nextSibling'.
	var fl_ns				= true;
	
	//* use or not use previous parent imported node for 'nextSibling'	[BOOLEAN]
	//** true  - use (by default),
	//** false - not use.
	var fl_p_imp_node_ns	= true;
	
	
	//Mark the start node
	set_attribute_of_element(node_in, "jsdom", "tmp");
	
	while(buf_node)
	{
		if(buf_node)
		{
			fl_ns = true;
			
			//import a node with all attributes
			imp_node = jsDOM_import_one_node(target_document, buf_node);
			
			if(!is_node(imp_node))
			{
				break;
			}
			
			//attach a node
			imp_node = object_attach(p_imp_node, imp_node, "end");
			
			if(!imp_node)
			{
				break;
			}
			
			//check child nodes of the buf_node
			if(buf_node.childNodes.length)
			{
				//get first child node
				buf_node = buf_node.firstChild;
				
				p_imp_node = imp_node;
				
				//off 'nextSibling'
				fl_ns = false;
			}
			
			//** sibling
			while(fl_ns)
			{
				//check a next node of the current level (next sibling node)
				//** if there is no next sibling node then return to the parent node of the current level (parsing of the current level of completed!)
				if(buf_node.nextSibling)
				{
					//get next sibling node
					buf_node = buf_node.nextSibling;
					
					if(!fl_p_imp_node_ns)
					{
						p_imp_node		 = p_imp_node.parentNode;
						fl_p_imp_node_ns = true;
					}
					
					//off 'nextSibling'
					fl_ns = false;
				}
				else
				{
					//get the parent node of the current level
					buf_node = buf_node.parentNode;
					
					p_imp_node		 = imp_node.parentNode;
					fl_p_imp_node_ns = false;
					
					//on 'nextSibling'
					fl_ns = true;
					
					//** if the parent node contains the attribute 'jsdom' then exit from function (end parsing!)
					if(check_attribute_of_element(buf_node, "jsdom", "tmp"))
					{
						//off 'nextSibling'
						fl_ns = false;
						
						//break parsing
						buf_node = null;
					}
				}
			}
		}
	}
	
	//Remove the attribute 'jsdom'
	set_attribute_of_element(node_in, "jsdom", null);
	
	return return_result;
	
}


/*	Функция:	поиск соответствия заданных параметров с параметрами узла дерева документа.
*	Вход:
*				node_in				- указатель на узел дерева документа;			[OBJECT]
*				re_node_name_in		- название искомого узла (строка регулярного	[STRING || NULL]
*										выражения, например, "td|TD") или null;
*				attr_name_in		- название атрибута (например, "class"			[STRING || NULL]
*										или null;
*				re_attr_value_in	- значение атрибута (строка регулярного			[STRING || NULL]
*										выражения, например, "button1|Button1").
*	Выход:
*				результат поиска:													[BOOLEAN]
*					- true	- если параметры node_in совпадают с заданными,
*					- false	- если параметры node_in не совпадают с заданными.
*	Описание:
*				Если не задан один из входных параметров, то возвращается false.
*
*				Поиск по атрибутам и их значениям осуществляется только для
*					элементных узлов (nodeType == 1, т.е. не текстовый,
*					не комментарий и т.п.) 
*/
function jsDOM_search_node(node_in, re_node_name_in, attr_name_in, re_attr_value_in)
{
	//Объявление переменных
	var return_result = false;	//[BOOLEAN]
	
	
	//Проверка существования функций search_sub_string(), check_attribute_of_element(), get_attribute_of_element()
	if(typeof search_sub_string == "function" && typeof check_attribute_of_element == "function" && typeof get_attribute_of_element == "function")
	{
		//проверка существования функции is_node()
		if(typeof is_node == "function")
		{
			//проверка параметра node_in
			if(is_node(node_in))
			{
				//признак результата поиска по re_node_name_in	[BOOLEAN]
				var f_node_name = false;
				
				//признак результата поиска по attr_name_in		[BOOLEAN]
				var f_attr_name = false;

				
				//проверка параметра node_name_in
				if(typeof re_node_name_in == "string")
				{
					//если node_in.nodeName == re_node_name_in, то f_node_name = true
					//(т.е. параметр узла совпадает с одним из заданных) 
					if(search_sub_string(re_node_name_in, node_in.nodeName))
					{
						f_node_name = true;
						
						//Debug ---
						//if(typeof debug_console == "object" && typeof widget_debug_console_insert_new_text_line == "function")
						//{
						//	widget_debug_console_insert_new_text_line(debug_console, "jsDOM: search, nodeName ok");
						//}
						//--- Debug
					}
				}
				
				//проверка параметра attr_name_in и типа узла объекта node_in 
				if(typeof attr_name_in == "string" && node_in.nodeType == 1)
				{
					//если был задан параметр re_node_name_in и его проверка
					//прошла удачно или если он не был задан, то продолжаем
					//проверку на совпадение параметров
					if((typeof re_node_name_in == "string" && f_node_name) || typeof re_node_name_in != "string")
					{
						//Debug ---
						//if(typeof debug_console == "object" && typeof widget_debug_console_insert_new_text_line == "function")
						//{
						//	widget_debug_console_insert_new_text_line(debug_console, "jsDOM: search, attr or value start");
						//}
						//--- Debug
						
						//проверка параметра re_attr_value_in
						if(typeof re_attr_value_in == "string")
						{
							if(check_attribute_of_element(node_in, attr_name_in, re_attr_value_in))
							{
								f_attr_name = true;
								
								//Debug ---
								//if(typeof debug_console == "object" && typeof widget_debug_console_insert_new_text_line == "function")
								//{
								//	widget_debug_console_insert_new_text_line(debug_console, "jsDOM: search, attr and value ok");
								//}
								//--- Debug
							}
						}
						else
						{
							//получение значения атрибута attr_name_in узла node_in			[STRING || NULL]
							var attr_value = get_attribute_of_element(node_in, attr_name_in);

							
							//проверка полученного значения 
							if(typeof attr_value == "string") 
							{
								f_attr_name = true;
								
								//Debug ---
								//if(typeof debug_console == "object" && typeof widget_debug_console_insert_new_text_line == "function")
								//{
								//	widget_debug_console_insert_new_text_line(debug_console, "jsDOM: search, attr ok");
								//}
								//--- Debug
							}
						}
					}
				}
				else
				{
					//если поиск только по nodeName объекта
					f_attr_name = true;
				}
				
				//формирование результата совпадения параметров
				if(f_node_name && f_attr_name)
				{
					return_result = true;
				}
			}
		}
	}
	
	return return_result;
}


/*	Функция:	разбор дерева документа (парсинг).
*	Вход:
*				root_node_in		- указатель на узел дерева документа,			[OBJECT]
*										с которого нужно начинать поиск;
*				re_node_name_in		- название искомого узла (строка регулярного	[STRING || NULL]
*										выражения, например, "td|TD") или null;
*				attr_name_in		- название атрибута (например, "class"			[STRING || NULL]
*										или null;
*				re_attr_value_in	- значение атрибута (строка регулярного			[STRING || NULL]
*										выражения, например, "button1|Button1")
*										или null.
*	Выход:
*				массив указателей на узлы дерева документа или пустой массив.		[ARRAY]
*	Описание:
*				Если не задан параметр root_node_in (равен null или не объект узла дерева документа), то возвращается пустой массив
*				(обход дерева документа не производится).
*
*				Другие входные атрибуты функции (re_node_name_in, attr_name_in, re_attr_value_in) являются необязательными (дополнительными)
*				и используются для конкретизации (фильтрации) поиска объектов дерева документа.
*
*				Если дополнительные атрибуты не заданы, то возвращается массив из всех объектов, входящих в root_node_in.
*/
function jsDOM_parsing(root_node_in, re_node_name_in, attr_name_in, re_attr_value_in)
{
	//Объявление переменных
	
	//* возвращаемое значение	[ARRAY]
	var return_array_nodes = new Array();
	
	
	//Проверка существования функции is_node()
	if(typeof is_node != "function")
	{
		return return_array_nodes;
	}
	
	//Проверка существования функции jsDOM_search_node()
	if(typeof jsDOM_search_node != "function")
	{
		return return_array_nodes;
	}
	
	//Проверка входных атрибутов
	if(typeof root_node_in != "object")
	{
		return return_array_nodes;
	}
	
	if(!is_node(root_node_in))
	{
		return return_array_nodes;
	}
	
	//* указатель на первый дочерний объект			[OBJECT]
	var buf_node	= root_node_in.firstChild;
	
	//* признак необходимости получения				[BOOLEAN]
	//* следующего родственного объекта ("сиблинг")
	//** true - получить следующий родственный элемент (той же вложенности, что и исходный, по-умолчанию),
	//** false - не получать.
	var fl_ns		= true;
	
	//* признак соответствия параметров объекта		[BOOLEAN]
	//* параметрам поиска (по-умолчанию, соответствует)
	var fl_fit		= true;
	
	
	//Разбор дерева документа, начиная с первого объекта root_node_in
	while(buf_node)
	{
		if(buf_node)
		{
			//установка признаков (по-умолчанию)
			fl_ns	= true;
			fl_fit	= true;
			
			//проверка входных атрибутов - дополнительных параметров поиска
			if(typeof re_node_name_in == "string" || typeof attr_name_in == "string")
			{
				//проверка соответствия параметров
				fl_fit = jsDOM_search_node(buf_node, re_node_name_in, attr_name_in, re_attr_value_in);
			}
			
			//** если соответствует, то указатель на объект добавляется в выходной массив
			if(fl_fit)
			{
				return_array_nodes.push(buf_node);
			}
			
			//проверка - имеется ли у объекта buf_node дочерние объекты
			if(buf_node.childNodes.length)
			{
				//получение указателя на первый дочерний объект
				buf_node = buf_node.firstChild;
				
				//"сиблинг" не нужен (переход на следующий цикл)
				fl_ns = false;
			}
			
			//"сиблинг" - получение следующего родственного элемента того же уровня
			while(fl_ns)
			{
				//проверка - имеется ли указатель на следующий объект
				//** если следующего объекта нет, то переход обратно - на уровень выше;
				//** если был переход на уровень выше, то продолжается цикл "сиблинг".
				if(buf_node.nextSibling)
				{
					//получение указателя на следующий объект
					buf_node = buf_node.nextSibling;
					
					//прерываем цикл "сиблинг"
					fl_ns = false;
				}
				else
				{
					//получение указателя на родительский объекта
					//** переход на уровень выше, т.к. на этом уровне уже нет объектов
					buf_node = buf_node.parentNode;
					
					//продолжение "сиблинга", т.к. начинали с этого же
					//родительского объекта, а на следующем цикле
					//"сиблинга" получаем указатель на следующий
					//элемент - на уровне с родительским объектом,
					//с которого спустились.
					fl_ns = true;
					
					//** если родительский объект - "верхний предел", то прекращаем парсинг документа
					if(buf_node == root_node_in)
					{
						//прерывание цикла "сиблинга"
						fl_ns = false;
						
						//обнуление buf_node (прерываем цикл парсинга)
						buf_node = null;
					}
				}
			}
		}
	}
	
	return return_array_nodes;
}


/*	Функция:	получение указателя на объект с заданными параметрами.
*	Вход:
*				root_node_in		- указатель на узел дерева документа,			[OBJECT]
*										с которого нужно начинать поиск;
*				re_node_name_in		- название искомого узла (строка регулярного	[STRING || NULL]
*										выражения, например, "td|TD") или null;
*				attr_name_in		- название атрибута (например, "class"			[STRING || NULL]
*										или null;
*				re_attr_value_in	- значение атрибута (строка регулярного			[STRING || NULL]
*										выражения, например, "button1|Button1").
*	Выход:
*				указатель на объект или null.	[OBJECT || NULL]
*	Описание:
*				Если не задан один из входных параметров, то возвращается null.
*/
function jsDOM_get_object(root_node_in, re_node_name_in, attr_name_in, re_attr_value_in)
{
	//Объявление переменных
	var return_object = null;   //[OBJECT]
	
	
	//проверка наличия функции jsDOM_parsing()
	if(typeof jsDOM_parsing == "function")
	{
		//получение массива искомых элементов 
		var array_nodes = jsDOM_parsing(root_node_in, re_node_name_in, attr_name_in, re_attr_value_in);
		
		
		//проверка полученного массива
		if(array_nodes)
		{
			if(array_nodes.length)
			{
				//инициализация указателя на объект
				return_object = array_nodes[0]; 
			}
		}
	}
	
	return return_object;
}


/*	Функция:	установка визуального состояния объекта (объектов).
*	Вход:
*				root_node_in	- указатель на корневой объект (узел),					[OBJECT]
*				re_objs_in		- список имен объектов (строка регулярного выражения),	[STRING]
* 				visual_state_in	- визуальное состояние:									[STRING]
* 									-- "visible" (by default),
* 									-- "hidden".
* 
*	Выход:
*				результат:	[INTEGER]
*					- -1	- ошибка,
*					- > -1	- кол-во обработанных узлов.
* 
*	Описание:
* 
*			Если не заданы входной параметр root_node_in, то выход из функции (ошибка!).
*
*			Если список объектов не задан или объекты не найдены, то выход.
* 
* 			Имена объектов - это название узла или значение одного из ключевых атрибутов: "id", "name", "class"!
*
*			Список имен объектов задается следующим образом: "^table$|^button_edit$|^checkbox1$|^button_filtr$".
* 
*/
function jsDOM_set_visual_state(root_node_in, re_objs_in, visual_state_in)
{
	//** результат	[INTEGER]
	var return_result = -1;
	
	
	//Проверка функций search_sub_string()
	if(typeof search_sub_string != "function")
	{
		return return_result;
	}
	
	//Проверка функции get_attribute_of_element()
	if(typeof get_attribute_of_element != "function")
	{
		return return_result;
	}
	
	//Проверка функций object_show()
	if(typeof object_show != "function")
	{
		return return_result;
	}
	
	//Проверка функций object_hide()
	if(typeof object_hide != "function")
	{
		return return_result;
	}
	
	//Проверка функций jsDOM_parsing()
	if(typeof jsDOM_parsing != "function")
	{
		return return_result;
	}
	
	//Проверка входного параметра
	if(typeof root_node_in != "object")
	{
		return return_result;
	}
	
	//* массив названий поддерживаемых атрибутов	[ARRAY]
	var array_attr		= new Array("nodeName", "id", "name", "class");
	
	//* список ключевых имен объектов								[ARRAY || NULL]
	var re_list_names	= ((typeof re_objs_in == "string") ? re_objs_in : null);
	
	//* визуальное состояние						[STRING]
	var visual_state	= "visible";
	
	//* массив указателе на объекты контейнера		[ARRAY || NULL]
	var array_objs		= jsDOM_parsing(root_node_in, null, null, null);
	
	//* значение ключевого атрибута					[STRING || NULL]
	var attr			= null;
	
	//* счетчики									[INTEGER]
	var i				= 0;
	var j				= 0;
	
	
	if(typeof visual_state_in == "string")
	{
		if(visual_state_in == "hidden")
		{
			visual_state = visual_state_in;
		}
	}
	
	return_result = 0;
	
	for(i=0; i<array_objs.length; i++)
	{
		//проверка типа объекта (только узлы DOM!)
		if(array_objs[i].nodeType != 1)
		{
			continue;
		}
		
		for(j=0; j<array_attr.length; j++)
		{
			if(array_attr == "nodeName")
			{
				//** имя узла
				attr = array_objs[i].nodeName;
			}
			else
			{
				//** имя ключевого атрибута
				attr = get_attribute_of_element(array_objs[i], array_attr[j]);
			}
			
			//сверка значения ключевого атрибута со списком исходных значений
			if(search_sub_string(re_list_names, attr))
			{
				switch(visual_state)
				{
					case "hidden":
						
						//скрытие объекта
						object_hide(array_objs[i]);
						
						break;
						
					default:
						
						//отображение объекта
						object_show(array_objs[i]);
						
						break;
				}
				
				return_result++;
			}
		}
	}
	
	return return_result;
}


//ОПИСАНИЕ МЕТОДОВ В ПРОТОТИПЕ


//НАСЛЕДОВАНИЕ


//ИНИЦИАЛИЗАЦИЯ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ

