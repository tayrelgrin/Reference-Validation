// SettingBaseInfo.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "SettingBaseInfo.h"
#include "afxdialogex.h"


// SettingBaseInfo ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(SettingBaseInfo, CDialogEx)

SettingBaseInfo::SettingBaseInfo(CWnd* pParent /*=NULL*/)
	: CDialogEx(SettingBaseInfo::IDD, pParent)
{
	m_pwndShow = NULL;
}

SettingBaseInfo::~SettingBaseInfo()
{
}

void SettingBaseInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_Tab);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_cButton_Save);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_cButton_EXIT);
}


BEGIN_MESSAGE_MAP(SettingBaseInfo, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &SettingBaseInfo::OnBnClickedButtonSave)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &SettingBaseInfo::OnTcnSelchangeTab1)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &SettingBaseInfo::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// SettingBaseInfo �޽��� ó�����Դϴ�.




BOOL SettingBaseInfo::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_cButton_Save.LoadBitmaps(IDB_BITMAP_SAVE, IDB_BITMAP_SAVEPUSH, NULL, NULL);
	m_cButton_Save.SizeToContent();

	CString strTarget;

	strTarget.Format("%s%s","Setting : ", m_strSettingText );

	SetDlgItemText(IDC_STATIC_SETTING, strTarget);

	m_cButton_EXIT.LoadBitmaps(IDB_BITMAP_EXIT, IDB_BITMAP_EXITPUSH, NULL, NULL);
	m_cButton_EXIT.SizeToContent();
	m_Tab.InsertItem(1,_T("Base Info Items"));
	m_Tab.InsertItem(2,_T("Register"));
	m_Tab.InsertItem(3,_T("File List"));
 	
	CRect rect;

	m_Tab.GetClientRect(&rect);

	m_TabBaseInfo.Create(IDD_DIALOG_BASEITEM, &m_Tab);

	//////////////////////////////////////////////////////////////////////////
	// Base Info Items Tab init

	AddFileNameToComboBox(m_TabBaseInfo.m_cComboFiles);
	
	m_TabBaseInfo.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_SHOWWINDOW | SWP_NOZORDER);
	m_pwndShow = &m_TabBaseInfo;
	//////////////////////////////////////////////////////////////////////////

	m_TabRegister.Create(IDD_DIALOG_REGISTER, &m_Tab);
	m_TabRegister.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_NOZORDER);

	m_TabFileList.m_pData = m_pData;
	m_TabFileList.m_vConfigFileList = m_vConfigFileList;		// Ref ���� ���� ���
	m_TabFileList.m_vSettingFileList = m_vSettingFileList;		// �⺻ ���� ���� ���

	m_TabFileList.Create(IDD_DIALOG_FILELIST, &m_Tab);
	m_TabFileList.SetWindowPos(NULL, 5, 25, rect.Width()-10, rect.Height()-30, SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void SettingBaseInfo::AddFileNameToComboBox(CComboBox& incTarget)
{
	CString strTEMPs;
	strTEMPs.Empty();

	for(int i = 0; i < m_vSettingFileList.size(); i++)
	{
		CString strOriFilePath = m_vSettingFileList[i];
		CString strTest, strFile;
		if(strOriFilePath.Find('\\') == -1 && strOriFilePath=="")
		{
			AfxExtractSubString(strTest, strOriFilePath, 0, ':');
			AfxExtractSubString(strFile, strOriFilePath, 1, ':');
		}
		else
		{
			AfxExtractSubString(strTEMPs, strOriFilePath, 1, '\\');
			AfxExtractSubString(strTest, strTEMPs, 0, ':');
			AfxExtractSubString(strFile, strTEMPs, 1, ':');

			if(strTEMPs == "")	// Ȯ������
			{
				AfxExtractSubString(strTest, strOriFilePath, 2, ':');
				if(strTest != "")
				{
					AfxExtractSubString(strTest, strOriFilePath, 1, ':');
					AfxExtractSubString(strFile, strOriFilePath, 2, ':');
				}
				else
				{
					AfxExtractSubString(strTest, strOriFilePath, 0, ':');
					AfxExtractSubString(strFile, strOriFilePath, 1, ':');
				}
			}
		}
		CString strCompare;
		bool bResult = false;

		for (int index = 0; incTarget.GetCount() > index; index++ )
		{
			incTarget.GetLBText(index, strCompare);
			if(strCompare == strTest)
				bResult = true;
		}
		if(!bResult)
			incTarget.AddString(strTest);
	}
}


void SettingBaseInfo::OnBnClickedButtonSave()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}


void SettingBaseInfo::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	*pResult = 0;

	if (m_pwndShow != NULL)
	{
		m_pwndShow->ShowWindow(SW_HIDE);
		m_pwndShow = NULL;
	}

	int nIndex = m_Tab.GetCurSel();

	switch (nIndex)
	{
	case 0:
		for(int i = 0; i < m_vSettingFileList.size(); i++)
		{
			m_TabBaseInfo.m_cComboFiles.AddString(m_vSettingFileList[i]);
		}
		
		m_TabBaseInfo.ShowWindow(SW_SHOW);
		m_pwndShow = &m_TabBaseInfo;
		break;
	case 1:
		m_TabRegister.ShowWindow(SW_SHOW);
		m_pwndShow = &m_TabRegister;
		break;
	case 2:
		m_TabFileList.ShowWindow(SW_SHOW);
		m_pwndShow = &m_TabFileList;
		break;
	}
}


void SettingBaseInfo::OnBnClickedButtonExit()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	::SendMessage(this->m_hWnd, WM_CLOSE,NULL,NULL);
}
