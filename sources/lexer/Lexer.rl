#include <iostream>
#include <iterator>

#include "includes/p9/lexer/LexemeTypes.hh"

#include "p9/lexer/Lexer.hh"

using namespace p9;
using namespace p9::lexer;

%% machine p9lexer;
%% write data;

Lexer::Lexer( char const * p, std::size_t n )
: _p( p )
, _pe( _p + n )
, _eof( _pe )
, _ts( 0 )
, _te( 0 )
, _cs( 0 )
, _act( _cs )
{
}

Lexeme Lexer::consume( void )
{
	%%{
		Increment = "++" ;
		Decrement = "--" ;
		
		Assign = "=";
		
		AssignNumericAddition = "+=";
		AssignNumericSubstraction = "-=";
		AssignNumericMultiplication = "*=";
		AssignNumericDivision = "/=";
		AssignNumericModulo = "%=";
		
		AssignBinaryAnd = "&=";
		AssignBinaryOr = "|=";
		AssignBinaryXor = "^=";
		AssignBinaryLShift = "<<=";
		AssignBinaryRShift = ">>=";
		
		NumericAddition = "+";
		NumericSubstraction = "-";
		NumericMultiplication = "*";
		NumericDivision = "/";
		NumericModulo = "%";
		
		BinaryNot = "~";
		BinaryAnd = "&";
		BinaryOr = "|";
		BinaryXor = "^";
		BinaryLShift = "<<";
		BinaryRShift = ">>";
		
		LogicalNot = "!";
		LogicalAnd = "&&";
		LogicalOr = "||";
		
		RelationalEqual = "==";
		RelationalDifferent = "!=";
		RelationalLesser = "<";
		RelationalGreater = ">";
		RelationalLesserOrEqual = "<=";
		RelationalGreaterOrEqual = ">=";
		
		LBrace = "{";
		RBrace = "}";
		
		LParenthesis = "(";
		RParenthesis = ")";
		
		LBracket = "[";
		RBracket = "]";
		
		Dot = ".";
		Comma = ",";
		Semicolon = ";";
		Colon = ":";
		
		Mixed = "mixed";
		Void = "void";
		
		This = "this";
		Super = "super";

		New = "new";

		Function = "function";
		Class = "class";

		Public = "public";
		Private = "private";

		Import = "import";
		From = "from";
		As = "as";

		Return = "return";

		Identifier = [a-zA-Z]([a-zA-Z0-9_]*[a-zA-Z0-9]|[a-zA-Z0-9]*);
		Number = "0x"[0-9a-fA-F]|'0'[0-7]+|[0-9]+('.'[0-9]*)?|[0-9]*'.'[0-9]+;
		String = "\"\"";
		
		Spaces = [ \t]+;
        Newline = '\r''\n'|'\r'|'\n';
		
		main := |*
			
			Increment => { type = T_Increment; fbreak; };
			Decrement => { type = T_Decrement; fbreak; };
			Assign => { type = T_Assign; fbreak; };
			
			AssignNumericAddition => { type = T_AssignNumericAddition; fbreak; };
			AssignNumericSubstraction => { type = T_AssignNumericSubstraction; fbreak; };
			AssignNumericMultiplication => { type = T_AssignNumericMultiplication; fbreak; };
			AssignNumericDivision => { type = T_AssignNumericDivision; fbreak; };
			AssignNumericModulo => { type = T_AssignNumericModulo; fbreak; };
			
			AssignBinaryAnd => { type = T_AssignBinaryAnd; fbreak; };
			AssignBinaryOr => { type = T_AssignBinaryOr; fbreak; };
			AssignBinaryXor => { type = T_AssignBinaryXor; fbreak; };
			AssignBinaryLShift => { type = T_AssignBinaryLShift; fbreak; };
			AssignBinaryRShift => { type = T_AssignBinaryRShift; fbreak; };
			
			NumericAddition => { type = T_NumericAddition; fbreak; };
			NumericSubstraction => { type = T_NumericSubstraction; fbreak; };
			NumericMultiplication => { type = T_NumericMultiplication; fbreak; };
			NumericDivision => { type = T_NumericDivision; fbreak; };
			NumericModulo => { type = T_NumericModulo; fbreak; };
			
			BinaryNot => { type = T_BinaryNot; fbreak; };
			BinaryAnd => { type = T_BinaryAnd; fbreak; };
			BinaryOr => { type = T_BinaryOr; fbreak; };
			BinaryXor => { type = T_BinaryXor; fbreak; };
			BinaryLShift => { type = T_BinaryLShift; fbreak; };
			BinaryRShift => { type = T_BinaryRShift; fbreak; };
			
			LogicalNot => { type = T_LogicalNot; fbreak; };
			LogicalAnd => { type = T_LogicalAnd; fbreak; };
			LogicalOr => { type = T_LogicalOr; fbreak; };
			
			RelationalEqual => { type = T_RelationalEqual; fbreak; };
			RelationalDifferent => { type = T_RelationalDifferent; fbreak; };
			RelationalLesser => { type = T_RelationalLesser; fbreak; };
			RelationalGreater => { type = T_RelationalGreater; fbreak; };
			RelationalLesserOrEqual => { type = T_RelationalLesserOrEqual; fbreak; };
			RelationalGreaterOrEqual => { type = T_RelationalGreaterOrEqual; fbreak; };
			
			LBrace => { type = T_LBrace; fbreak; };
			RBrace => { type = T_RBrace; fbreak; };
			
			LParenthesis => { type = T_LParenthesis; fbreak; };
			RParenthesis => { type = T_RParenthesis; fbreak; };
			
			LBracket => { type = T_LBracket; fbreak; };
			RBracket => { type = T_RBracket; fbreak; };
			
			Dot => { type = T_Dot; fbreak; };
			Comma => { type = T_Comma; fbreak; };
			Semicolon => { type = T_Semicolon; fbreak; };
			Colon => { type = T_Colon; fbreak; };
			
			Mixed => { type = T_Mixed; fbreak; };
			Void => { type = T_Void; fbreak; };

			This => { type = T_This; fbreak; };
			Super => { type = T_Super; fbreak; };

			New => { type = T_New; fbreak; };

			Function => { type = T_Function; fbreak; };
			Class => { type = T_Class; fbreak; };

			Public => { type = T_Public; fbreak; };
			Private => { type = T_Private; fbreak; };

			Import => { type = T_Import; fbreak; };
			From => { type = T_From; fbreak; };
			As => { type = T_As; fbreak; };
			
			Return => { type = T_Return; fbreak; };
			
			Identifier => { type = T_Identifier; fbreak; };
			Number => { type = T_Number; fbreak; };
			String => { type = T_String; fbreak; };
			
			Spaces => { type = T_Spaces; fbreak; };
			Newline => { type = T_Newline; fbreak; };
			
			any => { fbreak; };
			
		*|;
	}%%;
	
	int type = 0;
	
	%% variable p _p;
	%% variable pe _pe;
	%% variable eof _eof;
	
	%% variable ts _ts;
	%% variable te _te;
	
	%% variable cs _cs;
	%% variable act _act;
	
	%% write init;
	%% write exec;
	
	if ( _p == _pe )
		
		return Lexeme::endOfFile;
	
	if ( ! type )
		
		return Lexeme::invalid;
	
	return Lexeme( type, _ts, _te - _ts );
}
