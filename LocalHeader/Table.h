struct block
{
 sf::RectangleShape rblock;
 sf::Text tblock;
 int x,y,w,h;
 public :
 void init(sf::Font*);
};
void block::init(sf::Font* font)
{
 tblock.setFont(*font);
 tblock.setPosition(x,y);
 rblock.setPosition(x,y);
 //rblock.setSize(sf::Vector2f(w,h));
 rblock.setFillColor(sf::Color(255,255,255,100));
}
class Table
{
 sf::RenderTarget *t;
 sf::Font font;
 std::vector<block> vblock;
 std::vector<std::string> head,vals;
 int ncol,nrow;
 int x,y;
 public :
 Table();
 void init();
 void Render();
 void setPosition(int xx,int yy);
 void adj(int);
 void get(sf::RenderTarget* a,std::vector<std::string>,std::vector<std::string>,int,int);
};
void Table::adj(int ai)
{
 float max = 0;
 std::vector<float> temp;
 for(int i = ai; i < vblock.size();i+=ncol)
   temp.push_back(vblock[i].tblock.getGlobalBounds().width);
 for(int i = 0;i < temp.size();i++)
    if(max < temp[i])
     max = temp[i];
 for(int i = ai; i < vblock.size();i+=ncol)
  vblock[i].rblock.setSize(sf::Vector2f(max + 10,60));
}
Table::Table()
{
  font.loadFromFile("data/sans.ttf");

}
void Table::setPosition(int xx,int yy)
{
 x = xx;
 y = yy;
}
void Table::get(sf::RenderTarget* a,std::vector<std::string> he,std::vector<std::string> v,int xx = 200,int yy = 100)
{
 t = a;
 head = he;
 vals = v;
 x  = xx;
 y = yy;
 init();
}
void Table::init()
{
  int c = 0,s = 0;
  ncol = head.size();
  nrow = vals.size()/ncol;
  vblock.resize(head.size() + vals.size());
  for(int i = 0;i < vblock.size();i++)
   vblock[i].init(&font);
  for(int i = 0;i < head.size();i++)
   vblock[i].tblock.setString(head[i]);
  for(int i = head.size();i < vblock.size();i++)
   vblock[i].tblock.setString(vals[i - (head.size())]);
  for(int i = 0;i<ncol;i++)
       adj(i);
  for(int i = 0;i < vblock.size();i++)
  {
   vblock[i].h = 40 + 20;
   if(i%ncol == 0)
    s = 0;
   else
    s += vblock[i%ncol - 1].rblock.getSize().x;
   vblock[i].x = x + s;
   vblock[i].y = y + (i/ncol)*(40 + 20);
   vblock[i].init(&font);
  }
}
void Table::Render()
{
  for(int i = 0;i < vblock.size();i++)
  {
   t->draw(vblock[i].rblock);
   t->draw(vblock[i].tblock);
  }
}
