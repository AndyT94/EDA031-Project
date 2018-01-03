# EDA031Project

# A News System Implementation

## 1 Background

```
Usenet News is an old (started in 1986) system for sharing information over the web. Information
is distributed in the form of “articles” that are posted to “newsgroups”. Articles are distributed
to news servers, and a user can hook up to a news server and read articles and also post articles
in newsgroups and create new newsgroups. The user runs a news client which uses the NNTP^1
protocol to communicate with the server.
In this project, you shall develop your own news system, consisting of a news server and
a news client. Both programs shall be written in C++. The server is dedicated and does not
share news with other servers. Instead of NNTP you will use the communication protocol that is
defined in section 6.
```

## 2 System Requirements

```
2.1 General Requirements
```
```
The system consists of a server that handles a database containing newsgroups and articles and a
client that accepts commands from the user and communicates with the server. Several clients
may be connected to the server simultaneously.
The following tasks can be performed:
```
- List newsgroups.
- Create and delete newsgroups.
- List articles in a newsgroup.
- Read, write and delete articles in a newsgroup.

```
The system keeps track of the title and the author of each article. It cannot handle subject threads,
follow-up articles or similar advanced concepts that are available in standard NNTP-based news
implementations.
The communication between the server and the client follows the messaging protocol that is
defined in section 6.
There are no security requirements on the system. For instance, any user can delete news-
groups and articles, even if he or she is not the creator.
```
```
2.2 Server Requirements
```
```
Detailed requirements on the server:
```
- There are two versions of the server: the first version uses a database stored in primary
    memory, the second a database stored on disk.
- The in-memory version of the server starts from scratch each time it is invoked and builds
    the database in primary memory.
- The disk version of the database remembers the database between invocations. Changes to
    the database are immediately reflected on disk. See section 3.2.
- Each newsgroup has a unique name. A newsgroup also has a unique identification number,
    greater than zero. Identification numbers may not be reused.
- Each article has a title, an author and an article text. The article names need not be unique.
    An article also has an identification number, which must be unique in the newsgroup.
       Identification numbers may not be reused.
- Listings of newsgroups and articles are in chronological order, with the oldest item first.
- There are no limitations on the number of newsgroups or the number of articles in a
    newsgroup.
- There are no limitations on the length of newsgroup titles, article titles, author names or
    article texts.
- If a client misbehaves, for example by not following the messaging protocol, it is immediately
    disconnected by the server.
- The server tries to handle all errors. If it cannot recover from an error, it terminates with an
    informative error message.

**2.3 Client Requirements**

Requirements on the client:

- The clients reads commands from the keyboard, communicates with the server and presents
    the replies from the server on the terminal.
- The client is easy to use and contains informative help texts. No manual is necessary to use
    the client program.
- The client tries to handle all errors. If it cannot recover from an error, it terminates with an
    informative error message.
