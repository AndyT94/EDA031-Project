#ifndef NEWSGROUP_H
#define NEWSGROUP_H

class NewsGroups {
public:
  NewsGroups(int &id, std::std::map<int, Article>);
  std::int getId();
  std::vector<Article> getArticles();
  std:: String getName();


}
