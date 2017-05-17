#pragma once
#include "afxwin.h"


// ListLogTab 대화 상자입니다.

class ListLogTab : public CDialogEx
{
	DECLARE_DYNAMIC(ListLogTab)

public:
	ListLogTab(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~ListLogTab();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_LISTLOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listLogBox;
	virtual BOOL OnInitDialog();
	void AddListLog(CString inData);
};
