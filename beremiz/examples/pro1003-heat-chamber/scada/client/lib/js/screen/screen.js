//JAVASCRIPT DOCUMENT


/*   Библиотека: функции для работы с параметрами экрана, размерами
*					и положением объектов
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


/*	Версия 1.0.4:
*		- добавлена фунция get_object_height();
*		- добавлена фунция get_object_width().
*
*	Версия 1.0.3:
*		- добавлена функция object_hide();
*		- добавлена функция object_show();
*		- добавлена функция get_object_visible();
*		- добавлена функция set_object_height().
*
*	Версия 1.0.2:
*		- добавлена функция set_real_object_position(obj_in, position_in)
*		  * позиционирование только в центре экрана (center).
*
*	Версия 1.0.1:
*		- в функции get_real_object_position(obj_in) добавлена обработка
*		  свойства currentStyle и проверка возвращаемого значения
*		  функции parseInt(). (функция не работала в IE).
*/


/*	Глобальные переменные:	Нет.
*
*	Описание функций:
*		*** получение размера экрана/рабочей области в пикселах ***
*		get_screen_size()
*
*		*** получение координат объекта в пикселах ***
*		get_real_object_coords(obj_in)
*
*		*** получение позиции объекта в пикселах ***
*		get_real_object_position(obj_in)
*
*		*** получение координат указателя манипулятора (через объект события) в пикселах ***
*		get_mouse_coords_about_event(ev)
*
*		*** получение смещения указателя манипулятора относительно цели события
*			(через объекта события) в пикселах ***
*		get_mouse_offset_about_target(target, ev)
*
*		*** позиционирование объекта в пределах рабочей области экрана *** 
*		set_real_object_position(obj_in, position_in)
*
*		*** скрытие объекта ***
*		object_hide(obj_in)
*
*		*** отображение объекта ***
*		object_show(obj_in)
*
*		*** проверка визуального состояния объекта ***
*		get_object_visible(obj_in)
*
*		*** установка высоты объекта в пиксела или % ***
*		set_object_height(box_in, height_in)
*
*	Описание классов: Нет.
*
*	Описание методов в прототипе: Нет.
*
*	Наследование: Нет.
*
*	Инициализация глобальных переменных: Нет.
*/


/*	Зависимости:
*		regexp.js:
*			- search_sub_string().
*/


//ГЛОБАЛЬНЫЕ ПЕРЕМЕННЫЕ


//ОПИСАНИЕ ФУНКЦИЙ

/*	Функция:	Получение размера экрана/рабочей области в пикселах.
*	Вход:		Нет.
*	Выход:
*				Объект со свойствами:	[OBJECT]
*					w - ширина,			[NUMBER]
*					h - высота.			[NUMBER]
*/
function get_screen_size()
{
	//Объявление переменных
	
	//Ширина	[NUMBER]
	var w = 0;
	
	//Высота	[NUMBER]
	var h  = 0;

	
	//Получение значений ширины и высоты рабочей области в пикселах
	w = (window.innerWidth ? window.innerWidth : (document.documentElement.clientWidth ? document.documentElement.clientWidth : document.body.offsetWidth));
	h = (window.innerHeight ? window.innerHeight : (document.documentElement.clientHeight ? document.documentElement.clientHeight : document.body.offsetHeight));
	
	return {w:w, h:h};
}


/*	Функция:	Получение координат объекта в пикселах.
*	Вход:
*				obj_in - указатель на объект.	[OBJECT]
*	Выход:
*				Объект со свойствами:	[OBJECT]
*					x - координата X верхнего левого угла,	[NUMBER]
*					y - координата Y верхнего левого угла.	[NUMBER]
*/
function get_real_object_coords(obj_in)
{
	//Объявление переменных
	
	//Координата X верхнего левого угла	[NUMBER]
	var x = 0;
	
	//Координата Y верхнего левого угла	[NUMBER]
	var y = 0;

	
	//Проверка входных параметров
	if(typeof obj_in == "object")
	{
		//* т.к. typeof null == "object" 
		if(obj_in)
		{
			//определение координат объекта в пикселах
			y = obj_in.offsetHeight;
		
			while(obj_in)
			{
				x += obj_in.offsetLeft;
				y += obj_in.offsetTop;
				obj_in = obj_in.offsetParent;
			}
		}
	}
	
	return {x:x, y:y};
}


