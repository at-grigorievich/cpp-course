#include "EndParagraphAction.h"
#include "MarkdownContext.h"

namespace MarkdownToHtml {
    void EndParagraphAction::Execute(MarkdownContext& ctx, const std::string&) {
        ctx.Renderer.Add("</p>");
    }
}
