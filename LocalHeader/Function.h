struct dat
{
  std::string name,userid,des;
  char admin_status;
};
class Function
{
 sf::RenderTarget* t;
 Table T;
 std::vector<std::string> dt;
 std::string query,tdate;
 public :
 dat det;
 std::once_flag af,bf,cf,df,ef,rf;
 bool inputs;
 Form f;
 Function(){inputs = false;}
 void get(sf::RenderTarget*);
 void init();
 void getdata();
 void input(char);
 void Run();
 void findbook();
 void retbook();
 void remuser();
 void addbook();
 void adduser();
 void rembook();
 void showusers();
 void showbooks();
 void issue_book();
 void Render();
};
void Function::issue_book()
{
  std::stringstream a;
  time_t now = time(0);
  tm *ltm = localtime(&now);
   a << ltm->tm_mday;
   a << "/";
   a << ltm->tm_mon;
   a << "/";
   a << (ltm->tm_year) + 1900;// + "/" + (std::string)ltm->tm_mon + "/" + (std::string)ltm->tm_mday;
   tdate = a.str();
   query = "update book set issue_status = \""+ det.userid +"\",issue_date = \""+tdate+"\" where acode = ";
   std::cout<<query;
}
void Function::Render()
{
 f.Render();
}
void Function::Run()
{
 std::cout<<run(query);
 query = "";
}
void Function::get(sf::RenderTarget* a)
{
 t = a;
 f.get(t);
}
void Function::input(char is)
{
  f.inputdata(is);
}
void Function::findbook()
{

   inputs = true;
  std::call_once ( af, [&]{ f.Change(4); }) ;
  if(f.button.click.Clicked())
  {
   ::issue_book(f.data[0],det.userid);
   inputs = false;
  }
}
void Function::retbook()
{
 selection("select acode,bname,Aname,LOCATION from book"," where issue_status = \"" + det.userid + "\"",2);
 if(dd.size())
 {
  T.get(t,dd[0],dd[1],200,100);
  T.Render();
 }
 inputs = true;
 std::call_once ( rf, [&]{ f.Change(6); }) ;
  query = "update book set issue_status = \"No\" where acode = \"" + f.data[0] +"\"";
  if(f.button.click.Clicked())
  {
   inputs = false;
   Run();
  }
}
void Function::rembook()
{
    inputs = true;
    std::call_once ( bf, [&]{ f.Change(1); }) ;
  query = "delete from book where acode =";
  query += f.data[0];
  if(f.button.click.Clicked())
  {
   Run();
   inputs = false;
  }
}
void Function::addbook()
{
  std::string temp;
  char a = ')';
  inputs = true;
  std::call_once ( cf, [&]{ f.Change(2); }) ;
  query = "insert into book(acode,bname,Aname,issue_status,issue_date,LOCATION) values(";
  if(f.button.click.Clicked())
  {
   inputs = false;
   temp += f.data[0] + ",";
   for(int i = 1;i < f.data.size() - 1;i++)
   temp += "\""+f.data[i] + "\"" + ",";
   temp += "\"No\",00-00-0000,";
   temp += "\""+f.data[f.data.size()-1]+"\",";
   temp = temp.substr(0,temp.size()-1);
   temp.push_back(a);
   query += temp;
   //std::cout<<query;
    Run();
  }
}
void Function::adduser()
{
 std::string temp;
  char a = ')';
  inputs = true;
  std::call_once ( df, [&]{ f.Change(3); }) ;
  query = "insert into login(userid,name,pass,admin_status,des,bp) values(";
  if(f.button.click.Clicked())
  {
   inputs = false;
   for(int i = 0;i < f.data.size();i++)
   temp += "\""+f.data[i] + "\"" + ",";
   temp += "10,";
   temp = temp.substr(0,temp.size()-1);
   temp.push_back(a);
   query += temp;
   Run();
  }
}
void Function::remuser()
{

  inputs = true;
   std::call_once ( ef, [&]{ f.Change(1); }) ;
  query = "delete from login where userid =";
  if(f.button.click.Clicked())
  {
   query += "\"" + f.data[0] + "\"";
   Run();
   inputs = false;
  }
}
void Function::showusers()
{
 selection("select * from login","",0);
 T.get(t,dd[0],dd[1]);
 T.Render();
}
void Function::showbooks()
{
 selection("select acode,bname,Aname,LOCATION from book"," where issue_status = \"No\"",1); //space i
 T.get(t,dd[0],dd[1]);
 T.Render();
}
