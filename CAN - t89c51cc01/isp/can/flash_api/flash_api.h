/*H***************************************************************************
* NAME: flash_api.h 
*----------------------------------------------------------------------------
* CREATED_BY:    Jean-sébastien Berthy
* CREATION_DATE: 13/12/2000   
* AUTHOR:        
* REVISION       
* DATE:         
*----------------------------------------------------------------------------
* PURPOSE: 
*****************************************************************************/
#ifndef _FLASH_API_H_
#define _FLASH_API_H

/*_____ I N C L U D E S ____________________________________________________*/

/*_____ M A C R O S ________________________________________________________*/

/* 
* These constants are used to compiled or not the corresponding function 
*
* #define __API_RD_DEVICE_DATA  => function __api_rd_device_data compiled
* #undef  __API_RD_HSB		=> function __api_rd_HSB not compiled
*/

#define  __API_RD_CODE_BYTE
#define  __API_WR_CODE_BYTE
#define  __API_WR_CODE_PAGE
#define  __API_ERASE_BLOCK

#define  __API_RD_BOOT_VERSION
#define  __API_RD_BSB
#define  __API_RD_SBV
#define  __API_RD_EB
#define  __API_RD_DEVICE_DATA
#define  __API_RD_DEVICE_ID1
#define  __API_RD_DEVICE_ID2
#define  __API_RD_DEVICE_ID3
#define  __API_RD_HSB
#define  __API_RD_MANUFACTURER
#define  __API_RD_SSB
#define  __API_RD_BTC_1
#define  __API_RD_BTC_2
#define  __API_RD_BTC_3
#define  __API_RD_NNB
#define  __API_RD_CRIS

#define  __API_WR_BSB
#define  __API_WR_SBV
#define  __API_WR_SSB
#define  __API_WR_EB
#define  __API_WR_BTC_1
#define  __API_WR_BTC_2
#define  __API_WR_BTC_3
#define  __API_WR_NNB
#define  __API_WR_CRIS

#define  __API_ERASE_SBV

#define	 __API_SET_X2
#define  __API_CLR_X2
#define  __API_SET_BLJB
#define  __API_CLR_BLJB

#define  __API_EEPROM_BUSY
#define  __API_RD_EEPROM_BYTE
#define  __API_WR_EEPROM_BYTE

#define  __API_START_BOOTLOADER
#define  __API_START_ISP


// Constante value for api_command.
#define _COMMAND_ER_BLOCK				0
#define _COMMAND_WR_CODE_BYTE		13
#define _COMMAND_WR_CODE_PAGE		13
#define _COMMAND_WR_XAF					4
#define _COMMAND_RD_XAF					5
#define _COMMAND_WR_FUSE_BIT		7
#define _COMMAND_RD_HW					8
#define _COMMAND_RD_SPECIAL  		14

#define MSK_CMOD_WDTE	0x40

/*_____ D E F I N I T I O N ________________________________________________*/

typedef enum {	
		NO_SECURITY = 0xFF,
		WR_SECURITY = 0xFE,
		RD_WR_SECURITY = 0xFC
	} ssb_t;

typedef enum {
		BLOCK_0 = 0x00,
    BLOCK_1 = 0x20,
    BLOCK_2 = 0x40,
    BLOCK_3 = 0x80,
    BLOCK_4 = 0xC0 } block_t;

typedef enum {	
		EEPROM_NOT_BUSY, 
		EEPROM_BUSY     }eeprom_t;


/*_____ D E C L A R A T I O N ______________________________________________*/



extern Uchar __api_rd_generic (Uchar command, Uchar dpl);
extern Uchar __api_wr_generic (Uchar command, Uchar value, Uchar dpl);
extern Uchar __api_wr_fuse (Uchar mask, Uchar filter);


/*---- API for Read access  ------------------------------------------------*/
/****************************************************************************/
#ifdef __API_RD_BSB
  #define __api_rd_BSB() 					__api_rd_generic(_COMMAND_RD_XAF, 0x00)
#endif

#ifdef __API_RD_SBV
	#define __api_rd_SBV() 					__api_rd_generic(_COMMAND_RD_XAF, 0x01)
#endif

#ifdef __API_RD_SSB
	#define __api_rd_SSB() 					__api_rd_generic(_COMMAND_RD_XAF, 0x05)
#endif

#ifdef __API_RD_EB
	#define __api_rd_EB() 					__api_rd_generic(_COMMAND_RD_XAF, 0x06)
#endif

#ifdef __API_RD_BTC_1
	#define __api_rd_BTC_1() 					__api_rd_generic(_COMMAND_RD_XAF, 0x1C)
#endif

#ifdef __API_RD_BTC_2
	#define __api_rd_BTC_2() 					__api_rd_generic(_COMMAND_RD_XAF, 0x1D)
#endif

#ifdef __API_RD_BTC_3
	#define __api_rd_BTC_3() 					__api_rd_generic(_COMMAND_RD_XAF, 0x1E)
