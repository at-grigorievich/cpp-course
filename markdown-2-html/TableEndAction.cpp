#include "TableEndAction.h"
#include "MarkdownContext.h"

namespace MarkdownToHtml {
	void MarkdownToHtml::TableEndAction::Execute(MarkdownContext& ctx, const std::string& line)
	{
		ctx.Renderer.Add("</table>");
	}
}
