
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
	DDX_Control(pDX, IDC_EDIT1, m_EditInListCtrl);
}

BEGIN_MESSAGE_MAP(CData_ManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CData_ManagerDlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDC_BUTTON_SETTING, &CData_ManagerDlg::OnBnClickedButtonSetting)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CData_ManagerDlg::OnBnClickedButtonExit)
	ON_BN_CLICKED(IDC_BUTTON_LOADSETTING, &CData_ManagerDlg::OnBnClickedButtonLoadsetting)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CData_ManagerDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_RELOAD, &CData_ManagerDlg::OnBnClickedButtonReload)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CData_ManagerDlg::OnBnClickedButtonSave)
	ON_LBN_SELCHANGE(IDC_LIST_PRJ, &CData_ManagerDlg::OnLbnSelchangeListPrj)
	ON_LBN_SELCHANGE(IDC_LIST_BUILDNUM, &CData_ManagerDlg::OnLbnSelchangeListBuildnum)
	ON_LBN_SELCHANGE(IDC_LIST_CONFIGNUM, &CData_ManagerDlg::OnLbnSelchangeListConfignum)
	ON_LBN_SELCHANGE(IDC_LIST_DOE, &CData_ManagerDlg::OnLbnSelchangeListDoe)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE_MAIN, &CData_ManagerDlg::OnTvnSelchangedTreeMain)	
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, &CData_ManagerDlg::OnLvnColumnclickList1)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CData_ManagerDlg::OnLvnItemchangedList1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CData_ManagerDlg::OnNMDblclkList1)
ON_WM_SYSCHAR()
ON_EN_KILLFOCUS(IDC_EDIT1, &CData_ManagerDlg::OnEnKillfocusEdit1)
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

	m_cFileData = new FileType;
	m_cBasicData = new FileType;

	m_strBasicLoadTxt = "Load Reference Setting :";
/*	AfxSetAllocStop(98269);*/
	m_bIsAllCheck = false;
	InitMainList();
	MakeDataDirectory();

	m_cValueData.LoadXMLFileListInValue();
	
	m_cValueData.LoadBaseFileList();

 	m_cValueData.GetConfigNameList(m_vConfigName);
	AddRefinfoToListBox();

	Button_Imaging();

	m_bNotFirst = false;
	m_bNewData = false;
	m_bModify = false;
	m_cNewConfigData	= new ConfigDMData();
	m_cNewSettingData	= new ConfigDMData();
	m_cValueData.AddNewConfigData(m_cNewConfigData);
	m_cValueData.AddNewSettingData(m_cNewSettingData);
	//Set the style to listControl
	ListView_SetExtendedListViewStyle(::GetDlgItem(m_hWnd,IDC_LIST1),LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES); 
	
	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_HIDE);

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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	bool bWorking = true;
	if(m_cAddNewRefDlg.GetSafeHwnd()!=NULL)
	{
		m_cAddNewRefDlg.DestroyWindow();
	}
	if (m_bNewData || m_bModify)
	{
		if(AfxMessageBox("There is some Working Data, Continue To make new one without saving?", MB_OKCANCEL))
			bWorking = true;
		else
			bWorking = false;
	}
	if(bWorking)
	{
		if(IDOK == m_cAddNewRefDlg.DoModal())
		{
			BeginWaitCursor();

			LoadSettingTextChange(m_strBasicLoadTxt,false);

			m_cNewConfigData->InitListAndVectors();
			m_cNewSettingData->InitListAndVectors();
			m_cValueData.InitBaseInfo();

			m_vTestList.clear();
			m_vDirList.clear();
			m_cBasicData->InitList();
			m_cFileData->InitList();

			std::vector<CString> temp;
			temp.clear();

			m_strPrj		= m_cAddNewRefDlg.GetProject();
			m_strBuildNum	= m_cAddNewRefDlg.GetBuild();
			m_strConfigNum	= m_cAddNewRefDlg.GetConfig();
			m_strDOE		= m_cAddNewRefDlg.GetDOE();
			m_bPreDataUsed  = m_cAddNewRefDlg.GetPreDataUsed();
			m_strRootPath   = m_cAddNewRefDlg.GetDirRootPath();

			m_cNewConfigData->SetProject(m_strPrj);
			m_cNewConfigData->SetBuildNum(m_strBuildNum);
			m_cNewConfigData->SetConfigNum(m_strConfigNum);
			m_cNewConfigData->SetDOE(m_strDOE);

			m_cNewSettingData->SetProject(m_strPrj);
			m_cNewSettingData->SetBuildNum(m_strBuildNum);
			m_cNewSettingData->SetConfigNum(m_strConfigNum);
			m_cNewSettingData->SetDOE(m_strDOE);

			m_cAddNewRefDlg.GetDirList(m_vDirList);

			if(!m_bPreDataUsed)
			{
				m_cNewConfigData->GetTestDirFromVector(m_vDirList, temp, m_strRootPath);
				m_cNewConfigData->GetTestNameFromDirVector(temp, m_vTestList);
				m_cNewConfigData->SetTestList(m_vTestList);
				m_cNewConfigData->SetTestDirList(m_vDirList);
				m_cNewConfigData->SetBaseFiles(temp);
				m_cNewConfigData->GetFilePathInDir(temp, m_vDirList);

				m_cNewSettingData->SetTestList(m_vTestList);
				m_cNewSettingData->SetTestDirList(m_vDirList);
				m_cNewSettingData->SetBaseFiles(temp);

				AddNewConfig(m_cNewConfigData, m_cNewSettingData);

				temp.clear();

				CString strComb = m_strPrj+'_'+m_strBuildNum+'_'+m_strConfigNum+'_'+m_strDOE;
				std::vector<CString> vTemp;

				FindStringInVector(m_vConfigName, strComb, vTemp);

				if (vTemp.size()==0)
				{
					m_vConfigName.push_back(strComb);
				}

				vTemp.clear();
			}
			else
			{
				CString strPrePrj		= m_cAddNewRefDlg.GetPreProject();
				CString strPreBuildNum	= m_cAddNewRefDlg.GetPreBuild();
				CString strPreConfigNum	= m_cAddNewRefDlg.GetPreConfig();
				CString strPreDOE		= m_cAddNewRefDlg.GetPreDOE();

				CString strTarget = strPrePrj + '_' + strPreBuildNum + '_' + strPreConfigNum + '_' + strPreDOE;
				CString strTemp;
				std::vector<CString> vFileList;

				FindStringInVector(m_vConfigName, strTarget, vFileList);

				// File Read 
				CString strEXEDirectory, strValuePath, strSettingPath;

				strEXEDirectory = m_cNewConfigData->GetEXEDirectoryPath();

				strValuePath.Format(_T("%s%s%s%s%s%s%s%s%s%s"), strEXEDirectory, "\\Data\\Value\\", m_strPrj, "\\", m_strBuildNum,"-", m_strConfigNum, "-", m_strDOE,".xml");
				strSettingPath.Format(_T("%s%s%s%s%s%s%s%s%s%s"),strEXEDirectory,"\\Data\\Setting\\Setting-", m_strPrj, "-", m_strBuildNum, "-", m_strConfigNum, "-", m_strDOE,".xml");

				m_cNewConfigData->LoadDataFiles(strValuePath);
				m_cNewSettingData->LoadDataFiles(strSettingPath);
			}

			AddToTree(m_cNewSettingData);

			if(m_lbProject.FindStringExact(-1, m_strPrj) == -1)
				AddProjectToListBox(m_strPrj);

			if(m_lbBuild.FindStringExact(-1, m_strBuildNum) == -1)
				AddBuildToListBox(m_strBuildNum);

			if(m_lbConfig.FindStringExact(-1, m_strConfigNum) == -1)
				AddConfigToListBox(m_strConfigNum);

			if(m_lbDOE.FindStringExact(-1, m_strDOE) == -1)
				AddDOEToListBox(m_strDOE);
			m_bNewData = true;
			EndWaitCursor();
		}
	}	
}


