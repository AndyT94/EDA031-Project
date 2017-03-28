#ifndef NEWSGROUP_H
#define NEWSGROUP_H
#include <map>
#include <string>

class NewsGroup {
public:
  NewsGroup(int &id, string const name,std::std::map<int,Article> m);
  std::int get_newsgroupId();
  std::vector<Article> get_articles();
  std::Article get_article(int &article_id const);
  std:: string get_name();
  std::void delete_article(int &article_id const);
  std::int get_size();

private:
  std::map<int,Article> map;
  int id;
  string const name;


};

#endif
