
// Data_ValidationDlg.cpp : ���� ����
#include "stdafx.h"
#include "Data_Validation.h"
#include "Data_ValidationDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CData_ValidationDlg ��ȭ ����




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
END_MESSAGE_MAP()


// CData_ValidationDlg �޽��� ó����

BOOL CData_ValidationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�. ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	//////////////////////////////////////////////////////////////////////////
	m_ListCtrl_Main.SetExtendedStyle(LVS_EX_GRIDLINES | LVCFMT_CENTER | LVS_EDITLABELS);

	m_ListCtrl_Main.InsertColumn(0, _T("Config"),		LVCFMT_CENTER, 90,  -1);
	m_ListCtrl_Main.InsertColumn(1, _T("Test"),			LVCFMT_CENTER, 100, -1);
	m_ListCtrl_Main.InsertColumn(2, _T("Result"),		LVCFMT_CENTER, 120, -1);
	m_ListCtrl_Main.InsertColumn(3, _T("Progress"),		LVCFMT_CENTER, 200, -1);

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

	m_ListLogDlg.AddListLog("Load XML File List From Value Directory");
	m_TotalData.LoadXMLFileListInValue();

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�. ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CData_ValidationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ����ڰ� �ּ�ȭ�� â�� ���� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CData_ValidationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CData_ValidationDlg::OnBnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_ButtonStop.EnableWindow(TRUE);
	m_ButtonStop.ShowWindow(TRUE);
	m_ButtonStart.EnableWindow(FALSE);
	m_ButtonStart.ShowWindow(FALSE);

	int nIndex = m_TreeMain.GetCount();

	do
	{
		if(nIndex < 1)
		{
			AfxMessageBox("No Reference!\nChoose Reference ", MB_OK);
			break;
		}

		if(m_ConfigSelectDlg.DoModal() == true)
		{
			// ���콺 wait start
			BeginWaitCursor();
			// m_ConfigSelectDlg���� ���� ��������
			// ���ǹ� : ������ �� ���� ��� ����

			m_ListLogDlg.AddListLog("Start Reference Validation");

			// Validation start
			m_TotalData.Validation();

			// ���콺 wait end
			EndWaitCursor();
		}
	}while(false);	
}


void CData_ValidationDlg::OnBnClickedButtonStop()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_ButtonStop.EnableWindow(FALSE);
	m_ButtonStop.ShowWindow(FALSE);
	m_ButtonStart.EnableWindow(TRUE);
	m_ButtonStart.ShowWindow(TRUE);

	if (AfxMessageBox("Stop the validation?",MB_OKCANCEL)==1)
	{
		m_ListLogDlg.AddListLog("Stop Reference Validation");
	}	
}


void CData_ValidationDlg::OnBnClickedButtonRefSelect()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	ITEMIDLIST      *pidlBrowse;
	char   Pathname[MAX_PATH];
	BROWSEINFO     BrInfo;

	std::vector<CString> vTestDir;
	std::vector<CString> vFileNames;

	m_ListLogDlg.AddListLog("Pushed Select Ref Button");

	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;

	vTestDir.clear();
	vFileNames.clear();

	memset( &BrInfo, 0, sizeof(BrInfo) );
	BrInfo.pszDisplayName =(LPTSTR)Pathname;
	BrInfo.lpszTitle = _T("Choose Reference Directory to Validate.");
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;

	// ���� ���� ���̾�α� ����
	pidlBrowse = SHBrowseForFolder(&BrInfo);
	if( pidlBrowse != NULL)
	{
		// �н��� ����
		BOOL bSuccess = ::SHGetPathFromIDList(pidlBrowse, (LPTSTR)Pathname);
		if ( bSuccess )
		{
			// file, directory check
			m_TotalData.GetDirList(Pathname,vTestDir, vFileNames);
			m_ListLogDlg.AddListLog(Pathname);
			m_ListLogDlg.AddListLog("Check Base Info In All Data");

			bool bCheckResult = m_TotalData.CheckBaseInfoInAllData(Pathname, vTestDir);
			if(bCheckResult == false)
			{
				m_ListLogDlg.AddListLog("Reference Checking Fail!");
				AfxMessageBox("Reference Checking Fail!", MB_OK);
				vTestDir.clear();
				vFileNames.clear();
			}
			else
			{
				m_TotalData.AddRootPath(Pathname);
				m_ListLogDlg.AddListLog("Check Base Info In All Data : PASS");
				CString strRefName, strTemp;
				strRefName.Format("");
				strTemp.Format("");
				strTemp = Pathname;
				int nIndex = strTemp.ReverseFind('\\');
				strRefName = strTemp.Mid(nIndex+1);
				
				// check same item in tree
				BOOL bCheckResult = CheckExistDataInTree(strRefName);
				// Add To Tree
				if(bCheckResult == FALSE)
				{
					AddToTreeRefName(strRefName);

					// Add To member vector
					m_TotalData.AddTestDirectoryPath(vTestDir);
					m_TotalData.AddFilePath(vFileNames);
					m_ListLogDlg.AddListLog("Add to Member Vector");

					// Extract Test Name From Dir Vector
					std::vector<CString> vTestName;
					std::vector<CString> vTempName;
					CString strConfig;
					strConfig.Format("");

					m_TotalData.RemoveRootPathInVector( vTestDir,  vTempName,  Pathname);
					m_ListLogDlg.AddListLog("Remove Root Path in Directory Vector");

					m_TotalData.GetConfigFromTestDirNameVector(vTempName, strConfig);
					m_ListLogDlg.AddListLog("Extract Config : " + strConfig );

					m_TotalData.GetTestNameFromTestDirNameVector(vTempName, vTestName);
					m_ListLogDlg.AddListLog("Extract Test Name From Directory Name");

					// Add To ListControl
					AddConfigAndTestToListControl(strConfig, vTestName);
				}
				else
				{
					AfxMessageBox("Already Same Config in Data ", MB_OK);
				}
			}
		}
		else
		{
			m_ListLogDlg.AddListLog("Wrong Folder.");
			MessageBox(_T("Wrong Folder."), _T("lol"), MB_OKCANCEL|MB_ICONASTERISK );
		}
	}
}