void CData_ManagerDlg::OnBnClickedButtonSetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(m_cSettingDlg.GetSafeHwnd()!=NULL)
	{
		m_cSettingDlg.DestroyWindow();
	}
	if(m_strDOE!="")
	{
		m_cSettingDlg.m_strSettingText = m_strPrj + "-" + m_strBuildNum + "-" + m_strConfigNum + "-" + m_strDOE;

		std::vector<CString> vConfigFileNames;				// ref 디렉토리에 있는 파일 정보를 가져오기 위한 벡터
		m_cNewConfigData->GetFileNames(vConfigFileNames);	// ref 디렉토리에 있는 파일 정보 m_cNewConfigData에서 전부 가져오기

		m_cSettingDlg.m_vConfigFileList = vConfigFileNames;
		m_cSettingDlg.m_vSettingFileList = m_vAllFileList;	// Base setting 을 위한 파일 리스트

		m_cSettingDlg.m_pData = &m_cValueData;

		m_cSettingDlg.DoModal();

		m_vAllFileList = m_cSettingDlg.m_vSettingFileList;

		bool bModify = m_cSettingDlg.m_bModifyFlag;

		if (bModify)
		{
			HTREEITEM hNode;
			TestType cBaseInfoTest;
			hNode = m_treeMainTest.GetNextItem(m_treeMainTest.GetRootItem(), TVGN_NEXT);
			CString strTest = m_treeMainTest.GetItemText(hNode);
			cBaseInfoTest.SetTestName(strTest);

			m_cValueData.GetBaseInfo(*m_cBasicData);

			CList<BasicData*> Templist;
			m_cBasicData->CopyDataToList(Templist);
			m_cNewSettingData->InitBaseInfoList();
			m_cNewSettingData->SetBaseInfoList(Templist);
			m_cNewSettingData->SetNewDataFlag(true);

			m_bModify = true;
		}
		AddToTree(m_cNewSettingData);
		CheckBaseInfoInAllData();
	}
	else
	{
		AfxMessageBox("Choose DOE", MB_OK);
	}
}


void CData_ManagerDlg::OnBnClickedButtonExit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	bool bWorking = true;
	if(m_bNewData || m_bModify)
	{
		if(AfxMessageBox("Close SW without Save?", MB_OKCANCEL) == 1)
		{
			bWorking = true;
		}
		else
			bWorking = false;
	}
	if(bWorking)
	{
		m_vTestList.clear();
		m_vDirList.clear();

		//m_cValueData.InitBaseInfo();
		m_cValueData.InitAllData();
			
		m_cNewConfigData->InitListAndVectors();
		m_cNewSettingData->InitListAndVectors();

		delete m_cFileData;
		delete m_cBasicData;
		::SendMessage(this->m_hWnd, WM_CLOSE,NULL,NULL);
	}
}


void CData_ManagerDlg::OnBnClickedButtonLoadsetting()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ConfigDMData* pSetting = m_cNewSettingData;
	ConfigDMData* pConfig   = m_cNewConfigData;

	CString strEXEDirectory;

	char szFilter[] = "All Files(*.*)|*.*||";

	strEXEDirectory = pSetting->GetEXEDirectoryPath();

	strEXEDirectory = strEXEDirectory + "\\Data\\Setting\\";

	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);

	dlg.m_ofn.lpstrInitialDir = strEXEDirectory;	// 초기 경로 지정
	if( m_strDOE == "")
	{
		AfxMessageBox("Choose config first",MB_OK);
	}
	else
	{
		if(IDOK == dlg.DoModal())
		{
			BeginWaitCursor(); 

			CString strSettingPath;
			strSettingPath.Format("%s",dlg.GetPathName());
			CString strFileName, strConfig, strResult, strFileHead;
			CString strPrj, strBuild, strConfigNum, strDOE;
			strFileName.Format("");
			strConfig.Format("");
			strResult.Format("");
			strFileHead.Format("");

			strPrj.Format("");
			strBuild.Format("");
			strConfigNum.Format("");
			strDOE.Format("");

			// 읽어들일 파일이 현재와 같은지 확인
			int nIndex = strSettingPath.ReverseFind('\\');

			strFileName = strSettingPath.Mid(nIndex+1);

			AfxExtractSubString(strFileHead, strFileName,0,'-');

			if(strFileHead == "Setting")
			{
				AfxExtractSubString(strPrj,			strFileName,1,'-');
				AfxExtractSubString(strBuild,		strFileName,2,'-');
				AfxExtractSubString(strConfigNum,	strFileName,3,'-');
				AfxExtractSubString(strDOE,			strFileName,4,'-');

				CString strTemp;
				strTemp.Format("");
				AfxExtractSubString(strTemp,			strDOE,0,'.');
				strDOE = strTemp;

				if(strPrj != m_strPrj ||
					strBuild != m_strBuildNum || 
					strConfigNum != m_strConfigNum || 
					strDOE != m_strDOE)
				{
					pSetting->InitListAndVectors();

					pSetting->LoadDataFiles(strSettingPath);

					// p에서 이름 파일 이름 가져와서 이름 바꾸기
					ChangeSettingFileNameToConfigFileName(pConfig, pSetting);

					pSetting->SetBuildNum(m_strBuildNum);
					pSetting->SetProject(m_strPrj);
					pSetting->SetConfigNum(m_strConfigNum);
					pSetting->SetDOE(m_strDOE);

					CList<BasicData*> cTemp;

					pSetting->GetBaseInfoList(cTemp);

					m_cValueData.SetBaseInfoFromConfig(cTemp);

					cTemp.RemoveAll();
					int nIndexTemp = strSettingPath.ReverseFind('\\');

					strFileName = strSettingPath.Mid(nIndexTemp+1);

					nIndexTemp = strFileName.ReverseFind('.');
					strConfig = strFileName.Left(nIndexTemp);

					CString strTemp;
					GetDlgItemText(IDC_STATIC_LOAD, (LPSTR(LPCTSTR(strTemp))), 255);
					strResult.Format("%s%s",strTemp, strConfig);
					LoadSettingTextChange(strResult,true);

					m_bModify = true;

					AddToTree(pSetting);

					EndWaitCursor();
				}
				else
				{
					AfxMessageBox("You chose same config data\n Choose another one",MB_OK);
				}
				
			}
			else
			{
				AfxMessageBox("You chose Wrong file!",MB_OK);
			}
		}	
	}	
}

