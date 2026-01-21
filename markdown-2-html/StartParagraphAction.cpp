#include "StartParagraphAction.h"
#include "MarkdownContext.h"

namespace MarkdownToHtml {
    void StartParagraphAction::Execute(MarkdownContext& ctx, const std::string&) {
        ctx.Renderer.Add("<p>");
    }
}
