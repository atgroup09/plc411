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


/*   Library: bit logic.
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
*		*** get bit mask ***
*		getBitMask($BitNum_in = 0)
*
*		*** test bit ***
*		testBit($Word_in = 0, $BitNum_in = 0)
*
*		*** get bit value ***
*		getBitValue($Word_in = 0, $BitNum_in = 0)
*
*		*** get first Byte from DWord ***
*		Byte0($DWordIn = 0)
*
*		*** get second Byte from DWord ***
*		Byte1($DWordIn = 0)
*
*		*** get third Byte from DWord ***
*		Byte2($DWordIn = 0)
*
*		*** get fourth Byte from DWord ***
*		Byte3($DWordIn = 0)
*
*		*** get first Word from DWord ***
*		Word0($DWordIn = 0)
*
*		*** get second Word from DWord ***
*		Word1($DWordIn = 0)
*
*		*** merge two Bytes into Word ***
*		mergeWord($Byte0In = 0, $Byte1In = 0)
*
*		*** merge four Bytes into DWord ***
*		mergeDWord($Byte0In = 0, $Byte1In = 0, $Byte2In = 0, $Byte3In = 0)
*
*		*** merge two Words into DWord ***
*		mergeDWordV2($Word0In = 0, $Word1In = 0)
*
*		*** clear Bit in Number ***
*		clearBit($NumberIn = 0, $BitNumIn = 0)
*
*		*** set Bit in Number ***
*		setBit($NumberIn = 0, $BitNumIn = 0)
*
*		*** get Bit ***
*		getBit($NumberIn = 0, $BitNumIn = 0)
*
*		*** get Bit (boolean) ***
*		getBitBoo($NumberIn = 0, $BitNumIn = 0)
*
*		*** check Bit status (if bit is clear) ***
*		isBitClear($NumberIn = 0, $BitNumIn = 0)
*
*		*** check Bit status (if bit is set) ***
*		isBitSet($NumberIn = 0, $BitNumIn = 0)
*
*		*** invert Bit ***
*		invertBit($NumberIn = 0, $BitNumIn = 0)
*
*		*** copy Bits ***
*		copyBits($NumberIn = 0, $StartBitIn = 0, $NumBitsIn = 0)
*
*		*** split the number on bits and save the result into buffer (array or string) ***
*		splitBits($NumberIn = 0, &$BufferIn = null)
*
*
*	Classes: none.
*/


//** GLOBAL VARIABLES



//** FUNCTIONS

/*	Function: get bit mask.
*
*	Input:
*			BitNum_in - bit number (0 ... ).	[INTEGER]
*	Output:
*			bit mask.	[INTEGER]
*/
function getBitMask($BitNum_in = 0)
{
	return ((is_int($BitNum_in)) ? (1 << $BitNum_in) : 0);
}


/*	Function: test bit.
*
*	Input:
*			Word_in		- word;					[INTEGER]
*			BitNum_in	- bit number (0 ... ).	[INTEGER]
*	Output:
*			nonzero result, 2**offset, if the bit at 'offset' is one.	[INTEGER]
*/
function testBit($Word_in = 0, $BitNum_in = 0)
{
	if(is_int($Word_in))
	{
		$BitMask = getBitMask($BitNum_in);
		
		return ($Word_in & $BitMask);
	}
	
	return 0;
}


/*	Function: get bit value.
*
*	Input:
*			Word_in		- word;					[INTEGER]
*			BitNum_in	- bit number (0 ... ).	[INTEGER]
*	Output:
*			bit value (0 || 1).	[INTEGER]
*/
function getBitValue($Word_in = 0, $BitNum_in = 0)
{
	$Mask = getBitMask($BitNum_in);
	$Test = ($Word_in & $Mask);
	
	return (($Test != $Mask) ? 0 : 1);
}


/*	Function: get first Byte from DWord.
*
*	Input:
*			DWordIn - double word.	[INTEGER]
*	Output:
*			first Byte.	[INTEGER]
*/
function Byte0($DWordIn = 0)
{
	return ((is_int($DWordIn)) ? (($DWordIn >> 0)  & 0xFF) : 0);
}


/*	Function: get second Byte from DWord.
*
*	Input:
*			DWordIn - double word.	[INTEGER]
*	Output:
*			second Byte.	[INTEGER]
*/
function Byte1($DWordIn = 0)
{
	return ((is_int($DWordIn)) ? (($DWordIn >> 8)  & 0xFF) : 0);
}


/*	Function: get third Byte from DWord.
*
*	Input:
*			DWordIn - double word.	[INTEGER]
*	Output:
*			third Byte.	[INTEGER]
*/
function Byte2($DWordIn = 0)
{
	return ((is_int($DWordIn)) ? (($DWordIn >> 16)  & 0xFF) : 0);
}


