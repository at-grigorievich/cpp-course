#pragma once

#include "IFSMAction.h"
#include <iostream>

namespace MarkdownToHtml {
    class DebugAction : public IFSMAction {
    public:
        void Execute(MarkdownContext& ctx, const std::string& line) override {
            std::cout << "ASFSAFSAFSFSF" << line;
        }
    };
}
