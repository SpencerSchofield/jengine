#ifndef SCRIPT_H
#define SCRIPT_H

#include <string>
#include <vector>

namespace Jengine {

	namespace Script {

		// class prototypes
		class Operator;

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
			std::string name;

		private:
		};

		class Expression {
		public:

			Expression();
			Expression(double value);
			Expression(std::string value);
			Expression(Operator* value);
			Expression(Identifier* value);
			Expression(unsigned int type, Expression* a, Expression* b);
			~Expression();

			Operator* op = nullptr;
			Identifier* identifier = nullptr;

			Identifier* value();
		private:
		};

		class Statement {
		public:
			Statement();

			std::vector<Identifier*> identifiers;
			std::vector<Expression> expressions;
			Statement* parent;

		private:
		};

		class Number : public Identifier {
		public:
			Number();
			Number(double value);
			Number(Identifier* identifier);

			operator Expression* const();

			double value;
		};

		class String : public Identifier {
		public:
			String(std::string value);
			String(Identifier* identifier);
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
			enum TYPE {
				IF,
				WHILE,
				RETURN
			};

			Keyword (Keyword::TYPE type);
			~Keyword();

			Keyword::TYPE type;
			Expression* expression;
			Statement* statement;
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
			~Operator();

			Expression* toExpression();

			Identifier* value();

		private:
			Operator::TYPE type;
			Expression* a;
			Expression* b;
		};


		Statement createProgram(std::string program);
		Statement createStatement(std::string program, bool& error, Statement* parent = nullptr);
	}

} // namespace Jengine

#endif // SCRIPT_H
