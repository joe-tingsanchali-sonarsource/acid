#pragma once

#include "Files/NodeFormat.hpp"

namespace acid {
class ACID_EXPORT Xml : public NodeFormatType<Xml> {
public:	
	static Node ParseString(std::string_view string);
	static void WriteStream(const Node &node, std::ostream &stream, Format format = Minified);

private:
	static void AddToken(std::string_view view, std::vector<Token> &tokens);
	static void Convert(Node &current, const std::vector<Token> &tokens, int32_t &k);
	static Node &CreateProperty(Node &current, const std::string &name);
	
	static void AppendData(const Node &node, std::ostream &stream, Format format, int32_t indent);
};
}
