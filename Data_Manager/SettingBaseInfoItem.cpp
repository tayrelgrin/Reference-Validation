// SettingBaseInfoItem.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "SettingBaseInfoItem.h"
#include "afxdialogex.h"


// SettingBaseInfoItem ��ȭ �����Դϴ�.

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


// SettingBaseInfoItem �޽��� ó�����Դϴ�.
