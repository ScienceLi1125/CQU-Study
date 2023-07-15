#include "ir/ir_operand.h"

#include <string>
#include <utility>


ir::Operand::Operand(std::string  n, Type t): name(std::move(n)), type(t) {}
