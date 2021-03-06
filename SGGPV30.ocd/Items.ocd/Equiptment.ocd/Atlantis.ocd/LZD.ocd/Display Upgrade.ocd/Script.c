/* Display Upgradet */



local alpha;
local starget;
local jumper;

func Initialize()
{
  this.Visibility = VIS_Owner;
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
  
  var d = 900;
  var x = GetX(center) - GetX();
  var y = GetY(center) - GetY();

  for (var creature in FindObjects(Find_Distance(d, x, y), Find_OCF(OCF_Alive), Find_Exclude(center)))
  {   
    var xd = (creature->GetX() - center->GetX()) / (d / 30);
    var yd = (creature->GetY() - center->GetY()) / (d / 30);
    var marker = CreateObject(LZD2, xd, yd + 6, owner);
    marker->SetCon(creature->GetEnergy()/2);
  }
  
  Trekking();
  return(1);
}

func Trekking()
{
  var owner = GetOwner();
  var center = GetCursor(owner);
  
  var d = 900;
  if(starget)
  {
    if(ObjectDistance(center,starget) >= 900)
    {
     return(1);
    }
    var xd = (starget->GetX() - center->GetX(center)) / (d / 30);
    var yd = (starget->GetY() - GetY(center)) / (d / 30);
    var marke = CreateObject(LZD3, xd, yd + 6, owner);
    
    if(marke->GetOCF() & OCF_Alive)
    {
     marke->SetClrModulation(RGB(255,0,0));
    }
    
    if(marke->GetOCF() & OCF_Collectible)
    {
     marke->SetClrModulation(RGB(0,255,0));
    }
    
    if(marke->GetCategory() & C4D_Vehicle)
    {
     marke->SetClrModulation(RGB(0,0,255));
    }
    marke.name = starget;
  }
  
  if(jumper)
  {
    if(ObjectDistance(center,jumper) >= 900)
    {
     return(1);
    }
    var xd = (jumper->GetX() - center->GetX()) / (d / 30);
    var yd = (jumper->GetY() - center->GetY()) / (d / 30);
    var marke = CreateObject(LZD5, xd, yd + 6, owner);
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
Length = 5,
Delay = 10,
X = 0,
Y = 0,
Wdt = 75,
Hgt = 75,
NextAction = "Search",
PhaseCall = "Searching",
},  };
local Name = "$Name$";
