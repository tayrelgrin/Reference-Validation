#pragma once


// SettingBaseInfoItem 대화 상자입니다.

class SettingBaseInfoItem : public CDialogEx
{
	DECLARE_DYNAMIC(SettingBaseInfoItem)

public:
	SettingBaseInfoItem(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~SettingBaseInfoItem();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DIALOG_BASEITEM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