void CData_ManagerDlg::LoadSettingTextChange(CString inNewString, bool inFlag)
{
	CString strTemp;
	GetDlgItemText(IDC_STATIC_LOAD, (LPSTR(LPCTSTR(strTemp))), 255);
	
	SetDlgItemText(IDC_STATIC_LOAD,inNewString);
	(GetDlgItem(IDC_STATIC_LOAD))->ShowWindow(inFlag);
}


void CData_ManagerDlg::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strTarget = m_strPrj + '_' + m_strBuildNum + '_' + m_strConfigNum + '_' + m_strDOE;
	CString strValuePath, strSettingPath;
	CString strMessage, strEXEDirectory;

	ConfigDMData* pConfig = m_cNewConfigData;
	ConfigDMData* pSetting = m_cNewSettingData;

	strEXEDirectory = pConfig->GetEXEDirectoryPath();

	if (m_strPrj != "" && m_strBuildNum != "" && m_strConfigNum != "" && m_strDOE != "")
	{
		strMessage.Format(_T("Delete %s-%s-%s-%s Files?"),m_strPrj, m_strBuildNum, m_strConfigNum,m_strDOE );
		if(IDYES == AfxMessageBox(strMessage,MB_YESNO))
		{
			strValuePath.Format(_T("%s%s%s%s%s%s%s%s%s%s"), strEXEDirectory, "\\Data\\Value\\", m_strPrj, "\\", m_strBuildNum,"-", m_strConfigNum, "-", m_strDOE,".xml");
			strSettingPath.Format(_T("%s%s%s%s%s%s%s%s%s%s"),strEXEDirectory,"\\Data\\Setting\\Setting-", m_strPrj, "-", m_strBuildNum, "-", m_strConfigNum, "-", m_strDOE,".xml");

			::DeleteFile(strValuePath);
			::DeleteFile(strSettingPath);

			m_treeMainTest.DeleteAllItems();
			m_ListCtrlMain.DeleteAllItems();

			m_lbConfig.ResetContent();
			m_lbDOE.ResetContent();
			m_lbBuild.ResetContent();
			m_lbProject.ResetContent();

			// list box 수정 
			pConfig->InitListAndVectors();
			pSetting->InitListAndVectors();

			m_cValueData.LoadXMLFileListInValue();

			m_cValueData.GetConfigNameList(m_vConfigName);
			AddRefinfoToListBox();
		}
	}
}


void CData_ManagerDlg::OnBnClickedButtonReload()
{
	HTREEITEM hItem;
	CString strDirName ="";
	CString strFileName, strTestName;

	BeginWaitCursor();

	m_ListCtrlMain.DeleteAllItems();
	m_treeMainTest.DeleteAllItems();

	hItem = m_treeMainTest.GetNextItem(NULL, TVGN_CARET); // 현재 선택된 아이템의 핸들을 가져온다.
	strFileName = m_treeMainTest.GetItemText(hItem); // 그 아이템의 이름을 얻어온다.
	
	hItem = m_treeMainTest.GetNextItem(hItem, TVGN_PARENT); // 현재 선택되어진 아이템의 상위 아이템을 가져온다.
	strTestName = m_treeMainTest.GetItemText(hItem); // 그 아이템의 이름을 얻어온다.

	hItem = m_treeMainTest.GetNextItem(hItem, TVGN_PARENT); // 현재 선택되어진 아이템의 상위의 상위 아이템을 가져온다.
	strDirName = m_treeMainTest.GetItemText(hItem); // 그 아이템의 이름을 얻어온다.

	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ConfigDMData* pConfig = m_cNewConfigData;
	ConfigDMData* pSetting = m_cNewSettingData;
	
	CString strTarget = m_strPrj + '_' + m_strBuildNum + '_' + m_strConfigNum + '_' + m_strDOE;
	CString strTemp;
	std::vector<CString> vFileList;

	FindStringInVector(m_vConfigName, strTarget, vFileList);

	// File Read 
	CString strEXEDirectory, strValuePath, strSettingPath;

	strEXEDirectory = pConfig->GetEXEDirectoryPath();

	strValuePath.Format(_T("%s%s%s%s%s%s%s%s%s%s"), strEXEDirectory, "\\Data\\Value\\", m_strPrj, "\\", m_strBuildNum,"-", m_strConfigNum, "-", m_strDOE,".xml");
	strSettingPath.Format(_T("%s%s%s%s%s%s%s%s%s%s"),strEXEDirectory,"\\Data\\Setting\\Setting-", m_strPrj, "-", m_strBuildNum, "-", m_strConfigNum, "-", m_strDOE,".xml");

	pConfig->LoadDataFiles(strValuePath);
	pSetting->LoadDataFiles(strSettingPath);

	CList<BasicData*> cTemp;

	pSetting->GetBaseInfoList(cTemp);

	m_cValueData.SetBaseInfoFromConfig(cTemp);

	AddToTree(pSetting);
	Sleep(1000);

	EndWaitCursor();
}


void CData_ManagerDlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	if (IDYES == AfxMessageBox("Save Data?",MB_YESNO))
	{
		if( m_strPrj != "" &&
			m_strBuildNum != "" &&
			m_strConfigNum != "" &&
			m_strDOE != "")
		{
			BeginWaitCursor();
			CList<BasicData*> vTemp;
			m_cBasicData->CopyDataToList(vTemp);
			if (vTemp.GetCount() == 0)
			{
				AfxMessageBox("Setting the base info!",MB_OK);
			}
			else
			{
				bool bResult = m_cValueData.SaveRefToFile(_T("temp"));
				EndWaitCursor();
				if(bResult)
				{
					MessageBox ("Complete Save the data to File",NULL,MB_OK);
					m_bNewData = false;
					m_bModify  = false;
				}
				else
					MessageBox ("FAIL!! There is a something missing",NULL,MB_OK);
			}
		}
		else
			AfxMessageBox("FAIL!! There is no data to save", MB_OK);
	}
}


void CData_ManagerDlg::AddToTree(ConfigDMData* inpData)
{
	m_treeMainTest.DeleteAllItems();

	std::vector<CString> vData;
	CString strTemp, strTest, strFile;
	CString compare, strTargetFile;
	
	m_vAllFileList.clear();
	inpData->GetFileNames(m_vAllFileList);

	HTREEITEM h_BASEINFO = m_treeMainTest.InsertItem(_T("Base Info"), TVI_ROOT, TVI_LAST);
	HTREEITEM h_Root;
	HTREEITEM h_Child;
	HTREEITEM h_2Child;
	for(int i= 0 ; i < m_vAllFileList.size(); i++)
	{
		strTemp.Format("");
		strTest.Format("");
		strFile.Format("");
		compare.Format("");
		strTargetFile.Format("");

		AfxExtractSubString(strTemp, m_vAllFileList[i], 2, ':');

		if(m_vAllFileList[i].Find('\\') == -1 && strTemp=="")
		{
			strTemp = m_vAllFileList[i];

			AfxExtractSubString(strTest, strTemp, 0, ':');
			AfxExtractSubString(strFile, strTemp, 1, ':');

 			if(m_treeMainTest.GetCount() >= 1 && i != 0)
 				compare = m_treeMainTest.GetItemText(h_Root);	// Search in Root level in tree

			if(strTest != compare)
				h_Root = m_treeMainTest.InsertItem(strTest, TVI_ROOT, TVI_LAST);

			h_Child = m_treeMainTest.InsertItem(strFile, h_Root, NULL);

		}
		else
		{
			strTargetFile = m_vAllFileList[i];
			AfxExtractSubString(strTemp, strTargetFile, 0, '\\');
			AfxExtractSubString(strTemp,strTemp, 0, ':');

			if(m_treeMainTest.GetCount() > 0 && i != 0)
				compare = m_treeMainTest.GetItemText(h_Root);	// Search in Root level in tree

			if(strTemp != compare)
				h_Root = m_treeMainTest.InsertItem(strTemp, TVI_ROOT, TVI_LAST);

			AfxExtractSubString(strTemp, strTargetFile, 1, '\\');
			if(strTemp == m_strBasicLoadTxt)	// CString의 저주
			{
				strTemp.Format("");
			}
			AfxExtractSubString(strTest, strTemp, 0, ':');
			AfxExtractSubString(strFile, strTemp, 1, ':');

			if(strTemp == "")	// 확인하자
			{
				AfxExtractSubString(strTest, strTargetFile, 1, ':');
				AfxExtractSubString(strFile, strTargetFile, 2, ':');
			}

			if(m_treeMainTest.GetCount() > 0 && i != 0)	
				compare = m_treeMainTest.GetItemText(h_Child);	// Serach in h_Child level in tree

			if(strTest != compare)
				h_Child = m_treeMainTest.InsertItem(strTest, h_Root, NULL);

			h_2Child = m_treeMainTest.InsertItem(strFile, h_Child, NULL);
		}
	}
}


void CData_ManagerDlg::InitMainList()
{
	// init List
	m_ListCtrlMain.DeleteAllItems();

	// List style
	m_ListCtrlMain.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES | LVCFMT_CENTER | LVS_EDITLABELS);

	m_ListCtrlMain.InsertColumn(0, _T("Critical item"), LVCFMT_CENTER, 20,  -1);
	m_ListCtrlMain.InsertColumn(1, _T("File"),			LVCFMT_CENTER, 100, -1);
	m_ListCtrlMain.InsertColumn(2, _T("Section"),		LVCFMT_CENTER, 125, -1);
	m_ListCtrlMain.InsertColumn(3, _T("Item"),			LVCFMT_CENTER, 150, -1);
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
	bool bCompareResult = true;
	CString strTemp;
	strTemp.Format("");

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
	bool bDo = true;

	if(m_bNewData || m_bModify)
	{
		if(1 == AfxMessageBox("There are some modification, Do you want to escape without save?", MB_OKCANCEL))
		{
			bDo = true;

			if(m_bNewData)
			{
				m_cNewConfigData->InitListAndVectors();
				m_cNewSettingData->InitListAndVectors();
			}
			m_bNewData = false;
			m_bModify = false;
		}
		else 
			bDo = false;
	}
	if(bDo)
	{
		LoadSettingTextChange(m_strBasicLoadTxt,false);
		m_lbConfig.ResetContent();
		m_lbBuild.ResetContent();
		m_lbDOE.ResetContent();
		m_treeMainTest.DeleteAllItems();
		m_strDOE = "";
		m_ListCtrlMain.DeleteAllItems();

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
		
			for (int j = 0; j< m_lbBuild.GetCount(); j++)
			{
				CString strTarget;
				m_lbBuild.GetText(j, strTarget);
				if(strTarget == strTemp)
					bCompareResult = false;
			}
			if(bCompareResult)	// 중복 확인 
				m_lbBuild.AddString(strTemp);
		}
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
	bool bDo = true;

	if(m_bNewData || m_bModify)
	{
		if(1 == AfxMessageBox("There are some modification, Do you want to escape without save?", MB_OKCANCEL))
		{
			bDo = true;
			if(m_bNewData)
			{
				m_cNewConfigData->InitListAndVectors();
				m_cNewSettingData->InitListAndVectors();
			}
			m_bNewData = false;
			m_bModify = false;
		}
		else 
			bDo = false;
	}
	if(bDo)
	{
		LoadSettingTextChange(m_strBasicLoadTxt,false);
		m_lbConfig.ResetContent();
		m_lbDOE.ResetContent();
		m_treeMainTest.DeleteAllItems();
		m_strDOE = "";
		m_ListCtrlMain.DeleteAllItems();

		int nIndex = m_lbBuild.GetCurSel();
		m_lbBuild.GetText(nIndex, m_strBuildNum);

		CString strTargetName = m_strPrj + '_' + m_strBuildNum;
		CString strTemp;
		std::vector<CString> vFileList;
		bool bCompareResult = true;

		FindStringInVector(m_vConfigName, strTargetName, vFileList);

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
}


void CData_ManagerDlg::OnLbnSelchangeListConfignum()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	bool bDo = true;

	if(m_bNewData || m_bModify)
	{
		if(1 == AfxMessageBox("There are some modification, Do you want to escape without save?", MB_OKCANCEL))
		{
			bDo = true;
			if(m_bNewData)
			{
				m_cNewConfigData->InitListAndVectors();
				m_cNewSettingData->InitListAndVectors();
			}
			m_bNewData = false;
			m_bModify = false;
		}
		else 
			bDo = false;
	}
	if(bDo)
	{
		LoadSettingTextChange(m_strBasicLoadTxt,false);
		m_lbDOE.ResetContent();
		m_treeMainTest.DeleteAllItems();
		m_ListCtrlMain.DeleteAllItems();
		m_strDOE = "";

		int nIndex = m_lbConfig.GetCurSel();
		m_lbConfig.GetText(nIndex, m_strConfigNum);
		m_ListCtrlMain.DeleteAllItems();

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
}


