#ifndef DATABASE_H
#define DATABASE_H

class Database {
public:
  virtual std::vector<Newsgroup> list_newsgroups() const = 0;
  virtual void create_newsgroup(const std::string& name) = 0;
  virtual void delete_newsgroup(int& group_id) = 0;
  virtual std::vector<Article> list_articles(int& group_id) const = 0;
  virtual void create_article(int& group_id, std::string& title, std::string& author, std::string& text) = 0;
  virtual void delete_article(int& group_id, int& article_id) = 0;
  virtual Article get_article(int& group_id, int& article_id) const = 0;
};

#endif
