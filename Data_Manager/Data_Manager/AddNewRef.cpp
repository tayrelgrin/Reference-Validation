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
	DDX_Control(pDX, IDC_COMBO1, m_cComboPrj);
	DDX_Control(pDX, IDC_COMBO2, m_cComboBuild);
	DDX_Control(pDX, IDC_COMBO3, m_cComboConfig);
	DDX_Control(pDX, IDC_COMBO4, m_cComboDOE);
}


BEGIN_MESSAGE_MAP(AddNewRef, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADDCANCEL, &AddNewRef::OnBnClickedButtonAddcancel)
	ON_BN_CLICKED(IDC_RADIO_REF, &AddNewRef::OnBnClickedRadioRef)
	ON_BN_CLICKED(IDC_RADIO_USEDATA, &AddNewRef::OnBnClickedRadioUsedata)
	ON_EN_CHANGE(IDC_MFCEDITBROWSE1, &AddNewRef::OnEnChangeMfceditbrowse1)
	ON_BN_CLICKED(IDC_BUTTON_ADDOK, &AddNewRef::OnBnClickedButtonAddok)
	ON_CBN_SETFOCUS(IDC_COMBO1, &AddNewRef::OnCbnSetfocusCombo1)
	ON_CBN_SETFOCUS(IDC_COMBO3, &AddNewRef::OnCbnSetfocusCombo3)
	ON_CBN_SETFOCUS(IDC_COMBO4, &AddNewRef::OnCbnSetfocusCombo4)
	ON_CBN_SETFOCUS(IDC_COMBO2, &AddNewRef::OnCbnSetfocusCombo2)
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

	LoadFileListInValue();
	AddProjectToCombo();

	m_cComboPrj.AddString("");
	m_cComboPrj.SetCurSel(0);

	m_editCtrl.OnChangeLayout();

	bPreDataUsed = false;
	GetDlgItem(IDC_BUTTON_ADDOK)->EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void AddNewRef::OnBnClickedRadioRef()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO_USEDATA))->SetCheck(FALSE);

	m_cComboPrj.EnableWindow(FALSE);
	m_cComboBuild.EnableWindow(FALSE);
	m_cComboConfig.EnableWindow(FALSE);
	m_cComboDOE.EnableWindow(FALSE);
	m_editCtrl.EnableWindow(TRUE);

	bPreDataUsed = false;
}

void AddNewRef::OnBnClickedRadioUsedata()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	((CButton*)GetDlgItem(IDC_RADIO_REF))->SetCheck(FALSE);

	m_cComboPrj.EnableWindow(TRUE);
	m_cComboBuild.EnableWindow(TRUE);
	m_cComboConfig.EnableWindow(TRUE);
	m_cComboDOE.EnableWindow(TRUE);
	m_editCtrl.EnableWindow(FALSE);

	bPreDataUsed = true;
}

void AddNewRef::OnEnChangeMfceditbrowse1()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialogEx::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
	std::vector<CString> vDummy;
	m_vStrDir.clear();
	m_editCtrl.GetWindowText(m_strDirRootPath);
	m_cNewConfig.GetDirList(m_strDirRootPath, m_vStrDir,vDummy);
	m_cNewConfig.GetConfigInfoFromVector(m_vStrDir, m_strDirRootPath, m_strPrj, m_strBuild, m_strConfig, m_strDOE);
	EditBoxSetting();

	if(!CheckRefEffective(m_strDirRootPath, m_vStrDir))
	{
		AfxMessageBox("The Reference has some problem, Check it Please!\n Details are in ListLog(TBD)", MB_OK);
		GetDlgItem(IDC_BUTTON_ADDOK)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_ADDOK)->EnableWindow(TRUE);
	}
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

	int nIndex = m_cComboDOE.GetCurSel();
	if(bPreDataUsed)
	{
		m_cComboDOE.GetLBText(nIndex, m_strDOE);
		m_strPreDOE = m_strDOE;
	}

	m_EditPrj.GetWindowText(m_strPrj);
	m_EditBuild.GetWindowText(m_strBuild);
	m_EditConfig.GetWindowText(m_strConfig);
	m_EditDOE.GetWindowText(m_strDOE);

	cNewConfig.SetProject(m_strPrj);
	cNewConfig.SetBuildNum(m_strBuild);
	cNewConfig.SetConfigNum(m_strConfig);
	cNewConfig.SetDOE(m_strDOE);

	if(bPreDataUsed)
	{
		// file copy function
		FileCopy();
	}	
	if(bEffectiveResult)
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