void CData_ManagerDlg::OnLbnSelchangeListDoe()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	bool bDo = true;

	if(m_bNewData || m_bModify)
	{
		if(1 == AfxMessageBox("There are some modification, Do you want to Reload?", MB_OKCANCEL))
		{
			bDo = true;
			if(m_bNewData)
			{
				m_cNewConfigData->InitListAndVectors();
				m_cNewSettingData->InitListAndVectors();
			}
			m_bNewData = false;
			m_bModify = false;
		}
		else 
			bDo = false;
	}
	if(bDo)
	{
		LoadSettingTextChange(m_strBasicLoadTxt,false);
		ConfigDMData* pConfig = m_cNewConfigData;
		ConfigDMData* pSetting = m_cNewSettingData;

		m_treeMainTest.DeleteAllItems();
		m_vAllFileList.clear();
		m_cBasicData->SetListCountZero();

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

		strValuePath.Format(_T("%s%s%s%s%s%s%s%s%s%s"), strEXEDirectory, "\\Data\\Value\\", m_strPrj, "\\", m_strBuildNum,"-", m_strConfigNum, "-", m_strDOE,".xml");
		strSettingPath.Format(_T("%s%s%s%s%s%s%s%s%s%s"),strEXEDirectory,"\\Data\\Setting\\Setting-", m_strPrj, "-", m_strBuildNum, "-", m_strConfigNum, "-", m_strDOE,".xml");

		pConfig->LoadDataFiles(strValuePath);
		pConfig->SetProject(m_strPrj);
		pConfig->SetBuildNum(m_strBuildNum);
		pConfig->SetConfigNum(m_strConfigNum);
		pConfig->SetDOE(m_strDOE);

		pSetting->LoadDataFiles(strSettingPath);
		pSetting->SetProject(m_strPrj);
		pSetting->SetBuildNum(m_strBuildNum);
		pSetting->SetConfigNum(m_strConfigNum);
		pSetting->SetDOE(m_strDOE);

		CList<BasicData*> cTemp;

		pSetting->GetBaseInfoList(cTemp);

		m_cValueData.SetBaseInfoFromConfig(cTemp);

		// treeview에 뿌려주기
		AddToTree(pSetting);
		EndWaitCursor();
		m_bNotFirst = true;
		m_bModify = false;
	}
}


void CData_ManagerDlg::MakeDataDirectory()
{
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	CString strEXEPath = path;

	int i = strEXEPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	CString strTemp = strEXEPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.
	
	strEXEPath.Format(_T("%s%s"),strTemp,"\\Data");
	CreateDirectory(strEXEPath,NULL);
	CreateDirectory(strEXEPath+"\\Value",NULL);
	CreateDirectory(strEXEPath+"\\Setting",NULL);
}


void CData_ManagerDlg::OnTvnSelchangedTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	m_ListCtrlMain.DeleteAllItems();
	Sleep(500);
	HTREEITEM hNode;
	std::string strFileName, strTestName, strDirName, strCombe;

	hNode = m_treeMainTest.GetNextItem(NULL, TVGN_CARET);		// 현재 선택된 아이템의 핸들을 가져온다.
	strFileName = m_treeMainTest.GetItemText(hNode);			// 그 아이템의 이름을 얻어온다.

 	hNode = m_treeMainTest.GetNextItem(hNode, TVGN_PARENT);		// 현재 선택되어진 아이템의 상위 아이템을 가져온다.
 	strTestName = m_treeMainTest.GetItemText(hNode);			// 그 아이템의 이름을 얻어온다.
 
 	hNode = m_treeMainTest.GetNextItem(hNode, TVGN_PARENT);		// 현재 선택되어진 아이템의 상위 아이템을 가져온다.
 	strDirName = m_treeMainTest.GetItemText(hNode);				// 그 아이템의 이름을 얻어온다.

	if (strDirName.length()>100)
	{
		strDirName = "";
	}

	if(strFileName == "Base Info")
	{
		//TestType cBaseInfoTest;
		hNode = m_treeMainTest.GetNextItem(NULL, TVGN_CARET);
		hNode = m_treeMainTest.GetNextItem(hNode, TVGN_NEXT);
		
		m_cBasicData->SetListCountZero();
		m_cValueData.GetBaseInfo(*m_cBasicData);

		AddBaseInfoToListControl(m_treeMainTest.GetItemText(hNode));
		
	}
	else
	{
		if(strTestName!="")
		{
			FileType* cSetting = new FileType;
			if(strDirName!="")
			{
				if(m_bNewData)
					strCombe = strDirName+"\\"+strTestName;
				else
					strCombe = strDirName+":"+strTestName;
			}
			else
				strCombe = strTestName;
			m_cNewConfigData->SearchFileDataInList(strCombe.c_str(), strFileName.c_str(), *m_cFileData);
			m_cNewSettingData->SearchFileDataInList(strCombe.c_str(), strFileName.c_str(), *cSetting);

			AddToListControl(strFileName.c_str(), *m_cFileData, *cSetting);

			delete cSetting;
		}
		else
			m_ListCtrlMain.DeleteAllItems();
	}
}


void CData_ManagerDlg::AddToListControl(CString inStrFileName, FileType& inData, FileType& inSetting)
{
	m_ListCtrlMain.DeleteAllItems(); 

	CList<BasicData*> Items;
	inData.CopyDataToList(Items);

	POSITION pos = Items.GetHeadPosition();
	int nIndex = 0;
	CString strSequence;
	CString strOri, strValue, strDescrip;
	CString strSection, strItem;

	strSection.Format("");
	strSequence.Format("");
	strOri.Format("");
	strValue.Format("");
	strDescrip.Format("");
	strItem.Format("");

	BeginWaitCursor();
	while(pos)
	{
		strSequence.Format(_T("%d"), nIndex);

		BasicData* temp = Items.GetNext(pos);
		strSection = temp->getSection();
		strItem = temp->getItem();
		strOri	= temp->getValue();
		AfxExtractSubString(strValue,	strOri, 0, '/');
		AfxExtractSubString(strDescrip, strOri, 1, '/');

		if (strValue==m_strBasicLoadTxt)
		{
			strValue.Format("");
		}
		if (strDescrip==m_strBasicLoadTxt)
		{
			strDescrip.Format("");
		}

		m_ListCtrlMain.InsertItem(nIndex, strSequence);
		m_ListCtrlMain.SetItem(nIndex, 0,LVIF_TEXT,  "",0,0,0,NULL );
		m_ListCtrlMain.SetItem(nIndex, 1,LVIF_TEXT,  inStrFileName,0,0,0,NULL );
		m_ListCtrlMain.SetItem(nIndex, 2,LVIF_TEXT,  strSection,0,0,0,NULL);
		m_ListCtrlMain.SetItem(nIndex, 3,LVIF_TEXT,  strItem ,0,0,0,NULL);
		m_ListCtrlMain.SetItem(nIndex, 4,LVIF_TEXT,  strValue ,0,0,0,NULL);
		m_ListCtrlMain.SetItem(nIndex, 5,LVIF_TEXT,  strDescrip ,0,0,0,NULL);

		nIndex++;
	}

	// fill check boxes
	//////////////////////////////////////////////////////////////////////////
	CList<BasicData*> Settings;
	inSetting.CopyDataToList(Settings);

	pos = Settings.GetHeadPosition();
	nIndex = 0;
	strSequence;

	while(pos)
	{
		BasicData* temp = Items.GetNext(pos);

		strValue = temp->getValue();

		if (strValue == "1")
		{
			m_ListCtrlMain.SetCheck(nIndex,1);
		}
		nIndex++;
	}
	

	//////////////////////////////////////////////////////////////////////////

	pos = Items.GetHeadPosition();

	POSITION pTemp = NULL;

	while(pos && Items.GetSize()>0)
	{
		pTemp = pos;

		BasicData* temp = Items.GetNext(pos);
		delete temp;
		Items.RemoveAt(pTemp);
	}
	
	EndWaitCursor();
}


