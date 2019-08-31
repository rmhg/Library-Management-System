class Main
{
  sf::RenderTarget *t;
  sf::Event e;
  int ww,wh;
  Login sign;
  User U;
  bool setCall;
  public :
  Main(sf::RenderTarget*);
  void init();
  void Render();
  void Play();
  void run();
  void Callonce();
};
//RUNNING ORDER
//load->login->user
Main::Main(sf::RenderTarget* a):t(a)
{
 ww=600;wh=800;
 setCall = false;
}
void Main::Render()
{
 if(!sign.loginstatus)
 {
  sign.Render();
  }
  else
  {
   if(!setCall)
   Callonce();
   //sign.~Login();
   U.Render();
  }
}
void Main::Play()
{
  sf::VideoMode mode = sf::VideoMode::getDesktopMode();
  sf::RenderWindow* temp  = dynamic_cast<sf::RenderWindow*>(t);   //B2D
  temp->create(sf::VideoMode(mode.width,mode.height,mode.bitsPerPixel),"",0);
  temp->setFramerateLimit(60);
  init();
  while(temp->isOpen())
  {
    while(temp->pollEvent(e))
    {
      if(U.cf.startrender)
      U.cf.FormFunc(e);
      else
      if(!sign.loginstatus)
       sign.FormFunc(e);
    }
    temp->clear();
    this->Render();
    temp->display();
  }
}
void Main::Callonce()
{
  setCall = true;
  U.getdata(sign.datato());
  U.init();
}
void Main::init()
{
 sign.get(t);
 U.get(t);
}
