#include "newsgroup.h"
#include <string>
#include <map>

using namespace std;

NewsGroup::NewsGroup(int &id,string const name,map<int,Article> m ): id(id),map(m), name(name) {}

int NewsGroup::get_newsgroupId(){
  return id;
}

int NewsGroup::get_size(){
  return map.size();
}

string NewsGroup::get_name(){
  return name;
}

Article NewsGroup::get_article(int &article_id const){
  map<int,Article>:: iterator p;

  p = map.find(article_id);
  if(p != map.end()){
    return p->second;
  }
  return null;

}
void NewsGroup::delete_article(int &id,int &article_id const){

}


}
