/* bit.h
 *
 * Bit functions
 *
 * Copyright (C) 2013  Pavel Bobkov  (www.chipenable.ru)
 * Copyright (C) 2014-2020 AT09 (atgroup09@gmail.com)
 *
 * The C code in this page is free software: you can
 * redistribute it and/or modify it under the terms of the GNU
 * General Public License (GNU GPL) as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.  The code is distributed WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU GPL for more details.
 *
 * As additional permission under GNU GPL version 3 section 7, you
 * may distribute non-source (e.g., minimized or compacted) forms of
 * that code without the copy of the GNU GPL normally required by
 * section 4, provided you include this license notice and a URL
 * through which recipients can access the Corresponding Source.
 */

#ifndef BIT_H_
#define BIT_H_


/** @def    Get N-bits of DWORD.
 *  @param  DwordIn - DWORD.
 *  @param  PosIn   - start bit position:
 *  @arg      = 0 ...
 *  @param  MaskIn  - OR-mask.
 *  @return Word.
 *  @details Ex.: FourBits = GET_NBITS(DWord, 0, 4, 0xF);
 */
#define GET_NBITS(DWordIn, PosIn, MaskIn)                   ((DWordIn >> PosIn) & MaskIn)


/** @def    Get four bits of DWORD.
 *  @param  DwordIn - DWORD.
 *  @param  PartIn  - part:
 *  @arg      = 0 - first four bits
 *  @arg      = 1 - second four bits
 *  @arg      = ...
 *  @return Word.
 *  @details Ex.: FourBits = GET_4BITS(DWord, 0);
 */
#define GET_4BITS(DWordIn, PartIn)                                  ((DWordIn >> PartIn*4) & 0xF)

/** @def    Get eight bits of DWORD.
 *  @param  DwordIn - DWORD.
 *  @param  PartIn  - part:
 *  @arg      = 0 - first eight bits
 *  @arg      = 1 - second eight bits
 *  @arg      = ...
 *  @return Word.
 *  @details Ex.: EightBits = GET_8BITS(DWord, 0);
 */
#define GET_8BITS(DWordIn, PartIn)                                  ((DWordIn >> PartIn*8) & 0xFF)


/** @def    Get first byte of DWORD.
 *  @param  DwordIn  - DWORD.
 *  @return Byte.
 *  @details Ex.: Byte0 = BYTE0(DWord);
 */
#define BYTE0(DWordIn)                                              ((DWordIn >> 0)  & 0xFF)

/** @def    Get second byte of DWORD.
 *  @param  DwordIn  - DWORD.
 *  @return Byte.
 *  @details Ex.: Byte1 = BYTE1(DWord);
 */
#define BYTE1(DWordIn)                                             ((DWordIn >> 8)  & 0xFF)

/** @def    Get third byte of DWORD.
 *  @param  DwordIn  - DWORD.
 *  @return Byte.
 *  @details Ex.: Byte2 = BYTE2(DWord);
 */
#define BYTE2(DWordIn)                                             ((DWordIn >> 16) & 0xFF)

/** @def    Get fourth byte of DWORD.
 *  @param  DwordIn  - DWORD.
 *  @return Byte.
 *  @details Ex.: Byte3 = BYTE3(DWord);
 */
#define BYTE3(DWordIn)                                             ((DWordIn >> 24) & 0xFF)

/** @def    Get byte of DWORD.
 *  @param  DwordIn   - DWORD.
 *  @param  BytePosIn - byte position:
 *  @arg      = 0 ... 3
 *  @return Byte.
 *  @details Ex.: Byte0 = BYTE_N(DWord, 0);
 */
#define BYTE_N(DWordIn, BytePosIn)                                 ((DWordIn >> (BytePosIn*8)) & 0xFF)


/** @def    Get first word of DWORD.
 *  @param  DwordIn - DWORD.
 *  @return Word.
 *  @details Ex.: Word0 = WORD0(DWord);
 */
#define WORD0(DWordIn)                                             ((DWordIn >> 0)  & 0xFFFF)

/** @def    Get second word of DWORD.
 *  @param  DwordIn - DWORD.
 *  @return Word.
 *  @details Ex.: Word1 = WORD1(DWord);
 */
#define WORD1(DWordIn)                                             ((DWordIn >> 16) & 0xFFFF)


/** @def    Get first dword of LWORD.
 *  @param  LwordIn - LWORD.
 *  @return DWord.
 *  @details Ex.: DWord0 = DWORD0(LWord);
 */