/*	Функция: 	Получение позиции объекта в пикселах.
*	Вход:
*				obj_in - указатель на объект.	[OBJECT]
*	Выход:
*				Объект со свойствами:	[OBJECT]
*					x - координата X верхнего левого угла,	[NUMBER]
*					y - координата Y верхнего левого угла.	[NUMBER]
*/
function get_real_object_position(obj_in)
{
	//Объявление переменных
	
	//Расстояние от левого края броузера до объекта	[NUMBER]
	var left = 0;
	
	//Расстояние от верхнего края броузера до объкта	[NUMBER]
	var top = 0;
	
	
	//Проверка входных параметров
	if(typeof obj_in == "object")
	{
		//* т.к. typeof null == "object" 
		if(obj_in)
		{
			//определение смещения объекта
			while(obj_in.offsetParent)
			{
				//определение смещения слева
				left += obj_in.offsetLeft;
				
				//определение смещения сверху
				top += obj_in.offsetTop;
			
				if(obj_in.currentStyle)
				{
					if(!isNaN(parseInt(obj_in.currentStyle.borderLeftWidth)))
					{
						left += parseInt(obj_in.currentStyle.borderLeftWidth);
					}
					
					if(!isNaN(parseInt(obj_in.currentStyle.borderTopWidth)))
					{
						top += parseInt(obj_in.currentStyle.borderTopWidth);
					} 
				}				
				
				//получение объекта-родителя от объкта obj_in		
				obj_in = obj_in.offsetParent;
			}
			
			//определение смещения слева
			left += obj_in.offsetLeft;
			
			//определение смещения сверху
			top += obj_in.offsetTop;
			
			//проверка параметров смещения, заданных через атрибут "style"
			if(obj_in.currentStyle)
			{
				if(!isNaN(parseInt(obj_in.currentStyle.borderLeftWidth)))
				{
					left += parseInt(obj_in.currentStyle.borderLeftWidth);
				}
				
				if(!isNaN(parseInt(obj_in.currentStyle.borderTopWidth)))
				{
					top += parseInt(obj_in.currentStyle.borderTopWidth);
				} 
			}
		}
	}
	
	return {x:left, y:top};
}


/*	Функция: 	Получение координат указателя манипулятора.
*					(через объекта события) в пикселах.
*	Вход:
*			    ev_in - объект события.	[OBJECT]
*	Выход:
*				Объект со свойствами:	[OBJECT]
*					x - координата X верхнего левого угла,	[NUMBER]
*					y - координата Y верхнего левого угла.	[NUMBER]
*/
function get_mouse_coords_about_event(ev_in)
{
	//Объявление переменных
	
	//Координата X указателя манипулятора	[NUMBER]
	var x_out = 0;
	
	//Координата Y указателя манипулятора	[NUMBER]
	var y_out = 0;
	
	
	//Проверка входных параметров
	if(typeof ev_in == "object")
	{
		//* т.к. typeof null == "object" 
		if(ev_in)
		{
			//получение координат указателя манипулятора
			if(ev_in.pageX || ev_in.pageY)
			{
				x_out = ev_in.pageX;
				y_out = ev_in.pageY;
			}
			else
			{
				x_out = ev_in.clientX + document.body.scrollLeft - document.body.clientLeft;
				y_out = ev_in.clientY + document.body.scrollTop - document.body.clientTop;
			}
		}
	}
	
	return {x:x_out, y:y_out};
}


/*	Функция:  	Получение смещения указателя манипулятора относительно
*					цели события 	(через объекта события) в пикселах.
*	Вход:
*				target_in	- цель события,		[OBJECT]
*			    ev_in		- объект события.	[OBJECT]
*	Выход:
*				объект со свойствами:	[OBJECT]
*					x - координата X верхнего левого угла,	[NUMBER]
*					y - координата Y верхнего левого угла.	[NUMBER]
*/
function get_mouse_offset_about_target(target_in, ev_in)
{
	//Объявление переменных
	
	//Координата X указателя манипулятора	[NUMBER]
	var x_out = 0;
	
	//Координата Y указателя манипулятора	[NUMBER]
	var y_out = 0;
	

	//Проверка входных параметров
	if(typeof target_in == "object" && typeof ev_in == "object")
	{
		//* т.к. typeof null == "object" 
		if(target_in && ev_in)
		{
			//проверка существования функции get_real_object_position()
			if(typeof get_real_object_position == "function")
			{
				//проверка существования функции get_mouse_coords_about_event()
				if(typeof get_mouse_coords_about_event == "function")
				{
					//получение смещения курсора манипулятора относительно объекта события	[OBJECT]
					var mouse_pos = get_mouse_coords_about_event(ev_in);
					
					//получение позиции объекта [OBJECT]
					var target_pos  = get_real_object_position(target_in);
					
					
					//проверка параметров
					if(mouse_pos && target_pos)
					{
						x_out = mouse_pos.x - target_pos.x;
						y_out = mouse_pos.y - target_pos.y;
					}
				}
			}
		}
	}

	return {x:x_out, y:y_out};
}


