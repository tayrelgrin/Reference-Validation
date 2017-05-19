#pragma once
#include <vector>
#include "afxwin.h"


// Config_Select_Dlg ��ȭ �����Դϴ�.

class Config_Select_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Config_Select_Dlg)

public:
	Config_Select_Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Config_Select_Dlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_CONFIG_SELECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	void SetValueFileList(std::vector<CString> inValueFiles);
	void AddPrjToCombo();
	void FindStringInVector(std::vector<CString> invData, CString inTarget, std::vector<CString>& outvData);
private:
	CString m_strProject;
	CString m_strBuild;
	CString m_strConfig;
	CString m_strDOE;
	std::vector<CString> m_vValueFiles;
public:
	CComboBox m_cCombo_Prj;
	CComboBox m_cCombo_Build;
	CComboBox m_cCombo_Config;
	CComboBox m_cCombo_DOE;
	afx_msg void OnCbnSelchangeComboPrj();
	afx_msg void OnCbnSelchangeComboBuild();
	afx_msg void OnCbnSelchangeComboConfig();
	afx_msg void OnCbnSelchangeComboDoe();
	afx_msg void OnBnClickedOk();
};
