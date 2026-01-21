#include "TableRowAction.h"
#include "MarkdownContext.h"
#include "InlineParser.h"
#include <sstream>

namespace MarkdownToHtml {
    void TableRowAction::Execute(MarkdownContext& ctx, const std::string& line) {
        std::string row = "<tr>";

        std::istringstream ss(line);
        std::string cell;

        while (std::getline(ss, cell, '|')) {
            if (cell.empty()) continue;
            row += "<td>" + InlineParser::Parse(cell) + "</td>";
        }

        row += "</tr>";
        ctx.Renderer.Add(row);
    }
}