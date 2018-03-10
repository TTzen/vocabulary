#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <vector>
#include <string>

using std::string;
using std::vector;

#define DICTIONARY_PATH "/home/sky/english/dictionary"

class vocabulary
{
    typedef struct
    {
        string English;
        string Chinese;
        int    priority;
    }English_unit;

public:
    vocabulary();
    ~vocabulary() {}

public:
   static vocabulary* get_instance()
   {
        static vocabulary instance;
        return &instance;
   }

   void work();

private:
   int load_dictionar();
   int load_vocabulary(string dictionary_name);
   int split_line(string src, vector<string>& reslut);

private:
    vector<string> m_dictionary;
    vector<English_unit> m_vocabularys;
};

#endif // VOCABULARY_H
