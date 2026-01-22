
#include <iostream>
#include "MarkdownParser.h"
#include "MarkdownFileData.h"
#include <windows.h>
#include <future>

#define SINGLETHREAD_MODE 1
#define MULTITHREAD_MODE 1

using namespace MarkdownToHtml;

int ChooseThreadMode();
void InvokeSingleParsing(const std::vector<MarkdownFileData>& markdownSrcSet);
void InvokeParallelParsing(const std::vector<MarkdownFileData>& markdownSrcSet);

int main()
{
    setlocale(LC_ALL, "ru-RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    /*std::string md =
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
        "End with **bold**, *italic*, and `inline code` in one line.\n";*/

    std::vector<MarkdownFileData> markdownSrcSet = MarkdownFileData::FromUserInput();
    int selectedThreadMode = ChooseThreadMode();

    if (selectedThreadMode == SINGLETHREAD_MODE) {
        InvokeSingleParsing(markdownSrcSet);
    }
    else {
        InvokeParallelParsing(markdownSrcSet);
    }
}

int ChooseThreadMode() {
    while (true) {
        std::cout << "Select mode: 1 = single-thread, 2 = multi-thread: ";
        int mode = 0;
        std::cin >> mode;
        std::cin.ignore();

        if (mode == 1) return SINGLETHREAD_MODE;
        if (mode == 2) return MULTITHREAD_MODE;

        std::cout << "Invalid mode selected.\n";
    } 
}

void InvokeSingleParsing(const std::vector<MarkdownFileData>& markdownSrcSet) {
    using namespace MarkdownToHtml;

    MarkdownParser parser;

    for (const MarkdownFileData& mdFile : markdownSrcSet) {
        std::ifstream in(mdFile.fullPath);
        std::stringstream buffer;
        buffer << in.rdbuf();

        std::string html = parser.Parse(buffer.str());

        if (html.empty() == false)
            MarkdownFileData::SaveAsHtml(mdFile, html, false);
    }
}

void InvokeParallelParsing(const std::vector<MarkdownFileData>& markdownSrcSet) {
    std::vector<std::future<void>> tasks;

    for (const MarkdownFileData mdFile : markdownSrcSet) {
        tasks.emplace_back(std::async(std::launch::async, [mdFile]() {
            std::ifstream in(mdFile.fullPath);
            std::stringstream buffer;
            buffer << in.rdbuf();

            MarkdownParser parser;
            std::string html = parser.Parse(buffer.str());

            if (html.empty() == false)
                MarkdownFileData::SaveAsHtml(mdFile, html, true);
            }));
    }

    for (auto& t : tasks) {
        t.get();
    }
}
