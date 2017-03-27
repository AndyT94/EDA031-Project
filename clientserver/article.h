#ifndef ARTICLE_H
#define ARTICLE_H

#include <string>

class Article {
public:
  Article(const std::string& ti, const std::string& au, const std::string& te, int& i);
  std::string get_title();
  std::string get_author();
  std::string get_text();
  int get_id();
private:
  std::string title;
  std::string author;
  std::string text;
  int id;
}

#endif
