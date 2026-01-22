#pragma once

namespace MarkdownToHtml {
	enum class ParserState
	{
		None,
		Paragraph,
		CodeBlock,
		Table,
		UnorderedList,
		OrderedList
	};
}