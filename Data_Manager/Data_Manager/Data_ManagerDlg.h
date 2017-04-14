
// Data_ManagerDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "afxext.h"
#include "AddNewRef.h"
#include "InformationManager.h"
#include "SettingBaseInfo.h"
#include <string>
#include "afxcmn.h"



// CData_ManagerDlg 대화 상자
class CData_ManagerDlg : public CDialogEx
{
// 생성입니다.
public:
	CData_ManagerDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DATA_MANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	CBitmapButton m_cButton_New;
	CBitmapButton m_cButton_LoadSetting;
	CBitmapButton m_cButton_Save;
	CBitmapButton m_cButton_Delete;
	CBitmapButton m_cButton_Reload;
	CBitmapButton m_cButton_Setting;
	CBitmapButton m_cButton_EXIT;
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedButtonSetting();
	afx_msg void OnBnClickedButtonExit();
	
	void Button_Imaging();	
	void InitMainList();
	afx_msg void OnBnClickedButtonLoadsetting();

	CListCtrl m_ListCtrlMain;
	CTreeCtrl m_treeMainTest;
	afx_msg void OnLbnSetfocusListPrj();	
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonReload();
	afx_msg void OnBnClickedButtonSave();

public:
	void AddToTree(ConfigDMData* inpData);
	void AddNewConfig(ConfigDMData* inData, ConfigDMData* inSetting);
	void AddProjectToListBox(CString inPrj);
	void AddBuildToListBox(CString inBuild);
	void AddConfigToListBox(CString inConfig);
	void AddDOEToListBox(CString inDOE);
	void AddRefinfoToListBox();
	void FindStringInVector(std::vector<CString> invData, CString inTarget, std::vector<CString>& outvData);
	void MakeDataDirectory();
	void AddToListControl(CString inStrFileName, FileType& inData);
private:
	std::vector<CString> m_vDirList;
	std::vector<CString> m_vTestList;
	std::vector<CString> m_vConfigName;
	AddNewRef m_cAddNewRefDlg;
	SettingBaseInfo m_cSettingDlg;
	ConfigDMData m_cNewConfigData;
	ConfigDMData m_cNewSettingData;
	InformationManager m_cValueData;
	FileType m_cFileData;
	CString m_strRootPath;
	CString m_strPrj;
	CString m_strBuildNum;
	CString m_strConfigNum;
	CString m_strDOE;
	
public:
	CListBox m_lbProject;
	CListBox m_lbBuild;
	CListBox m_lbConfig;
	CListBox m_lbDOE;
	afx_msg void OnLbnSelchangeListPrj();
	afx_msg void OnLbnSelchangeListBuildnum();
	afx_msg void OnLbnSelchangeListConfignum();
	afx_msg void OnLbnSelchangeListDoe();
	afx_msg void OnTvnSelchangedTreeMain(NMHDR *pNMHDR, LRESULT *pResult);
};
