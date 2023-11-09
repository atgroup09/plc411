//JAVASCRIPT DOCUMENT


/*   Library: Bit-functions.
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


/*
@brief  Function: Get first byte from Dword.
@param  Dword_in - DWORD. [NUMBER]
@return First byte. [NUMBER]
*/
function getByte0(Dword_in)
{
	return ((typeof Dword_in == "number") ? ((Dword_in >> 0) & 0xFF) : 0);
}


/*
@brief  Function: Get second byte from Dword.
@param  Dword_in - DWORD. [NUMBER]
@return Second byte. [NUMBER]
*/
function getByte1(Dword_in)
{
	return ((typeof Dword_in == "number") ? ((Dword_in >> 8) & 0xFF) : 0);
}


/*
@brief  Function: Get third byte from Dword.
@param  Dword_in - DWORD. [NUMBER]
@return Third byte. [NUMBER]
*/
function getByte2(Dword_in)
{
	return ((typeof Dword_in == "number") ? ((Dword_in >> 16) & 0xFF) : 0);
}


/*
@brief  Function: Get fourth byte from Dword.
@param  Dword_in - DWORD. [NUMBER]
@return Fourth byte. [NUMBER]
*/
function getByte3(Dword_in)
{
	return ((typeof Dword_in == "number") ? ((Dword_in >> 24) & 0xFF) : 0);
}


/*
@brief  Function: Get byte from Dword.
@param  Dword_in - DWORD. [NUMBER]
@param  ByteNum_in - the number of byte (0 ... 3). [NUMBER]
@return Byte from DWORD. [NUMBER]
*/
function getByte(Dword_in, ByteNum_in)
{
	if(typeof Dword_in == "number" && typeof ByteNum_in == "number")
	{
		switch(ByteNum_in)
		{
			case 0:
				return (getByte0(Dword_in));
			
			case 1:
				return (getByte1(Dword_in));
			
			case 2:
				return (getByte2(Dword_in));
			
			case 3:
				return (getByte3(Dword_in));
		}
	}
	
	return (0);
}


/*
@brief  Function: Get first word from Dword.
@param  Dword_in - DWORD. [NUMBER]
@return First word. [NUMBER]
*/
function getWord0(Dword_in)
{
	return ((typeof Dword_in == "number") ? ((Dword_in >> 0) & 0xFFFF) : 0);
}


/*
@brief  Function: Get second word from Dword.
@param  Dword_in - DWORD. [NUMBER]
@return Second word. [NUMBER]
*/
function getWord1(Dword_in)
{
	return ((typeof Dword_in == "number") ? ((Dword_in >> 16) & 0xFFFF) : 0);
}


/*
@brief  Function: Get byte from Dword.
@param  Dword_in - DWORD. [NUMBER]
@param  WordNum_in - the number of word (0 ... 1). [NUMBER]
@return Byte from DWORD. [NUMBER]
*/
function getWord(Dword_in, WordNum_in)
{
	if(typeof Dword_in == "number" && typeof WordNum_in == "number")
	{
		switch(WordNum_in)
		{
			case 0:
				return (getWord0(Dword_in));
			
			case 1:
				return (getWord1(Dword_in));
		}
	}
	
	return (0);
}


/*
@brief  Function: Merge bytes into word.
@param  Byte0_in - first byte; [NUMBER]
@param  Byte1_in - second byte. [NUMBER]
@return Word. [NUMBER]
*/
function mergeWord(Byte0_in, Byte1_in)
{
	return ((typeof Byte0_in == "number" && typeof Byte1_in == "number") ? (((0xFFFF & Byte1_in) << 8) | Byte0_in) : 0);
}


/*
@brief  Function: Merge bytes into Dword.
@param  Byte0_in - first byte; [NUMBER]
@param  Byte1_in - second byte; [NUMBER]
@param  Byte2_in - third byte; [NUMBER]
@param  Byte3_in - fourth byte. [NUMBER]
@return Dword. [NUMBER]
*/
function mergeDword(Byte0_in, Byte1_in, Byte2_in, Byte3_in)
{
	return ((typeof Byte0_in == "number" && typeof Byte1_in == "number" && typeof Byte2_in == "number" && typeof Byte3_in == "number") ? (((0xFFFFFFFF & Byte3_in) << 24) | ((0xFFFFFFFF & Byte2_in) << 16) | ((0xFFFFFFFF & Byte1_in) << 8) | Byte0_in) : 0);
}


