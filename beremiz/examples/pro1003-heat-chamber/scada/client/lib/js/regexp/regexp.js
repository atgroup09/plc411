//JAVASCRIPT DOCUMENT


/*   Библиотека: функции для работы с регулярными выражениями
*
*    Copyright (C) 2010  ATgroup09 (atgroup09@gmail.com)
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


/*	Версия 1.0.0
*
*/


/*	Глобальные переменные: нет.
*
*	Описание функций:
*		*** поиск подстроки в пределах исходной строки (по заданному шаблону) ***
*		search_sub_string(re_string, src_string)
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
*
*/


//ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ


//ОПИСАНИЕ ФУНКЦИЙ

/*	ФУНКЦИЯ:	Поиск подстроки в пределах исходной строки
*					(по заданному шаблону).
*	ВХОД:
*				re_string_in	- шаблон подстроки (регулярное выражение),	[STRING]
*				src_string_in	- исходная строка.							[STRING]
*	ВЫХОД:
*				Результат поиска подстроки:	[BOOLEAN]
*				 - true  - если подстрока найдена,
*				 - false - если подстрока не найдена.
*/
function search_sub_string(re_string_in, src_string_in)
{
	//Проверка входных параметров
	if(typeof re_string_in == "string" && typeof src_string_in == "string")
	{
		//поиск подстроки в исходной строке
		return RegExp(re_string_in).test(src_string_in);
	}
	
	return false;
}


/*	ФУНКЦИЯ:	Замена подстроки в пределах исходной строки
*					(по заданному шаблону).
*	ВХОД:
*				re_string_in		- шаблон подстроки (регулярное выражение),	[STRING]
*				src_string_in		- исходная строка,							[STRING]
*				new_substring_in	- новое значение подстроки.					[STRING]
*	ВЫХОД:
*				Новая строка или src_string_in.	[STRING || NULL]
*/
function replace_sub_string(re_string_in, src_string_in, new_substring_in)
{
	//Проверка существования функции search_sub_string()
	if(typeof search_sub_string != "function")
	{
		return src_string_in;
	}
	
	//Проверка входных параметров
	if(typeof new_substring_in == "string")
	{
		//поиск подстроки в исходной строке
		if(search_sub_string(re_string_in, src_string_in))
		{
			//* объект регулярного выражения	[OBJECT]
			var rx = new RegExp(re_string_in);
			
			
			//замена подстроки в пределах исходной строки
			return src_string_in.replace(rx, new_substring_in);
		}
	}
	
	return src_string_in;
}


//ОПИСАНИЕ КЛАССОВ


//ОПИСАНИЕ МЕТОДОВ В ПРОТОТИПЕ


//НАСЛЕДОВАНИЕ


//ИНИЦИАЛИЗАЦИЯ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ

