class FormGui
{
 sf::RenderTarget *t;
 std::vector<sf::RectangleShape> textblock;
 sf::RectangleShape box;
 sf::Text text;
 std::vector<bool> selected;
 public :
 void setlook();
 void Render();
};
void FormGui::setlook()
{
 for(int i = 0;i < textblock.size();i++)
 {
  textblock[i].setSize(sf::Vector2f(100.f,30.f));
 }
 box.setSize(sf::Vector2f(120.f,t.size() * 30.f + (t.size() + 1)*10.f));
}
void Render()
{
 for(int i = 0;i < textblock.size();i++)
 {
  t->draw(textblock[i]);
 }
}