void CData_ValidationDlg::OnBnClickedButtonLogin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_ListLogDlg.AddListLog("Log in");
	m_LogInDlg.DoModal();
}



void CData_ValidationDlg::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
}


void CData_ValidationDlg::OnNMRClickTreeMain(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	// ���� ��ư �߰�
}


void CData_ValidationDlg::OnBnClickedButtonDelete()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// Ʈ������ ������ ������ ���� ��������
	
	CString strSelectedConfigName;
	strSelectedConfigName.Format("");

	HTREEITEM hItem;
	hItem = m_TreeMain.GetNextItem(NULL, TVGN_CARET); // ���� ���õ� �������� �ڵ��� �����´�.
	strSelectedConfigName = m_TreeMain.GetItemText(hItem);

	// ����Ʈ ��Ʈ�ѿ� ����
	if(hItem != NULL)
	{
		if (AfxMessageBox(_T("Delete %s Config?", strSelectedConfigName),MB_OKCANCEL) == 1)
		{
			m_TreeMain.DeleteItem(hItem);
			CString strConfigNum;
			CString strTemp;
			strConfigNum.Format("");
			strTemp.Format("");

			std::vector<CString> vTestDIrPath;

			m_TotalData.GetTestDirectoryPath(vTestDIrPath);

			int nDelCount = 0;
			// m_vTestName m_vDirName ���� �ش� ���� ����
			for (int i= 0; i< vTestDIrPath.size(); i++)
			{
				if (vTestDIrPath[i].Find(strSelectedConfigName))
				{
					m_TotalData.DeleteTestDirectoryPath(strSelectedConfigName);

					if(strTemp == "")
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
			
			m_TotalData.DeleteFilPath(strSelectedConfigName);			

			nDelCount = 0;
			int nItemCount = m_ListCtrl_Main.GetItemCount();
			for (int i=0 ; i < nItemCount; i++)
			{
				CString strListItem;
				strListItem.Format("");
				strListItem = m_ListCtrl_Main.GetItemText(nDelCount,0);
				if (strListItem == strConfigNum)
				{
					m_ListCtrl_Main.DeleteItem(nDelCount);
				}
				else
					nDelCount++;
			}
			m_ListLogDlg.AddListLog("Delete Config :" + strConfigNum);
		}
	}		
}

BOOL CData_ValidationDlg::CheckExistDataInTree(CString strRefName)
{
	BOOL bResult = FALSE;

	return bResult;
}

void CData_ValidationDlg::AddConfigAndTestToListControl(CString inConfig, std::vector<CString> vTestName)
{
	for (int i=0; i<vTestName.size(); i++)
	{
		m_ListCtrl_Main.InsertItem(i, "");
		m_ListCtrl_Main.SetItem(i, 0,LVIF_TEXT,  inConfig,0,0,0,NULL );
		m_ListCtrl_Main.SetItem(i, 1,LVIF_TEXT,  vTestName[i],0,0,0,NULL );
		m_ListCtrl_Main.SetItem(i, 2,LVIF_TEXT,  "Ready",0,0,0,NULL);
		m_ListCtrl_Main.SetItem(i, 3,LVIF_TEXT,  "0%",0,0,0,NULL);
		//CreateProgressBar(i,3);
	}
}

void CData_ValidationDlg::CreateProgressBar(int nIndex, int nSubIndex)
{
	CProgressCtrl* ProgEntry = new CProgressCtrl;
	CRect ItemRect;

	RECT rtListCtrl, rtDlg, rtSubItem;
	HWND hwndBox = ::GetDlgItem(this->m_hWnd, IDC_LIST_MAIN);

	//Get the Rectangle of the listControl
	::GetWindowRect(hwndBox,&rtListCtrl);

	//Get the Rectangle of the Dialog
	::GetWindowRect(m_hWnd,&rtDlg);

	// Dialog�� ��ġ�� ListCtrl�� left & top ��ġ�� ���Ѵ�.
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