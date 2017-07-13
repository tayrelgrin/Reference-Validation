// Config_Select_Dlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Validation.h"
#include "Config_Select_Dlg.h"
#include "afxdialogex.h"
#include "resource.h" 

// Config_Select_Dlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(Config_Select_Dlg, CDialogEx)

Config_Select_Dlg::Config_Select_Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Config_Select_Dlg::IDD, pParent)
{

}

Config_Select_Dlg::~Config_Select_Dlg()
{
}

void Config_Select_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_PRJ, m_cCombo_Prj);
	DDX_Control(pDX, IDC_COMBO_BUILD, m_cCombo_Build);
	DDX_Control(pDX, IDC_COMBO_CONFIG, m_cCombo_Config);
	DDX_Control(pDX, IDC_COMBO_DOE, m_cCombo_DOE);
}


BEGIN_MESSAGE_MAP(Config_Select_Dlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_PRJ, &Config_Select_Dlg::OnCbnSelchangeComboPrj)
	ON_CBN_SELCHANGE(IDC_COMBO_BUILD, &Config_Select_Dlg::OnCbnSelchangeComboBuild)
	ON_CBN_SELCHANGE(IDC_COMBO_CONFIG, &Config_Select_Dlg::OnCbnSelchangeComboConfig)
	ON_CBN_SELCHANGE(IDC_COMBO_DOE, &Config_Select_Dlg::OnCbnSelchangeComboDoe)
	ON_BN_CLICKED(IDOK, &Config_Select_Dlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Config_Select_Dlg �޽��� ó�����Դϴ�.


BOOL Config_Select_Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	m_strProject.Format(_T(""));
	m_strBuild.Format(_T(""));
	m_strConfig.Format(_T(""));
	m_strDOE.Format(_T(""));

	AddPrjToCombo();

	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}

void Config_Select_Dlg::SetValueFileList(std::vector<CString> inValueFiles)
{
	m_vValueFiles.assign(inValueFiles.begin(), inValueFiles.end());
}

void Config_Select_Dlg::AddPrjToCombo()
{
	CString strTemp;
	CString strTarget;
	bool bResult = true;
	for (int i = 0; i < m_vValueFiles.size(); i++)
	{
		bResult = true;
		AfxExtractSubString(strTemp,m_vValueFiles[i],0,'_');
		for (int j= 0; j< m_cCombo_Prj.GetCount(); j++)
		{
			m_cCombo_Prj.GetLBText(j,strTarget);
			if (strTarget == strTemp)
			{
				bResult = false;
			}
		}
		if (bResult)
		{
			m_cCombo_Prj.AddString(strTemp);
		}
	}
}

void Config_Select_Dlg::OnCbnSelchangeComboPrj()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cCombo_Build.ResetContent();
	m_cCombo_Config.ResetContent();
	m_cCombo_DOE.ResetContent();

//	m_cCombo_Build.AddString(_T(""));
	m_cCombo_Build.SetCurSel(0);

	int nIndex = m_cCombo_Prj.GetCurSel();
	m_cCombo_Prj.GetLBText(nIndex, m_strProject);

	std::vector<CString> vFileList;
	FindStringInVector(m_vValueFiles, m_strProject, vFileList);
	CString strTemp;
	bool bCompareResult = true;

	for (int i=0; i<vFileList.size(); i++)
	{
		bCompareResult = true;
		AfxExtractSubString(strTemp, vFileList[i], 1, '_');

		for (int j = 0; j< m_cCombo_Build.GetCount(); j++)
		{
			CString strTarget;
			m_cCombo_Build.GetLBText(j, strTarget);
			if(strTarget == strTemp)
				bCompareResult = false;
		}
		if(bCompareResult)	// �ߺ� Ȯ�� 
		{
			m_cCombo_Build.AddString(strTemp);
		}
	}
}

void Config_Select_Dlg::FindStringInVector(std::vector<CString> invData, CString inTarget, std::vector<CString>& outvData)
{
	for(int i= 0; i<invData.size(); i++)
	{
		if(invData[i].Find(inTarget) != -1)
		{
			outvData.push_back(invData[i]);
		}
	}
}

