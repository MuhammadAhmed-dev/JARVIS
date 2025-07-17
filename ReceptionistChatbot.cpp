#include "ReceptionistChatbot.h"

ReceptionistChatbot::ReceptionistChatbot()
{
    head = nullptr;
    try
    {
        loadKnowledgeBase("Questions.txt", "Answers.txt");
        loadUserResponses("UserQuestions.txt", "UserAnswers.txt");
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

ReceptionistChatbot::~ReceptionistChatbot()
{
    while (head)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
    }
}

string ReceptionistChatbot ::lowercaseQuery(const string &query)
{
    string lowercaseQuery = query;
    transform(lowercaseQuery.begin(), lowercaseQuery.end(), lowercaseQuery.begin(), ::tolower);
    return lowercaseQuery;
}

bool ReceptionistChatbot::getResponse(const string &userQuery, string &response)
{
    string userQuery1 = userQuery;
    string processedQuery = preprocess(userQuery);

    if (userResponses.find(processedQuery) != userResponses.end())
    {
        response = userResponses[processedQuery];
        return response.find("bye") != string::npos;
    }

    Node *matchingNode = findMatchingNode(processedQuery);

    if (matchingNode)
    {
        response = matchingNode->answer;
        return response.find("bye") != string::npos;
    }

    response = askUser(userQuery1);
    saveUserResponse(userQuery1, response);

    return response.find("bye") != string::npos;
}

void ReceptionistChatbot ::loadKnowledgeBase(const string &questionsFile, const string &answersFile)
{
    ifstream questionsStream(questionsFile);
    ifstream answersStream(answersFile);

    if (!questionsStream.is_open() || !answersStream.is_open())
    {
        throw runtime_error("Questions or answers file not found. Unable to load knowledge base.");
    }

    string questionEntry;
    string answerEntry;

    while (getline(questionsStream, questionEntry) && getline(answersStream, answerEntry))
    {
        insert(questionEntry, answerEntry);
    }

    questionsStream.close();
    answersStream.close();
}

void ReceptionistChatbot ::insert(const string &question, const string &answer)
{
    Node *newNode = new Node(question, answer);
    newNode->next = head;
    head = newNode;
}

void ReceptionistChatbot ::loadUserResponses(const string &questionsFile, const string &answersFile)
{
    ifstream questionsStream(questionsFile);
    ifstream answersStream(answersFile);

    if (!questionsStream.is_open() || !answersStream.is_open())
    {
        throw runtime_error("Questions or answers file not found. Unable to load knowledge base.");
    }

    string questionEntry;
    string answerEntry;

    while (getline(questionsStream, questionEntry) && getline(answersStream, answerEntry))
    {
        insert(questionEntry, answerEntry);
    }

    questionsStream.close();
    answersStream.close();
}

ReceptionistChatbot ::Node *ReceptionistChatbot::findMatchingNode(const string &query)
{
    Node *current = head;
    int minDistance = numeric_limits<int>::max();
    Node *bestMatch = nullptr;

    while (current)
    {
        int distance = calculateLevenshteinDistance(query, preprocess(current->question));

        if (distance < minDistance)
        {
            minDistance = distance;
            bestMatch = current;
        }

        current = current->next;
    }

    if (minDistance <= 3)
    {
        return bestMatch;
    }

    return nullptr;
}

int ReceptionistChatbot ::calculateLevenshteinDistance(const string &str1, const string &str2)
{
    const int m = str1.length();
    const int n = str2.length();

    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= m; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }

    return dp[m][n];
}

string ReceptionistChatbot ::preprocess(const string &str)
{
    // Implement your own logic to remove common words and symbols
    vector<string> commonWords = {"what", "i", "when", "where", "who", "whom", "which", "how", "the", "a", "an", "in", "on", "at", "by", "with", "can"};
    string str1 = lowercaseQuery(str);
    string processedQuery = str1; // Fix: Use the correct parameter name

    // Using a stack to remove common words
    stack<string> wordsToRemove;
    for (const string &word : commonWords)
    {
        size_t pos = processedQuery.find(word);
        while (pos != string::npos)
        {
            wordsToRemove.push(word);
            pos = processedQuery.find(word, pos + 1);
        }
    }

    // Remove words found in the stack
    while (!wordsToRemove.empty())
    {
        string wordToRemove = wordsToRemove.top();
        size_t pos = processedQuery.find(wordToRemove);
        while (pos != string::npos)
        {
            processedQuery.erase(pos, wordToRemove.length());
            pos = processedQuery.find(wordToRemove);
        }
        wordsToRemove.pop();
    }

    // Remove symbols and convert to lowercase
    processedQuery.erase(remove_if(processedQuery.begin(), processedQuery.end(), ::ispunct), processedQuery.end());
    transform(processedQuery.begin(), processedQuery.end(), processedQuery.begin(), ::tolower);

    // Trim leading and trailing whitespaces
    processedQuery.erase(processedQuery.begin(), find_if(processedQuery.begin(), processedQuery.end(), [](int ch)
                                                         { return !isspace(ch); }));
    processedQuery.erase(find_if(processedQuery.rbegin(), processedQuery.rend(), [](int ch)
                                 { return !isspace(ch); })
                             .base(),
                         processedQuery.end());
    return processedQuery;
}

string ReceptionistChatbot ::askUser(const string &query)
{
    string userResponse;
    cout << "Jarvis: I don't know the answer. Can you please provide a response for \"" << query << "\"? \nUser Response: ";
    getline(cin, userResponse);
    cout << "Jarvis: Thank you for teaching me!" << endl;
    return userResponse;
}

void ReceptionistChatbot ::saveUserResponse(const string &query, const string &response)
{
    ofstream userQuestionsFile("UserQuestions.txt", ios::app);
    ofstream userAnswersFile("UserAnswers.txt", ios::app);

    if (userQuestionsFile.is_open() && userAnswersFile.is_open())
    {
        userQuestionsFile << lowercaseQuery(query) << "\n";
        userAnswersFile << response << "\n";

        userQuestionsFile.close();
        userAnswersFile.close();

        userResponses[preprocess(query)] = response;
    }
    else
    {
        cerr << "Error: Unable to open user files for writing.\n";
    }
}
