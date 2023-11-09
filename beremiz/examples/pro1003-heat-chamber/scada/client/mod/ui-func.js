/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*  Module: Client side - UI-functions.
*
*   Copyright (C) 2019  ATgroup09 (atgroup09@gmail.com)
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


//** FUNCTIONS

/*
@brief  Scroll to node.
@param  NodeIn - node; [OBJECT]
@param  TopOffsetIn - offset from top of Node; [NUMBER]
@param  AnimateIn - animate effect (msec). [NUMBER]
@return None.
*/
function scrollToNode(NodeIn, TopOffsetIn, AnimateIn)
{
	if(typeof NodeIn == "object")
	{
		if(NodeIn)
		{
			TopOffset = 0;
			if(typeof TopOffsetIn == "number")
			{
				if(TopOffsetIn > 0) TopOffset = TopOffsetIn;
			}
			
			Animate = 500;
			if(typeof AnimateIn == "number")
			{
				if(AnimateIn > 0) Animate = AnimateIn;
			}
			
			$("html, body").animate({ scrollTop: NodeIn.offset().top-TopOffset }, Animate);
		}
	}
}

