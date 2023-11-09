/* @page type.h
 *       Structured and union types
 *       2020, atgroup09@gmail.com
 */

#ifndef TYPE_H_
#define TYPE_H_

#include <stdint.h>
#include "bit.h"


/** @def ID of types
 */
#define TYPE_BYTE         (uint8_t)1
#define TYPE_WORD         (uint8_t)2
#define TYPE_DWORD        (uint8_t)3
#define TYPE_LWORD        (uint8_t)4
#define TYPE_FLOAT        (uint8_t)5
#define TYPE_DOUBLE       (uint8_t)6
#define TYPE_SINT         (uint8_t)7
#define TYPE_INT          (uint8_t)8
#define TYPE_DINT         (uint8_t)9
#define TYPE_LINT         (uint8_t)10
#define TYPE_BOOL         TYPE_BYTE
#define TYPE_UINT         TYPE_WORD
#define TYPE_UDINT        TYPE_DWORD
#define TYPE_ULINT        TYPE_LWORD
#define TYPE_REAL         TYPE_FLOAT
#define TYPE_LREAL        TYPE_DOUBLE


/** @def Size of types
 *       in bytes
 */
#define TYPE_BYTE_SZ              (uint8_t)sizeof(uint8_t)
#define TYPE_BOOL_SZ              TYPE_BYTE_SZ
#define TYPE_SINT_SZ              (uint8_t)sizeof(int8_t)

#define TYPE_WORD_SZ              (uint8_t)sizeof(uint16_t)
#define TYPE_UINT_SZ              TYPE_WORD_SZ
#define TYPE_INT_SZ               (uint8_t)sizeof(int16_t)

#define TYPE_DWORD_SZ             (uint8_t)sizeof(uint32_t)
#define TYPE_UDINT_SZ             TYPE_DWORD_SZ
#define TYPE_DINT_SZ              (uint8_t)sizeof(int32_t)

#define TYPE_FLOAT_SZ             (uint8_t)sizeof(float)
#define TYPE_REAL_SZ              TYPE_FLOAT_SZ

#define TYPE_LWORD_SZ             (uint8_t)sizeof(uint64_t)
#define TYPE_ULINT_SZ             TYPE_LWORD_SZ
#define TYPE_LINT_SZ              (uint8_t)sizeof(int64_t)

#define TYPE_DOUBLE_SZ            (uint8_t)sizeof(double)
#define TYPE_LREAL_SZ             TYPE_DOUBLE_SZ


/** @def Size of types
 *       in words
 */
#define TYPE_BYTE_WSZ             (uint8_t)1
#define TYPE_BOOL_WSZ             TYPE_BYTE_WSZ
#define TYPE_SINT_WSZ             (uint8_t)1

#define TYPE_WORD_WSZ             (uint8_t)1
#define TYPE_UINT_WSZ             (uint8_t)1
#define TYPE_INT_WSZ              (uint8_t)1

#define TYPE_DWORD_WSZ            (uint8_t)(TYPE_DWORD_SZ/TYPE_WORD_SZ)
#define TYPE_UDINT_WSZ            TYPE_DWORD_WSZ
#define TYPE_DINT_WSZ             (uint8_t)(TYPE_DINT_SZ/TYPE_WORD_SZ)
#define TYPE_FLOAT_WSZ            (uint8_t)(TYPE_FLOAT_SZ/TYPE_WORD_SZ)
#define TYPE_REAL_WSZ             TYPE_FLOAT_WSZ

#define TYPE_LWORD_WSZ            (uint8_t)(TYPE_LWORD_SZ/TYPE_WORD_SZ)
#define TYPE_ULINT_WSZ            TYPE_LWORD_WSZ
#define TYPE_LINT_WSZ             (uint8_t)(TYPE_LINT_SZ/TYPE_WORD_SZ)
#define TYPE_DOUBLE_WSZ           (uint8_t)(TYPE_DOUBLE_SZ/TYPE_WORD_SZ)
#define TYPE_LREAL_WSZ            TYPE_DOUBLE_WSZ


/** @def Size of types
 *       in dwords
 */
