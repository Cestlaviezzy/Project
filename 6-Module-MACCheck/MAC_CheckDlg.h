
// MAC_CheckDlg.h: 头文件
//

#pragma once


// CMACCheckDlg 对话框
class CMACCheckDlg : public CDialogEx
{
// 构造
public:
	CMACCheckDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAC_CHECK_DIALOG };
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
	int CMACCheckDlg::GetFileLine(CString road);
	void CMACCheckDlg::CharToUTF8(CString &str);
	void CMACCheckDlg::OnRunExe(CString path, CString Param, CString DestPath);
	CEdit m_edit2;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CEdit m_edit1;
	COLORREF EndResult_textColor;//to change the color of result
	COLORREF EndResult_backColor;//to change the color of result
	CBrush EndResult_backBrush;//to change the color of result
	void CMACCheckDlg::DisplayResult(CString Result);
	CStatic m_static_localmac;
	CStatic m_static_macaddr;
	CStatic m_static_mac;
	CStatic m_static_num;
	CStatic m_static_pcb;
	CStatic m_static_result;
	CEdit m_edit3;
	CEdit m_edit4;
	int CMACCheckDlg::PutCSVItemLine(FILE *file, CStringArray &sItemLine);
	//void CMACCheckDlg::TestCSV(CString Item, CString Result);
	CString MACdata = _TEXT("MacData.csv");
	CFont m_font_result, m_font, m1_font, m2_font, m_button_font;
	int Number = 1;//记录测试次数
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CEdit m_edit5;
	CStatic m_static_sn;
	CEdit m_edit6;
	CStatic m_static_qr;
	int MACLENGTH = 12;//MAC 长度
	CButton m_button;
	CString s = L"\n";
};
