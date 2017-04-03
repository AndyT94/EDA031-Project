#include "server.h"
#include "connection.h"
#include "connectionclosedexception.h"
#include "nosuchelementexception.h"
#include "databasememory.h"
#include "MessageHandler.h"
#include "newsgroup.h"
#include "protocol.h"

#include <memory>
#include <iostream>
#include <string>
#include <stdexcept>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
	if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}

	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}

	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}

	DatabaseMemory db;
	MessageHandler msg_handler;
	while (true) {
		auto conn = server.waitForActivity();
		if (conn != nullptr) {
			try {
				auto cmd = msg_handler.recv_code(*conn);
				switch (cmd) {
					case Protocol::COM_LIST_NG: {
						if (msg_handler.recv_code(*conn) != Protocol::COM_END) {
							throw ConnectionClosedException();
						}
						vector<NewsGroup> v;
						v = db.list_newsgroups();
						msg_handler.send_code(*conn, Protocol::ANS_LIST_NG);
						msg_handler.send_int_parameter(*conn, v.size());
						for (unsigned int i = 0; i < v.size(); ++i) {
							msg_handler.send_int_parameter(*conn, v[i].get_newsgroupId());
							msg_handler.send_string_parameter(*conn, v[i].get_name());
						}
						msg_handler.send_code(*conn, Protocol::ANS_END);
						break;

					} case Protocol::COM_CREATE_NG: {
						string name;
						name = msg_handler.recv_string_paramter(*conn);
						if (msg_handler.recv_code(*conn) != Protocol::COM_END) {
							throw ConnectionClosedException();
						}
						msg_handler.send_code(*conn, Protocol::ANS_CREATE_NG);
						if (db.create_newsgroup(name)) {
							msg_handler.send_code(*conn, Protocol::ANS_ACK);
						} else {
							msg_handler.send_code(*conn, Protocol::ANS_NAK);
							msg_handler.send_code(*conn, Protocol::ERR_NG_ALREADY_EXISTS);
						}
						msg_handler.send_code(*conn, Protocol::ANS_END);
						break;

					}	case Protocol::COM_DELETE_NG: {
						int group_id = msg_handler.recv_int_parameter(*conn);
						if (msg_handler.recv_code(*conn) != Protocol::COM_END) {
							throw ConnectionClosedException();
						}
						msg_handler.send_code(*conn, Protocol::ANS_DELETE_NG);
						if (db.delete_newsgroup(group_id)) {
							msg_handler.send_code(*conn, Protocol::ANS_ACK);
						} else {
							msg_handler.send_code(*conn, Protocol::ANS_NAK);
							msg_handler.send_code(*conn, Protocol::ERR_NG_DOES_NOT_EXIST);
						}
						msg_handler.send_code(*conn, Protocol::ANS_END);
						break;

					} case Protocol::COM_LIST_ART: {
						int group_id = msg_handler.recv_int_parameter(*conn);
						if (msg_handler.recv_code(*conn) != Protocol::COM_END) {
							throw ConnectionClosedException();
						}
						msg_handler.send_code(*conn, Protocol::ANS_LIST_ART);
						if (db.hasGroup(group_id)) {
							vector<Article> a;
							a = db.list_articles(group_id);
							msg_handler.send_code(*conn, Protocol::ANS_ACK);
							msg_handler.send_int_parameter(*conn, a.size());
							for (unsigned int i = 0; i < a.size(); ++i) {
								msg_handler.send_int_parameter(*conn, a[i].get_id());
								msg_handler.send_string_parameter(*conn, a[i].get_title());
							}
						} else {
							msg_handler.send_code(*conn, Protocol::ANS_NAK);
							msg_handler.send_code(*conn, Protocol::ERR_NG_DOES_NOT_EXIST);
						}
						msg_handler.send_code(*conn, Protocol::ANS_END);
						break;

					} case Protocol::COM_CREATE_ART: {
						int group_id = msg_handler.recv_int_parameter(*conn);
						string title;
						title = msg_handler.recv_string_paramter(*conn);
						string author;
						author = msg_handler.recv_string_paramter(*conn);
						string text;
						text = msg_handler.recv_string_paramter(*conn);
						if (msg_handler.recv_code(*conn) != Protocol::COM_END) {
							throw ConnectionClosedException();
						}
						msg_handler.send_code(*conn, Protocol::ANS_CREATE_ART);
						if (db.create_article(group_id, title, author, text)) {
							msg_handler.send_code(*conn, Protocol::ANS_ACK);
						} else {
							msg_handler.send_code(*conn, Protocol::ANS_NAK);
							msg_handler.send_code(*conn, Protocol::ERR_NG_DOES_NOT_EXIST);
						}
						msg_handler.send_code(*conn, Protocol::ANS_END);
						break;

					} case Protocol::COM_DELETE_ART: {
						int group_id = msg_handler.recv_int_parameter(*conn);
						int article_id = msg_handler.recv_int_parameter(*conn);
						if (msg_handler.recv_code(*conn) != Protocol::COM_END) {
							throw ConnectionClosedException();
						}
						msg_handler.send_code(*conn, Protocol::ANS_DELETE_ART);
						if(!db.hasGroup(group_id)) {
							msg_handler.send_code(*conn, Protocol::ANS_NAK);
							msg_handler.send_code(*conn, Protocol::ERR_NG_DOES_NOT_EXIST);
							msg_handler.send_code(*conn, Protocol::ANS_END);
							break;
						}
						try {
							db.delete_article(group_id, article_id);
							msg_handler.send_code(*conn, Protocol::ANS_ACK);
						} catch (NoSuchElementException&) {
							msg_handler.send_code(*conn, Protocol::ANS_NAK);
							msg_handler.send_code(*conn, Protocol::ERR_ART_DOES_NOT_EXIST);
						}
						msg_handler.send_code(*conn, Protocol::ANS_END);
						break;

					} case Protocol::COM_GET_ART: {
						int group_id = msg_handler.recv_int_parameter(*conn);
						int article_id = msg_handler.recv_int_parameter(*conn);
						if (msg_handler.recv_code(*conn) != Protocol::COM_END) {
							throw ConnectionClosedException();
						}
						msg_handler.send_code(*conn, Protocol::ANS_GET_ART);
						if(!db.hasGroup(group_id)) {
							msg_handler.send_code(*conn, Protocol::ANS_NAK);
							msg_handler.send_code(*conn, Protocol::ERR_NG_DOES_NOT_EXIST);
							msg_handler.send_code(*conn, Protocol::ANS_END);
							break;
						}
						try {
							Article a = db.get_article(group_id, article_id);
							msg_handler.send_code(*conn, Protocol::ANS_ACK);
							msg_handler.send_string_parameter(*conn, a.get_title());
							msg_handler.send_string_parameter(*conn, a.get_author());
							msg_handler.send_string_parameter(*conn, a.get_text());
						} catch (NoSuchElementException&) {
							msg_handler.send_code(*conn, Protocol::ANS_NAK);
							msg_handler.send_code(*conn, Protocol::ERR_ART_DOES_NOT_EXIST);
						}
						msg_handler.send_code(*conn, Protocol::ANS_END);
						break;
					} default:
						throw ConnectionClosedException();
						break;
				}
			} catch (ConnectionClosedException&) {
				server.deregisterConnection(conn);
				cout << "Client closed connection" << endl;
			}
		} else {
			conn = make_shared<Connection>();
			server.registerConnection(conn);
			cout << "New client connects" << endl;
		}
	}
}
