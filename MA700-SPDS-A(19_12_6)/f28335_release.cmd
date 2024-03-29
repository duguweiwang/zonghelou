/******************************************************************************
*                                                                             *
*                         COPYRIGHT (C)   SAE                                 *
*                         ALL RIGHTS RESERVED                                 *
*                                                                             *
*    The copying, use, distribution or disclosure of the confidential and     *
*    proprietary information contained in this document(s) is strictly        *
*    prohibited without prior written consent. Any breach shall subject       *
*    the infringing party to remedies. The owner reserves all rights in       *
*    the event of the grant of a patent or the registration of a utility      *
*    model or design.                                                         *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Module Description:  CMD file for CPA&DCP APP for Formal Relesse        *
*     Module Name:         %name:     f28335_release.cmd %                    *
*     Module Version:      %version:  2 %                                 *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:                                                               *
*                                                                             * 
*     Controller:                                                             *
*                                                                             * 
*-----------------------------------------------------------------------------*
*                                                                             *
*     Author:                                                                 *
*                 %created_by:    maolei %                                           *
*                                                                             *                                      
*     Date:       %date_modified:  Tue Jun 26 18:04:37 2012 %                 *
*                                                                             *
******************************************************************************/


MEMORY
{
PAGE 0:    /* Program Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE1 for data allocation */
   ZONE0       : origin = 0x004000, length = 0x001000     /* XINTF zone 0 */
   RAML0       : origin = 0x008000, length = 0x001000     /* on-chip RAM block L0 */
   RAML1       : origin = 0x009000, length = 0x001000     /* on-chip RAM block L1 */
   RAML2       : origin = 0x00A000, length = 0x001000     /* on-chip RAM block L2 */
   RAML3       : origin = 0x00B000, length = 0x001000     /* on-chip RAM block L3 */
   ZONE6       : origin = 0x0100000, length = 0x100000    /* XINTF zone 6 */ 
   ZONE7A      : origin = 0x0200000, length = 0x00FC00    /* XINTF zone 7 - program space */ 
   BEGIN       : origin = 0x33FFF6, length = 0x000002     /* Part of FLASHA.  Used for "boot to Flash" bootloader mode. 0x300000*/
   FLASH_CoH   : origin = 0x300002, length = 0x02FFFE     /* on-chip FLASH */

  // FLASHH      : origin = 0x300000, length = 0x008000     /* on-chip FLASH */
  // FLASHG      : origin = 0x308000, length = 0x008000     /* on-chip FLASH */
  // FLASHF      : origin = 0x310000, length = 0x008000     /* on-chip FLASH */
  // FLASHE      : origin = 0x318000, length = 0x008000     /* on-chip FLASH */
  // FLASHD      : origin = 0x320000, length = 0x008000     /* on-chip FLASH */
  // FLASHC      : origin = 0x328000, length = 0x008000     /* on-chip FLASH */

   FLASHB      : origin = 0x330000, length = 0x007f6a     /* on-chip FLASH */

   Flash_VerBlk      : origin = 0x337f6a, length = 0x000050     /* Part of FLASHB.  to store version string */
   Flash_MemMap      : origin = 0x337fba, length = 0x000040     /* Part of FLASHB.  to store flash memory map */
   Flash_CRC16       : origin = 0x337ffa, length = 0x000006     /* Part of FLASHB.  to store crc16 value*/

  // FLASHA      : origin = 0x338000, length = 0x007F80     /* on-chip FLASH */

   CSM_RSVD    : origin = 0x33FF80, length = 0x000076     /* Part of FLASHA.  Program with all 0x0000 when CSM is in use. */
   CSM_PWL     : origin = 0x33FFF8, length = 0x000008     /* Part of FLASHA.  CSM password locations in FLASHA */
   OTP         : origin = 0x380400, length = 0x000400     /* on-chip OTP */
   ADC_CAL     : origin = 0x380080, length = 0x000009     /* ADC_cal function in Reserved memory */
   
   IQTABLES    : origin = 0x3FE000, length = 0x000b50     /* IQ Math Tables in Boot ROM */
   IQTABLES2   : origin = 0x3FEB50, length = 0x00008c     /* IQ Math Tables in Boot ROM */  
   FPUTABLES   : origin = 0x3FEBDC, length = 0x0006A0     /* FPU Tables in Boot ROM */
   ROM         : origin = 0x3FF27C, length = 0x000D44     /* Boot ROM */        
   RESET       : origin = 0x3FFFC0, length = 0x000002     /* part of boot ROM  */
   VECTORS     : origin = 0x3FFFC2, length = 0x00003E     /* part of boot ROM  */

PAGE 1 :   /* Data Memory */
           /* Memory (RAM/FLASH/OTP) blocks can be moved to PAGE0 for program allocation */
           /* Registers remain on PAGE1                                                  */
   
   BOOT_RSVD   : origin = 0x000000, length = 0x000050     /* Part of M0, BOOT rom will use this for stack */
   RAMM0       : origin = 0x000050, length = 0x0003B0     /* on-chip RAM block M0 */
   RAMM1       : origin = 0x000400, length = 0x000400     /* on-chip RAM block M1 */
   RAML4       : origin = 0x00C000, length = 0x004000     /* on-chip RAM block L1 */

   ZONE7B      : origin = 0x20FC00, length = 0x000400     /* XINTF zone 7 - data space */

}

