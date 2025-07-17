# 🤖 Receptionist Chatbot (Jarvis)

A lightweight, terminal-based receptionist chatbot built in **C++**. Jarvis uses a simple question-answer knowledge base and fuzzy matching to provide relevant responses to user queries. If it doesn't know an answer, it asks the user and learns it for future use.

---

## 🧠 Features

* 📘 Loads Q\&A from knowledge base files
* 🔍 Uses **Levenshtein distance** for fuzzy query matching
* ✍️ Learns from new user questions and saves answers
* 💬 Conversational terminal interface
* 🧵 Linked-list structure to manage question-answer nodes

---

## 🗂️ Project Structure

```
ReceptionistChatbot/
├── ReceptionistChatbot.h       # Chatbot class declaration
├── ReceptionistChatbot.cpp     # Chatbot implementation
├── chatbot.cpp                 # Main program entry point
├── questions.txt               # file with predefined questions
├── answers.txt                 # file with predefined answers
├── UserQuestions.txt           # file maintained by JARVIS
├── UserAnswers.txt             # file maintained by JARVIS
└── README.md
```

---

## ⚙️ How It Works

1. **Initialization**:

   * Loads questions and answers into a singly linked list.
   * Converts queries to lowercase and preprocesses for fuzzy matching.

2. **Interaction**:

   * Accepts user input.
   * Searches for a matching question using string similarity.
   * If found, returns the corresponding answer.
   * If not found, prompts the user for an answer and saves it.

3. **Persistence**:

   * Learns from user input and updates its memory (`userResponses` map).
   * (Optional) You can extend it to save new data to file.

---

## ✅ Getting Started

### 1. **Clone the Repository**

```bash
git clone https://github.com/yourusername/receptionist-chatbot.git
cd receptionist-chatbot
```

### 2. **Compile the Program**

Use any C++ compiler (e.g., g++, clang++). Here's a sample with `g++`:

```bash
g++ chatbot.cpp -o chatbot
```

### 3. **Run the Chatbot**

```bash
./chatbot
```

You’ll see:

```
Jarvis: Hi! How can I help you today? Type 'bye' to exit.
You:
```

---

## 💡 Example Conversation

```
Jarvis: Hi! How can I help you today? Type 'bye' to exit.
You: What are your working hours?
Jarvis: Our working hours are from 9 AM to 5 PM, Monday to Friday.
You: Where is the cardiology department?
Jarvis: Sorry, I don't know the answer to that. Can you please tell me?
You: It's on the second floor, left wing.
Jarvis: Got it. I'll remember that.
```

---

## 🛠️ Customization

You can populate your own knowledge base using:

* `questions.txt`
* `answers.txt`

Then, modify `loadKnowledgeBase()` to read from those files at startup.

---

## 🧪 Possible Improvements

* Save new learned responses to disk
* Add spell correction (currently uses Levenshtein but doesn't correct input)
* GUI interface using Qt or a web frontend
* Context-awareness for follow-up questions
