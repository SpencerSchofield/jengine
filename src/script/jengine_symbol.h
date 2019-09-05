#ifndef JENGINE_SYMBOL_H
#define JENGINE_SYMBOL_H

#include "jengine_tokens.h"
#include <unordered_map>

#include <iostream>

namespace Jengine {
	namespace Script {

		enum class SYMBOL_TYPE {
			Integer,
			Real,
			String,
			IntegerFunction,
			RealFunction,
			StringFunction,
			Invalid
		};

		class SymbolTable {
		public:
			SymbolTable() {
				this->current = new SymbolList("global");
			}

			~SymbolTable() {
				delete this->current;
			}

			void error(const std::string& msg = "") {
				std::cout << "Symbol Error (" << this->current->name() << "): " << msg << '\n';
			}

			void addSymbol(const std::string& name, SYMBOL_TYPE type) {
				if (this->current->list.find(name) != this->current->list.end()) {
					this->current->list[name] = type;
				}
				else {
					error("duplicate symbol defined - " + name);
				}
			}

			SYMBOL_TYPE findSymbol(const std::string& name) {
				SYMBOL_TYPE t = this->current->findSymbol(name);
				if (t == SYMBOL_TYPE::Invalid)
					error("Symbol could not be found");
				return t;
			}

			void addScope(const std::string& name) {
				this->current = new SymbolList(name, this->current);
			}

			void removeScope() {
				SymbolList* t = this->current;
				this->current = this->current->parent;
				delete t;
			}

		private:

			class SymbolList {
			public:
				SymbolList(const std::string& name, SymbolList* parent = nullptr)
					: scopename(name), parent(parent) {
				}

				SYMBOL_TYPE findSymbol(const std::string& name) {
					if (this->list.find(name) != this->list.end()) {
						return this->list[name];
					}
					if (this->parent != nullptr) {
						return this->parent->findSymbol(name);
					}
					return SYMBOL_TYPE::Invalid;
				}

				std::string name() {
					std::string out = this->scopename;
					if (this->parent != nullptr) {
						out = this->parent->name() + ':' + out;
					}
					return out;
				}

				std::unordered_map<std::string, SYMBOL_TYPE> list;
				const std::string scopename;
				SymbolList* parent;
			};

			SymbolList* current;
		};

	}
}

#endif // JENGINE_SYMBOL_H
