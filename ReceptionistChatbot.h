#ifndef RECEPTIONISTCHATBOT_H
#define RECEPTIONISTCHATBOT_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <limits>
#include <stack>

using namespace std;

class ReceptionistChatbot
{
public:
    ReceptionistChatbot();
    ~ReceptionistChatbot();
    bool getResponse(const string &userQuery, string &response);

private:
    struct Node
    {
        string question;
        string answer;
        Node *next;

        Node(const string &q, const string &a) : question(q), answer(a), next(nullptr) {}
    };

    Node *head;
    unordered_map<string, string> userResponses;
    string lowercaseQuery(const string &query);
    string preprocess(const string &str);
    void loadKnowledgeBase(const string &questionsFile, const string &answersFile);
    void insert(const string &question, const string &answer);
    void loadUserResponses(const string &questionsFile, const string &answersFile);
    Node *findMatchingNode(const string &query);
    int calculateLevenshteinDistance(const string &str1, const string &str2);
    string askUser(const string &query);
    void saveUserResponse(const string &query, const string &response);
};

#endif
