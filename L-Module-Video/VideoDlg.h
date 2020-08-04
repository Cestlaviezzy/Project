
// VideoDlg.h: 头文件
//

#pragma once


// CVideoDlg 对话框
class CVideoDlg : public CDialogEx
{
// 构造
public:
	CVideoDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VIDEO_DIALOG };
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
	CString PATH;
	int CVideoDlg::GetFileLine(CString road);
	CString AB_TXT = L"C:\\GOODWAY\\AB.txt";
	CString AB;
	CString CVideoDlg::ReadFileFirstLine(CString path);
	void CVideoDlg::OnWriteFileLine(CString path, CString str);
	CString PASS = _T("pass");
	CString FAIL = _T("fail");
	CString s = _T(",");
	CString DB1500 = _T("DB1500");
	CString p = _T("p");
	void CVideoDlg::OnRunExe(CString path, CString Param);
	CString left = _T("[");
	CString right = _T("]");
	void CVideoDlg::OnAuToFun();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);

};
