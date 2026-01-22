#pragma once

#include "IFSMAction.h"

namespace MarkdownToHtml {
    class EndListAction : public IFSMAction {
    private:
        std::string listTag;
    public:
        EndListAction(const std::string& tag) : listTag(tag) {}
        void Execute(MarkdownContext& ctx, const std::string& line) override;
    };
}