/*	Function: get fourth Byte from DWord.
*
*	Input:
*			DWordIn - double word.	[INTEGER]
*	Output:
*			fourth Byte.	[INTEGER]
*/
function Byte3($DWordIn = 0)
{
	return ((is_int($DWordIn)) ? (($DWordIn >> 24)  & 0xFF) : 0);
}


/*	Function: get first Word from DWord.
*
*	Input:
*			DWordIn - double word.	[INTEGER]
*	Output:
*			first Word.	[INTEGER]
*/
function Word0($DWordIn = 0)
{
	return ((is_int($DWordIn)) ? (($DWordIn >> 0)  & 0xFFFF) : 0);
}


/*	Function: get second Word from DWord.
*
*	Input:
*			DWordIn - double word.	[INTEGER]
*	Output:
*			second Word.	[INTEGER]
*/
function Word1($DWordIn = 0)
{
	return ((is_int($DWordIn)) ? (($DWordIn >> 16)  & 0xFFFF) : 0);
}


/*	Function: merge two Bytes into Word.
*
*	Input:
*			Byte0In - first byte;	[INTEGER]
*			Byte1In - second byte.	[INTEGER]
*	Output:
*			merged Word.	[INTEGER]
*/
function mergeWord($Byte0In = 0, $Byte1In = 0)
{
	return ((is_int($Byte0In) && is_int($Byte1In)) ? (((0xFFFF & $Byte1In) << 8) | $Byte0In) : 0);
}


/*	Function: merge four Bytes into DWord.
*
*	Input:
*			Byte0In - first byte;	[INTEGER]
*			Byte1In - second byte;	[INTEGER]
*			Byte2In - third byte;	[INTEGER]
*			Byte3In - fourth byte.	[INTEGER]
*	Output:
*			merged DWord.	[INTEGER]
*/
function mergeDWord($Byte0In = 0, $Byte1In = 0, $Byte2In = 0, $Byte3In = 0)
{
	return ((is_int($Byte0In) && is_int($Byte1In) && is_int($Byte2In) && is_int($Byte3In)) ? (((0xFFFFFFFF & $Byte3In) << 24) | ((0xFFFFFFFF & $Byte2In) << 16) | ((0xFFFFFFFF & $Byte1In) << 8) | $Byte0In) : 0);
}


/*	Function: merge two Words into DWord.
*
*	Input:
*			Word0In - first word;	[INTEGER]
*			Word1In - second word.	[INTEGER]
*	Output:
*			merged DWord.	[INTEGER]
*/
function mergeDWordV2($Word0In = 0, $Word1In = 0)
{
	return ((is_int($Word0In) && is_int($Word1In)) ? (((0xFFFFFFFF & $Word1In) << 16) | $Word0In) : 0);
}


/*	Function: clear Bit in Number.
*
*	Input:
*			NumberIn - number;		[INTEGER]
*			BitNumIn - bit number (0 ...).	[INTEGER]
*	Output:
*			new Number.	[INTEGER]
*/
function clearBit($NumberIn = 0, $BitNumIn = 0)
{
	$Res = 0;

	if(is_int($NumberIn) && is_int($BitNumIn))
	{
		$Res = $NumberIn;
	
		if($BitNumIn >= 0)
		{
			$Res &= (~(1<<($BitNumIn)));
		}
	}

	return ($Res);
}


/*	Function: set Bit in Number.
*
*	Input:
*			NumberIn - number;		[INTEGER]
*			BitNumIn - bit number (0 ...).	[INTEGER]
*	Output:
*			new Number.	[INTEGER]
*/
function setBit($NumberIn = 0, $BitNumIn = 0)
{
	$Res = 0;

	if(is_int($NumberIn) && is_int($BitNumIn))
	{
		$Res = $NumberIn;
	
		if($BitNumIn >= 0)
		{
			$Res |= (1<<($BitNumIn));
		}
	}

	return ($Res);
}


/*	Function: get Bit.
*
*	Input:
*			NumberIn - number;		[INTEGER]
*			BitNumIn - bit number (0 ...).	[INTEGER]
*	Output:
*			0 || 1.	[INTEGER]
*/
function getBit($NumberIn = 0, $BitNumIn = 0)
{
	$Res = 0;

	if(is_int($NumberIn) && is_int($BitNumIn))
	{
		$Res = $NumberIn;
	
		if($BitNumIn >= 0)
		{
			$Res = (((1<<$BitNumIn)&$NumberIn)&&(1<<$BitNumIn));
		}
	}

	return ($Res);
}


/*	Function: get Bit (boolean).
*
*	Input:
*			NumberIn - number;		[INTEGER]
*			BitNumIn - bit number (0 ...).	[INTEGER]
*	Output:
*			false || true.	[BOOLEAN]
*/
function getBitBoo($NumberIn = 0, $BitNumIn = 0)
{
	$Res = ((function_exists("getBit")) ? getBit($NumberIn, $BitNumIn) : 0);

	return (($Res > 0) ? true : false);
}


