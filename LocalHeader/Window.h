class Window
{
 sf::RenderTarget *t;
 sf::VertexArray lines;
 sf::Vertex line[2],cross1[2],cross2[2];
 sf::RenderWindow *w;
 sf::Texture tex;
 sf::Sprite Bg;
 sf::RectangleShape rect,stop,backr;
 sf::Font font;
 sf::Text title,backt;
 sf::Event e;
 Login temp;
 Form f;
 sf::VideoMode fullScreen;
 Clickable resizeb,closeb,backb;
 Menu m;
 Table b;
 User h;
 int Rs;
 About Ab;
 bool small,x;
 public :
 std::string inputstr;
 bool on;
 Window(){Rs = 3;}
 Window(sf::RenderTarget *t);
 void clickable();
 void Play();
 void init();
 void RenderMain();
 void Render();
 void resizew();
 void Close();
 void Draggable();
 void initObj();
 void Back();
 void FormMan();
 void input();
};
void Window::Back()
{
  if(backb.Clicked())
   Rs=0;
}
void Window::input()
{
 if(e.type == sf::Event::TextEntered)
 {
       temp.FormFunc(e.text.unicode);
      if(h.func.inputs)
       h.input(e.text.unicode);
      if(x)
       f.inputdata(e.text.unicode);
 }
}
void Window::Draggable()
{
  Clickable temp;
  temp.get(w,0,0,w->getSize().x - 100,40,true);
   if(small && temp.Hover())
    if(e.type == sf::Event::MouseButtonPressed)
    {
     while(e.type != sf::Event::MouseButtonReleased)
     {
      w->pollEvent(e);
      w->setPosition(sf::Vector2i(sf::Mouse::getPosition().x,sf::Mouse::getPosition().y ));
      }
      return ;
    }

}
void Window::Close()
{
 if(closeb.Hover())
 {
  cross1[0].color = sf::Color::Red;
  cross1[1].color = sf::Color::Red;
  cross2[0].color = sf::Color::Red;
  cross2[1].color = sf::Color::Red;
 }
 else
 {
  cross1[0].color = sf::Color::Blue;
  cross1[1].color = sf::Color::Blue;
  cross2[0].color = sf::Color::Green;
  cross2[1].color = sf::Color::Green;
 }
 if(closeb.Clicked())
 {
  w->close();
  exit(0);
 }
}
void Window::resizew()
{
 if(resizeb.Hover())
  rect.setOutlineColor(sf::Color(0,255,0,100));
 else
  rect.setOutlineColor(sf::Color(255,0,0,100));
 if(small&&resizeb.Clicked())
  init();
 else
 if(resizeb.Clicked())
 {
  w->create(sf::VideoMode(800,600),"",0);
  small = true;
  Bg.setScale((float)t->getSize().y/tex.getSize().y,(float)t->getSize().y/tex.getSize().y);
  initObj();
 }
 m.onResize();
 temp.Resize();
// books.Resize();
  h.Resize();
}
void Window::Render()
{
 t->draw(Bg);
 t->draw(stop);
 t->draw(backr);
 t->draw(backt);
 Close();
 resizew();
 Back();
 t->draw(title);
 t->draw(rect);
 t->draw(cross1,2,sf::Lines);
 t->draw(cross2,2,sf::Lines);
 switch(Rs)
 {
   case 0: {m.Render();
            if(m.opc[0].Clicked())
              Rs = 1;
             if(m.opc[1].Clicked())
               Rs = 2;
             if(m.opc[2].Clicked())
             {
               Rs = 3;
               x = true;
             }
            }
   break;
   case 1:{temp.Render();
            if(temp.loginstatus)
               {
                h.getdata(temp.datato());
                Rs = 4;
               }
          }
    break;
   case 2:{Ab.Render();
          }
    break;
   case 3:{
            f.Formty(5);
            f.Render();
            if(f.button.click.Clicked())
            {
             insertuser(f.data);
             Rs = 0;
             x = false;
             break;
            }
          }
   break;
   case 4:{
           h.Render();
           if(h.logouts)
           {
            temp.Reset();
            Rs = 0;
            h.logouts = false;
           }
          }
    break;
   case 5:{
          }
 }
}
void Window::init()
{
  on = false ;
  w = dynamic_cast<sf::RenderWindow*>(t);
  fullScreen = sf::VideoMode::getDesktopMode();
  w->create(fullScreen,"",0);
  small = false;
  font.loadFromFile("data/sans.ttf");
  title.setFont(font);
  title.setString("LMS");
  title.setPosition(0,0);
  title.setFillColor(sf::Color::Transparent);
  title.setOutlineColor(sf::Color::Black);
  title.setOutlineThickness(0.4);
  tex.loadFromFile("data/background.jpg");
  Bg.setTexture(tex);
  Bg.setScale((float)t->getSize().x/tex.getSize().x,(float)t->getSize().y/tex.getSize().y);
  m.get(t,100,100,100,100);
  initObj();
}
void Window::initObj()
{
   x = false;
   line[0] = sf::Vertex(sf::Vector2f(0,40.f),sf::Color::Red);
   line[1] = sf::Vertex(sf::Vector2f(t->getSize().x,40.f),sf::Color::Green);
   rect.setSize(sf::Vector2f(10,10));
   rect.setPosition(t->getSize().x - 45,10);
   rect.setFillColor(sf::Color::Transparent);
   rect.setOutlineColor(sf::Color::Black);
   rect.setOutlineThickness(1.8);
   resizeb.get(w,rect.getPosition().x,rect.getPosition().y,rect.getSize().x,rect.getSize().y,true);
   cross1[0] = sf::Vertex(sf::Vector2f(t->getSize().x - 10,10),sf::Color::Blue);
   cross2[0] = sf::Vertex(sf::Vector2f(t->getSize().x - 20,10),sf::Color::Green);
   cross1[1] = sf::Vertex(sf::Vector2f(t->getSize().x - 20,20),sf::Color::Blue);
   cross2[1] = sf::Vertex(sf::Vector2f(t->getSize().x - 10,20),sf::Color::Green);
   closeb.get(w,t->getSize().x - 20,10,10,10);
   stop.setSize(sf::Vector2f(t->getSize().x,40.f));
   stop.setPosition(0,0);
   stop.setFillColor(sf::Color(255,255,255, 100));
   backr.setSize(sf::Vector2f(100,50));
   backt = title;
   backr.setPosition(0,40);
   backr.setFillColor(sf::Color(255,255,255, 100));
   backt.setPosition(backr.getPosition().x,backr.getPosition().y);
   backt.setString("MAIN");
   backb.get(w,backr.getPosition().x,backr.getPosition().y,backr.getSize().x,backr.getSize().y,true);
   temp.get(t);
   Ab.get(t);
//   books.get(t,0);
    f.get(t);
   h.get(t);
}
Window::Window(sf::RenderTarget *a):t(a)
{
 Rs = 0;
 init();
}
void Window::Play()
{
  while(w->isOpen())
  {
   w->setFramerateLimit(30);
    while(w->pollEvent(e))
    {
     if(e.type == sf::Event::Closed)
     {
      w->close();
      exit(0);
     }
      input();
      Draggable();
      while(!w->hasFocus()){while(w->pollEvent(e)){}}
    }
     w->clear(sf::Color::Black);
     Render();
     w->display();
  }
}
