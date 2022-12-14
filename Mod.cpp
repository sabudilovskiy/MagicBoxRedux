#include "Mod.h"
#include "ModExceptions.h"
#include <QString>
Mod::Mod(std::wstring id, XMLNode &node) : _id(std::move(id))
{
    auto node_name = node.get_child(L"name");
    if (!node_name) throw MissingName(QString::fromStdWString(_id).toStdString());
    _name = node_name->get_value();
    auto node_type = node.get_child(L"type");
    if (!node_type) throw MissingModType(QString::fromStdWString(_id).toStdString());
    std::wstring wtype = node_type->get_value();
    if (wtype == L"DB"){
        _type = Type::DB;
    }
    else if (wtype == L"SDK"){
        _type = Type::SDK;
    }
    else throw UnknownModType(QString::fromStdWString(_id).toStdString());
    auto node_versions = node.get_child(L"versions");
    if (!node_versions) throw MissingVersions(QString::fromStdWString(_id).toStdString());
    for (auto& version : *node_versions){
        _verisons.push_back(version.second->get_value());
    }
    if (_verisons.empty()){
        throw MissingVersions(QString::fromStdWString(_id).toStdString());
    }
    auto node_selected_version = node.get_child(L"selected-version");
    if (!node_selected_version){
        _selected_version = 0;
    }
    else {
        _selected_version = std::stoi(node_selected_version->get_value());
    }
}

const std::wstring &Mod::get_id() const
{
    return _id;
}

const std::wstring &Mod::get_name() const
{
    return _name;
}

const std::vector<std::wstring> &Mod::get_versions() const
{
    return _verisons;
}


int Mod::get_selected_version(){
    return _selected_version;
}

void Mod::set_selected_version(int selected_version){
    if (0 <= selected_version && selected_version <= _verisons.size()){
        _selected_version = selected_version;
    }
}

const std::wstring &Mod::get_version()
{
    return _verisons[_selected_version];
}

Mod::Type Mod::get_type() const{
    return _type;
}
