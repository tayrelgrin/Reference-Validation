#pragma once
#include "afxext.h"
#include "afxwin.h"
#include "InformationManager.h"
#include "afxcmn.h"
#include "BasicData.h"

// BaseItem 대화 상자입니다.

class BaseItem : public CDialogEx
{
	DECLARE_DYNAMIC(BaseItem)

public:
	BaseItem(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~BaseItem();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_BASEITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_cButton_BI_Add;
	CBitmapButton m_cButton_BI_Remove;
	CBitmapButton m_cButton_BI_LoadSetting;
	CBitmapButton m_cButton_BI_Reload;
	virtual BOOL OnInitDialog();
	CComboBox m_cComboFiles;
	afx_msg void OnCbnSelchangeCombo1();
	InformationManager* m_pData;
	CListCtrl m_ListCtrl_BaseItem;
	CString m_strFirstTestName;
	CString m_strRefFileName;
	CTreeCtrl m_TreeCtrl_BaseFile;
	afx_msg void OnNMClickTreeBi(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAdditembi();
	bool m_bModifyFlag;
	void AddBaseInfoItemToList();
	bool CheckExistSameData(HTREEITEM inData);
	afx_msg void OnBnClickedButtonDeleteitembi();
};
