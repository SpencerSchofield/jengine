#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "jengine_parser.h"
#include "jengine_symbol.h"

namespace Jengine {
	namespace Script {

		class Interpreter
		{
		public:
			Interpreter(const Parser& parser)
				: parser(parser) {
			}

			void error() {
				std::cout << "Interpreter error\n";
			}

			Token visitBinaryOperation(AST* node) {
				Token left = visit(static_cast<AST_BinaryOperation*>(node)->left);
				Token right = visit(static_cast<AST_BinaryOperation*>(node)->right);

				if (node->token.type == TOKEN_TYPE::Plus) {
					return left + right;
				}
				if (node->token.type == TOKEN_TYPE::Minus) {
					return left - right;
				}
				if (node->token.type == TOKEN_TYPE::Modulo) {
					return left % right;
				}
				if (node->token.type == TOKEN_TYPE::Multiply) {
					return left * right;
				}
				if (node->token.type == TOKEN_TYPE::Divide) {
					return left / right;
				}
				if (node->token.type == TOKEN_TYPE::IntegerDivide) {
					return left.intDivide(right);
				}
				if (node->token.type == TOKEN_TYPE::More) {
					return left > right;
				}
				if (node->token.type == TOKEN_TYPE::Less) {
					return left < right;
				}
				if (node->token.type == TOKEN_TYPE::Equal) {
					return left == right;
				}
				if (node->token.type == TOKEN_TYPE::NotEqual) {
					return left != right;
				}
				if (node->token.type == TOKEN_TYPE::And) {
					return left && right;
				}
				if (node->token.type == TOKEN_TYPE::Or) {
					return left || right;
				}
				return Token();
			}

			Token visitUnaryOperation(AST* node) {
				Token value = visit(static_cast<AST_UnaryOperation*>(node)->value);
				if (node->token.type == TOKEN_TYPE::Plus) {
					return value;
				}
				if (node->token.type == TOKEN_TYPE::Minus) {
					return -value;
				}
				return Token();
			}

			Token visitCompoundStatement(AST* node) {
				Token result(TOKEN_TYPE::Invalid);
				AST_StatementList* theList = static_cast<AST_StatementList*>(node);
				for (unsigned int i = 0; i < theList->statements.size(); ++i) {
					result = visit(theList->statements[i]);
				}
				return result;
			}

			Token visitAssignmentStatement(AST* node) {
				Token value = visit(static_cast<AST_AssignmentStatement*>(node)->value);
				memory[static_cast<AST_AssignmentStatement*>(node)->token.value.s] = value;
				return value;
			}

			Token visitWhileStatement(AST* node) {
				Token result;
				while (visit(static_cast<AST_IfStatement*>(node)->condition)) {
					result = visit(static_cast<AST_IfStatement*>(node)->statement);
				}
				return result;
			}

			Token visitIfStatement(AST* node) {
				if (visit(static_cast<AST_IfStatement*>(node)->condition)) {
					return visit(static_cast<AST_IfStatement*>(node)->statement);
				}
				if (static_cast<AST_IfStatement*>(node)->elseStatement != nullptr) {
					return visit(static_cast<AST_IfStatement*>(node)->elseStatement);
				}
				return {TOKEN_TYPE::Invalid};
			}

			Token visitFunctionDeclaration(AST* node) {
				AST_FunctionDeclaration* t = static_cast<AST_FunctionDeclaration*>(node);
				functions[t->token.value.s] = t;
				return {TOKEN_TYPE::Invalid};
			}

			Token visitFunctionCall([[maybe_unused]] AST* node) {
				return Token();
			}

			Token visitVariable(AST* node) {
				if (node->token.isIdentifier()) {
					return memory[node->token.value.s];
				}
				return node->token;
			}

			Token visitTokenList([[maybe_unused]] AST* node) {
				return Token();
			}

			Token visitEmpty([[maybe_unused]] AST* node) {
				return Token();
			}

			Token visit(AST* node) {
				if (node->type == AST_TYPE::BinaryOperation) {
					return visitBinaryOperation(node);
				}
				if (node->type == AST_TYPE::UnaryOperation) {
					return visitUnaryOperation(node);
				}
				if (node->type == AST_TYPE::CompoundStatement) {
					return visitCompoundStatement(node);
				}
				if (node->type == AST_TYPE::AssignmentStatement) {
					return visitAssignmentStatement(node);
				}
				if (node->type == AST_TYPE::WhileStatement) {
					return visitWhileStatement(node);
				}
				if (node->type == AST_TYPE::IfStatement) {
					return visitIfStatement(node);
				}
				if (node->type == AST_TYPE::FunctionDeclaration) {
					return visitFunctionDeclaration(node);
				}
				if (node->type == AST_TYPE::FunctionCall) {
					return visitFunctionCall(node);
				}
				if (node->type == AST_TYPE::Variable) {
					return visitVariable(node);
				}
				if (node->type == AST_TYPE::TokenList) {
					return visitTokenList(node);
				}
				if (node->type == AST_TYPE::Empty) {
					return visitEmpty(node);
				}
				return Token();
			}

			Token run() {
				this->parser.parse();
				AST* node = this->parser.root;
				return visit(node);
			}

			Parser parser;
			SymbolTable table;
			std::unordered_map<std::string, Token> memory;
			std::unordered_map<std::string, AST_FunctionDeclaration*> functions;
		};

	} // namespace Script
} // namespace Jengine

#endif // INTERPRETER_H
