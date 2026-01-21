#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace MarkdownToHtml {
	struct MarkdownFileData {
        std::string fullPath; 
        std::string directory;
        std::string filename; 

        MarkdownFileData(const std::string& path) : fullPath(path) {
            std::filesystem::path p(path);
            directory = p.parent_path().string();
            filename = p.stem().string();        
        }

        static MarkdownFileData FromUserInput() {
            std::string path;

            while (true) {
                std::string outputForUser = "Select .md file: ";
                std::cout << outputForUser;
                std::getline(std::cin, path);

                std::filesystem::path p(path);
                if (p.extension() != ".md") {
                    std::cout << "Error: file must have extension .md\n";;
                    continue;
                }

                if (!std::filesystem::exists(p)) {
                    std::cout << "Error: File does not exist\n";
                    continue;
                }

                return MarkdownFileData(path);
            }
        }

        static std::string& SaveAsHtml(const MarkdownFileData& mdFile, const std::string& htmlContent) {
            std::filesystem::path htmlPath = std::filesystem::path(mdFile.directory) / (mdFile.filename + ".html");

            std::ofstream outFile(htmlPath);
            if (!outFile.is_open()) {
                throw std::runtime_error("Failed to create file: " + htmlPath.string());
            }

            outFile << htmlContent;
            std::cout << "HTML saved successfully to path: " << htmlPath << std::endl;
        }
	};
}