#include <iostream>
#include "ReceptionistChatbot.cpp"
using namespace std;

int main()
{
    try
    {
        ReceptionistChatbot chatbot;

        string userInput;
        cout << "Jarvis: Hi! How can I help you today? Type 'bye' to exit.\n";

        while (true)
        {
            cout << "You: ";
            getline(cin, userInput);

            string response;
            if (userInput == "bye" || userInput == "BYE" || userInput == "Bye")
            {
                cout << "Jarvis: Goodbye! Have a great day.\n";
                break;
            }
            chatbot.getResponse(userInput, response);
            cout << "Jarvis: " << response << "\n";
        }
    }
    catch (const exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "Unknown error occurred.\n";
    }

    return 0;
}
