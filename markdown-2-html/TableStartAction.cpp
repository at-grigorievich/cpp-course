#include "TableStartAction.h"
#include "MarkdownContext.h"

namespace MarkdownToHtml {
	void MarkdownToHtml::TableStartAction::Execute(MarkdownContext& ctx, const std::string& line)
	{
		ctx.Renderer.Add("<table>");
	}
}
