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


/*   Library: IEEE-754 (float32).
*
*    Copyright (C) 2016  ATgroup09 (atgroup09@gmail.com)
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
*		- libraries: none.
*/

/*	Global variables: none
*
*	Functions:
*
*		*** merge High and Low-word ***
*		IEEE754MergeWords16($LoWord16_in = 0, $HiWord16_in = 0)
*
*		*** get Float32 from Double Word ***
*		IEEE754GetFloat32($DoubleWord_in = 0)
*
*
*	Classes: none.
*/


//** GLOBAL VARIABLES



//** FUNCTIONS

/*	Function: merge High and Low-word.
*
*	Input:
*			LoWord16_in - Low word (16 bit);
*			HiWord16_in - High word (16 bit).
*	Output:
*			32-bit word (double word).
*/
function IEEE754MergeWords16($LoWord16_in = 0, $HiWord16_in = 0)
{
	$LoWord16	= ((is_int($LoWord16_in)) ? ($LoWord16_in & 65535) : 0);
    $HiWord16	= ((is_int($HiWord16_in)) ? ($HiWord16_in & 65535) : 0);
    $Word32		= 0;
	
    $Word32  = ($HiWord16 << 16);
    $Word32 |= $LoWord16;
	
	return $Word32;
}


/*	Function: get Float32 from Double Word.
*
*	Input:
*			DoubleWord_in - double word (32 bit).
*
*	Output:
*			Float32 (32 bit).
*/
function IEEE754GetFloat32($DoubleWord_in = 0)
{
	$Float32 = 0.0;
	
	if($DoubleWord_in > 0)
	{
		$Sign	  = (float)(($DoubleWord_in >> 31) ? -1 : 1);
		$Exp	  = (float)(($DoubleWord_in >> 23) & 0xFF);
		$Mantissa = (float)(($Exp > 0.0) ? (($DoubleWord_in & 0x7FFFFF ) | 0x800000) : (($DoubleWord_in & 0x7FFFFF) << 1));
		$Exp -= 127.0;
		
		$Float32 = ($Sign*$Mantissa*(pow(2, ($Exp-23.0))));
	}
	
	return $Float32;
}

?>
