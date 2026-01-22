#pragma once

namespace MarkdownToHtml {
	enum class LineType {
		Empty,
		Header,
		ListItem,
		CodeFence,
		Text,
		TableDivider,
		TableRow,
		UnorderedListItem,
		OrderedListItem 
	};
}