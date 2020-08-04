#include "pch.h"
#include "ShellExe.h"
#include <string>


using namespace std;

ShellExe::ShellExe() {}
ShellExe::~ShellExe() {}


void ShellExe::DoEvent()
{
	MSG msg;
	if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))//取消息，检索应用程序的消息队列，   PM_REMOVE取过之后从消息队列中移除  
	{
		//发消息  
		::TranslateMessage(&msg);
		::DispatchMessage(&msg);
	}
	
}
void ShellExe::TheadWait(HANDLE m_hThread)
{
	//HANDLE DoEvent();//线程事件
	/////////////////////////////////////等待线程完成函数///////////////////////////////////////////
	DWORD dwRet;																				                                                
	DoEvent();																					                                        
	do																							                                
	{																							                                
		dwRet = MsgWaitForMultipleObjects(1, &m_hThread, FALSE, INFINITE, QS_ALLINPUT);  
		if (dwRet != WAIT_OBJECT_0)																                                                        
		{																						                                
			DoEvent();																			                                
		}																						                                
	} while ((dwRet != WAIT_OBJECT_0) && (dwRet != WAIT_FAILED));                           
////////////////////////////////////////////////////////////////////////////////////////////////////

}

void ShellExe::OnOpenFile(CString path, CString Param)
{
	SHELLEXECUTEINFO ShExecInfo = { 0 };
	ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
	ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
	ShExecInfo.hwnd = NULL;
	ShExecInfo.lpVerb = L"runas";
	ShExecInfo.lpFile = path;
	ShExecInfo.lpParameters = Param;
	ShExecInfo.lpDirectory = NULL;
	ShExecInfo.nShow = SW_SHOW;
	ShExecInfo.hInstApp = NULL;
	ShellExecuteEx(&ShExecInfo);
//	WaitForSingleObject(ShExecInfo.hProcess, INFINITE);
	//无限等待同时防止程序假死
	TheadWait(ShExecInfo.hProcess);
	//if (ShExecInfo.hProcess != NULL)
	//{
	//	//Sleep(1);
	//	TerminateProcess(ShExecInfo.hProcess, 0);
	//	ShExecInfo.hProcess = NULL;
	//}
}