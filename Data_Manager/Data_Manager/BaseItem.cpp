// BaseItem.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "BaseItem.h"
#include "afxdialogex.h"


// BaseItem ��ȭ �����Դϴ�.

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
	ON_CBN_SELCHANGE(IDC_COMBO1, &BaseItem::OnCbnSelchangeCombo1)
	ON_NOTIFY(NM_CLICK, IDC_TREE_BI, &BaseItem::OnNMClickTreeBi)
	ON_BN_CLICKED(IDC_BUTTON_ADDITEMBI, &BaseItem::OnBnClickedButtonAdditembi)
	ON_BN_CLICKED(IDC_BUTTON_DELETEITEMBI, &BaseItem::OnBnClickedButtonDeleteitembi)
END_MESSAGE_MAP()


// BaseItem �޽��� ó�����Դϴ�.


BOOL BaseItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
	
	m_strRefFileName.Format(_T(""));

	CString strSection, strItem, strValue;

	strSection.Format(_T(""));
	strItem.Format(_T(""));
	strValue.Format(_T(""));

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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void BaseItem::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_TreeCtrl_BaseFile.DeleteAllItems();

	int nIndex = m_cComboFiles.GetCurSel();
	if(nIndex == -1)
		return;

	CString strSelect = "";
	m_cComboFiles.GetLBText(nIndex,strSelect);

	 if(strSelect.Find("Reference") != -1)
		 strSelect = "_Register";

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
	strFileName.Format("%s%s",strSelect,".ini");
	cTarget->SearchFileInList(strFileName,cFile);

	if(strSelect.Find("_Register") != -1)
	{
		strFileName = cFile.GetFileName();
		strFileName.Replace("_Register","");

		m_strRefFileName.Format("%s",strFileName);

		cFile.InitList();
		cTarget->SearchFileInList(strFileName,cFile);
	}
	
	CList<BasicData*> FileListData;
	cFile.CopyDataToList(FileListData);
	
	HTREEITEM h_Root;
	HTREEITEM h_Child;

	POSITION pPos = FileListData.GetHeadPosition();
	std::string strSection;
	std::string strItem;
	std::string strCompare = "";

	while(pPos)
	{
		BasicData* temp = FileListData.GetNext(pPos);

		strSection	= temp->getSection();
		strItem		= temp->getItem();

		if(strSection.compare("") == 0)
			continue;

		if(m_TreeCtrl_BaseFile.GetCount() >= 1)
			strCompare = m_TreeCtrl_BaseFile.GetItemText(h_Root);	// Search in Root level in tree

		if(strSection.compare(strCompare) != 0)
			h_Root = m_TreeCtrl_BaseFile.InsertItem(strSection.c_str(), TVI_ROOT, TVI_LAST);
		h_Child = m_TreeCtrl_BaseFile.InsertItem(strItem.c_str(), h_Root, NULL);
	}
}


void BaseItem::OnNMClickTreeBi(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	TV_HITTESTINFO hit_info;

	// ȭ��󿡼� ���콺�� ��ġ�� ��´�.
	::GetCursorPos(&hit_info.pt);

	// ���� ���콺 ��ǥ�� Ʈ����Ʈ�� ������ ��ǥ�� �����Ѵ�.
	::ScreenToClient(m_TreeCtrl_BaseFile.m_hWnd, &hit_info.pt);

	// ���� ���콺 ��ǥ�� ��ġ�� �׸� ������ ��´�.
	HTREEITEM current_item = m_TreeCtrl_BaseFile.HitTest(&hit_info);

	if(current_item != NULL)
	{
		// ���콺�� ��ġ�� �׸��� ã�Ҵٸ� �ش� �׸��� �����Ѵ�.
		m_TreeCtrl_BaseFile.Select(current_item, TVGN_CARET);
	}

	HTREEITEM hNode;
	CString strFileName ="";
	CString strTestName = "";
	CString strCombe = "";

	hNode = m_TreeCtrl_BaseFile.GetNextItem(NULL, TVGN_CARET);		// ���� ���õ� �������� �ڵ��� �����´�.
	strFileName.Format("%s", m_TreeCtrl_BaseFile.GetItemText(hNode));			// �� �������� �̸��� ���´�.

	
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

	hNode = m_TreeCtrl_BaseFile.GetNextItem(hNode, TVGN_PARENT);	// ���� ���õǾ��� �������� ���� �������� �����´�.
	strTestName.Format("%s", m_TreeCtrl_BaseFile.GetItemText(hNode));			// �� �������� �̸��� ���´�.

	*pResult = 0;
}