#endif

#ifdef __API_RD_NNB
	#define __api_rd_NNB() 					__api_rd_generic(_COMMAND_RD_XAF, 0x1F)
#endif

#ifdef __API_RD_CRIS
	#define __api_rd_CRIS() 					__api_rd_generic(_COMMAND_RD_XAF, 0x20)
#endif

#ifdef __API_RD_HSB
	#define __api_rd_HSB() 					__api_rd_generic(_COMMAND_RD_HW, 0x00)
#endif

#ifdef __API_RD_MANUFACTURER 
	#define __api_rd_manufacturer() __api_rd_generic(_COMMAND_RD_XAF, 0x30)
#endif

#ifdef __API_RD_DEVICE_ID1
	#define __api_rd_device_id1() 	__api_rd_generic(_COMMAND_RD_XAF, 0x31)
#endif

#ifdef __API_RD_DEVICE_ID2
	#define __api_rd_device_id2() 	__api_rd_generic(_COMMAND_RD_XAF, 0x60)
#endif

#ifdef __API_RD_DEVICE_ID3
	#define __api_rd_device_id3() 	__api_rd_generic(_COMMAND_RD_XAF, 0x61)
#endif

#ifdef __API_RD_BOOT_VERSION
	#define __api_rd_bootloader_version() 	__api_rd_generic(_COMMAND_RD_SPECIAL, 0x00)
#endif

extern Uchar __api_rd_code_byte (Uchar code * pt_address);


/*---- API for Write access  -----------------------------------------------*/
/****************************************************************************/

extern Uchar __api_wr_code_byte (Uchar xdata* , Uchar);
extern Uchar __api_wr_code_page (Uchar xdata* pt_code, Uchar xdata* pt_xram, Uchar nb_data);

#ifdef __API_WR_BSB
	#define __api_wr_BSB(value) 		__api_wr_generic(_COMMAND_WR_XAF, value, 0)
#endif

#ifdef __API_WR_SBV
	#define __api_wr_SBV(value) 		__api_wr_generic(_COMMAND_WR_XAF, value, 1)
#endif

#ifdef __API_WR_SSB
	#define __api_wr_SSB(value) 		__api_wr_generic(_COMMAND_WR_XAF, value, 5)
#endif

#ifdef __API_WR_EB
	#define __api_wr_EB(value) 			__api_wr_generic(_COMMAND_WR_XAF, value, 6)
#endif

#ifdef __API_WR_BTC_1
	#define __api_wr_BTC_1(value) 	__api_wr_generic(_COMMAND_WR_XAF, value, 0x1C)
#endif

#ifdef __API_WR_BTC_2
	#define __api_wr_BTC_2(value) 	__api_wr_generic(_COMMAND_WR_XAF, value, 0x1D)
#endif

#ifdef __API_WR_BTC_3
	#define __api_wr_BTC_3(value) 	__api_wr_generic(_COMMAND_WR_XAF, value, 0x1E)
#endif

#ifdef __API_WR_NNB
	#define __api_wr_NNB(value) 		__api_wr_generic(_COMMAND_WR_XAF, value, 0x1F)
#endif

#ifdef __API_WR_CRIS
	#define __api_wr_CRIS(value) 		__api_wr_generic(_COMMAND_WR_XAF, value, 0x20)
#endif

#ifdef __API_ERASE_SBV
	#define __api_erase_SBV() 			__api_wr_generic(_COMMAND_WR_XAF, 0xFF, 1)
#endif

#ifdef __API_SET_X2
	#define __api_set_X2()					__api_wr_fuse(0x80, 0x80)
#endif

#ifdef __API_CLR_X2
	#define __api_clr_X2()					__api_wr_fuse(0x80, 0x00)
#endif

#ifdef __API_SET_BLJB
	#define __api_set_BLJB()				__api_wr_fuse(0x40, 0x40)
#endif

#ifdef __API_CLR_BLJB
	#define __api_clr_BLJB()				__api_wr_fuse(0x40, 0x00)	
#endif

extern Uchar __api_erase_block (block_t);

/*---- API for EEPROM access  ----------------------------------------------*/
/****************************************************************************/

#ifdef __API_EEPROM_BUSY
  extern eeprom_t __api_eeprom_busy (void);
#endif

#ifdef __API_RD_EEPROM_BYTE
  extern Uchar __api_rd_eeprom_byte	(Uchar xdata *);
#endif

#ifdef __API_WR_EEPROM_BYTE
  extern Uchar __api_wr_eeprom_byte	(Uchar xdata *, Uchar);
#endif

/*---- API to start bootloader execution  ----------------------------------*/
/****************************************************************************/

#ifdef __API_START_BOOTLOADER
  extern void __api_start_bootloader (void);
#endif

#ifdef __API_START_ISP
  extern void __api_start_isp (void);
#endif

#endif 