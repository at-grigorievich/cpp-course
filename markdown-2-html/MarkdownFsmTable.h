#pragma once

#include <map>
#include <utility>
#include "ParserState.h"
#include "LineType.h"
#include "FsmTransition.h"

namespace MarkdownToHtml {
    using FsmKey = std::pair<ParserState, LineType>;

    class MarkdownFsmTable {
    public:
        MarkdownFsmTable();
        const FsmTransition* Find(ParserState state, LineType type) const;

    private:
        std::map<FsmKey, FsmTransition> _table;
    };
}
