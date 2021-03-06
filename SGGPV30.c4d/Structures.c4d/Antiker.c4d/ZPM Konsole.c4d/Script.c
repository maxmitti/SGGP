#strict 2
#include BAS3

local zpm1, zpm2, zpm3;
local User;
local info;
local iMode;

func Initialize()
{
  zpm1 = CreateObject(ZPM2);
  zpm2 = CreateObject(ZPM2);
  zpm3 = CreateObject(ZPM2);
  SetObjectOrder(zpm1,this);
  SetObjectOrder(zpm2,this);
  SetObjectOrder(zpm3,this);
  return(1);
}

func Damage()
{
  if(GetDamage() > 200)
  {
   Explode(EnrgA()+EnrgB()+EnrgC()+50);
  }
  return(1);
}

func Destruction()
{
  if(zpm1) zpm1->RemoveObject();
  if(zpm2) zpm2->RemoveObject();
  if(zpm3) zpm3->RemoveObject();
  return _inherited();
}

func ZpmA()
{
  if(zpm1->GetZpm() == 0)
  {
   return("1.ZPM:<c ff0000> Nicht vorhanden</c>");
  }

  if(GetAction(zpm1) == "Depledet")
  {
   return("1.ZPM:<c 000000> Ersch�pft</c>");
  }
  
  if(GetAction(zpm1) == "Activen")
  {
   return("1.ZPM:<c 00ff00> Aktiv</c>");
  }
  
  if(GetAction(zpm1) == "Inactive")
  {
   return("1.ZPM:<c 0000ff> Inaktiv</c>");
  }
  return(1);
}

func ZpmB()
{
  if(zpm2->GetZpm() == 0)
  {
   return("2.ZPM:<c ff0000> Nicht vorhanden</c>");
  }

  if(GetAction(zpm2) == "Depledet")
  {
   return("2.ZPM:<c 000000> Ersch�pft</c>");
  }
  
  if(GetAction(zpm2) == "Activen")
  {
   return("2.ZPM:<c 00ff00> Aktiv</c>");
  }
  
  if(GetAction(zpm2) == "Inactive")
  {
   return("2.ZPM:<c 0000ff> Inaktiv</c>");
  }
  return(1);
}

func ZpmC()
{
  if(zpm3->GetZpm() == 0)
  {
   return("3.ZPM:<c ff0000> Nicht vorhanden</c>");
  }

  if(GetAction(zpm3) == "Depledet")
  {
   return("3.ZPM:<c 000000> Ersch�pft</c>");
  }
  
  if(GetAction(zpm3) == "Activen")
  {
   return("3.ZPM:<c 00ff00> Aktiv</c>");
  }
  
  if(GetAction(zpm3) == "Inactive")
  {
   return("3.ZPM:<c 0000ff> Inaktiv</c>");
  }
  return(1);
}

func EnrgA()
{
  return(zpm1->Enrg());
}

func EnrgB()
{
  return(zpm2->Enrg());
}

func EnrgC()
{
  return(zpm3->Enrg());
}

func Check()
{
  if(GetCon() != 100)
  {
   return(1);
  }

  if(CheckEnergyNeedChain())
  {
   GiveEnerg();
  }
  if(zpm1)
  {
	zpm1->SetPosition(GetX()-13,GetY()-5);
	zpm1->SetYDir();
  }
  else
  {
	  zpm1 = CreateObject(ZPM2);
	  SetObjectOrder(zpm1,this);
  }
  if(zpm2)
  {
	  zpm2->SetPosition(GetX()+3,GetY()-5);
	  zpm2->SetYDir();
  }
  else
  {
	  zpm2 = CreateObject(ZPM2);
	  SetObjectOrder(zpm2,this);
  }
  if(zpm3)
  {
	  zpm3->SetPosition(GetX()+13,GetY()-5);
	  zpm3->SetYDir();
  }
  else
  {
	  zpm3 = CreateObject(ZPM2);
	  SetObjectOrder(zpm3,this);
  }
  if(info)
  {
   Message(Format("%v (%v%)|%v (%v%)|%v (%v%)",ZpmA(),EnrgA(),ZpmB(),EnrgB(),ZpmC(),EnrgC()),this);
  }
  else Message("");
  return(1);
}

func GiveEnerg()
{
  if(zpm1->GetZpm() != 0)
  {
   if(GetAction(zpm1) == "Activen")
   {
    zpm1->Minus();
    DoEnergy(10000);
    return(1);
   }
  }
  
  if(zpm2->GetZpm() != 0)
  {
   if(GetAction(zpm2) == "Activen")
   {
    zpm2->Minus();
    DoEnergy(10000);
    return(1);
   }
  }
  
  if(zpm3->GetZpm() != 0)
  {
   if(GetAction(zpm3) == "Activen")
   {
    zpm3->Minus();
    DoEnergy(10000);
    return(1);
   }
  }
  return(0);
}

func Free()
{
  if(zpm1->GetZpm() == 0)
  {
   return(1);
  }
  if(zpm2->GetZpm() == 0)
  {
   return(1);
  }
  if(zpm3->GetZpm() == 0)
  {
   return(1);
  }
  return(0);
}

