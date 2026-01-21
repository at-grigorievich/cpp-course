#include "MarkdownFsmTable.h"

#include "StartParagraphAction.h"
#include "EndParagraphAction.h"
#include "AddTextAction.h"
#include "HeaderAction.h"
#include "StartCodeBlockAction.h"
#include "EndCodeBlockAction.h"
#include "AddCodeLineAction.h"
#include "TableStartAction.h"
#include "TableEndAction.h"
#include "TableRowAction.h"

namespace MarkdownToHtml {
    MarkdownFsmTable::MarkdownFsmTable() {

        // None → Text → Paragraph
        _table[{ParserState::None, LineType::Text}] = {
            ParserState::Paragraph,
            {
                std::make_shared<StartParagraphAction>(),
                std::make_shared<AddTextAction>()
            }
        };

        // Paragraph → Text
        _table[{ParserState::Paragraph, LineType::Text}] = {
            ParserState::Paragraph,
            {
                std::make_shared<AddTextAction>()
            }
        };

        // Paragraph → Empty → None
        _table[{ParserState::Paragraph, LineType::Empty}] = {
            ParserState::None,
            {
                std::make_shared<EndParagraphAction>()
            }
        };

        // Header
        _table[{ParserState::None, LineType::Header}] = {
            ParserState::None,
            {
                std::make_shared<HeaderAction>()
            }
        };

        // Code block start
        _table[{ParserState::None, LineType::CodeFence}] = {
            ParserState::CodeBlock,
            {
                std::make_shared<StartCodeBlockAction>()
            }
        };

        // Code block content
        _table[{ParserState::CodeBlock, LineType::Text}] = {
            ParserState::CodeBlock,
            {
                std::make_shared<AddCodeLineAction>()
            }
        };

        // Code block end
        _table[{ParserState::CodeBlock, LineType::CodeFence}] = {
            ParserState::None,
            {
                std::make_shared<EndCodeBlockAction>()
            }
        };

        // None → TableRow → Table
        _table[{ParserState::None, LineType::TableRow}] = {
            ParserState::Table,
            {
                std::make_shared<TableStartAction>(),
                std::make_shared<TableRowAction>()
            }
        };

        // Table → TableRow → Table
        _table[{ParserState::Table, LineType::TableRow}] = {
            ParserState::Table,
            {
                std::make_shared<TableRowAction>()
            }
        };

        // Table → Empty → None (конец таблицы)
        _table[{ParserState::Table, LineType::Empty}] = {
            ParserState::None,
            {
                std::make_shared<TableEndAction>()
            }
        };

        // Table → Text → None (если после таблицы обычный текст)
        _table[{ParserState::Table, LineType::Text}] = {
            ParserState::None,
            {
                std::make_shared<TableEndAction>(),
                std::make_shared<StartParagraphAction>(),
                std::make_shared<AddTextAction>()
            }
        };
    }

    const FsmTransition*
        MarkdownFsmTable::Find(ParserState state, LineType type) const {
        auto it = _table.find({ state, type });
        return it == _table.end() ? nullptr : &it->second;
    }
}
