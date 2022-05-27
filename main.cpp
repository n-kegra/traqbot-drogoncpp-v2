#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>
#include <yaml-cpp/yaml.h>
using namespace std;

string SnakeCaseToUpperCamelCase(string str) {
    int cnt = 0;
    string res;
    for (char c : str) {
        if (c == '_') {
            cnt = 0;
            continue;
        } else {
            res += char(cnt == 0 ? toupper(c) : tolower(c));
            cnt++;
        }
    }
    return res;
}

auto ind(int count) { return string(count, ' '); }

string getTypeString(string type) {
    if (type == "string")
        return "std::string";
    else if (type == "boolean")
        return "bool";
    else if (type == "number")
        return "int32_t";
    else if (type.front() == '$')
        return SnakeCaseToUpperCamelCase(type.substr(1));
    return "unknown";
}

string getTypeString(string type, bool array) {
    if (array) {
        return "std::vector<" + getTypeString(type) + ">";
    } else {
        return getTypeString(type);
    }
}

string getJsonToValueConvertCode(string node, string type, string name = "") {
    if (type == "string")
        return node + ".asString()";
    else if (type == "boolean")
        return node + ".asBool()";
    else if (type == "number")
        return node + ".asInt()";
    else {
        auto type_str = getTypeString(type);
        if (type_str == "unknown")
            type_str = "decltype(" + name + ")";
        return type_str + "().fromJson(" + node + ")";
    }
}

struct Item {
    using ItemArray = vector<pair<string, Item>>;
    variant<string, ItemArray> type;
    string flavor;
    bool array;

    void outputJsonFunction(ostream& ost, int indent, ItemArray& items) const {

        ost << ind(indent) << "auto& fromJson(const Json::Value& _json) {"
            << endl;
        for (const auto& item : items) {
            const auto& key = item.first;
            const auto& subitem = item.second;
            const auto type = holds_alternative<string>(subitem.type)
                                  ? get<string>(subitem.type)
                                  : "Object";

            if (subitem.array) {
                ost << ind(indent + 2) << "for(const auto& _subitem : _json[\""
                    << key << "\"]) {" << endl;
                ost << ind(indent + 4) << "this->" << key << ".push_back("
                    << getJsonToValueConvertCode("_subitem", type) << ");"
                    << endl;
                ost << ind(indent + 2) << "}" << endl;
            } else {
                ost << ind(indent + 2) << "this->" << key << " = "
                    << getJsonToValueConvertCode("_json[\"" + key + "\"]", type,
                                                 "this->" + key)
                    << ";" << endl;
            }
        }
        ost << ind(indent) << "  return *this;" << endl;
        ost << ind(indent) << "}" << endl;
        // ost << ind(indent) << "Json::Value toJson() {" << endl;
        // ost << ind(indent) << "  Json::Value _json;" << endl;
        // for (const auto& item : items) {
        //     ost << ind(indent + 2) << endl;
        // }
        // ost << ind(indent) << "  return _json;" << endl;
        // ost << ind(indent) << "}" << endl;
    }

    void outputModelStruct(ostream& ost, string type_name, string name = "",
                           int indent = 0) const {
        if (holds_alternative<string>(this->type)) {
            ost << ind(indent)
                << getTypeString(get<string>(this->type), this->array) << ' '
                << name << ';' << endl;
        } else if (holds_alternative<ItemArray>(this->type)) {
            if (type_name.empty()) {
                ost << ind(indent) << "struct {" << endl;
            } else {
                ost << ind(indent) << "struct " << type_name << " {" << endl;
            }
            auto subitems = get<ItemArray>(this->type);
            for (const auto& subitem : subitems) {
                subitem.second.outputModelStruct(ost, "", subitem.first,
                                                 indent + 2);
            }

            outputJsonFunction(ost, indent + 2, subitems);

            if (name.empty()) {
                ost << ind(indent) << "};" << endl;
            } else {
                ost << ind(indent) << "} " << name << ";" << endl;
            }
        }
    }
};

