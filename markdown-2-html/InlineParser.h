#pragma once
#include <string>

namespace MarkdownToHtml {
    class InlineParser {
    public:
        // avaialble **bold**, *italic*, `code`
        static std::string Parse(const std::string& text);
    };
}