/* Allocate sections to memory blocks.
   Note:
         codestart user defined section in DSP28_CodeStartBranch.asm used to redirect code 
                   execution when booting to flash
         ramfuncs  user defined section to store functions that will be copied from Flash into RAM
*/ 
 
SECTIONS
{
 
   /* Allocate program areas: */
   .cinit              : > FLASH_CoH      PAGE = 0
   .pinit              : > FLASH_CoH,     PAGE = 0
   .text               : > FLASH_CoH      PAGE = 0
   codestart           : > BEGIN       PAGE = 0
   ramfuncs            : LOAD = FLASH_CoH,
                         RUN = RAML0, 
                         LOAD_START(_RamfuncsLoadStart),
                         LOAD_END(_RamfuncsLoadEnd),
                         RUN_START(_RamfuncsRunStart),
                         PAGE = 0

   csmpasswds          : > CSM_PWL     PAGE = 0
   csm_rsvd            : > CSM_RSVD    PAGE = 0
   
   /* Allocate uninitalized data sections: */
   .stack              : > RAML1       PAGE = 0
   .ebss               : > RAML4       PAGE = 1
   .esysmem            : > RAML4       PAGE = 1

   /* Initalized sections go in Flash */
   /* For SDFlash to program these, they must be allocated to page 0 */
   .econst             : > FLASH_CoH      PAGE = 0
   .switch             : > FLASH_CoH      PAGE = 0

    my_sect            : > FLASH_CoH      PAGE = 0

   /* Allocate IQ math areas: */
   IQmath              : > FLASH_CoH      PAGE = 0                  /* Math Code */
   IQmathTables     : > IQTABLES,  PAGE = 0, TYPE = NOLOAD 
   
   /* Uncomment the section below if calling the IQNexp() or IQexp()
      functions from the IQMath.lib library in order to utilize the 
      relevant IQ Math table in Boot ROM (This saves space and Boot ROM 
      is 1 wait-state). If this section is not uncommented, IQmathTables2
      will be loaded into other memory (SARAM, Flash, etc.) and will take
      up space, but 0 wait-state is possible.
   */
   /*
   IQmathTables2    : > IQTABLES2, PAGE = 0, TYPE = NOLOAD 
   {
   
              IQmath.lib<IQNexpTable.obj> (IQmathTablesRam)
   
   }
   */
   
   FPUmathTables    : > FPUTABLES, PAGE = 0, TYPE = NOLOAD 
         
   /* Allocate DMA-accessible RAM sections: */
   DMARAML4         : > RAML4,     PAGE = 1
 //  DMARAML5         : > RAML5,     PAGE = 1
  // DMARAML6         : > RAML6,     PAGE = 1
  // DMARAML7         : > RAML7,     PAGE = 1
   
   /* Allocate 0x400 of XINTF Zone 7 to storing data */
   ZONE7DATA        : > ZONE7B,    PAGE = 1

   /* .reset is a standard section used by the compiler.  It contains the */ 
   /* the address of the start of _c_int00 for C Code.   /*
   /* When using the boot ROM this section and the CPU vector */
   /* table is not needed.  Thus the default type is set here to  */
   /* DSECT  */ 
   .reset              : > RESET,      PAGE = 0, TYPE = DSECT
   vectors             : > VECTORS     PAGE = 0, TYPE = DSECT
   
   /* Allocate ADC_cal function (pre-programmed by factory into TI reserved memory) */
   .adc_cal     : load = ADC_CAL,   PAGE = 0, TYPE = NOLOAD

    crcblock        : > Flash_CRC16     PAGE = 0
    mapblock        : > Flash_MemMap    PAGE = 0
    verblock        : > Flash_VerBlk    PAGE = 0

}

/*===========================================================================
 End of file.
===========================================================================*/


