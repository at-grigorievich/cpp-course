#pragma once
#include "IFSMAction.h"

namespace MarkdownToHtml {
    class AddCodeLineAction : public IFSMAction {
    public:
        void Execute(MarkdownContext& ctx, const std::string& line) override;
    };
}