/*	Функция: 	Позиционирование объекта в пределах рабочей области экрана.
*	Вход:
*				obj_in		- указатель на объект;	[OBJECT]
*				position_in	- позиция объекта:		[STRING]
*								"center" - по центру экрана.
*	Выход:
*				объект со свойствами:	[OBJECT]
*					x - координата X верхнего левого угла,	[NUMBER]
*					y - координата Y верхнего левого угла.	[NUMBER]
*/
function set_real_object_position(obj_in, position_in)
{
	//Проверка входных параметров
	if(typeof obj_in == "object" && typeof position_in == "string")
	{
		//* т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования функций search_sub_string(), get_screen_size()
			if(typeof search_sub_string == "function" && typeof get_screen_size == "function")
			{
				//проверка позиций объекта
				if(search_sub_string("center", position_in))
				{
					//получение размера рабочей области экрана		[OBJECT]
					var screen_size = get_screen_size();
					
					
					//проверка существования у объекта screen_size свойства h и w
					if(typeof screen_size.h == "number" && typeof screen_size.w == "number")
					{
						switch(position_in)
						{
							//если позиционирование "По центру экрана"
							case "center":
								
 								//проверка существования у объекта obj_in свойств offsetHeight и offsetWidth
 								if(typeof obj_in.offsetHeight == "number" && typeof obj_in.offsetWidth == "number")
 								{
									obj_in.style.left = (screen_size.w - obj_in.offsetWidth)/2;
									obj_in.style.top = (screen_size.h - obj_in.offsetHeight)/2;
								}
								
								break;
						}
					}
				}
			}
		}
	}
}


/*	Функция:	Скрыть объект.
*	Вход:
*				obj_in - указатель на объект.	[OBJECT]
*	Выход:		Нет.
*	Описание:
*				Если не задан один из входных параметров, то
*					объект не скрывается.
*/
function object_hide(obj_in)
{
	//Проверка входных параметров
	if(typeof obj_in == "object")
	{
		//* т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования у объекта obj_in свойства style
			if(typeof obj_in.style == "object")
			{
				//скрытие объекта
				obj_in.style.display = "none";
			}
		}
	}
}


/*	Функция:	Отобразить объект.
*	Вход:
*				obj_in - указатель на объект.	[OBJECT]
*	Выход:		Нет.
*	Описание:
*				Если не задан один из входных параметров, то
*					объект не отображается.
*/
function object_show(obj_in)
{
	//Проверка входных параметров
	if(typeof obj_in == "object")
	{
		//* т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования у объекта obj_in свойства style
			if(typeof obj_in.style == "object")
			{
				//отображение объекта
				obj_in.style.display = "block";
			}
		}
	}
}


/*	Функция:	Проверка визуального состояния объекта.
*	Вход:
*				obj_in - указатель на объект.		[OBJECT]
*	Выход:
*				true - объект видим на экране,		[BOOLEAN]
*				false - объект не видим на экране	[BOOLEAN]	
*						или не доступен/определен.
*	Описание:
*				Если не задан один из входных параметров, то
*					возвращается false.
*/
function get_object_visible(obj_in)
{
	//Проверка входных параметров
	if(typeof obj_in == "object")
	{
		//* т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования у объекта obj_in свойства style
			if(typeof obj_in.style == "object")
			{
				//проверка визуального состояния объекта
				if(obj_in.style.display != "none")
				{
					return true;
				}
			}
		}
	}
	
	return false;
}


