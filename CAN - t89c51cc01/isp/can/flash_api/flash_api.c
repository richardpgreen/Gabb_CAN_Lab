/*C**************************************************************************
* NAME: api_cc01.c  
*----------------------------------------------------------------------------
* CREATED_BY:    Jean-Sebastien Berthy
* CREATION_DATE: 15/01/2000 
* AUTHOR:        $Author: jberthy $
* REVISION       $Revision: 1.3 $
* DATE:          $Date: 2001/09/06 06:23:18 $
*----------------------------------------------------------------------------
* PURPOSE: 
* This file contains whole of functions to access T89C51CC01 Flash and EEPROM. 
*****************************************************************************/

/*_____ I N C L U D E S ____________________________________________________*/

#include "config.h"

/*_____ M A C R O S ________________________________________________________*/

/*_____ D E F I N I T I O N ________________________________________________*/

Uchar  data api_command 	_at_ 0x1C;
Uchar  data api_value 		_at_ 0x1D;
Uchar  data api_dpl 		_at_ 0x1F;
Uchar  data api_dph 		_at_ 0x1E;

 
#define MSK_AUXR1_ENBOOT	0x20
#define MAP_BOOT 			AUXR1 |= MSK_AUXR1_ENBOOT;
#define UNMAP_BOOT		AUXR1 &= ~MSK_AUXR1_ENBOOT;

#define __API_FLASH_ENTRY_POINT (*((const void(code*)(void)) 0xFFC0 ))
#define __API_JMP_ISP_START (*((const void(code*)(void)) 0xFF00 ))
#define __API_JMP_BOOTLOADER (*((const void(code*)(void)) 0xF800 ))

/*_____ D E C L A R A T I O N ______________________________________________*/


/*F**************************************************************************
* NAME: __api_rd_generic                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* Uchar command: api_command to call    
* Uchar dpl    : api_dpl
* return: 
* Uchar : read value
*----------------------------------------------------------------------------
* PURPOSE: 
* This function allows to read xaf and special area
*****************************************************************************
* NOTE: 
*****************************************************************************/
Uchar __api_rd_generic (Uchar command, Uchar dpl)
{
  api_command = command;
  api_dpl     = dpl;
	MAP_BOOT;
	__API_FLASH_ENTRY_POINT();
	UNMAP_BOOT;

  return(api_value);
}

/*F**************************************************************************
* NAME: __api_wr_generic                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* Uchar command: api_command to call    
* Uchar value  : api_value
* Uchar dpl    : api_dpl
* return: 
* Uchar return: command status (1 - ok)
*----------------------------------------------------------------------------
* PURPOSE: 
* This function allows to write in xaf
*****************************************************************************
* NOTE: 
*****************************************************************************/
Uchar __api_wr_generic (Uchar command, Uchar value, Uchar dpl)
{

  bit ea_save;

  ea_save = EA;
  EA = 0;
  api_command = command;
  api_dpl     = dpl;
  api_value   = value;
	MAP_BOOT;
	__API_FLASH_ENTRY_POINT();
	UNMAP_BOOT;
  EA = ea_save;    	// restore interrupt state
  return(1);

}


/*F**************************************************************************
* NAME: __api_rd_code_byte                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* Uint16 address : address in flash memory to read    
* return: 
* Uchar device : read value
*----------------------------------------------------------------------------
* PURPOSE: 
* This function allows to read a flash memory byte.
*****************************************************************************
* NOTE: 
* To use this function the constante __API_RD_CODE_BYTE must be define in 
* C header file api_cc01.h.
*****************************************************************************/
#ifdef __API_RD_CODE_BYTE
Uchar __api_rd_code_byte (Uchar code * pt_address)
{
  return(*pt_address);
}
#endif