#define DWORD0(LWordIn)                                            ((LWordIn >> 0)  & 0xFFFFFFFF)

/** @def    Get second dword of LWORD.
 *  @param  LwordIn - LWORD.
 *  @return Word.
 *  @details Ex.: DWord1 = DWORD1(LWord);
 */
#define DWORD1(LWordIn)                                            ((LWordIn >> 32) & 0xFFFFFFFF)


/** @def    Merge two four bits parts to BYTE.
 *  @param  Bit40In - first four bits.
 *  @param  Bit41In - second four bits.
 *  @return Byte.
 *  @details Ex.: Byte = MERGE_BYTE(Bit4_p0, Bit4_p1);
 */
#define MERGE_BYTE(Bit40In, Bit41In)                               (((0xFF & Bit41In) << 4) | Bit40In)


/** @def    Merge two bytes to WORD.
 *  @param  Byte0In - first byte.
 *  @param  Byte1In - second byte.
 *  @return Word.
 *  @details Ex.: Word = MERGE_WORD(Byte0, Byte1);
 */
#define MERGE_WORD(Byte0In, Byte1In)                               (((0xFFFF & Byte1In) << 8) | Byte0In)

/** @def    Merge four bytes to DWORD.
 *  @param  Byte0In   - first byte.
 *  @param  Byte1In   - second byte.
 *  @param  _byte2_in - third byte.
 *  @param  _byte3_in - fourth byte.
 *  @return DWord.
 *  @details Ex.: DWord = MERGE_DWORD(Byte0, Byte1, Byte3, Byte4);
 */
#define MERGE_DWORD(Byte0In, Byte1In, _byte2_in, _byte3_in)        (((0xFFFFFFFF & _byte3_in) << 24) | ((0xFFFFFFFF & _byte2_in) << 16) | ((0xFFFFFFFF & Byte1In) << 8) | Byte0In)

/** @def    Merge two words to DWORD.
 *  @param  Word0In   - first word.
 *  @param  Word1In   - second word.
 *  @return DWord.
 *  @details Ex.: DWord = MERGE_DWORD_V2(Word0, Word1);
 */
#define MERGE_DWORD_V2(Word0In, Word1In)                           (((0xFFFFFFFF & Word1In) << 16) | Word0In)


/** @def    Merge two dwords to LWORD.
 *  @param  DWord0In   - first dword.
 *  @param  DWord1In   - second dword.
 *  @return LWord.
 *  @details Ex.: LWord = MERGE_LWORD(DWord0, DWord1);
 */
#define MERGE_LWORD(DWord0In, DWord1In)                           (((0xFFFFFFFFFFFFFFFF & DWord1In) << 32) | DWord0In)


/** @def    Get bit number.
 *  @param  BitIn - bit position.
 *  @return 0.
 */
#define GET_BIT0(BitIn)										      (0<<BitIn)

/** @def    Get bit number.
 *  @param  BitIn - bit position.
 *  @return 2^BitIn.
 *  @details Ex.: BitNum = BIT1(2);
 *                = 2^2 = 4
 */
#define GET_BIT1(BitIn)										      (1<<BitIn)


/** @def    Reset all bits in value.
 *  @param  ValueIn - value.
 *  @return None.
 *  @details Ex.: BITS_RES(Value);
 *                Value = 0
 */
#define BITS_RES(ValueIn)								           ValueIn = 0

/** @def    Reset bit in value.
 *  @param  ValueIn - value.
 *  @param  BitIn   - bit position:
 *  @arg      = 0 ...
 *  @return None.
 *  @details Ex.: BIT_RES(Value, 0);
 *                Value.0 = 0
 */
#define BIT_RES(ValueIn, BitIn)						               ValueIn &= (~(1<<(BitIn)))

/** @def    Set bit in value.
 *  @param  ValueIn - value.
 *  @param  BitIn   - bit position:
 *  @arg      = 0 ...
 *  @return None.
 *  @details Ex.: BIT_SET(Value, 0);
 *                Value.0 = 1
 */
#define BIT_SET(ValueIn, BitIn)							           ValueIn |= (1<<(BitIn))


/** @def    Set bit state.
 *  @param  ValueIn  - value.
 *  @param  BitPosIn - bit position:
 *  @arg      = 0 ...
 *  @param  BitValIn - bit value
 *  @arg      = 0
 *  @arg      = 1
 *  @return New value.
 *  @details Ex.: Byte = BIT_SET_VALUE(Byte, 1, 0);
 *                Byte = BIT_SET_VALUE(Byte, 0, 7);
 */
