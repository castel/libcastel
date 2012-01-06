#include <iostream>
#include <iterator>

#include <p9/lexer/Lexer.hh>
#include <p9/lexer/TokenDefinitions.hh>

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

Token Lexer::consume( void )
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
		
		Spaces = [ \r\n\t]+;
		
		main := |*
			
			Increment => { tok = Increment; fbreak; };
			Decrement => { tok = Decrement; fbreak; };
			Assign => { tok = Assign; fbreak; };
			
			AssignNumericAddition => { tok = AssignNumericAddition; fbreak; };
			AssignNumericSubstraction => { tok = AssignNumericSubstraction; fbreak; };
			AssignNumericMultiplication => { tok = AssignNumericMultiplication; fbreak; };
			AssignNumericDivision => { tok = AssignNumericDivision; fbreak; };
			AssignNumericModulo => { tok = AssignNumericModulo; fbreak; };
			
			AssignBinaryAnd => { tok = AssignBinaryAnd; fbreak; };
			AssignBinaryOr => { tok = AssignBinaryOr; fbreak; };
			AssignBinaryXor => { tok = AssignBinaryXor; fbreak; };
			AssignBinaryLShift => { tok = AssignBinaryLShift; fbreak; };
			AssignBinaryRShift => { tok = AssignBinaryRShift; fbreak; };
			
			NumericAddition => { tok = NumericAddition; fbreak; };
			NumericSubstraction => { tok = NumericSubstraction; fbreak; };
			NumericMultiplication => { tok = NumericMultiplication; fbreak; };
			NumericDivision => { tok = NumericDivision; fbreak; };
			NumericModulo => { tok = NumericModulo; fbreak; };
			
			BinaryNot => { tok = BinaryNot; fbreak; };
			BinaryAnd => { tok = BinaryAnd; fbreak; };
			BinaryOr => { tok = BinaryOr; fbreak; };
			BinaryXor => { tok = BinaryXor; fbreak; };
			BinaryLShift => { tok = BinaryLShift; fbreak; };
			BinaryRShift => { tok = BinaryRShift; fbreak; };
			
			LogicalNot => { tok = LogicalNot; fbreak; };
			LogicalAnd => { tok = LogicalAnd; fbreak; };
			LogicalOr => { tok = LogicalOr; fbreak; };
			
			RelationalEqual => { tok = RelationalEqual; fbreak; };
			RelationalDifferent => { tok = RelationalDifferent; fbreak; };
			RelationalLesser => { tok = RelationalLesser; fbreak; };
			RelationalGreater => { tok = RelationalGreater; fbreak; };
			RelationalLesserOrEqual => { tok = RelationalLesserOrEqual; fbreak; };
			RelationalGreaterOrEqual => { tok = RelationalGreaterOrEqual; fbreak; };
			
			LBrace => { tok = LBrace; fbreak; };
			RBrace => { tok = RBrace; fbreak; };
			
			LParenthesis => { tok = LParenthesis; fbreak; };
			RParenthesis => { tok = RParenthesis; fbreak; };
			
			LBracket => { tok = LBracket; fbreak; };
			RBracket => { tok = RBracket; fbreak; };
			
			Dot => { tok = Dot; fbreak; };
			Comma => { tok = Comma; fbreak; };
			Semicolon => { tok = Semicolon; fbreak; };
			Colon => { tok = Colon; fbreak; };
			
			Mixed => { tok = Mixed; fbreak; };
			Void => { tok = Void; fbreak; };
			This => { tok = This; fbreak; };
			New => { tok = New; fbreak; };
			Function => { tok = Function; fbreak; };
			Class => { tok = Class; fbreak; };
			Public => { tok = Public; fbreak; };
			Private => { tok = Private; fbreak; };
			Import => { tok = Import; fbreak; };
			From => { tok = From; fbreak; };
			As => { tok = As; fbreak; };
			Return => { tok = Return; fbreak; };
			
			Identifier => { tok = Identifier; fbreak; };
			Number => { tok = Number; fbreak; };
			String => { tok = String; fbreak; };
			
			Spaces => { next = true; fbreak; };
			
			any => { std::cout << "unexpected" << std::endl; };
			
		*|;
	}%%;
	
	bool next = false;
	int tok = 0;
	
	%% variable p _p;
	%% variable pe _pe;
	%% variable eof _eof;
	
	%% variable ts _ts;
	%% variable te _te;
	
	%% variable cs _cs;
	%% variable act _act;
	
	%% write init;
	%% write exec;
	
	if ( next )
		
		return consume( );
	
	if ( _p == _pe )
		
		return Token( Eof );
	
	return tok ? Token( tok, _ts, _te - _ts ) : Token( );
}
