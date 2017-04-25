#pragma once
#include "afxext.h"
#include "afxcmn.h"
#include "InformationManager.h"

// CheckingFileList ��ȭ �����Դϴ�.

class CheckingFileList : public CDialogEx
{
	DECLARE_DYNAMIC(CheckingFileList)

public:
	CheckingFileList(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CheckingFileList();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_FILELIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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
