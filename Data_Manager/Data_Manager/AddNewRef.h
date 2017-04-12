#pragma once
#include "ConfigDMData.h"
#include "afxeditbrowsectrl.h"
#include <vector>
#include "afxwin.h"



// AddNewRef ��ȭ �����Դϴ�.

class AddNewRef : public CDialogEx
{
	DECLARE_DYNAMIC(AddNewRef)

public:
	AddNewRef(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~AddNewRef();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddcancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioRef();
	afx_msg void OnBnClickedRadioUsedata();	
	afx_msg void OnEnChangeMfceditbrowse1();
	void GetDirList( std::vector<CString>& inVDirList);
	void CopyConfigData(ConfigDMData inData);
	void EditBoxSetting();
	void InitAllData();
private:
	CString m_strBuild;
	CString m_strDOE;
	CString m_strConfig;
	CString m_strPrj;
	CString m_strDirRootPath;
	ConfigDMData m_cNewConfig;
	CMFCEditBrowseCtrl m_editCtrl;
	std::vector<CString> m_vStrDir;
public:
	CEdit m_EditPrj;
	CEdit m_EditBuild;
	CEdit m_EditConfig;
	CEdit m_EditDOE;
	afx_msg void OnBnClickedButtonAddok();
	CString GetBuild();
	CString GetProject();
	CString GetConfig();
	CString GetDOE();
	CString GetDirRootPath();
};
