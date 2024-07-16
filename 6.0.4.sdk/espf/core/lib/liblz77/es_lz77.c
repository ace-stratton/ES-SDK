/*
 * Copyright (c) 2020-2022 EnduroSat AD. All rights reserved.
 *
 * Contents and presentations are protected world-wide.
 * Any kind of using, copying etc. is prohibited without prior permission.
 */
/**
 * @addtogroup liblz77
 * @{
 *
 * @file es_lz77.h
 * @brief LZ77 library implementation
 *
 * @}
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include <SdMngr.h>
#include "es_lz77.h"

/* set this to 1 for a greedy encoder */
#define GREEDY    0

/* ratio vs. speed constant */
/* the larger this constant, the better the compression */
#define MAXCOMPARES 75

/* unused entry flag */
#define NIL       0xFFFF

/* bits per symbol- normally 8 for general purpose compression */
#define CHARBITS  8

/* minimum match length & maximum match length */
#define THRESHOLD 2
#define MATCHBITS 4
#define MAXMATCH  ((1 << MATCHBITS) + THRESHOLD - 1)

/* sliding dictionary size and hash table's size */
/* some combinations of HASHBITS and THRESHOLD values will not work correctly because of the way this program hashes strings */
#define DICTBITS  13
#define HASHBITS  10
#define DICTSIZE  (1 << DICTBITS)
#define HASHSIZE  (1 << HASHBITS)

/* # bits to shift after each XOR hash */
/* this constant must be high enough so that only THRESHOLD + 1 characters are in the hash accumulator at one time */
#define SHIFTBITS ((HASHBITS + THRESHOLD) / (THRESHOLD + 1))

/* sector size constants */
#define SECTORBIT 10
#define SECTORLEN (1 << SECTORBIT)
#define SECTORAND ((0xFFFF << SECTORBIT) & 0xFFFF)

/* dictionary plus MAXMATCH extra chars for string comparisions */
static uint8_t dict[DICTSIZE + MAXMATCH];

/* hashtable & link list table */
static unsigned int hash[HASHSIZE];
static unsigned int nextlink[DICTSIZE];

/* misc. global variables */
static unsigned int matchlength, matchpos, bitbuf, bitsin;
unsigned int masks[17] = {0,1,3,7,15,31,63,127,255,511,1023,2047,4095,8191,16383,32767,65535};

static FIL infile, outfile;

const osMutexAttr_t LZ77_Mutex_attr = {
  "LZ77_Mutex",
  osMutexRecursive | osMutexPrioInherit,
  NULL,
  0U
};

static osMutexId_t mid_LZ77;

/* writes multiple bit codes to the output stream */
void SendBits(unsigned int bits, unsigned int numbits)
{
    char c;
    UINT bw;

    bitbuf |= (bits << bitsin);

    bitsin += numbits;

    if (bitsin > 16)         /* special case when # bits in buffer exceeds 16 */
    {
        c = bitbuf & 0xFF;
        bw = 0;
        if (SdMngr_f_write(&outfile, &c, 1, &bw) != FR_OK || bw < 1)
        {
            //error writing to output file
            return;
        }
        bitbuf = bits >> (8 - (bitsin - numbits));
        bitsin -= 8;
    }

    while (bitsin >= 8)
    {
        c = bitbuf & 0xFF;
        bw = 0;
        if (SdMngr_f_write(&outfile, &c, 1, &bw) != FR_OK || bw < 1)
        {
            //error writing to output file
            return;
        }
        bitbuf >>= 8;
        bitsin -= 8;
    }
}

/* reads multiple bit codes from the input stream */
unsigned int ReadBits(unsigned int numbits)
{
    unsigned int i;
    unsigned char c;
    UINT br;

    i = bitbuf >> (8 - bitsin);

    while (numbits > bitsin)
    {
        if (SdMngr_f_read(&infile, &c, 1, &br) != FR_OK || br < 1)
        {
            //error reading from input file
            return 0;
        }
        bitbuf = c;
        i |= (bitbuf << bitsin);
        bitsin += 8;
    }

    bitsin -= numbits;

    return (i & masks[numbits]);
}

