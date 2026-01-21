#include "EndCodeBlockAction.h"
#include "MarkdownContext.h"

namespace MarkdownToHtml {
    void EndCodeBlockAction::Execute(MarkdownContext& ctx,const std::string&) {
        ctx.Renderer.Add("</pre>");
    }
}

