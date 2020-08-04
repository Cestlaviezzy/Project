#pragma once
class fileinfo
{

public:
	fileinfo();
	~fileinfo();
	int GetFileLine(CString road);
	CString ReadFileALL(CString path);
	int Newgetfileline(CString path);
	//CString ReadLineToResult(CString path);
	CString ReadFileFirstLine(CString path);
	void WriteFileToPath(CString path, char* WriteBuf);
	CString DefectFileRead(CString path);
	void AddFileINI(CString pathsrc, CString pathdst);

	//1、抓取GOODWAY下所有result.log文件最后一行数据
	//2、合并成Result.log文件函数
	CString OnReadFileLastLine(CString path);
	void OnWriteFileLine(CString path, CString str);
	void getFolderDayFile(CString pathStr, CStringArray& arrStrFile);
	void OnFileMerge(CString strPath, CString dstPath);
	void OnFileMergeAll(CString PathA, CString PathB, CString PathResult);
	CString VerCheck(CString path);
	CString GOODWAY = L"C:\\GOODWAY";
	int ReadSetINI(CString path);
	int SendToMESWaitTime(CString path);

	void fileinfo::CharToUTF8(CString &str);
};

