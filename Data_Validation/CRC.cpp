#include "StdAfx.h"
#include "CRC.h"


CCRC::CCRC(void)
{
}


CCRC::~CCRC(void)
{
}


BOOL CCRC::GetFileCRC32( IN CString In_strPath, OUT int& Out_nCRC )
{
	CCRC32 CCRC_Data;

	if( !CCRC_Data.DoCRC( IN (LPSTR)(LPCTSTR)In_strPath , OUT Out_nCRC ) ) return FALSE;
	else return TRUE;
}