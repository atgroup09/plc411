/* bit.h
 *
 * Bit functions
 *
 * Copyright (C) 2013  Pavel Bobkov  (www.chipenable.ru)
 * Copyright (C) 2014  ATgroup09 (atgroup09@gmail.com)
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


#define BYTE0(DWordIn)                                             ((DWordIn >> 0)  & 0xFF)
#define BYTE1(DWordIn)                                             ((DWordIn >> 8)  & 0xFF)
#define BYTE2(DWordIn)                                             ((DWordIn >> 16) & 0xFF)
#define BYTE3(DWordIn)                                             ((DWordIn >> 24) & 0xFF)
#define BYTE4(DWordIn)                                             ((DWordIn >> 32) & 0xFF)
#define BYTE5(DWordIn)                                             ((DWordIn >> 40) & 0xFF)
#define BYTE6(DWordIn)                                             ((DWordIn >> 48) & 0xFF)
#define BYTE7(DWordIn)                                             ((DWordIn >> 56) & 0xFF)


/** \brief  Get Low-word from DWORD.
 *  \param  DWordIn - DWORD.
 *  \return Low-word.
 */
#define WORD0(DWordIn)                                             ((DWordIn >> 0)  & 0xFFFF)

/** \brief  Get High-word from DWORD.
 *  \param  DWordIn - DWORD.
 *  \return High-word.
 */
#define WORD1(DWordIn)                                             ((DWordIn >> 16) & 0xFFFF)


/** \brief  Get a part of 4-bits from DWORD.
 *  \param  DWordIn - DWORD.
 *  \param  PartIn - part of DWORD:
 *  \arg             = 0 - first 4 bit
 *  \arg             = 1 - second 4 bit
 *  \arg             = 2 - third 4 bit
 *  \arg             = 3 - fourth 4 bit
 *  \return High-word.
 */
#define DWORD_BY_4BITS(DWordIn, PartIn)                            ((DWordIn >> PartIn*4) & 0xF)

/** \brief  Get a part of 8-bits from DWORD.
 *  \param  DWordIn - DWORD.
 *  \param  PartIn - part of DWORD:
 *  \arg             = 0 - first 8 bit
 *  \arg             = 1 - second 8 bit
 *  \return High-word.
 */
#define DWORD_BY_8BITS(DWordIn, PartIn)                            ((DWordIn >> PartIn*8) & 0xFF)


/** \brief  Merge two Semibytes into one Byte.
 *  \param  Bit40In - first 4 bit of Byte
 *  \param  Bit41In - second 4 bit of Byte
 *  \return Merged Byte.
 */
#define MERGE_BYTE(Bit40In, Bit41In)                               (((0xFF & Bit41In) << 4) | Bit40In)

/** @def    Merge two bytes to WORD.
 *  @param  Byte0In - first byte.
 *  @param  Byte1In - second byte.
 *  @return Word.
 *  @details Ex.: Word = MERGE_WORD(Byte0, Byte1);
 */
#define MERGE_WORD(Byte0In, Byte1In)                               (((0xFFFF & Byte1In) << 8) | Byte0In)

/** \brief  Merge four Bytes into one DWord.
 *  \param  Byte0In - first Byte
 *  \param  Byte1In - second Byte
 *  \param  Byte2In - third Byte
 *  \param  Byte3In - fourth Byte
 *  \return Merged DWord.
 */
#define MERGE_DWORD(Byte0In, Byte1In, _byte2_in, _byte3_in)        (((0xFFFFFFFF & _byte3_in) << 24) | ((0xFFFFFFFF & _byte2_in) << 16) | ((0xFFFFFFFF & Byte1In) << 8) | Byte0In)

/** \brief  Merge two Words into one DWord.
 *  \param  Word0In - first Word
 *  \param  Word1In - second Word
 *  \return Merged DWord.
 */
#define MERGE_DWORD_V2(Word0In, Word1In)                           (((0xFFFFFFFF & Word1In) << 16) | Word0In)


/** \brief  Get mask with 0-bit set.
 *  \param  BitIn - position of 0-bit
 *  \return 0 (always).
 */
#define BIT_0(BitIn)										       (0<<BitIn)

/** \brief  Get mask with bit set.
 *  \param  BitIn - position of bit
 *  \return Mask with bit set.
 */
#define BIT_1(BitIn)										       (1<<BitIn)


/** \brief  Reset (=0) all bits in Value.
 *  \param  ValueIn - Value.
 *  \return None.
 */
#define BITS_RES(ValueIn)								           ValueIn = 0


/** \brief  Reset (=0) target bit in Value.
 *  \param  ValueIn - Value.
 *  \param  BitIn - bit position in Value.
 *  \return None.
 */
#define BIT_RES(ValueIn, BitIn)						               ValueIn &= (~(1<<(BitIn)))

/** \brief  Set (=1) target bit in Value.
 *  \param  ValueIn - Value.
 *  \param  BitIn - bit position in Value.
 *  \return None.
 */
#define BIT_SET(ValueIn, BitIn)							           ValueIn |= (1<<(BitIn))

/** \brief  Set/Reset target bit in Value.
 *  \param  ValueIn - Value.
 *  \param  BitIn - bit position in Value.
 *  \param  BitValIn - bit value:
 *   \arg     = 0 - reset
 *   \arg     = 1 - set
 *  \return None.
 */
#define BIT_SR_VALUE(ValueIn, BitIn, BitValIn)                     ValueIn = ((BitValIn==0) ? (ValueIn&(~(1<<(BitIn)))) : (ValueIn|(1<<(BitIn))))

/** \brief  Get state of target bit in Value.
 *  \param  ValueIn - Value.
 *  \param  BitIn - bit position in Value.
 *  \return State of target bit.
 */
#define BIT_GET_VALUE(ValueIn, BitIn)					           ((((1<<BitIn)&ValueIn)&(1<<BitIn))!=0 ? 1 : 0)

/** \brief  Check if target bit in Value is cleared (=0).
 *  \param  ValueIn - Value.
 *  \param  BitIn - bit position in Value.
 *  \return 0 if target bit is not clear, otherwise - 1.
 */
#define BIT_IS_CLEAR(ValueIn, BitIn)					           ((ValueIn&(1<<(BitIn)))==0)

/** \brief  Check if target bit in Value is set (=1).
 *  \param  ValueIn - Value.
 *  \param  BitIn - bit position in Value.
 *  \return 0 if target bit is not set, otherwise - 1.
 */
#define BIT_IS_SET(ValueIn, BitIn)						           ((ValueIn&(1<<(BitIn)))!=0)


/** \brief Invert bit.
 *  \param  ValueIn - target value.
 *  \param  BitIn - bit number.
 *  \return none.
 */
#define BIT_INVERT(ValueIn, BitIn)						           ValueIn ^= (1<<(BitIn))


#define BIT_TRUE												   1
#define BIT_FALSE												   0

#define BIT_LO											           0
#define BIT_HI										               1

#define HEX_BASE                                                   16
#define DEC_BASE                                                   10


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


#endif /* BIT_H_ */
