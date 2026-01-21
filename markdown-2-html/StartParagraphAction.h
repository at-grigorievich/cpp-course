#pragma once

#include "IFSMAction.h"

namespace MarkdownToHtml {
    class StartParagraphAction : public IFSMAction {
    public:
        void Execute(MarkdownContext& ctx, const std::string& line) override;
    };
}