/*F**************************************************************************
* NAME: __api_wr_code_byte                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* Uint16 address : address to program
* Uchar value : data to write   
* return: 
* Uchar return : 
*       return = 0x00 -> pass                            
*       return != 0x00 -> fail
*----------------------------------------------------------------------------
* PURPOSE: 
* This function allows to program data byte in Flash memory.
*****************************************************************************
* NOTE: 
* To use this function the constante __API_WR_CODE_BYTE must be define in 
* C header file api_cc01.h.
*****************************************************************************/
#ifdef __API_WR_CODE_BYTE
Uchar __api_wr_code_byte (Uchar xdata * pt_address, Uchar value)
{
  bit ea_save;

  ea_save = EA;
  EA = 0;
  api_command = _COMMAND_WR_CODE_BYTE;
	FCON = 0x08;

	*pt_address = value;

	MAP_BOOT;
	__API_FLASH_ENTRY_POINT();
	UNMAP_BOOT;
  EA = ea_save;    	// restore interrupt state

  return(api_value);
}
#endif

/*F**************************************************************************
* NAME: __api_wr_code_page                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* Uint16 add_flash : address of the first byte to program in the Flash
* Uint16 add_xram  : address in XRAM of the first data to program
* Uchar nb_data : number of bytes to program
* return: 
* Uchar return : 
*       return = 0x00 -> pass                            
*       return != 0x00 -> fail
*----------------------------------------------------------------------------
* PURPOSE: 
* This function allows to program until 128 Datas in Flash memory.
* Number of bytes to program is limited such as the Flash write remains in a
* single 128 bytes page. 
*****************************************************************************
* NOTE: 
* To use this function the constante __API_WR_CODE_PAGE must be define in 
* C header file api_cc01.h.
* This function used Dual Data Pointer DPTR0&1. At the end of this function 
* DPTR = DPTR0.
*****************************************************************************/
#ifdef __API_WR_CODE_PAGE
Uchar __api_wr_code_page (Uchar xdata * pt_code, Uchar xdata * pt_xram, Uchar nb_data)
{
  Uchar data i, temp, temp_nb_data;
  bit ea_save;
  Uint16  data add_pt_code, add_pt_xram;

	add_pt_xram = pt_xram;
	add_pt_code = pt_code;
  temp_nb_data = nb_data;
  ea_save = EA;
  EA = 0;
	api_command = _COMMAND_WR_CODE_BYTE;
	for (i=0 ; i< temp_nb_data; i++,add_pt_xram++,add_pt_code++)
	{
		temp = *(Uchar xdata *)add_pt_xram;
		FCON = 0x08;
		*(Uchar xdata *)add_pt_code = temp;
		FCON = 0x00;
	}

	MAP_BOOT;
	__API_FLASH_ENTRY_POINT();
	UNMAP_BOOT;
  EA = ea_save;    	// restore interrupt state
	
  return(api_value);
}
#endif

/*F**************************************************************************
* NAME: __api_wr_fuse                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* Uchar return : 
*----------------------------------------------------------------------------
* PURPOSE: 
*****************************************************************************
* NOTE: 
*****************************************************************************/
Uchar __api_wr_fuse (Uchar mask, Uchar filter)
{
  Uchar value;
  bit ea_save;

  ea_save = EA;
  EA = 0;
  value  = __api_rd_HSB();
  value &= ~mask;
 	api_value   = value | filter;
	api_command = _COMMAND_WR_FUSE_BIT;
	MAP_BOOT;
	__API_FLASH_ENTRY_POINT();
	UNMAP_BOOT;
  EA = ea_save;    	// restore interrupt state
	
  return(1);
}



