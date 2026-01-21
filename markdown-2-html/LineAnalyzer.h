#pragma once

#include <string>
#include "LineType.h"

namespace MarkdownToHtml {
    class LineAnalyzer {
    public:
        static LineType Analyze(const std::string& line);
    };
}