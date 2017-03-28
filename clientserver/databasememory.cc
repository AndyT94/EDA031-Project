#include "databasememory.h"
#include "protocol.h"
#include "article.h"
#include <string>
#include <vector>

using namespace std;

DatabaseMemory::DatabaseMemory() : newest_group(1) {}

vector<Newsgroup> DatabaseMemory::list_newsgroups() const override {
  vector<Newsgroup> result;
  for(auto it = groups.begin(); it != groups.end(); ++it) {
    result.push_back(it->second);
  }
  sort(result.begin(), result.end(), [](const Newsgroup& lhs, const Newsgroup& rhs) {
    return lhs.get_newsgroupId() < rhs.get_newsgroupId();
  });
  return result;
}

void DatabaseMemory::create_newsgroup(const string& name) override {
  Newsgroup n(newest_group, name);
  groups.insert(make_pair(newest_group, n));
  ++newest_group;
}

void DatabaseMemory::delete_newsgroup(int& group_id) override {
  groups.erase(group_id);
}

vector<Article> DatabaseMemory::list_articles(int& group_id) const override {
  groups[group_id].getArticles();
}

void DatabaseMemory::create_article(int& group_id, string& title, string& author, string& text) override {
  groups[group_id].create_article(title, author, text);
}

void DatabaseMemory::delete_article(int& group_id, int& article_id) override {
  groups[group_id].delete_article(article_id);
}

Article DatabaseMemory::get_article(int& group_id, int& article_id) const override {
   return groups[group_id].get_article(article_id);
}
