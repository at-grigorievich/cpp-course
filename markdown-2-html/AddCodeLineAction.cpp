#include "AddCodeLineAction.h"
#include "MarkdownContext.h"

namespace MarkdownToHtml {
    void AddCodeLineAction::Execute(MarkdownContext& ctx, const std::string& line) {
        ctx.Renderer.Add(line);
    }
}