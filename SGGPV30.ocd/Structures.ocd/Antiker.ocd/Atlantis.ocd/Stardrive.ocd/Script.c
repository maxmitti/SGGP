/*-- Sternenantrieb --*/

// Stellt die Grundfunktionalität für alle Burgbauteile bereit


#include ALW2

local targets;

public func CastlePartWidth() { return (80); }
public func CastlePartHeight() { return (74); }
public func CastlePartTop() { return (-13); }
public func CastlePartBasement() { return; }
public func GetResearchBase() { return(ALW2); }
public func Atlantis()	{return(1);}
public func Height()		{return(GetY()+20);}
private func ExplodeSize()	{return 75;}

protected func Initialize()
{
	CreateObject(ALSK,0,0,GetOwner());
	return(_inherited());
}

protected func Check()
{
	return(1);
}


public func ControlUp(pCaller)
{
	for(obj in FindObjects(Find_InRect(-40,AbsY(0),80,Height()),Find_Or(Find_Owner(GetOwner()),Find_Owner(NO_OWNER))))
	{
		if(obj)
			obj->SetPosition(GetX(obj),GetY(obj)-1);
	}
	return(1);
}

public func ControlDown(pCaller)
{
		for(obj in FindObjects(Find_InRect(-40,AbsY(0),80,Height()),Find_Or(Find_Owner(GetOwner()),Find_Owner(NO_OWNER))))
		{
			obj->SetPosition(GetX(obj),GetY(obj)+1);
		}
	return(1);
}

public func ControlLeft(pCaller)
{
		for(obj in FindObjects(Find_InRect(-40,AbsY(0),80,Height()),Find_Or(Find_Owner(GetOwner()),Find_Owner(NO_OWNER))))
		{
			obj->SetPosition(GetX(obj)-1,GetY(obj));
		}
	return(1);
}

public func ControlRight(pCaller)
{
		for(obj in FindObjects(Find_InRect(-40,AbsY(0),80,Height()),Find_Or(Find_Owner(GetOwner()),Find_Owner(NO_OWNER))))
		{
			obj->SetPosition(GetX(obj)+1,GetY(obj));
		}
	return(1);
}
local Name = "$Name$";
