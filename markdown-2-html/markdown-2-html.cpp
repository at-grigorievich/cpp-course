
#include <iostream>
#include "MarkdownParser.h"
#include "MarkdownFileData.h"
#include <windows.h>
#include <future>

int main()
{
    using namespace MarkdownToHtml;

    setlocale(LC_ALL, "ru-RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    MarkdownParser parser;

    std::string md =
        "# Main Title\n"
        "\n"
        "This is a simple paragraph with **bold text**, *italic text*, and `inline code`.\n"
        "\n"
        "## Subtitle\n"
        "\n"
        "Another paragraph here.\n"
        "\n"
        "### Smaller Title\n"
        "\n"
        "- This list item is ignored by current parser (optional future feature)\n"
        "- Another list item\n"
        "\n"
        "HTML block example:\n"
        "\n"
        "<h2>HTML Header Block</h2>\n"
        "<p>Some HTML paragraph inside Markdown.</p>\n"
        "\n"
        "Table Example:\n"
        "\n"
        "| Name   | Age | Country |\n"
        "|--------|-----|---------|\n"
        "| Alice  | 28  | UK      |\n"
        "| Bob    | 35  | US      |\n"
        "| Charlie| 22  | NL      |\n"
        "\n"
        "Code block:\n"
        "\n"
        "```\n"
        "#include <iostream>\n"
        "int main() {\n"
        "    std::cout << \"Hello, Markdown!\" << std::endl;\n"
        "    return 0;\n"
        "}\n"
        "```\n"
        "\n"
        "Empty lines above separate blocks.\n"
        "\n"
        "End with **bold**, *italic*, and `inline code` in one line.\n";

    
    std::vector<MarkdownFileData> markdownSrcSet = MarkdownFileData::FromUserInput();

    std::vector<std::future<void>> tasks;

    for (const MarkdownFileData mdFile : markdownSrcSet) {
        tasks.emplace_back(std::async(std::launch::async, [mdFile]() {
            std::ifstream in(mdFile.fullPath);
            std::stringstream buffer;
            buffer << in.rdbuf();

            MarkdownParser parser;
            std::string html = parser.Parse(buffer.str());

            if (!html.empty())
                MarkdownFileData::SaveAsHtml(mdFile, html);
            }));
    }

    for (auto& t : tasks) {
        t.get();
    }
}
