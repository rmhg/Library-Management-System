struct currentuser
{
 std::string name,userid,des;
 char admin_status;
 bool check;
};
class Login
{
  std::string euserid,epass,pass,userid,name;
  char admin_status;
  sf::RenderTarget *t;
  bool found;
  public :
  Form f;
  currentuser ue;
  Login();
  Login(sf::RenderTarget*);
  bool loginstatus;
  void init();
  void Render();
  currentuser datato();
  void checklogin();
  void FormFunc(char);
  void getdata();
  void get(sf::RenderTarget*);
  void Reset();
  void Resize();
};
Login::Login()
{

}
void Login::Reset()
{
 loginstatus = false;
 euserid = "";
 epass = "";
 found = false;
 f.data[1] = "";
}
void Login::Resize()
{
 f.Resize();
}
void Login::get(sf::RenderTarget *w)
{
 t = w;
 f.get(t,1);
 f.Formty(0);
 loginstatus = false;
 pass = "";
 userid = "";
 run("select * from login","user");
}
void Login::checklogin()
{
 if(!found)
  init();
 if(euserid == userid && epass == pass)
 {
    loginstatus = true;
 }
  else
   loginstatus = false;
}
Login::Login(sf::RenderTarget* w):t(w)
{
 f.get(t,1);
 loginstatus = false;
 pass = "";
 userid = "";
 run("select * from login","user");
}
void Login::init()
{

  int pos = 0;
  //getdata from database
  for(int i = 0;(i < uco); i++)
  {
   userid = (vmap[i].find("userid")->second);
   pass = (vmap[i].find("pass")->second);
   if(euserid == userid)
    {
     pos = i;
     found = true;
     break;
    }
   }
   name = (vmap[pos].find("name")->second);
   admin_status = *(vmap[pos].find("admin_status")->second).c_str();
}
void Login::Render()
{
 getdata();
 f.Render();
}
void Login::getdata()
{
   temps u = extract(f);
   euserid = (u.a)[0];
   epass = u.a[1];
   if(f.button.click.Clicked())
     checklogin();
}
currentuser Login::datato()
{
  currentuser temp;
  if(loginstatus)
   {
     temp.name = name;
     temp.userid = userid;
     temp.admin_status = admin_status;
     temp.check = true;
   }
   else
   temp.check = false;
   return temp;
}
void Login::FormFunc(char is)
{
 f.inputdata(is);
}
