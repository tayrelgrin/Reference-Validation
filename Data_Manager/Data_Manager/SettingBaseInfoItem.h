#pragma once


// SettingBaseInfoItem ��ȭ �����Դϴ�.

class SettingBaseInfoItem : public CDialogEx
{
	DECLARE_DYNAMIC(SettingBaseInfoItem)

public:
	SettingBaseInfoItem(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~SettingBaseInfoItem();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DIALOG_BASEITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
