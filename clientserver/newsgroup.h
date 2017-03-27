#ifndef NEWSGROUP_H
#define NEWSGROUP_H

#include <string>

class NewsGroup {
public:
  NewsGroup(int &id, std::std::map<int, vector<Article>> m);
  std::int getNewsGroupId();
  std::vector<Article> getArticles(int &newsgroup_id);
  std::Article getAtricle(int &newsgroup_id const,int &article_id const)
  std:: String getName();
  std::void deleteArticle();
  std::int getSize();

private:
  std::map<int, vector<Article> map;
  int id;


}
