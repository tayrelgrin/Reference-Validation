
// Data_ValidationDlg.cpp : 구현 파일
#include "stdafx.h"
#include "Data_Validation.h"
#include "Data_ValidationDlg.h"
#include "afxdialogex.h"

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


// CData_ValidationDlg 대화 상자




CData_ValidationDlg::CData_ValidationDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CData_ValidationDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CData_ValidationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_START, m_ButtonStart);
	DDX_Control(pDX, IDC_BUTTON_STOP, m_ButtonStop);
	DDX_Control(pDX, IDC_LIST_MAIN, m_ListCtrl_Main);
	DDX_Control(pDX, IDC_TAB1, m_TabCtrl_Main);
	DDX_Control(pDX, IDC_TREE_MAIN, m_TreeMain);
	DDX_Control(pDX, IDC_PROGRESS1, m_Progressctrl);
}

BEGIN_MESSAGE_MAP(CData_ValidationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CData_ValidationDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CData_ValidationDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_REF_SELECT, &CData_ValidationDlg::OnBnClickedButtonRefSelect)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CData_ValidationDlg::OnBnClickedButtonLogin)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CData_ValidationDlg::OnTcnSelchangeTab1)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_MAIN, &CData_ValidationDlg::OnNMRClickTreeMain)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CData_ValidationDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_LISTLOG, &CData_ValidationDlg::OnBnClickedButtonListlog)
	ON_BN_CLICKED(IDC_BUTTON_RESULTLOG, &CData_ValidationDlg::OnBnClickedButtonResultlog)
END_MESSAGE_MAP()


// CData_ValidationDlg 메시지 처리기

