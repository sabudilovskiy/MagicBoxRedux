#ifndef XML_H
#define XML_H

#include "xmlitem.h"
#include <vector>
#include <fstream>
#include <xmlnode.h>
#include <algorithm>
#include <stdexcept>
class XML{
    XMLNode* root;
public:
    XML();
    XML(std::wistream& file);
    void load_to_file(std::wostream& file);
    ~XML();
    XMLNode* get_child(const std::wstring& name);
    XMLNode* get_root();
    std::vector<std::pair<std::wstring, XMLNode*>>::const_iterator cbegin() const;
    std::vector<std::pair<std::wstring, XMLNode*>>::const_iterator cend() const;
    std::vector<std::pair<std::wstring, XMLNode*>>::iterator begin();
    std::vector<std::pair<std::wstring, XMLNode*>>::iterator end();
};

class UnclosedTag : public std::exception{
    std::string name_tag;
public:
    const char * what () const override{
        return name_tag.c_str();
    }
    UnclosedTag(std::string name_tag):name_tag(name_tag + " не закрыт тег"){
    }
};

class InCorrectXML : public std::exception{

};
#endif // XML_H
