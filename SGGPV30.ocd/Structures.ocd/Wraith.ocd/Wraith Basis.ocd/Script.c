/*-- Basis --*/



#include DOOR
//#include BA15

protected func SoundOpenDoor() { return(1); }
protected func SoundCloseDoor() { return(1); }

func Damage()
{
  if(GetDamage() >= 250)
  {
   Explode(80);
  }
  return(1);
}
local ActMap = {
OpenDoor = {
Prototype = Action,
Name = "OpenDoor",
Length = 14,
Delay = 1,
X = 0,
Y = 0,
Wdt = 150,
Hgt = 60,
NextAction = "DoorOpen",
Sound = "luke1",
},
DoorOpen = {
Prototype = Action,
Name = "DoorOpen",
Length = 1,
Delay = 10,
X = 1950,
Y = 0,
Wdt = 150,
Hgt = 60,
NextAction = "CloseDoor",
StartCall = "OpenEntrance",
EndCall = "CloseEntrance",
},
CloseDoor = {
Prototype = Action,
Name = "CloseDoor",
Length = 14,
Delay = 1,
Reverse = 1,
X = 0,
Y = 0,
Wdt = 150,
Hgt = 60,
NextAction = "Idle",
Sound = "luke1",
},  };
local Name = "$Name$";
