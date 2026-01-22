#include <regex>
#include "AddListItemAction.h"
#include "MarkdownContext.h"
#include "InlineParser.h"
#include "LineAnalyzer.h"
#include "LineType.h"

namespace MarkdownToHtml {
    void AddListItemAction::Execute(MarkdownContext& ctx, const std::string& line) {
        std::string content = line;

        static std::regex ul(R"(^\s*[\*\-]\s+)");
        static std::regex ol(R"(^\s*\d+\.\s+)");

        // определяем тип строки через LineAnalyzer
        LineType type = LineAnalyzer::Analyze(line);
        if (type == LineType::UnorderedListItem) {
            content = std::regex_replace(content, ul, "");
        }
        else if (type == LineType::OrderedListItem) {
            content = std::regex_replace(content, ol, "");
        }

        ctx.Renderer.Add("<li>");
        ctx.Renderer.Add(InlineParser::Parse(content));
        ctx.Renderer.Add("</li>");
    }
}
