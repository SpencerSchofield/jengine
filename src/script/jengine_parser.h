#ifndef PARSER_H
#define PARSER_H

#include "jengine_lexer.h"
#include "jengine_ast.h"

namespace Jengine {
	namespace Script {

		class Parser
		{
		public:
			Parser(const Lexer& lexer)
				: lexer(lexer), currentToken(this->lexer.nextToken()), previous(AST_TYPE::Empty) {
			}

			void error(const std::string& msg = "") {
				std::cout << "Syntax error: Current Token (" << this->currentToken.toString() << ")\n" << msg << '\n';
				exit(-1);
			}

			void eat(TOKEN_TYPE tokenType) {
				if (this->currentToken.type == tokenType)
					this->currentToken = this->lexer.nextToken();
				else
					error("cannot eat token");
			}

			void eatIdentifier() {
				if (this->currentToken.type == TOKEN_TYPE::Integer) {
					return eat(TOKEN_TYPE::Integer);
				}
				if (this->currentToken.type == TOKEN_TYPE::Real) {
					return eat(TOKEN_TYPE::Real);
				}
				if (this->currentToken.type == TOKEN_TYPE::String) {
					return eat(TOKEN_TYPE::String);
				}
				error("cannot eat identifier");
			}

			// program				: statementList
			AST_StatementList* program() {
				return statementList();
			}

			// functionDeclaration	: "function" identifier "(" identifierList ")" compoundStatement
			AST_FunctionDeclaration* functionDeclaration() {
				eat(TOKEN_TYPE::Function);
				Token id = this->currentToken;
				eatIdentifier();
				eat(TOKEN_TYPE::Lparenthesis);
				AST_TokenList* parameters = identifierList();
				eat(TOKEN_TYPE::Rparenthesis);
				return new AST_FunctionDeclaration(id, parameters, compoundStatement());
			}

			Token identifier() {
				Token token = this->currentToken;
				eatIdentifier();
				return token;
			}

			// may not be needed
			AST* numberIdentifier() {

			}

			// may not be needed
			AST* stringIdentifier() {

			}

			AST_StatementList* compoundStatement() {
				AST_StatementList* result;
				eat(TOKEN_TYPE::LcurlyBrace);
				result = statementList();
				eat(TOKEN_TYPE::RcurlyBrace);
				previous = AST_TYPE::CompoundStatement;
				return result;
			}

			// statementList		: [statement {";" statement}]
			AST_StatementList* statementList() {
				AST_StatementList* result = new AST_StatementList;
				result->statements.push_back(statement());
				while (this->currentToken.type == TOKEN_TYPE::SemiColon) {
					if (this->previous != AST_TYPE::CompoundStatement) {
						eat(TOKEN_TYPE::SemiColon);
					}
					result->statements.push_back(statement());
				}
				return result;
			}

			// statement			: [functionDeclaration | compoundStatement | assignmentStatement | ifstatement | whilestatement | expression]
			AST* statement() {
				this->previous = AST_TYPE::Empty;
				if (this->currentToken.type == TOKEN_TYPE::Function) {
					return functionDeclaration();
				}
				else if (this->currentToken.type == TOKEN_TYPE::LcurlyBrace) {
					return compoundStatement();
				}
				else if (this->currentToken.isIdentifier()) {
					return assignmentStatement();
				}
				else if (this->currentToken.type == TOKEN_TYPE::If) {
					return ifstatement();
				}
				else if (this->currentToken.type == TOKEN_TYPE::While) {
					return whilestatement();
				}
				else {
					return expression();
				}
			}

			// assignmentStatement	: identifier "=" expression;
			AST_AssignmentStatement* assignmentStatement() {
				Token token = identifier();
				eat(TOKEN_TYPE::Assign);
				return new AST_AssignmentStatement(token, expression());
			}

			AST* conditional() {
				AST* result;
				eat(TOKEN_TYPE::Lparenthesis);
				result = expression();
				eat(TOKEN_TYPE::Rparenthesis);
				return result;
			}

			// ifstatement			: "if" conditional statement ["else" statement]
			AST_IfStatement* ifstatement() {
				eat(TOKEN_TYPE::If);
				AST_IfStatement* ifState = new AST_IfStatement(conditional(), statement());
				if (this->currentToken.type == TOKEN_TYPE::Else) {
					eat(TOKEN_TYPE::Else);
					ifState->elseStatement = statement();
				}
				return ifState;
			}

			// whilestatement		: "while" conditional statement
			AST_WhileStatement* whilestatement() {
				eat(TOKEN_TYPE::While);
				return new AST_WhileStatement(conditional(), statement());
			}

			// identifierList		: [identifier {"," identifier}]
			AST_TokenList* identifierList() {
				AST_TokenList* result = new AST_TokenList;
				if (!this->currentToken.isIdentifier())
					return result;
				result->list.push_back(identifier());
				while (this->currentToken.type == TOKEN_TYPE::Comma) {
					eat(TOKEN_TYPE::Comma);
					result->list.push_back(identifier());
				}
				return result;
			}

			// list				: expression ["," list]
			AST_StatementList* list() {
				AST_StatementList* result = new AST_StatementList;
				result->statements.push_back(expression());
				while (this->currentToken.type == TOKEN_TYPE::Comma) {
					eat(TOKEN_TYPE::Comma);
					result->statements.push_back(expression());
				}
				return result;
			}

