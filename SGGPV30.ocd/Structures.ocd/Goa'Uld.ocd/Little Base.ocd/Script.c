/*-- Kleine Basis --*/



#include DOOR
#include BAS9

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

protected func ContainedUp()
{
  Sound("Connect");
  Message("Du kannst deine Basis|mit [Doppelgraben] aufr�sten!|Daf�r ben�tigst du entweder 50 Clunker|oder du legst in die Basis:|2x Holz|2x Metall|4x Stein",this());
  return(1);
}
  
protected func ContainedDigDouble()
{
  if(ObjectCount(WOOD,0,0,0,0,0,0,0,this()) >= 2)
  {
   if(ObjectCount(METL,0,0,0,0,0,0,0,this()) >= 2)
   {
    if(ObjectCount(ROCK,0,0,0,0,0,0,0,this()) >= 4)
    {
     FindObject(WOOD,0,0,0,0,0,0,0,this())->RemoveObject();
     FindObject(WOOD,0,0,0,0,0,0,0,this())->RemoveObject();
     FindObject(METL,0,0,0,0,0,0,0,this())->RemoveObject();
     FindObject(METL,0,0,0,0,0,0,0,this())->RemoveObject();
     FindObject(ROCK,0,0,0,0,0,0,0,this())->RemoveObject();
     FindObject(ROCK,0,0,0,0,0,0,0,this())->RemoveObject();
     FindObject(ROCK,0,0,0,0,0,0,0,this())->RemoveObject();
     FindObject(ROCK,0,0,0,0,0,0,0,this())->RemoveObject();
     Message("Du hast die Basis aufger�stet f�r:|2x Holz|2x Metall|4x Stein",this());
     Sound("Uncash");
     SetPosition(GetX(this()),GetY(this())-3);
     ChangeDef(GOEB);
     return(1);
    }
   }
  }

  if(GetWealth(GetOwner(this())) >= 50)
  {
   SetWealth(GetOwner(this()),GetWealth(GetOwner(this())) - 50);
   Message("Du hast die Basis f�r 50 aufger�stet!",this());
   Sound("Uncash");
   SetPosition(GetX(this()),GetY(this())-3);
   ChangeDef(GOEB);
   return(1);
  }
  return(1);
}
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
     
local ActMap = {
OpenDoor = {
Prototype = Action,
Name = "OpenDoor",
Length = 1,
Delay = 1,
FacetBase = 1,
NextAction = "DoorOpen",
},
DoorOpen = {
Prototype = Action,
Name = "DoorOpen",
Length = 1,
Delay = 10,
FacetBase = 1,
NextAction = "CloseDoor",
StartCall = "OpenEntrance",
EndCall = "CloseEntrance",
},
CloseDoor = {
Prototype = Action,
Name = "CloseDoor",
Length = 1,
Delay = 1,
FacetBase = 1,
NextAction = "Idle",
},  };
local Name = "$Name$";
