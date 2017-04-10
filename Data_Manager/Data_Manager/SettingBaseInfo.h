#pragma once
#include "afxcmn.h"
#include "afxext.h"
#include "CheckingFileList.h"
#include "Register.h"
#include "BaseItem.h"



// SettingBaseInfo ��ȭ �����Դϴ�.

class SettingBaseInfo : public CDialogEx
{
	DECLARE_DYNAMIC(SettingBaseInfo)

public:
	SettingBaseInfo(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SettingBaseInfo();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_Setting };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
