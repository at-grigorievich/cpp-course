#include "AddTextAction.h"
#include "MarkdownContext.h"
#include "InlineParser.h"

namespace MarkdownToHtml {
    void AddTextAction::Execute(MarkdownContext& ctx,
        const std::string& line) {
        ctx.Renderer.Add(InlineParser::Parse(line));
    }
}
