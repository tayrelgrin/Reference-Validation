
// Data_ManagerDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "Data_ManagerDlg.h"
#include "afxdialogex.h"
#include <ShellAPI.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CData_ManagerDlg 대화 상자




CData_ManagerDlg::CData_ManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CData_ManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
}


void CData_ManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_BUTTON_NEW, m_cButton_New);
	DDX_Control(pDX, IDC_BUTTON_LOADSETTING, m_cButton_LoadSetting);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cButton_Save);
	DDX_Control(pDX, IDC_BUTTON_DELETE, m_cButton_Delete);
	DDX_Control(pDX, IDC_BUTTON_RELOAD, m_cButton_Reload);
	DDX_Control(pDX, IDC_BUTTON_SETTING, m_cButton_Setting);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_cButton_EXIT);
	DDX_Control(pDX, IDC_TREE_MAIN, m_treeMainTest);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrlMain);
	DDX_Control(pDX, IDC_LIST_PRJ, m_lbProject);
	DDX_Control(pDX, IDC_LIST_BUILDNUM, m_lbBuild);
	DDX_Control(pDX, IDC_LIST_CONFIGNUM, m_lbConfig);
	DDX_Control(pDX, IDC_LIST_DOE, m_lbDOE);
}

BEGIN_MESSAGE_MAP(CData_ManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CData_ManagerDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CData_ManagerDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CData_ManagerDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_LOADSETTING, &CData_ManagerDlg::OnBnClickedButtonLoadsetting)
	ON_LBN_SETFOCUS(IDC_LIST_PRJ, &CData_ManagerDlg::OnLbnSetfocusListPrj)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CData_ManagerDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_RELOAD, &CData_ManagerDlg::OnBnClickedButtonReload)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CData_ManagerDlg::OnBnClickedButtonSave)
	ON_LBN_SELCHANGE(IDC_LIST_PRJ, &CData_ManagerDlg::OnLbnSelchangeListPrj)
	ON_LBN_SELCHANGE(IDC_LIST_BUILDNUM, &CData_ManagerDlg::OnLbnSelchangeListBuildnum)
	ON_LBN_SELCHANGE(IDC_LIST_CONFIGNUM, &CData_ManagerDlg::OnLbnSelchangeListConfignum)
	ON_LBN_SELCHANGE(IDC_LIST_DOE, &CData_ManagerDlg::OnLbnSelchangeListDoe)
	ON_NOTIFY(NM_CLICK, IDC_TREE_MAIN, &CData_ManagerDlg::OnNMClickTreeMain)
END_MESSAGE_MAP()


// CData_ManagerDlg 메시지 처리기

BOOL CData_ManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다. 응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	InitMainList();
	MakeDataDirectory();

	m_cValueData.LoadXMLFileListInValue();
	
	m_cValueData.LoadBaseFileList();

 	m_cValueData.GetConfigNameList(m_vConfigName);
	AddRefinfoToListBox();

	Button_Imaging();
	
	
	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}


void CData_ManagerDlg::Button_Imaging()
{
	// New Button image calling
	m_cButton_New.LoadBitmaps(IDB_BITMAP_NEW, IDB_BITMAP_NEWPUSH, NULL, NULL);
	m_cButton_New.SizeToContent();

	// Setting Load image calling
	m_cButton_LoadSetting.LoadBitmaps(IDB_BITMAP_LOADSETTING,IDB_BITMAP_LOADSETTINGPUSH,IDB_BITMAP_LOADSETTING,IDB_BITMAP_LOADSETTING);
	m_cButton_LoadSetting.SizeToContent();

	// Save image calling
	m_cButton_Save.LoadBitmaps(IDB_BITMAP_SAVE,IDB_BITMAP_SAVEPUSH,NULL,NULL);
	m_cButton_Save.SizeToContent();

	// Delete image calling
	m_cButton_Delete.LoadBitmaps(IDB_BITMAP_DELETE,IDB_BITMAP_DELETEPUSH,NULL,NULL);
	m_cButton_Delete.SizeToContent();

	// Reload image calling
	m_cButton_Reload.LoadBitmaps(IDB_BITMAP_RELOAD,IDB_BITMAP_RELOADPUSH,NULL,NULL);
	m_cButton_Reload.SizeToContent();

	// Setting image calling
	m_cButton_Setting.LoadBitmaps(IDB_BITMAP_SET,IDB_BITMAP_SETPUSH,NULL,NULL);
	m_cButton_Setting.SizeToContent();

	// EXIT image calling
	m_cButton_EXIT.LoadBitmaps(IDB_BITMAP_EXIT,IDB_BITMAP_EXITPUSH,NULL,NULL);
	m_cButton_EXIT.SizeToContent();
}