/*	Function: check Bit status (if bit is clear).
*
*	Input:
*			NumberIn - number;		[INTEGER]
*			BitNumIn - bit number (0 ...).	[INTEGER]
*	Output:
*			true if Bit is clear, otherwise - false.	[BOOLEAN]
*/
function isBitClear($NumberIn = 0, $BitNumIn = 0)
{
	$Res = ((function_exists("getBitBoo")) ? getBitBoo($NumberIn, $BitNumIn) : false);

	return (($Res == false) ? true : false);
}


/*	Function: check Bit status (if bit is set).
*
*	Input:
*			NumberIn - number;		[INTEGER]
*			BitNumIn - bit number (0 ...).	[INTEGER]
*	Output:
*			true if Bit is set, otherwise - false.	[BOOLEAN]
*/
function isBitSet($NumberIn = 0, $BitNumIn = 0)
{
	$Res = ((function_exists("getBitBoo")) ? getBitBoo($NumberIn, $BitNumIn) : false);

	return (($Res == true) ? true : false);
}


/*	Function: invert Bit.
*
*	Input:
*			NumberIn - number;		[INTEGER]
*			BitNumIn - bit number (0 ...).	[INTEGER]
*	Output:
*			new Number.	[INTEGER]
*/
function invertBit($NumberIn = 0, $BitNumIn = 0)
{
	$Res = 0;

	if(is_int($NumberIn) && is_int($BitNumIn))
	{
		$Res = $NumberIn;
	
		if($BitNumIn >= 0)
		{
			$Res ^= (1<<($BitNumIn));
		}
	}

	return ($Res);
}


/*	Function: copy Bits.
*
*	Input:
*			NumberIn 	- number;		[INTEGER]
*			StartBitIn	- the position of start bit (0 ... 31);	[INTEGER]
*			NumBitsIn	- the number of copied bits (1 ... 32).	[INTEGER]

*			BitNumIn - bit number (0 ...).	[INTEGER]
*	Output:
*			new Number.	[INTEGER]
*/
function copyBits($NumberIn = 0, $StartBitIn = 0, $NumBitsIn = 0)
{
	$Res = 0;

	if(is_int($NumberIn) && is_int($StartBitIn) && is_int($NumBitsIn) && function_exists("isBitSet") && function_exists("setBit"))
	{
		if($StartBitIn >= 0 && $NumBitsIn > 0)
		{
			if($StartBitIn <= 31)
			{
				$NumBits = ((($StartBitIn+$NumBitsIn+1) <= 32) ? $NumBitsIn : 32-$StartBitIn+1);
				
				for($i=$StartBitIn; $i<$NumBits; $i++)
				{
					if(isBitSet($NumberIn, $i))
					{
						$Res = setBit($Res, $i);
					}
				}
			}
		}
	}

	return ($Res);
}


/*	Function: split the number on bits and save the result into buffer (array or string).
*
*	Input:
*			NumberIn 	- number;	[INTEGER]
*			BufferIn	- link to buffer.	[ARRAY || STRING]
*	Output:
*			the number of bits.	[INTEGER]
*	Note:
*			structure of array buffer:
*				[0] - fitst bit
*				[1] - second bit
*				...
*
*			structure of string buffer:
*				"31bit 30bit ... 1bit 0bit" (ex.: 10001100110011001100110011001100)
*/
function splitBits($NumberIn = 0, &$BufferIn = null)
{
	$Res = 0;
	
	if(is_int($NumberIn) && (is_array($BufferIn) || is_string($BufferIn)) && function_exists("getBit"))
	{
		$BufferIn = ((is_array($BufferIn)) ? array() : "");
		$Bit = 0;
		
		for($i=0; $i<32; $i++)
		{
			$Bit = getBit($NumberIn, $i);
			
			if(is_array($BufferIn))
			{
				$BufferIn[$i] = $Bit;
			}
			else
			{
				$BufferIn = (($Bit == 0) ? ("0").($BufferIn) : ("{$Bit}").($BufferIn));
			}
			
			$Res++;
		}
	}
	
	return ($Res);
}


/*	Function: code 16-bit signed integer value to Two's complement.
*
*	Input:
*			$Sign16bitIn - 16-bit signed integer value.	[INTEGER]
*	Output:
*			16-bit unsigned integer value.	[INTEGER]
*	Note:
*/
function codeTwos($Sign16bitIn = 0)
{
    return (($Sign16bitIn < 0) ? ((-1*$Sign16bitIn)^0xFFFF)+1 : $Sign16bitIn);
}


/*	Function: decode 16-bit unsigned integer value from Two's complement.
*
*	Input:
*			$Unsign16bitIn - 16-bit unsigned integer value.	[INTEGER]
*	Output:
*			16-bit signed integer value.	[INTEGER]
*	Note:
*/
function decodeTwos($Unsing16bitIn)
{
    return (($Unsing16bitIn > 0x7FFF) ? ($Unsing16bitIn-0xFFFF-1) : $Unsing16bitIn);
}

?>
