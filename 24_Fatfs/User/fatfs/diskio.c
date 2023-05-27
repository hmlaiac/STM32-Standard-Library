/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
#include ".\spi\bsp_spi.h"


/* Definitions of physical drive number for each drive */
//#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
//#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
//#define USB		2	/* Example: Map USB MSD to physical drive 2 */
#define SPI_FLASH						0
#define SD_CARD							1

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case SPI_FLASH :
		result = RES_OK;
		SPI_CONFIG();
		SPI_Release_Power_Down();
		// translate the reslut code here
		stat = RES_OK;
		return stat;

	case SD_CARD :
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case SPI_FLASH :
		result = RES_OK;
		SPI_CONFIG();
		// translate the reslut code here
		stat = RES_OK;
		return stat;

	case SD_CARD :
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case SPI_FLASH :
		// translate the arguments here
		SPI_Read_data(buff, sector, count*0x1000);
		result = RES_OK;

		// translate the reslut code here

		return res;

	case SD_CARD :
		// translate the arguments here

		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case SPI_FLASH :
		// translate the arguments here
		BufferWrite((uint8_t*)buff, sector, count*0x1000);
		result = RES_OK;

		// translate the reslut code here
		
		return res;

	case SD_CARD :
		// translate the arguments here



		// translate the reslut code here

		return res;
	}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	int result;

	switch (pdrv) {
	case SPI_FLASH :

		// Process of the command for the ATA drive

		return res;

	case SD_CARD :

		// Process of the command for the MMC/SD card

		return res;
	}

	return RES_PARERR;
}
#endif