void CData_ManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다. 문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CData_ManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CData_ManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CData_ManagerDlg::OnBnClickedButtonNew()
{
	//AfxSetAllocStop(801);

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_cAddNewRefDlg.GetSafeHwnd()!=NULL)
	{
		m_cAddNewRefDlg.DestroyWindow();
	}

	if(IDOK == m_cAddNewRefDlg.DoModal())
	{
		for(int i = 0; i<m_vTestList.size(); i++)
		{
			m_vTestList.erase(m_vTestList.begin()+i);
		}
		m_vTestList.clear();

		for(int i = 0; i<m_vDirList.size(); i++)
		{
			m_vDirList.erase(m_vDirList.begin()+i);
		}
		m_vDirList.clear();

		std::vector<CString> temp;
		for(int i = 0; i<temp.size(); i++)
		{
			temp.erase(temp.begin()+i);
		}

		m_strPrj		= m_cAddNewRefDlg.GetProject();
		m_strBuildNum	= m_cAddNewRefDlg.GetBuild();
		m_strConfigNum	= m_cAddNewRefDlg.GetConfig();
		m_strDOE		= m_cAddNewRefDlg.GetDOE();
		
		m_strRootPath = m_cAddNewRefDlg.GetDirRootPath();
		m_cAddNewRefDlg.GetDirList(m_vDirList);

		ConfigDMData* cNewConfig = new ConfigDMData();
		ConfigDMData* cNewSetting = new ConfigDMData();

		cNewConfig->GetTestDirFromVector(m_vDirList, temp, m_strRootPath);
		cNewConfig->GetTestNameFromDirVector(temp, m_vTestList);
		cNewConfig->SetTestList(m_vTestList);
		cNewConfig->SetTestDirList(m_vDirList);
		cNewConfig->SetBaseFiles(temp);
		cNewConfig->GetFilePathInDir(temp, m_vDirList);
		
		cNewSetting->SetTestList(m_vTestList);
		cNewSetting->SetTestDirList(m_vDirList);
		cNewSetting->SetBaseFiles(temp);

		AddNewConfig(cNewConfig, cNewSetting);

		for(int i = 0; i<temp.size(); i++)
		{
			temp.erase(temp.begin()+i);
		}
		temp.clear();

		AddToTree(cNewSetting);

		CString strComb = m_strPrj+'_'+m_strBuildNum+'_'+m_strConfigNum+'_'+m_strDOE;
		std::vector<CString> vTemp;

		FindStringInVector(m_vConfigName, strComb, vTemp);

		if (vTemp.size()==0)
		{
			m_vConfigName.push_back(strComb);
		}

		for(int i = 0; i<vTemp.size(); i++)
		{
			vTemp.erase(vTemp.begin()+i);
		}
		vTemp.clear();

		if(m_lbProject.FindStringExact(-1, m_strPrj) == -1)
			AddProjectToListBox(m_strPrj);

		if(m_lbBuild.FindStringExact(-1, m_strBuildNum) == -1)
			AddBuildToListBox(m_strBuildNum);

		if(m_lbConfig.FindStringExact(-1, m_strConfigNum) == -1)
			AddConfigToListBox(m_strConfigNum);

		if(m_lbDOE.FindStringExact(-1, m_strDOE) == -1)
			AddDOEToListBox(m_strDOE);
	}
}


void CData_ManagerDlg::OnBnClickedButtonSetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_cSettingDlg.GetSafeHwnd()!=NULL)
	{
		m_cSettingDlg.DestroyWindow();
	}
	m_cSettingDlg.Create(SettingBaseInfo::IDD, this);
	m_cSettingDlg.CenterWindow();
	m_cSettingDlg.ShowWindow(SW_SHOW);
}


