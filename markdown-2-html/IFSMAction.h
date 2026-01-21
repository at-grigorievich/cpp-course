#pragma once

#include <string>
#include "MarkdownContext.h"

namespace MarkdownToHtml {
	class IFSMAction {
	public:
		virtual ~IFSMAction() = default;
		virtual void Execute(MarkdownContext& ctx, const std::string& line) = 0;
	};
}