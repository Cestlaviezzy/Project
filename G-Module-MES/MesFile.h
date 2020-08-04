#pragma once
class MesFile
{
public:
	MesFile();
	~MesFile();

	void MesFile::CharToUTF8(CString &str);
	int MesFile::GetFileLine(CString road);
	CString MesFile::ReadFileALL(CString path);
};