bool AddNewRef::GetPreDataUsed()
{
	return bPreDataUsed;
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


void AddNewRef::LoadFileListInValue()
{
	ConfigDMData cTempConfig;

	CString strEXEDirectory;

	m_vConfigName.clear();

	strEXEDirectory = cTempConfig.GetEXEDirectoryPath();

	strEXEDirectory += "\\Data\\Value";

	SetCurrentDirectory(strEXEDirectory); //현재 검색할 디렉터리 설정.

	CFileFind finder;

	std::vector<CString> vStrFilePath;
	std::vector<CString> vDummy;

	cTempConfig.GetDirList(strEXEDirectory,vDummy, vStrFilePath);

	CString strPrj, strBuild, strConfig, strDOE;

	for (int i = 0; i < vStrFilePath.size(); i++)
	{
		ParsingBBCD(vStrFilePath[i], strPrj, strBuild, strConfig, strDOE);

		CString strComb = strPrj + '_'+ strBuild + '_' + strConfig + '_' + strDOE;

		m_vConfigName.push_back(strComb);
	}
}

void AddNewRef::ParsingBBCD(CString inStr, CString& outStrPrj, CString& outStrBuild, CString& outStrConfig, CString& outStrDOE)
{
	int nIndex = inStr.ReverseFind('\\');
	CString strFileName = inStr.Mid((nIndex+1));
	CString strTemp = inStr.Left(nIndex);

	AfxExtractSubString(outStrBuild,	strFileName,0,'-');
	AfxExtractSubString(outStrConfig,	strFileName,1,'-');
	nIndex = strFileName.Find('-',0);
	nIndex = strFileName.Find('-',nIndex+1);
	outStrDOE = strFileName.Mid(nIndex+1);
	AfxExtractSubString(outStrDOE,		outStrDOE,0,'.');

	nIndex = strTemp.ReverseFind('\\');
	outStrPrj = strTemp.Mid(nIndex+1);
}


void AddNewRef::AddProjectToCombo()
{
	CString strTemp;
	CString strTarget;
	bool bResult = true;
	for (int i = 0; i < m_vConfigName.size(); i++)
	{
		AfxExtractSubString(strTemp,m_vConfigName[i],0,'_');
		for (int j= 0; j< m_cComboPrj.GetCount(); j++)
		{
			m_cComboPrj.GetLBText(j,strTarget);
			if (strTarget == strTemp)
			{
				bResult = false;
			}
		}
		if (bResult)
		{
			m_cComboPrj.AddString(strTemp);
		}
	}
}



void AddNewRef::FindStringInVector(std::vector<CString> invData, CString inTarget, std::vector<CString>& outvData)
{
	for(int i= 0; i<invData.size(); i++)
	{
		if(invData[i].Find(inTarget) != -1)
		{
			outvData.push_back(invData[i]);
		}
	}
}

void AddNewRef::OnCbnSetfocusCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_cComboBuild.ResetContent();
	m_cComboConfig.ResetContent();
	m_cComboDOE.ResetContent();

	m_cComboBuild.AddString("");
	m_cComboBuild.SetCurSel(0);

	int nIndex = m_cComboPrj.GetCurSel();
	m_cComboPrj.GetLBText(nIndex, m_strPrj);

	std::vector<CString> vFileList;
	FindStringInVector(m_vConfigName, m_strPrj, vFileList);
	CString strTemp;
	bool bCompareResult = true;

	for (int i=0; i<vFileList.size(); i++)
	{
		bCompareResult = true;
		AfxExtractSubString(strTemp, vFileList[i], 1, '_');

		for (int j = 0; j< m_cComboBuild.GetCount(); j++)
		{
			CString strTarget;
			m_cComboBuild.GetLBText(j, strTarget);
			if(strTarget == strTemp)
				bCompareResult = false;
		}
		if(bCompareResult)	// 중복 확인 
		{
			m_cComboBuild.AddString(strTemp);
		}
	}
	m_EditPrj.SetWindowText(m_strPrj);
}


