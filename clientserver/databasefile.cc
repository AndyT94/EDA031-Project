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
    while (getline(file,line)) {
      istringstream iss(line);
      string object;
      iss >> object;
      if (object == "GROUP") {
        string name;
        iss >> name;
        create_newsgroup(name);
      } else if (object == "ART") {
        int group_id;
        iss >> group_id;
        string title;
        iss >> title;
        string author;
        iss >> author;
        string text = "";
        string word;
        while(iss >> word) {
          text += word;
        }
        create_article(group_id, title, author, text);
      }
    }
    file.close();
  }
}

void DatabaseFile::save() {
  ofstream file(db);
  if (file.is_open()) {
    for (auto it = groups.begin(); it != groups.end(); ++it) {
      file << "GROUP " << it->second.get_name() << endl;
      vector<Article> articles = it->second.get_articles();
      for (auto a_it = articles.begin(); a_it != articles.end(); ++a_it) {
        file << "ART " << a_it->get_id() << " " << a_it->get_title() << " " << a_it->get_author() << " " << a_it->get_text() << endl;
      }
    }
  }
}
