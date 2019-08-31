class load
{
 sf::RenderTarget *t;
 sf::RenderWindow *w;
 sf::Texture tex;
 sf::Sprite Bg;
 sf::VideoMode fullscreen;
 sf::RectangleShape lines[4];
 sf::Event e;
 sf::SoundBuffer sound;
 sf::Font font;
 sf::Text lms,by,rm;
 sf::Color colarr[7] = {sf::Color::White,sf::Color::Cyan,sf::Color::Yellow,sf::Color::Blue,sf::Color::Red,sf::Color::Green,sf::Color::Magenta};;
 int ww,wh,ca;
 public :
 load(sf::RenderTarget*);
 void animate();
 void init();
 void Render();
 void Play();
};
load::load(sf::RenderTarget* a):t(a)
{
// colarr[7] = {sf::Color::White,sf::Color::Cyan,sf::Color::Yellow,sf::Color::Blue,sf::Color::Red,sf::Color::Green,sf::Color::Magenta};
 font.loadFromFile("data/sans.ttf");
 fullscreen = sf::VideoMode::getDesktopMode();
 ww = (700.00/1920.00)*fullscreen.width;
 wh = (450.00/1080.00)*fullscreen.height;
 lines[0].setPosition(0,0);
 lines[0].rotate(-37.87470599);
 lines[1].setPosition(ww/2,wh);
 lines[1].rotate(37.87470599);
 lines[2].setPosition(0,wh);
 lines[2].rotate(37.87470599);
 lines[3].setPosition(ww/2,0);
 lines[3].rotate(-37.87470599);
 tex.loadFromFile("data/load.jpg");
 Bg.setTexture(tex);
 Bg.setScale((float)ww/tex.getSize().x,(float)wh/tex.getSize().y);
 for(int i = 0;i < 4;i++)
 {
  lines[i].setSize(sf::Vector2f(10,0));
  lines[i].setFillColor(sf::Color(255,255,255,50));
  lines[i].setOutlineThickness(0);
 }
 lms.setFont(font);
 lms.setCharacterSize(70);
 lms.setString("LMS");
 lms.setFillColor(sf::Color::Transparent);
 lms.setOutlineColor(sf::Color::Yellow);
 lms.setOutlineThickness(0);
 by = lms;
 by.setString("By");
 by.setCharacterSize(30);
 by.setOutlineColor(sf::Color::White);
 by.setOutlineThickness(1);
 rm = lms;
 rm.setString("Rahul Mishra");
 rm.setOutlineColor(sf::Color::Cyan);
 rm.setCharacterSize(60);
 rm.setOutlineThickness(0);
 ca = sqrt(pow(ww/2,2) + pow(wh,2));
}
void load::Render()
{
   t->draw(Bg);
   t->draw(rm);
 for(int i = 0;i < 4;i++)
  t->draw(lines[i]);
  t->draw(lms);
  t->draw(by);
 animate();
}
void load::animate()
{
 static float vel1 = 0;
 lms.setPosition(ww/2 - lms.getGlobalBounds().width/2.f,(8.0/45.0)*(float)wh);
 by.setPosition(ww/2 - by.getGlobalBounds().width/2.f,wh/2 - by.getGlobalBounds().height/2.f);
 rm.setPosition(ww/2 - rm.getGlobalBounds().width/2.f,wh - rm.getGlobalBounds().height - 100);
 static float k = 5,co = 0;
 switch((int)vel1/ca)
 {
  case 0:{lines[0].setSize(sf::Vector2f(10,vel1));lines[2].setSize(sf::Vector2f(10,-vel1));}
  break;
  case 1:{lines[1].setSize(sf::Vector2f(10,-vel1 + ca));lines[3].setSize(sf::Vector2f(10,vel1 - ca));k = 5; lms.setOutlineThickness(1);lms.setFillColor(sf::Color(200,200,0,100+co));rm.setOutlineThickness(1);rm.setFillColor(sf::Color(255,255,200,100 + co++));}
  break;
 }
 if(vel1/ca >= 3)
 {
  w->close();
  return ;
 }
 vel1+=k;
}
void load::init()
{

}
void load::Play()
{
  w = dynamic_cast<sf::RenderWindow*>(t);
  w->create(sf::VideoMode(ww,wh),"",0);
  while(w->isOpen())
  {
   w->setFramerateLimit(60);
   while(w->pollEvent(e))
   {
    if(e.type == sf::Event::Closed)
    {
     w->close();
     exit(0);
    }
   }
   w->clear();
   Render();
   w->display();
  }
}
