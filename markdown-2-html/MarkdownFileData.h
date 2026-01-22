#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <mutex> 

namespace MarkdownToHtml {
    inline std::mutex coutMutex;

	struct MarkdownFileData {
        std::string fullPath; 
        std::string directory;
        std::string filename; 

        MarkdownFileData(const std::string& path) : fullPath(path) {
            std::filesystem::path p(path);
            directory = p.parent_path().string();
            filename = p.stem().string();        
        }

        static std::vector<MarkdownFileData> FromUserInput() {
            std::vector<MarkdownFileData> result;

            while (true) {
                std::cout << "Enter path to .md file: ";

                std::string path;
                std::getline(std::cin, path);

                if (path.size() >= 2 &&
                    ((path.front() == '"' && path.back() == '"') ||
                        (path.front() == '\'' && path.back() == '\'')))
                {
                    path = path.substr(1, path.size() - 2);
                }

                std::filesystem::path p(path);

                if (p.extension() != ".md") {
                    std::cout << "Error: file must have extension .md\n";
                    continue;
                }

                if (!std::filesystem::exists(p)) {
                    std::cout << "Error: file does not exist\n";
                    continue;
                }

                result.emplace_back(path);

                while (true) {
                    std::cout << "Add another file? (y/n): ";

                    std::string answer;
                    std::getline(std::cin, answer);

                    if (answer == "y" || answer == "Y") {
                        break;
                    }

                    if (answer == "n" || answer == "N") {
                        return result;
                    }

                    std::cout << "Please enter 'y' or 'n'.\n";
                }
            }
        }

        static void SaveAsHtml(const MarkdownFileData& mdFile, const std::string& htmlContent, bool isParallel) {
            std::filesystem::path htmlPath = std::filesystem::path(mdFile.directory) / (mdFile.filename + ".html");

            std::ofstream outFile(htmlPath);
            if (!outFile.is_open()) {
                throw std::runtime_error("Failed to create file: " + htmlPath.string());
            }

            outFile << htmlContent;

            if(isParallel)
            {
                std::lock_guard<std::mutex> lock(coutMutex);
                std::cout << "HTML saved successfully to path: " << htmlPath << std::endl;
                return;
            }

            std::cout << "HTML saved successfully to path: " << htmlPath << std::endl;
        }
	};
}