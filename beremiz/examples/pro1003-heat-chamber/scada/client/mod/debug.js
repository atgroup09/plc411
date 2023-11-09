/*	JAVASCRIPT DOCUMENT
*
*
*	TEXT CODING - UTF-8
*
*	BEST VIEWED WITH A:
*		- tabulation  - 4,
*		- font family - monospace 10.
*/


/*   Module: debug-functions.
*
*    Copyright (C) 2018  ATgroup09 (atgroup09@gmail.com)
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


/*	Depending on the:
*
*		- global variables: none.
*
*
*		- libraries:
*
*
*
*		- CSS: none.
*/


/*	Global variables:
*
*
*
*	Functions:
*
*
*
*	Classes:
*
*
*
*	Methods in the prototype: none.
*
*
*	Class inheritance: none.
*
*
*	Initialization of global variables:
*
*/


//** GLOBAL VARIABLES


//** FUNCTIONS

/*	Function:	Print debug-message.
*	   Input:
*				AllowIn - allow;
*				MsgIn   - message.
*	  Output:
*				None.
*       Note:
*/
function printDebug(AllowIn, MsgIn)
{
	if(AllowIn && typeof console != "undefined" && typeof MsgIn != "undefined")
	{
		console.log(MsgIn);
	}
}


//** CLASSES


//** METHODS IN THE PROTOTYPE


//** CLASS INHERITANCE

