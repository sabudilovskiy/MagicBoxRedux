#include "xmlnode.h"
#include <algorithm>
#include <fstream>
XMLNode::XMLNode(std::wstring value):value(std::move(value)), type(XMLNodeType::VALUE){

}

XMLNode::XMLNode() : type(XMLNodeType::NAMESPACE){

}

XMLNode::~XMLNode()
{
    for (auto& i : childs){
        delete i.second;
    }
}

XMLNodeType XMLNode::get_type(){
    return type;
}

std::vector<std::pair<std::wstring, XMLNode*>>::const_iterator XMLNode::cbegin() const
{
    return childs.cbegin();
}

std::vector<std::pair<std::wstring, XMLNode*>>::const_iterator XMLNode::cend() const
{
    return childs.cend();
}

std::vector<std::pair<std::wstring, XMLNode*>>::iterator XMLNode::begin()
{
    return childs.begin();
}

std::vector<std::pair<std::wstring, XMLNode*>>::iterator XMLNode::end()
{
    return childs.end();
}
bool operator==(const std::pair<std::wstring, XMLNode*> elem, const std::wstring& key){
    return elem.first == key;
}
void XMLNode::add_child(std::wstring name, XMLNode *child){
    childs.emplace_back(std::move(name), child);
}

XMLNode *XMLNode::add_child(std::wstring name)
{
    XMLNode* new_node = new XMLNode();
    childs.emplace_back(std::move(name), new_node);
    return new_node;
}

XMLNode *XMLNode::add_child(std::wstring name, std::wstring value)
{
    XMLNode* new_node = new XMLNode(std::move(value));
    childs.emplace_back(std::move(name), new_node);
    return new_node;
}

XMLNode* XMLNode::get_child(std::wstring name)
{
    auto found = std::find(childs.begin(), childs.end(), std::move(name));
    if (found != childs.end()){
        return found->second;
    }
    else return nullptr;
}

const std::wstring &XMLNode::get_value() const
{
    return value;
}

void XMLNode::set_value(std::wstring new_value)
{
    value = new_value;
}

void XMLNode::load_to_file(std::wstring_view name, std::wostream &file)
{
    file << L'<';
    file << name;
    file << L'>';
    if (type==XMLNodeType::NAMESPACE){
        file << L"\n\n";
        std::sort(childs.begin(), childs.end());
        for (auto& child : childs){
            child.second->load_to_file(child.first, file);
            file <<  L"\n";
        }
    }
    else file << value;
    file << L"</";
    file << name;
    file << L">\n";
    file.flush();
}