func HasZpm(bool active)
{
	var i;
  if(zpm1->GetZpm() != 0)
  {
   if(!active) i++;
   else if(zpm1->GetZpm()->GetAction() == "Activen") i++;
  }
  if(zpm2->GetZpm() != 0)
  {
   if(!active) i++;
   else if(zpm2->GetZpm()->GetAction() == "Activen") i++;
  }
  if(zpm3->GetZpm() != 0)
  {
   if(!active) i++;
   else if(zpm3->GetZpm()->GetAction() == "Activen") i++;
  }
  return i;
}

public func GetActiveZPMCount()
{
	return HasZpm(true);
}

public func GetAllZPMs()
{
	return [zpm1, zpm2, zpm3];
}

func ControlDigDouble(pCaller)
{
  User = pCaller;
  CreateMenu(GetID(this()), User, 0,0, "ZPM Konsole", 0, 1);
  AddMenuItem("Info An/Aus", "Info",MEPU,User);
  if(FindContents(ZPM_,User))
  {
   if(Free())
   {
    AddMenuItem("ZPM hineinlegen","PutZpm",MEPU,User);
   }
  }
  if(HasZpm())
  {
   AddMenuItem("ZPM herausnehmen","GetZpm",MEPU,User);
  }
  
  
  if(ZpmA() == "1.ZPM:<c 00ff00> Aktiv</c>")
  {
   AddMenuItem("1.ZPM Deaktivieren","SwtZpmA",MEPU,User);
  }
  if(ZpmA() == "1.ZPM:<c 0000ff> Inaktiv</c>")
  {
   AddMenuItem("1.ZPM Aktivieren","SwtZpmA",MEPU,User);
  }
  
  if(ZpmB() == "2.ZPM:<c 00ff00> Aktiv</c>")
  {
   AddMenuItem("2.ZPM Deaktivieren","SwtZpmB",MEPU,User);
  }
  if(ZpmB() == "2.ZPM:<c 0000ff> Inaktiv</c>")
  {
   AddMenuItem("2.ZPM Aktivieren","SwtZpmB",MEPU,User);
  }
  
  if(ZpmC() == "3.ZPM:<c 00ff00> Aktiv</c>")
  {
   AddMenuItem("3.ZPM Deaktivieren","SwtZpmC",MEPU,User);
  }
  if(ZpmC() == "3.ZPM:<c 0000ff> Inaktiv</c>")
  {
   AddMenuItem("3.ZPM Aktivieren","SwtZpmC",MEPU,User);
  }
  return(1);
}

func SwtZpmA()
{
  if(GetAction(FindContents(ZPM_,zpm1)) == "Activen")
  {
   FindContents(ZPM_,zpm1)->SetAction("Inactive");
  }
  else
  {
   FindContents(ZPM_,zpm1)->SetAction("Activen");
  }
  return(1);
}

func SwtZpmB()
{
  if(GetAction(FindContents(ZPM_,zpm2)) == "Activen")
  {
   FindContents(ZPM_,zpm2)->SetAction("Inactive");
  }
  else
  {
   FindContents(ZPM_,zpm2)->SetAction("Activen");
  }
  return(1);
}

func SwtZpmC()
{
  if(GetAction(FindContents(ZPM_,zpm3)) == "Activen")
  {
   FindContents(ZPM_,zpm3)->SetAction("Inactive");
  }
  else
  {
   FindContents(ZPM_,zpm3)->SetAction("Activen");
  }
  return(1);
}

func GetZpm()
{
  if(zpm1->GetZpm() != 0)
  {
   FindContents(ZPM_,zpm1)->Enter(User);
   return(1);
  }
  
  if(zpm2->GetZpm() != 0)
  {
   FindContents(ZPM_,zpm2)->Enter(User);
   return(1);
  }
  
  if(zpm3->GetZpm() != 0)
  {
   FindContents(ZPM_,zpm3)->Enter(User);
   return(1);
  }
  return(1);
}

func PutZpm()
{
  if(!FindContents(ZPM_,User))
  {
   return(1);
  }
  
  if(zpm1->GetZpm() == 0)
  {
   FindContents(ZPM_,User)->Enter(zpm1);
   return(1);
  }
  
  if(zpm2->GetZpm() == 0)
  {
   FindContents(ZPM_,User)->Enter(zpm2);
   return(1);
  }
  
  if(zpm3->GetZpm() == 0)
  {
   FindContents(ZPM_,User)->Enter(zpm3);
   return(1);
  }
  return(1);
}

func Info()
{
  if(info)
  {
   info = 0;
  }
  else
  {
   info = 1;
  }
  Sound("Connect");
  return(1);
}
func IsAntiker()
{
	return(1);
}

public func AtlantisOSFunc()
{
	var i = 0;
	for(var zpm in GetAllZPMs())
	{
		if(zpm && zpm->GetAction() == "Activen")
		{
			i += zpm->Enrg();
		}
	}
	if(i < 10) return ATLANTISOS_ZPMLOW;
	return ATLANTISOS_OK;
}