void Config_Select_Dlg::OnCbnSelchangeComboBuild()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cCombo_Config.ResetContent();
	m_cCombo_DOE.ResetContent();

	//m_cCombo_Config.AddString(_T(""));
	m_cCombo_Config.SetCurSel(0);

	int nIndex = m_cCombo_Build.GetCurSel();
	m_cCombo_Build.GetLBText(nIndex, m_strBuild);

	CString strTarget =  m_strProject+'_' + m_strBuild;

	std::vector<CString> vFileList;
	FindStringInVector(m_vValueFiles, strTarget, vFileList);
	CString strTemp;
	bool bCompareResult = true;

	for (int i=0; i<vFileList.size(); i++)
	{
		bCompareResult = true;
		AfxExtractSubString(strTemp, vFileList[i], 2, '_');

		for (int j = 0; j< m_cCombo_Config.GetCount(); j++)
		{
			CString strTargetConfig;
			m_cCombo_Config.GetLBText(j, strTargetConfig);
			if(strTargetConfig == strTemp)
				bCompareResult = false;
		}
		if(bCompareResult)	// �ߺ� Ȯ�� 
		{
			m_cCombo_Config.AddString(strTemp);
		}
	}
}


void Config_Select_Dlg::OnCbnSelchangeComboConfig()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_cCombo_DOE.ResetContent();

	//m_cCombo_DOE.AddString(_T(""));
	m_cCombo_DOE.SetCurSel(0);

	int nIndex = m_cCombo_Prj.GetCurSel();
	m_cCombo_Prj.GetLBText(nIndex, m_strProject);

	nIndex = m_cCombo_Build.GetCurSel();
	m_cCombo_Build.GetLBText(nIndex, m_strBuild);

	nIndex = m_cCombo_Config.GetCurSel();
	m_cCombo_Config.GetLBText(nIndex, m_strConfig);

	std::vector<CString> vFileList;
	CString strTarget =  m_strProject+'_' + m_strBuild + '_' + m_strConfig;

	FindStringInVector(m_vValueFiles, strTarget, vFileList);
	CString strTemp;
	bool bCompareResult = true;

	for (int i=0; i<vFileList.size(); i++)
	{
		bCompareResult = true;
		AfxExtractSubString(strTemp, vFileList[i], 3, '_');

		for (int j = 0; j< m_cCombo_DOE.GetCount(); j++)
		{
			CString strTargetConfig;
			m_cCombo_DOE.GetLBText(j, strTargetConfig);
			if(strTargetConfig == strTemp)
				bCompareResult = false;
		}
		if(bCompareResult)	// �ߺ� Ȯ�� 
		{
			m_cCombo_DOE.AddString(strTemp);
		}
	}
}


void Config_Select_Dlg::OnCbnSelchangeComboDoe()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	int nIndex = m_cCombo_Prj.GetCurSel();
	m_cCombo_Prj.GetLBText(nIndex, m_strProject);

	nIndex = m_cCombo_Build.GetCurSel();
	m_cCombo_Build.GetLBText(nIndex, m_strBuild);

	nIndex = m_cCombo_Config.GetCurSel();
	m_cCombo_Config.GetLBText(nIndex, m_strConfig);

	nIndex = m_cCombo_DOE.GetCurSel();
	m_cCombo_DOE.GetLBText(nIndex, m_strDOE);
}


void Config_Select_Dlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if(m_strProject != "" && 
		m_strBuild != "" &&
		m_strConfig != "" &&
		m_strDOE != "")
	{
		CDialogEx::OnOK();
	}
	else
	{
		AfxMessageBox(_T("Choose Reference "), MB_OK);
	}
}


CString Config_Select_Dlg::GetProject()
{
	return m_strProject;
}
CString Config_Select_Dlg::GetBuild()
{
	return m_strBuild;
}
CString Config_Select_Dlg::GetConfig()
{
	return m_strConfig;
}
CString Config_Select_Dlg::GetDOE()
{
	return m_strDOE;
}