/* sends a match to the output stream */
void SendMatch(unsigned int matchlen, unsigned int matchdistance)
{
    SendBits(1, 1);

    SendBits(matchlen - (THRESHOLD + 1), MATCHBITS);

    SendBits(matchdistance, DICTBITS);
}

/* sends one character (or literal) to the output stream */
void SendChar(unsigned int character)
{
    SendBits(0, 1);

    SendBits(character, CHARBITS);
}

/* initializes the search structures needed for compression */
void InitEncode(void)
{
    unsigned int i;

    for (i = 0; i < HASHSIZE; i++) hash[i] = NIL;

    nextlink[DICTSIZE] = NIL;
}

/* loads dictionary with characters from the input stream */
unsigned int LoadDict(unsigned int dictpos)
{
    unsigned int i, j;

    i = 0;
    if (SdMngr_f_read(&infile, &dict[dictpos], SECTORLEN, &i) != FR_OK || i < 1)
    {
        //end of file
        return 0;
    }

    /* since the dictionary is a ring buffer, copy the characters at the very start of the dictionary to the end */
    if (dictpos == 0)
    {
        for (j = 0; j < MAXMATCH; j++) dict[j + DICTSIZE] = dict[j];
    }

    return i;
}

/* deletes data from the dictionary search structures */
/* this is only done when the number of bytes to be compressed exceeds the dictionary's size */
void DeleteData(unsigned int dictpos)
{
    unsigned int i, j;

    j = dictpos;

    /* delete all references to the sector being deleted */

    for (i = 0; i < DICTSIZE; i++)
        if ((nextlink[i] & SECTORAND) == j) nextlink[i] = NIL;

    for (i = 0; i < HASHSIZE; i++)
        if ((hash[i] & SECTORAND) == j) hash[i] = NIL;
}

/* hash data just entered into dictionary */
/* XOR hashing is used here, but practically any hash function will work */
void HashData(unsigned int dictpos, unsigned int bytestodo)
{
    unsigned int i, j, k;

    if (bytestodo <= THRESHOLD)   /* not enough bytes in sector for match? */
        for (i = 0; i < bytestodo; i++) nextlink[dictpos + i] = NIL;
    else
    {
        /* matches can't cross sector boundries */
        for (i = bytestodo - THRESHOLD; i < bytestodo; i++)
            nextlink[dictpos + i] = NIL;

        j = (((unsigned int)dict[dictpos]) << SHIFTBITS) ^ dict[dictpos + 1];

        k = dictpos + bytestodo - THRESHOLD;  /* calculate end of sector */

        for (i = dictpos; i < k; i++)
        {
            nextlink[i] = hash[j = (((j << SHIFTBITS) & (HASHSIZE - 1)) ^ dict[i + THRESHOLD])];
            hash[j] = i;
        }
    }
}

/* finds match for string at position dictpos */
/* this search code finds the longest AND closest match for the string at dictpos */
void FindMatch(unsigned int dictpos, unsigned int startlen)
{
    unsigned int i, j, k;
    unsigned char l;

    i = dictpos; matchlength = startlen; k = MAXCOMPARES;
    l = dict[dictpos + matchlength];

    do
    {
        if ((i = nextlink[i]) == NIL) return;   /* get next string in list */

        if (dict[i + matchlength] == l)        /* possible larger match? */
        {
            for (j = 0; j < MAXMATCH; j++)          /* compare strings */
                if (dict[dictpos + j] != dict[i + j]) break;

            if (j > matchlength)  /* found larger match? */
            {
                matchlength = j;
                matchpos = i;
                if (matchlength == MAXMATCH) return;  /* exit if largest possible match */
                l = dict[dictpos + matchlength];
            }
        }
    }
    while (--k);  /* keep on trying until we run out of chances */
}

