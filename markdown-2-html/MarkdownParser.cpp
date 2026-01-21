#include "MarkdownParser.h"
#include "LineAnalyzer.h"
#include <sstream>

namespace MarkdownToHtml {
    std::string MarkdownParser::Parse(const std::string& markdown) {
        std::istringstream ss(markdown);
        std::string line;

        while (std::getline(ss, line)) {
            LineType type = LineAnalyzer::Analyze(line);

            const FsmTransition* transition = _fsm.Find(_ctx.State, type);
            if (!transition) continue;

            for (auto& action : transition->Actions) {
                action->Execute(_ctx, line);
            }

            _ctx.State = transition->NextState;
        }

        return _ctx.Renderer.Result();
    }
}