#define TYPE_LWORD_DWSZ           (uint8_t)(TYPE_LWORD_SZ/TYPE_DWORD_SZ)


/** @def Byte order
 */
#define TYPE_BYTE_ORDER_3210      (uint8_t)0    //3-2-1-0   (big-endian format: 0 1 2 3)
#define TYPE_BYTE_ORDER_0123      (uint8_t)1    //0-1-2-3   (big-endian format: 3 2 1 0)
#define TYPE_BYTE_ORDER_1032      (uint8_t)2    //1-0-3-2   (big-endian format: 2 3 0 1)
#define TYPE_BYTE_ORDER_2301      (uint8_t)3    //2-3 0-1   (big-endian format: 1 0 3 2)
#define TYPE_BYTE_ORDER_NONE      TYPE_BYTE_ORDER_0123
#define TYPE_BYTE_ORDER_DEF       TYPE_BYTE_ORDER_0123


/** @typedef Union type
 *           DOUBLE > BYTES
 */
typedef union {
    double   data;
    uint8_t  bytes[TYPE_DOUBLE_SZ];
} DOUBLE_ubt;

/** @typedef Union type
 *           DOUBLE > WORDS
 */
typedef union {
    double   data;
    uint16_t words[TYPE_DOUBLE_WSZ];
} DOUBLE_uwt;

typedef union {
    double   data;
    uint8_t  bytes[TYPE_DOUBLE_SZ];
    uint16_t words[TYPE_DOUBLE_WSZ];
} DOUBLE_ubwt;


/** @typedef Union type
 *           LINT > BYTES
 */
typedef union {
    int64_t data;
    uint8_t bytes[TYPE_LWORD_SZ];
} LINT_ubt;

/** @typedef Union type
 *           LINT > WORDS
 */
typedef union {
    int64_t  data;
    uint16_t words[TYPE_LWORD_WSZ];
} LINT_uwt;


/** @typedef Union type
 *           LWORD > BYTES
 */
typedef union {
    uint64_t data;
    uint8_t  bytes[TYPE_LWORD_SZ];
} LWORD_ubt;

/** @typedef Union type
 *           LWORD > BYTES
 */
typedef union {
    uint64_t data;
    uint32_t dwords[TYPE_LWORD_DWSZ];
    uint8_t  bytes[TYPE_LWORD_SZ];
} LWORD_udwt;


/** @typedef Union type
 *           LWORD > WORDS
 */
typedef union {
    uint64_t data;
    uint16_t words[TYPE_LWORD_WSZ];
} LWORD_uwt;


/** @typedef Union type
 *           FLOAT > BYTES
 */
typedef union {
    float    data;
    uint8_t  bytes[TYPE_FLOAT_SZ];
} FLOAT_ubt;

/** @typedef Union type
 *           FLOAT > WORDS
 */
typedef union {
    float    data;
    uint16_t words[TYPE_FLOAT_WSZ];
} FLOAT_uwt;


/** @typedef Union type
 *           DINT > BYTES
 */
typedef union {
    int32_t data;
    uint8_t bytes[TYPE_DINT_SZ];
} DINT_ubt;

/** @typedef Union type
 *           DINT > WORDS
 */
typedef union {
    int32_t  data;
    uint16_t words[TYPE_DINT_WSZ];
} DINT_uwt;


/** @typedef Union type
 *           DWORD > BYTES
 */
typedef union {
    uint32_t data;
    uint8_t  bytes[TYPE_DWORD_SZ];
} DWORD_ubt;

/** @typedef Union type
 *           DWORD > WORDS
 */
typedef union {
    uint32_t data;
    uint16_t words[TYPE_DWORD_WSZ];
} DWORD_uwt;


/** @typedef Union type
 *           INT > BYTES
 */
typedef union {
    int16_t data;
    uint8_t bytes[TYPE_INT_SZ];
} INT_ubt;

/** @typedef Union type
 *           INT > WORDS
 */
typedef union {
    int16_t  data;
    uint16_t words[TYPE_INT_WSZ];
} INT_uwt;


/** @typedef Union type
 *           WORD > BYTES
 */
