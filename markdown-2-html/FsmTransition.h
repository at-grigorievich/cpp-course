#pragma once
#include <vector>
#include <memory>
#include "ParserState.h"
#include "IFSMAction.h"

namespace MarkdownToHtml {
    struct FsmTransition {
        ParserState NextState;
        std::vector<std::shared_ptr<IFSMAction>> Actions;
    };
}