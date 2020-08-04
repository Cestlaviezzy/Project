#pragma once
class MESCheck
{
public:
	MESCheck();
	~MESCheck();
	CString CheckPCB(CString site, CString pcb);
	CString GetPCBdata(CString site, CString pcb);
	CString ResultToMES(CString site, CString user, CString equip, CString pcb, CString defect, CString result);
	CString SaveLogToMES(CString site, CString user, CString pcb, CString equip, CString defect, CString result);
};

