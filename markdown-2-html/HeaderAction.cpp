#include "HeaderAction.h"
#include "MarkdownContext.h"
#include "InlineParser.h"

namespace MarkdownToHtml {
    void HeaderAction::Execute(MarkdownContext& ctx, const std::string& line) {
        int level = 0;

        while (line[level] == '#') {
            level++;
        }

        std::string text = line.substr(level + 1);
        ctx.Renderer.Add(
            "<h" + std::to_string(level) + ">" + InlineParser::Parse(text) + "</h" + std::to_string(level) + ">"
        );
    }
}
