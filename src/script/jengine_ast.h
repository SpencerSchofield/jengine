#ifndef JENGINE_AST_H
#define JENGINE_AST_H

#include <vector>
#include "jengine_tokens.h"

namespace Jengine {
	namespace Script {

		enum class AST_TYPE {
			BinaryOperation,
			UnaryOperation,
			CompoundStatement,
			AssignmentStatement,
			WhileStatement,
			IfStatement,
			FunctionDeclaration,
			FunctionCall,
			Variable,
			TokenList,
			Empty
		};

		struct AST {
			AST(AST_TYPE type, const Token& token)
				: type(type), token(token) {
			}

			AST(AST_TYPE type)
				: type(type), token(TOKEN_TYPE::Invalid) {
			}

			AST_TYPE type;
			Token token;
		};

		// may not be needed
		struct AST_Variable : public AST {
			AST_Variable(const Token& value)
				: AST(AST_TYPE::Variable, value) {
			}
		};

		struct AST_TokenList : public AST {
			AST_TokenList()
				: AST(AST_TYPE::TokenList) {
			}

			std::vector<Token> list;
		};

		struct AST_BinaryOperation : public AST {
			AST_BinaryOperation(AST* left, const Token& op, AST* right)
				: AST(AST_TYPE::BinaryOperation, op), left(left), right(right){
			}

			AST* left;
			AST* right;
		};

		struct AST_UnaryOperation : public AST {
			AST_UnaryOperation(const Token& op, AST* value)
				: AST(AST_TYPE::UnaryOperation, op), value(value) {
			}

			AST* value;
		};

		struct AST_StatementList : public AST {
			AST_StatementList()
				: AST(AST_TYPE::CompoundStatement) {
			}

			std::vector<AST*> statements;
		};

		struct AST_FunctionDeclaration : public AST {
			AST_FunctionDeclaration(const Token& id, AST_TokenList* parameters, AST_StatementList* statement)
				: AST(AST_TYPE::FunctionDeclaration, id), statement(statement), parameters(parameters) {
			}

			AST_StatementList* statement;
			AST_TokenList* parameters;
		};

		struct AST_FunctionCall : public AST {
			AST_FunctionCall(const Token& id, AST_StatementList* arguments)
				: AST(AST_TYPE::FunctionCall, id), arguments(arguments) {
			}

			AST_StatementList* arguments;
		};

		struct AST_AssignmentStatement : public AST {
			AST_AssignmentStatement(const Token& id, AST* value)
				: AST(AST_TYPE::AssignmentStatement, id), value(value) {
			}

			AST* value;
		};

		struct AST_WhileStatement : public AST {
			AST_WhileStatement(AST* condition, AST* statement)
				: AST(AST_TYPE::WhileStatement), condition(condition), statement(statement) {
			}

			AST* condition;
			AST* statement;
		};

		struct AST_IfStatement : public AST {
			AST_IfStatement(AST* condition, AST* statement)
				: AST(AST_TYPE::IfStatement), condition(condition), statement(statement) {

			}

			AST* condition;
			AST* statement;
			AST* elseStatement;
		};

	} // namespace Script
} // namespace Jengine

#endif // JENGINE_AST_H
