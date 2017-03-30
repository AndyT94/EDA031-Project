
   /* myclient.cc: sample client program */
   #include "connection.h"
   #include "connectionclosedexception.h"
   #include "messagehandler.h"
   #include <iostream>
   #include <string>
   #include <stdexcept>
   #include <cstdlib>


   using namespace std;


 int main(int argc, char* argv[]) {
    if (argc != 3) {
        cerr << "Usage: myclient host-name port-number" << endl;
exit(1); }
    int port = -1;
    try {
        port = stoi(argv[2]);
    } catch (exception& e) {
        cerr << "Wrong port number. " << e.what() << endl;
exit(1); }
    Connection conn(argv[1], port);
    if (!conn.isConnected()) {
        cerr << "Connection attempt failed" << endl;
exit(1); }
    cout << "Type a command: ";
    string line;
    string cmd;
    Connection conn;
    MessageHandler mh;
    while (getline(cin,line)) {
      istringstream iss(line);
      cmd << iss(line);
        try {
          switch(cmd)
        case "list":
          mh.send_code(conn,COM_LIST_NG);
          mh.send_code(conn,COM_END);
          break;

        case "create NewsGroup":
          mh.send_code(conn,COM_CREATE_NG);
          cout << "Name the NewsGroup :"
          string title;
          cin >> title;
          mh.send_string_parameter(conn,title);
          mh.send_code(conn,COM_END);
          break;

        case "delete NewsGroup":
          mh.send_code(conn,COM_DELETE_NG);
          cout << "Give the id of the group you want to delete:"
          int id;
          cin >> id
          mh.send_int_parameter(conn,id);
          mh.send_code(conn,COM_END);
          break;

        case "list article":
          mh.send_code(conn, COM_LIST_ART);
          cout << "Give the id of the NewsGroup:"
          int id;
          cin >> id
          mh.send_int_parameter(conn,id);
          mh.send_code(conn,COM_END);
          break;

        case "create article"
          mh.send_code(conn, COM_LIST_ART);
          cout << "Give the id of the NewsGroup:"
          int id;
          cin >> id
          mh.send_int_parameter(conn,id);
          cout << "Give the article a title:"
          string title;
          cin >> title
          mh.send_string_parameter(conn,title);
          cout << "Write who is the author of the article:"
          string author;
          cin >> author
          mh.send_string_parameter(conn,author);
          cout << "Write the text:"
          string text;
          cin >> text
          mh.send_string_parameter(conn,text);
          mh.send_code(conn,COM_END);
          break;

        case "delete article"
          mh.send_code(conn, COM_DELETE_ART);
          cout << "Give the id of the NewsGroup:"
          int id;
          cin >> id
          mh.send_int_parameter(conn,id);
          cout << "Give the id of the article you want to delete:"
          int id;
          cin >> id
          mh.send_int_parameter(conn,id);
          mh.send_code(conn,COM_END);
          break;

        case "get article"
          mh.send_code(conn,COM_GET_ART);
          cout << "Give the id of the NewsGroup:"
          int id;
          cin >> id
          mh.send_int_parameter(conn,id);
          cout << "Give the id of the article you want to delete:"
          int id;
          cin >> id
          mh.send_int_parameter(conn,id);
          mh.send_code(conn,COM_END);
          break;
          }
        } catch (ConnectionClosedException&) {
            cout << " no reply from server. Exiting." << endl;
            exit(1);
} }
}