void AddNewRef::OnCbnSetfocusCombo2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_cComboConfig.ResetContent();
	m_cComboDOE.ResetContent();

	m_cComboConfig.AddString("");
	m_cComboConfig.SetCurSel(0);

	int nIndex = m_cComboBuild.GetCurSel();
	m_cComboBuild.GetLBText(nIndex, m_strBuild);

	CString strTarget =  m_strPrj+'_' + m_strBuild;

	std::vector<CString> vFileList;
	FindStringInVector(m_vConfigName, strTarget, vFileList);
	CString strTemp;
	bool bCompareResult = true;
	
	for (int i=0; i<vFileList.size(); i++)
	{
		bCompareResult = true;
		AfxExtractSubString(strTemp, vFileList[i], 2, '_');

		for (int j = 0; j< m_cComboConfig.GetCount(); j++)
		{
			CString strTarget;
			m_cComboConfig.GetLBText(j, strTarget);
			if(strTarget == strTemp)
				bCompareResult = false;
		}
		if(bCompareResult)	// 중복 확인 
		{
			m_cComboConfig.AddString(strTemp);
		}
	}
	m_EditBuild.SetWindowText(m_strBuild);
}


void AddNewRef::OnCbnSetfocusCombo3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	m_cComboDOE.ResetContent();

	m_cComboDOE.AddString("");
	m_cComboDOE.SetCurSel(0);

	int nIndex = m_cComboPrj.GetCurSel();
	m_cComboPrj.GetLBText(nIndex, m_strPrj);

	nIndex = m_cComboBuild.GetCurSel();
	m_cComboBuild.GetLBText(nIndex, m_strBuild);

	nIndex = m_cComboConfig.GetCurSel();
	m_cComboConfig.GetLBText(nIndex, m_strConfig);

	std::vector<CString> vFileList;
	CString strTarget =  m_strPrj+'_' + m_strBuild + '_' + m_strConfig;

	FindStringInVector(m_vConfigName, strTarget, vFileList);
	CString strTemp;
	bool bCompareResult = true;

	for (int i=0; i<vFileList.size(); i++)
	{
		bCompareResult = true;
		AfxExtractSubString(strTemp, vFileList[i], 3, '_');

		for (int j = 0; j< m_cComboDOE.GetCount(); j++)
		{
			CString strTarget;
			m_cComboDOE.GetLBText(j, strTarget);
			if(strTarget == strTemp)
				bCompareResult = false;
		}
		if(bCompareResult)	// 중복 확인 
		{
			m_cComboDOE.AddString(strTemp);
		}
	}
	m_EditConfig.SetWindowText(m_strConfig);
}


void AddNewRef::OnCbnSetfocusCombo4()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int nIndex = m_cComboPrj.GetCurSel();
	m_cComboPrj.GetLBText(nIndex, m_strPrj);
	m_strPrePrj = m_strPrj;

	nIndex = m_cComboBuild.GetCurSel();
	m_cComboBuild.GetLBText(nIndex, m_strBuild);
	m_strPreBuild = m_strBuild;

	nIndex = m_cComboConfig.GetCurSel();
	m_cComboConfig.GetLBText(nIndex, m_strConfig);
	m_strPreConfig = m_strConfig;

	nIndex = m_cComboDOE.GetCurSel();
	m_cComboDOE.GetLBText(nIndex, m_strDOE);
	m_strPreDOE = m_strDOE;

	m_EditDOE.SetWindowText(m_strDOE);
}


