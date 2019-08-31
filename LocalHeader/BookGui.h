class TableGui
{
 sf::RenderTarget *t;
 std::vector<std::string> heads,vals;
 Table table;
 std::string q;
 int type;
 public:
 TableGui();
 void get(sf::RenderTarget*,int);
 void init();
 void setPosition(int x,int y);
 void Render();
 void Refresh();
};
TableGui::TableGui()
{
 type = 0;
}
void TableGui::setPosition(int x,int y)
{
 table.setPosition(x,y);
}
void TableGui::Refresh()
{
 std::cout<<std::endl<<type<<"swwwwwwwwwwww"<<std::endl;
 switch(type)
 {
  case 0:{
          selection("select * from book","",1);
           heads = dd[0];
           vals = dd[1];
        }
 break;
 case 1:{
          selection("select * from login",0);
           heads = dd[0];
           vals = dd[1];
         }
 }
 table.get(t,heads,vals);
}
void TableGui::get(sf::RenderTarget* a,int ty = 0)
{
  t = a;
  type = ty;
  std::cout<<std::endl<<ty<<"dsssdddddd"<<std::endl<<"called\n";
  init();
}
void TableGui::init()
{
 std::cout<<"qqqqqqqqqqq";
 std::string h;
 switch(type)
 {
  case 0:{
           selection("select * from book","",1);
           heads = dd[0];
           vals = dd[1];
         }
  break;
  case 1:{
           selection("select * from login","",0);
           heads = dd[0];
           vals = dd[1];
           std::cout<<vals.size();
           std::cout<<std::endl<<type<<std::endl;
         }
 }
 table.get(t,heads,vals);
}
void TableGui::Render()
{
 table.Render();
 std::cout<<std::endl<<type<<std::endl;
}
