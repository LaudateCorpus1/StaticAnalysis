#include "ICommand.h"
#include "AnalysisRunner.h"

ICommand::ICommand(AnalysisRunner *parent) : mParent(parent)
{
}


ICommand::~ICommand(void)
{
}

void ICommand::initialise( const duint Base,const duint Size )
{
	mBase = Base;
	mSize = Size;
}

unsigned int ICommand::getInstruction( const duint bytesOffset, DISASM* disasm )
{
	return mParent->getInstruction(bytesOffset,disasm);
}