void AddNewRef::FileCopy()
{
	m_EditPrj.GetWindowText(m_strPrj);
	m_EditBuild.GetWindowText(m_strBuild);
	m_EditConfig.GetWindowText(m_strConfig);
	m_EditDOE.GetWindowText(m_strDOE);

	ConfigDMData cTempConfig;

	CString strPrj, strBuild, strConfig, strDOE;
	CString strEXEDirectory;
	CString strValuePath, strSettingPath;
	CString strOriValuePath, strOriSettingPath;


	int nIndex = m_cComboPrj.GetCurSel();
	m_cComboPrj.GetLBText(nIndex, strPrj);

	nIndex = m_cComboBuild.GetCurSel();
	m_cComboBuild.GetLBText(nIndex, strBuild);

	nIndex = m_cComboConfig.GetCurSel();
	m_cComboConfig.GetLBText(nIndex, strConfig);


	nIndex = m_cComboDOE.GetCurSel();
	m_cComboDOE.GetLBText(nIndex, strDOE);

	strEXEDirectory = cTempConfig.GetEXEDirectoryPath();

	SetCurrentDirectory(strEXEDirectory); //현재 검색할 디렉터리 설정

	strOriValuePath.Format(_T("%s%s%s%s%s%s%s%s%s%s"), strEXEDirectory, "\\Data\\Value\\", strPrj, "\\", strBuild,"-", strConfig, "-", strDOE,".xml");
	strOriSettingPath.Format(_T("%s%s%s%s%s%s%s%s%s%s"),strEXEDirectory,"\\Data\\Setting\\Setting-", strPrj, "-", strBuild, "-", strConfig, "-", strDOE,".xml");

	strValuePath.Format(_T("%s%s%s%s%s%s%s%s%s%s"), strEXEDirectory, "\\Data\\Value\\", m_strPrj, "\\", m_strBuild,"-", m_strConfig, "-", m_strDOE,".xml");
	strSettingPath.Format(_T("%s%s%s%s%s%s%s%s%s%s"),strEXEDirectory,"\\Data\\Setting\\Setting-", m_strPrj, "-", m_strBuild, "-", m_strConfig, "-", m_strDOE,".xml");


	CopyFile(strOriValuePath, strValuePath, TRUE);
	CopyFile(strOriSettingPath, strSettingPath, TRUE);
}

CString AddNewRef::GetPreBuild()
{
	return m_strPreBuild;
}
CString AddNewRef::GetPreProject()
{
	return m_strPrePrj;
}

CString AddNewRef::GetPreConfig()
{
	return m_strPreConfig;
}

CString AddNewRef::GetPreDOE()
{
	return m_strPreDOE;
}


bool AddNewRef::CheckRefEffective(CString instrPath, std::vector<CString> invData)
{
	SetCurrentDirectory(instrPath); //현재 검색할 디렉터리 설정.

	bool bResult = true;
	bEffectiveResult = false;

	int nFileCount = 0;
	int nDirCount = 0;
	CFileFind cFinder;
	CString strFileName;
	CString strDirName;
	CString strDirPath;
	int nFindIndex;
	CString strRegister;
	CString strRefFile;
	CString strError = "";

	std::vector<bool> vResult;

	nDirCount = invData.size();

	if (nDirCount > 3)
	{
		for (int i = 0; i < nDirCount; i++)
		{
			CString strTemp = invData[i];
			SetCurrentDirectory(strTemp);

			BOOL bSearching = cFinder.FindFile();
			nFindIndex = strTemp.ReverseFind('\\');
			strDirName = strTemp.Mid(nFindIndex+1);
			bool bRefFile = false;
			bool bRegister = false;
			bool bSpec = false;		
			bool bDirectory = false;

			strRefFile	= strDirName + ".ini";
			strRegister = strDirName + "_Register.ini";
			nFileCount = 0;

			while(bSearching)
			{
				bSearching = cFinder.FindNextFile();
				strFileName = cFinder.GetFileName();

				if(cFinder.IsArchived())
				{
					strFileName = cFinder.GetFileName();

					if( strFileName == _T(".") ||
						strFileName == _T("..")||
						strFileName == _T("Thumbs.db") ) continue;

					if (strFileName == strRefFile)
					{
						bRefFile = true;
					}
					else if(strFileName == strRegister)
					{
						bRegister = true;
					}
					else if(strFileName == "Spec.ini")
					{
						bSpec = true;
					}

					if (bRegister && bRefFile && bSpec)
					{
						break;
					}
					nFileCount++;
				}
				else if (cFinder.IsDirectory() && !cFinder.IsDots())	// no-spec and REL
				{
					bDirectory = true;
				}
			}
			if (!bDirectory)
			{
				if (bRegister && bRefFile && bSpec && (nFileCount >4) )
				{
					vResult.push_back(true);
				}
				else
				{
					vResult.push_back(false);
				}
			}
		}

		for (int i = 0; i < vResult.size() ; i++)
		{
			if(vResult[i] == false)
			{

				bResult = false;
				break;
			}
		}	
	}
	if(vResult.size()<3)
		bResult = false;

	if (bResult)
	{
		bEffectiveResult = true;
	}

	return bResult;
}