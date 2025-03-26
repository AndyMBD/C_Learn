#ifndef  MAIN_H
#define  MAIN_H

#define RESET_ENTRY_POINT (vuint32)_usr_init

#ifndef V_MEMROM1
   #define V_MEMROM1                 /* fast data access in ROM */
#endif

#ifndef MEMORY_ROM
   #ifndef V_MEMROM2
      #define V_MEMROM2        const    /* fast data access in ROM */
   #endif
#endif

#ifndef V_MEMROM3
   # define V_MEMROM3
#endif
typedef unsigned char  vuint8;

/** Structure definition for subfunction parameter check */
typedef struct tagSubFctInfoTable
{
   /** Pointer to subfunction ID table */
   V_MEMROM1 vuint8 V_MEMROM2 V_MEMROM3  *subFctParamIdTable;
   /** Session support, length check and security level configuration */
   vuint8                     sessionSupport;
   /** Service length. If special length check is not set, fixed check against this value. */
//    tCwDataLengthType          serviceLen;
   /** Selects main handler function */
//    vsintx                     mainInstanceHandlerIdx;
} tSubFctInfoTable;

#endif