/*
@brief  Function: Merge words into Dword.
@param  Word0_in - first word; [NUMBER]
@param  Word1_in - second word. [NUMBER]
@return Dword. [NUMBER]
*/
function mergeDwordV2(Word0_in, Word1_in)
{
	return ((typeof Word0_in == "number" && typeof Word1_in == "number") ? (((0xFFFFFFFF & Word1_in) << 16) | Word0_in) : 0);
}


/*
@brief  Function: Clear all bits.
@param  Number_in - a number. [NUMBER]
@return New number. [NUMBER]
*/
function clearBits(Number_in)
{
	return (0);
}


/*
@brief  Function: Clear bit in a number.
@param  Number_in - a number; [NUMBER]
@param  Bit_in - the number of bit (>0). [NUMBER]
@return New number. [NUMBER]
*/
function clearBit(Number_in, Bit_in)
{
	var Res = 0;
	
	if(typeof Number_in == "number")
	{
		var Res = Number_in;
		
		if(typeof Bit_in == "number")
		{
			if(Bit_in >= 0) Res &= (~(1<<(Bit_in)));
		}
	}
	
	return (Res);
}


/*
@brief  Function: Check bit in a number.
@param  Number_in - a number; [NUMBER]
@param  Bit_in - the number of bit (>0). [NUMBER]
@return True if bit is clear (0), otherwise - False (1). [BOOLEAN]
*/
function isBitClear(Number_in, Bit_in)
{
	if(typeof Number_in == "number")
	{
		var Res = Number_in;
		
		if(typeof Bit_in == "number")
		{
			if(Bit_in >= 0) return ((Number_in&(1<<(Bit_in)))==0);
		}
	}
	
	return (false);
}


/*
@brief  Function: Set bit in a number.
@param  Number_in - a number; [NUMBER]
@param  Bit_in - the number of bit (>0). [NUMBER]
@return New number. [NUMBER]
*/
function setBit(Number_in, Bit_in)
{
	var Res = 0;
	
	if(typeof Number_in == "number")
	{
		var Res = Number_in;
		
		if(typeof Bit_in == "number")
		{
			if(Bit_in >= 0) Res |= (1<<(Bit_in));
		}
	}
	
	return (Res);
}


/*
@brief  Function: Check bit in a number.
@param  Number_in - a number; [NUMBER]
@param  Bit_in - the number of bit (>0). [NUMBER]
@return True if bit is set (1), otherwise - False (0). [BOOLEAN]
*/
function isBitSet(Number_in, Bit_in)
{
	if(typeof Number_in == "number")
	{
		var Res = Number_in;
		
		if(typeof Bit_in == "number")
		{
			if(Bit_in >= 0) return ((Number_in&(1<<(Bit_in)))!=0);
		}
	}
	
	return (false);
}


/*
@brief  Function: Get bit value from a number.
@param  Number_in - a number; [NUMBER]
@param  Bit_in - the number of bit (>0). [NUMBER]
@return Bit value (0 or 1). [NUMBER]
*/
function getBit(Number_in, Bit_in)
{
	if(typeof Number_in == "number")
	{
		if(typeof Bit_in == "number")
		{
			if(Bit_in >= 0) return ((((1<<Bit_in)&Number_in)&&(1<<Bit_in)) ? 1 : 0);
		}
	}
	
	return (0);
}


/*
@brief  Function: Invert bit in a number.
@param  Number_in - a number; [NUMBER]
@param  Bit_in - the number of bit (>0). [NUMBER]
@return New number. [NUMBER]
*/
function invertBit(Number_in, Bit_in)
{
	var Res = 0;
	
	if(typeof Number_in == "number")
	{
		var Res = Number_in;
		
		if(typeof Bit_in == "number")
		{
			if(Bit_in >= 0) Res ^= (1<<(Bit_in));
		}
	}
	
	return (Res);
}

