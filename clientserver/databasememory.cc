#include "protocol.h"
#include "article.h"
#include "newsgroup.h"
#include "databasememory.h"
#include "nosuchelementexception.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

DatabaseMemory::DatabaseMemory() : newest_group(1) {}

vector<NewsGroup> DatabaseMemory::list_newsgroups() const {
  vector<NewsGroup> result;
  for(auto it = groups.begin(); it != groups.end(); ++it) {
    result.push_back(it->second);
  }
  sort(result.begin(), result.end(), [](NewsGroup& lhs, NewsGroup& rhs) {
    return lhs.get_newsgroupId() < rhs.get_newsgroupId();
  });
  return result;
}

bool DatabaseMemory::create_newsgroup(const string& name) {
  for (auto it = groups.begin(); it != groups.end(); ++it) {
    if (it->second == name) {
      return false;
    }
  }
  NewsGroup n(newest_group, name);
  groups.insert(make_pair(newest_group, n));
  ++newest_group;
  return true;
}

bool DatabaseMemory::delete_newsgroup(int group_id) {
  auto it = groups.find(group_id);
  if (it != groups.end()) {
    groups.erase(it);
    return true;
  }
  return false;
}

vector<Article> DatabaseMemory::list_articles(int group_id) {
  return groups[group_id].get_articles();
}

bool DatabaseMemory::create_article(int group_id, string& title, string& author, string& text) {
  if (groups.count(group_id) == 0) {
    return false;
  }
  groups[group_id].create_article(title, author, text);
  return true;
}

void DatabaseMemory::delete_article(int group_id, int article_id) {
  groups[group_id].delete_article(article_id);
}

Article DatabaseMemory::get_article(int group_id, int article_id) {
   return groups[group_id].get_article(article_id);
}

bool DatabaseMemory::hasGroup(int group_id) {
  return group.count(group_id) != 0;
}