/*F**************************************************************************
* NAME: api_erase_block                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* block_t num_block 
*         num_block = BLOCK_0 (erase Flash between 0x0000-0x1FFF)
*         num_block = BLOCK_1 (erase Flash between 0x2000-0x3FFF)
*         num_block = BLOCK_2 (erase Flash between 0x3000-0x7FFF)
*         num_block = BLOCK_3 (erase Flash between 0x8000-0xBFFF)
*         num_block = BLOCK_4 (erase Flash between 0xC000-0xFFFF)
* return: 
*----------------------------------------------------------------------------
* PURPOSE: 
* This function allows to erase Block in Flash.
*****************************************************************************
* NOTE: 
* To use this function the constante __API_ERASE_BLOCK must be define in
* C header file api_cc01.h.
*****************************************************************************/
#ifdef __API_ERASE_BLOCK
Uchar __api_erase_block (block_t num_block)
{
  bit ea_save;

  ea_save = EA;
  EA = 0;
  api_command = _COMMAND_ER_BLOCK;
  api_dph     = num_block;
	MAP_BOOT;
	__API_FLASH_ENTRY_POINT();
	UNMAP_BOOT;
  EA = ea_save;    	// restore interrupt state

  return(1);
}
#endif

/*F**************************************************************************
* NAME: api_eeprom_busy                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* return: 
* eeprom_t eep :  
*       eep = EEPROM_NOT_BUSY
*       eep = EEPROM_BUSY 
*----------------------------------------------------------------------------
* PURPOSE: 
* This function allows to check if eeprom is busy or not.
*****************************************************************************
* NOTE: 
* To use this function the constante __API_EEPROM_BUSY must be define in
* C header file api_cc01.h.
*****************************************************************************/
#ifdef __API_EEPROM_BUSY
eeprom_t __api_eeprom_busy (void)
{ 
	return(EECON & 0x01);
}
#endif

/*F**************************************************************************
* NAME: api_rd_eeprom                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* Uchar xdata *address : address to read
* return: 
*----------------------------------------------------------------------------
* PURPOSE: 
* This function allows to read a byte in Eeprom.
*****************************************************************************
* NOTE: 
* To use this function the constante __API_RD_EEPROM must be define in
* C header file api_cc01.h.
*****************************************************************************/
#ifdef __API_RD_EEPROM_BYTE
Uchar __api_rd_eeprom_byte(Uchar xdata *address)
{  
  Uchar val; 

  EECON = 0x02;
  val   = *address;  
  EECON = 0x00;

  return (val);
}
#endif

/*F**************************************************************************
* NAME: api_wr_eeprom_byte                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* Uchar xdata* address : address to read
* Uchar value : data to write
* return: 
*----------------------------------------------------------------------------
* PURPOSE: 
* This function allows to program a byte in Eeprom.
*****************************************************************************
* NOTE: 
* To use this function the constante __API_WR_EEPROM_BYTE must be define in
* C header file api_cc01.h.
*****************************************************************************/
#ifdef __API_WR_EEPROM_BYTE
Uchar __api_wr_eeprom_byte (Uchar xdata *address, Uchar value)
{
  bit ea_save;

  ea_save = EA;
  EA = 0;
  EECON = 0x02;
  *address = value;/* addr is a pointer to external data mem */
  EECON = 0x50;          
  EECON = 0xA0;
  EA = ea_save;
          
	return (1);
}
#endif

/*F**************************************************************************
* NAME: api_start_isp                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* return: 
*----------------------------------------------------------------------------
* PURPOSE: 
*****************************************************************************
* NOTE: 
* To use this function the constante __API_START_ISP must be define in
* C header file api_cc01.h.
*****************************************************************************/
#ifdef __API_START_ISP
void __api_start_isp (void)
{
	EA = 0;
	MAP_BOOT;
	__API_JMP_ISP_START();
}
#endif

/*F**************************************************************************
* NAME: api_start_bootloader                                            
*----------------------------------------------------------------------------
* AUTHOR: Jean-Sebastien Berthy 
*----------------------------------------------------------------------------
* PARAMS:  
* return: 
*----------------------------------------------------------------------------
* PURPOSE: 
*****************************************************************************
* NOTE: 
* To use this function the constante __API_START_BOOTLOADER must be define in
* C header file.
*****************************************************************************/
#ifdef __API_START_BOOTLOADER
void __api_start_bootloader (void)
{
	EA = 0;
	MAP_BOOT;
	__API_JMP_BOOTLOADER();
}
#endif
