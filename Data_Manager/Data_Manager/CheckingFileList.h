#pragma once
#include "afxext.h"
#include "afxcmn.h"
#include "InformationManager.h"

// CheckingFileList 대화 상자입니다.

class CheckingFileList : public CDialogEx
{
	DECLARE_DYNAMIC(CheckingFileList)

public:
	CheckingFileList(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CheckingFileList();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_FILELIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CBitmapButton m_cButton_LoadSetting;
	CBitmapButton m_cButton_Reload;
	afx_msg void OnBnClickedButtonLsfl();
	afx_msg void OnBnClickedButtonAdditem();
	CBitmapButton m_cButton_Add;
	CBitmapButton m_cButton_Remove;
	afx_msg void OnBnClickedButtonDeleteitem();
	CTreeCtrl m_treectrlFileList;
	CListCtrl m_ListctrlFileList;
	void AddFileNameToTreeView(CTreeCtrl& incTarget);
	InformationManager* m_pData;
	std::vector<CString> m_vConfigFileList;
	std::vector<CString> m_vSettingFileList;
	void AddFileNameToListview();
};
