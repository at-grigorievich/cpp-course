#include "EndListAction.h"
#include "MarkdownContext.h"

namespace MarkdownToHtml {
    void EndListAction::Execute(MarkdownContext& ctx, const std::string& line) {
        ctx.Renderer.Add(listTag);
    }
}
