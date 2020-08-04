#include "pch.h"
#include "fileinfo.h"
#include <atlbase.h>
#include <atlconv.h>


fileinfo::fileinfo() {}

fileinfo::~fileinfo() {}

const int UNICODE_TXT_FLG = 0xFEFF;

void fileinfo::CharToUTF8(CString &str)
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
int fileinfo::GetFileLine(CString road)
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
CString fileinfo::ReadFileALL(CString path)
{
	CStdioFile file;
	CString arry[1000];
	CString all_result;
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

int fileinfo::Newgetfileline(CString path)
{
	CString str;
	CStdioFile file;
	file.Open(path, CFile::modeRead);
	int line = 0;
	while (file.ReadString(str))
	{
		line++;
	}
	file.Close();
	return line;
}

//读取第一行 规定第一行为程序最终结果
CString fileinfo::ReadFileFirstLine(CString path)
{
	CStdioFile file;
	CString line_result;
	if (file.Open(path, CFile::modeRead))
	{
		file.ReadString(line_result);
		CharToUTF8(line_result);
		file.Close();			//不能写反，先关闭后return
		return line_result;
	}
	else
	{
		AfxMessageBox(L"2.文件不存在");
	}

}

//创建AB.txt文件
void fileinfo::WriteFileToPath(CString path, char* WriteBuf)
{
	CFile file;
	file.Open(path, CFile::modeWrite | CFile::modeRead | CFile::modeCreate);

	//char *WriteBuf = "";
	file.Write(WriteBuf, strlen(WriteBuf));  //strlen()+1  会有个空格
	file.Close();
	WriteBuf = NULL;
}

void fileinfo::AddFileINI(CString pathsrc, CString pathdst)
{
	CString str = L"";
	str = ReadFileALL(pathsrc);
	CharToUTF8(str);
	USES_CONVERSION;
	if ((str.Find(L"fail")) == -1)
	{
		CFile file;
		CString P = _T("PASS,\r\n");
		file.Open(pathdst, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
		file.SeekToBegin();
		CT2CA outputString(P, CP_UTF8);
		CT2CA outputStringstr(str, CP_UTF8);
		file.Write(outputString, ::strlen(outputString));
		file.Write(outputStringstr, ::strlen(outputStringstr));
		file.Flush();
		file.Close();
	}
	else
	{
		CFile file;
		CString F = _T("FAIL,\r\n");
		file.Open(pathdst, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
		file.SeekToBegin();
		CT2CA outputString(F, CP_UTF8);
		CT2CA outputStringstr(str, CP_UTF8);
		file.Write(outputString, ::strlen(outputString));
		file.Write(outputStringstr, ::strlen(outputStringstr));
		file.Flush();
		file.Close();
	}
}

//通过最终结果查询，将所有不良代码截取汇总
CString fileinfo::DefectFileRead(CString path)
{
	CStdioFile file;
	CString arry[1000];
	CString str;
	CString res;
	CString dst;
	CString result;
	int nn;
	nn = Newgetfileline(path);
	//int line = GetFileLine(path);
	if (file.Open(path, CFile::modeRead))
	{
		for (int i = 0; i < nn; i++)
		{
			file.ReadString(str);
			if (str.Left(4) == "fail")
			{
				res = str.Mid(5, 6);
				dst += res + L",";
			}

		}
		file.Close();
		result = dst.TrimRight(L",");
		CharToUTF8(result);

		return result;
	}
	else
	{
		AfxMessageBox(L"1.文件不存在");
	}
}

//校验版本的函数
CString fileinfo::VerCheck(CString path)
{
	CStdioFile file;
	int a, b;
	CString str;
	CString res;
	CString dst;
	int line = GetFileLine(path);
	if (file.Open(path, CFile::modeRead))
	{
		for (int i = 0; i < line; i++)
		{
			file.ReadString(str);
			if (str.Left(7) == "Current")
			{
				a = str.Find(L"[");
				b = str.Find(L"]");
				dst = str.Mid(a + 1, b - a - 1);
			}
			//a = str.Find(L",");
			//b = str.ReverseFind(',');
		}
		CharToUTF8(dst);
		file.Close();

		return dst;
	}
	else
	{
		AfxMessageBox(L"1.文件不存在");
	}
}
/*************************************************************************************************************/
CString fileinfo::OnReadFileLastLine(CString path)
{
	CStdioFile file;
	CString str;
	CString dst;
	CString result;
	CString nu = L"";
	file.Open(path, CFile::modeRead);
	file.ReadString(nu);
	while (file.ReadString(str))
	{
		dst += str + L",\n";
	}
	//result = dst;
	//function(result);
	CharToUTF8(dst);


	return dst;
	file.Close();
}


//写入UTF-8
void fileinfo::OnWriteFileLine(CString path, CString str)
{
	CFile file;
	file.Open(path, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
	file.SeekToEnd();
	CT2CA outputString(str, CP_UTF8);
	file.Write(outputString, ::strlen(outputString));
	file.Flush();
	file.Close();
}

//void fileinfo::OnWriteFileLine(CString path, CString str)
//{
//	USES_CONVERSION;
//	CStdioFile file;
//	char * pFileName = T2A(str);
//	file.Open(path, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
//	file.SeekToEnd();
//	file.Write(pFileName, strlen(pFileName));
//	file.Flush();
//	file.Close();
//	pFileName = NULL;
//}

void fileinfo::getFolderDayFile(CString pathStr, CStringArray& arrStrFile)
{
	CString myDataPath, fdPath;
	myDataPath = pathStr + L"\\*.*";
	CString strTmp;

	CFileFind find;
	BOOL bf = find.FindFile(myDataPath);
	while (bf)
	{
		bf = find.FindNextFile();
		if (!find.IsDots())
		{
			fdPath = find.GetFilePath();
			if (find.IsDirectory())
			{
				//如果是文件夹，递归，继续往下找                        
				getFolderDayFile(fdPath, arrStrFile);
			}
			else
			{
				//如果是文件,判断是否是*.log
				strTmp = fdPath.Right(10);
				strTmp.MakeLower();
				if (strTmp == L"result.txt")
					arrStrFile.Add(fdPath);
			}
		}
	}
	find.Close();
}


void fileinfo::OnFileMerge(CString strPath, CString dstPath)
{
	CString dst;
	CStringArray str;
	CString data;
	getFolderDayFile(strPath, str);
	for (int i = 0; i < str.GetSize(); i++)
	{
		dst = str.GetAt(i);
		data = OnReadFileLastLine(dst);
		OnWriteFileLine(dstPath, data);
		//OnWriteFileLine(dstPath, L",");
	}
}


void fileinfo::OnFileMergeAll(CString PathA, CString PathB, CString PathResult)
{
	USES_CONVERSION;
	CString strA, strB;
	strA = ReadFileALL(PathA);
	strB = ReadFileALL(PathB);
	CharToUTF8(strA);
	CharToUTF8(strB);
	CFile file;
	//char * dstA = T2A(strA);
	//char * dstB = T2A(strB);
	file.Open(PathResult, CFile::modeNoTruncate | CFile::modeCreate | CFile::modeWrite);
	file.SeekToEnd();
	CT2CA outputStringA(strA, CP_UTF8);
	CT2CA outputStringB(strB, CP_UTF8);
	file.Write(outputStringA, ::strlen(outputStringA));
	file.Write(outputStringB, ::strlen(outputStringB));
	//file.Write(dstA, strlen(dstA));
	//file.Write(dstB, strlen(dstB));
	file.Flush();
	file.Close();
}


int fileinfo::ReadSetINI(CString path)
{

	CString stra;
	int n;
	GetPrivateProfileString(_T("TestSleep"), _T("SleepTime"), CString("NULL"), stra.GetBuffer(MAX_PATH), MAX_PATH, path);
	n = _ttoi(stra);
	return n;
}