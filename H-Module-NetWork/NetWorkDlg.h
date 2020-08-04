
// NetWorkDlg.h: 头文件
//

#pragma once


// CNetWorkDlg 对话框
class CNetWorkDlg : public CDialogEx
{
// 构造
public:
	CNetWorkDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_NETWORK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	void CNetWorkDlg::OnRunExe(CString path, CString Param);
	int CNetWorkDlg::GetFileLine(CString road);
	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;
	CEdit m_edit4;
	CEdit m_edit5;
	CEdit m_edit6;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	COLORREF EndResult_textColor4;//to change the color of result
	COLORREF EndResult_backColor4;//to change the color of result
	CBrush EndResult_backBrush4;//to change the color of result
	COLORREF EndResult_textColor5;//to change the color of result
	COLORREF EndResult_backColor5;//to change the color of result
	CBrush EndResult_backBrush5;//to change the color of result
	COLORREF EndResult_textColor6;//to change the color of result
	COLORREF EndResult_backColor6;//to change the color of result
	CBrush EndResult_backBrush6;//to change the color of result
	void CNetWorkDlg::DisplayResultIP(CString Result);
	void CNetWorkDlg::DisplayResultSpeed(CString Result);
	void CNetWorkDlg::DisplayResultFinal(CString Result);
	CFont font;
	CFont m_font;
	CStatic m_local;
	CStatic m_server;
	CStatic m_speed;
	CStatic m_pingresult;
	CStatic m_speedresult;
	CStatic m_finalresult;
	CButton m_start;
	CString AB_TXT = L"C:\\GOODWAY\\AB.txt";
	CString CNetWorkDlg::ReadFileFirstLine(CString path);
	void CNetWorkDlg::OnWriteFileLine(CString path, CString str);
	CString NET = _T("NET");
	CString DB1403 = _T("DB1403");
	CString s = _T(",");
	CString T = _T("T");
	CString result_flag;//结果判断标志
	void CNetWorkDlg::AuToFunc();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
