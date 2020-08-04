#pragma once
class MESconnet
{
public:
	MESconnet();
	~MESconnet();

	CString MESconnet::CheckSite(CString site);
	CString MESconnet::CheckPCB(CString site, CString pcb);
	CString MESconnet::GetPCBdata(CString site, CString pcb);
	CString ResultToMES(CString site, CString user, CString equip, CString pcb, CString defect, CString result);

};

