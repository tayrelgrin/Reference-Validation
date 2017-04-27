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
					strTest = strDir + "-" + strTest;
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
					strTest = strDir + "-" + strTest;
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

	// tree���� üũ �� �����۵� ������ ����
	
	UINT uCount = m_treectrlFileList.GetVisibleCount();
	HTREEITEM hItem = m_treectrlFileList.GetFirstVisibleItem();

	bool bChecked;
	CString strFileName;
	CString strItem;
	// Toggle the check state of all the visible items.
	for (UINT i = 0; i < uCount; i++)
	{
		ASSERT(hItem != NULL);
		bChecked = m_treectrlFileList.GetCheck(hItem);

		if(bChecked)
		{
			hItem = m_treectrlFileList.GetNextItem(NULL, TVGN_CARET);
			strItem = m_treectrlFileList.GetItemText(hItem);

			hItem = m_treectrlFileList.GetNextItem(hItem, TVGN_PARENT);		// ���� ���õǾ��� �������� ���� �������� �����´�.
			strFileName = m_treectrlFileList.GetItemText(hItem);			// �� �������� �̸��� ���´�.

			int nCount = m_ListctrlFileList.GetItemCount();
			m_ListctrlFileList.InsertItem(nCount, strFileName);
			m_ListctrlFileList.SetItem(nCount, 0,LVIF_TEXT,  strFileName,0,0,0,NULL );
		}
		//hItem = m_treectrlFileList.GetNextVisibleItem(hItem);
	}
	
	// tree�� üũ �����ϱ�
	

	// listctrl�� ������ �߰��ϱ�
}


void CheckingFileList::OnBnClickedButtonDeleteitem()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// listctrl���� ������ ����
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

	hNode = m_treectrlFileList.GetNextItem(hNode, TVGN_PARENT);	// ���� ���õǾ��� �������� ���� �������� �����´�.
	strTestName = m_treectrlFileList.GetItemText(hNode);			// �� �������� �̸��� ���´�.

}
