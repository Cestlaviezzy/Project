
// USB-ModuleDlg.h: 头文件
//

#pragma once


// CUSBModuleDlg 对话框
class CUSBModuleDlg : public CDialogEx
{
// 构造
public:
	CUSBModuleDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_USBMODULE_DIALOG };
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
	CString CUSBModuleDlg::ReadFileFirstLine(CString path);
	void CUSBModuleDlg::OnWriteFileLine(CString path, CString str);
	void CUSBModuleDlg::OnRunExe(CString path, CString Param);
	CString USB32 = _TEXT("USB32");
	CString DB1300 = _TEXT("DB1300");
	CString PASS = _TEXT("pass");
	CString FAIL = _TEXT("fail");
	CString NOTR = _TEXT("null");
	CString s = L",";
	CString p = L"port";
	CString AB;
	CString AB_TXT = _TEXT("C:\\GOODWAY\\AB.txt");
	CFileFind finderTXT,finderResult;

	//定义log里面所有变量
	CString CONN = _TEXT("CONN");		//连接
	CString SHORT = _TEXT("SHORT");		//短路
	CString ISO = _TEXT("ISO");			//同步
	CString INT = _TEXT("INT");			//中断
	CString CTRL = _TEXT("CTRL");		//命令
	CString VBUS = _TEXT("VBUS");		//电压
	CString BC1_2 = _TEXT("BC1_2");		//快充
	CString LOAD = _TEXT("LOAD");		//负载
	CString BULK = _TEXT("BULK");		//块
	CString FS = _TEXT("FS");			//全速
	CString HS = _TEXT("HS");			//高速
	CString SS = _TEXT("SS");			//超速
	CString CONNResult3, CONNResult2;
	CString SHORTResult3, SHORTResult2;
	CString ISOResult3, ISOResult2;
	CString INTResult3, INTResult2;
	CString CTRLResult3, CTRLResult2;
	CString VBUSResult3, VBUSResult2;
	CString BC1_2Result3, BC1_2Result2;
	CString LOADResult3, LOADResult2;
	CString BULKResult3, BULKResult2;
	CString FSResult3, FSResult2;
	CString HSResult3, HSResult2;
	CString SSResult3, SSResult2;
	//PORT结果
	CString PortResult;
	CString ResultNULL = _TEXT("could not found Result.txt");
	void OnAuToFunc();
	afx_msg void OnWindowPosChanging(WINDOWPOS* lpwndpos);
};
