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
void NewsGroup::delete_article(int &article_id const){
  for(auto it = map.begin(); it!= map.end(); ++it){
    if(*it->second.get_id() == article_id ){
      map.erase(*it);
    }
  }
}

vector<Article> NewsGroup get_articles(){
  vector<Article> articles;
  for (auto it = map.begin(); it != map.end();++it){
    articles.push_back(*it);
  }
  return articles;
}



}
