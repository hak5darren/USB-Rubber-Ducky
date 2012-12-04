/*This file has been prepared for Doxygen automatic documentation generation.*/
/*! \file *********************************************************************
 *
 * \brief FAT 12/16/32 Services.
 *
 * This file defines a useful set of functions for file navigation.
 *
 * \author               Atmel Corporation: http://www.atmel.com \n
 *                       Support and FAQ: http://support.atmel.no/
 *
 *****************************************************************************/

/* Copyright (c) 2009 Atmel Corporation. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. The name of Atmel may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * 4. This software may only be redistributed and used in connection with an Atmel
 * AVR product.
 *
 * THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * EXPRESSLY AND SPECIFICALLY DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 */
#ifndef _NAVIGATION_H_
#define _NAVIGATION_H_

#include "fs_com.h"
#include "fat.h"

//! \name nav_filelist_set() options parameter
//! @{
#define  FS_FIND_NEXT      true     //!< move in list to next file
#define  FS_FIND_PREV      false    //!< move in list to previous file
//! @}


//**********************************************************************
//************************ String format select ************************

//! This function selects the UNICODE mode for all routines with FS_STRING parameter 
//!
//! @verbatim
//! If you have enabled the FS_ASCII AND FS_UNICODE define
//! then FS_STRING parameter can be a ASCII or UNICODE string.
//! @endverbatim
//!
void  nav_string_unicode( void );

//! This function selects the ASCII mode for all routines with FS_STRING parameter 
//!
//! @verbatim
//! If you have enabled the FS_ASCII AND FS_UNICODE define
//! then FS_STRING parameter can be a ASCII or UNICODE string.
//! @endverbatim
//!
void  nav_string_ascii( void );

//! This function selects the LENGTH string mode for all routines with FS_STRING parameter 
//!
//! @verbatim
//! In LENGTH string mode when you call a routine with FS_STRING parameter
//! only the size (16bits, unit ASCII or UNICODE) is returned in the first 16bits of string array.
//! @endverbatim
//!
void  nav_string_length_enable( void );

//! This function deselects the LENGTH string mode for all routines with FS_STRING parameter 
//!
//! @verbatim
//! In LENGTH string mode when you call a routine with FS_STRING parameter
//! only the size (16bits, unit ASCII or UNICODE) is returned in the first 16bits of string array.
//! @endverbatim
//!
void  nav_string_length_disable( void );

//**********************************************************************
//********************** To optimize speed access **********************

//! This function disables the disk check before each actions on disk
//!
//! @verbatim
//! By default, between each read/write access a check disk (test unit ready) is sended at device.
//! This check can reduce the speed access on specific disk.
//! @endverbatim
//!
void  nav_checkdisk_disable( void );

//! This function enables the disk check before each actions on disk
//!
//! @verbatim
//! By default, between each read/write access a check disk (test unit ready) is sended at device.
//! This check can reduce the speed access on specific disk.
//! @endverbatim
//!
void  nav_checkdisk_enable( void );


//**********************************************************************
//************** Initialise or Stop navigation module ****************** 


//! This function resets ALL navigations to init file system core
//!
//! @verbatim
//! Call this at the program startup or before a new session (e.g. USB Device exit)
//! @endverbatim
//!
void  nav_reset( void );

//! This function flush ALL navigations before exit of file system core
//!
//! @verbatim
//! Call this at the program exit or before a USB Device session
//! @endverbatim
//!
void  nav_exit( void );

//! This function selects the navigation to use
//!
//! @param     u8_idnav    navigator identifier to select (0 to FS_NB_NAVIGATOR-1)
//!
//! @return    false if ID navigator don't exist
//! @return    true otherwise
//!
Bool  nav_select( uint8_t u8_idnav );

//! This function returns the navigation identifier used
//!
//! @return    u8_idnav    navigator identifier selected
//!
uint8_t    nav_get( void );

//! This function copys the navigator information to another navigator
//!
//! @param     u8_idnav       navigator identifier where the main navigator will be copied
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
//! @verbatim
//! Use this routine to select quickly the same file in another navigator
//! @endverbatim
//!
Bool  nav_copy( uint8_t u8_idnav );


//**********************************************************************
//********************* Drive navigation functions *********************


