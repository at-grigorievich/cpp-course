#include "InlineParser.h"
#include <regex>

namespace MarkdownToHtml {
    std::string InlineParser::Parse(const std::string& text) {
        std::string out = text;
        out = std::regex_replace(out, std::regex(R"(\*\*(.*?)\*\*)"), "<strong>$1</strong>");
        out = std::regex_replace(out, std::regex(R"(\*(.*?)\*)"), "<em>$1</em>");
        out = std::regex_replace(out, std::regex(R"(`(.*?)`)"), "<code>$1</code>");
        return out;
    }
}

