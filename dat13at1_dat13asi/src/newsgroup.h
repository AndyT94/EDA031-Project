#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include "article.h"
#include <map>
#include <string>
#include <vector>

class NewsGroup {
public:
  NewsGroup();
  NewsGroup(int id, const std::string& name);
  int get_newsgroupId();
  std::vector<Article> get_articles();
  Article& get_article(int article_id);
  std::string get_name();
  void delete_article(int article_id);
  int get_size();
  void create_article(std::string &title, std::string &author, std::string &text);

private:
  std::map<int, Article> map;
  int id;
  std::string name;
  int counter;
};

#endif
