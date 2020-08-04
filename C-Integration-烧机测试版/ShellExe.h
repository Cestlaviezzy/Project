#pragma once
class ShellExe
{
public:
	ShellExe();
	~ShellExe();

	//void ShellExeFile(CString name, CString path);
	CString Param = NULL;

	void OnOpenFile(CString path, CString lpParam);
//	void OnOpenEXEParam(CString result_path, CString exe_path, CString exe_Param);

};

