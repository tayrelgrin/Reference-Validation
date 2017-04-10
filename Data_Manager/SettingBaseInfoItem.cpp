// SettingBaseInfoItem.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "SettingBaseInfoItem.h"
#include "afxdialogex.h"


// SettingBaseInfoItem 대화 상자입니다.

IMPLEMENT_DYNAMIC(SettingBaseInfoItem, CDialogEx)

SettingBaseInfoItem::SettingBaseInfoItem(CWnd* pParent /*=NULL*/)
	: CDialogEx(SettingBaseInfoItem::IDD, pParent)
{

}

SettingBaseInfoItem::~SettingBaseInfoItem()
{
}

void SettingBaseInfoItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(SettingBaseInfoItem, CDialogEx)
END_MESSAGE_MAP()


// SettingBaseInfoItem 메시지 처리기입니다.
