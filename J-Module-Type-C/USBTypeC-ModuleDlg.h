
// USBTypeC-ModuleDlg.h: 头文件
//

#pragma once


// CUSBTypeCModuleDlg 对话框
class CUSBTypeCModuleDlg : public CDialogEx
{
// 构造
public:
	CUSBTypeCModuleDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USBTYPECMODULE_DIALOG };
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
	CString ReadFirstLine(CString path);
	CString ReadLastLine(CString path);
	void OnWriteFileLine(CString path, CString str);
	void OnRunExe(CString path, CString Param);
	CString TypeC = L"TypeC\\";
	CString DB1300 = _TEXT("DB1300");
	CString PASS = _TEXT("pass");
	CString FAIL = _TEXT("fail");
	CString NOTR = _TEXT("null");
	CString s = _TEXT(",");
	CString AB;
	CString AB_TXT = _TEXT("C:\\GOODWAY\\AB.txt");
	CString ResultNULL = _TEXT("could not found More_Detail_Result.txt");
	CFileFind finderTXT, finderResult;
	//BOOL ifFindresult = finderResult.FindFile(ResultPath);
	BOOL ifFindtxt = finderTXT.FindFile(AB_TXT);
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
	int CUSBTypeCModuleDlg::GetFileLine(CString road);
	CString CUSBTypeCModuleDlg::ReadFileALL(CString path);
	void CUSBTypeCModuleDlg::OnAuToFunc();
};
