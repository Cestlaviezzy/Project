#pragma once


// NoConnectMax 对话框

class NoConnectMax : public CDialogEx
{
	DECLARE_DYNAMIC(NoConnectMax)

public:
	NoConnectMax(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~NoConnectMax();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_macmax;
//	CEdit m_edit_devmax;
	virtual BOOL OnInitDialog();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CString macmax;
//	CString devmax;
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	CFont font;
	CStatic m_static_macmax;
};