typedef union {
    uint16_t data;
    uint8_t  bytes[TYPE_WORD_SZ];
} WORD_ubt;

/** @typedef Union type
 *           WORD > WORDS
 */
typedef union {
    uint16_t data;
    uint16_t words[TYPE_WORD_WSZ];
} WORD_uwt;


/** @typedef Union type
 *           SINT > BYTES
 */
typedef union {
    int8_t  data;
    uint8_t bytes[TYPE_SINT_SZ];
} SINT_ubt;

/** @typedef Union type
 *           SINT > WORDS
 */
typedef union {
    int8_t   data;
    uint16_t words[TYPE_SINT_WSZ];
} SINT_uwt;


/** @typedef Union type
 *           BYTE > BYTES
 */
typedef union {
    uint8_t  data;
    uint8_t  bytes[TYPE_BYTE_SZ];
} BYTE_ubt;

/** @typedef Union type
 *           BYTE > WORDS
 */
typedef union {
    uint8_t  data;
    uint16_t words[TYPE_BYTE_WSZ];
} BYTE_uwt;


/** @typedef Union type
 *           WORDS[2] > FLOAT > DWORD > WORD > BYTE
 */
typedef union {
	uint8_t  data_byte;
	uint16_t data_word;
	uint32_t data_dword;
	float    data_float;
    uint16_t words[TYPE_FLOAT_WSZ];
} ANY32_uwt;


/** @brief  Get size (bytes) of data type.
 *  @param  TyIn - ID of data type.
 *  @return Size of data type.
 */
uint8_t Type_GetSz(const uint8_t TyIn);

/** @brief  Get size (words) of data type.
 *  @param  TyIn - ID of data type.
 *  @return Size of data type.
 */
uint8_t Type_GetWSz(const uint8_t TyIn);


/** @brief  Init bytes.
 *  @param  BuffIn    - pointer to buffer of bytes.
 *  @param  BuffSzIn  - size of buffer of bytes.
 *  @param  InitValIn - init-value.
 *  @return Size of inited bytes.
 */
uint8_t Type_InitBytes(uint8_t *BuffIn, const uint16_t BuffSzIn, const uint8_t InitValIn);

/** @brief  Direct copy byte (extended).
 *  @param  FromIn   - pointer to source buffer or 0.
 *  @param  FromSzIn - size of source buffer or 0.
 *  @param  ToIn     - pointer to destination buffer.
 *  @param  ToSzIn   - size of destination buffer.
 *  @param  ZeroedIn - zeroed destination buffer:
 *  @arg               = 0 - no,
 *  @arg               = 1 - yes.
 *  @return Size of copied words (<= ToSzIn).
 *  @note   If FromIn == 0 And/Or FromSzIn == 0, Then ToIn will be zeroed only.
 *  @note   FromIn[0] > ToIn[0] ... FromIn[FromSzIn] > ToIn[FromSzIn]
 */
uint8_t Type_CopyBytesExt(const uint8_t *FromIn, const uint8_t FromSzIn, uint8_t *ToIn, const uint8_t ToSzIn, const uint8_t ZeroedIn);

/** @brief  Direct copy byte.
 *  @param  FromIn   - pointer to source buffer.
 *  @param  FromSzIn - size of source buffer.
 *  @param  ToIn     - pointer to destination buffer.
 *  @return Size of copied bytes.
 *  @note   FromIn[0] > ToIn[0] ... FromIn[FromSzIn] > ToIn[FromSzIn]
 */
uint8_t Type_CopyBytes(const uint8_t *FromIn, const uint8_t FromSzIn, uint8_t *ToIn);


/** @brief  Reverse copy byte (extended).
 *  @param  FromIn   - pointer to source buffer or 0.
 *  @param  FromSzIn - size of source buffer or 0.
 *  @param  ToIn     - pointer to destination buffer.
 *  @param  ToSzIn   - size of destination buffer.
 *  @param  ZeroedIn - zeroed destination buffer:
 *  @arg               = 0 - no,
 *  @arg               = 1 - yes.
 *  @return Size of copied words (<= ToSzIn).
 *  @note   If FromIn == 0 And/Or FromSzIn == 0, Then ToIn will be zeroed only.
 *  @note   FromIn[FromSzIn] > ToIn[0] ... FromIn[0] > ToIn[FromSzIn]
 */