/*	Функция:	Установка высоты объекта в пикселах или %.
*	Вход:
*				obj_in		- указатель на объект.				[OBJECT]
*				height_in	- значение высоты в пикселах или %	[STRING || NUMBER]
*								(число или строка вида "450",
*								"450px", "90%").
*	Выход:
*				Высота контейнера в пикселах.	[NUMBER]
*	Описание:
*				Если не задан один из входных параметров, то
*					возвращается 0.
*/
function set_object_height(obj_in, height_in)
{
	//Объявление переменных
	var return_height = 0;   //[NUMBER]
	
	
	//Проверка входных параметров
	if(typeof obj_in == "object" && typeof height_in != "undefined")
	{
		//т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования у объекта obj_in свойства style, offsetHeight
			if(typeof obj_in.style == "object" && typeof obj_in.offsetHeight == "number")
			{
				//получение объекта style	[OBJECT]
				var obj_style = obj_in.style;
				

				//проверка существования у объекта obj_style свойства height
				if(typeof obj_style.height == "string")
				{
					//если значение параметра height_in целочисленное
					//(typeof height == "number"), то устанавливаем
					//высоту сразу же
					if(typeof height_in == "number")
					{
						obj_style.height = height_in;
					}
					else
					{
						//если значение параметра height_in строковое
						//(typeof height == "string"), то проверяем
						//формат строки ("450", 450px", "90%")
						if(typeof height_in == "string")
						{
							//проверка наличия функции search_sub_string()
							if(typeof search_sub_string == "function")
							{
								//сравнение строкового значения с шаблоном
								if(search_sub_string("(^[0-9]*)(px|%)?$", height_in))
								{
									obj_style.height = height_in;
								}
							}
						}
					}
				}
				
				//получение высоты контейнера в пикселах
				return_height = obj_in.offsetHeight-0;
			}
		}
	}
	
	return return_height;
}


/*	Функция:	Получение высоты объекта в пикселах.
*	Вход:
*				obj_in - указатель на объект.	[OBJECT]
*	Выход:
*				Высота контейнера в пикселах.	[NUMBER]
*	Описание:
*				Если не задан один из входных параметров, то
*					возвращается 0.
*/
function get_object_height(obj_in)
{
	//Проверка входных параметров
	if(typeof obj_in == "object")
	{
		//т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования у объекта obj_in свойства offsetHeight
			if(typeof obj_in.offsetHeight == "number")
			{
				return obj_in.offsetHeight;
			}
		}
	}
	
	return 0;
}


/*	Функция:	Установка ширины объекта в пикселах или %.
*	Вход:
*				obj_in		- указатель на объект.				[OBJECT]
*				height_in	- значение ширины в пикселах или %	[STRING || NUMBER]
*								(число или строка вида "450",
*								"450px", "90%").
*	Выход:
*				Ширина контейнера в пикселах.	[NUMBER]
*	Описание:
*				Если не задан один из входных параметров, то
*					возвращается 0.
*/
function set_object_width(obj_in, width_in)
{
	//Объявление переменных
	var return_width = 0;   //[NUMBER]
	
	
	//Проверка входных параметров
	if(typeof obj_in == "object" && typeof width_in != "undefined")
	{
		//т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования у объекта obj_in свойства style, offsetWidth
			if(typeof obj_in.style == "object" && typeof obj_in.offsetWidth == "number")
			{
				//получение объекта style	[OBJECT]
				var obj_style = obj_in.style;
				

				//проверка существования у объекта obj_style свойства width
				if(typeof obj_style.width == "string")
				{
					//если значение параметра width_in целочисленное
					//(typeof width == "number"), то устанавливаем
					//ширину сразу же
					if(typeof width_in == "number")
					{
						obj_style.width = width_in;
					}
					else
					{
						//если значение параметра width_in строковое
						//(typeof width == "string"), то проверяем
						//формат строки ("450", 450px", "90%")
						if(typeof width_in == "string")
						{
							//проверка наличия функции search_sub_string()
							if(typeof search_sub_string == "function")
							{
								//сравнение строкового значения с шаблоном
								if(search_sub_string("(^[0-9]*)(px|%)?$", width_in))
								{
									obj_style.width = width_in;
								}
							}
						}
					}
				}
				
				//получение высоты контейнера в пикселах
				return_width = obj_in.offsetWidth-0;
			}
		}
	}
	
	return return_width;
}


/*	Функция:	Получение ширины объекта в пикселах.
*	Вход:
*				obj_in - указатель на объект.	[OBJECT]
*	Выход:
*				Ширина контейнера в пикселах.	[NUMBER]
*	Описание:
*				Если не задан один из входных параметров, то
*					возвращается 0.
*/
function get_object_width(obj_in)
{
	//Проверка входных параметров
	if(typeof obj_in == "object")
	{
		//т.к. typeof null == "object" (obj_in)
		if(obj_in)
		{
			//проверка существования у объекта obj_in свойства offsetWidth
			if(typeof obj_in.offsetWidth == "number")
			{
				return obj_in.offsetWidth;
			}
		}
	}
	
	return 0;
}


//ОПИСАНИЕ КЛАССОВ


//ОПИСАНИЕ МЕТОДОВ В ПРОТОТИПЕ


//НАСЛЕДОВАНИЕ


//ИНИЦИАЛИЗАЦИЯ ГЛОБАЛЬНЫХ ПЕРЕМЕННЫХ