void CData_ManagerDlg::AddBaseInfoToListControl( CString inData)
{
	m_ListCtrlMain.DeleteAllItems(); 

	CList<BasicData*> lBaseItems;
	CList<BasicData*> lBaseValueItems;
	FileType* pFile = new FileType;
	std::vector<CString> vFileNames;

	m_cBasicData->CopyDataToList(lBaseItems);

	std::string strTarget = _T("");
	std::string strPreItem = _T("");

	int nIndex = 0;
	CString strSequence = "";
	CString strOri = "";
	std::string strValue = "";
	std::string strDescrip = "";
	BeginWaitCursor();

	POSITION pos = lBaseItems.GetHeadPosition();

	while(pos)
	{
		strSequence.Format(_T("%d"), nIndex);
		BasicData* temp = lBaseItems.GetNext(pos);
		strTarget = temp->getValue();

		if(strTarget.find('/') != -1)
		{
			CString strTemp;
			AfxExtractSubString(strTemp, strTarget.c_str(), 0,'/');
			strTarget = strTemp;
		}

		if(strTarget.compare(strPreItem) != 0)	// 아이템 체인지
		{
			strPreItem = strTarget;
			CString strTemp = strTarget.c_str();
			strTemp = strTemp+".ini";

			m_cNewConfigData->SearchFileDataInList(inData,strTemp,*pFile) ;

			pFile->CopyDataToList(lBaseValueItems);
		}

		POSITION pValuePos = lBaseValueItems.GetHeadPosition();
		CString strFileName, strSetting, strDescription;
		while(pValuePos)
		{
			BasicData* tempValue = lBaseValueItems.GetNext(pValuePos);
			if (tempValue->getSection()== temp->getSection() && 
				tempValue->getItem() == temp->getItem())
			{
				CString strTemp = "";
				strTemp = temp->getValue();

				// 파일 이름에서 세팅값 분리
				AfxExtractSubString(strFileName, strTemp, 0,'/');
				AfxExtractSubString(strSetting,	 strTemp, 1,'/');
				AfxExtractSubString(strDescription,  strTemp, 2,'/');	// 주석 분리

				if (strTemp == "")
				{
					strFileName = strTemp;
				}

				temp->setValue(tempValue->getValue());	// Value 값 저장
				break;
			}
		}

		m_ListCtrlMain.InsertItem(nIndex, strSequence);
		m_ListCtrlMain.SetItem(nIndex, 0,LVIF_TEXT,  "",0,0,0,NULL );

		m_ListCtrlMain.SetItem(nIndex, 1,LVIF_TEXT,  strFileName,0,0,0,NULL );
		m_ListCtrlMain.SetItem(nIndex, 2,LVIF_TEXT,  temp->getSection(),0,0,0,NULL);
		m_ListCtrlMain.SetItem(nIndex, 3,LVIF_TEXT,  temp->getItem() ,0,0,0,NULL);

		if (strSetting == "1")
		{
			m_ListCtrlMain.SetCheck(nIndex,1);
		}

		CString strTemp1, strTemp2;

		strOri = temp->getValue();
		if(AfxExtractSubString(strTemp1, strOri, 0, '/'))
			strValue = LPSTR(LPCTSTR(strTemp1));
		if(AfxExtractSubString(strTemp2, strOri, 1, '/'))
			strDescrip = LPSTR(LPCTSTR(strTemp2));
		m_ListCtrlMain.SetItem(nIndex, 4,LVIF_TEXT,  strValue.c_str() ,0,0,0,NULL);
		m_ListCtrlMain.SetItem(nIndex, 5,LVIF_TEXT,  strDescrip.c_str() ,0,0,0,NULL);
		nIndex++;
	}

	delete pFile;
	EndWaitCursor();
}


//this function will returns the item text depending on the item and SubItem Index
CString CData_ManagerDlg::GetItemText(HWND hWnd, int m_nItem, int nSubItem) const
{
	LVITEM lvi;
	memset(&lvi, 0, sizeof(LVITEM));
	lvi.iSubItem = nSubItem;
	CString str;
	int nLen = 128;
	int nRes;
	do
	{
		nLen *= 2;
		lvi.cchTextMax = nLen;
		lvi.pszText = str.GetBufferSetLength(nLen);
		nRes  = (int)::SendMessage(hWnd, LVM_GETITEMTEXT, (WPARAM)m_nItem,
			(LPARAM)&lvi);
	} while (nRes == nLen-1);
	str.ReleaseBuffer();
	return str;
}

void CData_ManagerDlg::OnOK()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	
	CWnd* pwndCtrl = GetFocus();

	// 	get the control ID which is presently having the focus
	int ctrl_ID = pwndCtrl->GetDlgCtrlID();
	CString strNewData;


	if(::GetDlgItem(GetParent()->GetSafeHwnd(), IDC_EDIT1) == pwndCtrl->GetSafeHwnd() ||  
		::GetDlgItem(GetParent()->GetSafeHwnd(), IDC_EDIT1) == m_hFocus)
	{  
		// EditCtrl로 부터 Text를 얻어온다.  
		CString cStrText;  
		::GetWindowText(::GetDlgItem(GetParent()->GetSafeHwnd(), IDC_EDIT1), LPSTR(LPCTSTR(cStrText)), 255);  
		 
		// 얻어온 텍스트를 ListCtrl 에 적용시킨다  
		SetCell(::GetDlgItem (m_hWnd,IDC_LIST1), strNewData, m_nItem, m_nSubItem);
 
		// EditCtrl의 Focus를 죽인다.  
		::SendMessage(::GetDlgItem(GetParent()->GetSafeHwnd(), IDC_EDIT1), WM_KILLFOCUS, 0, 0);  
		::ShowWindow(::GetDlgItem(GetParent()->GetSafeHwnd(), IDC_EDIT1), SW_HIDE);  
		::SetFocus(pwndCtrl->GetSafeHwnd());  

	}
	m_hFocus = (HWND)0;
}


void CData_ManagerDlg::SetCell(HWND hWnd1, CString value, int nRow, int nCol)
{
	TCHAR     szString [256];
	wsprintf(szString,value ,0);

	//Fill the LVITEM structure with the values given as parameters.
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = nRow;
	lvItem.pszText = szString;
	lvItem.iSubItem = nCol;
	if(nCol >0)
		//set the value of listItem
		::SendMessage(hWnd1,LVM_SETITEM, (WPARAM)0,(WPARAM)&lvItem);
	else
		//Insert the value into List
		ListView_InsertItem(hWnd1,&lvItem);
}

// This function inserts the default values into the listControl
void CData_ManagerDlg::InsertItems()
{
	HWND hWnd = ::GetDlgItem(m_hWnd, IDC_LIST1);
}

