class Content
{
 sf::RectangleShape rect;
 sf::RenderTarget* t;
 sf::RenderWindow *window;
 sf::Color hColor,nColor;
 sf::Text text;
 sf::Font font;
 bool button;
 std::string textstr;
 int w,h;
 public:
 bool hover();
 int Change;
 Content();
 Content(int x ,int y,sf::RenderTarget *a,std::string,int,int,bool,sf::Color,sf::Color);
 void init();
 void ColorMech();
 int onClick();
 void gettext(std::string);
 void get(int x ,int y,sf::RenderTarget *a,std::string,int,int,bool,sf::Color,sf::Color);
 void Render();
};
void Content::init()
{
}
void Content::ColorMech()
{
 if(hover())
   rect.setFillColor(hColor);
  else
    rect.setFillColor(nColor);
}
bool Content::hover()
{
 window = (dynamic_cast<sf::RenderWindow*>(t));
  if(button)
     if(sf::Mouse::getPosition(*window).x > rect.getPosition().x && sf::Mouse::getPosition(*window).x < (rect.getPosition().x + rect.getSize().x) && sf::Mouse::getPosition((*window)).y > rect.getPosition().y && sf::Mouse::getPosition(*window).y < (rect.getPosition().y + rect.getSize().y))
        return true;
   return false;
}
int Content::onClick()
{

  if(button)
     if(hover())
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
         // snd.play();
          return 1;
        }
        return 0;
}
Content::Content()
{
 this->Change = 0;
 init();
}
void Content::get(int x ,int y,sf::RenderTarget *a,std::string str,int ew,int eh,bool click = false,sf::Color n=sf::Color::White,sf::Color hc = sf::Color::Blue)
{
  init();
  this->w = ew;
  this->h = eh;
  this->t = a;
  this->nColor = n;
  this->hColor = hc;
  this->rect.setFillColor(nColor);
  this->textstr = str;
  this->rect.setSize(sf::Vector2f(w,h));
  this->rect.setFillColor(sf::Color::White);
  this->rect.setPosition(sf::Vector2f(x,y));
  this->text.setFillColor(sf::Color::Black);
  this->font.loadFromFile("data/sans.ttf");
  this->text.setString(this->textstr);
  this->text.setPosition(this->rect.getPosition().x,this->rect.getPosition().y);
  this->text.setFont(this->font);
  this->button = click;
  this->Change = 0;
}
Content::Content(int x ,int y,sf::RenderTarget *a,std::string str,int ew,int eh,bool click = false,sf::Color n=sf::Color::White,sf::Color hc = sf::Color::Blue)
{
 init();
 this->w = ew;
 this->h = eh;
 this->t = a;
 this->nColor = n;
 this->hColor = hc;
 this->rect.setFillColor(nColor);
 this->rect.setSize(sf::Vector2f(100,100));
 this->rect.setPosition(sf::Vector2f(x,y));
 this->text.setFont(font);
 this->text.setFillColor(sf::Color::Black);
 this->font.loadFromFile("data/sans.ttf");
 this->text.setString(str);
 this->text.setPosition(x,y);
 this->button = click;
 text.setFont(this->font);
}
void Content::gettext(std::string a)
{
 text.setString(a);
}
void Content::Render()
{
   ColorMech();
   Change = onClick();
   t->draw(this->rect);
   this->text.setFont(this->font);
   t->draw(this->text);
}
