/**
 * @file ir_reader.h
 * @author Yuntao Dai (d1581209858@live.com)
 * @brief ir reader, for reading a text to ir::Program
 * @version 0.1
 * @date 2023-03-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef IR_READER_H
#define IR_READER_H

#include"ir/ir.h"

#include<fstream>


namespace ir {

// definition of Reader
struct Reader {
    /**
     * @brief read from input file and translate it into a ir::Program if it's a valid ir file
     * @param fin: the input ir src file
     * @return return a nullptr if the input file is invalid, else return a pointer to ir::Program, caller should free it
     */
    static ir::Program* read(std::ifstream& fin);
};
    
} // namespace ir


#endif