BOOL CData_ValidationDlg::OnInitDialog()
{
	//AfxSetAllocStop(519410);
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

	
	//////////////////////////////////////////////////////////////////////////
	m_ListCtrl_Main.SetExtendedStyle(LVS_EX_GRIDLINES | LVCFMT_CENTER | LVS_EDITLABELS);

	m_ListCtrl_Main.InsertColumn(0, _T("Config"),		LVCFMT_CENTER, 100,  -1);
	m_ListCtrl_Main.InsertColumn(1, _T("Test"),			LVCFMT_CENTER, 180, -1);
	m_ListCtrl_Main.InsertColumn(2, _T("Result"),		LVCFMT_CENTER, 200, -1);
	m_ListCtrl_Main.InsertColumn(3, _T("Progress"),		LVCFMT_CENTER, 260, -1);

	m_TabCtrl_Main.InsertItem(1,_T("List Log"));
	m_TabCtrl_Main.InsertItem(2,_T("Fail Item"));
	//////////////////////////////////////////////////////////////////////////

	CRect rect;

	m_TabCtrl_Main.GetClientRect(&rect);

	m_ListLogDlg.Create(IDD_DIALOG_LISTLOG, &m_TabCtrl_Main);
	m_ListLogDlg.SetWindowPos(NULL, 0, 25, rect.Width()-30, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);

	m_pwndShow = &m_ListLogDlg;

	m_FailItemDlg.Create(IDD_DIALOG_FAILITEM, &m_TabCtrl_Main);
	m_FailItemDlg.SetWindowPos(NULL, 0, 25, rect.Width()-30, rect.Height()-30, SWP_NOZORDER);


	//////////////////////////////////////////////////////////////////////////
	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof path);

	CString strPath = path;

	int i = strPath.ReverseFind('\\');//실행 파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	CString strTemp = strPath.Left(i);//뒤에 있는 현재 실행 파일 이름을 지운다.

	strPath.Format(_T("%s%s"),strTemp,"\\ResultLog");
	CreateDirectory(strPath,NULL);

	//////////////////////////////////////////////////////////////////////////
	
	CString strEXEPath = m_TotalData.GetEXEDirectoryPath();
	m_ListLog = new ListLog(strEXEPath, &m_ListLogDlg);
	m_ListLog->CreateLogFile();
	m_ListLog->WriteLogFile(_T("Start Validation SW"));
	m_TotalData.SetListLog(m_ListLog);
	m_TotalData.SetListCtrl(&m_ListCtrl_Main);
	
	m_Progressctrl.SetRange(0,100);
	m_TotalData.SetProgressBar(&m_Progressctrl);
	m_TotalData.SetFailItemPointer(&m_FailItemDlg);
	m_TotalData.LoadXMLFileListInValue();
	m_ListLog->WriteLogFile(_T("Load XML File List From Value Directory"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CData_ValidationDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CData_ValidationDlg::OnPaint()
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
HCURSOR CData_ValidationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CData_ValidationDlg::OnBnClickedButtonStart()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_TreeMain.GetCount();

	do
	{
		if(nIndex < 1)
		{
			AfxMessageBox(_T("No Reference!\nChoose Reference "), MB_OK);
			break;
		}
	
		std::vector<CString> vValueFileList;
		m_ListLog->WriteLogFile(_T("Load File list in Value Directory"));
		m_TotalData.LoadXMLFileListInValue();

		m_TotalData.GetValueXMLFileList(vValueFileList);
		m_ConfigSelectDlg.SetValueFileList(vValueFileList);

		if(m_ConfigSelectDlg.DoModal() == true)
		{
			m_ButtonStart.EnableWindow(FALSE);
			m_ButtonStart.ShowWindow(FALSE);
			m_ButtonStop.EnableWindow(TRUE);
			m_ButtonStop.ShowWindow(TRUE);

			UpdateWindow();
			m_FailItemDlg.ClearItems();

			// 마우스 wait start
			BeginWaitCursor();

			CString strPrj		= m_ConfigSelectDlg.GetProject();
			CString strBuild	= m_ConfigSelectDlg.GetBuild();
			CString strConfig	= m_ConfigSelectDlg.GetConfig();
			CString strDOE		= m_ConfigSelectDlg.GetDOE();

			CString strConfigName;
			strConfigName.Format(_T("%s\\%s-%s-%s.xml"),strPrj,strBuild,strConfig,strDOE);
			m_ListLog->WriteLogFile(strConfigName);
			m_ListLog->WriteLogFile(_T("Start Reference Validation"));

			// Validation start
			m_TotalData.Validation(strConfigName);
			m_ListLog->WriteLogFile(_T("Reference Validation is done"));

			m_ButtonStop.EnableWindow(FALSE);
			m_ButtonStop.ShowWindow(FALSE);
			m_ButtonStart.EnableWindow(TRUE);
			m_ButtonStart.ShowWindow(TRUE);

			// 마우스 wait end
			EndWaitCursor();
			UpdateWindow();
		}
	}while(false);	
}


void CData_ValidationDlg::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (AfxMessageBox(_T("Stop the validation?"),MB_OKCANCEL)==1)
	{
		m_ListLog->WriteLogFile(_T("Stop Reference Validation"));

		m_TotalData.InitAllData();

		m_ButtonStop.EnableWindow(FALSE);
		m_ButtonStop.ShowWindow(FALSE);
		m_ButtonStart.EnableWindow(TRUE);
		m_ButtonStart.ShowWindow(TRUE);
	}
}


