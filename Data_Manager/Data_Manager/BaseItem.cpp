// BaseItem.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "BaseItem.h"
#include "afxdialogex.h"


// BaseItem 대화 상자입니다.

IMPLEMENT_DYNAMIC(BaseItem, CDialogEx)

BaseItem::BaseItem(CWnd* pParent /*=NULL*/)
	: CDialogEx(BaseItem::IDD, pParent)
{
	
}

BaseItem::~BaseItem()
{
}

void BaseItem::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_ADDITEMBI, m_cButton_BI_Add);
	DDX_Control(pDX, IDC_BUTTON_DELETEITEMBI, m_cButton_BI_Remove);
	DDX_Control(pDX, IDC_BUTTON_BILS, m_cButton_BI_LoadSetting);
	DDX_Control(pDX, IDC_BUTTON_BIRL, m_cButton_BI_Reload);
	DDX_Control(pDX, IDC_COMBO1, m_cComboFiles);
	DDX_Control(pDX, IDC_LIST_BI, m_ListCtrl_BaseItem);
	DDX_Control(pDX, IDC_TREE_BI, m_TreeCtrl_BaseFile);
}


BEGIN_MESSAGE_MAP(BaseItem, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_BIRL, &BaseItem::OnBnClickedButtonBirl)
	ON_CBN_SELCHANGE(IDC_COMBO1, &BaseItem::OnCbnSelchangeCombo1)

	ON_NOTIFY(NM_CLICK, IDC_TREE_BI, &BaseItem::OnNMClickTreeBi)
	ON_BN_CLICKED(IDC_BUTTON_ADDITEMBI, &BaseItem::OnBnClickedButtonAdditembi)
	ON_BN_CLICKED(IDC_BUTTON_BILS, &BaseItem::OnBnClickedButtonBils)
	ON_BN_CLICKED(IDC_BUTTON_DELETEITEMBI, &BaseItem::OnBnClickedButtonDeleteitembi)
END_MESSAGE_MAP()


// BaseItem 메시지 처리기입니다.