			AST* expr_pre0() {
				if (Token token = this->currentToken;
					token.type == TOKEN_TYPE::Plus) {
					eat(TOKEN_TYPE::Plus);
					return expr_pre0();
				}
				else if (token.type == TOKEN_TYPE::Minus) {
					eat(TOKEN_TYPE::Minus);
					return new AST_UnaryOperation(token, expr_pre0());
				}
				else if (token.type == TOKEN_TYPE::IntegerLiteral
						 || token.type == TOKEN_TYPE::RealLiteral
						 || token.type == TOKEN_TYPE::StringLiteral) {
					eat(token.type);
					return new AST_Variable(token);
				}
				else if (token.type == TOKEN_TYPE::Lparenthesis) {
					eat(TOKEN_TYPE::Lparenthesis);
					AST* result = expression();
					eat(TOKEN_TYPE::Rparenthesis);
					return result;
				}
				else if (token.isIdentifier()) {
					eatIdentifier();
					if (this->currentToken.type == TOKEN_TYPE::LsquareBrace) {
						// index
						return index();
					}
					if (this->currentToken.type == TOKEN_TYPE::Lparenthesis) {
						// function call
						return call();
					}
					return new AST_Variable(token);
				}
				else {
					return new AST_Variable({TOKEN_TYPE::Invalid,0});
				}
			}

			AST* expr_pre1() {
				AST* left = expr_pre0();
				if (this->currentToken.type == TOKEN_TYPE::Modulo
					|| this->currentToken.type == TOKEN_TYPE::Multiply
					|| this->currentToken.type == TOKEN_TYPE::Divide
					|| this->currentToken.type == TOKEN_TYPE::IntegerDivide) {
					Token token = this->currentToken;
					eat(token.type);
					left = new AST_BinaryOperation(left, token, expr_pre0());
				}
				return left;
			}

			AST* expr_pre2() {
				AST* left = expr_pre1();
				if (this->currentToken.type == TOKEN_TYPE::Plus
					|| this->currentToken.type == TOKEN_TYPE::Minus) {
					Token token = this->currentToken;
					eat(token.type);
					left = new AST_BinaryOperation(left, token, expr_pre1());
				}
				return left;
			}

			AST* expr_pre3() {
				AST* left = expr_pre2();
				if (this->currentToken.type == TOKEN_TYPE::More
					|| this->currentToken.type == TOKEN_TYPE::Less) {
					Token token = this->currentToken;
					eat(token.type);
					left = new AST_BinaryOperation(left, token, expr_pre2());
				}
				return left;
			}

			AST* expr_pre4() {
				AST* left = expr_pre3();
				if (this->currentToken.type == TOKEN_TYPE::Equal
					|| this->currentToken.type == TOKEN_TYPE::NotEqual) {
					Token token = this->currentToken;
					eat(token.type);
					left = new AST_BinaryOperation(left, token, expr_pre3());
				}
				return left;
			}

			AST* expr_pre5() {
				AST* left = expr_pre4();
				if (this->currentToken.type == TOKEN_TYPE::And) {
					Token token = this->currentToken;
					eat(token.type);
					left = new AST_BinaryOperation(left, token, expr_pre4());
				}
				return left;
			}

			AST* expr_pre6() {
				AST* left = expr_pre5();
				if (this->currentToken.type == TOKEN_TYPE::Or) {
					Token token = this->currentToken;
					eat(token.type);
					left = new AST_BinaryOperation(left, token, expr_pre5());
				}
				return left;
			}

			AST* expression() {
				return expr_pre6();
			}

			AST_FunctionCall* call() {
				Token id = this->currentToken;
				eatIdentifier();
				eat(TOKEN_TYPE::Lparenthesis);
				AST_StatementList* arguments = list();
				eat(TOKEN_TYPE::Rparenthesis);
				return new AST_FunctionCall(id, arguments);
			}

			AST* index() {

			}


			void parse() {
				this->root = program();
			}

			Lexer lexer;
			Token currentToken;
			AST* root;
			AST_TYPE previous;
		};

	} // namespace Script
} // namespace Jengine

#endif // PARSER_H

/*
program				: statementList
functionDeclaration	: "function" identifier "(" identifierList ")" compoundStatement
identifier			: numberIdentifier | stringIdentifier
numberIdentifier	: letter {alnum}
stringIdentifier	: numberIdentifier "$"
compoundStatement	: "{" statementList "}"
statementList		: [statement {";" statement}]
statement			: [functionDeclaration | compoundStatement | assignmentStatement | ifstatement | whilestatement | expression]
assignmentStatement	: identifier "=" expression;
conditional			: "(" expression ")"
ifstatement			: "if" conditional statement ["else" statement]
whilestatement		: "while" conditional statement
identifierList		: [identifier {"," identifier}]
list				: [expression {"," expression}]
empty				:

expr_pre0			: "+" expr_pre0 | "-" expr_pre0 | number | string | "(" expression ")" | index | call | identifier
expr_pre1			: expr_pre0 {("%" | "*" | "/" | "//" ) expr_pre0}
expr_pre2			: expr_pre1 {("+" | "-") expr_pre1}
expr_pre3			: expr_pre2 {(">" | "<") expr_pre2}
expr_pre4			: expr_pre3 {("==" | "!=") expr_pre3}
expr_pre5			: expr_pre4 {"&&" expr_pre4}
expr_pre6			: expr_pre5 {"||" expr_pre5}
expression			: expr_pre6

call				: identifier "(" list ")"
index				: identifier "[" expression "]"

digit				: "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
letter				: "A" | "B" | ... | "Y" | "Z" | "a" | "b" | ... | "y" | "z"
alnum				: digit | letter
string				: {alnum}
number				: digit {digit} [.] {digit}
*/
