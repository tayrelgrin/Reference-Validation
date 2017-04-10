#pragma once
#include "afxcmn.h"


// Register 대화 상자입니다.

class Register : public CDialogEx
{
	DECLARE_DYNAMIC(Register)

public:
	Register(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Register();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_REGISTER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listRegister;
	virtual BOOL OnInitDialog();
};
