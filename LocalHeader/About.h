class About
{
  sf::RenderTarget *t;
  sf::Font font;
  sf::Text title,Text;
  int x,y;
  public :
  About(){}
  About(sf::RenderTarget*);
  void get(sf::RenderTarget* ewin);
  void init();
  void Render();
};
void About::get(sf::RenderTarget* ewin)
{
 t = ewin;
 init();
}
void About::init()
{
  font.loadFromFile(FONT);
  title.setFont(font);
  title.setString("ABOUT");
  title.setPosition(t->getSize().x/2 - title.getGlobalBounds().width/2,40);
}
void About::Render()
{
 t->draw(title);
}
