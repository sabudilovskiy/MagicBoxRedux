#ifndef XMLNODE_H
#define XMLNODE_H
#include<unordered_map>
enum XMLNodeType{
    VALUE, NAMESPACE
};
class XMLNode
{
    std::vector<std::pair<std::wstring, XMLNode*>> childs;
    std::wstring value;
    XMLNodeType type;
public:
    XMLNode(std::wstring value);
    XMLNode();
    ~XMLNode();
    XMLNodeType get_type();
    std::vector<std::pair<std::wstring, XMLNode*>>::const_iterator cbegin() const;
    std::vector<std::pair<std::wstring, XMLNode*>>::const_iterator cend() const;
    std::vector<std::pair<std::wstring, XMLNode*>>::iterator begin();
    std::vector<std::pair<std::wstring, XMLNode*>>::iterator end();
    void add_child(std::wstring name, XMLNode* child);
    XMLNode* add_child(std::wstring name);
    XMLNode* add_child(std::wstring name, std::wstring value);
    XMLNode* get_child(std::wstring name);
    const std::wstring& get_value() const;
    void set_value(std::wstring new_value);
    void load_to_file(std::wstring_view name, std::wostream& file);
};
#endif // XMLNODE_H
