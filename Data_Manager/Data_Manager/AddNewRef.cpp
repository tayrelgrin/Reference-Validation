// AddNewRef.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "AddNewRef.h"
#include "afxdialogex.h"


// AddNewRef ��ȭ �����Դϴ�.

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


// AddNewRef �޽��� ó�����Դϴ�.


void AddNewRef::OnBnClickedButtonAddcancel()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	::SendMessage(this->m_hWnd, WM_CLOSE,NULL,NULL);
}


BOOL AddNewRef::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	((CButton*)GetDlgItem(IDC_RADIO_REF))->SetCheck(TRUE);
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void AddNewRef::OnBnClickedRadioRef()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CButton*)GetDlgItem(IDC_RADIO_USEDATA))->SetCheck(FALSE);
}


void AddNewRef::OnBnClickedRadioUsedata()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	((CButton*)GetDlgItem(IDC_RADIO_REF))->SetCheck(FALSE);
}



void AddNewRef::OnEnChangeMfceditbrowse1()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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