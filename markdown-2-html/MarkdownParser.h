#pragma once
#include <string>
#include "MarkdownContext.h"
#include "MarkdownFsmTable.h"
#include "MarkdownFileData.h"

namespace MarkdownToHtml {
    class MarkdownParser {
    public:
        std::string Parse(const std::string& markdown);
        std::string Parse(const MarkdownFileData& markdown);

    private:
        MarkdownContext _ctx;
        MarkdownFsmTable _fsm;
    };
}