void CData_ManagerDlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for(int i = 0; i<m_vTestList.size(); i++)
	{
		m_vTestList.erase(m_vTestList.begin()+i);
	}
	m_vTestList.clear();

	for(int i = 0; i<m_vDirList.size(); i++)
	{
		m_vDirList.erase(m_vDirList.begin()+i);
	}
	m_vDirList.clear();
	
	m_cValueData.InitAllData();
	m_cNewConfigData.InitListAndVectors();
	m_cNewSettingData.InitListAndVectors();

	::SendMessage(this->m_hWnd, WM_CLOSE,NULL,NULL);
}


void CData_ManagerDlg::OnBnClickedButtonLoadsetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	(GetDlgItem(IDC_STATIC_LOAD))->ShowWindow(TRUE);
}


void CData_ManagerDlg::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//m_cData.DeleteConfigData();
}


void CData_ManagerDlg::OnBnClickedButtonReload()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CData_ManagerDlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	BeginWaitCursor();
	m_cValueData.SaveRefToFile(_T("temp"));
	EndWaitCursor();

	MessageBox (NULL,NULL,MB_OK);
}


void CData_ManagerDlg::AddToTree(ConfigDMData* inpData)
{
	m_treeMainTest.DeleteAllItems();

	std::vector<CString> vData, vTestName;
	CString strTemp, strTest, strFile;
	CString compare;

	inpData->GetFileNames(vTestName);

	HTREEITEM h_BASEINFO = m_treeMainTest.InsertItem(_T("Base Info"), TVI_ROOT, TVI_LAST);
	HTREEITEM h_Root;
	HTREEITEM h_Child;
	HTREEITEM h_2Child;
	for(int i= 0 ; i < vTestName.size(); i++)
	{
		AfxExtractSubString(strTemp, vTestName[i], 2, ':');

		if(vTestName[i].Find('\\') == -1 && strTemp=="")
		{
			strTemp = vTestName[i];

			AfxExtractSubString(strTest, strTemp, 0, ':');
			AfxExtractSubString(strFile, strTemp, 1, ':');

 			if(m_treeMainTest.GetCount() >= 1 && i != 0)
 				compare = m_treeMainTest.GetItemText(h_Root);	// Serach in Root level in tree

			if(strTest != compare)
				h_Root = m_treeMainTest.InsertItem(strTest, TVI_ROOT, TVI_LAST);

			h_Child = m_treeMainTest.InsertItem(strFile, h_Root, NULL);

		}
		else
		{
			AfxExtractSubString(strTemp, vTestName[i], 0, '\\');
			AfxExtractSubString(strTemp,strTemp, 0, ':');

			if(m_treeMainTest.GetCount() > 0 && i != 0)
				compare = m_treeMainTest.GetItemText(h_Root);	// Serach in Root level in tree

			if(strTemp != compare)
				h_Root = m_treeMainTest.InsertItem(strTemp, TVI_ROOT, TVI_LAST);

			AfxExtractSubString(strTemp, vTestName[i], 1, '\\');
			AfxExtractSubString(strTest, strTemp, 0, ':');
			AfxExtractSubString(strFile, strTemp, 1, ':');

			if(strTemp.Find(':') != -1 || strTemp == "")
			{
				AfxExtractSubString(strTest, vTestName[i], 1, ':');
				AfxExtractSubString(strFile, vTestName[i], 2, ':');
			}

			

			if(m_treeMainTest.GetCount() > 0 && i != 0)	
				compare = m_treeMainTest.GetItemText(h_Child);	// Serach in h_Child level in tree

			if(strTest != compare)
				h_Child = m_treeMainTest.InsertItem(strTest, h_Root, NULL);

			h_2Child = m_treeMainTest.InsertItem(strFile, h_Child, NULL);
		}
	}
}


void CData_ManagerDlg::OnLbnSetfocusListPrj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CData_ManagerDlg::InitMainList()
{
	// init List
	m_ListCtrlMain.DeleteAllItems();

	// List style
	m_ListCtrlMain.SetExtendedStyle(LVS_EX_GRIDLINES);

	m_ListCtrlMain.InsertColumn(0, _T("Critical item"), LVCFMT_CENTER, 80,  -1);
	m_ListCtrlMain.InsertColumn(1, _T("File"),			LVCFMT_CENTER, 100, -1);
	m_ListCtrlMain.InsertColumn(2, _T("Section"),		LVCFMT_CENTER, 100, -1);
	m_ListCtrlMain.InsertColumn(3, _T("Item"),			LVCFMT_CENTER, 120, -1);
	m_ListCtrlMain.InsertColumn(4, _T("Value"),			LVCFMT_CENTER, 120, -1);
	m_ListCtrlMain.InsertColumn(5, _T("Description"),	LVCFMT_CENTER, 200, -1);

}


