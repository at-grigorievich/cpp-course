#include <gtest/gtest.h>

#include "MarkdownParser.h"

using namespace MarkdownToHtml;

TEST(MarkdownParser, HeaderIsParsed)
{
    MarkdownParser parser;

    std::string md = "### Title";
    std::string html = parser.Parse(md);

    EXPECT_NE(html.find("<h3>"), std::string::npos);
    EXPECT_NE(html.find("Title"), std::string::npos);
}

TEST(MarkdownParser, BoldAndItalic)
{
    MarkdownParser parser;

    std::string md = "**bold** *italic*";
    std::string html = parser.Parse(md);

    EXPECT_NE(html.find("<strong>bold</strong>"), std::string::npos);
    EXPECT_NE(html.find("<em>italic</em>"), std::string::npos);
}

TEST(MarkdownParser, UnorderedList)
{
    MarkdownParser parser;

    std::string md =
        "* one\n"
        "* two\n"
        "\n";

    std::string html = parser.Parse(md);
    EXPECT_NE(html.find("<ul>"), std::string::npos);
    EXPECT_NE(html.find("<li>\none\n</li>"), std::string::npos);
    EXPECT_NE(html.find("<li>\ntwo\n</li>"), std::string::npos);
    EXPECT_NE(html.find("</ul>"), std::string::npos);
}

TEST(MarkdownParser, CodeBlock)
{
    MarkdownParser parser;

    std::string md =
        "``` cpp\n"
        "int x = 42;\n"
        "```\n";

    std::string html = parser.Parse(md);

    EXPECT_NE(html.find("<pre>"), std::string::npos);
    EXPECT_NE(html.find("int x = 42;"), std::string::npos);
}

TEST(MarkdownParserTableTest, SimpleTable) {
    std::string markdown =
        "| Name | Age | Country |\n"
        "|------|-----|---------|\n"
        "| Alice | 28 | UK |\n"
        "| Bob | 35 | US |\n"
        "| Charlie | 22 | NL |\n"
        "\n";

    MarkdownParser parser;
    std::string html = parser.Parse(markdown);

    std::string expected =
        "<table>\n"
        "<tr><td> Name </td><td> Age </td><td> Country </td></tr>\n"
        "<tr><td> Alice </td><td> 28 </td><td> UK </td></tr>\n"
        "<tr><td> Bob </td><td> 35 </td><td> US </td></tr>\n"
        "<tr><td> Charlie </td><td> 22 </td><td> NL </td></tr>\n"
        "</table>\n";

    EXPECT_NE(html.find("<table>"), std::string::npos);
    EXPECT_NE(html.find("<tr><td> Name </td><td> Age </td><td> Country </td></tr>"), std::string::npos);
    EXPECT_NE(html.find("<tr><td> Alice </td><td> 28 </td><td> UK </td></tr>"), std::string::npos);
    EXPECT_NE(html.find("<tr><td> Bob </td><td> 35 </td><td> US </td></tr>"), std::string::npos);
    EXPECT_NE(html.find("<tr><td> Charlie </td><td> 22 </td><td> NL </td></tr>"), std::string::npos);
    EXPECT_NE(html.find("</table>\n"), std::string::npos);

    EXPECT_EQ(html, expected);
}
