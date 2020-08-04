#pragma once
class MesDll
{
public:
	MesDll();
	~MesDll();
	CString MesDll::CheckSite(CString Site);
	CString MesDll::CheckUser(CString Site, CString User);
	CString MesDll::CheckPCB(CString Site, CString Pcb);
	CString MesDll::CheckNumber(CString Site, CString Pcb);
	CString MesDll::CheckPCBisExist(CString Pcb);
	CString MesDll::MESToSave(CString Site, CString User, CString Pcb, CString Equip, CString Defect, CString Result);
	CString MesDll::MESToStation(CString Site, CString User, CString Pcb, CString Equip, CString Defect, CString Result);
	CString MesDll::MESNewDLL(CString Site, CString User, CString Pcb, CString SN, CString MAC, CString Packageing);
};

