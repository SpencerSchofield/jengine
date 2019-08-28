#include "jengine_script.h"

namespace Jengine {

	namespace Script {

		Expression::Expression(double value)
		{
			this->identifier = new Number(value);
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

		Identifier* Operator::value()
		{
			Identifier* tempA = this->a->identifier;
			Identifier* output = nullptr;
			Identifier* aValue = this->a->value();
			Identifier* bValue = this->b->value();
			switch (this->type) {
				// boolean
				case ASSIGN:
					this->a->identifier = this->b->value();
					delete tempA;
					output = this->a->identifier;
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
			delete aValue;
			delete bValue;
			return output;
		}

		Number::Number(double value)
			: Identifier(Identifier::TYPE::NUMBER)
		{
			this->value = value;
		}

		String::String(std::string value)
			: Identifier(Identifier::TYPE::STRING)
		{
			this->value = value;
		}

		Identifier::Identifier(Identifier::TYPE type)
		{
			this->type = type;
		}

	}

} // namespace Jengine
