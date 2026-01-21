#pragma once
#include <string>
#include "MarkdownContext.h"
#include "MarkdownFsmTable.h"

namespace MarkdownToHtml {
    class MarkdownParser {
    public:
        std::string Parse(const std::string& markdown);

    private:
        MarkdownContext _ctx;
        MarkdownFsmTable _fsm;
    };
}