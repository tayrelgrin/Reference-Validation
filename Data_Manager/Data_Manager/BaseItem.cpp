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
	ON_BN_CLICKED(IDC_BUTTON_BIRL, &BaseItem::OnBnClickedButtonBirl)
	ON_CBN_SELCHANGE(IDC_COMBO1, &BaseItem::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// BaseItem �޽��� ó�����Դϴ�.


BOOL BaseItem::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.

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

	
	return TRUE;  // return TRUE unless you set the focus to a control
	// ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}


void BaseItem::OnBnClickedButtonBirl()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	
}


void BaseItem::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_TreeCtrl_BaseFile.DeleteAllItems();

	int nIndex = m_cComboFiles.GetCurSel();
	if(nIndex == -1)
		return;

	CString strSelect = "";
	m_cComboFiles.GetLBText(nIndex,LPSTR(LPCTSTR(strSelect)));

	 if(strSelect == "Register")
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
	strFileName.Format("%s%s",strFileName,".ini");
	cTarget->SearchFileInList(strFileName,cFile);
	CList<BasicData*> FileListData;
	cFile.CopyDataToList(FileListData);

	
	HTREEITEM h_Root;
	HTREEITEM h_Child;

	POSITION pPos = FileListData.GetHeadPosition();
	CString strSection, strItem, compare = "";

	while(pPos)
	{
		BasicData* temp = FileListData.GetNext(pPos);

		strSection	= temp->getSection();
		strItem		= temp->getItem();

		if(m_TreeCtrl_BaseFile.GetCount() >= 1)
			compare = m_TreeCtrl_BaseFile.GetItemText(h_Root);	// Search in Root level in tree

		if(strSection != compare)
			h_Root = m_TreeCtrl_BaseFile.InsertItem(strSection, TVI_ROOT, TVI_LAST);
		h_Child = m_TreeCtrl_BaseFile.InsertItem(strItem, h_Root, NULL);
	}
}