void CData_ValidationDlg::OnBnClickedButtonRefSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ITEMIDLIST      *pidlBrowse;
	char   Pathname[MAX_PATH];
	BROWSEINFO     BrInfo;

	std::vector<CString> vTestDir;
	std::vector<CString> vFileNames;

	m_ListLog->WriteLogFile(_T("Pushed Select Ref Button"));

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;

	vTestDir.clear();
	vFileNames.clear();

	memset( &BrInfo, 0, sizeof(BrInfo) );
	BrInfo.pszDisplayName =(LPTSTR)Pathname;
	BrInfo.lpszTitle = _T("Choose Reference Directory to Validate.");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	// 폴더 선택 다이얼로그 띄우기
	pidlBrowse = SHBrowseForFolder(&BrInfo);
	if( pidlBrowse != NULL)
	{
		// 패스를 얻어옴
		BOOL bSuccess = ::SHGetPathFromIDList(pidlBrowse, (LPTSTR)Pathname);
		if ( bSuccess )
		{
			// file, directory check
			m_TotalData.GetDirList((LPTSTR)Pathname,vTestDir, vFileNames);
			m_ListLog->WriteLogFile((LPTSTR)Pathname);
			m_ListLog->WriteLogFile(_T("Check Base File In All Data"));

			bool bCheckResult = m_TotalData.CheckBaseInfoInAllData((LPTSTR)Pathname, vTestDir);
			if(bCheckResult == false)
			{
				m_ListLog->WriteLogFile(_T("Reference Checking Fail!"));
				AfxMessageBox(_T("Reference Checking Fail!"), MB_OK);
				vTestDir.clear();
				vFileNames.clear();
			}
			else
			{
				m_TotalData.AddRootPath((LPTSTR)Pathname);
				m_ListLog->WriteLogFile(_T("Check Base File In All Data : PASS"));
				CString strRefName, strTemp;
				strRefName.Format(_T(""));
				strTemp.Format(_T(""));
				strTemp = Pathname;
				int nIndex = strTemp.ReverseFind('\\');
				strRefName = strTemp.Mid(nIndex+1);
				
				// check same item in tree
				BOOL bCheckTreeResult = CheckExistDataInTree(strRefName);
				// Add To Tree
				if(bCheckTreeResult == FALSE)
				{
					AddToTreeRefName(strRefName);
					AddToTreeTestName(vTestDir);

					// Add To member vector
					m_TotalData.AddTestDirectoryPath(vTestDir);
					m_TotalData.AddFilePath(vFileNames);
					m_ListLog->WriteLogFile(_T("Add to Member Vector"));

					// Extract Test Name From Dir Vector
					std::vector<CString> vTestName;
					std::vector<CString> vTempName;
					CString strConfig;
					strConfig.Format(_T(""));

					m_TotalData.RemoveRootPathInVector( vTestDir,  vTempName, (LPTSTR)Pathname);
					m_ListLog->WriteLogFile(_T("Remove Root Path in Directory Vector"));

					m_TotalData.GetConfigFromTestDirNameVector(vTempName, strConfig);
					m_ListLog->WriteLogFile(_T("Extract Config : ") + strConfig );

					m_TotalData.GetTestNameFromTestDirNameVector(vTempName, vTestName);
					m_ListLog->WriteLogFile(_T("Extract Test Name From Directory Name"));

					// Add To ListControl
					AddConfigAndTestToListControl(strConfig, vTestName);
				}
				else
				{
					AfxMessageBox(_T("Already Same Config in Data "), MB_OK);
				}
			}
		}
		else
		{
			m_ListLog->WriteLogFile(_T("Wrong Folder."));
			MessageBox(_T("Wrong Folder."), _T("lol"), MB_OKCANCEL|MB_ICONASTERISK );
		}
	}
}


void CData_ValidationDlg::OnBnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_ListLog->WriteLogFile(_T("Log in"));
	m_LogInDlg.DoModal();
}



void CData_ValidationDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	if (m_pwndShow != NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}

	int nIndex = m_TabCtrl_Main.GetCurSel();

	switch (nIndex)
	{
	case 0:
		m_ListLogDlg.ShowWindow(SW_SHOW);
		m_pwndShow = &m_ListLogDlg;
		break;
	case 1:
		m_FailItemDlg.ShowWindow(SW_SHOW);
		m_pwndShow = &m_FailItemDlg;
		break;
	}
}


void CData_ValidationDlg::AddToTreeRefName(CString inData)
{
	HTREEITEM h_BASEINFO = m_TreeMain.InsertItem(inData, TVI_ROOT, TVI_LAST);
	UpdateWindow();
}


void CData_ValidationDlg::OnNMRClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	*pResult = 0;

	// 삭제 버튼 추가
}


