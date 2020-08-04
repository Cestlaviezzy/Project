
// LoadVoltageDlg.h: 头文件
//

#pragma once


// CLoadVoltageDlg 对话框
class CLoadVoltageDlg : public CDialogEx
{
// 构造
public:
	CLoadVoltageDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOADVOLTAGE_DIALOG };
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
	CString CLoadVoltageDlg::ReadFileALL(CString path);
	int CLoadVoltageDlg::GetFileLine(CString road);
	void CLoadVoltageDlg::OnWriteFileLine(CString path, CString str);
	CString CLoadVoltageDlg::ReadFileFirstLine(CString path);
	int n = 0;
	CString s = _T(",");
	CString Function = _T("PD");
	CString T = _T("T");
	CString AB_TXT = _TEXT("C:\\GOODWAY\\AB.txt");
	CString ResultNULL = _TEXT("could not Result.txt");
	CString pass = _TEXT("pass");
	CString fail = _TEXT("fail");
	CString not = _TEXT("null");
	CString DH1102 = _T("DH1102");
	CString GetVBus = _T("Get_VBus:");
	CString GetCurrent = _T("Get_Current:");
	CString NoLoadVBus = _T("No_Load_VBus:");
	CString LoadVBus = _T("Load_VBus:");
	void CLoadVoltageDlg::OnRunExe(CString path, CString Param);
	void CLoadVoltageDlg::AuToFunc();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
