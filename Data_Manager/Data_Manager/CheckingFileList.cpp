// CheckingFileList.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "CheckingFileList.h"
#include "afxdialogex.h"


// CheckingFileList 대화 상자입니다.

IMPLEMENT_DYNAMIC(CheckingFileList, CDialogEx)

CheckingFileList::CheckingFileList(CWnd* pParent /*=NULL*/)
	: CDialogEx(CheckingFileList::IDD, pParent)
{

}

CheckingFileList::~CheckingFileList()
{
}

void CheckingFileList::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LSFL, m_cButton_LoadSetting);
	DDX_Control(pDX, IDC_BUTTON_RLFL, m_cButton_Reload);
	DDX_Control(pDX, IDC_BUTTON_ADDITEM, m_cButton_Add);
	DDX_Control(pDX, IDC_BUTTON_DELETEITEM, m_cButton_Remove);
	DDX_Control(pDX, IDC_TREE2, m_treectrlFileList);
	DDX_Control(pDX, IDC_LIST6, m_ListctrlFileList);
}


BEGIN_MESSAGE_MAP(CheckingFileList, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_LSFL, &CheckingFileList::OnBnClickedButtonLsfl)
	ON_BN_CLICKED(IDC_BUTTON_ADDITEM, &CheckingFileList::OnBnClickedButtonAdditem)
	ON_BN_CLICKED(IDC_BUTTON_DELETEITEM, &CheckingFileList::OnBnClickedButtonDeleteitem)
	ON_NOTIFY(NM_CLICK, IDC_TREE2, &CheckingFileList::OnNMClickTree2)
END_MESSAGE_MAP()


// CheckingFileList 메시지 처리기입니다.


BOOL CheckingFileList::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bModifyFlag = false;

	m_cButton_Reload.LoadBitmaps(IDB_BITMAP_RELOAD,IDB_BITMAP_RELOADPUSH,NULL,NULL);
	m_cButton_Reload.SizeToContent();

	m_cButton_LoadSetting.LoadBitmaps(IDB_BITMAP_LOADSETTING,IDB_BITMAP_LOADSETTINGPUSH,NULL,NULL);
	m_cButton_LoadSetting.SizeToContent();

	AddFileNameToTreeView(m_treectrlFileList);
	

	m_cButton_LoadSetting.LoadBitmaps(IDB_BITMAP_LOADSETTING,IDB_BITMAP_LOADSETTINGPUSH,NULL,NULL);
	m_cButton_LoadSetting.SizeToContent();
	
	m_cButton_Add.LoadBitmaps(IDB_BITMAP_RIGHT,IDB_BITMAP_RIGHTPUSH,NULL,NULL);
	m_cButton_Add.SizeToContent();
	m_cButton_Remove.LoadBitmaps(IDB_BITMAP_LEFT,IDB_BITMAP_LEFTPUSH,NULL,NULL);
	m_cButton_Remove.SizeToContent();


	m_ListctrlFileList.SetExtendedStyle(LVS_EX_GRIDLINES | LVCFMT_CENTER | LVS_EDITLABELS);

	m_ListctrlFileList.InsertColumn(0, _T("Test"), LVCFMT_CENTER, 110,  -1);
	m_ListctrlFileList.InsertColumn(1, _T("File"), LVCFMT_CENTER, 170, -1);
	AddFileNameToListview();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CheckingFileList::AddFileNameToTreeView(CTreeCtrl& incTarget)
{
	CString strTEMPs;
	strTEMPs.Empty();

	HTREEITEM h_Root;
	HTREEITEM h_Child;
	HTREEITEM h_2Child;

	for(int i = 0; i < m_vConfigFileList.size(); i++)
	{
		CString strOriFilePath = m_vConfigFileList[i];
		CString strDir, strTest, strFile;

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

			if(strTEMPs == "")	// 확인하자
			{
				AfxExtractSubString(strTest, strOriFilePath, 2, ':');
				if(strTest != "")
				{
					AfxExtractSubString(strDir, strOriFilePath, 0, ':');
					AfxExtractSubString(strTest, strOriFilePath, 1, ':');
					strTest = strDir + ":" + strTest;
					AfxExtractSubString(strFile, strOriFilePath, 2, ':');
				}
				else
				{
					AfxExtractSubString(strTest, strOriFilePath, 0, ':');
					AfxExtractSubString(strFile, strOriFilePath, 1, ':');
				}
			}
		}
		std::string strCompare;
		bool bResult = false;

		if(incTarget.GetCount() > 0 && i != 0)	
			strCompare = incTarget.GetItemText(h_Child);	// Serach in h_Child level in tree

		if(strTest != strCompare.c_str())
			h_Child = incTarget.InsertItem(strTest, TVI_ROOT, TVI_LAST);

		h_2Child = incTarget.InsertItem(strFile, h_Child, NULL);
	}
}

