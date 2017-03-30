
   /* myclient.cc: sample client program */
   #include "connection.h"
   #include "connectionclosedexception.h"
   #include "MessageHandler.h"
   #include "protocol.h"
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
    Connection con(argv[1], port);
    auto conn = make_shared<Connection>(con);
    if (!conn.isConnected()) {
        cerr << "Connection attempt failed" << endl;
exit(1); }
    cout << "Type a command: ";
    string line;
    MessageHandler mh;
    while (getline(cin,line)) {
        try {

        if(line == "list"){
          mh.send_code(conn,Protocol::COM_LIST_NG);
          mh.send_code(conn,Protocol::COM_END);
          mh.recv_code(conn);
          int nbr = mh.recv_int_parameter(conn);
          for(int i = 0; i < nbr; ++i){
            int id = mh.recv_int_parameter(conn);
            string name = mh.recv_string_paramter(conn);
            cout << "NewsGroup id " << id << " " << " Name" << name << endl;
          }
          mh.recv_code(conn);

        } else if(line == "create NewsGroup"){
          mh.send_code(conn,Protocol::COM_CREATE_NG);
          cout << "Name the NewsGroup :";
          string title;
          cin >> title;
          mh.send_string_parameter(conn,title);
          mh.send_code(conn,Protocol::COM_END);

          mh.recv_code(conn);
          if(mh.recv_code(conn) == Protocol::ANS_ACK){
            cout << "Succesfully created a new NewsGroup!";
          } else {
            cout << "NewsGroup already exists";
            mh.recv_code(conn);
          }
          mh.recv_code(conn);

        } else if(line == "delete NewsGroup"){
          mh.send_code(conn,Protocol::COM_DELETE_NG);
          cout << "Give the id of the group you want to delete:";
          int id;
          cin >> id;
          mh.send_int_parameter(conn,id);
          mh.send_code(conn,Protocol::COM_END);

          mh.recv_code(conn);
          if(mh.recv_code(conn) == Protocol::ANS_ACK){
            cout << "Succesfully deleted the choosen NewsGroup!";
          } else {
            cout << "NewsGroup does not exist";
            mh.recv_code(conn);
          }
          mh.recv_code(conn);
        } else if(line == "list article"){
          mh.send_code(conn,Protocol::COM_LIST_ART);
          cout << "Give the id of the NewsGroup:";
          int id;
          cin >> id;
          mh.send_int_parameter(conn,id);
          mh.send_code(conn,Protocol::COM_END);

          mh.recv_code(conn);
          if(mh.recv_code(conn) == Protocol::ANS_ACK){
            int nbr = mh.recv_int_parameter(conn);
            for(int i = 0; i < nbr;++i){
              int id = mh.recv_int_parameter(conn);
              string title = mh.recv_string_paramter(conn);
              cout << "article id" << id << " " << "article title :" << title << endl;
            }

          } else {
            cout << "NewsGroup does not exist";
            mh.recv_code(conn);
          }
          mh.recv_code(conn);
        } else if(line == "create article"){
          mh.send_code(conn,Protocol::COM_LIST_ART);
          cout << "Give the id of the NewsGroup:";
          int id;
          cin >> id;
          mh.send_int_parameter(conn,id);
          cout << "Give the article a title:";
          string title;
          cin >> title;
          mh.send_string_parameter(conn,title);
          cout << "Write who is the author of the article:";
          string author;
          cin >> author;
          mh.send_string_parameter(conn,author);
          cout << "Write the text:";
          string text;
          cin >> text;
          mh.send_string_parameter(conn,text);
          mh.send_code(conn,COM_END);

          mh.recv_code(conn);
          if(mh.recv_code(conn) == Protocol::ANS_ACK){
            cout << "Succesfully created a article!";
          } else {
            cout << "NewsGroup does not exist";
            mh.recv_code(conn);
          }
          mh.recv_code(conn);

        }else if(line == "delete article"){
          mh.send_code(conn,Protocol::COM_DELETE_ART);
          cout << "Give the id of the NewsGroup:";
          int id;
          cin >> id;
          mh.send_int_parameter(conn,id);
          cout << "Give the id of the article you want to delete:";
          int id;
          cin >> id;
          mh.send_int_parameter(conn,id);
          mh.send_code(conn,Protocol::COM_END);

          mh.recv_code(conn);
          if(mh.recv_code(conn) == Protocol::ANS_ACK){
            cout << "Succesfully deleted the choosen article!";
          } else if ( mh.recv_code(conn) == Protocol::ANS_NAK) {
            cout << "NewsGroup does not exist";
            mh.recv_code(conn);
          } else {
            cout << "Article does not exist";
            mh.recv_code(conn);
          }
          mh.recv_code(conn);
        } else if(line == "get article"){
          mh.send_code(conn,Protocol::COM_GET_ART);
          cout << "Give the id of the NewsGroup:";
          int id;
          cin >> id;
          mh.send_int_parameter(conn,id);
          cout << "Give the id of the article you want to delete";
          int id;
          cin >> id;
          mh.send_int_parameter(conn,id);
          mh.send_code(conn,Protocol::COM_END);

          mh.recv_code(conn);
          if(mh.recv_code(conn) == Protocol::ANS_ACK){
            string title = mh.recv_string_paramter(conn);
            string author = mh.recv_string_paramter(conn);
            string text = mh.recv_string_paramter(conn);
          } else if(mh.recv_code(conn) == Protocol::ANS_NAK){
            cout << "NewsGroup does not exist";
            mh.recv_code(conn);
          } else {
            cout << "Article does not exist";
            mh.recv_code(conn);
          }
          mh.recv_code(conn);

        }
          }
        } catch (ConnectionClosedException&) {
            cout << " no reply from server. Exiting." << endl;
            exit(1);
} }
}
