﻿
// IntegrationDlg.h: 头文件
//

#pragma once

enum MES_LED_ID {
	Green_pic,
	Red_pic,
	Yellow_pic,
};

enum LOGO_ID {
	GOODWAY_LOGO,
};

// CIntegrationDlg 对话框
class CIntegrationDlg : public CDialogEx
{
// 构造
public:
	CIntegrationDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INTEGRATION_DIALOG };
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
	afx_msg void OnconfigPage();
	CListCtrl m_listA;
	CListCtrl m_listB;
	int rowsA;
	int colsA;
	int rowsB;
	int colsB;
	CFont m_font_result, m_font;
	CFont DateFont, TimeFont, CountFont;
	CStatic m_MES_result;
	void OnReadINIfileA();
	void OnReadINIfileB();
	void DisplayResult(CString Result);
	COLORREF EndResult_textColor;//to change the color of result
	COLORREF EndResult_backColor;//to change the color of result
	CBrush EndResult_backBrush;//to change the color of result


	CString pass = _T("PASS");
	CString fail = _T("FAIL");
	CString wait = _T("WAIT");
	//afx_msg void OnBnClickedButton1();
	
	CString PathA = L"..\\menuA.ini";
	CString PathB = L"..\\menuB.ini";
	CString Configini = L"..\\Config.ini";
	CEdit m_edit1;


	CString VBS = L"C:\\GOODWAY\\VBS";
	CString CON = L"\\";
	CString GOODWAY = L"C:\\GOODWAY";
	CString exe_result_log = L"result.log";
	CString Internet = L"Internet";
	CString Video = L"Video";
	CString USB = L"USB";
	CString InternetPath = GOODWAY + CON + Internet + CON + exe_result_log;
	CString VideoPath = GOODWAY + CON + Video + CON + exe_result_log;
	CString USBPath = GOODWAY + CON + USB + CON + exe_result_log;


	CString Param = NULL;
	char* s_A = "A";
	char* s_B = "B";
	CString TXT_AB = L"AB.txt";

	CString log_A = L"result_A.log";
	CString log_B = L"result_B.log";
	CString log_temp_result = L"temp_result.log";
	CString log_final_result = L"Result.log";

	CString path_AB = GOODWAY + CON + TXT_AB;								//AB.txt路径

	CString log_path_A = GOODWAY + CON + log_A;								//log结果文件路径
	CString log_path_B = GOODWAY + CON + log_B;
	CString log_path_temp_result = GOODWAY + CON + log_temp_result;			//临时文件路径 方便检查是否有fail
	CString log_path_result = GOODWAY + CON + log_final_result;				//最终生成要上传MES的文件路径
	//CString PathX = log_path_result;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnNMCustomdrawList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawList2(NMHDR *pNMHDR, LRESULT *pResult);
	void OnDelFile(CString path);
	void SelectPic(UINT nIDEvent);
	void ShowPic(CString LED_OriginalPath);
	void ShowPic_Logo(CString LED_OriginalPath);
	afx_msg void OnBnClickedRadio1();
	int RadioState_Green;
	int RadioState_Red;
	int RadioState_Yellow;
	CEdit m_edit_site;
	CEdit m_edit_user;
	CEdit m_edit_equip;
	CEdit m_edit_pcb;
	CEdit m_edit_number;
	CString mes_equip, mes_user, mes_site, mes_pcb, mes_number;
	CString CheckNumberResult;
	afx_msg void OnBnClickedRadio2();
	CStatic m_edit_picture;
	CString defect_pass = L"";
	
	CStatic m_static_test_A;
	CStatic m_static_test_B;
	CStatic m_static_test_result;
	CStatic m_static_user_login;
	CStatic m_static_MES_set;
	CStatic m_static_site;
	CStatic m_static_user;
	CStatic m_static_equip;
	CStatic m_static_pcb;

	CStatic m_static_number;
	//MES password chaeck
	int mespasswordflag;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	void IntegrationStart(CString PCB);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//int ThreadFlag;//线程开启和关闭标志值，是全局变量
	int TF;
	int loginclose;
	//void CIntegrationDlg::KMeansSegment(); 
	//void CIntegrationDlg::WaitForThreadExit(void);
	CString mes_check_result_ini = GOODWAY + CON + L"result.ini";
	CStatic m_static_goodway_logo;
	void CIntegrationDlg::SelectPic_Logo(UINT nIDEvent);
	void CIntegrationDlg::CharToUTF8(CString &str);
	HBRUSH m_redbrush;
	UINT CIntegrationDlg::ThreadFunc(LPVOID lParam);
	//afx_msg BOOL OnDeviceChange(UINT nEventType, DWORD dwData);
	bool bFindRemovableDevice = false;
	CString DeviceRemovable = L"F";
	//void CIntegrationDlg::BFuncCheck();
	int casen = 0;

	CString Choose;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMDblclkList2(NMHDR *pNMHDR, LRESULT *pResult);
};


DWORD WINAPI ThreadProcPASS(LPVOID lpParameter);
DWORD WINAPI ThreadProcFAIL(LPVOID lpParameter);
DWORD WINAPI ThreadProcTime(LPVOID lpParameter);
DWORD WINAPI ThreadProcCheck(LPVOID lpParameter);
//DWORD WINAPI ThreadProcBCheckTime(LPVOID lpParameter);