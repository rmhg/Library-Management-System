struct temps
{
 std::vector<std::string> a;
};
struct Submit
{
 sf::Text text;
 sf::RectangleShape rect;
 Clickable click;
 void setPosition(int,int);
 void init(sf::RenderTarget *t,sf::Font *font,int xx,int yy,int ww,int hh);
 void heff();
};
void Submit::setPosition(int xx,int yy)
{
  rect.setPosition(xx,yy);
  text.setPosition(rect.getPosition().x,rect.getPosition().y);
  click.setPosition(rect.getPosition().x,rect.getPosition().y);
}
void Submit::init(sf::RenderTarget *t,sf::Font *font,int xx,int yy,int ww,int hh)
{
 rect.setSize(sf::Vector2f(ww,hh));
 rect.setPosition(xx,yy);
 rect.setFillColor(sf::Color::Transparent);
 rect.setOutlineColor(sf::Color::Yellow);
 rect.setOutlineThickness(0);
 click.get(dynamic_cast<sf::RenderWindow*>(t),rect.getPosition().x,rect.getPosition().y,rect.getSize().x,rect.getSize().y);
 text.setFont(*font);
 text.setString("SUBMIT");
 text.setPosition(rect.getPosition().x,rect.getPosition().y);
}
void Submit::heff()
{
 if(click.Hover())
   rect.setOutlineThickness(0.6);
  else
   rect.setOutlineThickness(0);
}
class Form
{
 sf::RenderTarget *t;
 sf::RenderWindow *w;
 sf::Font font;
 sf::Text head;
 std::vector<sf::Text> rent;
 sf::RectangleShape dr;
 sf::RectangleShape rect;
 std::vector<std::string> data;
 std::vector<std::string> cdata;
 int size;
 int x,y;
 int type;
 int p;
 public :
 bool done;
 Submit button;
 Form();
 Form(sf::RenderTarget*);
 void get(sf::RenderTarget* a,int);
 void init();
 void inText();
 void inputdata(char);
 void Resize();
 void Formty(int ty);
 void Render();
 bool Change(int ty);
 friend class Login;
 friend temps extract(Form f);
 friend class Function;
 friend class Window;
};
temps extract(Form f)
{
  temps k;
  k.a = f.data;
  return k;
}
bool Form::Change(int ty)
{
 cdata.clear();
 data.clear();
 Formty(ty);
 inText();
 return true;
}
void Form::inText()
{
 for(int i = 0;i < data.size();i++)
   rent[i].setString(cdata[i] + data[i]);
}
Form::Form()
{
 p = 0;
 done  = false;
 font.loadFromFile("data/sans.ttf");
 head.setFillColor(sf::Color::Black);
 dr.setSize(sf::Vector2f(100,100));
 dr.setFillColor(sf::Color(255,255,255,100));
}
Form::Form(sf::RenderTarget* a):t(a)
{
}
void Form::Formty(int ty = 0)
{
  std::string temp,h;
  switch(ty)
  {
    case 0:{
             h = "LOGIN";
             temp = "USERID :";
             cdata.push_back(temp);
             temp = "PASSWORD :";
             cdata.push_back(temp);
             size = 2;
           }
    break;
    case 1:{
             h = "DELETION";
             temp = "ID :";
             cdata.push_back(temp);
             size = 1;
           }
    break;
    case 2:{
             h = "ADD BOOK";
             temp = "ACODE :";
             cdata.push_back(temp);
            temp = "BOOK NAME :";
             cdata.push_back(temp);
             temp = "AUTHOR NAME :";
             cdata.push_back(temp);
             temp = "LOCATION :";
             cdata.push_back(temp);
             size = 4;
           }
    break;
    case 3:{
             h = "ADD USER";
             temp = "USERID :";
             cdata.push_back(temp);
             temp = "NAME :";
             cdata.push_back(temp);
             temp = "PASSWORD :";
             cdata.push_back(temp);
             temp = "ADMIN_STATUS(Y/N) :";
             cdata.push_back(temp);
             temp = "DESIGNATION :";
             cdata.push_back(temp);
             size = 5;
           }
     break;
     case 4:{
             h = "ISSUE BOOK";
             temp = "ACODE :";
             cdata.push_back(temp);
             size = 1;
            }
     break;
     case 5:{
              h = "NEW USER";
              temp = "USERID :";
             cdata.push_back(temp);
             temp = "NAME :";
             cdata.push_back(temp);
             temp = "PASSWORD :";
             cdata.push_back(temp);
             temp = "ADMIN_STATUS(Y/N) :";
             cdata.push_back(temp);
             temp = "DESIGNATION :";
             cdata.push_back(temp);
             size = 5;
            }
    break;
    case 6:{
             h = "RETURN BOOK";
             temp = "ACODE :";
             cdata.push_back(temp);
             size = 1;
           }
  }
  head.setString(h);
  cdata.resize(size);
  data.resize(size);
  rent.resize(size);
  init();
}
void Form::get(sf::RenderTarget* a,int ty = 1)
{
 t = a;
 x = t->getSize().x/2 - 200;
 y = t->getSize().y/2 - 100;
 type = ty;
 init();
}
void Form::init()
{
  font.loadFromFile("data/sans.ttf");
  head.setFont(font);
  head.setPosition(t->getSize().x/2 - head.getGlobalBounds().width/2,80);
  dr.setPosition(x - 10,y - 10);
  for(int i = 0;i < data.size();i++)
  {
    rent[i].setFillColor(sf::Color::Black);
    rent[i].setFont(font);
    rent[i].setPosition(x + 10,y + rent[i].getCharacterSize()*i + 10);
  }
  w = dynamic_cast<sf::RenderWindow*>(t);
  button.init(t,&font,t->getSize().x - 200,t->getSize().y - 200,100,50);
  int s = 0;
  for(int i = 0; i < rent.size(); i++)
    s += rent[i].getCharacterSize();
  dr.setSize(sf::Vector2f(10,s + 20*rent.size() + 10));
}
void Form::inputdata(char is)
{
   switch(is)
   {
    case 13 :{
               if(p < data.size()-1)
                   p++;
             }
    break;
    case 8  :{
               if(data[p].empty()&&p>0)
                 p--;
               data[p] = data[p].substr(0,data[p].length()-1);
             }
    break;
    default :{

               data[p].push_back(is);
             }
    break;
   }
}
void Form::Resize()
{
 for(int i = 0;i < data.size();i++)
   rent[i].setPosition(x + 10,y + rent[i].getCharacterSize()*i + 10);
    head.setPosition(t->getSize().x/2 - 200,70);
}
void Form::Render()
{
  button.heff();
  if(button.click.Clicked())
   p = 0;
  dr.setSize(sf::Vector2f(rent[0].getGlobalBounds().width + 100,dr.getSize().y));
  t->draw(dr);
  t->draw(head);
  t->draw(button.rect);
  t->draw(button.text);
  inText();
  for(unsigned int i = 0; i < rent.size();i++)
     t->draw(rent[i]);
}
