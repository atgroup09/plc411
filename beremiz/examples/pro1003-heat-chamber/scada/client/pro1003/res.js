/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  pro1003
*   webSCADA client / text resources
*   AT09 (atgroup09@gmail.com), 2023
*
*   The JavaScript code in this page is free software: you can
*   redistribute it and/or modify it under the terms of the GNU
*   General Public License (GNU GPL) as published by the Free Software
*   Foundation, either version 3 of the License, or (at your option)
*   any later version.  The code is distributed WITHOUT ANY WARRANTY;
*   without even the implied warranty of MERCHANTABILITY or FITNESS
*   FOR A PARTICULAR PURPOSE.  See the GNU GPL for more details.
*
*   As additional permission under GNU GPL version 3 section 7, you
*   may distribute non-source (e.g., minimized or compacted) forms of
*   that code without the copy of the GNU GPL normally required by
*   section 4, provided you include this license notice and a URL
*   through which recipients can access the Corresponding Source.
*/

//** GLOBAL VARIABLES

var G_RES = { ru: {      SrvConnErr: "Ошибка! Нет подключения к серверу {0}!",
						  NoDataErr: "Ошибка! Нет данных длительное время! Проверьте связь с сервером {0}.",
				    WsNotSupportErr: "Ошибка! Ваш браузер не поддерживает работу с web-сокетами!",
							Connect: "подключиться",
			             Disconnect: "отключиться",
			              WebSocket: "WebSocket",
						   WatchDog: "WatchDog",
						  Connected: "соединение установлено",
					   Disconnected: "соединение сброшено",
					  AutoReconnect: "попытка восстановления соединения...",
					     ConnStates: ["подключение...", "подключено", "отключение...", "отключено", "отключено"],
					           None: "---",
						      HS001: "HS-001",
					          HS002: "HS-002",
					           H001: "H-001",
						       C001: "C-001",
						     SET_ID: "ID",
						         SP: "SP",
						          D: "D",
						        DHI: "DHi",
						        THI: "THi",
						        DLO: "DLo",
						        TLO: "TLo",
						         TB: "Tb",
					          STATE: "КОНТУР УПРАВЛЕНИЯ",
					     HS001_List: {0:"СТОП", 1:"ПУСК"},
						 HS002_List: {0:"без продувки", 1:"с продувкой"},
					     OffOn_List: {0:"ВЫКЛ", 1:"ВКЛ"},
						 STATE_List: {0:"ВЫКЛ", 1:"ПРОДУВКА", 2:"РАБОТА", 3:"ОБРЫВ КОНТУРА УПРАВЛЕНИЯ", 4:"ЗАКЛИНИВАНИЕ КОНТУРА УПРАВЛЕНИЯ"},
					STATE_ListShort: {0:"ВЫКЛ", 1:"ПРОДУВКА", 2:"РАБОТА", 3:"ОБРЫВ", 4:"ЗАКЛИНИВАНИЕ"},
					STATE_ListColor: {0:null, 1:"blue", 2:"green", 3:"red", 4:"red"}
				  }
			};
