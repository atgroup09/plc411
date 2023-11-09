/*	JAVASCRIPT DOCUMENT
*	UTF-8
*/

/*   Module: Response result.
*
*    Copyright (C) 2018-2019  ATgroup09 (atgroup09@gmail.com)
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


//** GLOBAL VARIABLES


//** FUNCTIONS


//** CLASSES

/*	Class:	Response result parser.
*	Input:
*			ResultIn - response result.		[OBJECT || NULL]
*	Note:
*
*			Structure of ResultIn:
*
*				{ result: {  status: true|false,
*						    message: String
*						  },
*				    data: [ {Key:Value, ...},
*                            ...
*                          ],
*				 fillset: [ SelectID: { options:[ {text:Text, value:Value, selected:Boolean}, ... ], clear:Boolean, append:Boolean },
*                           ...
*                          ],
*                    idq: String,
*                form_id: String
*				}
*
*				or
*
*				{  status: true|false,
*				  message: ...,
*					data: ...,
*				 fillset: ...,
*                    idq: ...,
*                form_id: ...
*				}
*
*				or
*
*				"#Header#Content"
*
* where, 
*     result.status or status   - status of response (true - OK, false - error)
*     result.message or message - error message
*                          data - array of lists of named values (by Key) of DataForm
*                       fillset - setting and list of options to fill of select-lists of DataForm
*                           idq - ID of request (required)
*                       form_id - ID of DataForm (required)
*/
function jsResponseResult(ResultIn)
{
	//Public properties
	
	this.Status      = false;
	this.Message     = "";
	this.HaveMessage = false;
	this.Data 		 = null;
	this.Fillset 	 = null;
	this.idq 	     = null;
	this.TargetID    = null;
	
	
	//Private properties
	
	
	//Methods
	
	this.parseResult = function(ResultIn)
	{
		if(typeof ResultIn == "object")
		{
			if(ResultIn)
			{
				if(typeof ResultIn["status"] == "boolean") this.Status = ResultIn["status"];
				if(typeof ResultIn["message"] == "string") this.Message = ResultIn["message"];
			}
		}
	};
	
	//Public Method: Parse result.
	//Input:
	//			ResultIn - response result.		[OBJECT || NULL]
	//Output:
	//			none.
	//Note:
	//
	this.parse = function(ResultIn)
	{
		this.Status  = false;
		this.Message = "";
		this.Data    = null;
		
		if(typeof ResultIn == "object")
		{
			if(ResultIn)
			{
				this.parseResult(ResultIn);
				
				if(typeof ResultIn["result"] == "object") this.parseResult(ResultIn["result"]);
				if(typeof ResultIn["data"] != "undefined") this.Data = ResultIn["data"];
				if(typeof ResultIn["fillset"] != "undefined") this.Fillset = ResultIn["fillset"];
				if(typeof ResultIn["idq"] == "string") this.idq = ResultIn["idq"];
				if(typeof ResultIn["target_id"] == "string") this.TargetID = ResultIn["target_id"];
			}
		}
		else if(typeof ResultIn == "string")
		{
			this.Message = ResultIn.replace(/^#[a-zA-Z]*#/gi, '');
		}
		
		this.HaveMessage = ((this.Message.length) ? true : false);
	};
	
	
	//Constructor
	this.parse(ResultIn);
}


