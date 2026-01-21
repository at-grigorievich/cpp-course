#pragma once
#include "ParserState.h"
#include "HtmlRenderer.h"

namespace MarkdownToHtml {
    class MarkdownContext {
    public:
        ParserState State;

        MarkdownContext();

        HtmlRenderer Renderer;
    };
};