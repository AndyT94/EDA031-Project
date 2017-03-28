#ifndef DATABASEMEMORY_H
#define DATABASEMEMORY_H

#include <string>
#include <vector>
#include <map>
#include "article.h"

class DatabaseMemory {
public:
  DatabaseMemory();
  std::vector<Newsgroup> list_newsgroups() const override;
  void create_newsgroup(const std::string& name) override;
  void delete_newsgroup(int& group_id) override;
  std::vector<Article> list_articles(int& group_id) const override;
  void create_article(int& group_id, std::string& title, std::string& author, std::string& text) override;
  void delete_article(int& group_id, int& article_id) override;
  Article get_article(int& group_id, int& article_id) const override;
private:
  int newest_group;
  map<int, Newsgroup> groups;
};

#endif
