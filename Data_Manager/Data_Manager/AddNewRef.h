#pragma once
#include "ConfigDMData.h"
#include "afxeditbrowsectrl.h"
#include <vector>
#include "afxwin.h"
#include <Windows.h>


// AddNewRef 대화 상자입니다.

class AddNewRef : public CDialogEx
{
	DECLARE_DYNAMIC(AddNewRef)

public:
	AddNewRef(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~AddNewRef();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddcancel();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedRadioRef();
	afx_msg void OnBnClickedRadioUsedata();	
	afx_msg void OnEnChangeMfceditbrowse1();
	afx_msg void OnBnClickedButtonAddok();
	afx_msg void OnCbnSetfocusCombo1();
	afx_msg void OnCbnSetfocusCombo3();
	afx_msg void OnCbnSetfocusCombo4();
	afx_msg void OnCbnSetfocusCombo2();

	CString GetBuild();
	CString GetProject();
	CString GetConfig();
	CString GetDOE();
	CString GetPreBuild();
	CString GetPreProject();
	CString GetPreConfig();
	CString GetPreDOE();
	bool CheckRefEffective(CString instrPath, std::vector<CString> invData);

	CString GetDirRootPath();
	void GetDirList( std::vector<CString>& inVDirList);
	void EditBoxSetting();
	void InitAllData();
	void LoadFileListInValue();
	void ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE);
	void AddProjectToCombo();
	void FindStringInVector(std::vector<CString> invData, CString inTarget, std::vector<CString>& outvData);
	void FileCopy();
	bool GetPreDataUsed();
private:
	CString m_strBuild;
	CString m_strDOE;
	CString m_strConfig;
	CString m_strPrj;
	CString m_strPreBuild;
	CString m_strPreDOE;
	CString m_strPreConfig;
	CString m_strPrePrj;
	CString m_strDirRootPath;
	ConfigDMData m_cNewConfig;
	CMFCEditBrowseCtrl m_editCtrl;
	std::vector<CString> m_vStrDir;
	std::vector<CString> m_vConfigName;
	bool bPreDataUsed;
	bool bEffectiveResult;
public:
	CEdit m_EditPrj;
	CEdit m_EditBuild;
	CEdit m_EditConfig;
	CEdit m_EditDOE;

	CComboBox m_cComboPrj;
	CComboBox m_cComboBuild;
	CComboBox m_cComboConfig;
	CComboBox m_cComboDOE;
};
