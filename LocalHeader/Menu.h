class Menu
{
  int x,y,w,h,chs;
  int spacey,spacex;
  sf::RenderTarget *t;
  sf::RenderWindow *win;
  sf::RectangleShape rect;
  std::vector<sf::RectangleShape> heff;
  sf::Font font;
  std::vector<sf::Text> options;
  std::vector<std::string> vstr;
  std::vector<float> vi;
  bool s;
  public :
  std::vector<Clickable> opc;
  Menu();
  Menu(sf::RenderTarget*);
  void init();
  void Render();
  void get(sf::RenderTarget *a,int xx,int yy,int ww,int hh,std::vector<std::string>,bool);
  void onResize();
  void adj();
  void buttoning();
};
void Menu::adj()
{
 float max = 0;
 std::vector<float> temp;
 for(int i = 0; i < options.size();i++)
   temp.push_back(options[i].getGlobalBounds().width);
 for(int i = 0;i < temp.size();i++)
    if(max < temp[i])
     max = temp[i];
  rect.setSize(sf::Vector2f(max + 10,(options[0].getCharacterSize() + 10) * options.size()));
}
void Menu::onResize()
{
if(!s)
   rect.setPosition(t->getSize().x/2 - w/2,t->getSize().y/2 - h/2);
   else
   rect.setPosition(x,y);
 for(int i = 0;i < options.size();i++)
  options[i].setPosition(rect.getPosition().x + spacex,rect.getPosition().y + spacey*i + chs*i);
}
void Menu::get(sf::RenderTarget *a,int xx,int yy,int ww,int hh,std::vector<std::string> tes = std::vector<std::string>(),bool st = false)
{
  t = a;
  x = xx;
  y = yy;
  w = ww;
  h = hh;
  s = st;
  if(tes.size())
   vstr = tes;
  init();
}
Menu::Menu()
{
  std::string a = "LOGIN";
  std::string b = "ABOUT";
  std::string c = "NEW USER";
  vstr.push_back(a);
  vstr.push_back(b);
  vstr.push_back(c);

}
void Menu::init()
{
   spacex = 3;
   spacey = 10;
   chs = 30;
   rect.setSize(sf::Vector2f(w,h));
   if(!s)
   rect.setPosition(t->getSize().x/2 - w/2,t->getSize().y/2 - h/2);
   else
   rect.setPosition(x,y);
   rect.setFillColor(sf::Color(255,255,255,170));
   rect.setOutlineColor(sf::Color::Black);
   rect.setOutlineThickness(0.8);
   font.loadFromFile("data/sans.ttf");
   if(options.size() < vstr.size())
   for(int i = 0; i < vstr.size(); i++)
   {
     sf::Text temp;
     temp.setFont(font);
     temp.setCharacterSize(chs);
     temp.setPosition(rect.getPosition().x + spacex,rect.getPosition().y + spacey*i + chs*i);
     temp.setString(vstr[i]);
     temp.setFillColor(sf::Color::Transparent);
     temp.setOutlineColor(sf::Color::Black);
     temp.setOutlineThickness(0.5);
     options.push_back(temp);
   }
   win = dynamic_cast<sf::RenderWindow*>(t);
   if(opc.size() < vstr.size())
   for(int i = 0;i<vstr.size();i++)
   {
     Clickable temp;
     temp.get(win,options[i].getPosition().x,options[i].getPosition().y,options[i].getLocalBounds().width,chs);
     opc.push_back(temp);
   }
   if(heff.size() < vstr.size())
   for(int i = 0; i < vstr.size();i++)
   {
    sf::RectangleShape temp;
    temp.setSize(sf::Vector2f(0,10));
    temp.setPosition(options[i].getPosition().x,options[i].getPosition().y + chs);
    temp.setFillColor(sf::Color(200,250,240,200));
    heff.push_back(temp);
    vi.push_back(0);
   }
   adj();
}
void Menu::buttoning()
{
 for(int i = 0; i < opc.size();i++)
 {
  heff[i].setPosition(options[i].getPosition().x,options[i].getPosition().y + chs);
  opc[i].get(win,options[i].getPosition().x,options[i].getPosition().y,options[i].getLocalBounds().width,chs);
  if(opc[i].Hover())
  {
   options[i].setFillColor(sf::Color::Blue);
   heff[i].setSize(sf::Vector2f(vi[i]>=options[i].getLocalBounds().width?options[i].getLocalBounds().width:vi[i]+=(float)t->getSize().x/1000,10));
  }
  else
  {
   options[i].setFillColor(sf::Color::Transparent);
   heff[i].setSize(sf::Vector2f(vi[i]<=0?0:vi[i]-=t->getSize().x/700,10));
  }
 }
}
void Menu::Render()
{
  buttoning();
  t->draw(rect);
  for(int i = 0;i < options.size();i++)
  {
   t->draw(options[i]);
   t->draw(heff[i]);
  }

}
Menu::Menu(sf::RenderTarget *a):t(a)
{
  init();
}
