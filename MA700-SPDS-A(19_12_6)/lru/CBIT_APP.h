/****************************************************************************
*                                                                           *
*                         COPYRIGHT (C)   SAE      	    					*
*                         ALL RIGHTS RESERVED                               *
*                                                                           *
*    The copying, use, distribution or disclosure of the confidential and   *
*    proprietary information contained in this document(s) is strictly      *
*    prohibited without prior written consent. Any breach shall subject     *
*    the infringing party to remedies. The owner reserves all rights in     *
*    the event of the grant of a patent or the registration of a utility    *
*    model or design.                                                       *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*     Module Description:  module to provide a realtime scheduler	        *
*     Module Name:         %name:     CBIT_APP.h %                          *
*     Module Version:      %version:  1 %                                   *
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*     Compiler:	  		                                          			*
*                                                                           *
*     Controller:                                             				*
*                                                                           *
*---------------------------------------------------------------------------*
*                                                                           *
*     Author:                                  								*
*				  %created_by:       mason                                  *
*									                                        *
*     Date:       %date_modified:  2014-12-03 %                 			*
*                                                                           *
****************************************************************************/
#ifndef __CBIT_APP_H__
#define __CBIT_APP_H__

#include "DEVICE.h"
#include "DEVICE_cfg.h"


/*extern void CBIT_APP_Init(void);*/

extern void CBIT_APP_Process(void);
extern UNUM16 CBIT_APP_Test(void);






#endif
/***************************************************************************
End of file.
***************************************************************************/
