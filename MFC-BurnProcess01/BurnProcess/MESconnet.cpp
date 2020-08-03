﻿#include "pch.h"
#include "MESconnet.h"


#using "..\\Debug\\EquipLinkMes.dll"

//using namespace Genesis;
using namespace System;



MESconnet::MESconnet() {}
MESconnet::~MESconnet() {}


CString MESconnet::CheckSite(CString site)
{
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^messite = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ put_site = gcnew String(site);
	res = messite->CheckSite(put_site);
	return res;
}

CString MESconnet::CheckPCB(CString site, CString pcb)
{
	/*
	判断PCB是否存在
	需要2个参数：	1.siteNo
					2.pcbNo
	*/

	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^pcbdata = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ put_site = gcnew String(site);
	System::String^ put_pcb = gcnew String(pcb);

	res = pcbdata->CheckPCB(put_site, put_pcb);

	return res;
}

CString MESconnet::GetPCBdata(CString site, CString pcb)
{
	/*
	通过PCB获取工单号
	需要2个参数：	1.siteNo
					2.pcbNo
	*/
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^pcbdata = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ put_site = gcnew String(site);
	System::String^ put_pcb = gcnew String(pcb);

	res = pcbdata->GetPcbData(put_site, put_pcb);
	return res;
}

//传入结果路径 判断结果文件第一行是pass or fail来上传良品或者不良
CString MESconnet::ResultToMES(CString site, CString user, CString pcb, CString equip, CString defect, CString result)
{
	/*
	需要6个参数：	1.siteNo
					2.userNo
					3.equipListString
					4.pcbNo
					5.defListString
					6.resultListString
	*/
	CString res;
	Genesis::Gtimes::Interface::EquipLinkMes ^sendresulttomes = gcnew Genesis::Gtimes::Interface::EquipLinkMes;
	System::String^ put_site = gcnew String(site);
	System::String^ put_user = gcnew String(user);
	System::String^ put_pcb = gcnew String(pcb);
	System::String^ put_equip = gcnew String(equip);
	System::String^ put_defect = gcnew String(defect);
	System::String^ put_result = gcnew String(result);
	res = sendresulttomes->SendResultToMes(put_site, put_user, put_pcb, put_equip, put_defect, put_result);
	return res;
}