BOOL BaseItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_bModifyFlag = false;

	m_cButton_BI_Reload.LoadBitmaps(IDB_BITMAP_RELOAD,IDB_BITMAP_RELOADPUSH,NULL,NULL);
	m_cButton_BI_Reload.SizeToContent();

	m_cButton_BI_LoadSetting.LoadBitmaps(IDB_BITMAP_LOADSETTING,IDB_BITMAP_LOADSETTINGPUSH,NULL,NULL);
	m_cButton_BI_LoadSetting.SizeToContent();

	m_cButton_BI_Add.LoadBitmaps(IDB_BITMAP_RIGHT,IDB_BITMAP_RIGHTPUSH,NULL,NULL);
	m_cButton_BI_Add.SizeToContent();
	m_cButton_BI_Remove.LoadBitmaps(IDB_BITMAP_LEFT,IDB_BITMAP_LEFTPUSH,NULL,NULL);
	m_cButton_BI_Remove.SizeToContent();

	m_ListCtrl_BaseItem.DeleteAllItems();

	// List style
	m_ListCtrl_BaseItem.SetExtendedStyle(LVS_EX_GRIDLINES | LVCFMT_CENTER | LVS_EDITLABELS);

	m_ListCtrl_BaseItem.InsertColumn(0, _T("File"),				LVCFMT_CENTER, 90,  -1);
	m_ListCtrl_BaseItem.InsertColumn(1, _T("Section"),			LVCFMT_CENTER, 90,  -1);
	m_ListCtrl_BaseItem.InsertColumn(2, _T("Base Info"),		LVCFMT_CENTER, 125, -1);

	FileType* cBaseInfo = new FileType;
	m_pData->GetBaseInfo(*cBaseInfo);
	CList<BasicData*> lBaseInfoList;
	cBaseInfo->CopyDataToList(lBaseInfoList);

	POSITION pPos = lBaseInfoList.GetHeadPosition();

	CString strSection, strItem, strValue;

	int nIndex = 0;

	while(pPos)
	{
		BasicData* temp = lBaseInfoList.GetNext(pPos);

		strSection	= temp->getSection();
		strItem		= temp->getItem();
		strValue	= temp->getValue();

		m_ListCtrl_BaseItem.InsertItem(nIndex, strValue);
		m_ListCtrl_BaseItem.SetItem(nIndex, 0,LVIF_TEXT,  strValue,0,0,0,NULL );
		m_ListCtrl_BaseItem.SetItem(nIndex, 1,LVIF_TEXT,  strSection,0,0,0,NULL );
		m_ListCtrl_BaseItem.SetItem(nIndex, 2,LVIF_TEXT,  strItem,0,0,0,NULL );

		nIndex++;		
	}
	
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void BaseItem::OnBnClickedButtonBirl()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void BaseItem::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_TreeCtrl_BaseFile.DeleteAllItems();

	int nIndex = m_cComboFiles.GetCurSel();
	if(nIndex == -1)
		return;

	std::string strSelect = "";
	m_cComboFiles.GetLBText(nIndex,(LPTSTR)strSelect.c_str());

	 if(strSelect.compare("Register") == 0)
		 strSelect = "_Register";
	// else if(strSelect == "Reference")

	TestType* cTarget = new TestType;
	TestType* cTemp;
	FileType cFile;

	cTarget->SetTestName(m_strFirstTestName);

	bool bResult=false;
	cTemp = m_pData->SearchSettingData(*cTarget, bResult);
	if(!bResult)
	{
		delete cTarget;
		return;
	}
	cTarget = cTemp;
	CString strFileName;
	strFileName.Format("%s%s",strSelect.c_str(),".ini");
	cTarget->SearchFileInList(strFileName,cFile);
	CList<BasicData*> FileListData;
	cFile.CopyDataToList(FileListData);

	
	HTREEITEM h_Root;
	HTREEITEM h_Child;

	POSITION pPos = FileListData.GetHeadPosition();
	std::string strSection;
	std::string strItem;
	std::string compare = "";

	while(pPos)
	{
		BasicData* temp = FileListData.GetNext(pPos);

		strSection	= temp->getSection();
		strItem		= temp->getItem();

		if(m_TreeCtrl_BaseFile.GetCount() >= 1)
			compare = m_TreeCtrl_BaseFile.GetItemText(h_Root);	// Search in Root level in tree

		if(strSection.compare(compare) != 0)
			h_Root = m_TreeCtrl_BaseFile.InsertItem(strSection.c_str(), TVI_ROOT, TVI_LAST);
		h_Child = m_TreeCtrl_BaseFile.InsertItem(strItem.c_str(), h_Root, NULL);
	}
}


void BaseItem::OnNMClickTreeBi(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	TV_HITTESTINFO hit_info;

	// 화면상에서 마우스의 위치를 얻는다.
	::GetCursorPos(&hit_info.pt);

	// 얻은 마우스 좌표를 트리컨트롤 기준의 좌표로 변경한다.
	::ScreenToClient(m_TreeCtrl_BaseFile.m_hWnd, &hit_info.pt);

	// 현재 마우스 좌표가 위치한 항목 정보를 얻는다.
	HTREEITEM current_item = m_TreeCtrl_BaseFile.HitTest(&hit_info);

	if(current_item != NULL)
	{
		// 마우스가 위치한 항목을 찾았다면 해당 항목을 선택한다.
		m_TreeCtrl_BaseFile.Select(current_item, TVGN_CARET);
	}

	HTREEITEM hNode;
	CString strFileName ="";
	CString strTestName = "";
	CString strCombe = "";

	hNode = m_TreeCtrl_BaseFile.GetNextItem(NULL, TVGN_CARET);		// 현재 선택된 아이템의 핸들을 가져온다.
	strFileName = m_TreeCtrl_BaseFile.GetItemText(hNode);			// 그 아이템의 이름을 얻어온다.

	
	if(strFileName.Find('[') != -1 && (hit_info.flags & TVHT_ONITEMSTATEICON) != 0)
	{
		HTREEITEM hChildItem = m_TreeCtrl_BaseFile.GetChildItem(hNode);

		while (hChildItem != NULL)
		{
			if (m_TreeCtrl_BaseFile.GetCheck(hNode))
			{
				m_TreeCtrl_BaseFile.SetCheck(hChildItem,FALSE);
			}
			else
			{
				m_TreeCtrl_BaseFile.SetCheck(hChildItem,TRUE);
			}

			hChildItem = m_TreeCtrl_BaseFile.GetNextItem(hChildItem, TVGN_NEXT);
		}
	}

	hNode = m_TreeCtrl_BaseFile.GetNextItem(hNode, TVGN_PARENT);	// 현재 선택되어진 아이템의 상위 아이템을 가져온다.
	strTestName = m_TreeCtrl_BaseFile.GetItemText(hNode);			// 그 아이템의 이름을 얻어온다.

	*pResult = 0;
}