void CheckingFileList::AddFileNameToListview()
{
	m_ListctrlFileList.DeleteAllItems(); 
	CString strTEMPs;

	for(int i = 0; i < m_vSettingFileList.size(); i++)
	{
		CString strOriFilePath = m_vSettingFileList[i];
		CString strDir, strTest, strFile;
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

			if(strTEMPs == "")	// 확인하자
			{
				AfxExtractSubString(strTest, strOriFilePath, 2, ':');
				if(strTest != "")
				{
					AfxExtractSubString(strDir, strOriFilePath, 0, ':');
					AfxExtractSubString(strTest, strOriFilePath, 1, ':');
					strTest = strDir + ":" + strTest;
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

		int nIndex;
		CString strTempTest;
		CString strTempFile;

		for (nIndex = 0; m_ListctrlFileList.GetItemCount() > nIndex; nIndex++ )
		{
			strTempTest = m_ListctrlFileList.GetItemText(nIndex,0);
			strTempFile = m_ListctrlFileList.GetItemText(nIndex,1);
			if(strTempFile == strFile && strTempTest == strTest)
			{
				bResult = true;
				break;
			}
		}

		if(!bResult)
		{
			m_ListctrlFileList.InsertItem(nIndex, strTest);
			m_ListctrlFileList.SetItem(nIndex, 1,LVIF_TEXT,  strFile ,0,0,0,NULL);
		}
	}
}

void CheckingFileList::OnBnClickedButtonLsfl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 세팅 파일 읽어오기
}


void CheckingFileList::OnBnClickedButtonAdditem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UINT uCount = m_treectrlFileList.GetVisibleCount();
	HTREEITEM hParent = m_treectrlFileList.GetFirstVisibleItem();		// 현재 선택된 아이템의 핸들을 가져온다.
	HTREEITEM hItem;
	
	bool bChecked;
	bool bCompare = false;
	CString strTestName;
	CString strItem;
	CString strCompareTestName, strCompareFileName;

	while(hParent != NULL)
	{
		strTestName = m_treectrlFileList.GetItemText(hParent);
		HTREEITEM hChildItem = m_treectrlFileList.GetNextItem(hParent, TVGN_CHILD);

		while (hChildItem != NULL)
		{
			if (m_treectrlFileList.GetCheck(hChildItem))
			{
				int nCount = m_ListctrlFileList.GetItemCount();

				strTestName = m_treectrlFileList.GetItemText(hParent);
				strItem = m_treectrlFileList.GetItemText(hChildItem);

				// check same item in list control
				for (int i = 0; i< nCount ; i++)
				{
					strCompareTestName	= m_ListctrlFileList.GetItemText(i,0);
					strCompareFileName	= m_ListctrlFileList.GetItemText(i,1);
								 
					if(strCompareFileName == strTestName && 
						strCompareFileName == strItem )	// Same item case
					{
						bCompare = true;
						break;
					}
				}

				if(bCompare == false)
				{
					m_ListctrlFileList.InsertItem(nCount, strTestName);
					m_ListctrlFileList.SetItem(nCount, 0,LVIF_TEXT,  strTestName,0,0,0,NULL );
					m_ListctrlFileList.SetItem(nCount, 1,LVIF_TEXT,  strItem,0,0,0,NULL );
					
					m_bModifyFlag = true;
				}
			}
			hChildItem = m_treectrlFileList.GetNextItem(hChildItem, TVGN_NEXT);
		}
		hParent = m_treectrlFileList.GetNextItem(hParent,TVGN_NEXT);		// 현재 선택된 아이템의 핸들을 가져온다.
	}
}


