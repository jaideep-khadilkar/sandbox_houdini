/*
 * Copyright (c) 2015
 *	Side Effects Software Inc.  All rights reserved.
 *
 * Redistribution and use of Houdini Development Kit samples in source and
 * binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. The name of Side Effects Software may not be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE `AS IS' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *----------------------------------------------------------------------------
 */

#ifndef __DOP_GroupAndApply_h__
#define __DOP_GroupAndApply_h__

#include <DOP/DOP_Node.h>

namespace HDK_Sample {

class DOP_GroupAndApply : public DOP_Node
{
public:
	     DOP_GroupAndApply(OP_Network *net, const char *name,
			       OP_Operator *op);
    virtual ~DOP_GroupAndApply();

    static OP_Node		*myConstructor(OP_Network *net,
					       const char *name,
					       OP_Operator *op);
    static PRM_Template		 myTemplateList[];

protected:
    virtual void	 processObjectsSubclass(fpreal time,
					int foroutputidx,
					const SIM_ObjectArray &objects,
					DOP_Engine &engine);
    virtual void	 getInputInfoSubclass(int inputidx,
					DOP_InOutInfo &info);
    virtual void	 getOutputInfoSubclass(int inputidx,
					DOP_InOutInfo &info);

private:
    void		 GROUP(UT_String &str, fpreal t);
    int			 INPUTINDEX(fpreal t);
};

}

#endif
