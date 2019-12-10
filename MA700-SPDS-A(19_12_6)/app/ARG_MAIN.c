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
*     Module Description:  Module that pass control from ASM to C             *
*     Module Name:         %name:      arg_main.c %                           *
*     Module Version:      %version:   2 %                                    *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Compiler:    CCS 5.4                                                    *
*                                                                             *
*     Controller:  TMS320F28335                                               *
*                                                                             *
*-----------------------------------------------------------------------------*
*                                                                             *
*     Creator:    ZYR 2014-1-4                                                *
*     Author:                                                                 *
*                 %created_by:  maolei %                                      *
*                                                                             *
*     Date:       %date_modified:  Fri Apr 20 13:01:31 2012 %                 *
*                                                                             *
*******************************************************************************/
/******************************************************************************/
/*                                                                            */
/* This function is called from boot.asm or boot.c.                           */
/* To pass the control from ASM to c main function                            */
/*                                                                            */
/******************************************************************************/
#include "ARG_MAIN.h"

void arg_main_abort( void );

void arg_main_Exit( int status );

int _arg_main_Sched( void );

/*******************************************************************************
* Function:      _arg_main_Sched
*
* Description:   call the main function after c environment is initialized
*
* Parameters:    NONE
*
* Return values: int
*******************************************************************************/
int _arg_main_Sched( void )
{
 /* register int    argc = 0;
    register char **argv = 0;
    Don't need to pass parameters to main */

    return main();
}

/*******************************************************************************
* Function:      arg_main_Exit
*
* Description:   PROGRAM TERMINATION. called when the main loop is terminated
*
* Parameters:    NONE
*
* Return values: NONE
*******************************************************************************/
void arg_main_Exit( int status )
{
    arg_main_abort();
}

/*******************************************************************************
* Function:      arg_main_abort
*
* Description:   Halts execution after program terminated.
*
* Parameters:    NONE
*
* Return values: NONE
*******************************************************************************/
void arg_main_abort( void )
{
    while(1){};   /* SPINS FOREVER */
}
