#include "StartCodeBlockAction.h"
#include "MarkdownContext.h"

namespace MarkdownToHtml {
    void StartCodeBlockAction::Execute(MarkdownContext& ctx, const std::string&) {
        ctx.Renderer.Add("<pre>");
    }
}
