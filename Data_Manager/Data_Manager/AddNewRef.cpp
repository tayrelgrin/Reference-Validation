// AddNewRef.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "AddNewRef.h"
#include "afxdialogex.h"


// AddNewRef 대화 상자입니다.

IMPLEMENT_DYNAMIC(AddNewRef, CDialogEx)

AddNewRef::AddNewRef(CWnd* pParent /*=NULL*/)
	: CDialogEx(AddNewRef::IDD, pParent)
{
	
}

AddNewRef::~AddNewRef()
{
	InitAllData();
}

void AddNewRef::InitAllData()
{
	m_vStrDir.clear();
}

void AddNewRef::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MFCEDITBROWSE1, m_editCtrl);
	DDX_Control(pDX, IDC_EDIT_PrjName, m_EditPrj);
	DDX_Control(pDX, IDC_EDIT_BUILDNUM, m_EditBuild);
	DDX_Control(pDX, IDC_EDIT_CONFIGNUM, m_EditConfig);
	DDX_Control(pDX, IDC_EDIT_DOE, m_EditDOE);
}


BEGIN_MESSAGE_MAP(AddNewRef, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDCANCEL, &AddNewRef::OnBnClickedButtonAddcancel)
	ON_BN_CLICKED(IDC_RADIO_REF, &AddNewRef::OnBnClickedRadioRef)
	ON_BN_CLICKED(IDC_RADIO_USEDATA, &AddNewRef::OnBnClickedRadioUsedata)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &AddNewRef::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDC_BUTTON_ADDOK, &AddNewRef::OnBnClickedButtonAddok)
END_MESSAGE_MAP()


// AddNewRef 메시지 처리기입니다.


void AddNewRef::OnBnClickedButtonAddcancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	::SendMessage(this->m_hWnd, WM_CLOSE,NULL,NULL);
}


BOOL AddNewRef::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO_REF))->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void AddNewRef::OnBnClickedRadioRef()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO_USEDATA))->SetCheck(FALSE);
}


void AddNewRef::OnBnClickedRadioUsedata()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO_REF))->SetCheck(FALSE);
}



void AddNewRef::OnEnChangeMfceditbrowse1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	for(int i= 0; i<m_vStrDir.size(); i++)
	{
		m_vStrDir.erase(m_vStrDir.begin()+i);
	}
	std::vector<CString> vDummy;
	m_vStrDir.clear();
	//m_editCtrl.GetWindowTextW(m_strDirRootPath);
	m_editCtrl.GetWindowText(m_strDirRootPath);
	m_cNewConfig.GetDirList(m_strDirRootPath, m_vStrDir,vDummy);
	m_cNewConfig.GetConfigInfoFromVector(m_vStrDir, m_strDirRootPath, m_strPrj, m_strBuild, m_strConfig, m_strDOE);
	EditBoxSetting();
}


void AddNewRef::CopyConfigData(ConfigDMData inData)
{
	//m_cNewConfig = inData;
}

void AddNewRef::EditBoxSetting()
{
	CEdit *p=(CEdit *)GetDlgItem(IDC_EDIT_PrjName);
	p->SetWindowText(m_strPrj);

	p=(CEdit *)GetDlgItem(IDC_EDIT_BUILDNUM);
	p->SetWindowText(m_strBuild);

	p=(CEdit *)GetDlgItem(IDC_EDIT_CONFIGNUM);
	p->SetWindowText(m_strConfig);

	p=(CEdit *)GetDlgItem(IDC_EDIT_DOE);
	p->SetWindowText(m_strDOE);
}

void AddNewRef::OnBnClickedButtonAddok()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	ConfigDMData cNewConfig;

	cNewConfig.SetProject(m_strPrj);
	cNewConfig.SetBuildNum(m_strBuild);
	cNewConfig.SetConfigNum(m_strConfig);
	cNewConfig.SetDOE(m_strDOE);

	CDialogEx::OnOK();
}


CString AddNewRef::GetBuild()
{
	return m_strBuild;
}

CString AddNewRef::GetProject()
{
	return m_strPrj;
}

CString AddNewRef::GetDOE()
{
	return m_strDOE;
}

CString AddNewRef::GetConfig()
{
	return m_strConfig;
}

void AddNewRef::GetDirList(std::vector<CString>& inVDirList)
{
	inVDirList.clear();
	inVDirList.assign(m_vStrDir.begin(), m_vStrDir.end());
}

CString AddNewRef::GetDirRootPath()
{
	return m_strDirRootPath;
}