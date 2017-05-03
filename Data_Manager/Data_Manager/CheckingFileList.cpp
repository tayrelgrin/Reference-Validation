// CheckingFileList.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Data_Manager.h"
#include "CheckingFileList.h"
#include "afxdialogex.h"


// CheckingFileList ��ȭ �����Դϴ�.

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


// CheckingFileList �޽��� ó�����Դϴ�.


BOOL CheckingFileList::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
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
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
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

			if(strTEMPs == "")	// Ȯ������
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

			if(strTEMPs == "")	// Ȯ������
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ���� ���� �о����
}


void CheckingFileList::OnBnClickedButtonAdditem()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	UINT uCount = m_treectrlFileList.GetVisibleCount();
	HTREEITEM hParent = m_treectrlFileList.GetFirstVisibleItem();		// ���� ���õ� �������� �ڵ��� �����´�.
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
		hParent = m_treectrlFileList.GetNextItem(hParent,TVGN_NEXT);		// ���� ���õ� �������� �ڵ��� �����´�.
	}
}


void CheckingFileList::OnBnClickedButtonDeleteitem()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	TV_HITTESTINFO hit_info;

	// ȭ��󿡼� ���콺�� ��ġ�� ��´�.
	::GetCursorPos(&hit_info.pt);

	// ���� ���콺 ��ǥ�� Ʈ����Ʈ�� ������ ��ǥ�� �����Ѵ�.
	::ScreenToClient(m_treectrlFileList.m_hWnd, &hit_info.pt);

	// ���� ���콺 ��ǥ�� ��ġ�� �׸� ������ ��´�.
	HTREEITEM current_item = m_treectrlFileList.HitTest(&hit_info);

	if(current_item != NULL)
	{
		// ���콺�� ��ġ�� �׸��� ã�Ҵٸ� �ش� �׸��� �����Ѵ�.
		m_treectrlFileList.Select(current_item, TVGN_CARET);
	}

	HTREEITEM hNode;
	CString strFileName ="";
	CString strTestName = "";
	CString strCombe = "";

	hNode = m_treectrlFileList.GetNextItem(NULL, TVGN_CARET);		// ���� ���õ� �������� �ڵ��� �����´�.
	strFileName = m_treectrlFileList.GetItemText(hNode);			// �� �������� �̸��� ���´�.


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

	hNode = m_treectrlFileList.GetNextItem(hNode, TVGN_PARENT);		// ���� ���õǾ��� �������� ���� �������� �����´�.
	strTestName = m_treectrlFileList.GetItemText(hNode);			// �� �������� �̸��� ���´�.
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