void CData_ManagerDlg::AddNewConfig(ConfigDMData* inData, ConfigDMData* inSetting)
{
	inData->SetProject(m_strPrj);
	inData->SetBuildNum(m_strBuildNum);
	inData->SetConfigNum(m_strConfigNum);
	inData->SetDOE(m_strDOE);
	inData->SetNewDataFlag(TRUE);

	inSetting->SetProject(m_strPrj);
	inSetting->SetBuildNum(m_strBuildNum);
	inSetting->SetConfigNum(m_strConfigNum);
	inSetting->SetDOE(m_strDOE);
	inSetting->SetNewDataFlag(TRUE);

	m_cValueData.AddNewConfigData(inData);
	m_cValueData.AddNewSettingData(inSetting);
}

//////////////////////////////////////////////////////////////////////////
// Name     : AddProjectToListBox
// Function : Project list box에 출력
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void CData_ManagerDlg::AddRefinfoToListBox()
{
	for (int i= 0; i<m_vConfigName.size(); i++)
	{
		AfxExtractSubString(m_strPrj, m_vConfigName[i], 0, '_');

		AddProjectToListBox(m_strPrj);
	}
}

//////////////////////////////////////////////////////////////////////////
// Name     : AddProjectToListBox
// Function : Project list box에 출력
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void CData_ManagerDlg::AddProjectToListBox(CString inPrj)
{
	//m_lbProject.ResetContent();

	bool bCompareResult = true;
	CString strTemp;
	for(int i = 0; i<m_lbProject.GetCount(); i++)
	{
		m_lbProject.GetText(i, strTemp);
		if(inPrj == strTemp)
			bCompareResult = false;
	}
	
	if(bCompareResult)
		m_lbProject.AddString(inPrj);
}

//////////////////////////////////////////////////////////////////////////
// Name     : AddBuildToListBox
// Function : Build list box에 빌드 번호 출력
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void CData_ManagerDlg::AddBuildToListBox(CString inBuild)
{
	m_lbBuild.ResetContent();
	m_lbBuild.AddString(inBuild);
}

//////////////////////////////////////////////////////////////////////////
// Name     : AddConfigToListBox
// Function : Config를 list box에 출력
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void CData_ManagerDlg::AddConfigToListBox(CString inConfig)
{
	m_lbConfig.ResetContent();
	m_lbConfig.AddString(inConfig);
}

//////////////////////////////////////////////////////////////////////////
// Name     : AddDOEToListBox
// Function : DOE를 list box에 출력
// pre		: none
// return	: none
//////////////////////////////////////////////////////////////////////////
void CData_ManagerDlg::AddDOEToListBox(CString inDOE)
{
	m_lbDOE.ResetContent();
	m_lbDOE.AddString(inDOE);
}


void CData_ManagerDlg::OnLbnSelchangeListPrj()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	m_lbConfig.ResetContent();
	m_lbBuild.ResetContent();
	m_lbDOE.ResetContent();
	m_treeMainTest.DeleteAllItems();

	int nIndex = m_lbProject.GetCurSel();
	m_lbProject.GetText(nIndex, m_strPrj);

	std::vector<CString> vFileList;
	FindStringInVector(m_vConfigName, m_strPrj, vFileList);
	CString strTemp;
	bool bCompareResult = true;

	for (int i=0; i<vFileList.size(); i++)
	{
		bCompareResult = true;
		AfxExtractSubString(strTemp, vFileList[i], 1, '_');
		
		for (int i = 0; i< m_lbBuild.GetCount(); i++)
		{
			CString strTarget;
			m_lbBuild.GetText(i, strTarget);
			if(strTarget == strTemp)
				bCompareResult = false;
		}
		if(bCompareResult)	// 중복 확인 
			m_lbBuild.AddString(strTemp);
	}
}


void CData_ManagerDlg::FindStringInVector(std::vector<CString> invData, CString inTarget, std::vector<CString>& outvData)
{
	for(int i= 0; i<invData.size(); i++)
	{
		if(invData[i].Find(inTarget) != -1)
		{
			outvData.push_back(invData[i]);
		}
	}
}


