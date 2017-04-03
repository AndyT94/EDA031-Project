
   /* myclient.cc: sample client program */
   #include "connection.h"
   #include "connectionclosedexception.h"
   #include "MessageHandler.h"
   #include "protocol.h"
   #include <iostream>
   #include <string>
   #include <stdexcept>
   #include <cstdlib>
   #include <limits>

   using namespace std;


 int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: myclient host-name port-number" << endl;
        exit(1);
    }
    int port = -1;
    try {
        port = stoi(argv[2]);
    } catch (exception& e) {
        cerr << "Wrong port number. " << e.what() << endl;
        exit(1);
    }
    Connection conn(argv[1], port);
    if (!conn.isConnected()) {
        cerr << "Connection attempt failed" << endl;
        exit(1);
    }
    cout << "Type a command: ";
    string line;
    MessageHandler mh;

    while (getline(cin,line)) {
        try {

          if(line == "list newsgroup"){
            mh.send_code(conn,Protocol::COM_LIST_NG);
            mh.send_code(conn,Protocol::COM_END);
            mh.recv_code(conn);
            int nbr = mh.recv_int_parameter(conn);
            for(int i = 0; i < nbr; ++i){
              int id = mh.recv_int_parameter(conn);
              string name = mh.recv_string_paramter(conn);
              cout << "Newsgroup ID: "<< id << " Newsgroup name: " << name << endl;
            }
            mh.recv_code(conn);

          } else if(line == "create newsgroup"){
            mh.send_code(conn,Protocol::COM_CREATE_NG);
            cout << "Name the newsgroup: ";
            string name;
            getline(cin,name);
            while (name.empty()) {
              cout << "Please enter a non empty string! Try again: ";
              getline(cin,name);
            }
            mh.send_string_parameter(conn,name);
            mh.send_code(conn,Protocol::COM_END);

            mh.recv_code(conn);
            if(mh.recv_code(conn) == Protocol::ANS_ACK){
              cout << "Succesfully created a new newsgroup!" << endl;
            } else {
              cout << "Newsgroup already exists!" << endl;
              mh.recv_code(conn);
            }
            mh.recv_code(conn);

          } else if(line == "delete newsgroup") {
            cout << "Give the id of the group you want to delete: ";
            int id;
            cin >> id;
            if(!cin) {
              cout << "Expected an integer!" << endl;
            } else {
              mh.send_code(conn,Protocol::COM_DELETE_NG);
              mh.send_int_parameter(conn,id);
              mh.send_code(conn,Protocol::COM_END);

              mh.recv_code(conn);
              if(mh.recv_code(conn) == Protocol::ANS_ACK){
                cout << "Succesfully deleted the choosen newsgroup!" << endl;
              } else {
                cout << "Newsgroup does not exist! " << endl;
                mh.recv_code(conn);
              }
              mh.recv_code(conn);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

          } else if (line == "list article") {
            cout << "Give the id of the newsgroup: ";
            int id;
            cin >> id;
            if(!cin) {
              cout << "Expected an integer!" << endl;
            } else {
              mh.send_code(conn,Protocol::COM_LIST_ART);
              mh.send_int_parameter(conn,id);
              mh.send_code(conn,Protocol::COM_END);

              mh.recv_code(conn);
              if(mh.recv_code(conn) == Protocol::ANS_ACK){
                int nbr = mh.recv_int_parameter(conn);
                for (int i = 0; i < nbr; ++i) {
                  int id = mh.recv_int_parameter(conn);
                  string title = mh.recv_string_paramter(conn);
                  cout << "Article id: " << id << " " << "Article title: " << title << endl;
                }
              } else {
                cout << "Newsgroup does not exist" << endl;
                mh.recv_code(conn);
              }
              mh.recv_code(conn);
            }
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

          } else if(line == "create article"){
            cout << "Give the id of the newsgroup: ";
            int id;
            cin >> id;
            if(!cin) {
              cout << "Expected an integer!" << endl;
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
              mh.send_code(conn,Protocol::COM_CREATE_ART);
              mh.send_int_parameter(conn,id);

              cout << "Give the article a title: ";
              string title;
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
              getline(cin,title);
              while (title.empty()) {
                cout << "Please enter a non empty string! Try again: ";
                getline(cin,title);
              }
              mh.send_string_parameter(conn,title);

              cout << "Write who is the author of the article: ";
              string author;
              getline(cin, author);
              while (author.empty()) {
                cout << "Please enter a non empty string! Try again: ";
                getline(cin,author);
              }
              mh.send_string_parameter(conn,author);

              cout << "Write the text: ";
              string text;
              getline(cin, text);
              while (text.empty()) {
                cout << "Please enter a non empty string! Try again: ";
                getline(cin, text);
              }
              mh.send_string_parameter(conn,text);
              mh.send_code(conn,Protocol::COM_END);

              mh.recv_code(conn);
              if(mh.recv_code(conn) == Protocol::ANS_ACK){
                cout << "Succesfully created a article!" << endl;
              } else {
                cout << "Newsgroup does not exist" << endl;
                mh.recv_code(conn);
              }
              mh.recv_code(conn);
            }

          } else if (line == "delete article") {
            cout << "Give the id of the newsgroup: ";
            int id;
            cin >> id;
            if(!cin) {
              cout << "Expected an integer!" << endl;
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
              cout << "Give the id of the article you want to delete: ";
              int a_id;
              cin >> a_id;
              if(!cin) {
                cout << "Expected an integer!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
              } else {
                mh.send_code(conn,Protocol::COM_DELETE_ART);
                mh.send_int_parameter(conn,id);
                mh.send_int_parameter(conn,a_id);
                mh.send_code(conn,Protocol::COM_END);

                mh.recv_code(conn);

                int ans = mh.recv_code(conn);
                if (ans == Protocol::ANS_ACK) {
                  cout << "Succesfully deleted the choosen article!" << endl;
                } else {
                  if (mh.recv_code(conn) == Protocol::ERR_NG_DOES_NOT_EXIST) {
                    cout << "Newsgroup does not exist!" << endl;
                  } else {
                    cout << "Article does not exist!" << endl;
                  }
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                mh.recv_code(conn);
              }
            }

          } else if(line == "get article"){
            cout << "Give the id of the newsgroup: ";
            int id;
            cin >> id;
            if(!cin) {
              cout << "Expected an integer!" << endl;
              cin.clear();
              cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else {
              cout << "Give the id of the article you want to delete: ";
              int a_id;
              cin >> a_id;
              if(!cin) {
                cout << "Expected an integer!" << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
              } else {
                mh.send_code(conn, Protocol::COM_GET_ART);
                mh.send_int_parameter(conn, id);
                mh.send_int_parameter(conn, a_id);
                mh.send_code(conn, Protocol::COM_END);

                mh.recv_code(conn);
                if(mh.recv_code(conn) == Protocol::ANS_ACK){
                  string title = mh.recv_string_paramter(conn);
                  string author = mh.recv_string_paramter(conn);
                  string text = mh.recv_string_paramter(conn);

                  cout << "Title: " << title << endl << "Author: " << endl
                    << "Text: " << text << endl;
                } else {
                  if (mh.recv_code(conn) == Protocol::ERR_NG_DOES_NOT_EXIST) {
                    cout << "Newsgroup does not exist!" << endl;
                  } else {
                    cout << "Article does not exist!" << endl;
                  }
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                mh.recv_code(conn);
              }
            }
          } else {
            cout << "The following commands exist:" << endl << "list newsgroup" << endl
              << "create newsgroup" << endl << "delete newsgroup" << endl << "list article"
                << endl << "create article" << endl << "delete article" << endl << "get article" << endl;
          }
          cout << endl << "Type a command: ";
        } catch (ConnectionClosedException&) {
            cout << " no reply from server. Exiting." << endl;
            exit(1);
        }
    }
}