void CData_ValidationDlg::OnBnClickedButtonDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 트리에서 선택한 아이템 정보 가져오기
	
	CString strSelectedConfigName;
	strSelectedConfigName.Format(_T(""));

	HTREEITEM hItem;
	hItem = m_TreeMain.GetNextItem(NULL, TVGN_CARET); // 현재 선택된 아이템의 핸들을 가져온다.
	strSelectedConfigName = m_TreeMain.GetItemText(hItem);

	// 리스트 컨트롤에 삭제
	if(hItem != NULL)
	{
		if (AfxMessageBox(_T("Delete %s Config?", strSelectedConfigName),MB_OKCANCEL) == 1)
		{
			m_TreeMain.DeleteItem(hItem);
			CString strConfigNum;
			CString strTemp;
			strConfigNum.Format(_T(""));
			strTemp.Format(_T(""));

			std::vector<CString> vTestDIrPath;

			m_TotalData.GetTestDirectoryPath(vTestDIrPath);

			int nDelCount = 0;
			// m_vTestName m_vDirName 에서 해당 정보 삭제
			for (int i= 0; i< vTestDIrPath.size(); i++)
			{
				if (vTestDIrPath[i].Find(strSelectedConfigName))
				{
					m_TotalData.DeleteTestDirectoryPath(strSelectedConfigName);

					if(strTemp == _T(""))
					{
						int nTemp = vTestDIrPath[i].ReverseFind('\\');
						strTemp =  vTestDIrPath[i].Mid(nTemp+1);
						AfxExtractSubString(strConfigNum, strTemp, 4,'_');
						break;
					}
				}
				else
					nDelCount++;
			}
			
			m_TotalData.DeleteFilePath(strSelectedConfigName);			

			nDelCount = 0;
			int nItemCount = m_ListCtrl_Main.GetItemCount();
			for (int i=0 ; i < nItemCount; i++)
			{
				CString strListItem;
				strListItem.Format(_T(""));
				strListItem = m_ListCtrl_Main.GetItemText(nDelCount,0);
				if (strListItem == strConfigNum)
				{
					m_ListCtrl_Main.DeleteItem(nDelCount);
				}
				else
					nDelCount++;
			}
			m_ListLog->WriteLogFile(_T("Delete Config :") + strConfigNum);
		}
	}		
}

BOOL CData_ValidationDlg::CheckExistDataInTree(CString strRefName)
{
	BOOL bResult = FALSE;

	int nItemCount = m_TreeMain.GetCount();
	HTREEITEM hTemp, hNext;


	hNext = m_TreeMain.GetRootItem();
	hTemp = hNext;

	for (int i = 0; i < nItemCount; i++)
	{
		if(strRefName == m_TreeMain.GetItemText(hNext))
		{
			bResult = TRUE;
			break;
		}
		hNext = m_TreeMain.GetNextSiblingItem(hTemp);

	}
	return bResult;
}

void CData_ValidationDlg::AddConfigAndTestToListControl(CString inConfig, std::vector<CString> vTestName)
{
	int nCount = m_ListCtrl_Main.GetItemCount();

	m_ListCtrl_Main.InsertItem(nCount, _T(""));
	m_ListCtrl_Main.SetItem(nCount, 0,LVIF_TEXT,  inConfig,0,0,0,NULL );
	m_ListCtrl_Main.SetItem(nCount, 1,LVIF_TEXT,  _T("Reference File Check"),0,0,0,NULL );
	m_ListCtrl_Main.SetItem(nCount, 2,LVIF_TEXT,  _T("PASS"),0,0,0,NULL);
	m_ListCtrl_Main.SetItem(nCount, 3,LVIF_TEXT,  _T("100%"),0,0,0,NULL);

	nCount++;

	m_ListCtrl_Main.InsertItem(nCount, _T(""));
	m_ListCtrl_Main.SetItem(nCount, 0,LVIF_TEXT,  inConfig,0,0,0,NULL );
	m_ListCtrl_Main.SetItem(nCount, 1,LVIF_TEXT,  _T("Common Value Check"),0,0,0,NULL );
	m_ListCtrl_Main.SetItem(nCount, 2,LVIF_TEXT,  _T("Ready"),0,0,0,NULL);
	m_ListCtrl_Main.SetItem(nCount, 3,LVIF_TEXT,  _T("0%"),0,0,0,NULL);

	nCount++;
	m_ListCtrl_Main.InsertItem(nCount, _T(""));
	m_ListCtrl_Main.SetItem(nCount, 0,LVIF_TEXT,  inConfig,0,0,0,NULL );
	m_ListCtrl_Main.SetItem(nCount, 1,LVIF_TEXT,  _T("Naming Rule"),0,0,0,NULL );
	m_ListCtrl_Main.SetItem(nCount, 2,LVIF_TEXT,  _T("Ready"),0,0,0,NULL);
	m_ListCtrl_Main.SetItem(nCount, 3,LVIF_TEXT,  _T("0%"),0,0,0,NULL);

	nCount++;
	int nTestCount = 0;

	for (int i=nCount; i<vTestName.size()+nCount; i++)
	{
		m_ListCtrl_Main.InsertItem(i, _T(""));
		m_ListCtrl_Main.SetItem(i, 0,LVIF_TEXT,  inConfig,0,0,0,NULL );
		m_ListCtrl_Main.SetItem(i, 1,LVIF_TEXT,  vTestName[nTestCount++],0,0,0,NULL );
		m_ListCtrl_Main.SetItem(i, 2,LVIF_TEXT,  _T("Ready"),0,0,0,NULL);
		m_ListCtrl_Main.SetItem(i, 3,LVIF_TEXT,  _T("0%"),0,0,0,NULL);
		//CreateProgressBar(i,3);
	}
}