void CheckingFileList::OnBnClickedButtonDeleteitem()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	POSITION pos = m_ListctrlFileList.GetFirstSelectedItemPosition();

	while (pos != NULL)
	{
		int nItem = m_ListctrlFileList.GetNextSelectedItem(pos);
		m_ListctrlFileList.DeleteItem(nItem);
		pos = m_ListctrlFileList.GetFirstSelectedItemPosition();
		m_bModifyFlag = true;
	}
}


void CheckingFileList::OnNMClickTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	TV_HITTESTINFO hit_info;

	// 화면상에서 마우스의 위치를 얻는다.
	::GetCursorPos(&hit_info.pt);

	// 얻은 마우스 좌표를 트리컨트롤 기준의 좌표로 변경한다.
	::ScreenToClient(m_treectrlFileList.m_hWnd, &hit_info.pt);

	// 현재 마우스 좌표가 위치한 항목 정보를 얻는다.
	HTREEITEM current_item = m_treectrlFileList.HitTest(&hit_info);

	if(current_item != NULL)
	{
		// 마우스가 위치한 항목을 찾았다면 해당 항목을 선택한다.
		m_treectrlFileList.Select(current_item, TVGN_CARET);
	}

	HTREEITEM hNode;
	CString strFileName ="";
	CString strTestName = "";
	CString strCombe = "";

	hNode = m_treectrlFileList.GetNextItem(NULL, TVGN_CARET);		// 현재 선택된 아이템의 핸들을 가져온다.
	strFileName = m_treectrlFileList.GetItemText(hNode);			// 그 아이템의 이름을 얻어온다.


	if((hit_info.flags & TVHT_ONITEMSTATEICON) != 0)
	{
		HTREEITEM hChildItem = m_treectrlFileList.GetChildItem(hNode);

		while (hChildItem != NULL)
		{
			if (m_treectrlFileList.GetCheck(hNode))
			{
				m_treectrlFileList.SetCheck(hChildItem,FALSE);
			}
			else
			{
				m_treectrlFileList.SetCheck(hChildItem,TRUE);
			}

			hChildItem = m_treectrlFileList.GetNextItem(hChildItem, TVGN_NEXT);
		}
	}

	hNode = m_treectrlFileList.GetNextItem(hNode, TVGN_PARENT);		// 현재 선택되어진 아이템의 상위 아이템을 가져온다.
	strTestName = m_treectrlFileList.GetItemText(hNode);			// 그 아이템의 이름을 얻어온다.
}


void CheckingFileList::SaveFileListInListctrlToList()
{
	m_vSettingFileList.clear();

	CString strNewData;

	std::string strFileName, strItemName;
	CString strTemp1, strTemp2;

	for(int i = 0; i < m_ListctrlFileList.GetItemCount() ; i++)
	{
		strFileName = m_ListctrlFileList.GetItemText(i,0);
		strItemName = m_ListctrlFileList.GetItemText(i,1);

		strTemp1 = strFileName.c_str();
		strTemp2 = strItemName.c_str();

		strNewData = strTemp1 + ":" + strTemp2;

		m_vSettingFileList.push_back(strNewData);
	}	
}