//! This function returns the number of devices availabled
//!
//! @return    number of devices, 0 = NO DEVICE AVAILABLED
//!
//! @verbatim
//! This value may be dynamic because it depends of memory drivers (e.g. Mass Storage disk on USB host mode)
//! @endverbatim
//!
uint8_t    nav_drive_nb( void );

//! This function selects a drive in navigator but don't mount the disk partition
//!
//! @param     u8_number    device number (0 to nav_drive_nb()-1 )
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_drive_set( uint8_t u8_number );

//! This function returns the selected drive number
//!
//! @return    0 to nav_drive_nb()-1
//! @return    0xFF in case of no drive selected
//!
uint8_t    nav_drive_get( void );

//! This function returns the selected drive letter
//!
//! @return    'A','B',...
//! @return    'X', in case of no drive selected
//!
uint8_t    nav_drive_getname( void );

//! This function formats the current drive (=disk)
//!
//! @param     u8_fat_type    Select the format type<br>
//!            FS_FORMAT_DEFAULT, The system chooses the better FAT format <br>
//!            FS_FORMAT_FAT, The FAT12 or FAT16 is used to format the drive, if possible (disk space <2GB) <br>
//!            FS_FORMAT_FAT32, The FAT32 is used to format the drive, if possible (disk space >32MB) <br>
//!            FS_FORMAT_NOMBR_FLAG, if you don't want a MRB on the disk then add this flag (e.g. specific partition structure on a CD support)
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
//! @verbatim
//! WARNING: This routine can't format a multi-partiton, if the disk contains a multi-partition
//! then this one is erased and replaced by a single partition on ALL disk space.
//! @endverbatim
//!
Bool  nav_drive_format( uint8_t u8_fat_type );


//**********************************************************************
//******************* Partition navigation functions ******************* 


//! This function returns the number of partitions present on drive
//!
//! @return    u8_number   number of partitions
//!
uint8_t    nav_partition_nb( void );

//! This function selects a partition on drive
//!
//! @param     partition_number     partition number (0 to 3)
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_partition_set( uint8_t partition_number );

//! This function mounts the selected partition 
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
//! @verbatim
//! If the FS_MULTI_PARTITION option is disabled
//! then the mount routine selects the first partition supported by file system. <br>
//! After mount, the file list contains files and directories of ROOT directory 
//! @endverbatim
//!
Bool  nav_partition_mount( void );

//! This function gives the partition type
//!
//! @return partition type: FS_TYPE_FAT_12, FS_TYPE_FAT_16, FS_TYPE_FAT_32
//! @return FS_TYPE_FAT_UNM, in case of error or unknow format
//!
uint8_t    nav_partition_type( void );

//! This function reads or writes the serial number on the selected partition 
//!
//! @param     b_action    to select the action <br>
//!                        FS_SN_READ to read serial number <br>
//!                        FS_SN_WRITE to write serial number <br>
//! @param     a_u8_sn     pointer on an array (4 bytes) <br>
//!                        if FS_SN_READ, then the array is used to store the serial number <br>
//!                        if FS_SN_WRITE, then the array is used to give the new serial number <br>
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool  nav_partition_serialnumber( Bool b_action , uint8_t _MEM_TYPE_SLOW_ *a_u8_sn );

//! This function reads or writes the label of selected partition
//!
//! @param     b_action    to select the action <br>
//!                        FS_LABEL_READ to read label <br>
//!                        FS_LABEL_WRITE to write label <br>
//! @param     sz_label    pointer on a ASCII string (11 chars + NULL terminator =12 bytes) <br>
//!                        if FS_LABEL_READ, then the string is used to store label <br>
//!                        if FS_LABEL_WRITE, then the string is used to give the new label <br>
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_partition_label( Bool b_action , FS_STRING sz_label );

//! This function returns partition total space
//!
//! @return    number of sectors
//! @return    0, in case of error
//!
//! @verbatim
//! You shall mounted the partition before call this routine
//! @endverbatim
//!
uint32_t   nav_partition_space( void );

//! This function returns the partition cluster size
//!
//! @return    cluster size (unit sector)
//!
uint8_t    nav_partition_cluster_size( void );

