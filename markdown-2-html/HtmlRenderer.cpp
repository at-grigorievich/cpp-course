#include "HtmlRenderer.h"

namespace MarkdownToHtml {
    void HtmlRenderer::Add(const std::string& html) {
        _buffer.push_back(html);
    }

    std::string HtmlRenderer::Result() const {
        std::string out;
        for (const auto& line : _buffer) {
            out += line;
            out += '\n';
        }
        return out;
    }

    void HtmlRenderer::Clear() {
        _buffer.clear();
    }
}
