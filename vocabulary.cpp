#include "vocabulary.h"
#include <dirent.h>
#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <time.h>

using namespace std;

vocabulary::vocabulary()
{

}

void vocabulary::work()
{
    if (load_dictionar() == -1)
    {
        cout << "error" << endl;
        return;
    }

    int Dic_id;
    do
    {
        cout << "Please Choose a dictionary !!! ENTER NUMBER" << endl;
        for (size_t i = 0 ; i < m_dictionary.size(); ++i)
        {
            cout << "(" << i << ") :" << m_dictionary[i] << endl;
        }
        cin >> Dic_id;
    }
    while (Dic_id >= m_dictionary.size() || Dic_id < 0);
    load_vocabulary(m_dictionary[Dic_id]);

    srand(time(NULL));
    int num_vocabulary = m_vocabularys.size();
    while(true)
    {
        if (num_vocabulary == 0)
        {
            break;
        }
        int pos = rand() % num_vocabulary;
        cout << "ENGLIG" << endl;
        cout << "-----------------" << endl;
        cout << m_vocabularys[pos].English << endl;
        while (true)
        {
            cout << "Are you remember !!!  [Y/n]?" << endl;
            char flg;
            cin >> flg;
            if (flg == 'Y' || flg == 'y')
            {
                m_vocabularys.erase(m_vocabularys.begin() + pos);
                num_vocabulary --;
                cout << m_vocabularys[pos].Chinese << endl;
                cout << "(^ v ^)" << endl;
                break;
            }else if (flg == 'N' || flg == 'n')
            {
                cout << m_vocabularys[pos].Chinese << endl;
                cout << "(> o <)" << endl;
                break;
            }
        }
    }
}



int vocabulary::load_dictionar()
{
    if (access(DICTIONARY_PATH, F_OK) != 0)
    {
        cout << "Dictionary path worry!!!" << endl;
        return -1;
    }
    DIR* dir = opendir(DICTIONARY_PATH);
    if (dir == NULL)
    {
        cout << "Dictionary path don't open!!!" << endl;
        return -1;
    }

    struct dirent* file;
    while ((file = readdir(dir)) != NULL)
    {
        if (file->d_type != DT_REG || (file->d_name)[0] == '.')
        {
            continue;
        }
        char* ext = strrchr(file->d_name, '.');
        if (ext == NULL || strcasecmp(ext, ".eng") != 0)
        {
            continue;
        }
        m_dictionary.push_back(string(string(DICTIONARY_PATH) + "/" + file->d_name));
    }

    closedir(dir);
    dir = NULL;

    return m_dictionary.size();
}

int vocabulary::load_vocabulary(string dictionary_name)
{
    if (access(dictionary_name.c_str(), F_OK) != 0)
    {
        cout << "not find dictionary !!" << __FILE__ << __LINE__<<endl;
        return -1;
    }
    FILE* Fdic = fopen(dictionary_name.c_str(), "r");
    if (Fdic == NULL)
    {
        cout << "dic don't open!!!" << __FILE__ << __LINE__ << endl;
        return -1;
    }
    while (true)
    {
        char buffer[1024];
        memset(buffer, 0, 1024);
        char* ret = NULL;
        ret = fgets(buffer, 1024, Fdic);
        if (ret == NULL)
        {
            break;
        }
        vector<string> fileds;
        if (split_line(buffer, fileds) != 3)
        {
            continue;
        }
        English_unit unit;
        unit.English = fileds[0];
        unit.Chinese = fileds[1];
        sscanf(fileds[2].c_str(), "%d", &(unit.priority));
        m_vocabularys.push_back(unit);
    }
    fclose(Fdic);
    return m_vocabularys.size();
}


int vocabulary::split_line(string src, vector<string>& reslut)
{
    size_t post  = 0;
    size_t begin = 0;
    while (true)
    {
        post = src.find('>', begin);
        if (post == string::npos)
        {
            break;
        }
        string filed = src.substr(begin, post - begin);
        begin = post + 1;
        reslut.push_back(filed);
    }
    return reslut.size();
}
