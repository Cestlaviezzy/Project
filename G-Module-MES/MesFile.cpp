#include "pch.h"
#include "MesFile.h"


MesFile::MesFile() {};
MesFile::~MesFile() {};


void MesFile::CharToUTF8(CString &str)
{
	char *szBuf = new char[str.GetLength() + 1];//注意“+1”，char字符要求结束符，而CString没有
	memset(szBuf, '\0', str.GetLength());


	int i;
	for (i = 0; i < str.GetLength(); i++)
	{
		szBuf[i] = (char)str.GetAt(i);
	}
	szBuf[i] = '\0';//结束符。否则会在末尾产生乱码。

	int nLen;
	WCHAR *ptch;
	CString strOut;
	if (szBuf == NULL)
	{
		return;
	}
	nLen = MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, NULL, 0);//获得需要的宽字符字节数
	ptch = new WCHAR[nLen];
	memset(ptch, '\0', nLen);
	MultiByteToWideChar(CP_UTF8, 0, szBuf, -1, ptch, nLen);
	//str.Format(_T("%s"), ptch);
	str = ptch;
	if (NULL != ptch)
		delete[] ptch;
	ptch = NULL;

	if (NULL != szBuf)
		delete[]szBuf;
	szBuf = NULL;
	return;
}

//获取文件行数
int MesFile::GetFileLine(CString road)
{
	CStdioFile myFile;
	CFileException fileException;
	if (myFile.Open(road, CFile::modeCreate | CFile::modeNoTruncate | CFile::typeText | CFile::modeReadWrite), &fileException)
	{
		CString strContent;
		int order = 0;
		while (myFile.ReadString(strContent))
		{
			order++;
		}
		myFile.Close();
		return order;
	}
	else
	{
		myFile.Close();
		return 0;
	}
}
//读取整个文件
CString MesFile::ReadFileALL(CString path)
{
	CStdioFile file;
	CString arry[1000];
	CString data;
	CString all_result;
	CString result;
	int line = GetFileLine(path);
	if (file.Open(path, CFile::modeRead))
	{
		for (int i = 0; i < line; i++)
		{
			file.ReadString(arry[i]);
			all_result += arry[i] + L"\n";
			all_result.Replace(L" ", L"");
		}
		file.Close();
		return all_result;
	}
	else
	{
		file.Close();
		AfxMessageBox(L"all.文件不存在");
	}
}