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

	int i = strDirecPath.ReverseFind('\\');//���� ���� �̸��� ����� ���ؼ� ���ʿ� �ִ� '/'�� ã�´�.

	strDirecPath = strDirecPath.Left(i);//�ڿ� �ִ� ���� ���� ���� �̸��� �����.

	return strDirecPath;
}