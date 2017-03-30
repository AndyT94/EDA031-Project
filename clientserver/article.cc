#include "article.h"
#include <string>

using namespace std;

Article::Article(const string& ti, const string& au, const string& te, int i) : title(ti), author(au), text(te), id(i) {}

string Article::get_title() {
  return title;
}

string Article::get_author() {
  return author;
}

string Article::get_text() {
  return text;
}

int Article::get_id() {
  return id;
}