//! This function returns the partition free space
//!
//! @return    number of free sectors
//! @return    0 in case of error or full partition
//!
//! @verbatim
//! You shall mounted the partition before call this routine
//! @endverbatim
//!
uint32_t   nav_partition_freespace( void );

//! This function returns the partition space free in percent
//!
//! @return    percent of free space (0% to 100%)
//! @return    0% in case of error or full partition
//!
//! @verbatim
//! To speed up the compute, the resultat have an error delta of 1%
//! @endverbatim
//!
uint8_t    nav_partition_freespace_percent( void );


//**********************************************************************
//****************** File list navigation functions ******************** 

//! To display in File List only the files OR directories
//!
//! @param     b_type   FS_DIR  to display only directories presence <br>
//!                     FS_FILE to dispaly only files presence <br>
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool  nav_filelist_single_enable( Bool b_type );

//! To display in File List the directories AND files
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool  nav_filelist_single_disable( void );

//! This function resets the selection pointer, so "no file selected" in file list
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool  nav_filelist_reset( void );

//! This function checks if a file is selected
//!
//! @return    true  if a file is selected
//! @return    false if no file is selected
//!
Bool  nav_filelist_validpos( void );

//! This function checks if no file is open
//!
//! @return    true  if no file is open
//! @return    false if a file is open
//!
Bool  nav_filelist_fileisnotopen( void );

//! This function moves the selection pointer in file list
//!
//! @param     u16_nb      numbers of file to jump before stopping action <br>
//!                        0, stop at the first file found <br>
//!                        1, stop at the second file found <br>
//!
//! @param     b_direction search direction <br>
//!                        FS_FIND_NEXT, move to next file or directory
//!                        FS_FIND_PREV, move to previous file or directory
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
//! @verbatim
//! Note: if no file is selected then nav_filelist_set( 0 , FS_NEXT ) goes to the first entry of the file list.
//! @endverbatim
//!
Bool  nav_filelist_set( uint16_t u16_nb , Bool b_direction );

//! This function returns the position of selected file in file list
//!
//! @return    position of selected file (0 is the first position)
//! @return    FS_NO_SEL, in case of no file selected
//!
uint16_t   nav_filelist_get( void );

//! This function goes at a position in file list
//!
//! @param     u16_newpos     new position to select (0 is the first position)
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_filelist_goto( uint16_t u16_newpos );

//! This function searchs a file name in file list 
//!
//! @param     sz_name        name to search (UNICODE or ASCII) <br>
//!                           It must be terminate by NULL or '*' value
//! @param     b_match_case   false to ignore the case
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
//! @verbatim
//! This function starts a search at the next position of the current in file list 
//! @endverbatim
//!
Bool  nav_filelist_findname( const FS_STRING sz_name , Bool b_match_case );

//! This function checks the end of file list
//!
//! @return    false, NO end of file list
//! @return    true, in case of end of list or error
//!
Bool  nav_filelist_eol( void );

//! This function checks the beginning of file list
//!
//! @return    false, it is not the beginning of file list
//! @return    true, in case of the file selected is the first file, or in case of error
//!
Bool  nav_filelist_bol( void );

//! This function checks the presence of files or directories in file list
//!
//! @param     b_type   FS_DIR  to check the directory presence <br>
//!                     FS_FILE to check the file presence <br>
//!
//! @return    true, in case of a file or a directory exists
//! @return    false, in case of no file or no directory exists, or error
//!
Bool  nav_filelist_exist( Bool b_type );

//! This function computes the number of files or directories in file list
//!
//! @param     b_type   FS_DIR  to compute the number of directories <br>
//!                     FS_FILE to compute the number of files <br>
//!
//! @return    number of files or directories in file list
//!
uint16_t   nav_filelist_nb( Bool b_type );

//! This function goes to at the first file or directory in file list
//!
//! @param     b_type   FS_DIR  to go at the first directory <br>
//!                     FS_FILE to go at the first file <br>
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool  nav_filelist_first( Bool b_type );

//! This function goes to at the last file or directory in file list
//!
//! @param     b_type   FS_DIR  to go at the last directory <br>
//!                     FS_FILE to go at the last file <br>
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool  nav_filelist_last( Bool b_type );

//**********************************************************************
//************************ Index functions *****************************