void BaseItem::OnBnClickedButtonAdditembi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// 아이템 추가

	HTREEITEM hParent;
	CString strSectionName ="";
	CString strTestName = "";
	CString strFileName = "";

	int nIndex = m_cComboFiles.GetCurSel();
	m_cComboFiles.GetLBText(nIndex, strFileName);

	hParent = m_TreeCtrl_BaseFile.GetNextItem(m_TreeCtrl_BaseFile.GetRootItem(),TVGN_NEXT);		// 현재 선택된 아이템의 핸들을 가져온다.
	strSectionName = m_TreeCtrl_BaseFile.GetItemText(hParent);									// 그 아이템의 이름을 얻어온다.

	while(hParent != NULL)
	{
		HTREEITEM hChildItem = m_TreeCtrl_BaseFile.GetNextItem(hParent, TVGN_CHILD);

		while (hChildItem != NULL)
		{
			if (m_TreeCtrl_BaseFile.GetCheck(hChildItem))
			{
				strTestName = m_TreeCtrl_BaseFile.GetItemText(hChildItem);

				int nCount = m_ListCtrl_BaseItem.GetItemCount();

				CString strCompareSection, strCompareItem, strCompareFileName;
				bool bCompare = false;

				// check same item in list control
				for (int i = 0; i< nCount ; i++)
				{
					strCompareFileName	= m_ListCtrl_BaseItem.GetItemText(i,0);
					strCompareSection	= m_ListCtrl_BaseItem.GetItemText(i,1);
					strCompareItem		= m_ListCtrl_BaseItem.GetItemText(i,2);

					if(strCompareFileName == strFileName && 
						strCompareSection == strSectionName &&
						strCompareItem == strTestName)	// Same item case
					{
						bCompare = true;
						break;
					}
				}

				if(bCompare == false)
				{
					m_ListCtrl_BaseItem.InsertItem(nCount, strFileName);
					m_ListCtrl_BaseItem.SetItem(nCount, 0,LVIF_TEXT,  strFileName,0,0,0,NULL );
					m_ListCtrl_BaseItem.SetItem(nCount, 1,LVIF_TEXT,  strSectionName,0,0,0,NULL );
					m_ListCtrl_BaseItem.SetItem(nCount, 2,LVIF_TEXT,  strTestName,0,0,0,NULL );

					m_bModifyFlag = true;
				}
			}

			hChildItem = m_TreeCtrl_BaseFile.GetNextItem(hChildItem, TVGN_NEXT);
		}

		hParent = m_TreeCtrl_BaseFile.GetNextItem(hParent,TVGN_NEXT);		
		strSectionName = m_TreeCtrl_BaseFile.GetItemText(hParent);			
	}
}


void BaseItem::OnBnClickedButtonBils()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void BaseItem::AddBaseInfoItemToList()
{
	CString strFile, strSection, strItem;

	m_pData->InitBaseInfo();

	for(int i = 0; i < m_ListCtrl_BaseItem.GetItemCount(); i++)
	{
		BasicData* cNewData = new BasicData;

		strFile		= m_ListCtrl_BaseItem.GetItemText(i,0);
		strSection	= m_ListCtrl_BaseItem.GetItemText(i,1);
		strItem		= m_ListCtrl_BaseItem.GetItemText(i,2);

		cNewData->setSection(strSection);
		cNewData->setItem(strItem);
		cNewData->setValue(strFile);

		m_pData->AddNewBaseInfo(*cNewData);
	}
}

void BaseItem::OnBnClickedButtonDeleteitembi()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	POSITION pos = m_ListCtrl_BaseItem.GetFirstSelectedItemPosition();

	while (pos != NULL)
	{
		int nItem = m_ListCtrl_BaseItem.GetNextSelectedItem(pos);
		m_ListCtrl_BaseItem.DeleteItem(nItem);
		pos = m_ListCtrl_BaseItem.GetFirstSelectedItemPosition();
		m_bModifyFlag = true;
	}
}