uint8_t Type_CopyBytesRevExt(const uint8_t *FromIn, const uint8_t FromSzIn, uint8_t *ToIn, const uint8_t ToSzIn, const uint8_t ZeroedIn);

/** @brief  Reverse copy byte.
 *  @param  FromIn   - pointer to source buffer.
 *  @param  FromSzIn - size of source buffer.
 *  @param  ToIn     - pointer to destination buffer.
 *  @return Size of copied bytes.
 *  @note   FromIn[FromSzIn] > ToIn[0] ... FromIn[0] > ToIn[FromSzIn]
 */
uint8_t Type_CopyBytesRev(const uint8_t *FromIn, const uint8_t FromSzIn, uint8_t *ToIn);


/** @brief  Init words.
 *  @param  BuffIn    - pointer to buffer of words.
 *  @param  BuffSzIn  - size of buffer of words.
 *  @param  InitValIn - init-value.
 *  @return Size of inited words.
 */
uint16_t Type_InitWords(uint16_t *BuffIn, const uint16_t BuffSzIn, const uint16_t InitValIn);

/** @brief  Replace bytes in Word.
 *  @param  WoIn - target word.
 *  @return New Word.
 */
uint16_t Type_ReplaceWordBytes(const uint16_t WoIn);

/** @brief  Order bytes in Word.
 *  @param  WoIn - target word.
 *  @param  FromOrdIn - from ordering type.
 *  @param  ToOrdIn   - to ordering type.
 *  @return New Word.
 *  @note
 *  Ordering types:
 *    TYPE_BYTE_ORDER_3210
 *    TYPE_BYTE_ORDER_0123
 *    TYPE_BYTE_ORDER_1032
 *    TYPE_BYTE_ORDER_2301
 */
uint16_t Type_OrderWordBytes(const uint16_t WoIn, const uint8_t FromOrdIn, const uint8_t ToOrdIn);

/** @brief  Replace words.
 *  @param  Wo1In - pointer to first word.
 *  @param  Wo2In - pointer to second word.
 *  @return None.
 */
void Type_ReplaceWords(uint16_t *Wo1In, uint16_t *Wo2In);

/** @brief  Copy words (extended).
 *  @param  FromIn    - pointer to source buffer or 0.
 *  @param  FromSzIn  - size of source buffer or 0.
 *  @param  FromOrdIn - from ordering type.
 *  @param  ToIn      - pointer to destination buffer.
 *  @param  ToSzIn    - size of destination buffer.
 *  @param  ToOrdIn   - to ordering type.
 *  @param  ZeroedIn  - zeroed destination buffer:
 *  @arg               = 0 - no,
 *  @arg               = 1 - yes.
 *  @param ChangeMonIn - pointer to store of change-monitoring status (0 if change-monitoring is not used).
 *  @return Size of copied words (<= ToSzIn).
 *  @note
 *  Ordering types:
 *    TYPE_BYTE_ORDER_3210
 *    TYPE_BYTE_ORDER_0123
 *    TYPE_BYTE_ORDER_1032
 *    TYPE_BYTE_ORDER_2301
 *
 *  If FromIn == 0 And/Or FromSzIn == 0, Then ToIn will be zeroed only.
 */
uint8_t Type_CopyWordsExt(const uint16_t *FromIn, const uint16_t FromSzIn, const uint8_t FromOrdIn, uint16_t *ToIn, const uint16_t ToSzIn, const uint8_t ToOrdIn, const uint8_t ZeroedIn, uint8_t *ChangeMonIn);

/** @brief  Copy words.
 *  @param  FromIn   - pointer to source buffer.
 *  @param  FromSzIn - size of source buffer.
 *  @param  ToIn     - pointer to destination buffer.
 *  @return Size of copied words.
 */
uint8_t Type_CopyWords(const uint16_t *FromIn, const uint16_t FromSzIn, uint16_t *ToIn);


#endif /* TYPE_H_ */