BOOL CData_ManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	if(pMsg->message == WM_KEYDOWN){
		if(pMsg->wParam == VK_RETURN){
			if(pMsg->hwnd == GetDlgItem(IDC_EDIT1)->GetSafeHwnd())
			{
				CString str;
				GetDlgItemText(IDC_EDIT1, str);
				m_ListCtrlMain.SetItemText(m_nItem, m_nSubItem, str);

				GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );
			}
			return TRUE;
		}
		if(pMsg->wParam == VK_ESCAPE)
		{
			return TRUE;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CData_ManagerDlg::OnLvnColumnclickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	int nCnt = m_ListCtrlMain.GetItemCount();
	if( pNMLV->iSubItem == 0 )
	{
		if( m_bIsAllCheck )
		{
			for( int i=0 ; i<nCnt ; i++ )
				m_ListCtrlMain.SetCheck( i, FALSE );
			m_bIsAllCheck = FALSE;
			//SetHeaderCheck( FALSE );
		}
		else
		{
			for( int i=0 ; i<nCnt ; i++ )
				m_ListCtrlMain.SetCheck( i );
			m_bIsAllCheck = TRUE;
			
			//SetHeaderCheck( TRUE );
		}
		m_bModify = true;
	}
	*pResult = 0;
}


void CData_ManagerDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;
	int nCheckValue = 0;

	int nSelIndex = pNMLV->iItem; // 클릭한 아이템의 인덱스 얻어옴
	bool bFlag = false;
	CString strFile, strSection, strItem, strValue, strDescrip;

	if(pNMLV->uChanged)
	{
		if (nSelIndex > -1)
		{
			TV_HITTESTINFO hit_info;

			// 화면상에서 마우스의 위치를 얻는다.
			::GetCursorPos(&hit_info.pt);

			// 얻은 마우스 좌표를 트리컨트롤 기준의 좌표로 변경한다.
			::ScreenToClient(m_ListCtrlMain.m_hWnd, &hit_info.pt);

			strFile		= m_ListCtrlMain.GetItemText(nSelIndex,1);
			strSection	= m_ListCtrlMain.GetItemText(nSelIndex,2);
			strItem		= m_ListCtrlMain.GetItemText(nSelIndex,3);
			strValue	= m_ListCtrlMain.GetItemText(nSelIndex,4);
			strDescrip	= m_ListCtrlMain.GetItemText(nSelIndex,5);

			// 체크 박스에 체크 여부에 따라 세팅 값이 0 또는 1로 변경
			if((pNMLV->uNewState & 0x1000) && (pNMLV->uOldState & 0x2000))
			{
				nCheckValue = 0; // uncheck : release checking
				bFlag = true;
			}
			else if((pNMLV->uNewState & 0x2000) && (pNMLV->uOldState & 0x1000))
			{
				nCheckValue = 1; // check 
				bFlag = true;
			}

			if (bFlag && (hit_info.flags & TVHT_ONITEMSTATEICON) != 0)
			{
				// 변경된 세팅 값을 해당 객체에 저장
				strValue.Format("%d", nCheckValue);

				BasicData* cModifyTarget = new BasicData;

				cModifyTarget->setItem(strItem);
				cModifyTarget->setValue(strValue);
				cModifyTarget->setSection(strSection);

				HTREEITEM selectedItem;

				selectedItem = m_treeMainTest.GetNextItem(NULL, TVGN_CARET);		// 현재 선택된 아이템의 핸들을 가져온다.
				CString strTestName = m_treeMainTest.GetItemText(selectedItem);		// 그 아이템의 이름을 얻어온다.

				if (strTestName.Find(".ini") >-1)
				{
					selectedItem = m_treeMainTest.GetNextItem(selectedItem, TVGN_PARENT);		// 현재 선택된 아이템의 핸들을 가져온다.
					strTestName = m_treeMainTest.GetItemText(selectedItem);		// 그 아이템의 이름을 얻어온다.
				}

				if(strTestName == "Base Info")
				{
					m_cValueData.ModifyBaseInfoData(strTestName, strFile, cModifyTarget);
					HTREEITEM hItem = m_treeMainTest.GetNextItem(m_treeMainTest.GetRootItem(), TVGN_NEXT);
					
					CString strTest = m_treeMainTest.GetItemText(hItem);

					while(hItem != NULL)
					{
						m_cValueData.ModifySettingData(strTest, strFile, cModifyTarget);

						hItem = m_treeMainTest.GetNextItem(hItem, TVGN_NEXT);
						strTest = m_treeMainTest.GetItemText(hItem);

						HTREEITEM hChild = m_treeMainTest.GetNextItem(hItem, TVGN_CHILD);
						HTREEITEM hGrandChild = m_treeMainTest.GetNextItem(hChild, TVGN_CHILD);
						if (hGrandChild != NULL)
						{
							CString strChild = m_treeMainTest.GetItemText(hChild);
							CString strTemp = strTest + ":" + strChild;
							strTest = strTemp;
						}
					}
				}
				else
					m_cValueData.ModifySettingData(strTestName, strFile, cModifyTarget);

				delete cModifyTarget;

				bFlag = false;
				m_bModify = true;	// file save 를 위한 flag 변경
			}
		}
	}
}


void CData_ManagerDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	Invalidate();
	HWND hWnd1 =  ::GetDlgItem (m_hWnd,IDC_LIST1);
	LPNMITEMACTIVATE temp = (LPNMITEMACTIVATE) pNMHDR;

	//get the row number
	m_nItem = temp->iItem;
	//get the column number
	m_nSubItem = temp->iSubItem;

	// 선택된 지점이 올바르지 않을시...  
	if(m_nSubItem == 0 || m_nSubItem == -1 || m_nItem == -1)
		return ;

	//Retrieve the text of the selected subItem from the list
	CString strPreData = GetItemText(hWnd1,m_nItem ,m_nSubItem);
	CString strData = strPreData;

	RECT rtListCtrl, rtDlg, rtSubItem;

	// this macro is used to retrieve the Rectangle of the selected SubItem
	ListView_GetSubItemRect(hWnd1,temp->iItem,temp->iSubItem,LVIR_BOUNDS,&rtSubItem);

	//Get the Rectangle of the listControl
	::GetWindowRect(temp->hdr.hwndFrom,&rtListCtrl);

	//Get the Rectangle of the Dialog
	::GetWindowRect(m_hWnd,&rtDlg);

	// Dialog에 위치한 ListCtrl의 left & top 위치를 구한다.
	int nThisLeft = rtListCtrl.left - rtDlg.left;
	int nThisTop  = rtListCtrl.top  - rtDlg.top;

	if(m_nItem != -1)
		::SetWindowPos(	::GetDlgItem(m_hWnd,IDC_EDIT1),
		HWND_TOP,
		rtSubItem.left + nThisLeft ,
		rtSubItem.top + nThisTop-30,
		rtSubItem.right - rtSubItem.left - 3,
		rtSubItem.bottom - rtSubItem.top -1,
		NULL);

	::ShowWindow(::GetDlgItem(m_hWnd,IDC_EDIT1),SW_SHOW);
	::SetFocus(::GetDlgItem(m_hWnd,IDC_EDIT1));

	//Draw a Rectangle around the SubItem
	::Rectangle(::GetDC(temp->hdr.hwndFrom),rtSubItem.left,rtSubItem.top-1,rtSubItem.right,rtSubItem.bottom);

	//Set the listItem text in the EditBox
	::SetWindowText(::GetDlgItem(m_hWnd,IDC_EDIT1),strData);
	m_EditInListCtrl.SetSel(strData.GetLength());

	int nSel = strData.GetLength();
	::SendMessage(::GetDlgItem(GetParent()->GetSafeHwnd(), IDC_EDIT1), EM_SETSEL, LOWORD(nSel), HIWORD(nSel)); 

	// Focus를 잃었을 경우 ListCtrl에 적용시키기 위해 저장  
	m_hFocus = ::GetDlgItem(GetParent()->GetSafeHwnd(), IDC_EDIT1);
	Invalidate();

	*pResult = 0;
}


