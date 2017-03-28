#include "newsgroup.h"
#include "article.h"
#include <string>
#include <map>
#include <vector>
#include <cstddef>

using namespace std;

NewsGroup::NewsGroup(int id, const string& name): id(id), name(name) {}

int NewsGroup::get_newsgroupId(){
  return id;
}

int NewsGroup::get_size(){
  return map.size();
}

string NewsGroup::get_name(){
  return name;
}

Article& NewsGroup::get_article(int article_id){
  auto it = map.find(article_id);
  if(it != map.end()){
    return it->second;
  }
  return NULL;
}

void NewsGroup::delete_article(int article_id){
      map.erase(article_id);
}

vector<Article> NewsGroup::get_articles(){
  vector<Article> articles;
  for (auto it = map.begin(); it != map.end(); ++it){
    articles.push_back(it->second);
  }
  return articles;
}

void NewsGroup::create_article(string &title,string& author, string& text){
  Article a(title,author,text,counter++);
  map.insert(make_pair(counter,a));
}