void BaseItem::OnBnClickedButtonAdditembi()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// ������ �߰�

	HTREEITEM hParent;
	CString strSectionName ="";
	CString strTestName = "";
	CString strFileName = "";

	int nIndex = m_cComboFiles.GetCurSel();
	m_cComboFiles.GetLBText(nIndex, strFileName);

	if (strFileName == "Reference")
	{
		strFileName.Format("%s", m_strRefFileName);
	}

	hParent = m_TreeCtrl_BaseFile.GetNextItem(m_TreeCtrl_BaseFile.GetRootItem(),TVGN_NEXT);		// ���� ���õ� �������� �ڵ��� �����´�.
	strSectionName = m_TreeCtrl_BaseFile.GetItemText(hParent);									// �� �������� �̸��� ���´�.

	while(hParent != NULL)
	{
		HTREEITEM hChildItem = m_TreeCtrl_BaseFile.GetNextItem(hParent, TVGN_CHILD);

		while (hChildItem != NULL)
		{
			if (m_TreeCtrl_BaseFile.GetCheck(hChildItem))
			{
				strTestName.Format("%s", m_TreeCtrl_BaseFile.GetItemText(hChildItem));

				int nCount = m_ListCtrl_BaseItem.GetItemCount();

				CString strCompareSection, strCompareItem, strCompareFileName;
				bool bCompare = false;

				// check same item in list control
				for (int i = 0; i< nCount ; i++)
				{
					strCompareFileName.Format("%s",m_ListCtrl_BaseItem.GetItemText(i,0));
					strCompareSection.Format("%s", m_ListCtrl_BaseItem.GetItemText(i,1));
					strCompareItem.Format("%s", m_ListCtrl_BaseItem.GetItemText(i,2));

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
		strSectionName.Format("%s", m_TreeCtrl_BaseFile.GetItemText(hParent));
	}
}


bool BaseItem::CheckExistSameData(HTREEITEM inData)
{
	bool bResult = false;

	return bResult;
}


void BaseItem::AddBaseInfoItemToList()
{
	CString strFile, strSection, strItem;

	m_pData->InitBaseInfo();

	for(int i = 0; i < m_ListCtrl_BaseItem.GetItemCount(); i++)
	{
		BasicData* cNewData = new BasicData;

		strFile.Format("%s", m_ListCtrl_BaseItem.GetItemText(i,0));
		strSection.Format("%s",m_ListCtrl_BaseItem.GetItemText(i,1));
		strItem.Format("%s", m_ListCtrl_BaseItem.GetItemText(i,2));

		cNewData->setSection(strSection);
		cNewData->setItem(strItem);
		cNewData->setValue(strFile);

		m_pData->AddNewBaseInfo(*cNewData);
	}
}

void BaseItem::OnBnClickedButtonDeleteitembi()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	POSITION pos = m_ListCtrl_BaseItem.GetFirstSelectedItemPosition();

	while (pos != NULL)
	{
		int nItem = m_ListCtrl_BaseItem.GetNextSelectedItem(pos);
		m_ListCtrl_BaseItem.DeleteItem(nItem);
		pos = m_ListCtrl_BaseItem.GetFirstSelectedItemPosition();
		m_bModifyFlag = true;
	}
}