/* finds dictionary matches for characters in current sector */
void DictSearch(unsigned int dictpos, unsigned int bytestodo)
{
    unsigned int i, j;

#if (GREEDY == 0)

    unsigned int matchlen1, matchpos1;

    /* non-greedy search loop (slow) */

    i = dictpos; j = bytestodo;

    while (j) /* loop while there are still characters left to be compressed */
    {
        FindMatch(i, THRESHOLD);

        if (matchlength > THRESHOLD)
        {
            matchlen1 = matchlength;
            matchpos1 = matchpos;

            for ( ; ; )
            {
                FindMatch(i + 1, matchlen1);

                if (matchlength > matchlen1)
                {
                    matchlen1 = matchlength;
                    matchpos1 = matchpos;
                    SendChar(dict[i++]);
                    j--;
                }
                else
                {
                    if (matchlen1 > j)
                    {
                        matchlen1 = j;
                        if (matchlen1 <= THRESHOLD) { SendChar(dict[i++]); j--; break; }
                    }

                    SendMatch(matchlen1, (i - matchpos1) & (DICTSIZE - 1));
                    i += matchlen1;
                    j -= matchlen1;
                    break;
                }
            }
        }
        else
        {
            SendChar(dict[i++]);
            j--;
        }
    }

#else

    /* greedy search loop (fast) */

    i = dictpos; j = bytestodo;

    while (j) /* loop while there are still characters left to be compressed */
    {
        FindMatch(i, THRESHOLD);

        if (matchlength > j) matchlength = j;     /* clamp matchlength */

        if (matchlength > THRESHOLD)  /* valid match? */
        {
            SendMatch(matchlength, (i - matchpos) & (DICTSIZE - 1));
            i += matchlength;
            j -= matchlength;
        }
        else
        {
            SendChar(dict[i++]);
            j--;
        }
    }

#endif
}

/* main encoder */
void Compress(void)
{
    unsigned int dictpos, deleteflag, sectorlen;
    unsigned long bytescompressed;

    InitEncode();

    dictpos = deleteflag = 0;

    bytescompressed = 0;

    while (1)
    {
        /* delete old data from dictionary */
        if (deleteflag) DeleteData(dictpos);

        /* grab more data to compress */
        if ((sectorlen = LoadDict(dictpos)) == 0) break;

        /* hash the data */
        HashData(dictpos, sectorlen);

        /* find dictionary matches */
        DictSearch(dictpos, sectorlen);

        bytescompressed += sectorlen;

        dictpos += SECTORLEN;

        /* wrap back to beginning of dictionary when its full */
        if (dictpos == DICTSIZE)
        {
                dictpos = 0;
                deleteflag = 1;   /* ok to delete now */
        }
    }

    /* Send EOF flag */
    SendMatch(MAXMATCH + 1, 0);

    /* Flush bit buffer */
    if (bitsin) SendBits(0, 8 - bitsin);

    return;
}

/* main decoder */
void Decompress(void)
{
    unsigned int i, j, k, bw;
    unsigned long bytesdecompressed;

    i = 0;
    bytesdecompressed = 0;

    for ( ; ; )
    {
        if (ReadBits(1) == 0)   /* character or match? */
        {
            dict[i++] = ReadBits(CHARBITS);
            if (i == DICTSIZE)
            {
                bw = 0;
                if (SdMngr_f_write(&outfile, &dict[0], DICTSIZE, &bw) != FR_OK || bw != DICTSIZE)
                {
                    //error writing to output file
                    return;
                }
                i = 0;
                bytesdecompressed += DICTSIZE;
            }
        }
        else
        {
            /* get match length from input stream */
            k = (THRESHOLD + 1) + ReadBits(MATCHBITS);

            if (k == (MAXMATCH + 1))      /* Check for EOF flag */
            {
                bw = 0;
                if (SdMngr_f_write(&outfile, &dict[0], i, &bw) != FR_OK || bw != i)
                {
                    //error writing to output file
                    return;
                }
                bytesdecompressed += i;
                return;
            }

            /* get match position from input stream */
            unsigned int dict_bits_value = ReadBits(DICTBITS);

            if (i >= dict_bits_value)
            {
            	j = ((i - dict_bits_value) & (DICTSIZE - 1));
            }
            else
            {
            	break;
            }

            if ((i + k) >= DICTSIZE)
            {
                do
                {
                    dict[i++] = dict[j++];
                    j &= (DICTSIZE - 1);
                    if (i == DICTSIZE)
                    {
                        bw = 0;
                        if (SdMngr_f_write(&outfile, &dict[0], DICTSIZE, &bw) != FR_OK || bw != DICTSIZE)
                        {
                            //error writing to output file
                            return;
                        }
                        i = 0;
                        bytesdecompressed += DICTSIZE;
                    }
                }
                while (--k);
            }
            else
            {
                if ((j + k) >= DICTSIZE)
                {
                    do
                    {
                        dict[i++] = dict[j++];
                        j &= (DICTSIZE - 1);
                    }
                    while (--k);
                }
                else
                {
                    do
                    {
                        dict[i++] = dict[j++];
                    }
                    while (--k);
                }
            }
        }
    }
}

