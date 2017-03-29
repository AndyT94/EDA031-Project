#include "newsgroup.h"
#include "article.h"
#include "nosucharticleexception.h"
#include <string>
#include <map>
#include <vector>
#include <cstddef>

using namespace std;

NewsGroup::NewsGroup() {}

NewsGroup::NewsGroup(int i, const string& n): id(i), name(n), counter(0) {}

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
  if(it == map.end()){
    throw NoSuchArticleException();
  }
  return it->second;
}

void NewsGroup::delete_article(int article_id){
  auto it = map.find(article_id);
  if(it == map.end()){
    throw NoSuchArticleException();
  }
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
