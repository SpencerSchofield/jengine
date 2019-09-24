#ifndef SCRIPT_H
#define SCRIPT_H

#include "jengine_define.h"

UNSURE

/*
 * Security vunerability using static cast for AST_~~~ types as it is a downcast
 *
 * Change to dynamic cast / similar
 * or better yet just reimplement
 *
 */

#include "script/jengine_interpreter.h"

namespace Jengine {

	namespace Script {

	}

} // namespace Jengine

#endif // SCRIPT_H
