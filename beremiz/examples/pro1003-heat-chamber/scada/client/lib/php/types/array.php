<?php

//PHP SCRIPT DOCUMENT


/*   Библиотека: работа с массивами.
*
*    Copyright (C) 2010  ATgroup09 (atgroup09@gmail.com)
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


/*	Версия 1.0.1:
*/


/*	Глобальные переменные: нет.
*
*	Описание функций:
*		*** получение массива из заданных значений ***
*		get_type_array($params_in)
*
*	Описание классов: нет.
*/


/*	Зависимости:
*		- глобальные переменные: нет.
*
*		- библиотеки функций: нет.
*/


//ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ


//ОПИСАНИЕ ФУНКЦИЙ

/*	Функция:	Получение массива из заданных значений.
*	Вход:
*				$params_in - значение или массив значений.	[ANY TYPES]
*	Выход:
*				Массив из заданных значений.				[ARRAY]
*	Описание:
*				Если $params_in - массив, то он же и возвращается.
*				Если $params_in - переменная (не массив), то добавляется в выходной массив.
*
*				Если входной параметр не задан (null), то возвращается пустой массив.
*/
function get_type_array($params_in)
{
	//Объявление переменных
	
	//* массив строк дополнительных параметров	[ARRAY]
	$return_array = array();
	
	
	//Проверка входного параметра
	if(is_array($params_in))
	{
		//инициализация выходного параметра
		$return_array = $params_in;
	}
	else
	{
		//проверка на пустое значение
		if(!empty($params_in))
		{
			//формирование выходного параметра
			array_push($return_array, $params_in);
		}
	}
	
	return $return_array;
}


//ОПИСАНИЕ КЛАССОВ


//ОПИСАНИЕ ФУНКЦИЙ


?>
