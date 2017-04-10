#pragma once
#include "afxcmn.h"
#include "afxext.h"
#include "CheckingFileList.h"
#include "Register.h"
#include "BaseItem.h"



// SettingBaseInfo 대화 상자입니다.

class SettingBaseInfo : public CDialogEx
{
	DECLARE_DYNAMIC(SettingBaseInfo)

public:
	SettingBaseInfo(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SettingBaseInfo();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_Setting };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_Tab;
	CBitmapButton m_cButton_Save;
	CBitmapButton m_cButton_EXIT;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSave();

	BaseItem m_TabBaseInfo;
	CheckingFileList m_TabFileList;
	Register m_TabRegister;
	CWnd* m_pwndShow;
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonExit();
};
