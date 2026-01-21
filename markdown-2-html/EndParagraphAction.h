#pragma once
#include "IFSMAction.h"

namespace MarkdownToHtml {
    class EndParagraphAction : public IFSMAction {
    public:
        void Execute(MarkdownContext& ctx, const std::string&) override;
    };
}