void CData_ValidationDlg::CreateProgressBar(int nIndex, int nSubIndex)
{
	CProgressCtrl* ProgEntry = new CProgressCtrl;
	CRect ItemRect;

	RECT rtListCtrl, rtDlg;
	HWND hwndBox = ::GetDlgItem(this->m_hWnd, IDC_LIST_MAIN);

	//Get the Rectangle of the listControl
	::GetWindowRect(hwndBox,&rtListCtrl);

	//Get the Rectangle of the Dialog
	::GetWindowRect(m_hWnd,&rtDlg);

	// Dialog에 위치한 ListCtrl의 left & top 위치를 구한다.
	int nThisLeft = rtListCtrl.left - rtDlg.left;
	int nThisTop  = rtListCtrl.top  - rtDlg.top;

	m_ListCtrl_Main.GetSubItemRect(nIndex, nSubIndex, LVIR_BOUNDS, ItemRect);

	int left	= nThisLeft + ItemRect.left;
	int right	= nThisLeft + ItemRect.right;
	int top		= nThisTop  + ItemRect.top;
	int bottom	= nThisTop  + ItemRect.bottom;

	ProgEntry->Create(PBS_SMOOTH | WS_CHILD | WS_VISIBLE, CRect(left, top, right, bottom), this, 1);
	ProgEntry->SetRange(0, 100);
	ProgEntry->SetPos(0);
}

void CData_ValidationDlg::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	delete m_ListLog;

	CDialogEx::PostNcDestroy();
}


void CData_ValidationDlg::OnBnClickedButtonListlog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strEXEPath = m_TotalData.GetEXEDirectoryPath();
	CString strPath;
	strPath.Format(_T("%s%s"), strEXEPath,_T("\\ListLog"));
	ShellExecute(NULL, _T("open"), strPath, NULL, NULL, SW_SHOW);
}


void CData_ValidationDlg::OnBnClickedButtonResultlog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString strEXEPath = m_TotalData.GetEXEDirectoryPath();
	CString strPath;
	strPath.Format(_T("%s%s"), strEXEPath,_T("\\ResultLog"));
	ShellExecute(NULL, _T("open"), strPath, NULL, NULL, SW_SHOW);
}


void CData_ValidationDlg::AddToTreeTestName(std::vector<CString> vTestDirPath)
{
	// total 에서 dirvector 받기
	std::vector<CString> vTestTemp;
	std::vector<CString> vConfigDIr;

	// tree 에서 값 가져오기
	int nTreeItemCount = m_TreeMain.GetCount();
	std::vector<CString> vTreeItem;
	HTREEITEM hItem, hPre;
	CString strTreeItem;

	hItem = m_TreeMain.GetRootItem();
	int i = 0;
	while(hItem)
	{
		strTreeItem = m_TreeMain.GetItemText(hItem);
		hPre = hItem;
		hItem = m_TreeMain.GetNextItem(hItem, TVGN_NEXT);
		if(vTestDirPath[i++].Find(strTreeItem) == -1)
		{
			continue;
		}
		int nIndex = -1;

		for (int j = 0; j < vTestDirPath.size(); j++)
		{
			nIndex = vTestDirPath[j].ReverseFind('\\');
			vTestTemp.push_back(vTestDirPath[j].Mid(nIndex+1));
		}

		m_TotalData.GetTestNameFromTestDirNameVector(vTestTemp, vConfigDIr);

		for (int j = 0; j < vConfigDIr.size(); j++)
		{
			m_TreeMain.InsertItem(vConfigDIr[j], hPre, NULL);
		}
	}
	UpdateWindow();
}