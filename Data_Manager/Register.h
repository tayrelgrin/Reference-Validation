#pragma once
#include "afxcmn.h"


// Register ��ȭ �����Դϴ�.

class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Register();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listRegister;
	virtual BOOL OnInitDialog();
};
