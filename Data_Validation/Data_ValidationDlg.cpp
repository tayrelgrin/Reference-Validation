
// Data_ValidationDlg.cpp : 구현 파일
//

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
}

BEGIN_MESSAGE_MAP(CData_ValidationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CData_ValidationDlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CData_ValidationDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_REF_SELECT, &CData_ValidationDlg::OnBnClickedButtonRefSelect)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CData_ValidationDlg::OnBnClickedButtonLogin)
END_MESSAGE_MAP()


// CData_ValidationDlg 메시지 처리기

BOOL CData_ValidationDlg::OnInitDialog()
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

	m_ListCtrl_Main.SetExtendedStyle(LVS_EX_GRIDLINES | LVCFMT_CENTER | LVS_EDITLABELS);

	m_ListCtrl_Main.InsertColumn(0, _T("Config"),		LVCFMT_CENTER, 90,  -1);
	m_ListCtrl_Main.InsertColumn(1, _T("Test"),			LVCFMT_CENTER, 100, -1);
	m_ListCtrl_Main.InsertColumn(2, _T("Result"),		LVCFMT_CENTER, 120, -1);
	m_ListCtrl_Main.InsertColumn(3, _T("Progress"),		LVCFMT_CENTER, 200, -1);

	m_TabCtrl_Main.InsertItem(1,_T("List Log"));
	m_TabCtrl_Main.InsertItem(2,_T("Fail Item"));

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
	m_ButtonStop.EnableWindow(TRUE);
	m_ButtonStop.ShowWindow(TRUE);
	m_ButtonStart.EnableWindow(FALSE);
	m_ButtonStart.ShowWindow(FALSE);

	
}


void CData_ValidationDlg::OnBnClickedButtonStop()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_ButtonStop.EnableWindow(FALSE);
	m_ButtonStop.ShowWindow(FALSE);
	m_ButtonStart.EnableWindow(TRUE);
	m_ButtonStart.ShowWindow(TRUE);


}


void CData_ValidationDlg::OnBnClickedButtonRefSelect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	ITEMIDLIST      *pidlBrowse;
	char   Pathname[MAX_PATH];
	BROWSEINFO     BrInfo;


	BrInfo.hwndOwner = GetSafeHwnd();
	BrInfo.pidlRoot = NULL;

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
			m_TotalData.GetDirList(Pathname,m_vDirVector, m_vFileVector);
			bool bCheckResult = m_TotalData.CheckBaseInfoInAllData(Pathname, m_vDirVector);
			if(bCheckResult == false)
			{
				AfxMessageBox("Reference Checking Fail!", MB_OK);
				m_vFileVector.clear();
				m_vDirVector.clear();
			}
		}
		else
		{
			MessageBox(_T("Wrong Folder."), _T("lol"), MB_OKCANCEL|MB_ICONASTERISK );
		}
	}
}


void CData_ValidationDlg::OnBnClickedButtonLogin()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_LogInDlg.DoModal();
}

