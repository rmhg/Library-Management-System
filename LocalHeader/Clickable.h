class Clickable
{
 int x,y;
 int hx,hy;
 int w,h;
 sf::RenderWindow *window;
 //sf::Event *e;
 sf::SoundBuffer b;
 sf::Sound snd;
 bool soundenable;
 public :
 Clickable();
 Clickable(sf::RenderWindow *window);
 void init();
 void get(sf::RenderWindow *,int,int,int,int,bool);
 void setPosition(int,int);
 bool Hover();
 bool Clicked();
};
void Clickable::setPosition(int xx,int yy)
{
 x = xx;
 y = yy;
}
void Clickable::get(sf::RenderWindow *a,int xx,int yy,int ww,int hh,bool se = false)
{
 window = a;
 x = xx;
 y = yy;
 w = ww;
 h = hh;
 soundenable = se ;
 init();
}
Clickable::Clickable()
{
 soundenable = false ;
 init();
}
Clickable::Clickable(sf::RenderWindow *a):window(a)
{init();}
void Clickable::init()
{
  b.loadFromFile("Data/buttonclick.wav");
  snd.setBuffer(b);
}
bool Clickable::Hover()
{

 hx = sf::Mouse::getPosition(*window).x;
 hy = sf::Mouse::getPosition(*window).y;
 if(hx > x && hx <(x + w) && hy > y && hy < (y + h))
  return true;
 return false;
}
bool Clickable::Clicked()
{
 if(Hover())
   if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
   {
    //if(soundenable)
       snd.play();
    return true;
   }
  return false;
}
