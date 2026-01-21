#include "MarkdownParser.h"
#include "LineAnalyzer.h"
#include <sstream>
#include <iostream>
#include <fstream>

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

    std::string MarkdownParser::Parse(const MarkdownFileData& markdown) {
        std::ifstream file(markdown.fullPath);

        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл: " << markdown.fullPath << std::endl;
            return "";
        }

        std::string line;

        while (std::getline(file, line)) {
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
