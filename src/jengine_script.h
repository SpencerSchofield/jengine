#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include <vector>

namespace Jengine {

	namespace Script {

		class Operator; // class prototype

		class Identifier {
		public:
			enum TYPE {
				NUMBER,
				STRING,
				FUNCTION,
				NUMBER_ARRAY,
				STRING_ARRAY,
				KEYWORD
			};

			Identifier(Identifier::TYPE type);

			Identifier::TYPE type;

		private:
		};

		class Expression {
		public:

			Expression();
			Expression(double value);
			Expression(std::string value);
			Expression(Operator* value);

			Operator* op;
			Identifier* identifier;

			Identifier* value();
		private:
		};

		class Statement {
		public:

		private:
		};

		class Number : public Identifier {
		public:
			Number(double value);
			double value;
		};

		class String : public Identifier {
		public:
			String(std::string value);
			std::string value;
		};

		class Function : public Identifier {
		public:
			Function(Statement body);
			Statement body;
			std::vector<Identifier*> parameters;
		};

		class NumberArray : public Identifier {
		public:
			std::vector<Number> value;
		};

		class StringArray : public Identifier {
		public:
			std::vector<String> value;
		};

		class Keyword : public Identifier {
		public:
			// JEff
		};

		class Operator {
		public:
			enum TYPE {
				// boolean
				ASSIGN,
				ADD,
				SUBTRACT,
				DIVIDE,
				MULTIPLY,
				INTEGER_DIVIDE,
				MOD,

				// unary
				NOT
			};

			Operator(Operator::TYPE type, Expression* a, Expression* b);

			Identifier* value();

		private:
			Operator::TYPE type;
			Expression* a;
			Expression* b;
		};

	}

} // namespace Jengine

#endif // SCRIPT_H
