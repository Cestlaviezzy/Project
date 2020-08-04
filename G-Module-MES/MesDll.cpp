#include "pch.h"
#include "MesDll.h"

#using "..\\Debug\\EquipLinkMes.dll"

using namespace System;

MesDll::MesDll() {};
MesDll::~MesDll() {};


//检测工序
CString MesDll::CheckSite(CString Site)
{
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^MesSite = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ PutSite = gcnew String(Site);
	res = MesSite->CheckSite(PutSite);
	return res;
}


//检测工号
CString MesDll::CheckUser(CString Site, CString User)
{
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^MesUser = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ PutSite = gcnew String(Site);
	System::String^ PutUser = gcnew String(User);
	res = MesUser->CheckUser(PutSite, PutUser);
	return res;
}


//检测PCB
CString MesDll::CheckPCB(CString Site, CString Pcb)
{
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^MesPcb = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ PutSite = gcnew String(Site);
	System::String^ PutPcb = gcnew String(Pcb);
	res = MesPcb->CheckPCB(PutSite, PutPcb);
	return res;
}


//检测工单
CString MesDll::CheckNumber(CString Site, CString Pcb)
{
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^MesNumber = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ PutSite = gcnew String(Site);
	System::String^ PutPcb = gcnew String(Pcb);
	res = MesNumber->GetPcbData(PutSite, PutPcb);
	return res;
}


//通过PCB回传MAC SN Packageing
CString MesDll::CheckPCBisExist(CString Pcb)
{
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^MesExist = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ PutPcb = gcnew String(Pcb);
	res = MesExist->checkPCBisExist(PutPcb);
	return res;
}


//保存MES
CString MesDll::MESToSave(CString Site, CString User, CString Pcb, CString Equip, CString Defect, CString Result)
{
	/*
	需要6个参数：	1.SiteNo
					2.UserNo
					3.EquipListString
					4.PcbNo
					5.DefListString
					6.ResultListString
	*/
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^MesSave = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ PutSite = gcnew String(Site);
	System::String^ PutUser = gcnew String(User);
	System::String^ PutPcb = gcnew String(Pcb);
	System::String^ PutEquip = gcnew String(Equip);
	System::String^ PutDefect = gcnew String(Defect);
	System::String^ PutResult = gcnew String(Result);
	res = MesSave->SaveTestLogToMes(PutSite, PutUser, PutPcb, PutEquip, PutDefect, PutResult);
	return res;
}


//过站
CString MesDll::MESToStation(CString Site, CString User, CString Pcb, CString Equip, CString Defect, CString Result)
{
	/*
	需要6个参数：	1.SiteNo
					2.UserNo
					3.EquipListString
					4.PcbNo
					5.DefListString
					6.ResultListString
	*/
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^MesStation = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ PutSite = gcnew String(Site);
	System::String^ PutUser = gcnew String(User);
	System::String^ PutPcb = gcnew String(Pcb);
	System::String^ PutEquip = gcnew String(Equip);
	System::String^ PutDefect = gcnew String(Defect);
	System::String^ PutResult = gcnew String(Result);
	res = MesStation->SendResultToMes(PutSite, PutUser, PutPcb, PutEquip, PutDefect, PutResult);
	return res;
}


//新DLL  
CString MesDll::MESNewDLL(CString Site, CString User, CString Pcb, CString SN, CString MAC, CString Packageing)
{
	/*
	需要6个参数：	1.SiteNo
					2.UserNo
					3.PcbNo
					4.ag
					5.mac
					6.wbz
	*/
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^MesDll = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ PutSite = gcnew String(Site);
	System::String^ PutUser = gcnew String(User);
	System::String^ PutPcb = gcnew String(Pcb);
	System::String^ PutSN = gcnew String(SN);
	System::String^ PutMAC = gcnew String(MAC);
	System::String^ PutPackageing = gcnew String(Packageing);
	res = MesDll->updateWpLotColumns(PutSite, PutUser, PutPcb, PutSN, PutMAC, PutPackageing);
	return res;
}