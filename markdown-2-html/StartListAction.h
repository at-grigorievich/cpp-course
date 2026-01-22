#pragma once

#include "IFSMAction.h"

namespace MarkdownToHtml {
    class StartListAction : public IFSMAction {
    private:
        std::string listTag;
    public:
        StartListAction(const std::string& tag) : listTag(tag) {}
        void Execute(MarkdownContext& ctx, const std::string& line) override;
    };
}