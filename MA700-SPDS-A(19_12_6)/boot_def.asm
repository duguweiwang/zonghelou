;/*
; * Boot_def.asm
; *
; *  Created on: 2014-3-4
; *      Author: zhengyong
; */

;/****** Define for CRC  Block ******/
	.sect "crcblock"
	.global CRC16_Value
CRC16_Value  .word 0x0F04
Valid_Flag   .word 0x0055

;/****** Define for Flash Map Table ******/
	.sect "mapblock"
StartAddr	.word 0x0030,0x0000
EndAddr	    .word 0x0030,0x93BF

;/****** Define for Verstion String ******/
	.sect "verblock"
VerVendor	 .word "SAE"             ;3:
VerLoadType	 .word "001"             ;3:  Software Control Number:
                                     ;    "001":CPAsApp; "002":DCPapp; "003":BootLoader
VerDashNum   .word "1"               ;1:  Software Dash Number
VerVersion   .word "0003"            ;4:  Verstion Number xxxx
VerPartDesc  .word "CPA,ATA33-10"    ;12: Software Part Description

VerLRUID	 .word "0000"            ;4:  LRU ID
VerHwRevN    .word "00"              ;2:  Hardware Revision table count
VerHwRevT    .word "000000000000"    ;12: Hardware Revision Table
VerReserved0 .word 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF   ;7:
			 .word 0xFFFF,0xFFFF

VerDate      .word "2014-11-13"      ;10: date
VerSpace2    .word " "               ;1:
VerTime      .word "10:25:09"        ;8:  Time
VerReserved1 .word 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF   ;13:
			 .word 0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF
			 .word 0xFFFF,0xFFFF,0xFFFF
	.end

