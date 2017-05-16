#pragma once


// Config_Select_Dlg 대화 상자입니다.

class Config_Select_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Config_Select_Dlg)

public:
	Config_Select_Dlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~Config_Select_Dlg();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_CONFIG_SELECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