int LZ77_Compress(char *name_in, char *name_out, uint32_t timeout)
{
	// Lock resources
	osStatus_t val = osMutexAcquire(mid_LZ77, timeout);
	if (val != osOK)
	{
		if (val == osErrorTimeout)
		{
			return LZ77_ERROR_TIMEOUT;
		}
		return LZ77_ERROR_LOCK;
	}

    memset(dict, 0, sizeof(dict));
    memset(hash, 0, sizeof(hash));
    memset(nextlink, 0, sizeof(nextlink));
    matchlength = 0;
    matchpos = 0;
    bitbuf = 0;
    bitsin = 0;

    memset(&infile, 0, sizeof(FIL));
    memset(&outfile, 0, sizeof(FIL));

    if (f_open(&SDFatFS, &infile, name_in, FA_READ | FA_OPEN_EXISTING) != FR_OK)
    {
        return LZ77_ERROR_FILE;
    }
    if (f_open(&SDFatFS, &outfile, name_out, FA_WRITE | FA_OPEN_ALWAYS) != FR_OK)
    {
        f_close(&infile);
        return LZ77_ERROR_FILE;
    }

    Compress();

    f_close(&infile);
    f_close(&outfile);

	// Unlock resources
    osMutexRelease(mid_LZ77);

    return LZ77_ERROR_OK;
}

int LZ77_Decompress(char *name_in, const char *name_out, uint32_t timeout)
{
	// Lock resources
	osStatus_t val = osMutexAcquire(mid_LZ77, timeout);
	if (val != osOK)
	{
		if (val == osErrorTimeout)
		{
			return LZ77_ERROR_TIMEOUT;
		}
		return LZ77_ERROR_LOCK;
	}

    memset(dict, 0, sizeof(dict));
    memset(hash, 0, sizeof(hash));
    memset(nextlink, 0, sizeof(nextlink));
    matchlength = 0;
    matchpos = 0;
    bitbuf = 0;
    bitsin = 0;

    memset(&infile, 0, sizeof(FIL));
    memset(&outfile, 0, sizeof(FIL));

    if (f_open(&SDFatFS, &infile, name_in, FA_READ | FA_OPEN_EXISTING) != FR_OK)
    {
        return LZ77_ERROR_FILE;
    }
    if (f_open(&SDFatFS, &outfile, name_out, FA_WRITE | FA_OPEN_ALWAYS) != FR_OK)
    {
        f_close(&infile);
        return LZ77_ERROR_FILE;
    }

    Decompress();

    f_close(&infile);
    f_close(&outfile);

	// Unlock resources
    osMutexRelease(mid_LZ77);

    return LZ77_ERROR_OK;
}

void LZ77_Init(void)
{
	if (mid_LZ77 != NULL)
		return;

	mid_LZ77 = osMutexNew(&LZ77_Mutex_attr);
	if (mid_LZ77 == NULL)
	{
		// Mutex object not created
	}
}