namespace YAML {

template <> struct convert<Item::ItemArray> {
    static bool decode(const Node& node, Item::ItemArray& items) {
        for (const auto& subitem : node) {
            auto key = subitem.first.as<string>();
            auto submodel = subitem.second.as<Item>();
            items.push_back({key, submodel});
        }
        return true;
    }
};

template <> struct convert<Item> {
    static bool decode(const Node& node, Item& item) {
        const auto _type = node["type"];
        if (_type.IsMap()) {
            item.type = _type.as<Item::ItemArray>();
        } else {
            item.type = _type.as<string>();
        }

        const auto _flavor = node["flavor"];
        item.flavor = _flavor.IsDefined() ? _flavor.as<string>() : ""s;

        const auto _array = node["array"];
        item.array = _array.IsDefined() ? _array.as<bool>() : false;
        return true;
    }
};
} // namespace YAML

int main(int, char **) {
    auto events = YAML::LoadFile("../events.yaml");
    auto models = YAML::LoadFile("../models.yaml");

    ofstream events_h{"../out/events.h"};
    ofstream models_h{"../out/models.h"};

    models_h << "#include <string>\n"
                "#include <vector>\n"
                "#include <json/json.h>\n"
                "\n"
                "namespace traQBot {\n";
    for (const auto& model : models) {
        auto model_name = model.first.as<string>();
        auto model_entity = model.second.as<Item>();
        model_entity.outputModelStruct(models_h,
                                       SnakeCaseToUpperCamelCase(model_name));
    }
    models_h << "}\n"
                "\n"
             << endl;

    events_h << "#include <string>\n"
                "#include <vector>\n"
                "#include <variant>\n"
                "#include <drogon/drogon.h>\n"
                "#include <json/json.h>\n"
                "#include \"models.h\"\n"
                "\n"
                "namespace traQBot {\n";
    for (const auto& event : events) {
        auto event_id = event.first.as<string>();
        auto event_model = event.second.as<Item>();
        event_model.outputModelStruct(
            events_h, SnakeCaseToUpperCamelCase(event_id) + "Event");
    }
    events_h << "\n"
                "using EventPayload = std::variant<\n";
    int eventCnt = 0;
    for (const auto& event : events) {
        auto event_id = event.first.as<string>();
        events_h << "  " << SnakeCaseToUpperCamelCase(event_id) + "Event"
                 << ((eventCnt + 1 == events.size()) ? "" : ",") << endl;
        eventCnt++;
    }
    events_h << ">;\n"
                "\n"
                "enum class EventType {\n";
    for (const auto& event : events) {
        auto event_id = event.first.as<string>();
        events_h << "  " << SnakeCaseToUpperCamelCase(event_id) << "," << endl;
    }
    events_h << "  Unknown,\n"
                "};\n"
                "struct EventData {\n"
                "  EventType event;\n"
                "  std::string requestId;\n"
                "  std::string token;\n"
                "  EventPayload payload;\n"
                "};\n"
                "\n"
                "}\n"
                "\n"
                "namespace drogon {\n"
                "\n"
                "template <>\n"
                "inline traQ::EventData fromRequest(const HttpRequest& req) {\n"
                "  auto event = req.getHeader(\"X-TRAQ-BOT-EVENT\");\n"
                "  auto requestId = req.getHeader(\"X-TRAQ-BOT-REQUEST-ID\");\n"
                "  auto token = req.getHeader(\"X-TRAQ-BOT-TOKEN\");\n"
                "  auto json = req.getJsonObject();\n"
                "  traQ::EventData data;\n"
                "  data.requestId = requestId;\n"
                "  data.event = traQ::EventType::Unknown;\n"
                "  data.token = token;\n"
                "  if (json) {\n";
    for (const auto& event : events) {
        auto event_id = event.first.as<string>();
        events_h << "    if (event == \"" << event_id << "\") {" << endl;
        events_h << "      data.event = traQ::EventType::"
                 << SnakeCaseToUpperCamelCase(event_id) << ";" << endl;
        events_h << "      data.payload = traQ::"
                 << SnakeCaseToUpperCamelCase(event_id)
                 << "Event().fromJson(*json);" << endl;
        events_h << "    } else" << endl;
    }
    events_h << "    {\n";
    events_h << "      data.event = traQ::EventType::Unknown;\n";
    events_h << "    }\n";
    events_h << "  }\n"
                "  return data;\n"
                "}\n"
                ""
                "}"
             << endl;
}
