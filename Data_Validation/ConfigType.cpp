#include "StdAfx.h"
#include "ConfigType.h"


ConfigType::ConfigType(void)
{
}


ConfigType::~ConfigType(void)
{
}


CString ConfigType::GetEXEDirectoryPath()
{
	CString strDirecPath;
	strDirecPath.Format("");
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	strDirecPath = path;

	int i = strDirecPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	strDirecPath = strDirecPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.

	return strDirecPath;
}