//! This function returns a small index on the selected file
//!
//! @return    It is a small index structure with information on selected file (disk, partition, dir, file/dir selected)
//!
//! @verbatim
//! This routine is interresting to save a file position in small variable.
//! This pointer allow to reinit a navigator quickly with nav_gotoindex() routine.
//! @endverbatim
//!
Fs_index nav_getindex( void );

//! This function selects a file in the navigator via a file index
//!
//! @param     index       structure with information about file to select (disk, partition, dir, file/dir selected )
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
//! @verbatim
//! This routine allow to reinit a navigator quickly via a file index (disk, partition, dir, file/dir selected )
//! To get a file index, you shall used the routine nav_getindex().
//! @endverbatim
//!
Bool  nav_gotoindex( const Fs_index _MEM_TYPE_SLOW_ *index );

//**********************************************************************
//************************ Directory functions *************************


//! This function initializes the file list on the root directory
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool  nav_dir_root( void );

//! This function check the current directory
//!
//! @return  false the current directory selected is not the root directory
//! @return  true  the current directory selected is the root directory
//!
Bool  nav_dir_is_root( void );

//! This function enters in the selected directory in file list
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
//! @verbatim
//! After this routine the file list changes and contains the files and directories of the new directory.
//! By default no file is selected.
//! @endverbatim
//!
Bool  nav_dir_cd( void );

//! This function goes to the parent directory
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
//! @verbatim
//! After, the file list changes and contains the files and directories of the new directory.
//! By default, the file selected in file list is the previous (children) directory.
//! @endverbatim
//!
Bool  nav_dir_gotoparent( void );

//! This function returns the directory name corresponding at the file list
//!
//! @param     sz_path        string to store the name (ASCII or UNICODE )
//! @param     u8_size_max    string size (unit ASCII or UNICODE )
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_dir_name( FS_STRING sz_path  , uint8_t u8_size_max  );

//! This function creates a directory in the directory corresponding at file list
//!
//! @param     sz_name     directory name (ASCII or UNICODE )
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_dir_make( const FS_STRING sz_name  );

//! This function returns the full path of the selection
//!
//! @param     sz_path              string to store the path (ASCII or UNICODE )
//! @param     u8_size_path         string size (unit ASCII or UNICODE )
//! @param     b_view_file_select   true, to include in path the selected file name
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_getcwd( FS_STRING sz_path  , uint8_t u8_size_path , Bool b_view_file_select  );

//! This function selects a disk position via a path
//!
//! @param     sz_path           path string (ASCII or UNICODE )
//! @param     b_match_case      false to ignore the case
//! @param     b_create          true, if path no exists then create it <br>
//!                              false, no create path <br>
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
//! @verbatim
//! The syntact "./../../file_name" is supported.
//! With syntact "./dir_parent/directory_name"  the file list corresponding at "dir_parent" and "directory_name" is selected.
//! With syntact "./dir_parent/directory_name/" the file list corresponding at "directory_name" and no file is selected.
//! @endverbatim
//!
Bool  nav_setcwd( FS_STRING sz_path , Bool b_match_case , Bool b_create );


//**********************************************************************
//*********************** File control functions ***********************


//! This function returns the name of selected file
//!
//! @param     sz_name        string to store the name file (ASCII or UNICODE ) <br>
//! @param     u8_size_max    string size (unit ASCII or UNICODE )
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool nav_file_getname( FS_STRING sz_name, uint8_t u8_size_max );

//! This function returns the name of selected file or checks the string with the name of selected file 
//!
//! @param     b_mode         action mode: <br>
//!                           FS_NAME_GET    to get the name of selected file <br>
//!                           FS_NAME_CHECK  to check the name of selected file <br>
//! @param     sz_name        if FS_NAME_GET    then string to store the file name (ASCII or UNICODE ) <br>
//!                           if FS_NAME_CHECK  then string to match with file name (ASCII or UNICODE),
//!                                             it must be terminated by NULL or '*' value <br>
//! @param     b_match_case   false, ignore the case (only used in "FS_NAME_CHECK" action)
//!
//! @param     u8_size_max    string size (unit ASCII or UNICODE ), only used in "FS_NAME_GET" action
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool  nav_file_name( FS_STRING sz_name , uint8_t u8_size_max , Bool b_mode , Bool b_match_case  );

