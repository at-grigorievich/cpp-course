#pragma once

#include <string>
#include <vector>

namespace MarkdownToHtml {
    class HtmlRenderer {
    public:
        void Add(const std::string& html);
        std::string Result() const;
        void Clear();

    private:
        std::vector<std::string> _buffer;
    };
};