bool CData_ManagerDlg::CheckBaseInfoInAllData()
{
	std::vector<CString> vDifferentTest;

	bool bResult = m_cValueData.CheckBaseInfoInAllData(vDifferentTest);

	CString strErrorMessage = "";

	for (int i = 0; i < vDifferentTest.size(); i++)
	{
		CString temp = strErrorMessage;

		strErrorMessage.Format("%s\n%s", temp, vDifferentTest[i]);
	}

	if (strErrorMessage != "")
	{
		AfxMessageBox(strErrorMessage,MB_OK);
	}

	return bResult;
}


void CData_ManagerDlg::OnEnKillfocusEdit1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString str;
	GetDlgItemText(IDC_EDIT1, str);
	m_ListCtrlMain.SetItemText(m_nItem, m_nSubItem, str);

	GetDlgItem(IDC_EDIT1)->SetWindowPos(NULL, 0, 0, 0, 0, SWP_HIDEWINDOW );

	BasicData* cModifyData = new BasicData;

	CString strDir, strTest, strFile, strSection, strValue, strItem, strDescrip;

	HTREEITEM hItem;

	hItem = m_treeMainTest.GetNextItem(NULL, TVGN_CARET); // 현재 선택된 아이템의 핸들을 가져온다.
	strFile = m_treeMainTest.GetItemText(hItem); // 그 아이템의 이름을 얻어온다.


	hItem = m_treeMainTest.GetNextItem(hItem, TVGN_PARENT); // 현재 선택되어진 아이템의 상위 아이템을 가져온다.
	strTest = m_treeMainTest.GetItemText(hItem); // 그 아이템의 이름을 얻어온다.


	hItem = m_treeMainTest.GetNextItem(hItem, TVGN_PARENT); // 현재 선택되어진 아이템의 상위의 상위 아이템을 가져온다.
	strDir = m_treeMainTest.GetItemText(hItem); // 그 아이템의 이름을 얻어온다.

	if (strDir.GetLength()>100)
	{
		strDir = "";
	}

	strFile		= m_ListCtrlMain.GetItemText(m_nItem,1);
	strSection	= m_ListCtrlMain.GetItemText(m_nItem,2);
	strItem		= m_ListCtrlMain.GetItemText(m_nItem,3);
	strValue	= m_ListCtrlMain.GetItemText(m_nItem,4);
	strDescrip	= m_ListCtrlMain.GetItemText(m_nItem,5);
	
	cModifyData->setItem(strItem);
	cModifyData->setSection(strSection);
	if (strDescrip!="")
	{
		strValue = strValue + strDescrip;
	}
	cModifyData->setValue(strValue);
	
	if(strDir != "")
	{
		if (m_bNewData)
			strTest = strDir + "\\"+strTest;	
		else
			strTest = strDir + ":"+strTest;

	}

	m_cNewConfigData->ModifyData(strTest, strFile, cModifyData);

	delete cModifyData;

	m_bModify = true;
}


void CData_ManagerDlg::ChangeSettingFileNameToConfigFileName(ConfigDMData* inpConfig, ConfigDMData* outpSetting)
{
	std::vector<CString> vSettingBaseFileList;	// File Name 받을 변수
	std::vector<CString> vConfigBaseFileList;	// File Name 받을 변수
	std::vector<CString> vConfigRegisterFileList;	// File Name 에서 Register File을 추출해 받을 변수
	std::vector<CString> vSettingRegisterFileList;	// File Name 에서 Register File을 추출해 받을 변수

	inpConfig->GetFileNames(vConfigBaseFileList);
	outpSetting->GetFileNames(vSettingBaseFileList);

	CString strConfigFile, strSettingFile;
	strConfigFile.Format("");
	strSettingFile.Format("");

	int nIndex = -1;

	for (int i =0; i< vConfigBaseFileList.size(); i++)
	{
		strConfigFile = vConfigBaseFileList[i];
		nIndex = strConfigFile.Find("_Register");
		if(nIndex >-1)
		{
			vConfigRegisterFileList.push_back(strConfigFile);
		}
	}

	for (int i =0; i< vSettingBaseFileList.size(); i++)
	{
		strSettingFile = vSettingBaseFileList[i];
		nIndex = strSettingFile.Find("_Register");
		if(nIndex >-1)
		{
			vSettingRegisterFileList.push_back(strSettingFile);
		}
	}

	CString strTest, strFileName, strETC, strSettingTest, strSettingFileName, strSettingETC;
	CString strReferenceName, strSettingReferenceName;
	strTest.Format("");
	strFileName.Format("");
	strETC.Format("");
	strSettingTest.Format("");
	strSettingFileName.Format("");
	strSettingETC.Format("");
	strReferenceName.Format("");
	strSettingReferenceName.Format("");

	for (int i =0; i< vConfigRegisterFileList.size(); i++)
	{
		AfxExtractSubString(strTest,	 vConfigRegisterFileList[i],0,':');
		AfxExtractSubString(strFileName, vConfigRegisterFileList[i],1,':');
		AfxExtractSubString(strETC,		 vConfigRegisterFileList[i],2,':');

		
		if(strETC != "")
		{
			 CString strTemp = strTest;
			 strTest = strFileName;
			 strFileName = strETC;
			 strETC = strTemp;
		}
		strReferenceName = strFileName;
		strReferenceName.Replace("_Register","");

		for (int j =0; j< vSettingRegisterFileList.size(); j++)
		{
			AfxExtractSubString(strSettingTest,		vSettingRegisterFileList[j],0,':');
			AfxExtractSubString(strSettingFileName, vSettingRegisterFileList[j],1,':');
			AfxExtractSubString(strSettingETC,		vSettingRegisterFileList[j],2,':');

			if(strSettingETC != "")
			{
				CString strTemp = strSettingTest;
				strSettingTest = strSettingFileName;
				strSettingFileName = strSettingETC;
				strSettingETC = strTemp;
			}

			strSettingReferenceName = strSettingFileName;
			strSettingReferenceName.Replace("_Register","");

			if(strTest == strSettingTest && strETC == strSettingETC)
			{
				outpSetting->ChangeFileName(strTest,strFileName,strSettingFileName);
				outpSetting->ChangeFileName(strTest,strReferenceName,strSettingReferenceName);
				break;
			}
		}
	}
}