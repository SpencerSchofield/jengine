#include "jengine_script.h"

#include <cmath>
#include "jengine_file.h"
#include <vector>


#include <iostream>


namespace Jengine {

	namespace Script {

		Expression::Expression(double value)
		{
			this->identifier = new Number(value);
		}

		Expression::Expression(Operator* value)
		{
			this->op = value;
		}

		Expression::Expression(Identifier* value)
		{
			this->identifier = value;
		}

		Expression::Expression(unsigned int type, Expression* a, Expression* b)
		{
			this->op = new Operator((Operator::TYPE)type, a, b);
		}

		Expression::~Expression()
		{
			/*
			if (this->op)
				delete this->op;
			else
				delete this->identifier;
			*/
		}

		Identifier* Expression::value()
		{
			if (!this->identifier)
				return this->op->value();
			else
				return this->identifier;
		}

		Operator::Operator(Operator::TYPE type, Expression* a, Expression* b)
		{
			this->type = type;
			this->a = a;
			this->b = b;
		}

		Operator::~Operator()
		{
			delete this->a;
			if (this->b)
				delete this->b;
		}

		Expression* Operator::toExpression()
		{
			return new Expression(this);
		}

		Identifier* Operator::value()
		{
			Identifier* output = nullptr;
			Identifier* aValue = this->a->value();
			Identifier* bValue = this->b->value();
			switch (this->type) {
				// boolean
				case ASSIGN:
					if (!this->a->identifier)
						break;
					if (aValue->type == bValue->type) {
						if (aValue->type == Identifier::TYPE::NUMBER) {
							((Number*)this->a->identifier)->value = ((Number*)this->b->value())->value;
						}
						else if (aValue->type == Identifier::TYPE::STRING) {
							((String*)this->a->identifier)->value = ((String*)this->b->value())->value;
						}
						output = this->a->identifier;
					}
				break;

				case ADD:
					if (aValue->type == bValue->type) {
						// Fine
						if (aValue->type == Identifier::TYPE::NUMBER) {
							output = new Number(((Number*)aValue)->value+((Number*)bValue)->value);
						}
						if (aValue->type == Identifier::TYPE::STRING) {
							output = new String(((String*)aValue)->value+((String*)bValue)->value);
						}
					}
				break;

				case SUBTRACT:
					if (aValue->type == bValue->type) {
						// Fine
						if (aValue->type == Identifier::TYPE::NUMBER) {
							output = new Number(((Number*)aValue)->value-((Number*)bValue)->value);
						}
					}
				break;

				case DIVIDE:
					if (aValue->type == bValue->type) {
						// Fine
						if (aValue->type == Identifier::TYPE::NUMBER) {
							output = new Number(((Number*)aValue)->value/((Number*)bValue)->value);
						}
					}
				break;

				case MULTIPLY:
					if (aValue->type == bValue->type) {
						// Fine
						if (aValue->type == Identifier::TYPE::NUMBER) {
							output = new Number(((Number*)aValue)->value*((Number*)bValue)->value);
						}
					}
				break;

				case INTEGER_DIVIDE:
					if (aValue->type == bValue->type) {
						// Fine
						if (aValue->type == Identifier::TYPE::NUMBER) {
							output = new Number(((Number*)aValue)->value/(int)((Number*)bValue)->value);
						}
					}
				break;

				case MOD:
					if (aValue->type == bValue->type) {
						// Fine
						if (aValue->type == Identifier::TYPE::NUMBER) {
							output = new Number((int)((Number*)aValue)->value%(int)((Number*)bValue)->value);
						}
					}
				break;

				// unary
				case NOT:

				break;
			}
			return output;
		}

		Number::Number()
			: Identifier(Identifier::TYPE::NUMBER)
		{
			this->value = 0;
		}

		Number::Number(double value)
			: Identifier(Identifier::TYPE::NUMBER)
		{
			this->value = value;
		}

		Number::Number(Identifier* identifier)
			: Identifier(Identifier::TYPE::NUMBER)
		{
			if (identifier->type == this->type)
				this->value = ((Number*)identifier)->value;
			else
				this->value = nan("");
		}

		Jengine::Script::Number::operator Expression* const()
		{
			return new Expression(this);
		}

		String::String(std::string value)
			: Identifier(Identifier::TYPE::STRING)
		{
			this->value = value;
		}

		String::String(Identifier* identifier)
			: Identifier(Identifier::TYPE::STRING)
		{
			if (identifier->type == this->type)
				this->value = ((String*)identifier)->value;
			else
				this->value = "";
		}

		Identifier::Identifier(Identifier::TYPE type)
		{
			this->type = type;
		}

		Keyword::~Keyword()
		{
			if (this->expression)
				delete this->expression;
			if (this->statement)
				delete this->statement;
		}

		Statement createProgram(std::string program)
		{
			///////////////////////////
			// Purge Program of Junk //
			///////////////////////////

			// Remove all comments
			int found = 0;
			while ((found = program.find("//", found)) != -1) {
				program.erase(found, program.find('\n', found) - found);
			}

			// Remove all tabs
			program = Jengine::File::removeOccurences(program, "\t");

			// Remove all newlines
			program = Jengine::File::removeOccurences(program, "\t");

			// Remove all '\r' <- carriage returns??
			program = Jengine::File::removeOccurences(program, "\t");

			// Reduce spaces to single
			found = 0;
			while ((found = program.find("  ", found)) != -1) {
				program.erase(found, 1);
			}

			////////////////////
			// Get Down to it //
			////////////////////

			bool error;
			Statement out = createStatement(program, error);
			if (error)
				std::cout << "error\n";
			return out;
		}

		Statement createStatement(std::string program,  bool& error, Statement* parent)
		{
			Statement out;
			error = false;



			// Find functions
			int found = 0;
			while ((found = program.find("function ")) != -1) {

				// found beginning of function
				int start = program.find('{', found);
				if (start == -1)
					break;
				int a = start;
				int b = start;
				while (b<=a && b != -1) {
					a = program.find('}', a+1);
					b = program.find('{', b+1);
				}


				// Function body
				Function*  func = new Function(createStatement(program.substr(++start, a - start - 1), error));

				// add parameters

				start = program.find('(', found);
				int end = program.find(')', start);

				std::vector<std::string> params = Jengine::File::splitByDelimeter(program.substr(found+1, end - (found + 1)), ",");
				for (int i = params.size(); i--;) {
					params[i] = Jengine::File::removeOccurences(params[i], " ");
					if (params[i].length() != 0) {
						// add to parameters if it has an identifier

						if (params[i].find('$')) { // then string
							String* t = new String("");
							t->name = params[i];
							func->parameters.push_back(t);
						}
						else {// then number
							Number* t = new Number();
							t->name = params[i];
							func->parameters.push_back(t);
						}

					}
				}

				// set function name
				func->name = Jengine::File::removeOccurences(program.substr(found + 8, start-1), " ");


				program.erase(found, a - found + 1);
			}

			return out;
		}

		Statement::Statement()
		{

		}

		Function::Function(Statement body)
			: Identifier(Identifier::TYPE::FUNCTION)
		{
			this->body = body;
		}

	}

} // namespace Jengine
