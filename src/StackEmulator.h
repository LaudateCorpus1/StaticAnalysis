/* plugin:   (StaticAnalysis) for x64dbg <http://www.x64dbg.com>
 * author:   tr4ceflow@gmail.com <http://blog.traceflow.com>
 * license:  GLPv3
 */
#pragma once
#include "meta.h"

/* since some compilers don't use "push" to change the stack for arguments (see MingGW)
   we have to track all modifications to the stack for better analysis
   therefore we emulate the stack by only storing the virtual address from the last write-access

   -> advantage: we can track all modifications of the register for better placing of comments
*/

const unsigned int MAX_STACKSIZE = 50;

#define STACK_ERROR -1

class StackEmulator
{
	

	duint mStack[MAX_STACKSIZE];
	unsigned int mStackpointer;

public:
	StackEmulator(void);
	~StackEmulator(void);

	
	void pushFrom(duint addr);
	void popFrom(duint addr);
	void modifyFrom(int relative_offset, duint addr);

	void moveStackpointerBack(int offset);
	unsigned int pointerByOffset(int offset) const;
	duint lastAccessAtOffset(int offset) const;

	void emulate(const DISASM* disasm);
};

