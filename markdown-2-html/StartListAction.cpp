#include "StartListAction.h"
#include "MarkdownContext.h"

namespace MarkdownToHtml {
    void StartListAction::Execute(MarkdownContext& ctx, const std::string& line) {
        ctx.Renderer.Add(listTag);
    }
}
