/* Biomap */



local alpha;
local jumper;

protected func Initialize()
{
  SetClrModulation(RGBa(255, 255, 255, 255));
  
  SetVisibility(VIS_Owner);
  SetPosition(-80, 80);

  SetAction("FadeIn");
  return(1);
}

func FadingIn()
{
  alpha += 10;

  if (alpha >= 255)
  {
    SetAction("Search");
    alpha = 255;
  }
  SetClrModulation(RGBa(255, 255, 255, 255 - alpha));
  return(1);
}

func Searching()
{
  var owner = GetOwner();
  var center = GetCursor(owner);
  
  var d = 450;
  var x = GetX(center) - GetX();
  var y = GetY(center) - GetY();

  for (var creature in FindObjects(Find_Distance(d, x, y), Find_OCF(OCF_Alive), Find_Exclude(center)))
  {   
   var xd = (creature->GetX() - center->GetX()) / (d / 30);
   var yd = (creature->GetY() - center->GetY()) / (d / 30);
   var marker = CreateObject(LZDM, xd, yd + 6, owner);
   marker->SetCon(creature->GetEnergy()/2);
  }
  
  if(jumper)
  {
    if(ObjectDistance(center,jumper) >= 450)
    {
     return(1);
    }
    var xd = (GetX(jumper) - GetX(center)) / (d / 30);
    var yd = (GetY(jumper) - GetY(center)) / (d / 30);
    CreateObject(LZD4, xd, yd + 6, owner);
  }
  return(1);
}
local ActMap = {
FadeIn = {
Prototype = Action,
Name = "FadeIn",
Length = 1,
Delay = 1,
FacetBase = 1,
NextAction = "FadeIn",
StartCall = "FadingIn",
},
Search = {
Prototype = Action,
Name = "Search",
Length = 1,
Delay = 37,
FacetBase = 1,
NextAction = "Search",
StartCall = "Searching",
},  };
local Name = "$Name$";
