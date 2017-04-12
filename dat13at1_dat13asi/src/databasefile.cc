#include "article.h"
#include "newsgroup.h"
#include "databasefile.h"
#include "nosuchelementexception.h"
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

DatabaseFile::DatabaseFile() {
  newest_group = 1;
  db = "newsdb.txt";
  load(db);
}

vector<NewsGroup> DatabaseFile::list_newsgroups() const {
  vector<NewsGroup> result;
  for(auto it = groups.begin(); it != groups.end(); ++it) {
    result.push_back(it->second);
  }
  sort(result.begin(), result.end(), [](NewsGroup& lhs, NewsGroup& rhs) {
    return lhs.get_newsgroupId() < rhs.get_newsgroupId();
  });
  return result;
}

bool DatabaseFile::create_newsgroup(const string& name) {
  for (auto it = groups.begin(); it != groups.end(); ++it) {
    if (it->second.get_name() == name) {
      return false;
    }
  }
  NewsGroup n(newest_group, name);
  groups.insert(make_pair(newest_group, n));
  ++newest_group;
  vector<NewsGroup> r = list_newsgroups();
  for (auto it = r.begin(); it != r.end(); ++it) {
    cout << it->get_name() << endl;
  }
  save();

  return true;
}

bool DatabaseFile::delete_newsgroup(int group_id) {
  auto it = groups.find(group_id);
  if (it != groups.end()) {
    groups.erase(it);
    save();
    return true;
  }
  return false;
}

vector<Article> DatabaseFile::list_articles(int group_id) {
  return groups[group_id].get_articles();
}

bool DatabaseFile::create_article(int group_id, string& title, string& author, string& text) {
  if (groups.count(group_id) == 0) {
    return false;
  }
  groups[group_id].create_article(title, author, text);
  save();
  return true;
}

void DatabaseFile::delete_article(int group_id, int article_id) {
  groups[group_id].delete_article(article_id);
  save();
}

Article DatabaseFile::get_article(int group_id, int article_id) {
   return groups[group_id].get_article(article_id);
}

bool DatabaseFile::hasGroup(int group_id) {
  return groups.count(group_id) != 0;
}

void DatabaseFile::load(const string& filename) {
  string line;
  ifstream file(filename);
  if (file.is_open()) {
    string dbtext;
    while(getline(file, line)) {
      dbtext += line + "\n";
    }
    istringstream iss(dbtext);
    string word;
    int count = 0;
    while(getline(iss, word, '$')) {
      ++count;
      if (word == "GROUP") {
          int group_id;
          string id;
          getline(iss, id, '$');
          istringstream ss(id);
          ss >> group_id;
          string name;
          getline(iss, name, '$');
          NewsGroup n(group_id, name);
          groups.insert(make_pair(group_id, n));
          newest_group = max(newest_group, group_id);
        } else if (word == "ART") {
          int group_id;
          string id;
          getline(iss, id, '$');
          istringstream ss(id);
          ss >> group_id;
          string title;
          getline(iss, title, '$');
          string author;
          getline(iss, author, '$');
          string text;
          getline(iss, text, '$');
          groups[group_id].create_article(title, author, text);
        }
    }
    create_newsgroup(""); // First create_newsgroup does not register
    file.clear();
    file.close();
  }
}

void DatabaseFile::save() {
  ofstream file(db);
  if (file.is_open()) {
    cout << "OPENED" << endl;
    for (auto it = groups.begin(); it != groups.end(); ++it) {
      file << "$GROUP$" << it->second.get_newsgroupId() << "$" << it->second.get_name() << "$" <<endl;
      vector<Article> articles = it->second.get_articles();
      for (auto a_it = articles.begin(); a_it != articles.end(); ++a_it) {
        file << "$ART$" << it->second.get_newsgroupId() << "$" << a_it->get_title() << "$" << a_it->get_author() << "$" << a_it->get_text() << "$" << endl;
      }
    }
  }
}
