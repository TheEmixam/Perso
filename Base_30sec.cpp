
void DrawPeoples()
{
  
  
}

void DrawOnePeople(int iPlayers, int iArm, int iHand, float fRayon, Vec2 tCenter)
{
 float fWidth = 2*sin((360.f/iPlayers)/2)*fRayon;
 
 Shoulder.m_tPos = tCenter - (Vec2(0, fRayon + iArm).Rotate(360.f/iPlayers);
 Shoulder.setScale(fWidth/2); //Shoulder
  
}