//! This function returns the size of selected file (unit byte)
//!
//! @return    Size of selected file (unit byte)
//!
uint32_t   nav_file_lgt( void );

//! This function returns the size of selected file (unit sector)
//!
//! @return    Size of selected file (unit 512B)
//!
uint16_t   nav_file_lgtsector( void );

//! This function checks the write protection of disk and the attribut "read only" of selected file
//!
//! @return    false, it is possible to modify the selected file
//! @return    true, in other case
//!
Bool  nav_file_isreadonly( void );

//! This function returns the type of selected file
//!
//! @return    true, it is a directory
//! @return    false, in other case
//!
Bool  nav_file_isdir( void );

//! This function checks the extension of selected file
//!
//! @param     sz_filterext   extension filter (ASCII format, e.g.: "txt" or "txt,d*,wk" )
//!
//! @return    true, the file extension match with extension filter
//! @return    false, in other case
//!
Bool  nav_file_checkext( const FS_STRING sz_filterext );

//! This function returns the date of selected file
//!
//! @param     type_date      FS_DATE_LAST_WRITE,  to get the date of last write access <br>
//!                           FS_DATE_CREATION,    to get the date of file creation
//! @param     sz_date        ASCCI string (>17B) to store the information about date <br>
//!                           "YYYYMMDDHHMMSSMS" = year, month, day, hour, minute, seconde, miliseconde
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_file_dateget( FS_STRING sz_date , Bool type_date );

//! This function returns the attribut of selected file
//!
//! @return    attribut of selected file, see masks "FS_ATTR_" in fs_com.h file.
//!
uint8_t    nav_file_attributget( void );

//! This function changes the date of selected file
//!
//! @param     type_date      FS_DATE_LAST_WRITE,  to get the date of last write access <br>
//!                           FS_DATE_CREATION,    to get the date of file creation
//! @param     sz_date        ASCCI string contains the date to write<br>
//!                           "YYYYMMDDHHMMSSMS" = year, month, day, hour, minute, seconde, miliseconde
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_file_dateset( const FS_STRING sz_date , Bool type_date );

//! This function changes the attribut of selected file
//!
//! @param   u8_attribut   value to write on selected file, see masks "FS_ATTR_" in fs_com.h file.
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
Bool  nav_file_attributset( uint8_t u8_attribut );

//! This function deletes the selected file or directory
//!
//! @param     b_only_empty      true, delete the directory only if empty <br>
//!                              false, delete directories and files include in selected directory <br>
//!                              If the selection is not a directory then this param is ignored.
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_file_del( Bool b_only_empty );
  
//! This function renames the selected directory or file
//!
//! @param     sz_name     new name (ASCII or UNICODE )
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
Bool  nav_file_rename( const FS_STRING sz_name  );

//! This function creates a file with NULL size and NULL attribut
//!
//! @param     sz_name     file name to create (ASCII or UNICODE )
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
//! @verbatim
//! If you ues this routine to create a file, then you must called file_open() to open this new file
//! @endverbatim
//!
Bool  nav_file_create( const FS_STRING sz_name  );

//! This function updates the COPY navigator with the selected file
//!
//! @return  false in case of error, see global value "fs_g_status" for more detail
//! @return  true otherwise
//!
//! @verbatim
//! If you use the COPY navigator after this routine then the copy information is lost (see FS_NAV_ID_COPYFILE in conf_explorer.h).
//! @endverbatim
//!
Bool  nav_file_copy( void );

//! This function pastes the selected file in COPY navigator in the file list of the current navigator
//!
//! @param     sz_name     file name of the new file (ASCII or UNICODE )
//!
//! @return    false in case of error, see global value "fs_g_status" for more detail
//! @return    true otherwise
//!
//! @verbatim
//! After this routine, you shall called nav_file_paste_state() to run and way the copy
//! @endverbatim
//!
Bool  nav_file_paste_start( const FS_STRING sz_name  );

//! This function executes the copy file
//!
//! @param     b_stop      set true to stop copy action
//!
//! @return    copy status <br>
//!            COPY_BUSY,     copy running
//!            COPY_FAIL,     copy fail
//!            COPY_FINISH,   copy finish
//!
uint8_t    nav_file_paste_state( Bool b_stop );

#endif  // _NAVIGATION_H_