void CData_ManagerDlg::OnLbnSelchangeListBuildnum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lbConfig.ResetContent();
	m_lbDOE.ResetContent();
	m_treeMainTest.DeleteAllItems();

	int nIndex = m_lbBuild.GetCurSel();
	m_lbBuild.GetText(nIndex, m_strBuildNum);

	CString strTarget = m_strPrj + '_' + m_strBuildNum;
	CString strTemp;
	std::vector<CString> vFileList;
	bool bCompareResult = true;

	FindStringInVector(m_vConfigName, strTarget, vFileList);

	for (int i=0; i<vFileList.size(); i++)
	{
		bCompareResult = true;
		AfxExtractSubString(strTemp, vFileList[i], 2, '_');

		for (int j = 0; j< m_lbConfig.GetCount(); j++)
		{
			CString strTarget;
			m_lbConfig.GetText(j, strTarget);
			if(strTarget == strTemp)
				bCompareResult = false;
		}
		if(bCompareResult)	// 중복 확인 
			m_lbConfig.AddString(strTemp);
	}
}


void CData_ManagerDlg::OnLbnSelchangeListConfignum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_lbDOE.ResetContent();
	m_treeMainTest.DeleteAllItems();

	int nIndex = m_lbConfig.GetCurSel();
	m_lbConfig.GetText(nIndex, m_strConfigNum);

	CString strTargetName = m_strPrj + '_' + m_strBuildNum + '_' + m_strConfigNum;
	CString strTemp;
	std::vector<CString> vFileList;
	bool bCompareResult = true;

	FindStringInVector(m_vConfigName, strTargetName, vFileList);

	for (int i=0; i<vFileList.size(); i++)
	{
		bCompareResult = true;
		AfxExtractSubString(strTemp, vFileList[i], 3, '_');

		for (int j = 0; j< m_lbDOE.GetCount(); j++)
		{
			CString strTarget;
			m_lbDOE.GetText(j, strTarget);
			if(strTarget == strTemp)
				bCompareResult = false;
		}
		if(bCompareResult)	// 중복 확인
			m_lbDOE.AddString(strTemp);		
	}
}


void CData_ManagerDlg::OnLbnSelchangeListDoe()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ConfigDMData* pConfig = &m_cNewConfigData;
	ConfigDMData* pSetting = &m_cNewSettingData;
	m_treeMainTest.DeleteAllItems();

	int nIndex = m_lbDOE.GetCurSel();
	m_lbDOE.GetText(nIndex, m_strDOE);
	BeginWaitCursor(); 

	CString strTarget = m_strPrj + '_' + m_strBuildNum + '_' + m_strConfigNum + '_' + m_strDOE;
	CString strTemp;
	std::vector<CString> vFileList;

	FindStringInVector(m_vConfigName, strTarget, vFileList);

	// File Read 
	CString strEXEDirectory, strValuePath, strSettingPath;

	strEXEDirectory = pConfig->GetEXEDirectoryPath();

	strValuePath = strEXEDirectory + "\\Data\\Value\\" + m_strPrj + '\\' +  + m_strBuildNum + '-' + m_strConfigNum + '-' + m_strDOE + ".xml";
	strSettingPath = strEXEDirectory + "\\Data\\Setting\\Setting-" + m_strPrj + '-' +  + m_strBuildNum + '-' + m_strConfigNum + '-' + m_strDOE + ".xml";

	pConfig->LoadDataFiles(strValuePath);
	pSetting->LoadDataFiles(strSettingPath);

	// treeview에 뿌려주기
	AddToTree(pSetting);
	EndWaitCursor();
}


void CData_ManagerDlg::MakeDataDirectory()
{
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	CString strEXEPath = path;

	int i = strEXEPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	strEXEPath = strEXEPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.

	strEXEPath = strEXEPath + "\\Data";
	CreateDirectory(strEXEPath,NULL);
	CreateDirectory(strEXEPath+"\\Value",NULL);
	CreateDirectory(strEXEPath+"\\Setting",NULL);
}


void CData_ManagerDlg::OnNMClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	HTREEITEM hNode = NULL;

	m_treeMainTest.GetItemText(hNode);
}
