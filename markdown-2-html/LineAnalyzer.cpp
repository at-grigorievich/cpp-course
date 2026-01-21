#include "LineAnalyzer.h"
#include <regex>

namespace MarkdownToHtml {
    LineType LineAnalyzer::Analyze(const std::string& line) {
        if (line.empty())
            return LineType::Empty;
        if (line.rfind("```", 0) == 0)
            return LineType::CodeFence;
        if (line[0] == '#')
            return LineType::Header;

        static std::regex divider(R"(^\s*[:\-|]+\s*$)");
        if (std::regex_match(line, divider))
            return LineType::TableDivider;

        static std::regex row(R"(^\s*\|.*\|\s*$)");
        if (std::regex_match(line, row))
            return LineType::TableRow;


        return LineType::Text;
    }
}

