#pragma once
#include "afxwin.h"


// ListLogTab ��ȭ �����Դϴ�.

class ListLogTab : public CDialogEx
{
	DECLARE_DYNAMIC(ListLogTab)

public:
	ListLogTab(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~ListLogTab();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_LISTLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listLogBox;
	virtual BOOL OnInitDialog();
	void AddListLog(CString inData);
};