#define BIT_SET_VALUE(ValueIn, BitPosIn, BitValIn)               ((BitValIn == 0) ? (ValueIn & (~(1<<BitPosIn))) : (ValueIn | (1<<BitPosIn)))

/** @def    Get bit state from value.
 *  @param  ValueIn - value.
 *  @param  BitIn   - bit position:
 *  @arg      = 0 ...
 *  @return 0 or 1.
 *  @details Ex.: Bit0 = BIT_GET_VALUE(Value, 0);
 */
#define BIT_GET_VALUE(ValueIn, BitIn)					           ((((1<<BitIn)&ValueIn)&(1<<BitIn))!=0 ? 1 : 0)

/** @def    Test bit 0-state in value.
 *  @param  ValueIn - value.
 *  @param  BitIn   - bit position:
 *  @arg      = 0 ...
 *  @return Result:
 *  @arg      = 0 - bit in position is not 0
 *  @arg      = 1 - bit in position is 0
 *  @details Ex.: Bit0 = BIT_IS_CLEAR(Value, 0);
 */
#define BIT_IS_CLEAR(ValueIn, BitIn)					           ((ValueIn&(1<<(BitIn)))==0)

/** @def    Test bit 1-state in value.
 *  @param  ValueIn - value.
 *  @param  BitIn   - bit position:
 *  @arg      = 0 ...
 *  @return Result:
 *  @arg      = 0 - bit in position is not 1
 *  @arg      = 1 - bit in position is 1
 *  @details Ex.: Bit0 = BIT_IS_SET(Value, 0);
 */
#define BIT_IS_SET(ValueIn, BitIn)						           ((ValueIn&(1<<(BitIn)))!=0)


/** @def    Invert bit state in value.
 *  @param  ValueIn - value.
 *  @param  BitIn   - bit position:
 *  @arg      = 0 ...
 *  @return None.
 *  @details Ex.: BIT_INVERT(Value, 0);
 *                Value.0 = !Value.0
 */
#define BIT_INVERT(ValueIn, BitIn)						           ValueIn ^= (1<<(BitIn))


/** @def Bit states.
 */
#define BIT_TRUE												   (uint8_t)1
#define BIT_FALSE												   (uint8_t)0

#define BIT_ERROR2												   (uint8_t)2

#define BIT_LO											           (uint8_t)0
#define BIT_HI										               (uint8_t)1


/** @def Number bases.
 */
#define HEX_BASE                                                   (uint8_t)16
#define DEC_BASE                                                   (uint8_t)10


/** @def    Set bit into byte.
 *  @param  ByteIn   - target byte.
 *  @param  BitValIn - bit value
 *  @arg      = 0
 *  @arg      = 1
 *  @param  BitPosIn - bit position:
 *  @arg      = 0 ... 7
 *  @return New byte.
 *  @details Ex.: Byte = BYTE_SET_BIT(Byte, 1, 0);
 *                Byte = BYTE_SET_BIT(Byte, 0, 7);
 */
#define BYTE_SET_BIT(ByteIn, BitValIn, BitPosIn)                   ((BitValIn == 0) ? (ByteIn & (~(1<<BitPosIn))) : (ByteIn | (1<<BitPosIn)))


/** @def    Set byte into word.
 *  @param  WordIn - target word.
 *  @param  ByteIn - byte.
 *  @param  PosIn  - byte position:
 *  @arg      = 0
 *  @arg      = 1
 *  @return New word.
 *  @details Ex.: Word = WORD_SET_BYTE(Word, Byte0, 0);
 *                Word = WORD_SET_BYTE(Word, Byte1, 1);
 */
#define WORD_SET_BYTE(WordIn, ByteIn, PosIn)                       ((PosIn == 0) ? ((WordIn & 0xFF00) | ByteIn) : ((WordIn & 0x00FF) | ((0xFFFF & ByteIn) << 8)))


/** @def    Test value on limit
 *  @param  MinIn - minimum value
 *  @param  ValIn - value
 *  @param  MaxIn - maximum value
 *  @return Result code:
 *  @arg      = 0 - the value is out of limit
 *  @arg      = 1 - the value is in limit
 *  @details Min <= Val <= Max
 *           Ex.: if(VAL_IN_LIMITS(MinIn, ValIn, MaxIn)) ...;
 */
#define VAL_IN_LIMITS(MinIn, ValIn, MaxIn)                         ((ValIn >= MinIn && ValIn <= MaxIn) ? 1 : 0)


#endif /* BIT_H_ */
