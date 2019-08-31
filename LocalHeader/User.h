class User
{
  sf::RenderTarget *t;
  dat data;
  Menu menu[2],ag;
  sf::Font font;
  sf::Text head;
  sf::RectangleShape logout;
  sf::Text logoutt;
  Clickable logoutb;
  std::vector<std::string> a,b,c;
  public :
  Function func;
  bool logouts;
  User();
  User(sf::RenderTarget*);
  void get(sf::RenderTarget*);
  void getdata(currentuser);
  void init();
  void Resize();
  void Render();
  int Rs;
  void input(char);
  void gettofunc(dat u);
};
void User::gettofunc(dat u)
{
 func.det = u;
}
void User::input(char is)
{
 func.input(is);
}
User::User()
{
 a.push_back("GERNAL");
 a.push_back("ADMIN");
 b.push_back("ISSUE BOOK");
 b.push_back("RETURN BOOK");
 b.push_back("SHOW BOOKS");
 c.push_back("ADD USER");
 c.push_back("REM USER");
 c.push_back("ADD BOOK");
 c.push_back("REM BOOK");
 c.push_back("SHOW USERS");
 Rs = 0;
}
User::User(sf::RenderTarget* a)
{
 t = a;
}
void User::get(sf::RenderTarget* a)
{
 t = a;
 logouts = false;
 init();
}
void User::getdata(currentuser U)
{
 data.name = U.name;
 data.userid = U.userid;
 data.admin_status = U.admin_status;
 data.des = U.des;
 init();
}
void User::init()
{
 gettofunc(data);
 font.loadFromFile("data/sans.ttf");
 head.setFont(font);
 head.setString("WELCOME "+data.name);
 head.setPosition(t->getSize().x/2 - head.getGlobalBounds().width/2,40.f);
 logoutt.setFont(font);
 logoutt.setFillColor(sf::Color::Black);
 logoutt.setCharacterSize(20);
 logoutt.setString("LOGOUT");
 logout.setSize(sf::Vector2f(100,50));
 logout.setFillColor(sf::Color(255,255,255,100));
 logout.setPosition(t->getSize().x - 100,40);
 logoutt.setPosition(logout.getPosition().x,logout.getPosition().y);
 logoutb.get(dynamic_cast<sf::RenderWindow*>(t),logout.getPosition().x,logout.getPosition().y,logout.getSize().x,logout.getSize().y);
 ag.get(t,0,100,100,100,a,true);
 menu[0].get(t,0,0,100,100,b);
 menu[1].get(t,0,0,100,100,c);
 func.get(t);
}
void User::Resize()
{
 ag.onResize();
 menu[0].onResize();
 menu[1].onResize();
}
void User::Render()
{
  ag.Render();
  if(ag.opc[1].Clicked() && data.admin_status == 'Y')
    Rs = 1;
  if(ag.opc[0].Clicked())
    Rs = 0;
  t->draw(head);
  t->draw(logoutt);
  t->draw(logout);
  if(logoutb.Clicked())
   logouts = true;
  switch(Rs)
  {
   case 0:{
            menu[0].Render();
            if(menu[0].opc[0].Clicked())
             Rs = 2;
            if(menu[0].opc[1].Clicked())
             Rs = 3;
            if(menu[0].opc[2].Clicked())
              Rs = 9;

          }
   break;
   case 1:{
            menu[1].Render();
            if(menu[1].opc[0].Clicked())
               Rs = 4;
            if(menu[1].opc[1].Clicked())
                 Rs = 5;
            if(menu[1].opc[2].Clicked())
                  Rs = 6;
            if(menu[1].opc[3].Clicked())
                    Rs = 7;
            if(menu[1].opc[4].Clicked())
                    Rs = 8;
          }
   break;
   case 2:{ func.findbook();func.Render(); }
   break;
   case 3:{func.retbook();func.Render();}
   break;
   case 4:{func.adduser();func.Render();}
   break;
   case 5:{func.remuser();func.Render();}
   break;
   case 6:{func.addbook();func.Render();}
   break;
   case 7:{func.rembook();func.Render();}
   break;
   case 8:{func.showusers();}
   break;
   case 9:{func.showbooks();}
  }
}
