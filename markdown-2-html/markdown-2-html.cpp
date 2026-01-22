
#include <iostream>
#include "MarkdownParser.h"
#include "MarkdownFileData.h"
#include <windows.h>
#include <future>

#define SINGLETHREAD_MODE 1
#define MULTITHREAD_MODE 2

#define USE_CHRONO

using namespace MarkdownToHtml;

template<typename Func, typename... Args>
void MeasureAndInvoke(const std::string& taskName, Func&& func, Args&&... args) {
    auto start = std::chrono::high_resolution_clock::now();

    std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

    auto end = std::chrono::high_resolution_clock::now();
    auto durationMs = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << taskName << " executed in " << durationMs.count() << " ms\n";
}

int ChooseThreadMode();
void InvokeSingleParsing(const std::vector<MarkdownFileData>& markdownSrcSet);
void InvokeParallelParsing(const std::vector<MarkdownFileData>& markdownSrcSet);
void InvokeSingleParsingWithChrono(const std::vector<MarkdownFileData>& markdownSrcSet);
void InvokeParallelParsingWithChrono(const std::vector<MarkdownFileData>& markdownSrcSet);

int main()
{
    setlocale(LC_ALL, "ru-RU");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<MarkdownFileData> markdownSrcSet = MarkdownFileData::FromUserInput();
    int selectedThreadMode = ChooseThreadMode();

#ifdef USE_CHRONO
    if (selectedThreadMode == SINGLETHREAD_MODE) {
        MeasureAndInvoke("Single-thread parsing", InvokeSingleParsing, markdownSrcSet);
    }
    else {
        MeasureAndInvoke("Multi-thread parsing", InvokeParallelParsing, markdownSrcSet);
    }
    return 0;
#endif 

    if (selectedThreadMode == SINGLETHREAD_MODE) {
        InvokeSingleParsing(markdownSrcSet);
    }
    else {
        InvokeParallelParsing(markdownSrcSet);
    }

    return 0;
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

void InvokeSingleParsingWithChrono(const std::vector<MarkdownFileData>& markdownSrcSet) {
    auto start = std::chrono::high_resolution_clock::now();
    InvokeSingleParsing(markdownSrcSet);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> sec = end - start;
    std::cout << "Method executed in " << sec.count() << " s\n";
}

void InvokeParallelParsingWithChrono(const std::vector<MarkdownFileData>& markdownSrcSet) {
    auto start = std::chrono::high_resolution_clock::now();
    InvokeParallelParsing(markdownSrcSet);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> sec = end - start;
    std::cout << "Method executed in " << sec.count() << " s\n";
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
