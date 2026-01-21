#pragma once

#include "IFSMAction.h"

namespace MarkdownToHtml {
    class EndCodeBlockAction : public IFSMAction {
    public:
        void Execute(MarkdownContext& ctx, const std::string&) override;
    };
}