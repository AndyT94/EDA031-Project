#ifndef DATABASEFILE_H
#define DATABASEFILE_H

#include <string>
#include <vector>
#include <map>
#include "article.h"
#include "newsgroup.h"
#include "database.h"

class DatabaseFile : public Database {
public:
  DatabaseFile();
  std::vector<NewsGroup> list_newsgroups() const override;
  bool create_newsgroup(const std::string& name) override;
  bool delete_newsgroup(int group_id) override;
  std::vector<Article> list_articles(int group_id) override;
  bool create_article(int group_id, std::string& title, std::string& author, std::string& text) override;
  void delete_article(int group_id, int article_id) override;
  Article get_article(int group_id, int article_id) override;
  bool hasGroup(int group_id) override;
private:
  int newest_group;
  std::map<int, NewsGroup> groups;
  std::string db;
  void load(const std::string& filename);
  void save();
};

#endif
