#pragma once


// Config_Select_Dlg ��ȭ �����Դϴ�.

class Config_Select_Dlg : public CDialogEx
{
	DECLARE_DYNAMIC(Config_Select_Dlg)

public:
	Config_Select_Dlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~Config_Select_Dlg();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_CONFIG_SELECTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
