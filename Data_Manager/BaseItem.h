#pragma once
#include "afxext.h"


// BaseItem ��ȭ �����Դϴ�.

class BaseItem : public CDialogEx
{
	DECLARE_DYNAMIC(BaseItem)

public:
	BaseItem(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~BaseItem();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_BASEITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_cButton_BI_Add;
	CBitmapButton m_cButton_BI_Remove;
	CBitmapButton m_cButton_BI_LoadSetting;
	CBitmapButton m_cButton_BI_Reload;
	virtual BOOL OnInitDialog();
};
