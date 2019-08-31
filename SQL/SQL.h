#include "sqlite3.h"                //TRC2014011144A
#include <map>
#include <sstream>
std::map<std::string,std::string> datas;
std::vector< std::map<std::string,std::string> > vmap;
std::vector< std::vector<std::string > > dd;
std::vector< std::vector<std::string > > getselect(char**,char**,int);
std::vector< std::vector<std::string > > getselectu(char**,char**,int);
std::vector< std::vector< std::string> > getselectr(char**,char**,int);
int n;
static int uco = 0,bco = 0;
class books
{
 public:
 std::string acode,bname,aname,issue_status,issue_date,loca;
 books(){}
 books(std::string a,std::string b,std::string c,std::string d,std::string e,std::string f):acode(a),bname(b),aname(c),issue_status(d),issue_date(e),loca(f){}
};
class users
{
  public :
 std::string userid,name;
 char admin_status;
 users(){}
 users(std::string u,std::string n,char as):userid(u),name(n),admin_status(as)
 {}
};
int callback( void *data,int ncol,char** dcol,char** col)
{
  std::string ty = (const char *)data;
  for(int i=0;i<ncol;i++)
  datas.insert(std::pair<std::string,std::string>(col[i],dcol[i]));
   vmap.push_back(datas);
   if(ty =="user")
    uco++;
   if(ty =="book")
   bco++;
     if(ty == "cal")
      {
        std::stringstream e;
        e << (datas.begin()->second);
        e >> n;
      }
    if(ty == "rbooks")
    dd = getselectu(col,dcol,ncol);
    if(ty == "logins")
    {
     dd = getselectu(col,dcol,ncol);
    }
    if(ty == "books")
    dd = getselect(col,dcol,ncol);
    datas.clear();
  return 0;
}
std::once_flag flag,flag1;
std::vector< std::vector< std::string> > getselect(char** head,char** data,int nc)
{
 static std::vector<std::string> sheads,sdatas;
 std::call_once(flag,[&]{
        for(int i = 0;i < nc;i++)
              {
              sheads.push_back(head[i]);
              }
              });
 for(int i = 0;data[i]!= NULL;i++)
      sdatas.push_back(data[i]);
 if(sdatas.size() > n*sheads.size())
 sdatas.resize(n*sheads.size());
 std::vector<std::vector<std::string> > temp;
 temp.push_back(sheads);
 temp.push_back(sdatas);
 std::cout<<std::endl<<sheads.size()<<std::endl<<sdatas.size()<<std::endl;
 return temp;
}
std::vector< std::vector< std::string> > getselectu(char** head,char** data,int nc)
{
 static std::vector<std::string> shead,sdata;
 std::call_once(flag1,[&]{
        for(int i = 0;i < nc;i++)
              {
              shead.push_back(head[i]);
              }
              });
 for(int i = 0;data[i]!= NULL;i++)
      sdata.push_back(data[i]);
 if(sdata.size() > n*shead.size())
 sdata.resize(n*shead.size());
 std::vector<std::vector<std::string> > temp;
 temp.push_back(shead);
 temp.push_back(sdata);
 std::cout<<std::endl<<shead.size()<<std::endl<<sdata.size()<<std::endl;
 return temp;
}
std::vector< std::vector< std::string> > getselectr(char** head,char** data,int nc)
{
 static std::vector<std::string> rhead,rdata;
 std::call_once(flag1,[&]{
        for(int i = 0;i < nc;i++)
              {
              rhead.push_back(head[i]);
              }
              });
 for(int i = 0;data[i]!= NULL;i++)
      rdata.push_back(data[i]);
 if(rdata.size() > n*rhead.size())
 rdata.resize(n*rhead.size());
 std::vector<std::vector<std::string> > temp;
 temp.push_back(rhead);
 temp.push_back(rdata);
 return temp;
}
char* run(std::string q,std::string ty = "No")
{
  char *errmsg;
  sqlite3 *db;
  sqlite3_open("SQL/LMSDB.db",&db);
  sqlite3_exec(db,q.c_str(),callback,const_cast<char*>(ty.c_str()),&errmsg);
  sqlite3_close(db);
  return errmsg;
}
void qcount(std::string cond,int type)
{
 switch(type)
 {
  case 0:{
           run("select count(userid) from login" + cond,"cal");
         }
  break;
  case 1:{
           run("select count(acode) from book" + cond,"cal");
         }
 }
}
void insertuser(std::vector<std::string> datau)
{
 std::string query = "insert into login(userid,name,pass,admin_status,des,bp) values(",temp = "";
 for(int i = 0;i < datau.size();i++)
  temp += "\"" + datau[i] + "\",";
 temp += "10)";
 query += temp;
 run(query);
}
void insertbook(std::vector<std::string> datab)
{
 std::string query = "insert into book(acode,name,Aname,issue_status,issue_date,LOCATION) values(",temp = "";
 for(int i = 0;i < datab.size() - 3;i++)
 {
  temp += "\"" + datab[i] + "\",";
 }
  temp += "No,00-00-0000,\"" + datab[datab.size() - 1] + "\")";
  query += temp;
 run(query);
}
void selection(std::string q,std::string cond = "",int table  = 1)
{
 std::cout<<"check:"<<table;
 switch(table)
 {
  case 0:{

            dd.clear();
            qcount(cond,table);
            run(q + cond,"logins");
         }
   break;
   case 1:{
            dd.clear();
            qcount(cond,table);
            run(q+ cond,"books");
          }
   break;
   case 2:{
            dd.clear();
            qcount(cond,1);
            run(q+ cond,"rbooks");
          }
 }
}
bool issue_book(std::string ac,std::string euserid)
{
     run("update book set issue_status = \"" + euserid + "\"where acode = " + ac);
     return true;
}
bool returnbook(std::string ac,std::string euserid)
{
 run("update book set issue_status = \"No\",issue_date = \"00-00-0000\" where acode = " + ac);
 return true;
}
